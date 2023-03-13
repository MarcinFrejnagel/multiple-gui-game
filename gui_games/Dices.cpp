#include "Dices.h"

enum IDentities
{
    buttonThrowID = 0,
    buttonExitID = 1,
    buttonSaveID = 2,
    buttonRestartID = 3
};

wxBEGIN_EVENT_TABLE(Dices, wxFrame)
EVT_BUTTON(buttonThrowID, Dices::throwDices)
EVT_BUTTON(buttonExitID, Dices::exitDices)
EVT_BUTTON(buttonSaveID, Dices::savePoints)
EVT_BUTTON(buttonRestartID, Dices::restartGame)
wxEND_EVENT_TABLE()

Dices::Dices(const wxString& title, string nick) : wxFrame(nullptr, wxID_ANY, title)
{
    // Tworzenie obiektu wxPanel
    srand(time(NULL));
    roundNumber = 0;
    throwCounter = 0;
    nickname = nick;
    panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
    panel->SetBackgroundColour(wxColor(80, 80, 150));

    buttonThrow = new wxButton(panel, buttonThrowID, "Throw", wxPoint(400, 450), wxSize(90,50));
    buttonSave = new wxButton(panel, buttonSaveID, "buttonSave", wxPoint(510, 450), wxSize(90,50));
    buttonRestart = new wxButton(panel, buttonRestartID, "buttonRestart", wxPoint(620, 450), wxSize(90,50));
    buttonExit = new wxButton(panel, buttonExitID, "buttonExit", wxPoint(730, 450), wxSize(90,50));

    buttonThrow->SetCursor(wxCursor(wxCURSOR_HAND));
    buttonSave->SetCursor(wxCursor(wxCURSOR_HAND));
    buttonRestart->SetCursor(wxCursor(wxCURSOR_HAND));
    buttonExit->SetCursor(wxCursor(wxCURSOR_HAND));

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 14; ++j)
            *(*(scores + i) + j) = 0;

    // Tworzenie obiektu wxGrid
    
    setGrid();
    loadBitmaps();
}

Dices::~Dices()
{

}

void Dices::setGrid()
{
    grid = new wxGrid(panel, wxID_ANY, wxPoint(100, 50));
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

    for(int i = 0; i < 14; i++)
        grid->SetRowSize(i, 30);

    grid->SetSize(wxSize(240, 450));

    //grid->SetDefaultCellBackgroundColour(wxColour(0, 0, 255));
    //grid->SetLabelBackgroundColour(wxColour(255, 0, 0));

    //grid->SetGridFrozenBorderColour(wxColor(150, 150, 150));

    for (int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 14; ++j)
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
    handler = new wxPNGHandler;
    wxImage::AddHandler(handler);

    dicesBitmaps[0].LoadFile("dice1.png", wxBITMAP_TYPE_PNG);
    dicesBitmaps[1].LoadFile("dice2.png", wxBITMAP_TYPE_PNG);
    dicesBitmaps[2].LoadFile("dice3.png", wxBITMAP_TYPE_PNG);
    dicesBitmaps[3].LoadFile("dice4.png", wxBITMAP_TYPE_PNG);
    dicesBitmaps[4].LoadFile("dice5.png", wxBITMAP_TYPE_PNG);
    dicesBitmaps[5].LoadFile("dice6.png", wxBITMAP_TYPE_PNG);

    dices = new wxStaticBitmap * [5];

    dices[0] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[0], wxPoint(400, 50), wxSize(120, 120));
    dices[1] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[1], wxPoint(700, 50), wxSize(120, 120));
    dices[2] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[2], wxPoint(400, 290), wxSize(120, 120));
    dices[3] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[3], wxPoint(700, 290), wxSize(120, 120));
    dices[4] = new wxStaticBitmap(panel, wxID_ANY, dicesBitmaps[4], wxPoint(550, 170), wxSize(120, 120));

    drawNumber();
    
}

void Dices::drawNumber()
{
    for (int i = 0; i < 5; i++) {
        diceScore[i] = rand() % 6 + 1;
        dices[i]->SetBitmap(dicesBitmaps[diceScore[i] - 1]);
    }
}

void Dices::throwDices(wxCommandEvent& event)
{
    if (throwCounter < 3) {
        drawNumber();
        throwCounter++;
    }else{
        savePointsToGrid(0);
        throwCounter = 0;
    }

}

void Dices::exitDices(wxCommandEvent& event)
{
    Close();
}


void Dices::savePoints(wxCommandEvent& event)
{
    savePointsToGrid(0);
    drawNumber();
}

void Dices::savePointsToGrid(int player)
{
    int result = 0, check = 0;
    int temp_array[6] = { 1, 2, 3, 4, 5, 6 };
    
    if(roundNumber < 6){
        for(int i = 0; i < 5; ++i){
            if (diceScore[i] == roundNumber + 1)
                result += roundNumber + 1;
        }

        scores[player][roundNumber] = result;

    }else if(roundNumber == 6 ){
        result = findTheSameDices(3);
        scores[player][roundNumber] = result;
    
    }else if(roundNumber == 7){
        result = findTheSameDices(4);
        scores[player][roundNumber] = result;

    }else if (roundNumber == 8) {
        result = find3x2x();
        scores[player][roundNumber] = result;

    }else if (roundNumber == 9){
        result = findFromTo(6);

    }else if(roundNumber == 10){
        result = findFromTo(1);

    }else if(roundNumber == 11){
        result = findTheSameDices(5);
        scores[player][roundNumber] = result;

    }else if(roundNumber == 12){
        for (int i = 0; i < 5; ++i)
            result += *(diceScore + i);
        
        scores[player][12] = result;
    }

    scores[player][13] += result;
    grid->SetCellValue(roundNumber, player, to_string(result));
    grid->SetCellValue(13, player, to_string(scores[player][13]));
    
    roundNumber++;
    throwCounter = 0;
}

int Dices::find3x2x()
{
    int countDices = 0;
    int foundThreeDices = 0;
    int lookForPair = 0;
    int result = 0;

    for(int i = 1; i <= 6; ++i){
        countDices = 0;

        for(int j = 0; j < 5; ++j){
            if (diceScore[j] == i)
                countDices++;
        }

        if (countDices == 3) {
            result = 3 * i;
            lookForPair = 1;
            foundThreeDices = i;
            break;
        }else if(countDices == 5){
            return 5 * i;
        }
    }

    for(int i = 1; i <= 6 && lookForPair == 1; ++i){
        countDices = 0;

        for(int j = 0; j < 5; ++j){
            if (diceScore[j] == i && diceScore[j] != foundThreeDices)
                countDices++;
        }

        if (countDices == 2) {
            return result + (2 * i);
        }
    }

    return 0;
}

int Dices::findTheSameDices(int numberOfDices)
{
    int countDices = 0;

    for (int i = 1; i <= 6; ++i){
        countDices = 0;

        for(int j = 0; j < 5; ++j){
            if (diceScore[j] == i)
                countDices++;
        }

        if (countDices >= numberOfDices) {
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

void Dices::restartGame(wxCommandEvent& event)
{
    drawNumber();
    throwCounter = 0;
    roundNumber = 0;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 14; ++j) {
            grid->SetCellValue(j, i, " ");
            *(*(scores + i) + j) = 0;
        }
    }

    grid->SetCellValue(13, 0, to_string(0));
    grid->SetCellValue(13, 1, to_string(0));

}

