#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <iostream>
#include <string>
#include <time.h>
#include "TicTacToe.h"
#include "Dices.h"

#include <stdlib.h>

using namespace std;

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	wxPanel* panel;
	string nickname;
	wxTextCtrl* text_to_copy;
private:
	void SetUserNickname(wxCommandEvent &event);

	void OnButtonClickedSnake(wxCommandEvent &event);
	void OnButtonClickedTicTacToe(wxCommandEvent &event);
	void OnButtonClickedDices(wxCommandEvent &event);
	void OnButtonClickedBeetween(wxCommandEvent &event);
	wxDECLARE_EVENT_TABLE();
};