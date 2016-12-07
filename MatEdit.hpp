// CodeGear C++Builder
// Copyright (c) 1995, 2016 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MatEdit.pas' rev: 31.00 (Windows)

#ifndef MateditHPP
#define MateditHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Generics.Collections.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.adomxmldom.hpp>
#include <Vcl.Buttons.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Matedit
{
//-- forward type declarations -----------------------------------------------
struct TMaterial;
class DELPHICLASS TForm1;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TMaterial
{
public:
	System::Extended G;
	System::Extended ro0;
	System::Extended sigma0;
	System::Extended k;
	System::Extended alpha;
	System::Extended sigma1;
	System::Extended k1;
	System::Extended ctep;
	System::Extended gammatep;
	System::UnicodeString Name;
	int Color;
	System::UnicodeString __fastcall ToString(void);
};


class PASCALIMPLEMENTATION TForm1 : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TColorListBox* ColorListBox1;
	Vcl::Extctrls::TLabeledEdit* LabeledEdit2;
	Vcl::Stdctrls::TComboBox* ComboBox1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Extctrls::TShape* Shape1;
	Vcl::Extctrls::TLabeledEdit* GEdit;
	Vcl::Extctrls::TLabeledEdit* ro0Edit;
	Vcl::Extctrls::TLabeledEdit* sigma0Edit;
	Vcl::Extctrls::TLabeledEdit* sigma1Edit;
	Vcl::Extctrls::TLabeledEdit* kEdit;
	Vcl::Extctrls::TLabeledEdit* k1Edit;
	Vcl::Extctrls::TLabeledEdit* gammatepEdit;
	Vcl::Extctrls::TLabeledEdit* ctepEdit;
	Vcl::Extctrls::TLabeledEdit* alphaEdit;
	Vcl::Stdctrls::TButton* Button1;
	Xml::Xmldoc::TXMLDocument* MatDB;
	Vcl::Buttons::TSpeedButton* SpeedButton1;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Buttons::TSpeedButton* SpeedButton2;
	void __fastcall ColorListBox1Click(System::TObject* Sender);
	void __fastcall ComboBox1Change(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall LabeledEdit2Change(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall SpeedButton2Click(System::TObject* Sender);
	
private:
	System::Generics::Collections::TList__1<TMaterial>* MaterialList;
	
public:
	System::TArray__1<TMaterial> matarr;
	void __fastcall ReadFromFile(System::UnicodeString path);
	void __fastcall ReinitList(void);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TForm1(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TForm1(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TForm1(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TForm1(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TForm1* Form1;
extern DELPHI_PACKAGE System::UnicodeString __fastcall C2T(System::Uitypes::TColor cl);
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall T2C(System::UnicodeString s);
}	/* namespace Matedit */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MATEDIT)
using namespace Matedit;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MateditHPP
