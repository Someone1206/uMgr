// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

#include <wx/wx.h>
#include "mainFrame.h"

class uMgr
    : public wxApp {
public:
    virtual bool OnInit();

private:
    mainFrame* frame = nullptr;
};

wxIMPLEMENT_APP(uMgr);

bool uMgr::OnInit() {
    
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    // _CrtSetBreakAlloc(6369);
    // _CrtSetBreakAlloc(16250);

    frame = new mainFrame("Kill Me", wxDefaultPosition, wxSize(640, 480));
    frame->Show();
    return true;
}