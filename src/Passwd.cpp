#include <fstream>
#include "Passwd.h"
#include "ufw/GV.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(Passwd, wxFrame)
	EVT_BUTTON(Passwd::ID_GO_BTN, Passwd::OnGo)
wxEND_EVENT_TABLE()


Passwd::Passwd(std::string title, const char* paf)
	:wxFrame(nullptr, 69, title), grp_index_paf(paf)
{
	// frame design
	wxPanel* __p_pane = new wxPanel(this);
	wxBoxSizer* __p_sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* pwdMsg = new wxStaticText(__p_pane, 69, "Type the password");
	__p_sizer->Add(pwdMsg, 1, wxCENTER | wxALL, 5);

	password = new wxTextCtrl(__p_pane, ID_PWD_TXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	__p_sizer->Add(password, 1, wxALIGN_CENTER | wxALL, 1);

	wxButton* btn = new wxButton(__p_pane, ID_GO_BTN, "ゴ～");
	__p_sizer->Add(btn, 1, wxALIGN_CENTER | wxALL, 5);

	__p_pane->SetSizerAndFit(__p_sizer);
}

void Passwd::OnGo(wxCommandEvent& evt)
{
	std::ifstream pwdFile(GV::user_folder + GV::fsep + "Password.baka");
	std::string pwdStr = "";
	getline(pwdFile, pwdStr);
	if (password->GetValue() == pwdStr)
	{
		// go to mainframe
		std::ofstream f(GV::user_folder + GV::fsep + "ggg.txt");
		f << (char)1;
		f.close();
		wxMessageBox("Proceede", "?");
		MainWindow* ffff = new MainWindow("uMgr", wxPoint(), grp_index_paf);
		ffff->Show();
		Destroy();
	}
	else
	{
		wxMessageBox("Passwords don't Match!", "Invalid Password");
		password->SelectAll();
	}
}