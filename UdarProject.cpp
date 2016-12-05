// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
// ---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORMNS("MatEdit.pas", Matedit, Form1);
USEFORM("Graph.cpp", graphForm);
USEFORM("Main.cpp", mainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	try {
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Turquoise Gray");
		Application->CreateForm(__classid(TmainForm), &mainForm);
		Application->CreateForm(__classid(TgraphForm), &graphForm);
		Application->Run();
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception
				("Unknow error! If you see it, please, contact to Zuev V. V., PhD-H of Math. from Russia");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
