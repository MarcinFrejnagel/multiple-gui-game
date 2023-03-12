#include "Dices.h"

Dices::Dices(const wxString& title, string nick) : wxFrame(nullptr, wxID_ANY, title)
{
    // Tworzenie obiektu wxPanel
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 600));
    panel->SetBackgroundColour(wxColor(80, 80, 150));

    // Tworzenie obiektu wxGrid
    wxGrid* grid = new wxGrid(panel, wxID_ANY, wxPoint(100, 50));

    // Ustawianie liczb wierszy i kolumn
    grid->CreateGrid(14, 2);

    grid->SetColLabelValue(0, nick);
    grid->SetColLabelValue(1, "Bot");

    grid->SetCellValue(0, 0, "one");
    grid->SetCellValue(0, 1, "two");
    grid->SetCellValue(1, 0, "three");
    grid->SetCellValue(1, 1, "four");
    grid->SetCellValue(2, 0, "five");
    grid->SetCellValue(2, 1, "six");
    grid->SetCellValue(3, 0, "seven");
    grid->SetCellValue(3, 1, "eight");

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

    //rozmiar wiersza
    for(int i = 0; i < 14; i++)
        grid->SetRowSize(i, 30);

    //cale pole tabeli
    grid->SetSize(wxSize(240, 450));

    //grid->SetDefaultCellBackgroundColour(wxColour(0, 0, 255));
    //grid->SetLabelBackgroundColour(wxColour(255, 0, 0));

    //grid->SetGridFrozenBorderColour(wxColor(150, 150, 150));

    // Ustawianie edycji wierszy

    
    grid->EnableEditing(false);
    grid->EnableDragColSize(false);
    grid->EnableDragRowSize(false);
    grid->EnableDragGridSize(false);
    grid->EnableCellEditControl(false);
    grid->EnableScrolling(false, false);
    grid->SetScrollbars(1, 1, 0, 0, 0, 0);
    
}

Dices::~Dices()
{

}