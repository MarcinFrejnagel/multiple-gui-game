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
	Button_reset = 9,
	Button_exit = 10
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
EVT_BUTTON(Button_reset, TicTacToe::Reset)
EVT_BUTTON(Button_exit, TicTacToe::Exit)
wxEND_EVENT_TABLE()

TicTacToe::TicTacToe(const wxString& title, string nick) : wxFrame(nullptr, wxID_ANY, title)
{
	nickname = nick;
	panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
	panel->SetBackgroundColour(wxColor(80, 80, 150));
	player_score = 0;
	bot_score = 0;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			*(*(board + i) + j) = 0;

	inGame = true;
	round_number = 0;

	create_board();
	create_text();

	wxLogStatus("Tic tac toe");
}

TicTacToe::~TicTacToe() {
	free_memory();
}

void TicTacToe::create_text()
{
	strcpy(counter_text, "Number of rounds: 0");

	wxFont fontText(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont fontInfo(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont fontButton(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	wxColor color2(0, 200, 0), color3(229, 204, 255);

	resetButton = new wxButton(panel, Button_reset, "Reset", wxPoint(570, 400), wxSize(90, 50));
	exitButton = new wxButton(panel, Button_exit, "Exit", wxPoint(700, 400), wxSize(90, 50));

	resetButton->SetCursor(wxCursor(wxCURSOR_HAND));
	exitButton->SetCursor(wxCursor(wxCURSOR_HAND));

	counterText = new wxStaticText(panel, wxID_ANY, counter_text, wxPoint(550, 140)); // statyczny tekst
	nicknameText = new wxStaticText(panel, wxID_ANY, "Nickname: " + nickname, wxPoint(550, 100)); // statyczny tekst
	scoreTextPlayer = new wxStaticText(panel, wxID_ANY, "Player score: " + to_string(player_score), wxPoint(550, 180));
	scoreTextBot = new wxStaticText(panel, wxID_ANY, "Bot score: " + to_string(bot_score), wxPoint(550, 220));
	WinInfo = new wxStaticText(panel, wxID_ANY, "     ", wxPoint(600, 300), wxSize(100, 20));

	resetButton->SetFont(fontButton);
	resetButton->SetBackgroundColour(color3);

	exitButton->SetFont(fontButton);
	exitButton->SetBackgroundColour(color3);

	counterText->SetFont(fontText);
	counterText->SetForegroundColour(wxColor(200, 200, 200));

	nicknameText->SetFont(fontText);
	nicknameText->SetForegroundColour(wxColor(200, 200, 200));

	WinInfo->SetFont(fontInfo);
	WinInfo->SetForegroundColour(color2);

	scoreTextPlayer->SetFont(fontText);
	scoreTextPlayer->SetForegroundColour(color2);

	scoreTextBot->SetFont(fontText);
	scoreTextBot->SetForegroundColour(wxColor(255, 51, 51));
}

void TicTacToe::create_board()
{
	handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	tictactoe_board = new wxStaticBitmap * [4];

	*tictactoe_board = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg_board.png", wxBITMAP_TYPE_PNG), wxPoint(170, 70), wxSize(10, 440));
	*(tictactoe_board + 1) = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg_board.png", wxBITMAP_TYPE_PNG), wxPoint(320, 70), wxSize(10, 440));
	*(tictactoe_board + 2) = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg2_board.png", wxBITMAP_TYPE_PNG), wxPoint(30, 360), wxSize(440, 10));
	*(tictactoe_board + 3) = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg2_board.png", wxBITMAP_TYPE_PNG), wxPoint(30, 210), wxSize(440, 10));


	x.LoadFile("x.png", wxBITMAP_TYPE_PNG);
	circle.LoadFile("circle.png", wxBITMAP_TYPE_PNG);
	empty.LoadFile("empty.png", wxBITMAP_TYPE_PNG);

	buttons = new wxBitmapButton * [9];

	*(buttons) = new wxBitmapButton(panel, Button_board_1, empty, wxPoint(30, 70), wxSize(140, 140), 0);
	*(buttons + 1) = new wxBitmapButton(panel, Button_board_2, empty, wxPoint(180, 70), wxSize(140, 140), 0);
	*(buttons + 2) = new wxBitmapButton(panel, Button_board_3, empty, wxPoint(330, 70), wxSize(140, 140), 0);
	*(buttons + 3) = new wxBitmapButton(panel, Button_board_4, empty, wxPoint(30, 220), wxSize(140, 140), 0);
	*(buttons + 4) = new wxBitmapButton(panel, Button_board_5, empty, wxPoint(180, 220), wxSize(140, 140), 0);
	*(buttons + 5) = new wxBitmapButton(panel, Button_board_6, empty, wxPoint(330, 220), wxSize(140, 140), 0);
	*(buttons + 6) = new wxBitmapButton(panel, Button_board_7, empty, wxPoint(30, 370), wxSize(140, 140), 0);
	*(buttons + 7) = new wxBitmapButton(panel, Button_board_8, empty, wxPoint(180, 370), wxSize(140, 140), 0);
	*(buttons + 8) = new wxBitmapButton(panel, Button_board_9, empty, wxPoint(330, 370), wxSize(140, 140), 0);

	for(int i = 0; i < 9; ++i)
		(*(buttons + i))->SetCursor(wxCursor(wxCURSOR_HAND));

}

void TicTacToe::OnButtonClicked1(wxCommandEvent& event)
{
	if (*(*(board)) == 0 && inGame)
	{
		(*(buttons))->SetBitmap(x);
		*(*(board)) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked2(wxCommandEvent& event)
{

	if (*(*(board)+1) == 0 && inGame)
	{
		(*(buttons + 1))->SetBitmap(x);
		*(*(board)+1) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked3(wxCommandEvent& event)
{

	if (*(*(board)+2) == 0 && inGame)
	{
		(*(buttons + 2))->SetBitmap(x);
		*(*(board)+2) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked4(wxCommandEvent& event)
{

	if (*(*(board + 1)) == 0 && inGame)
	{
		(*(buttons + 3))->SetBitmap(x);
		*(*(board + 1)) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked5(wxCommandEvent& event)
{

	if (*(*(board + 1) + 1) == 0 && inGame)
	{
		(*(buttons + 4))->SetBitmap(x);
		*(*(board + 1) + 1) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked6(wxCommandEvent& event)
{
	if (*(*(board + 1) + 2) == 0 && inGame)
	{
		(*(buttons + 5))->SetBitmap(x);
		*(*(board + 1) + 2) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked7(wxCommandEvent& event)
{
	if (*(*(board + 2)) == 0 && inGame)
	{
		(*(buttons + 6))->SetBitmap(x);
		*(*(board + 2)) = 1;
		PlayGame();
	}
}
void TicTacToe::TicTacToe::OnButtonClicked8(wxCommandEvent& event)
{
	if (*(*(board + 2) + 1) == 0 && inGame)
	{
		(*(buttons + 7))->SetBitmap(x);
		*(*(board + 2) + 1) = 1;
		PlayGame();
	}
}
void TicTacToe::OnButtonClicked9(wxCommandEvent& event)
{
	if (*(*(board + 2) + 2) == 0 && inGame)
	{
		(*(buttons + 8))->SetBitmap(x);
		*(*(board + 2) + 2) = 1;
		PlayGame();
	}
}
void TicTacToe::Reset(wxCommandEvent& event)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			*(*(board + i) + j) = 0;

	inGame = true;
	round_number = 0;
	WinInfo->SetLabel("     ");
	*(counter_text + strlen(counter_text) - 1) = '0';
	counterText->SetLabel(counter_text);

	for (int i = 0; i < 9; ++i) {
		(*(buttons + i))->SetBitmap(empty);
	}

	panel->SetFocus();
}
void TicTacToe::Exit(wxCommandEvent& event)
{
	Close();
}

void TicTacToe::PlayGame()
{
	*(counter_text + strlen(counter_text) - 1) = (char)(round_number + '1');
	counterText->SetLabel(counter_text);

	if (round_number < 4) {
		srand(time(NULL));
		round_number++;

		int choiceX = 0;
		int choiceY = 0;


		if (is_win() > 0) {
			inGame = false;
			WinInfo->SetPosition(wxPoint(600, 300));
			player_score++;
			scoreTextPlayer->SetLabel("Player score: " + to_string(player_score));
			WinInfo->SetForegroundColour(wxColor(0, 200, 0));
			WinInfo->SetLabel("Player won!");
			return;
		}


		while (1) {
			choiceX = rand() % 3;
			choiceY = rand() % 3;
			if (*(*(board + choiceY) + choiceX) == 0)
				break;
		}

		*(*(board + choiceY) + choiceX) = 2;

		(*(buttons + choiceY * 3 + choiceX))->SetBitmap(circle);

		if (is_win() > 0) {
			inGame = false;
			WinInfo->SetForegroundColour(wxColor(255, 51, 51));
			bot_score++;
			scoreTextBot->SetLabel("Bot score: " + to_string(bot_score));
			WinInfo->SetPosition(wxPoint(620, 300));
			WinInfo->SetLabel("Bot won!");
			return;
		}
	}
	else
	{
		inGame = false;

		if (is_win() == 1) {
			player_score++;
			scoreTextPlayer->SetLabel("Player score: " + to_string(player_score));
			WinInfo->SetPosition(wxPoint(600, 300));
			WinInfo->SetForegroundColour(wxColor(0, 200, 0));
			WinInfo->SetLabel("Player won!");
		}
		else if (is_win() == 2) {
			bot_score++;
			scoreTextBot->SetLabel("Bot score: " + to_string(bot_score));
			WinInfo->SetForegroundColour(wxColor(255, 51, 51));
			WinInfo->SetPosition(wxPoint(620, 300));
			WinInfo->SetLabel("Bot won!");
		}
		else {
			WinInfo->SetForegroundColour(wxColor(255, 204, 0));
			WinInfo->SetPosition(wxPoint(640, 300));
			WinInfo->SetLabel("Draw!");
		}
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

	return 0;
}

void TicTacToe::free_memory()
{
	delete WinInfo;
	delete scoreTextPlayer;
	delete scoreTextBot;
	delete counterText;
	delete nicknameText;
	delete resetButton;
	delete exitButton;
	
	for (int i = 0; i < 4; ++i)
		delete tictactoe_board[i];
	delete[] tictactoe_board;

	for (int i = 0; i < 9; ++i)
		delete buttons[i];
	delete[] buttons;

	delete panel;
}