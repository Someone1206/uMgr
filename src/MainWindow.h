#pragma once
#include <wx/wx.h>
#include <string>
#include <fstream>
#include <vector>

class MainWindow
	:public wxFrame
{
public:
	MainWindow(std::string title, const wxPoint& pos, const char* _gen_paf);

	const char* gen_paf;

	std::vector<std::string> names, paths; // arbirtary length of 10
	
	wxPanel* __p_pane = nullptr;
	// pane for everything
	wxBoxSizer* __p_sizer = nullptr;
	// sizer for everything

	wxBoxSizer* p_log_s = nullptr;
	// panel layout when all logs selected
	wxBoxSizer* p_all_s = nullptr;
	// panel layout when viewing any other thing except all logs

	wxChoice* grp_list = nullptr;
	// combobox for groups
	wxTextCtrl* logs = nullptr;
	// text ctrl to show logs

	void ReadGen();

	enum 
	{
		ID_GRP_LIST,
		ID_BTN_AL,
		ID_BTN_LL
	};

	~MainWindow() {}
};

