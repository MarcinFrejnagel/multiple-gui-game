#include <wx/wx.h>
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	
	wxPanel* panel = new wxPanel(this); // newwin
	wxPNGHandler *handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxBitmap SnakeIMG, TicIMG, DicesIMG;
	SnakeIMG.LoadFile("snake.png", wxBITMAP_TYPE_PNG);
	DicesIMG.LoadFile("dices.png", wxBITMAP_TYPE_PNG);
	TicIMG.LoadFile("tictactoe.png", wxBITMAP_TYPE_PNG);

	wxBitmapButton * SnakeButton = new wxBitmapButton(panel, wxID_ANY, SnakeIMG, wxPoint(0, 0), wxSize(300, 800), 0);
	wxBitmapButton * TicTacToeButton = new wxBitmapButton(panel, wxID_ANY, TicIMG, wxPoint(300, 0), wxSize(300, 800), 0);
	wxBitmapButton * DicesButton = new wxBitmapButton(panel, wxID_ANY, DicesIMG, wxPoint(600, 0), wxSize(300, 800), 0);
	
	
	//wxButton* SnakeButton = new wxButton(panel, wxID_ANY, "Snake", wxPoint(100, 450), wxSize(100, 30)); // add przycisk
	//wxButton* TicTacToeButton = new wxButton(panel, wxID_ANY, "TicTacToe", wxPoint(350, 450), wxSize(100, 30)); // add przycisk
	//wxButton* DicesButton = new wxButton(panel, wxID_ANY, "Dices", wxPoint(600, 450), wxSize(100, 30)); // add przycisk
	//wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "tekst i chuj", wxPoint(70, 30)); // statyczny tekst
	//wxTextCtrl *textCtrl = new wxTextCtrl(panel, wxID_ANY, "nickname", wxPoint(500, 145), wxSize(200, -1)); // mozliwosc wpisania tekstu do ramki

};