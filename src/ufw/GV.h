#pragma once
#include <filesystem>

#if _WIN32
#include <Shlwapi.h>
#include <ShlObj.h>
#else
#include <unistd.h>
#endif // _WIN32

namespace GV
{
    extern std::string getU_F_name();

    namespace consts
    {
        extern char fsep;
        extern std::filesystem::path uPaf;
        extern std::string uName;
        extern std::string c_app_data;
        extern std::string user_data_folder;

    } // namespace consts

} // namespace GV

