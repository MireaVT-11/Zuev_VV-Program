//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Save.cpp", saveForm);
USEFORM("NewMaterial.cpp", newMaterialForm);
USEFORM("Graph.cpp", graphForm);
USEFORM("Grafic.cpp", graficForm);
USEFORM("Main.cpp", mainForm);
USEFORMNS("MatEdit.pas", Matedit, Form1);
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TmainForm), &mainForm);
		TStyleManager::TrySetStyle("Turquoise Gray");
		Application->CreateForm(__classid(TgraphForm), &graphForm);
		Application->CreateForm(__classid(TgraficForm), &graficForm);
		Application->CreateForm(__classid(TnewMaterialForm), &newMaterialForm);
		Application->CreateForm(__classid(TsaveForm), &saveForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("Unknow error! If you see it, please, "
				"contact to Zuev V. V., PhD-H of Math. from Russia");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
