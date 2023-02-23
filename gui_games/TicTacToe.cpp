#include "TicTacToe.h"
enum IDentities
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

wxBEGIN_EVENT_TABLE(TicTacToe, wxFrame)
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
wxEND_EVENT_TABLE()

TicTacToe::TicTacToe(const wxString& title, string nick) : wxFrame(nullptr, wxID_ANY, title)
{
	this->nickname = nick;
	this->panel= new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));

	wxPNGHandler *handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxStaticBitmap *tictactoe_board = new wxStaticBitmap(this->panel, wxID_ANY, wxBitmap("leg_board.png", wxBITMAP_TYPE_PNG), wxPoint(170, 70), wxSize(10, 440));
	wxStaticBitmap *tictactoe_board1 = new wxStaticBitmap(this->panel, wxID_ANY, wxBitmap("leg_board.png", wxBITMAP_TYPE_PNG), wxPoint(320, 70), wxSize(10, 440));
	wxStaticBitmap *tictactoe_board2 = new wxStaticBitmap(this->panel, wxID_ANY, wxBitmap("leg2_board.png", wxBITMAP_TYPE_PNG), wxPoint(30, 360), wxSize(440, 10));
	wxStaticBitmap *tictactoe_board3 = new wxStaticBitmap(this->panel, wxID_ANY, wxBitmap("leg2_board.png", wxBITMAP_TYPE_PNG), wxPoint(30, 210), wxSize(440, 10));
	this->panel->SetBackgroundColour(wxColor(80, 80, 150));


	wxStaticText* staticText = new wxStaticText(this->panel, wxID_ANY, "Counter of rounds:", wxPoint(600, 50)); // statyczny tekst
	//wxStaticText* staticText2 = new wxStaticText(this->panel, wxID_ANY, this->round_number, wxPoint(600, 70)); // statyczny tekst

	wxStaticText* staticText3 = new wxStaticText(this->panel, wxID_ANY, this->nickname, wxPoint(600, 10)); // statyczny tekst

	wxLogStatus("Tic tac toe");


	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			*(*(this->board + i) + j) = 0;


	wxBitmap X, Circle, Empty;

	X.LoadFile("x.png", wxBITMAP_TYPE_PNG);
	Circle.LoadFile("circle.png", wxBITMAP_TYPE_PNG);
	Empty.LoadFile("empty.png", wxBITMAP_TYPE_PNG);


	/*// wyznacz wymiary panelu
	int panelWidth = this->panel->GetSize().GetWidth();
	int panelHeight = this->panel->GetSize().GetHeight();

	// wyznacz wymiary bitmapy X
	int xWidth = X.GetWidth();
	int xHeight = X.GetHeight();

	// oblicz pozycjê, na której ma byæ rysowany obrazek X
	int xX = (panelWidth - xWidth) / 2;
	int xY = (panelHeight - xHeight) / 2;

	// utwórz instancjê wxStaticBitmap i ustaw jej bitmapê oraz pozycjê
	wxStaticBitmap* xBitmap = new wxStaticBitmap(this->panel, wxID_ANY, X, wxPoint(xX, xY), wxSize(xWidth, xHeight));*/
	
	this->Buttons = new wxBitmapButton * [9];

	*(this->Buttons) = new wxBitmapButton(this->panel, Button_board_1, Empty, wxPoint(30, 70), wxSize(140, 140), 0);
	*(this->Buttons + 1) = new wxBitmapButton(this->panel, Button_board_2, Empty, wxPoint(180, 70), wxSize(140, 140), 0);
	*(this->Buttons + 2) = new wxBitmapButton(this->panel, Button_board_3, Empty, wxPoint(330, 70), wxSize(140, 140), 0);
	*(this->Buttons + 3) = new wxBitmapButton(this->panel, Button_board_4, Empty, wxPoint(30, 220), wxSize(140, 140), 0);
	*(this->Buttons + 4) = new wxBitmapButton(this->panel, Button_board_5, Empty, wxPoint(180, 220), wxSize(140, 140), 0);
	*(this->Buttons + 5) = new wxBitmapButton(this->panel, Button_board_6, Empty, wxPoint(330, 220), wxSize(140, 140), 0);
	*(this->Buttons + 6) = new wxBitmapButton(this->panel, Button_board_7, Empty, wxPoint(30, 370), wxSize(140, 140), 0);
	*(this->Buttons + 7) = new wxBitmapButton(this->panel, Button_board_8, Empty, wxPoint(180, 370), wxSize(140, 140), 0);
	*(this->Buttons + 8) = new wxBitmapButton(this->panel, Button_board_9, Empty, wxPoint(330, 370), wxSize(140, 140), 0);

}


