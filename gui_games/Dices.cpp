#include "Dices.h"

wxBEGIN_EVENT_TABLE(Dices, wxFrame)
EVT_BUTTON(buttonThrowID, Dices::throwDices)
EVT_BUTTON(buttonExitID, Dices::exit)
EVT_BUTTON(buttonSaveID, Dices::savePoints)
EVT_BUTTON(buttonRestartID, Dices::reset)
wxEND_EVENT_TABLE()

Dices::Dices(const wxString& title, string nick) : wxFrame(nullptr, wxID_ANY, title)
{
    srand(time(NULL));
    roundNumber = 0;
    throwCounter = 0;
    nickname = nick;
    botPlaying = false;

    try
    {
        panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    panel->SetBackgroundColour(wxColor(147, 112, 219));

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 14; ++j)
            *(*(scores + i) + j) = 0;


    createButtons();
    setGrid();
    loadBitmaps();
    createText();
}

void Dices::createText()
{
    wxFont fontInfo(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD);
    wxFont fontText(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxColor backgroundColor(147, 112, 219);

    try
    {
        winInfo = new wxStaticText(this, wxID_ANY, " ", wxPoint(407, 220), wxSize(50, 10));
        throwCounterInfo = new wxStaticText(this, wxID_ANY, "Throws left: 3", wxPoint(550, 330), wxSize(50, 10));
        pointsInfo = new wxStaticText(this, wxID_ANY, "Points: " + to_string(getPoints()), wxPoint(550, 370), wxSize(50, 10));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    winInfo->SetFont(fontInfo);
    winInfo->SetBackgroundColour(wxColor(147, 112, 219));

    throwCounterInfo->SetFont(fontText);
    throwCounterInfo->SetBackgroundColour(backgroundColor);

    pointsInfo->SetFont(fontText);
    pointsInfo->SetBackgroundColour(backgroundColor);
}

void Dices::createButtons()
{
    try
    {
        buttonThrow = new wxButton(panel, buttonThrowID, "Throw", wxPoint(400, 450), wxSize(90, 50));
        buttonSave = new wxButton(panel, buttonSaveID, "Save", wxPoint(510, 450), wxSize(90, 50));
        buttonRestart = new wxButton(panel, buttonRestartID, "Reset", wxPoint(620, 450), wxSize(90, 50));
        buttonExit = new wxButton(panel, buttonExitID, "Exit", wxPoint(730, 450), wxSize(90, 50));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    wxFont fontButton(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxColor color2(0, 200, 0), color3(135, 206, 235);

    buttonThrow->SetFont(fontButton);
    buttonThrow->SetBackgroundColour(color3);

    buttonSave->SetFont(fontButton);
    buttonSave->SetBackgroundColour(color3);

    buttonRestart->SetFont(fontButton);
    buttonRestart->SetBackgroundColour(color3);

    buttonExit->SetFont(fontButton);
    buttonExit->SetBackgroundColour(color3);

    buttonThrow->SetCursor(wxCursor(wxCURSOR_HAND));
    buttonSave->SetCursor(wxCursor(wxCURSOR_HAND));
    buttonRestart->SetCursor(wxCursor(wxCURSOR_HAND));
    buttonExit->SetCursor(wxCursor(wxCURSOR_HAND));
}

Dices::~Dices()
{
    delete buttonThrow;
    delete buttonSave;
    delete buttonRestart;
    delete buttonExit;
    delete grid;
    delete winInfo;
    delete throwCounterInfo;
    delete pointsInfo;

    for (int i = 0; i < 5; ++i)
        delete dices[i];
    delete[] dices;

    delete panel;

    wxLogStatus("Menu");
}

void Dices::setGrid()
{
    try
    {
        grid = new wxGrid(panel, wxID_ANY, wxPoint(100, 50));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    grid->CreateGrid(14, 2);

    grid->SetColLabelValue(0, nickname);
    grid->SetColLabelValue(1, "Bot");

    grid->SetRowLabelValue(0, "Ones");
    grid->SetRowLabelValue(1, "Twos");
    grid->SetRowLabelValue(2, "Threes");
    grid->SetRowLabelValue(3, "Fours");
    grid->SetRowLabelValue(4, "Fives");
    grid->SetRowLabelValue(5, "Sixes");
    grid->SetRowLabelValue(6, "3x");
    grid->SetRowLabelValue(7, "4x");
    grid->SetRowLabelValue(8, "3x + 2x");
    grid->SetRowLabelValue(9, "1-5");
    grid->SetRowLabelValue(10, "2-6");
    grid->SetRowLabelValue(11, "5x");
    grid->SetRowLabelValue(12, "Chance");
    grid->SetRowLabelValue(13, "Sum of points");

    grid->SetLabelBackgroundColour(wxColor(245, 222, 179));
    grid->SetBackgroundColour(wxColor(32, 178, 170));
    grid->SetCellBackgroundColour(13, 0, wxColor(50, 205, 50));
    grid->SetCellBackgroundColour(13, 1, wxColor(220, 20, 60));
    grid->SetGridLineColour(wxColour(100, 100, 100));

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 13; ++j)
            grid->SetCellBackgroundColour(j, i, wxColor(255, 255, 204));
    }

    for (int i = 0; i < 14; ++i)
        grid->SetRowSize(i, 30);

    grid->SetSize(wxSize(240, 450));

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 14; ++j)
            grid->SetCellAlignment(j, i, wxALIGN_CENTRE, wxALIGN_CENTRE);
    }


    grid->EnableEditing(false);
    grid->EnableDragColSize(false);
    grid->EnableDragRowSize(false);
    grid->EnableDragGridSize(false);
    grid->EnableCellEditControl(false);
    grid->EnableScrolling(false, false);
    grid->SetScrollbars(1, 1, 0, 0, 0, 0);

    grid->SetCellValue(13, 0, to_string(0));
    grid->SetCellValue(13, 1, to_string(0));
}

void Dices::loadBitmaps()
{
    try
    {
        handler = new wxPNGHandler;
        wxImage::AddHandler(handler);
        dicesBitmaps[0].LoadFile("dice1.png", wxBITMAP_TYPE_PNG);
        dicesBitmaps[1].LoadFile("dice2.png", wxBITMAP_TYPE_PNG);
        dicesBitmaps[2].LoadFile("dice3.png", wxBITMAP_TYPE_PNG);
        dicesBitmaps[3].LoadFile("dice4.png", wxBITMAP_TYPE_PNG);
        dicesBitmaps[4].LoadFile("dice5.png", wxBITMAP_TYPE_PNG);
        dicesBitmaps[5].LoadFile("dice6.png", wxBITMAP_TYPE_PNG);
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    try
    {
        dices = new wxStaticBitmap * [5];

        dices[0] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[0], wxPoint(400, 50), wxSize(120, 120));
        dices[1] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[1], wxPoint(700, 50), wxSize(120, 120));
        dices[2] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[2], wxPoint(400, 290), wxSize(120, 120));
        dices[3] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[3], wxPoint(700, 290), wxSize(120, 120));
        dices[4] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[4], wxPoint(550, 170), wxSize(120, 120));
    }
    catch (exception& e)
    {
        wxMessageBox("Exception caught: " + string(e.what()), " Error");
        Close();
    }

    drawNumber();

}

