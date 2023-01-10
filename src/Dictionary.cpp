#include "Dictionary.h"

// From string
Dictionary::Dictionary(const std::string& path)
{
    filePath_ = path;
}

// Construct from IOobject
Dictionary::Dictionary(const IOObject& IO)
{
    filePath_ = IO.path();
    read();
}

Dictionary::Dictionary(const Dictionary& otherDict)
: 
localData_(otherDict.localData_)
{
    for(const auto& elem : otherDict.data_) 
    {
        if(elem.second) 
            data_.emplace(elem.first, std::make_unique<Dictionary>(*elem.second));
        else 
            data_.emplace(elem.first, nullptr);
    }
}

void Dictionary::bracketsTest(std::ifstream& in_file)            
{
    
    int openedBracketCounter(0);

    int closedBracketCounter(0);

    int lineCounter(0);

    std::string line;

    std::istringstream iss(line);

    while (!in_file.eof())
    {
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);
        openedBracketCounter += std::count(line.begin(), line.end(),'{');
        closedBracketCounter += std::count(line.begin(), line.end(),'}');
    }

    if (openedBracketCounter != closedBracketCounter)
    {
        in_file.close();
        std::string message = "Unbalanced number of brackets in dictionary";
        throw std::runtime_error(message);
    }

    in_file.clear();
    in_file.seekg(0);
}


bool Dictionary::read()
{
    // Passes the file location path into a ifsteam
    std::ifstream in_file(filePath_.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        return false;
    }

    bracketsTest(in_file);

    std::string line;
    std::istringstream iss (line);

    int lineCounter(0);

    nOpenParenthesis_ = 0;

    std::string possibleDictKeyword;

    // Read file
    while ( (nOpenParenthesis_ == 0) && !in_file.eof() )
    { 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

        if (line.find('{') != std::string::npos)
        {
            nOpenParenthesis_ ++;
        }
        
        if (nOpenParenthesis_ != 0)
        {
            std::string keyword;

            std::vector<std::string> vList (splitString(line,'{')); // Split by curly

            if(vList.empty() || vList[0].empty() )
            {
                keyword = possibleDictKeyword;
                line.erase(line.find("{"), 1);
                iss.clear();
                iss.str(line);
            }
            else
            {
                keyword = vList[0];    

                line.clear();

                for(unsigned int i = 1; i<vList.size(); i ++)
                {
                    if (i == 1)
                    {
                        line += vList[i];
                    }
                    else
                    {
                        line += '{' + vList[i];
                    }
                }
                iss.str(line);    
            }
        
            // Remove whitespaces
            trimWhiteSpaces(keyword);
            
            readSubDict(*this, in_file, iss, line, lineCounter, keyword);
        }
    
        else
        {
            if (!line.empty())
            {
                if (line.back() == ';')
                {
                    stripAndAppendToMap(line, localData_);
                }
                else
                {
                    possibleDictKeyword = line;
                }         
            }
        }
    }

    return true;
}


void Dictionary::readSubDict(Dictionary& tmp, std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter,const std::string& key)
{
    std::unique_ptr<Dictionary> tmp2Ptr = std::make_unique<Dictionary>();

    Dictionary& tmp2 = *tmp2Ptr;
    tmp2.nOpenParenthesis_ = tmp.nOpenParenthesis_;
    tmp2.finishedReadingSubDicts_ = tmp.finishedReadingSubDicts_;

    std::string keyword;

    while ( !tmp2.finishedReadingSubDicts_  && !in_file.eof() )
    {
        int newOpenParenthesis = nOpenParenthesis_; // update number of open parenthesis

        if (line.empty() || std::all_of(line.begin(),line.end(),isspace) ) // If line is empty or with only white spaces
        { 
            newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);
        }
        
        if (!line.empty() 
            && std::count(line.begin(), line.end(), ' ') == 0  
            && line[0] != '}' 
            && line.back() != ';'
            )
        {
            std::string keyword = line;
            newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);

            if (line[0] == '{')
            {
                line.erase(line.find("{"), 1); // erase from the string
                iss.clear(); // clear string stream
                iss.str(line); // update string stream
                nOpenParenthesis_++; // update number of open parenthesis
                readSubDict(tmp2, in_file, iss, line, lineCounter, keyword); // read dictionary
            }
            else
            {
                errorMessage(in_file, "Error while reading dictionary, on line: ", lineCounter);
            }
        }

        // Parse the string
        parseString(line, iss, in_file, tmp2, lineCounter);

        if (nOpenParenthesis_ < newOpenParenthesis)
        {
            newOpenParenthesis = nOpenParenthesis_;
            tmp2.finishedReadingSubDicts_ = true;
        }
    }    

    tmp.data_.emplace(key, std::move(tmp2Ptr));
}


