// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "ufw/GV.h"
#include "FirstSetup.h"
#include "Passwd.h"
#include "mainFrame.h"

class uMgr
    : public wxApp {
public:
    virtual bool OnInit();

};

wxIMPLEMENT_APP(uMgr);

bool uMgr::OnInit() {
    
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    // _CrtSetBreakAlloc(6369);
    // _CrtSetBreakAlloc(16250);

#if _WIN32
    std::filesystem::path __path__;
    TCHAR paf[MAX_PATH];
    SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0, paf);
    LPWSTR _paf = paf;
    {
        bool ret = PathAppend(_paf, L"uMgr_A_Data");
    }
    __path__ = _paf;
    GV::consts::c_app_data = __path__.string();
#else
    mkdir(uPaf + ".uMgr_A_Data");
    GV::consts::c_app_data = uPaf.string() + ".uMgr_A_Data";
#endif // _WIN32

    bool hasPwd = false;

    if (!std::filesystem::exists((GV::consts::c_app_data + GV::consts::fsep + "initialised.baka"))) {
        hasPwd = true; // uhh... can be used here also
        wxFileName exepaf(wxStandardPaths::Get().GetExecutablePath());
        FirstSetup* f = new FirstSetup("Setup", exepaf.GetPath());
        f->Centre(wxBOTH);
        f->Show();
    }
    else if (std::filesystem::exists((GV::consts::c_app_data + FSEP + "pwd.hentai")))
    {
        while (true) // :>
        {
            {
                std::ifstream pwd_f((GV::consts::c_app_data + FSEP + "pwd.hentai"));
                if (pwd_f.peek() == std::ifstream::traits_type::eof())
                    break;  // :>

                std::string tmp = "";
                getline(pwd_f, tmp);
                if (tmp == "")
                    break;
                pwd_f.close();
            }

            hasPwd = true;
            Passwd* pwd = new Passwd("Authentication");
            pwd->Center(wxBOTH);
            pwd->Show();
            break;
        }
    }
    if (!hasPwd)
    {
        mainFrame* fuuuu = new mainFrame("Fooooook", wxDefaultPosition, wxDefaultSize);
        fuuuu->Show();
    }

    return true;
}