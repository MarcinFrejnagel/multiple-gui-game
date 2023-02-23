#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

class TicTacToe : public wxFrame
{
public:
	TicTacToe(const wxString& title, string nick);
	char board[3][3];
	wxBitmapButton** Buttons;
	wxPanel* panel;
	string nickname;
	int round_number;

	void PlayGame();
	int is_win();
	
	void OnButtonClicked1(wxCommandEvent& event);
	void OnButtonClicked2(wxCommandEvent& event);
	void OnButtonClicked3(wxCommandEvent& event);
	void OnButtonClicked4(wxCommandEvent& event);
	void OnButtonClicked5(wxCommandEvent& event);
	void OnButtonClicked6(wxCommandEvent& event);
	void OnButtonClicked7(wxCommandEvent& event);
	void OnButtonClicked8(wxCommandEvent& event);
	void OnButtonClicked9(wxCommandEvent& event);
	void OnButtonClickedEndGame(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
	
};
