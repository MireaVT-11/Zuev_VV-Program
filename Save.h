//---------------------------------------------------------------------------
#ifndef SaveH
#define SaveH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TsaveForm : public TForm
{
__published:	// IDE-managed Components
		TLabel *Label1;
		TLabel *Label2;

		TButton *Button1;

		TSavePictureDialog *SavePictureDialog1;

		TEdit *Edit1;
		TEdit *Edit2;

        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TsaveForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TsaveForm *saveForm;
//---------------------------------------------------------------------------
#endif
