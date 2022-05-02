#ifndef READER_H
#define READER_H
#include<iostream>
#include<fstream>

/// Class for reading the solution parameters from a file
class Reader
{
    public:

        /// Default constructor
        Reader(std::string fileName);

        /// Destructor
        virtual ~Reader();

        // Member Functions
        /// Function to read string
        std::string ReadString(std::string str);
        /// Function to read double
        double ReadDouble(std::string str);
        /// Function to read integer
        int ReadInt(std::string str);
            
    protected:
    
    private:
    /// Name of the file
    std::string fileName_;
     
};

#endif
