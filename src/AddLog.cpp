#include "AddLog.h"


wxBEGIN_EVENT_TABLE(AddLog, wxFrame)
    EVT_CALENDAR_SEL_CHANGED(ID_CAL, AddLog::onDateSel)
    EVT_TIME_CHANGED(ID_TIME, AddLog::onTimeSel)
    EVT_BUTTON(ID_TIME_NOW, AddLog::onTimeNow)
    EVT_BUTTON(ID_DATE_NOW, AddLog::onDateToday)
    EVT_TEXT_MAXLEN(ID_PARAMS, AddLog::limitExceed)
    EVT_BUTTON(ID_CANCEL, AddLog::cancel)
    EVT_BUTTON(ID_ADD, AddLog::okei)
wxEND_EVENT_TABLE()

AddLog::AddLog(wxWindow* frame, const wxString& title, ReadOptions readOption, const wxString& entryName,
    const wxPoint& pos, const wxSize& size, const wxString& path)
    :
    wxFrame(frame, 69, title, pos, size, wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT)
{
    __frame = frame;  // assigning frame to __frame for enabling the frame later
    __frame->Enable(false);
    option = readOption;
    paf = std::string(path.mb_str());
    name = std::string(entryName.mb_str());

    wxPanel* __p_pane = new wxPanel(this, 699);  // the topmost panel
    wxBoxSizer* __p_pane_sizer = new wxBoxSizer(wxVERTICAL); // sizer for topmost panel
    __p_pane_sizer->Add(__p_pane, 1, wxEXPAND);

    wxBoxSizer* p_sizer = new wxBoxSizer(wxVERTICAL);       
    // sizer for the stuffs inside the topmost panel
    // i.e. all the controls
    wxStaticText* name = new wxStaticText(__p_pane, 69, entryName); // label for the entry name
    {
        wxFont name_font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        name->SetFont(name_font);
    }

    wxBoxSizer* info_sizer = new wxBoxSizer(wxHORIZONTAL);  
    // sizer to hold the crap in the middle part
    // i.e. calendar, time and genre exclusive stuffs

    // sizer for calendar
    wxBoxSizer* __cal = new wxBoxSizer(wxVERTICAL);
    date = new wxCalendarCtrl(__p_pane, ID_CAL, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize,
        wxCAL_SUNDAY_FIRST | wxCAL_SHOW_HOLIDAYS | wxCAL_SHOW_SURROUNDING_WEEKS | wxCAL_SEQUENTIAL_MONTH_SELECTION | wxCAL_SHOW_WEEK_NUMBERS);
    date->SetDate(wxDateTime::Now());
    wxButton* date_now = new wxButton(__p_pane, ID_DATE_NOW, "&Set Today's Date");
    __date = new wxStaticText(__p_pane, 69, ("Date Selected:    " + formatDate(date->GetDate().FormatISODate())));
    __cal->Add(__date, 0.1, wxEXPAND | wxBOTTOM | wxLEFT | wxALIGN_LEFT, 6);
    __cal->Add(date_now, 0.1, wxEXPAND | wxBOTTOM | wxLEFT | wxALIGN_LEFT, 6);
    __cal->Add(date, 1, wxEXPAND | wxTOP | wxLEFT, 6);
    //
    
    // sizer for time and genre exclusive controls
    wxBoxSizer* __clock_N_O = new wxBoxSizer(wxVERTICAL);
    time = new wxTimePickerCtrl(__p_pane, ID_TIME, wxDefaultDateTime);
    time->SetValue(wxDateTime::Now());
    __time = new wxStaticText(__p_pane, 6989, ("Time Selected:    " + time->GetValue().FormatISOTime()));
    // %x to replace
    time_now = new wxButton(__p_pane, ID_TIME_NOW, "&Set Current Time");
    //
    wxBoxSizer* __clock = new wxBoxSizer(wxHORIZONTAL); // sizer for time only
    __clock->Add(time, 1, wxEXPAND | wxALL, 6);
    __clock->Add(time_now, 1, wxEXPAND | wxALL, 6);

    // disabling them by default
    wxStaticText* _param1_ = new wxStaticText(__p_pane, 69, "Not available for current Genre");
    wxStaticText* _param2_ = new wxStaticText(__p_pane, 69, "Not available for current Genre");
    _param1_->Enable(false);
    _param2_->Enable(false);
    param1 = new NumCtrl(__p_pane, ID_PARAMS, "Not available for current Genre");
    param2 = new NumCtrl(__p_pane, ID_PARAMS, "Not available for current Genre");
    param1->Enable(false);
    param2->Enable(false);

    if (readOption == Anime) {
        _param1_->SetLabel("Season:");
        _param2_->SetLabel("Episode:");
        param1->SetValue("");
        param2->SetValue("");

        _param1_->Enable();
        _param2_->Enable();
        param1->Enable();
        param2->Enable();
    }
    else if (readOption == Manga) {
        _param1_->SetLabel("Chapter:");
        _param2_->SetLabel("Page:");
        param1->SetValue("");
        param2->SetValue("");

        _param1_->Enable();
        _param2_->Enable();
        param1->Enable();
        param2->Enable();
    }
    else if (readOption == Movies) {
        _param1_->SetLabel("Part (optional):");
        param1->SetValue("");

        _param1_->Enable();
        param1->Enable();
    }



    __clock_N_O->Add(__time, 1, wxEXPAND | wxALL | wxALIGN_LEFT, 12);
    __clock_N_O->Add(__clock, 1, wxEXPAND | wxLEFT | wxRIGHT, 6);
    __clock_N_O->Add(_param1_, 0.5, wxEXPAND | wxLEFT | wxRIGHT, 6);
    __clock_N_O->Add(param1, 1, wxEXPAND | wxLEFT | wxRIGHT, 6);
    __clock_N_O->Add(_param2_, 0.5, wxEXPAND | wxLEFT | wxRIGHT, 6);
    __clock_N_O->Add(param2, 1, wxEXPAND | wxLEFT | wxRIGHT, 6);

    info_sizer->Add(__cal, 1, wxEXPAND | wxALL, 5);
    info_sizer->Add(__clock_N_O, 1, wxEXPAND | wxALL, 5);

    // sizer for details and stuffs
    wxBoxSizer* __det_sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* det = new wxStaticText(__p_pane, 69, "Details:");
    details = new wxTextCtrl(__p_pane, 69, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    __det_sizer->Add(det, 1, wxEXPAND | wxALIGN_LEFT | wxLEFT | wxBOTTOM | wxRIGHT, 5);
    __det_sizer->Add(details, 3, wxEXPAND | wxLEFT | wxBOTTOM | wxRIGHT, 5);

    // sizer for add and cancel buttons
    wxBoxSizer* btn_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* add_btn = new wxButton(__p_pane, ID_ADD, "Add");
    wxButton* canc_btn = new wxButton(__p_pane, ID_CANCEL, "Cancel");
    btn_sizer->Add(canc_btn, wxEXPAND | wxALL | wxALIGN_RIGHT, 5);
    btn_sizer->Add(add_btn, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT | wxALIGN_RIGHT, 5);


    p_sizer->Add(name, 0.1, wxEXPAND | wxLEFT | wxTOP | wxALIGN_LEFT, 15); // adding name
    p_sizer->Add(info_sizer, 0.45, wxEXPAND | wxALL, 1);           // adding the other information stuffs
    p_sizer->Add(__det_sizer, 0.45, wxEXPAND | wxALL, 1);
    p_sizer->Add(btn_sizer, wxALL | wxEXPAND, 1);
    __p_pane->SetSizerAndFit(p_sizer);

    this->SetSizerAndFit(__p_pane_sizer);
}

void AddLog::onDateSel(wxCalendarEvent& evt)
{
    __date->SetLabel(("Date Selected:    " + formatDate(evt.GetDate().FormatISODate())));
}

void AddLog::onTimeSel(wxDateEvent& evt)
{
    __time->SetLabel(("Time Selected:    " + time->GetValue().FormatISOTime()));
}

void AddLog::onTimeNow(wxCommandEvent& evt)
{
    time->SetValue(wxDateTime::Now());
    __time->SetLabel(("Time Selected:    " + time->GetValue().FormatISOTime()));
}

void AddLog::onDateToday(wxCommandEvent& evt)
{
    date->SetDate(wxDateTime::Now());
    __date->SetLabel(("Date Selected:    " + formatDate(date->GetDate().FormatISODate())));
}

void AddLog::limitExceed(wxCommandEvent& evt)
{
    wxMessageBox("Bish that's impossible!", " ");
}

void AddLog::okei(wxCommandEvent& evt)
{
    std::string __details__ =
        std::string(formatDate(date->GetDate().FormatISODate()).mb_str()) + "\n" +
        std::string(time->GetValue().FormatISOTime().mb_str()) + "\n";

    if (option == Anime) {
        std::string msg = "";
        bool isEmpty = false;
        if (param1->IsEmpty()) {
            msg = "Season number can't be empty\n";
            isEmpty = true;
        }
        if (param2->IsEmpty()) {
            msg += "Episode number can't be empty";
            isEmpty = true;
        }
        if (isEmpty) {
            wxMessageBox(msg, "Empty Fields!");
            return;
        }
        __details__ += std::string(param1->GetValue().mb_str()) + "\n" +
            std::string(param2->GetValue().mb_str()) + "\n";
        // くそが get int doesn't work...
    }
    else if (option == Manga) {
        std::string msg = "";
        bool isEmpty = false;
        if (param1->IsEmpty()) {
            msg = "Chapter number can't be empty\n";
            isEmpty = true;
        }
        if (param2->IsEmpty()) {
            msg += "Page number can't be empty";
            isEmpty = true;
        }
        if (isEmpty) {
            wxMessageBox(msg, "Empty Fields!");
            return;
        }
        __details__ += std::string(param1->GetValue().mb_str()) + "\n" +
            std::string(param2->GetValue().mb_str()) + "\n";
    }
    __details__ += std::string(details->GetValue().mb_str()) + "\n";

    writeFile(paf, __details__, WriteOption::Create | WriteOption::Add, name);

    Destroy();
}

void AddLog::cancel(wxCommandEvent& evt)
{
    Destroy();
}

wxString AddLog::formatDate(wxString string1)
{
    std::string toFormat = std::string(string1.mb_str());
    int monthNo_1 = toFormat.at(5) - '0', monthNo_2 = toFormat.at(6) - '0';

    std::string month = "Jan", day = toFormat.substr(toFormat.length() - 2), year = toFormat.substr(0, 4);
    
    if (monthNo_1 <= 0) {
        switch (monthNo_2)
        {
        case 1:
            month = "January";
            break;
        case 2:
            month = "February";
            break;
        case 3:
            month = "March";
            break;
        case 4:
            month = "April";
            break;
        case 5:
            month = "May";
            break;
        case 6:
            month = "June";
            break;
        case 7:
            month = "July";
            break;
        case 8:
            month = "August";
            break;
        case 9:
            month = "September";
            break;
        default:
            break;
        }
    }
    else {
        switch (monthNo_2)
        {
        case 0:
            month = "Jimtober";   // 🥳🥳❤❤💜💜😊🎆🎇✨🎉🎊💜💜❤❤🥳🥳
            break;
        case 1:
            month = "November";
            break;
        case 2:
            month = "December";
            break;
        default:
            break;
        }
    }

    return wxString((day + "-" + month + "-" + year));
}

AddLog::~AddLog()
{
    __frame->Enable();
}
