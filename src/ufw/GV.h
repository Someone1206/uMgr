#pragma once
#include <filesystem>
#include <string>

#if _WIN32
#include <Shlwapi.h>
#include <ShlObj.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif // _WIN32

// a collection of all the global variables to be used
namespace GV
{
    // return the user folder name and updates the user folder path
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

std::string GV::getU_F_name()
{
#if _WIN32
    TCHAR userPaf[MAX_PATH];
    SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0, userPaf);
    GV::consts::uPaf = userPaf;
    // set user path
    std::string temp = GV::consts::uPaf.string();
    int index = 0, len = temp.length();
    for (int i = 0; i < len; i++)
    {
        if (temp.at(i) == GV::consts::fsep)
            index = i;
    }
    return temp.substr(index + 1);
    // get user folder name
#else
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL) 
        homedir = getpwuid(getuid())->pw_dir;
    GV::consts::uPaf = homedir;
    // set user path
    std::string temp = GV::consts::uPaf.string();
    int index = 0, len = temp.length();
    for (int i = 0; i < len; i++)
    {
        if (temp.at(i) == GV::consts::fsep)
            index = i;
    }
    return temp.substr(index + 1);
    // return user name
#endif // _WIN32
}

#define FSEP      GV::consts::fsep
#define folderN   "uMgrData"
#define uFolder   GV::consts::user_data_folder
#define aFolder   GV::consts::c_app_data
#define uPAF      GV::consts::uPaf

#define PWD_FILE  "pwd.hentai" // name of password file, (if it changes any day)
#define PREF_FILE "preferences.hentai" // file of bool values (too long to write every where)

#define SET_NO    2 // number of setting, for array, currently 2

static constexpr char SEP = (char)1;
static constexpr std::string prefFolder = aFolder + FSEP + "Preferences";
// fook i'm tired with dat dot

#if _WIN32
// hide the files on creation when Windows
#define GEN_INDEX_N      "GenreIndex.hentai"
#define ENTRY_INDEX_N    "EntryIndex.hentai"
#else
// making the files hidden if linux detected
#define GEN_INDEX_N      ".GenreIndex.hentai"
#define ENTRY_INDEX_N    ".EntryIndex.hentai"
#endif // _WIN32


#define RE_DEST   0x01000 // ms does shit like this to their macros
#define _DEST     0x01000 // this name makes moe sense
// destructive creation ||(signs of nerdiness) recreation from scratch (here, in this context)
#define _CONST     0x01001 // constructive creation