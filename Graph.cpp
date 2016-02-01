// ---------------------------------------------------------------------------
#pragma hdrstop

#include "Graph.h"
// ---------------------------------------------------------------------------

const double iLoveMagic = 4;

#pragma package(smart_init)
#pragma resource "*.dfm"
TgraphForm *graphForm;

// ---------------------------------------------------------------------------
__fastcall TgraphForm::TgraphForm(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TgraphForm::FormKeyDown(TObject *, WORD &, TShiftState) {
	if (graphForm->WindowState == wsMaximized) {
		//graphForm->ClientWidth = Screen->Width / iLoveMagic;
		//graphForm->ClientHeight = Screen->Height / iLoveMagic;

		graphForm->BorderStyle = bsSizeToolWin;
		graphForm->WindowState = wsNormal;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TgraphForm::FormClose(TObject *, TCloseAction &) {
	Application->Terminate();
}
// ---------------------------------------------------------------------------
