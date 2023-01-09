#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <string>
#include <vector>
#include <sstream> 
#include <algorithm>

int countCharacters(const std::string& line);

std::vector<std::string> splitString(const std::string& line, char delimiter);

void rightTrimWhiteSpaces(std::string& line);

void leftTrimWhiteSpaces(std::string& line);

void trimWhiteSpaces(std::string& line);

bool checkExactMatch
(
    const std::string& line, 
    const std::string& keyWord
);

void stripFromString(std::string& line, const std::string& word);


#endif