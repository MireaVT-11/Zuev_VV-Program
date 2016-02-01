//---------------------------------------------------------------------------

#ifndef NewMaterialH
#define NewMaterialH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TnewMaterialForm : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
		
        TEdit *NameEdit;
        TEdit *densEdit;
        TEdit *GEdit;
        TEdit *sigma0Edit;
        TEdit *kEdit;
        TEdit *sigma1Edit;
        TEdit *alphaEdit;
		
		// (2015 год) Массивы? Неее, не слышали.
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TPanel *Panel1;
		
        TColorDialog *ColorDialog1;
		
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Panel1Click(TObject *Sender);
		
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TnewMaterialForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TnewMaterialForm *newMaterialForm;
//---------------------------------------------------------------------------
#endif
