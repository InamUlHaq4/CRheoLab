#include "stringOp.h"

int countCharacters(const std::string& line)
{
    int nchars{0};

    for (unsigned i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ') 
        {
            nchars++;
        }
    }

    return nchars;
}


std::vector<std::string> splitString
(
    const std::string& line, 
    char delimiter
)
{
    std::stringstream ss(line);

    std::string word;

    std::vector<std::string> result;

    while (getline(ss, word, delimiter))
    {
        if (word.size() != 0)
        {
            // Remove white spaces
            word.erase(remove_if(word.begin(), word.end(), isspace), word.end());
            
            // push to vector
            result.push_back(word);
        }

    }
    return result;  
}

void rightTrimWhiteSpaces(std::string& line)
{
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), line.end());
}

void leftTrimWhiteSpaces(std::string& line)
{
    line.erase
    (
        line.begin(), std::find_if
        (
            line.begin(), line.end(), 
            [](unsigned char ch) 
            {
                return !std::isspace(ch);
            }
        )
    );
}

void trimWhiteSpaces(std::string& line)
{
    leftTrimWhiteSpaces(line);
    rightTrimWhiteSpaces(line);
}

bool checkExactMatch
(
    const std::string& line, 
    const std::string& keyWord
)
{
    // Check if string has a partial match
    std::size_t index = line.find(keyWord);

    // If it doesn't, return false
    if (index == std::string::npos)
    {
        return false;
    }

    // Create a lambda function to check if there are characters before or after the match string
    // [&line] means to pass line as a reference to the lambda function
   auto not_part_of_word = [&line](unsigned int index)
   {
        if (index < 0 || index >= line.size())
        {
            return true;
        } 
        if (std::isspace(line[index]) || std::ispunct(line[index]))
        {
            return true;
        } 

        return false;
    };

    bool checkCharactersBefore = not_part_of_word(index-1);
    bool checkCharactersAfter =  not_part_of_word(index+keyWord.size());
   
    return checkCharactersBefore && checkCharactersAfter;
}

void stripFromString
(
    std::string& line, 
    const std::string& word
)
{
    const std::size_t index = line.find(word);
    if (index != std::string::npos)
    {
        line.erase(index, word.length() );
    }
}



