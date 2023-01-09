#include "RunTime.h"
#include <boost/filesystem.hpp>

RunTime::RunTime()
:
    path_( getExecutablePath() ),
    controlDict_(system()+"controlDict"),
    time_{0}
{
    controlDict_.read();
    startTime_ = controlDict_.lookup<double>("startTime");
    endTime_   = controlDict_.lookup<double>("endTime");
    deltaT_    = controlDict_.lookup<double>("deltaT");
    std::string startFrom = controlDict_.lookup<std::string>("startFrom");

    if (startFrom == "latestTime")
        folder_ = getTimeFolder();
    else
        folder_ = "0/";
}

const std::string& RunTime::Path() const
{
   return path_;
}

const std::string& RunTime::Folder() const
{
    return folder_;
}

void RunTime::setFolder(std::string& newFolder)
{
    folder_ = newFolder;
}

const std::string RunTime::constant() const
{
    return Path() + "constant/";
}
    
const std::string RunTime::system () const
{
    return Path() + "system/";
}

const std::string RunTime::timeName() const
{
    return Path() + Folder();
}

bool RunTime::createTimeFolder() const
{
    std::ostringstream out;
    out.precision(controlDict_.lookup<int>("timePrecision"));
    out << std::fixed << time_;

    boost::filesystem::path newFolderPath(path_ + out.str());

    if (is_directory(newFolderPath))
    {
        return false;
    }
    else
    {
        boost::filesystem::create_directories(newFolderPath);
        folder_ = out.str()+"/";
    }

    return true;
}

bool RunTime::loop()
{
    if(time_ < endTime_)
    {
        time_ += deltaT_;
        return true;
    }
    else    
        return false;
}
