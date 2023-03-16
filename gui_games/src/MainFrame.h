#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "TicTacToe.h"
#include "Dices.h"

using namespace std;

enum IDs
{
	ticTacClick = 0,
	dicesClick = 1,
	nicknameClick = 2
};

class MainFrame : public wxFrame
{
private:
	wxPanel* panel;
	string nickname;
	wxTextCtrl* setNickText;
	wxStaticText* nickText;
	wxButton* nickButton;
	wxBitmapButton* ticTacToeButton, *dicesButton;
	wxPNGHandler* handler;

	void setUserNickname(wxCommandEvent& event);
	void buttonClickedTicTacToe(wxCommandEvent& event);
	void buttonClickedDices(wxCommandEvent& event);

	void setDesign();
	void createButtons();

public:
	MainFrame(const wxString& title);
	~MainFrame();

	wxDECLARE_EVENT_TABLE();
};
