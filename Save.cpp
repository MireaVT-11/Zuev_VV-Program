// ---------------------------------------------------------------------------
#pragma hdrstop

#include "Grafic.h"
#include "Save.h"
// ---------------------------------------------------------------------------

const int iLoveMagic = 116;

#pragma package(smart_init)
#pragma resource "*.dfm"
TsaveForm *saveForm;

// ---------------------------------------------------------------------------
__fastcall TsaveForm::TsaveForm(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TsaveForm::FormCreate(TObject *) {
	// Edit1->MaxValue = Screen->Width;
	// Edit2->MaxValue = Screen->Height-iLoveMagic;
	// (2015 год) Нужно заменить функции борланда на функции С++
	char buf[10];
	itoa(graficForm->Chart1->Width, buf, 10);
	Edit1->Text = buf;
	itoa(graficForm->Chart1->Width, buf, 10);
	Edit2->Text = buf;
}

// ---------------------------------------------------------------------------
void __fastcall TsaveForm::Button1Click(TObject *) {
	if (SavePictureDialog1->Execute()) {
		int oldX = graficForm->ClientWidth;
		int oldY = graficForm->ClientHeight;
		graficForm->Hide();
		graficForm->ClientWidth = Edit1->Text.ToInt();
		graficForm->ClientHeight = Edit2->Text.ToInt() + iLoveMagic;
		graficForm->Chart1->SaveToBitmapFile(SavePictureDialog1->FileName);
		graficForm->ClientWidth = oldX;
		graficForm->ClientHeight = oldY;
		graficForm->Show();
		Close();
	}
}
// ---------------------------------------------------------------------------