bool Dictionary::readDict(const std::string& dictName)
{
       // Passes the file location path into a ifsteam
    std::ifstream in_file(filePath_.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        return false;
    }

    std::string line;
    std::istringstream iss (line);

    int lineCounter(0);

    nOpenParenthesis_ = 0;

    std::string possibleDictKeyword = dictName;

    bool foundKeyword = false;
    bool isReadingSubDict = true;

    while( newLineAndUpdateSStream(in_file, iss, line, lineCounter) && !in_file.eof())
    {
        if(!foundKeyword)
        {
            foundKeyword = checkExactMatch(line, std::string(dictName));
        }

        if (foundKeyword) 
        {
            if (line.find('{') != std::string::npos)
            {
                nOpenParenthesis_ ++;
                isReadingSubDict = false;
            }

            if (nOpenParenthesis_ != 0)
            {
                std::string keyword;

                std::vector<std::string> vList (splitString(line,'{')); // Split by curly

                if(vList.empty() || vList[0].empty() )
                {
                    keyword = possibleDictKeyword;
                    line.erase(line.find("{"), 1);
                    iss.clear();
                    iss.str(line);
                }
                else
                {
                    keyword = vList[0];    

                    line.clear();

                    for(unsigned int i = 1; i<vList.size(); i ++)
                    {
                        if (i == 1)
                        {
                            line += vList[i];
                        }
                        else
                        {
                            line += '{' + vList[i];
                        }
                    }
                    iss.str(line);    
                }
            
                // Remove whitespaces
                trimWhiteSpaces(keyword);
                
                readSubDict(*this, in_file, iss, line, lineCounter, keyword);
            }
        }

        if(nOpenParenthesis_ == 0 && !isReadingSubDict)
        {
            break;
        }
    }

    if (!foundKeyword)
    {
        throw std::runtime_error("Dictionary: " + dictName + " not found in: " + filePath_);
    }

    return true;
}



const Dictionary& Dictionary::subDict(const std::string& dictName) const
{
    if(data_.count(dictName))
    {
        return *data_.at(dictName);
    }
    else
    {
        throw std::runtime_error("subdict does not exist!");
    }
}

