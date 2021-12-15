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
    // set the user folder name and updates the user folder path
    void getU_F_name();

    namespace consts
    {
        // stores the folder and file separator
        extern char fsep;
        // stores the the path of the user's home dir
        extern std::filesystem::path uPaf;
        // stores the user folder name
        extern std::string uName;
        // stores the path where the setting, pwd and others are stored in the user home dir
        // extern std::string c_app_data;
        // stores the path where the user stores their data
        extern std::string user_data_folder;
        // stores the path of preferences
        extern std::string user_preferences;

    } // namespace consts

    extern char fsep;

    extern std::string user_folder;

} // namespace GV


#define FSEP      GV::consts::fsep
#define folderN   "uMgrData"
#define USER_DATA   GV::consts::user_data_folder
#define uPAF      GV::consts::uPaf

#define PWD_FILE       "pwd.hentai"                  // name of password file, (if it changes any day)
#define PREF_FILE      "Preferences.hentai"          // file of bool values (too long to write every where)
#define TIT_FILE       "title.hentai"                // if i wish to change it any day
#define PREF_FOLDER    GV::consts::user_preferences  // i'm lazy
// fook i'm tired with dat dot

#define SET_NO    2 // number of setting, for array, currently 2

static constexpr char SEP = (char)1;

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