void Dices::drawNumber()
{
    for (int i = 0; i < 5; ++i)
    {
        diceScore[i] = rand() % 6 + 1;
        dices[i]->SetBitmap(dicesBitmaps[diceScore[i] - 1]);
    }
}

void Dices::throwDices(wxCommandEvent& event)
{
    if (botPlaying == false && roundNumber < 13)
    {

        drawNumber();
        pointsInfo->SetLabel("Points: " + to_string(getPoints()));
        throwCounter++;
        throwCounterInfo->SetLabel("Throws left: " + to_string(3 - throwCounter));
        if (throwCounter == 3)
            savePointsToGrid(0);
    }
}

void Dices::exit(wxCommandEvent& event)
{
    if (botPlaying == false)
    {

        Close();
    }
}

void Dices::savePoints(wxCommandEvent& event)
{
    if (botPlaying == false && roundNumber < 13)
    {
        savePointsToGrid(0);
    }

}

void Dices::savePointsToGrid(int player)
{
    int result = getPoints();

    scores[player][roundNumber] = result;
    scores[player][13] += result;
    grid->SetCellValue(roundNumber, player, to_string(result));
    grid->SetCellValue(13, player, to_string(scores[player][13]));

    wxYield();

    if (player == 0)
    {
        botPlaying = true;
        if (throwCounter == 3)
            Sleep(1500);
        playBot();
        throwCounter = 0;
        throwCounterInfo->SetLabel("Throws left: " + to_string(3 - throwCounter));
    }
    else
    {
        roundNumber++;
    }

    if (roundNumber == 13)
    {
        winner();
    }
}

