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
EVT_BUTTON(Button_board_1, TicTacToe::buttonClicked1)
EVT_BUTTON(Button_board_2, TicTacToe::buttonClicked2)
EVT_BUTTON(Button_board_3, TicTacToe::buttonClicked3)
EVT_BUTTON(Button_board_4, TicTacToe::buttonClicked4)
EVT_BUTTON(Button_board_5, TicTacToe::buttonClicked5)
EVT_BUTTON(Button_board_6, TicTacToe::buttonClicked6)
EVT_BUTTON(Button_board_7, TicTacToe::buttonClicked7)
EVT_BUTTON(Button_board_8, TicTacToe::buttonClicked8)
EVT_BUTTON(Button_board_9, TicTacToe::buttonClicked9)
EVT_BUTTON(Button_reset, TicTacToe::reset)
EVT_BUTTON(Button_exit, TicTacToe::exit)
wxEND_EVENT_TABLE()

TicTacToe::TicTacToe(const wxString& title, string nick) : wxFrame(nullptr, wxID_ANY, title)
{
    nickname = nick;
    panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
    panel->SetBackgroundColour(wxColor(80, 80, 150));
    playerScore = 0;
    botScore = 0;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            *(*(board + i) + j) = 0;

    inGame = true;
    roundNumber = 0;

    create_board();
    create_text();
}

TicTacToe::~TicTacToe()
{
    delete winInfo;
    delete scoreTextPlayer;
    delete scoreTextBot;
    delete counterText;
    delete nicknameText;
    delete resetButton;
    delete exitButton;

    for (int i = 0; i < 4; ++i)
        delete tictactoeBoard[i];
    delete[] tictactoeBoard;

    for (int i = 0; i < 9; ++i)
        delete buttons[i];
    delete[] buttons;

    delete panel;
}

