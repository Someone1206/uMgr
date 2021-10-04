#pragma once
#include <filesystem>

#if _WIN32
#include <Shlwapi.h>
#include <ShlObj.h>
#else
#include <unistd.h>
#endif // _WIN32

// a collection of all the global variables to be used
namespace GV
{
    /// <summary>
    /// return the user folder name and updates the user folder path
    /// </summary>
    std::string getU_F_name();

    namespace consts
    {
        // stores the folder and file separator
        extern char fsep;
        // stores the the path of the user's home dir
        extern std::filesystem::path uPaf;
        // stores the user folder name
        extern std::string uName;
        // stores the path where the setting, pwd and others are stored in the user home dir
        extern std::string c_app_data;
        // stores the path where the user stores their data
        extern std::string user_data_folder;

    } // namespace consts

} // namespace GV