void Dices::playBot()
{
    int savedPoints = 0;
    for (int i = 0; i < 3; ++i)
    {
        drawNumber();
        Sleep(1000);

        if (getPoints() > 0)
        {
            savedPoints = 1;
            savePointsToGrid(1);
            break;
        }

    }

    if (savedPoints == 0)
    {
        savePointsToGrid(1);
    }

    drawNumber();
    pointsInfo->SetLabel("Points: " + to_string(getPoints()));
    botPlaying = false;
}

int Dices::getPoints()
{
    int result = 0, check = 0;
    int temp_array[6] = { 1, 2, 3, 4, 5, 6 };

    if (roundNumber < 6)
    {
        for (int i = 0; i < 5; ++i)
        {
            if (diceScore[i] == roundNumber + 1)
                result += roundNumber + 1;
        }

    }
    else if (roundNumber == 6)
    {
        result = findTheSameDices(3);

    }
    else if (roundNumber == 1)
    {
        result = findTheSameDices(4);

    }
    else if (roundNumber == 8)
    {
        result = find3x2x();

    }
    else if (roundNumber == 9)
    {
        result = findFromTo(6);

    }
    else if (roundNumber == 10)
    {
        result = findFromTo(1);

    }
    else if (roundNumber == 11)
    {
        result = findTheSameDices(5);

    }
    else if (roundNumber == 12)
    {
        for (int i = 0; i < 5; ++i)
            result += *(diceScore + i);
    }

    return result;
}

int Dices::find3x2x()
{
    int countDices = 0;
    int foundThreeDices = 0;
    int lookForPair = 0;
    int result = 0;

    for (int i = 1; i <= 6; ++i)
    {
        countDices = 0;

        for (int j = 0; j < 5; ++j)
        {
            if (diceScore[j] == i)
                countDices++;
        }

        if (countDices == 3)
        {
            result = 3 * i;
            lookForPair = 1;
            foundThreeDices = i;
            break;
        }
        else if (countDices == 5)
        {
            return 5 * i;
        }
    }

    for (int i = 1; i <= 6 && lookForPair == 1; ++i)
    {
        countDices = 0;

        for (int j = 0; j < 5; ++j)
        {
            if (diceScore[j] == i && diceScore[j] != foundThreeDices)
                countDices++;
        }

        if (countDices == 2)
        {
            return result + (2 * i);
        }
    }

    return 0;
}

int Dices::findTheSameDices(int numberOfDices)
{
    int countDices = 0;

    for (int i = 1; i <= 6; ++i)
    {
        countDices = 0;

        for (int j = 0; j < 5; ++j)
        {
            if (diceScore[j] == i)
                countDices++;
        }

        if (countDices >= numberOfDices)
        {
            return numberOfDices * i;
        }
    }

    return 0;
}

int Dices::findFromTo(int choice)
{
    int check = 0;

    for (int i = 0; i < 5; ++i)
    {
        int number = *(diceScore + i);

        for (int j = 0; j < 5; ++j)
        {
            if (*(diceScore + j) == number && i != j)
                check = 1;
        }
        if (*(diceScore + i) == choice)
            check = 1;

    }
    if (check == 0 && choice == 6)
        return 15;
    else if (check == 0 && choice == 1)
        return 20;

    return 0;
}

void Dices::reset(wxCommandEvent& event)
{
    if (botPlaying == false)
    {
        drawNumber();
        throwCounter = 0;
        roundNumber = 0;

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 14; ++j)
            {
                grid->SetCellValue(j, i, " ");
                *(*(scores + i) + j) = 0;
            }
        }

        grid->SetCellValue(13, 0, to_string(0));
        grid->SetCellValue(13, 1, to_string(0));
        winInfo->SetLabel(" ");
        throwCounterInfo->SetLabel("Throws left: 3");
        pointsInfo->SetLabel("Points: " + to_string(getPoints()));
    }
}

void Dices::winner()
{
    if (scores[0][13] > scores[1][13])
    {
        winInfo->SetForegroundColour(wxColor(0, 255, 60));
        winInfo->SetPosition(wxPoint(407, 220));
        winInfo->SetLabel("Player won!");
    }
    else if (scores[0][13] == scores[1][13])
    {
        winInfo->SetForegroundColour(wxColor(255, 204, 0));
        winInfo->SetPosition(wxPoint(430, 220));
        winInfo->SetLabel("Draw!");
    }
    else
    {
        winInfo->SetForegroundColour(wxColor(220, 20, 60));
        winInfo->SetPosition(wxPoint(415, 220));
        winInfo->SetLabel("Bot won!");
    }
}
