#pragma once
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <wx/grid.h>

using namespace std;

class Dices : public wxFrame
{
public:
	Dices(const wxString& title, string nick);
	~Dices();
	string nickname;
	wxPanel* panel;
	wxStaticBitmap **dices;
	wxBitmap dicesBitmaps[6];
	int diceScore[5];
	wxButton* buttonThrow, *buttonExit, *buttonSave, *buttonRestart;
	wxPNGHandler* handler;
	wxGrid* grid;
	int throwCounter, roundNumber, scores[2][14];

	void throwDices(wxCommandEvent& event);
	void exitDices(wxCommandEvent& event);
	void savePoints(wxCommandEvent& event);
	void restartGame(wxCommandEvent& event);
	void savePointsToGrid(int player);

	wxDECLARE_EVENT_TABLE();

private:
	void setGrid();
	void loadBitmaps();
	void drawNumber();
	int findTheSameDices(int numberOfDices);
	int find3x2x();
	int findFromTo(int choice);
};