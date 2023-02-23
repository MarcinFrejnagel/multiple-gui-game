#include "TicTacToe.h"

/*enum IDentities
{
	Button_board_1 = 0,
	Button_board_2 = 1,
	Button_board_3 = 2,
	Button_board_4 = 3,
	Button_board_5 = 4,
	Button_board_6 = 5,
	Button_board_7 = 6,
	Button_board_8 = 7,
	Button_board_9 = 8,
	Button_end_game
};
*/
/*wxBEGIN_EVENT_TABLE(TicTacToe, wxFrame)
	EVT_BUTTON(Button_board_1, TicTacToe::OnButtonClicked1)
	EVT_BUTTON(Button_board_2, TicTacToe::OnButtonClicked2)
	EVT_BUTTON(Button_board_3, TicTacToe::OnButtonClicked3)
	EVT_BUTTON(Button_board_4, TicTacToe::OnButtonClicked4)
	EVT_BUTTON(Button_board_5, TicTacToe::OnButtonClicked5)
	EVT_BUTTON(Button_board_6, TicTacToe::OnButtonClicked6)
	EVT_BUTTON(Button_board_7, TicTacToe::OnButtonClicked7)
	EVT_BUTTON(Button_board_8, TicTacToe::OnButtonClicked8)
	EVT_BUTTON(Button_board_9, TicTacToe::OnButtonClicked9)
	EVT_BUTTON(Button_end_game, TicTacToe::OnButtonClickedEndGame)
wxEND_EVENT_TABLE()*/

TicTacToe::TicTacToe()
{
	/*for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			*(*(this->board + i) + j) = 0;

	this->Buttons = new wxBitmapButton * [9];

	this->GamePanel = new wxPanel(this);

	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxBitmap X, Circle, Empty;
	X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
	Circle.LoadFile("circle.png", wxBITMAP_TYPE_PNG);
	Empty.LoadFile("empty.png", wxBITMAP_TYPE_PNG);

	(this->Buttons) = new wxBitmapButton(this->GamePanel, Button_board_1, Empty, wxPoint(140 + 50, 140 + 50), wxSize(140, 140), 0);
	*/

}

/*
void OnButtonClicked1(wxCommandEvent& event)
{
	/*if (*(*(board)) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons))->SetBitmap(X);
		*(*(board)) = 1;
		PlayGame();
	}
}
void OnButtonClicked2(wxCommandEvent& event)
{
	/*
	if (*(*(board) + 1) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 1))->SetBitmap(X);
		*(*(board) + 1) = 1;
		PlayGame();
	}
}
void OnButtonClicked3(wxCommandEvent& event)
{
	/*
	if (*(*(board) + 2) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 2))->SetBitmap(X);
		*(*(board) + 2) = 1;
		PlayGame();
	}
}
void OnButtonClicked4(wxCommandEvent& event)
{
	/*
	if (*(*(board + 1)) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 3))->SetBitmap(X);
		*(*(board + 1)) = 1;
		PlayGame();
	}
}
void OnButtonClicked5(wxCommandEvent& event)
{
	/*
	if (*(*(board + 1) + 1) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 4))->SetBitmap(X);
		*(*(board + 1) + 1) = 1;
		PlayGame();
	}
}
void OnButtonClicked6(wxCommandEvent& event)
{
	/*if (*(*(board + 1) + 2) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 5))->SetBitmap(X);
		*(*(board + 1) + 2) = 1;
		PlayGame();
	}
}
void OnButtonClicked7(wxCommandEvent& event)
{
	/*if (*(*(board + 2)) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 6))->SetBitmap(X);
		*(*(board + 2)) = 1;
		PlayGame();
	}
}
void OnButtonClicked8(wxCommandEvent& event)
{
	/*if (*(*(board + 2) + 1) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 7))->SetBitmap(X);
		*(*(board + 2) + 1) = 1;
		PlayGame();
	}
}
void OnButtonClicked9(wxCommandEvent& event)
{
	/*if (*(*(board + 2) + 2) == 0)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + 8))->SetBitmap(X);
		*(*(board + 2) + 2) = 1;
		PlayGame();
	}
}

void PlayGame()
{
	this->round_number++;
	
	while(1){
		int choice = rand() % 9;

		if (*(*(borad + choice % 3) + choice / 3) == 0)
			break;
	}

	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxBitmap X, Circle, Empty;
	X.LoadFile("x.png", wxBITMAP_TYPE_PNG);

	(*(this->Buttons + choice))->SetBitmap(X);
	
}

*/