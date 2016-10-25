// ---------------------------------------------------------------------------
#pragma hdrstop

#include "Main.h"
#include "Save.h"
#include "Grafic.h"
// ---------------------------------------------------------------------------

const int iLoveMagic = 100;

// (2015 год) extern нужен, так как константы по умолчанию являются...
// (2015 год) ...локальными переменными для единицы компиляции
extern const int numSeries = 11;

#pragma package(smart_init)
#pragma resource "*.dfm"
TgraficForm *graficForm;

// ---------------------------------------------------------------------------
__fastcall TgraficForm::TgraficForm(TComponent* Owner) : TForm(Owner) {
	Series.reserve(numSeries);
	Series.push_back(Series1);
	Series.push_back(Series2);
	Series.push_back(Series3);
	Series.push_back(Series4);
	Series.push_back(Series5);
	Series.push_back(Series6);
	Series.push_back(Series7);
	Series.push_back(Series8);
	Series.push_back(Series9);
	Series.push_back(Series10);
	Series.push_back(Series11);
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::FormClose(TObject *, TCloseAction &) {
	NoAnim = false;
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::FormShow(TObject *) {
	// (2015 год) Какаята ненужная фигня (особенно после удаления Form3 (ProgressUnit)
	// this->Left = FormMain->Left+0.5*FormMain->Width-0.5*this->Width;
	// this->Top = FormMain->Top+0.5*FormMain->Height-0.5*this->Height;
	// this->Visible = true;
	// this->RefreshClick( this );
	Chart1->Title->Text->Clear(); // (Ales'hon'ne) Вот это - нужная фигня
	Chart1->Title->Text->Add(ComboBox1->Text + " (" + ComboBox2->Text + ")"); // (Ales'hon'ne) И это - оже
	// this->Visible = false;
	// Cursor = crDefault;
	draw();
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::ComboBox1Change(TObject *) {
	draw();
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::ComboBox2Change(TObject *) {
	draw();
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::BitBtn1Click(TObject *) {
	if (PrintDialog1->Execute())
		Chart1->Print();
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::Button1Click(TObject *) {
	// this->ShowModal();
	if (SavePictureDialog1->Execute()) {
		Chart1->SaveToBitmapFile(SavePictureDialog1->FileName);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::FormCreate(TObject *) {
	Chart1->PrintProportional = true;
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::FormResize(TObject *) {
	Chart1->Width = graficForm->ClientWidth;
	Chart1->Height = graficForm->ClientHeight - iLoveMagic;
}
// ---------------------------------------------------------------------------

void __fastcall TgraficForm::Chart1DblClick(TObject *) {
	Chart1->UndoZoom();
}
// ---------------------------------------------------------------------------

// "Во весь экран" ткнули. Ещё не сделанная функция // (2015 год) До сих пор ещё не сделанная...
void __fastcall TgraficForm::CheckBox1Click(TObject *) {
	draw();
}
// ---------------------------------------------------------------------------

// СпинЭдит, которого нет // (2015 год) И которого наверное не будет...
void __fastcall TgraficForm::CSpinEdit1Change(TObject *) {
	draw();
}
// ---------------------------------------------------------------------------
