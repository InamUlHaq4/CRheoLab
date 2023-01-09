#include "readHelpOperations.h"

std::string stripSingleComment(std::string& line)
{
    // strips from the string '//' onwards
    line=line.substr(0, line.find("//"));
    return line;
}


std::string stripBlockComment
(
    std::ifstream& in_file,
    std::string& line,
    int& lineCounter
)
{
    // Booleans to catch line and block comments
    bool findEndOfBlockComment = false;
    
    if((line.find( "*/" ) != std::string::npos))
    {
        std::string lineBackup=line;

        // strips line
        line=line.substr(0, line.find("/*"));
        lineBackup=lineBackup.substr(lineBackup.find("*/") + 2);
        line+= " "+lineBackup;
        return line;
    }
    // looks for the end of block comment
    while (!findEndOfBlockComment && !in_file.eof())
    {
        getline(in_file, line);
        lineCounter++;
        if((line.find( "*/" ) != std::string::npos))
        {
            findEndOfBlockComment=true;
            getline(in_file, line);
            lineCounter++;
        }
        else
        {
            continue;
        }
    }
    return line;
}

std::string stripComments
(
    std::ifstream& in_file, 
    std::string& line, 
    int& lineCounter
)
{
    bool checkComments=false;

    if(line.find( "//" ) != std::string::npos)
    {
        line = stripSingleComment(line);
        checkComments=true;
    }
    else if (line.find( "/*" ) != std::string::npos)
    {
        line = stripBlockComment(in_file, line, lineCounter);
        checkComments=true;
    }

    if (checkComments)
    {
        line = stripComments(in_file, line, lineCounter);
    }

    return line;
}

bool newLineAndUpdateSStream
(
    std::ifstream& in_file, 
    std::istringstream& iss, 
    std::string& line, 
    int& lineCounter, 
    bool updateStringStream
)
{
    if (getline(in_file, line))
        lineCounter++;
    else 
        return false;

    // Avoid empty lines
    while(line.find_first_not_of(' ') == std::string::npos && !in_file.eof())
    {
        if(getline(in_file, line))
            lineCounter++;
        else 
            return false;
    }

    line = stripComments(in_file, line, lineCounter);

    trimWhiteSpaces(line);

    if (updateStringStream)
    {
        // Update string stream
        iss.clear();
        iss.str(line);
    }

    return true;
}

bool checkCharacter
(
    std::ifstream& in_file, 
    std::istringstream& iss, 
    const char& C
)
{
    char c1;

    iss >> c1;

    if (iss.fail() || c1 != C)
    {
        return false;
    }

    return true;
}

void errorMessage
(
    std::ifstream& in_file, 
    const std::string& message, 
    int lineCounter, 
    bool turnOfLinePrinting
)
{
    // Error message to the user
    std::string errorMessage = message ;

    if (!turnOfLinePrinting)
    {
        errorMessage += "in line " + std::to_string(lineCounter);
    }

    // Closes the file
    in_file.close();

    // Throws exception to stop the program.
    throw std::runtime_error(errorMessage);
}

void checkSemiColon 
(
    std::ifstream& in_file, 
    std::string& line, 
    const int& lineCounter
)
{
    if ((line.find( ';' ) == std::string::npos))
    {
        errorMessage(in_file, "Missing ';' ", lineCounter);
    }
}

void vectorFormatError(std::ifstream& in_file, int lineCounter)
{
    std::string errorMessage = "Problem with vector format on line ";
    errorMessage +=  std::to_string(lineCounter);

    // Closes the file
    in_file.close();

    // Throws exception to stop the program.
    throw std::runtime_error(errorMessage);
};


double readScalarData
(
    std::ifstream& in_file, 
    std::istringstream& iss, 
    std::string& line, 
    int lineCounter
)
{

    line = stripComments(in_file, line, lineCounter);

    // update string stream
    iss.clear();
    iss.str(line);

    // Store data
    double scalar;

    iss >> scalar;

    // If something is wrong with string stream warn the user
    if (iss.fail())
    {
        errorMessage(in_file, "Problem reading scalar ", lineCounter);
    }
    
    return scalar;
}


std::string readString
(
    std::ifstream& in_file, 
    std::istringstream& iss, 
    std::string& line, 
    int lineCounter, 
    bool semiColumCheck = true
)
{

    if (semiColumCheck)
    {
        checkSemiColon(in_file, line, lineCounter);
        
        // Remove semicolum
        line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

    }

    line = stripComments(in_file, line, lineCounter);

    // Remove empty spaces
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

    // update string stream
    iss.clear();
    iss.str(line);

    // Store data
    std::string store;

    iss >> store;

    // If something is wrong with string stream warn the user
    if (iss.fail())
    {
        errorMessage(in_file, "Problem reading scalar ", lineCounter);
    }
    
    return store;
}


void readCharacter(std::ifstream& in_file, std::istringstream& iss, const char C, const int& lineCounter)
{
    char c1;

    iss >> c1;

    // If something is wrong, warn the user and shutdown program
    if (iss.fail() || c1 != C)
    {

        std::string message = "Missing ";
        message += C;
        message += " ";

        errorMessage(in_file, message, lineCounter);
    }
}

