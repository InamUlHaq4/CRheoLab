#ifndef RunTime_H
#define RunTime_H

#include <string>
#include "findFiles.h"
#include "Dictionary.h"

class RunTime
{
    public:
        // Default constructor
        RunTime();
        
        // Default Destructor
        ~RunTime() = default ;

        // No copy, no assigment
        RunTime(const RunTime&) = delete;
        void operator=(const RunTime&) = delete;

        
        // Access
        const double& time() const {return time_;}
        const double& deltaT() const {return deltaT_;}

        void setFolder(std::string& newFolder);
        void setDeltaT(double dT){deltaT_ = dT;}

        const std::string& Path() const;
        const std::string& Folder() const;
        const std::string constant () const;
        const std::string system () const;
        const std::string timeName () const;

        // Create folder
        bool createTimeFolder() const;

        // Loop
        bool loop();

        // Operators
        void operator++()
        {
            time_ += deltaT_;
            folder_ = std::to_string(time_);
        }

        void operator ++(int)
        {
            this->operator++();
        }

    private:
        std::string path_;
        Dictionary controlDict_;
        mutable std::string folder_;
        
        double startTime_;
        double endTime_;
        double time_;
        double deltaT_;
};

#endif 