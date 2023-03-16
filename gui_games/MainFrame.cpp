#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ticTacClick, MainFrame::buttonClickedTicTacToe)
EVT_BUTTON(dicesClick, MainFrame::buttonClickedDices)
EVT_BUTTON(nicknameClick, MainFrame::setUserNickname)

wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    try
    {
        panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    createButtons();
    setDesign();
};

MainFrame::~MainFrame()
{
    panel->Destroy();
}

void MainFrame::createButtons()
{
    try
    {
        nickText = new wxStaticText(panel, wxID_ANY, "Set your nickname:", wxPoint(365, 195));
        setNickText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 225), wxSize(200, 30));
        nickButton = new wxButton(panel, nicknameClick, "OK", wxPoint(405, 265), wxSize(90, 50));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }
}

void MainFrame::setDesign()
{
    panel->SetBackgroundColour(wxColor(102, 205, 170));

    wxFont fontNickname(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    nickText->SetFont(fontNickname);
    setNickText->SetFont(fontNickname);

    nickButton->SetCursor(wxCursor(wxCURSOR_HAND));
    nickButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    nickButton->SetBackgroundColour(wxColour(100, 250, 100));
}

void MainFrame::setUserNickname(wxCommandEvent& event)
{
    nickname = setNickText->GetValue().ToStdString();
    panel->Destroy();

    try
    {
        panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    panel->SetBackgroundColour(wxColor(102, 153, 204));

    try
    {
        handler = new wxPNGHandler;
        wxImage::AddHandler(handler);

        wxBitmap ticIMG, dicesIMG;
        ticIMG.LoadFile("tictactoe.png", wxBITMAP_TYPE_PNG);
        dicesIMG.LoadFile("dices.png", wxBITMAP_TYPE_PNG);
        ticTacToeButton = new wxBitmapButton(panel, ticTacClick, ticIMG, wxPoint(50, 64), wxSize(350, 450), 0);
        dicesButton = new wxBitmapButton(panel, dicesClick, dicesIMG, wxPoint(500, 64), wxSize(350, 450), 0);
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    ticTacToeButton->SetBackgroundColour(wxColor(102, 153, 204));
    dicesButton->SetBackgroundColour(wxColor(102, 153, 204));

    ticTacToeButton->SetCursor(wxCursor(wxCURSOR_HAND));
    dicesButton->SetCursor(wxCursor(wxCURSOR_HAND));

    CreateStatusBar();

    wxLogStatus("Menu");
}

void MainFrame::buttonClickedTicTacToe(wxCommandEvent& event)
{
    try
    {
        TicTacToe* tictactoe = new TicTacToe("TicTacToe", nickname);
        tictactoe->SetClientSize(900, 600);
        tictactoe->Center();
        tictactoe->Show();
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }
}

void MainFrame::buttonClickedDices(wxCommandEvent& event)
{
    try
    {
        Dices* dices = new Dices("Dices", nickname);
        dices->SetClientSize(900, 600);
        dices->Center();
        dices->Show();
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }
}