#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <fstream>
#include "ufw/init.h"

namespace GV
{
    // return the user folder name and updates the user folder path
    std::string getU_F_name();

    namespace consts
    {
        // stores the folder and file separator
        char fsep;
        // stores the the path of the user's home dir
        std::filesystem::path uPaf;
        // stores the user folder name
        std::string uName;
        // stores the path where the setting, pwd and others are stored in the user home dir
        std::string c_app_data;
        // stores the path where the user stores their data
        std::string user_data_folder;
        // stores the path of preferences
        std::string user_preferences;

    } // namespace consts

} // namespace GV


std::string GV::getU_F_name()
{
#if _WIN32
    TCHAR userPaf[MAX_PATH];
    SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0, userPaf);
    std::filesystem::path uPaf = userPaf;
    // set user path
    uFolder = uPaf.string();
    int index = 0, len = GV::consts::user_data_folder.length();
    for (int i = 0; i < len; i++)
    {
        if (GV::consts::user_data_folder.at(i) == GV::consts::fsep)
            index = i;
    }
    return GV::consts::user_data_folder.substr(index + 1);
    // get user folder name
#else
    const char* homedir;
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

class uMgr
    :public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(uMgr);

bool uMgr::OnInit() {
#ifndef _WIN32 || _WIN64 || __linux__ || __gnu_linux__ || linux || __linux || Macintosh || (__APPLE__ && __MACH__)
#error The Application isn't supported on your platform consider modifying the source code at https://www.github.com/Someone1206/uMgr
    return false;
#endif

    //////////////////////////////////////////////////////////////////////////////////////
    // initialise the global variables                                                  //
    FSEP = std::filesystem::path::preferred_separator;                                  //
    uPAF;                                                                               //
    GV::consts::uName = GV::getU_F_name();                                              //
                                                                                        //
#if _WIN32                                                                              //
    aFolder = "uMgr_A_Data";                                                            //
#else                                                                                   //
    aFolder = ".uMgr_A_Data";                                                           //
    // i mean wtaf linux(unix) kernel? y u add .                                        //
#endif                                                                                  //
                                                                                        //
    PREF_FOLDER = uFolder + FSEP + aFolder + FSEP + "Preferences";                                       //
    // uFolder;                                                                            //
    //                                                                                  //
    //////////////////////////////////////////////////////////////////////////////////////

//    if (!std::filesystem::exists(PREF_FOLDER))
//    {
//#if _WIN32
//        std::string str = PREF_FOLDER;
//        LPCSTR irdk = GV::consts::user_preferences.c_str();
//        CreateDirectoryA(irdk, nullptr);
//        // hide the directory
//        SetFileAttributesA(irdk, FILE_ATTRIBUTE_HIDDEN);
//#else
//        mkdir(prefFolder);
//#endif
//    }

    {
        std::string msg = FSEP + "\n" + uFolder + '\n' + GV::consts::uName + '\n' + PREF_FOLDER;
        wxMessageBox(msg, "Details");
    }

    // TODO: Call init() & read all settings and create dir hirerarchy

    // create windoe

    //if (!std::filesystem::exists((aFolder + FSEP + "initialised.baka")))
    //{
    //    wxFileName exepaf(wxStandardPaths::Get().GetExecutablePath());
    //    FirstSetup* f = new FirstSetup(exepaf.GetPath());
    //    f->Centre(wxBOTH);
    //    f->Show();
    //}
    //else if (!std::filesystem::exists((aFolder + FSEP + PWD_FILE)) && (!std::ifstream((aFolder + FSEP + PWD_FILE)).eof()))
    //    // if passwd is located, && not empty
    //{
    //    Passwd* pswd = new Passwd("Authenticate");
    //    pswd->Center(wxBOTH);
    //    pswd->Show();
    //}
    //else {
    //    // if not passwd protected!
    //    mainFrame* im_tired = new mainFrame(getFrameTitle(), wxDefaultPosition, wxDefaultSize);
    //    im_tired->Show();
    //}

    return true;
}