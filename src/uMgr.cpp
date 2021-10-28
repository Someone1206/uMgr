#include <wx/wx.h>

class uMgr
    :public wxApp {
public:
    virtual bool OnInit();
}

wxIMPLEMENT_APP(uMgr);

bool uMgr::OnInit() {
#ifndef _WIN32 | _WIN64 | __linux__ | __gnu_linux__ | linux | __linux // ik obsolete but idc
    #error The Application isn't supported on your platform consider modifying the source code at https://www.github.com/Someone1206/uMgr
    reportErr(("The Application isn't supported on your platform"
        " consider modifying the source code at\n"
        "https://www.github.com/Someone1206/uMgr"));
    return false;
#endif
    // create windoe
}