#include <wx/wx.h>
#include "MainFrame.h"
#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit(){
	MainFrame* mainFrame = new MainFrame("Mini Games");
	mainFrame->SetClientSize(900, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
