template< typename vectorType>
void VolField<vectorType>::readInternalField()
{
    // File location path
    std::string fileLocation = this->path();

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        //return 1;
    }

    // Line to store input from file
    std::string line;

    // stringstream to get data out of string
    std::istringstream iss (line);

    // Line counter for error reporting
    int lineCounter=0;

    // Read file
    while ( newLineAndUpdateSStream(in_file, iss, line, lineCounter) && !in_file.eof() )
    { 
        // Check if line has the exact match for the keyWord. 
        if ( checkExactMatch(line, std::string("internalField")) )
        {
            // Check if internalField is "uniform"
            if (checkExactMatch(line, "uniform"))
            {
                // Check if ; it at the end of the sentance
                checkSemiColon(in_file, line, lineCounter);

                // Strips the string from uniform onwards
                line = line.substr(line.find("uniform") + 7); 

                iss.str(line);
                
                internalField_.resize(1);
                
                if (!(iss >> internalField_[0]))
                {
                    errorMessage(in_file, "Error while parsing uniform field at line: ", lineCounter);
                }

                // Exits the loop (not necessary to continue looking into the file)
                break;

            } // If the internalField is non-uniform
            else if (checkExactMatch(line, "nonuniform")) 
            {
                // Updates lines 
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

                if (nPointsInNonUniformField != (int)mesh().nCells_)
                {
                    std::string message = "Number of points in internalField of file"  + this->name()
                                          + "does not match the number of cells in the mesh.\n"
                                          + "There are: " + std::to_string(nPointsInNonUniformField) 
                                          + " in the the file and " + std::to_string(mesh().nCells_) + " in the mesh."; 
                    errorMessage(in_file, message);
                }

                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                readCharacter(in_file, iss, '(', lineCounter);                

                // Resize the vector to accomudade the incoming data
                internalField_.resize(nPointsInNonUniformField);

                for(int i = 0; i < nPointsInNonUniformField; i++)
                {
                    // Updates lines 
                    newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                    if (!(iss >> internalField_[i]))
                    {
                        errorMessage(in_file, "Error while parsing nonuniform field at line: ", lineCounter);
                    }
                }

                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                readCharacter(in_file, iss, ')', lineCounter);    

                // check if ';' exists at the end
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                readCharacter(in_file, iss, ';', lineCounter);    

                // Breaks the loop once it is finished
                break;
            }
        }
    }

    if (in_file.eof() )
    {
        std::string message = "Keyword 'internalField not defined in file: " + this->name();
        errorMessage(in_file, message, 0, true);
    }

    // Close the file
    in_file.close();
}



template< typename vectorType>
void VolField<vectorType>::readDimensions()
{
    // File location path
    std::string fileLocation = this->path();

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        //return 1;
    }

    // Line to store input from file
    std::string line;

    // Variable to store the information
    vectorType store;

    // stringstream to get data out of string
    std::istringstream iss (line);

    // Line counter for error reporting
    int lineCounter=0;

    // Read file
    while (newLineAndUpdateSStream(in_file, iss, line, lineCounter) && !in_file.eof())
    { 
        // Check if line has the exact match for the keyWord. 
        if (checkExactMatch(line, std::string("dimensions")))
        {
            trimWhiteSpaces(line);
            std::size_t pos = line.find("dimensions");
            if (pos != 0)
            {
                std::string message = "Problems while looking for dimensions. There are unwanted characteres in line: " 
                                      + std::to_string(lineCounter) + " of file: " + this->name();
                errorMessage(in_file, message, 0, true);
            }

            line = line.substr(11, line.length());
            iss.str(line);

            if(!(iss >> dimensions_))
            {
                throw std::runtime_error("Problem reading dimensions in: " + this->name());
            } 

            break;
        }
    }

    if (in_file.eof() )
    {
        std::string message = "Keyword 'dimensions not found in: " + this->name();
        errorMessage(in_file, message, 0, true);
    }

    // Close the file
    in_file.close();
}