void TicTacToe::OnButtonClicked1(wxCommandEvent& event)
{
	if (*(*(this->board)) == 0)
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
void TicTacToe::OnButtonClicked2(wxCommandEvent& event)
{
	
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
void TicTacToe::OnButtonClicked3(wxCommandEvent& event)
{
	
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
void TicTacToe::OnButtonClicked4(wxCommandEvent& event)
{
	
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
void TicTacToe::OnButtonClicked5(wxCommandEvent& event)
{
	
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
void TicTacToe::OnButtonClicked6(wxCommandEvent& event)
{
	if (*(*(board + 1) + 2) == 0)
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
void TicTacToe::OnButtonClicked7(wxCommandEvent& event)
{
	if (*(*(board + 2)) == 0)
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
void TicTacToe::TicTacToe::OnButtonClicked8(wxCommandEvent& event)
{
	if (*(*(board + 2) + 1) == 0)
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
void TicTacToe::OnButtonClicked9(wxCommandEvent& event)
{
	if (*(*(board + 2) + 2) == 0)
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
void TicTacToe::OnButtonClickedEndGame(wxCommandEvent& event)
{

}
void TicTacToe::PlayGame()
{
	if (this->round_number < 4) {
		srand(time(NULL));
		this->round_number++;

		int choiceX = 0;
		int choiceY = 0;

		if(this->round_number > 2)
			if(is_win())
				return;
		
		while (1) {
			choiceX = rand() % 3;
			choiceY = rand() % 3;
			if (*(*(board + choiceY) + choiceX) == 0)
				break;
		}

		*(*(board + choiceY) + choiceX) = 2;

		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		wxBitmap X, Circle, Empty;
		Circle.LoadFile("circle.png", wxBITMAP_TYPE_PNG);
		(*(this->Buttons + choiceY * 3 + choiceX ))->SetBitmap(Circle);
	}
}
int TicTacToe::is_win()
{
	for (int i = 0; i < 3; i++)
	{
		if (*(*(board + i)) == 1 && *(*(board + i) + 1) == 1 && *(*(board + i) + 2) == 1)
		{
			return 1;
		}

		if (*(*(board + i)) == 2 && *(*(board + i) + 1) == 2 && *(*(board + i) + 2) == 2)
		{
			return 2;
		}

		if (*(*(board)+i) == 1 && *(*(board + 1) + i) == 1 && *(*(board + 2) + i) == 1)
		{
			return 1;
		}

		if (*(*(board)+i) == 2 && *(*(board + 1) + i) == 2 && *(*(board + 2) + i) == 2)
		{
			return 2;
		}
	}

	if (*(*(board)) == 1 && *(*(board + 1) + 1) == 1 && *(*(board + 2) + 2) == 1)
	{
		return 1;
	}
	if (*(*(board)) == 2 && *(*(board + 1) + 1) == 2 && *(*(board + 2) + 2) == 2)
	{
		return 2;
	}

	if (*(*(board)+2) == 1 && *(*(board + 1) + 1) == 1 && *(*(board + 2)) == 1)
	{
		return 1;
	}

	if (*(*(board)+2) == 2 && *(*(board + 1) + 1) == 2 && *(*(board + 2)) == 2)
	{
		return 2;
	}
}