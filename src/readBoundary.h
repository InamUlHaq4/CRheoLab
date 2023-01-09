template <typename vectorType>
void Boundary<vectorType>::readBoundaryPatch(const std::string& patchName)
{
 
    // Create structure to store information
    // patchBoundaryDefinitions store;
    uniformField_=true;
  
    // File location path
    std::string fileLocation = path();

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        in_file.close();
        throw std::runtime_error("The input file was not open correctly!");
    }

    // Line to store input from file
    std::string line;

    // Line counter for error reporting
    int lineCounter=0;

    // Sets a stringstream to get information from string
    std::istringstream iss (line);

    bool findBoundaryField = false;
    bool findPatch = false;
    bool endCycle = false; 

    // Read file
    while (!endCycle && !in_file.eof())
    { 
        // Updates lines 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

        if (checkExactMatch(line, std::string("boundaryField")))
        {
            findBoundaryField = true;
            // Updates lines
            newLineAndUpdateSStream(in_file, iss, line, lineCounter);

            readCharacter(in_file, iss, '{', lineCounter);    

            while(!findPatch && !in_file.eof())
            {
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                // Found patch 
                if ( checkExactMatch(line, patchName) )
                {
                    findPatch=true;

                    // Get next line
                    newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                    
                    // Check if '{' exists 
                    readCharacter(in_file, iss, '{', lineCounter);   

                    bool endInnerCycle = false;

                    while (!endInnerCycle)
                    {
                        // Get new line
                        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                        // Get type
                        if (checkExactMatch(line, "type"))
                        {
                            // trip type
                            line = line.substr(line.find("type") + 4); 

                            // Check semicoln
                            checkSemiColon(in_file, line, lineCounter);

                            // Remove ';' at the end and white spaces
                            line.erase(std::remove(line.begin(), line.end(), ';'), line.end());
                            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

                            // Store information into structure
                            this->type_ = line;

                            // Get new line
                            newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                        }

                        // Get other patch input that is not the entry 'value' or 'type' or singleLined characters (e.g, }, ) , ...
                        if
                        ( 
                            !checkExactMatch(line, "value") 
                            && 
                            !checkExactMatch(line, "type") 
                            && 
                            (countCharacters(line) > 1) 
                        ) // need to add here the name of the other patches in the mesh..
                        {
                            // Check if ; it at the end of the sentance
                            checkSemiColon(in_file, line, lineCounter);

                            // Remove ';' at the end
                            line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

                            // Split string by spaces
                            std::vector<std::string> tmp =  splitString(line, ' ');

                            // If there are more than 2 splits, warn the user (here for the time being... might change in the future)
                            if(tmp.size() > 2)
                            {
                                //errorMessage(in_file, "More than two strings ", lineCounter);
                            }

                            // store information in structure
                            std::string joinString;
                            std::for_each
                            (   std::next(tmp.begin()), tmp.end(), [&](const std::string & subString)
                                {
                                    joinString.empty()? joinString += subString : joinString+= " " + subString; 
                                }
                            );

                            // this->otherInfo_.insert ( std::pair<std::string, std::string>(tmp[0], tmp[1] ) );
                            this->otherInfo_.insert ( std::pair<std::string, std::string>(tmp[0], joinString ) );
                        }

                        // Get value
                        if( checkExactMatch(line, "value"))
                        {
                            if (checkExactMatch(line, "uniform"))
                            {
                                checkSemiColon(in_file, line, lineCounter);

                                // Strips the string from uniform onwards
                                line = line.substr(line.find("uniform") + 7); 

                                // update string stream
                                iss.clear();
                                iss.str(line);

                                // Create a primitiveType to store the data
                                definedValues_.resize(1);

                                if(!(iss >>definedValues_[0]))
                                {
                                    errorMessage(in_file, "Error while parsing uniform field at line: ", lineCounter);
                                }

                            } // If the internalField is non-uniform
                            else if (checkExactMatch(line, "nonuniform")) 
                            {
                                this->uniformField_=false;

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // Variable to store the number of points in the field
                                int nPointsInNonUniformField;

                                // Gets integer from string
                                iss >> nPointsInNonUniformField;

                                // If something is wrong, warn the user and shutdown the program
                                if (iss.fail())
                                {
                                    errorMessage(in_file, "Something is wrong with number of points in non-uniform field ", lineCounter);
                                }

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // check if parenthesis exists '('
                                readCharacter(in_file, iss, '(', lineCounter);   

                                // Resize the vector to accomudade the incoming data
                                definedValues_.resize(nPointsInNonUniformField);

                                for(int i = 0; i < nPointsInNonUniformField; i++)
                                {
                                    // Updates lines 
                                    newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                    if (!(iss >> definedValues_[i]))
                                    {
                                        errorMessage(in_file, "Error while parsing nonuniform field at line: ", lineCounter);
                                    }
                                }

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // Check if ')' exists
                                readCharacter(in_file, iss, ')', lineCounter);   

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // Check if ';' exists
                                readCharacter(in_file, iss, ';', lineCounter);

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                            }
                        }

                        // If another curly brace is found it will shutdown the program
                        char c1;
                        iss >> c1;
                        if (!iss.fail() && c1 == '{')
                        {
                            std::string message = "There is no closing parenthesis, '}', in patch " + patchName + " ";
                            errorMessage(in_file, message, lineCounter);
                        }

                        if (!iss.fail() && c1 == '}')
                        {
                            // Exits inner while
                            endInnerCycle=true;
                        }
                    }
                }
            }


            if (!findPatch)
            {
                std::string message = "Patch " + patchName + " not found";
                errorMessage(in_file, message, 0, true);
            }

            if 
            (
                this->type_.empty() 
                || 
                (
                    this->definedValues_.size()==0 
                    && 
                    ( (type_ != "empty") && (type_ != "symmetry") && (type_ != "zeroGradient")) 
                )
            )
            {
                std::string message = "Problem in patch " + patchName ;
                errorMessage(in_file, message, 0, true);
            }

            // Catch closing of boundaryField

            bool endBoundaryField = false;
            while (!endBoundaryField && !in_file.eof())
            {
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                char c1;
                iss >> c1;
                if ( c1 == '}')
                {

                   endBoundaryField= true;
                    // Exits outer while
                    endCycle=true;
                }
                else
                {
                   // Loop until finding two consecutive } } 
                   bool findFirstClosingCurly =false;
                   bool findSecondClosingCurly =false;

                   while (!findSecondClosingCurly && !in_file.eof())
                   {
                        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                        iss >> c1;

                        if ( !findFirstClosingCurly && c1 == '}')
                        {
                            findFirstClosingCurly = true;
                            newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                            c1=' '; // reset char
                            
                        }

                        iss >> c1;
                        if ( findFirstClosingCurly &&  c1 == '}')
                        {
                            findSecondClosingCurly = true;
                            endBoundaryField = true;
                            endCycle=true;
                        }
                        else
                        {
                            findFirstClosingCurly =false;
                        }
                   }
                }
            }

            if (!endBoundaryField)
            {
                errorMessage(in_file, "Missing '}' at the end of boundaryField", lineCounter, true);
            }
       
        }

        if ( !findBoundaryField && in_file.eof() )
        {
            std::string message = "Keyword 'boundaryField is not defined";
            errorMessage(in_file, message, 0, true);
        }
    }

    // Close the file
    in_file.close();
}
