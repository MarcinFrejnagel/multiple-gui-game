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

enum IDentities
{
	buttonThrowID = 0,
	buttonExitID = 1,
	buttonSaveID = 2,
	buttonRestartID = 3
};

class Dices : public wxFrame
{
public:
	Dices(const wxString& title, string nick);
	~Dices();
	string nickname;
	bool botPlaying;
	wxPanel* panel;
	wxStaticBitmap **dices;
	wxStaticText* winInfo, *throwCounterInfo, *pointsInfo;
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
	void createButtons();
	void createText();
	void setGrid();
	void loadBitmaps();
	void drawNumber();
	int findTheSameDices(int numberOfDices);
	int find3x2x();
	int findFromTo(int choice);
	void playBot();
	int getPoints();
	void winner();
};