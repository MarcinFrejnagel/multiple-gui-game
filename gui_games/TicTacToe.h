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
	~TicTacToe();
	char board[3][3];
	char counter_text[30], score_text[30];
	wxBitmapButton** Buttons;
	wxPanel* panel;
	wxStaticText* WinInfo, *staticText, *staticText2, *scoreText, *scoreText2;
	wxStaticBitmap** tictactoe_board;
	string nickname;
	int round_number, player_score, bot_score;
	wxButton *resetButton, *exitButton;
	bool inGame;
	wxPNGHandler* handler;
	wxBitmap X, Circle, Empty;

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
	void Reset(wxCommandEvent& event);
	void Exit(wxCommandEvent& event);
	
	void free_memory();
	void create_board();
	void create_text();

	wxDECLARE_EVENT_TABLE();
};
