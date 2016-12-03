#ifndef MainH
#define MainH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Dialogs.hpp>

#include "Graph.h"
#include "NewMaterial.h"
#include "Grafic.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.EngExt.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.FileCtrl.hpp>
#include <StrUtils.hpp>
// #include <Vcl.Bind.DBEngExt.hpp>
// #include <Vcl.Bind.Editors.hpp>

extern bool NoAnim;

void NewMat();
void draw();

/* Перенесена в другой файл!
 struct TMaterial
 {
 long double G;//модуль Юнга
 long double ro0;
 long double sigma0;
 long double k;
 long double alpha;
 long double sigma1;
 long double k1;

 //температура
 long double ctep, gammatep;

 char Name[ 30 ];
 int Color;
 }; */

class TmainForm : public TForm {
__published: // IDE-managed Components

	TEdit *alfEdit;
	TLabel *Label1;
	TEdit *c0Edit;
	TEdit *clEdit;
	TEdit *caEdit;
	TEdit *tEdit;
	TEdit *dtimeprEdit;
	TEdit *vindentEdit;
	TEdit *h0Edit;
	TEdit *n1Edit;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label7;
	TLabel *Label9;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label6;
	TButton *Refresh;
	TCheckBox *CheckBox1;
	TComboBox *jjjjBox;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label14;
	TEdit *rad0Edit;
	TEdit *rad1Edit;
	TEdit *n3Edit;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TBevel *Bevel5;
	TComboBox *matstrat0Box;
	TBevel *Bevel6;
	TComboBox *nstratBox;
	TEdit *h2iEdit1;
	TEdit *h2iEdit2;
	TEdit *h2iEdit3;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TComboBox *matstrat1Box;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TComboBox *matstrat2Box;
	TComboBox *matstrat3Box;
	TBevel *Bevel7;
	TButton *Button1;
	TBevel *Bevel8;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label8;
	TEdit *ntEdit;
	TCheckBox *CheckBoxn;
	TCheckBox *CheckBoxb;
	TCheckBox *CheckBoxs;
	TLabel *Label25;
	TEdit *Editb;
	TLabel *Label26;
	TEdit *Edits;
	TCheckBox *CheckBoxns;
	TCheckBox *CheckBoxbs;
	TCheckBox *CheckBoxn2;
	TCheckBox *CheckBoxb2;
	TLabel *Label27;
	TLabel *Label28;
	TEdit *Editn2;
	TEdit *Editb2;
	TCheckBox *CheckBoxno2;
	TCheckBox *CheckBoxnp1;
	TCheckBox *CheckBoxnp2;
	TCheckBox *CheckBoxnp3;
	TBevel *Bevel9;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBoxinss;
	TLabel *Label31;
	TEdit *Editinss;
	TRadioGroup *RadioGroup1;
	TLabel *Label32;
	TEdit *Editbsh;
	TCheckBox *CheckBoxbsh;
	TCheckBox *CheckBoxStakan;
	TLabel *Label29;
	TComboBox *ComboBoxBuild;
	TBevel *Bevel11;
	TBevel *Bevel10;
	TStaticText *StaticText1;
	TCheckBox *BeautyCBox;
	TBevel *Bevel12;
	TCheckBox *CheckBox2;
	TEdit *Edit1;
	TBindingsList *BindingsList1;
	TLinkControlToProperty *LinkControlToPropertyEnabled;
	TSpinEdit *InputEdit1;
	TLabel *Label30;
	TCheckBox *AltInpCBox;
	TCheckBox *CheckBox5;
	TButton *Button4;
	TEdit *DirEdit;
	TCheckBox *CinemaCBox;
	TSpinEdit *CinemaEdit;
	TCheckBox *BWCBox;
	TButton *LineButton;
	TCheckBox *CBoxPoints;

	void __fastcall RefreshClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall jjjjBoxChange(TObject *Sender);
	void __fastcall nstratBoxChange(TObject *Sender);
	void __fastcall GetBeginValue();
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall CheckBoxinssClick(TObject *Sender);
	void __fastcall CheckBoxbshClick(TObject *Sender);
	void __fastcall CheckBoxbClick(TObject *Sender);
	void __fastcall CheckBoxbsClick(TObject *Sender);
	void __fastcall CheckBoxb2Click(TObject *Sender);
	void __fastcall CheckBoxnClick(TObject *Sender);
	void __fastcall CheckBoxnsClick(TObject *Sender);
	void __fastcall CheckBoxn2Click(TObject *Sender);
	void __fastcall CheckBoxno2Click(TObject *Sender);
	void __fastcall CheckBoxnp1Click(TObject *Sender);
	void __fastcall CheckBoxnp2Click(TObject *Sender);
	void __fastcall CheckBoxnp3Click(TObject *Sender);
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall CheckBoxStakanClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall ntEditChange(TObject *Sender);
	void __fastcall LineButtonClick(TObject *Sender);

private: // User declarations
	void __fastcall BaseLoop(TObject *Sender, int k);
	void __fastcall InitLoop(TObject *Sender, int k);
	void __fastcall SquareLoop(TObject *Sender, int k);
	void __fastcall squareall();
	void __fastcall threegraphs(bool save, int i, bool cinema, UnicodeString path);

public: // User declarations
	__fastcall TmainForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
// ---------------------------------------------------------------------------
#endif
