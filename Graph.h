// ---------------------------------------------------------------------------

#ifndef GraphH
#define GraphH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

// ---------------------------------------------------------------------------
class TgraphForm : public TForm {
__published: // IDE-managed Components
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private: // User declarations
		public : // User declarations
	__fastcall TgraphForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TgraphForm *graphForm;
// ---------------------------------------------------------------------------
#endif
