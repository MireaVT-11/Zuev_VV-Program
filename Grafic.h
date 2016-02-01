//---------------------------------------------------------------------------

#ifndef GraficH
#define GraficH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <VclTee.Series.hpp>
#include <VclTee.TeeFunci.hpp>
#include <VclTee.TeEngine.hpp>
#include <VclTee.TeeProcs.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.Chart.hpp>

#include <vector>

using namespace std;

//---------------------------------------------------------------------------
extern const int numSeries;

class TgraficForm : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
		
		// (2015 год) Массивы? Неее, не слышали.
		TLineSeries *Series1;
        TLineSeries *Series2;
        TLineSeries *Series3;
        TLineSeries *Series4;
        TLineSeries *Series5;
        TLineSeries *Series6;
        TLineSeries *Series7;
        TLineSeries *Series8;
        TLineSeries *Series9;
        TLineSeries *Series10;
        TLineSeries *Series11;
		
        TCheckBox *CheckBox1;
		
		TComboBox *ComboBox1;
        TComboBox *ComboBox2;
		
        TLabel *Label1;
        TLabel *Label2;
		
        TBitBtn *BitBtn1;
        TButton *Button1;
		
        TPrintDialog *PrintDialog1;
		TSavePictureDialog *SavePictureDialog1;
		
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
		void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
		
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
		
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Chart1DblClick(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);

        void __fastcall CSpinEdit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
		__fastcall TgraficForm(TComponent* Owner);
		vector< TLineSeries* > Series;
};
//---------------------------------------------------------------------------
extern PACKAGE TgraficForm *graficForm;
//---------------------------------------------------------------------------
#endif
