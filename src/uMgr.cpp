#include <wx/wx.h>
#include "FirstSetup.h"


class uMgr
    :public wxApp {
public:
    virtual bool OnInit();
}

wxIMPLEMENT_APP(uMgr);

bool uMgr::OnInit() {
#ifndef _WIN32 || _WIN64 || __linux__ || __gnu_linux__ || linux || __linux || Macintosh || (__APPLE__ && __MACH__)
    #error The Application isn't supported on your platform consider modifying the source code at https://www.github.com/Someone1206/uMgr
    reportErr(("The Application isn't supported on your platform"
        " consider modifying the source code at\n"
        "https://www.github.com/Someone1206/uMgr"));
    return false;
#endif

    //////////////////////////////////////////////////////////////////////////////////////
    // initialise the global variables                                                  //
    char GV::consts::fsep = std::filesystem::path::preferred_separator;                 //
    std::filesystem::path GV::consts::uPaf;                                             //
    std::string GV::consts::uName = GV::getU_F_name();                                  //
                                                                                        //
#if _WIN32                                                                              //
    std::string GV::consts::c_app_data = "uMgr_A_Data";                                 //
#else                                                                                   //
    std::string GV::consts::c_app_data = ".uMgr_A_Data";                                //
    // i mean wtaf linux(unix) kernel? y u add .                                        //
#endif                                                                                  //
                                                                                        //
    std::string GV::constsuser_data_folder;                                             //
    //                                                                                  //
    //////////////////////////////////////////////////////////////////////////////////////

    if (!std::filesystem::exists(prefFolder))
    {
#if _WIN32
        std::wstring uhhhhh(prefFolder.start(), prefFolder.end());
        LPCWSTR irdk = uhhhhh.c_str();
        CreateDirectory(irdk, nullptr);
        // hide the directory
        SetFileAttributes(irdk, FILE_ATTRIBUTE_HIDDEN);
#else
        mkdir(prefFolder);
#endif
    }

    // create windoe

    if (!std::filesystem::exists((aFolder + FSEP + "initialised.baka")))
    {
        wxFileName exepaf(wxStandardPaths::Get().GetExecutablePath());
        FirstSetup* f = new FirstSetup("Setup", exepaf.GetPath());
        f->Centre(wxBOTH);
        f->Show();
    }
    else if (!std::filesystem::exists((aFolder + FSEP + "pwd.hentai")))
    // if passwd is located,
    {
        
    }
}