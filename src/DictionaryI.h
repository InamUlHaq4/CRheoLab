
template <typename T>
T Dictionary::lookup(const std::string& keyword) const
{
    if (localData_.find(keyword) != localData_.end())
    {
        // variable to store data
        T data;

        // pass string to string stream
        std::istringstream iss(localData_.at(keyword));
        
        // collect data
        iss >> data;

        // If operation failed or there are more data types in the same string. 
        // Shutdown the program
        if (iss.fail() || iss >> data)
        {
            throw std::runtime_error("Could not retrieve data type from "  + localData_.at(keyword) + ", keyword: " + keyword );
        }

        return data;
        
    } 

    //throw std::runtime_error("Could not retrieve keyword: "  + localData_.at(keyword) + ", in Dictionary " + this->filePath_);
    throw std::runtime_error("Could not retrieve keyword: "  + keyword );
}

template <typename T>
T Dictionary::lookupOrDefault(const std::string& keyword, T defaultV) const
{
    if (localData_.find(keyword) != localData_.end())
    {
        // variable to store data
        T data;

        // pass string to string stream
        std::istringstream iss(localData_.at(keyword));
        
        // collect data
        iss >> data;

        // If operation failed or there are more data types in the same string. 
        // Shutdown the program
        if (iss.fail() || iss >> data)
        {
            throw std::runtime_error("Could not retrieve data type from "  + localData_.at(keyword) + ", keyword: " + keyword );
        }

        return data;
        
    } 

    return defaultV;
}