#ifndef READ_HELP_OPERATIONS_H
#define READ_HELP_OPERATIONS_H

#include <iostream>
#include <sstream> 
#include <fstream>
#include <algorithm>

#include "stringOp.h"

std::string stripSingleComment(std::string& line);
std::string stripBlockComment(std::ifstream& in_file, std::string& line, int& lineCounter);
std::string stripComments(std::ifstream& in_file, std::string& line, int& lineCounter);
bool newLineAndUpdateSStream(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter, bool updateStringStream=true);
void errorMessage(std::ifstream& in_file, const std::string& message, int lineCounter=0, bool turnOffLinePrinting=false);
bool checkCharacter(std::ifstream& in_file, std::istringstream& iss, const char& C);
void checkSemiColon (std::ifstream& in_file, std::string& line, const int& lineCounter);

void vectorFormatError(std::ifstream& in_file, int lineCounter);

std::string readString(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter, bool semiColumCheck);
void readCharacter(std::ifstream& in_file, std::istringstream& iss, const char C, const int& lineCounter);


#endif