void TicTacToe::create_text()
{
    strcpy(counterOfText, "Number of rounds: 0");

    wxFont fontText(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont fontInfo(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont fontButton(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    wxColor color2(0, 200, 0), color3(229, 204, 255);

    try
    {
        resetButton = new wxButton(panel, Button_reset, "Reset", wxPoint(570, 400), wxSize(90, 50));
        exitButton = new wxButton(panel, Button_exit, "Exit", wxPoint(700, 400), wxSize(90, 50));

        counterText = new wxStaticText(panel, wxID_ANY, counterOfText, wxPoint(550, 140)); // statyczny tekst
        nicknameText = new wxStaticText(panel, wxID_ANY, "Nickname: " + nickname, wxPoint(550, 100)); // statyczny tekst
        scoreTextPlayer = new wxStaticText(panel, wxID_ANY, "Player score: " + to_string(playerScore),
            wxPoint(550, 180));
        scoreTextBot = new wxStaticText(panel, wxID_ANY, "Bot score: " + to_string(botScore), wxPoint(550, 220));
        winInfo = new wxStaticText(panel, wxID_ANY, "     ", wxPoint(600, 300), wxSize(100, 20));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    resetButton->SetCursor(wxCursor(wxCURSOR_HAND));
    exitButton->SetCursor(wxCursor(wxCURSOR_HAND));

    resetButton->SetFont(fontButton);
    resetButton->SetBackgroundColour(color3);

    exitButton->SetFont(fontButton);
    exitButton->SetBackgroundColour(color3);

    counterText->SetFont(fontText);
    counterText->SetForegroundColour(wxColor(200, 200, 200));

    nicknameText->SetFont(fontText);
    nicknameText->SetForegroundColour(wxColor(200, 200, 200));

    winInfo->SetFont(fontInfo);
    winInfo->SetForegroundColour(color2);

    scoreTextPlayer->SetFont(fontText);
    scoreTextPlayer->SetForegroundColour(color2);

    scoreTextBot->SetFont(fontText);
    scoreTextBot->SetForegroundColour(wxColor(255, 51, 51));
}

void TicTacToe::create_board()
{
    try
    {
        handler = new wxPNGHandler;

        tictactoeBoard = new wxStaticBitmap * [4];

        *tictactoeBoard = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg_board.png", wxBITMAP_TYPE_PNG),
            wxPoint(170, 70), wxSize(10, 440));
        *(tictactoeBoard + 1) = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg_board.png", wxBITMAP_TYPE_PNG),
            wxPoint(320, 70), wxSize(10, 440));
        *(tictactoeBoard + 2) = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg2_board.png", wxBITMAP_TYPE_PNG),
            wxPoint(30, 360), wxSize(440, 10));
        *(tictactoeBoard + 3) = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("leg2_board.png", wxBITMAP_TYPE_PNG),
            wxPoint(30, 210), wxSize(440, 10));

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
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    wxImage::AddHandler(handler);

    for (int i = 0; i < 9; ++i)
        (*(buttons + i))->SetCursor(wxCursor(wxCURSOR_HAND));
}

void TicTacToe::buttonClicked1(wxCommandEvent& event)
{
    if (*(*(board)) == 0 && inGame)
    {
        (*(buttons))->SetBitmap(x);
        *(*(board)) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked2(wxCommandEvent& event)
{

    if (*(*(board) + 1) == 0 && inGame)
    {
        (*(buttons + 1))->SetBitmap(x);
        *(*(board) + 1) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked3(wxCommandEvent& event)
{

    if (*(*(board) + 2) == 0 && inGame)
    {
        (*(buttons + 2))->SetBitmap(x);
        *(*(board) + 2) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked4(wxCommandEvent& event)
{

    if (*(*(board + 1)) == 0 && inGame)
    {
        (*(buttons + 3))->SetBitmap(x);
        *(*(board + 1)) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked5(wxCommandEvent& event)
{

    if (*(*(board + 1) + 1) == 0 && inGame)
    {
        (*(buttons + 4))->SetBitmap(x);
        *(*(board + 1) + 1) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked6(wxCommandEvent& event)
{
    if (*(*(board + 1) + 2) == 0 && inGame)
    {
        (*(buttons + 5))->SetBitmap(x);
        *(*(board + 1) + 2) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked7(wxCommandEvent& event)
{
    if (*(*(board + 2)) == 0 && inGame)
    {
        (*(buttons + 6))->SetBitmap(x);
        *(*(board + 2)) = 1;
        playGame();
    }
}

void TicTacToe::TicTacToe::buttonClicked8(wxCommandEvent& event)
{
    if (*(*(board + 2) + 1) == 0 && inGame)
    {
        (*(buttons + 7))->SetBitmap(x);
        *(*(board + 2) + 1) = 1;
        playGame();
    }
}

void TicTacToe::buttonClicked9(wxCommandEvent& event)
{
    if (*(*(board + 2) + 2) == 0 && inGame)
    {
        (*(buttons + 8))->SetBitmap(x);
        *(*(board + 2) + 2) = 1;
        playGame();
    }
}

void TicTacToe::reset(wxCommandEvent& event)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            *(*(board + i) + j) = 0;

    inGame = true;
    roundNumber = 0;
    winInfo->SetLabel("     ");
    *(counterOfText + strlen(counterOfText) - 1) = '0';
    counterText->SetLabel(counterOfText);

    for (int i = 0; i < 9; ++i)
    {
        (*(buttons + i))->SetBitmap(empty);
    }

    panel->SetFocus();
}

void TicTacToe::exit(wxCommandEvent& event)
{
    Close();
}

void TicTacToe::playGame()
{
    *(counterOfText + strlen(counterOfText) - 1) = (char)(roundNumber + '1');
    counterText->SetLabel(counterOfText);

    if (roundNumber < 4)
    {
        srand(time(NULL));
        roundNumber++;

        int choiceX = 0;
        int choiceY = 0;


        if (is_win() > 0)
        {
            inGame = false;
            winInfo->SetPosition(wxPoint(600, 300));
            playerScore++;
            scoreTextPlayer->SetLabel("Player score: " + to_string(playerScore));
            winInfo->SetForegroundColour(wxColor(0, 200, 0));
            winInfo->SetLabel("Player won!");
            return;
        }


        while (1)
        {
            choiceX = rand() % 3;
            choiceY = rand() % 3;
            if (*(*(board + choiceY) + choiceX) == 0)
                break;
        }

        *(*(board + choiceY) + choiceX) = 2;

        (*(buttons + choiceY * 3 + choiceX))->SetBitmap(circle);

        if (is_win() > 0)
        {
            inGame = false;
            winInfo->SetForegroundColour(wxColor(255, 51, 51));
            botScore++;
            scoreTextBot->SetLabel("Bot score: " + to_string(botScore));
            winInfo->SetPosition(wxPoint(620, 300));
            winInfo->SetLabel("Bot won!");
            return;
        }
    }
    else
    {
        inGame = false;

        if (is_win() == 1)
        {
            playerScore++;
            scoreTextPlayer->SetLabel("Player score: " + to_string(playerScore));
            winInfo->SetPosition(wxPoint(600, 300));
            winInfo->SetForegroundColour(wxColor(0, 200, 0));
            winInfo->SetLabel("Player won!");
        }
        else if (is_win() == 2)
        {
            botScore++;
            scoreTextBot->SetLabel("Bot score: " + to_string(botScore));
            winInfo->SetForegroundColour(wxColor(255, 51, 51));
            winInfo->SetPosition(wxPoint(620, 300));
            winInfo->SetLabel("Bot won!");
        }
        else
        {
            winInfo->SetForegroundColour(wxColor(255, 204, 0));
            winInfo->SetPosition(wxPoint(640, 300));
            winInfo->SetLabel("Draw!");
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

        if (*(*(board) + i) == 1 && *(*(board + 1) + i) == 1 && *(*(board + 2) + i) == 1)
        {
            return 1;
        }

        if (*(*(board) + i) == 2 && *(*(board + 1) + i) == 2 && *(*(board + 2) + i) == 2)
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

    if (*(*(board) + 2) == 1 && *(*(board + 1) + 1) == 1 && *(*(board + 2)) == 1)
    {
        return 1;
    }

    if (*(*(board) + 2) == 2 && *(*(board + 1) + 1) == 2 && *(*(board + 2)) == 2)
    {
        return 2;
    }

    return 0;
}