void Dictionary::parseString (std::string& line, std::istringstream& iss, std::ifstream& in_file, Dictionary& tmp2, int& lineCounter)
{
    std::string subString;

    std::string lineToAppend;

    int countWords{0};

    bool foundSemicolon (false);
    bool foundEndOfDict (false);

    while( getline(iss, subString, ' ') )
    {
        if (!subString.empty() && !std::all_of(subString.begin(),subString.end(), isspace ) )
        {
            if (subString.find('(') != std::string::npos)
            {
                std::size_t found = line.find('(');

                subString.clear();

                bool foundClosingParenthesis (false);
                for (int i = found; i< (int)line.size(); i++)
                {
                    char c = line[i];
                    if (c != ')')
                    {
                        subString += c;
                    }
                    else
                    {
                        foundClosingParenthesis = true;
                        subString += c;
                        if (std::count(subString.begin(), subString.end(), ')') > 1 || std::count(subString.begin(), subString.end(), '(') > 1) 
                        {
                            std::string message = "Unbalanced number of parenthesis in: " + subString + " ";
                            errorMessage(in_file, message, lineCounter);
                        }
                    }
                }

                if(!foundClosingParenthesis)
                {
                    errorMessage(in_file, "I have an error");
                }
            }
            
            // trim string until semicolon
            if (subString.find(';') != std::string::npos) 
            {
                subString =  subString.substr(0, subString.find(";"));
                line.erase(line.find(subString), subString.length() + 1);
                iss.clear();
                iss.str(line);
                foundSemicolon = true;
            }

            // Catch inline dictionary
            if (subString.find('{') != std::string::npos)
            {
                subString =  subString.substr(0, subString.find('{'));

                if (subString.empty()) // '{' is the first char in the string
                {
                    line.erase(0, line.find('{') + 1);
                    
                    rightTrimWhiteSpaces(lineToAppend); // check valid keyword
                    subString = lineToAppend;
                }
                else
                {
                    line.erase(line.find(subString), subString.length() + 1);
                }

                iss.clear();
                iss.str(line);
                nOpenParenthesis_++;
                readSubDict(tmp2, in_file, iss, line, lineCounter, subString); // read dictionary
                subString=line;
                countWords=0;
            }

            // Catch end of dictionary
            if (subString.find('}') != std::string::npos)
            {
                subString =  subString.substr(0, subString.find('}'));
                if (subString.empty()) // '}' is the first char in the string
                {
                    line.erase(0, line.find('}') + 1);
                }
                else
                {
                    line.erase(line.find(subString), subString.length() + 1);
                }

                iss.clear();
                iss.str(line);
                foundEndOfDict = true;
            }

            // Append to variable and trim from string stream
            if (!subString.empty())
            {
                lineToAppend.append(subString + ' ');
                
                if(!foundSemicolon)
                {
                    line.erase(line.find(subString), subString.length());
                    iss.clear();
                    iss.str(line);
                }

                countWords++;
            }

            if (countWords == 2)
            {
                if(foundSemicolon)
                {
                    trimWhiteSpaces(lineToAppend);
                    stripAndAppendToMap(lineToAppend, tmp2.localData_);
                    countWords=0;
                    foundSemicolon = false;
                    lineToAppend.clear();
                }
                else 
                {
                    // try to catch ; in the next char
                    iss >> std::ws; // remove whitespace from string stream
                    getline(iss, subString, ' ');
                    if (subString[0]==';')
                    {
                        line.erase(0, line.find(';') + 1);
                        stripAndAppendToMap(lineToAppend, tmp2.localData_);
                        countWords=0;
                        foundSemicolon = false;
                        lineToAppend.clear();
                    }
                    else
                    {
                        std::string message = "Lack of semicolumn in: " + lineToAppend + " on line ";
                        errorMessage(in_file,  message, lineCounter);
                    }
                }
            }

            if (foundEndOfDict)
            {
                nOpenParenthesis_--;
                return;
            }

        }
    }

    if(countWords == 1)
    {
        if (!foundSemicolon && line.back() != ';')
        {
            // check for dictionary
            std::string keyword = lineToAppend;
            newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);
            if (line[0] == '{')
            {
                line.erase(line.find("{"), 1); // erase from the string
                iss.clear(); // clear string stream
                iss.str(line); // update string stream
                nOpenParenthesis_++; // update number of open parenthesis
                readSubDict(tmp2, in_file, iss, line, lineCounter, keyword); // read dictionary
                countWords=0;
            }
            else
            {
                errorMessage(in_file, "Error while reading dictionary, on line: ", lineCounter);
            }
        }
        else
        {
            std::string message = "Keyword: " + lineToAppend + "without value, on line: ";
            errorMessage(in_file, message, lineCounter);
        }
    }
}

void Dictionary::stripAndAppendToMap(std::string& line, stringMap& m)
{
    line = line.substr(0, line.find(';'));
    
    std::istringstream ss(line);

    std::string key, value;
    ss >> key;

    bool findParenthesis = (line.find("(") != std::string::npos) && (line.find(")") != std::string::npos);

    if (findParenthesis)
    {
        size_t start = line.find('(');
        size_t end   = line.find(')');
        line = line.substr(start + 1, end - start - 1);
        ss.str(line);
    }

    bool parenthesisAppendFlag = true;

    while (ss >> value) 
    {
        if (findParenthesis)
        {
            if (parenthesisAppendFlag)
            {
                m[key] += '(';
                m[key] += value;
                parenthesisAppendFlag = false;
            }
            else
            {
                m[key] += " " + value;
            }
        }
        else
        {
            m[key] += value;
        }
    }

    if (findParenthesis)
    {
        m[key] += ')';
    }
}


std::ostream& operator<<(std::ostream& os, const indentDict& d) 
{
    int j = d.indentLevel;

    size_t size = 0;

    if (d.dict.localData().size() != 0)
    {
        // Get largest key
        for (const auto& elem : d.dict.localData())
        {
            if (size < elem.first.size())
            {
                size = elem.first.size();
            }
        }

        for (const auto& elem : d.dict.localData())
        {
            for (int k = 0; k < j; k++) 
                os << "\t";
            os <<elem.first 
            << std::setw(size)
            << "\t" 
            << elem.second 
            << ";" 
            << "\n";        
        }
    }


    for (const auto& elem : d.dict.data()) 
    {
        os << "\n";
        
        for (int k = 0; k < j; k++) 
            os << "\t";

        os  << elem.first 
            << "\n";

        for (int k = 0; k < j; k++) 
                os << "\t";

        os  << "{\n"
            << indentDict(*elem.second, j + 1);
                
        for (int k = 0; k < j; k++) 
            os << "\t";
        
        os  << "}"
            << "\n";
    }

    return os;
}


std::ostream& operator<<(std::ostream& os, const Dictionary& dict)
{
    os << indentDict(dict);

    return os;  
}