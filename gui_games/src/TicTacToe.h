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
private:
	char board[3][3];
	char counterOfText[30];
	wxBitmapButton** buttons;
	wxPanel* panel;
	wxStaticText* winInfo, * counterText, * nicknameText, * scoreTextPlayer, * scoreTextBot;
	wxStaticBitmap** tictactoeBoard;
	string nickname;
	int roundNumber, playerScore, botScore;
	wxButton* resetButton, * exitButton;
	bool inGame;
	wxPNGHandler* handler;
	wxBitmap x, circle, empty;

	void buttonClicked1(wxCommandEvent& event);
	void buttonClicked2(wxCommandEvent& event);
	void buttonClicked3(wxCommandEvent& event);
	void buttonClicked4(wxCommandEvent& event);
	void buttonClicked5(wxCommandEvent& event);
	void buttonClicked6(wxCommandEvent& event);
	void buttonClicked7(wxCommandEvent& event);
	void buttonClicked8(wxCommandEvent& event);
	void buttonClicked9(wxCommandEvent& event);
	void reset(wxCommandEvent& event);
	void exit(wxCommandEvent& event);

	void playGame();
	int is_win();
	void create_board();
	void create_text();

public:
	TicTacToe(const wxString& title, string nick);
	~TicTacToe();

	wxDECLARE_EVENT_TABLE();
};
