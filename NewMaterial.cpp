// ---------------------------------------------------------------------------
#pragma hdrstop

#include <cstdlib>
#include <ctime>

#include "NewMaterial.h"
#include "Main.h"

using namespace std; // (2015 год) Временный кАстыль
// ---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TnewMaterialForm *newMaterialForm;

const int iLoveMagic = 255;

// ---------------------------------------------------------------------------
__fastcall TnewMaterialForm::TnewMaterialForm(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TnewMaterialForm::Button1Click(TObject *) {
	NewMat();
}

// ---------------------------------------------------------------------------
void __fastcall TnewMaterialForm::Panel1Click(TObject *) {
	if (ColorDialog1->Execute()) {
		Panel1->Color = ColorDialog1->Color;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TnewMaterialForm::FormShow(TObject *) {
	srand(time(NULL));
	Panel1->Color = static_cast<TColor>(RGB(random(iLoveMagic), random(iLoveMagic), random(iLoveMagic)));
}
// ---------------------------------------------------------------------------
