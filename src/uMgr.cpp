#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <fstream>
#include <sstream>
#include "ufw/init.h"


namespace GV
{
    // set the user folder name and updates the user folder path
    void getU_F_name();

    namespace consts
    {
        // stores the folder and file separator
        char fsep;
        // stores the the path of the user's home dir
        std::filesystem::path uPaf;
        // stores the user folder name
        std::string uName;
        // stores the path where the setting, pwd and others are stored in the user home dir
        // std::string c_app_data;
        // stores the path where the user stores their data
        std::string user_data_folder;
        // stores the path of preferences
        std::string user_preferences;

    } // namespace consts

    char fsep;
    
    std::string user_folder;

    const char* uName;

} // namespace GV


void GV::getU_F_name()
{
#if _WIN32
    TCHAR userPaf[MAX_PATH];
    // get the current user path & set it to userPaf
    SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0, userPaf);
    std::filesystem::path uPaf = userPaf;
    // set user path
    GV::user_folder = uPaf.string();
    int index = uPaf.string().find_last_of(GV::fsep);
    GV::uName = uPaf.string().substr(index + 1).c_str();
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

    wxColour theme;
    // theme of the aplication (any valid rgb value)
    
    std::string currentTitle,
        // custom title of the application 
        grpIndexPath;
    // path to frp index file...
public:
    virtual bool OnInit();

    void InitApp();
};

wxIMPLEMENT_APP(uMgr);

bool uMgr::OnInit() {

    GV::fsep = std::filesystem::path::preferred_separator;
    GV::getU_F_name();

#if _WIN32
    GV::user_folder = GV::user_folder + GV::fsep + "uMgr_Data";
#else
    GV::user_folder += GV::fsep + ".uMgr_Data";
#endif // _WIN32

    InitApp();
    
    // TODO: Create Password manager

    //if (!std::filesystem::exists((USER_DATA + FSEP + "initialised.baka")))
    //{
    //    wxFileName exepaf(wxStandardPaths::Get().GetExecutablePath());
    //    FirstSetup* f = new FirstSetup(exepaf.GetPath());
    //    f->Centre(wxBOTH);
    //    f->Show();
    //}
    //else if (!std::filesystem::exists((USER_DATA + FSEP + PWD_FILE)) && (!std::ifstream((USER_DATA + FSEP + PWD_FILE)).eof()))
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

    return false;
}

void uMgr::InitApp() {
    wxMessageBox(GV::user_folder, "lllll");
    std::filesystem::create_directories(GV::user_folder);

#if _WIN32
    CreateDirectoryA(GV::user_folder.c_str(), nullptr);
    // hide it
    SetFileAttributesA(GV::user_folder.c_str(), FILE_ATTRIBUTE_HIDDEN);
#endif // _WIN32


    if (!std::filesystem::exists(GV::user_folder + GV::fsep + PREF_FILE)) {
        std::ofstream prefFile(GV::user_folder + GV::fsep + PREF_FILE);
        prefFile << "240, 240, 240\n";
        theme.Set(240, 240, 240);
        prefFile << "uMgr\n" << GV::user_folder;
        prefFile.close();
        currentTitle = "uMgr";
        grpIndexPath = GV::user_folder;
        return;
    }

    if (!std::filesystem::exists(GV::user_folder + GV::fsep + GEN_INDEX_N)) {
        std::ofstream file(GV::user_folder + GV::fsep + GEN_INDEX_N);
        file.close();
    }

    std::ifstream prefFile(GV::user_folder + GV::fsep + PREF_FILE);
    if (!prefFile) {
        wxMessageBox("cant open file", "err");
        return;
    }
    std::string line;
    getline(prefFile, line);
    {
        std::stringstream rgbs(line);
        int clrVals[3];
        for (char i = 0; i < 2; ++i) {
            rgbs >> line;
            clrVals[i] = std::stoi(line);
        }
        theme.Set(clrVals[0], clrVals[1], clrVals[2]);
    }
    getline(prefFile, currentTitle);
    getline(prefFile, grpIndexPath);
    prefFile.close();
}