// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "ufw/GV.h"
#include "FirstSetup.h"

class uMgr
    : public wxApp {
public:
    virtual bool OnInit();

private:
    FirstSetup* f = nullptr;
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

    bool init = false;

    if (!std::filesystem::exists((GV::consts::c_app_data + GV::consts::fsep + "initialised"))) {
        wxFileName exepaf(wxStandardPaths::Get().GetExecutablePath());
        f = new FirstSetup("Setup", exepaf.GetPath(), init);
        f->Show();
        f->Centre(wxBOTH);
    }
    return true;
}