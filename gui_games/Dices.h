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

class Dices : public wxFrame
{
public:
	Dices(const wxString& title, string nick);
	~Dices();
	string nickname;
};