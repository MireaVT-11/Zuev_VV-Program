// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MatEdit.pas' rev: 28.00 (Windows)

#ifndef MateditHPP
#define MateditHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <System.Generics.Collections.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Matedit
{
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
	System::AnsiString Name;
	int Color;
};


class DELPHICLASS TForm1;
class PASCALIMPLEMENTATION TForm1 : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
private:
	typedef System::DynamicArray<TMaterial> _TForm1__1;
	
	
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
	Vcl::Extctrls::TLabeledEdit* LabeledEdit6;
	Vcl::Extctrls::TLabeledEdit* LabeledEdit7;
	Vcl::Extctrls::TLabeledEdit* LabeledEdit8;
	Vcl::Extctrls::TLabeledEdit* LabeledEdit9;
	Vcl::Extctrls::TLabeledEdit* LabeledEdit10;
	Vcl::Stdctrls::TButton* Button1;
	void __fastcall ColorListBox1Click(System::TObject* Sender);
	void __fastcall ComboBox1Change(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall LabeledEdit2Change(System::TObject* Sender);
	
public:
	_TForm1__1 matarr;
	void __fastcall SetLen(int n);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TForm1(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TForm1(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TForm1(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TForm1(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TForm1* Form1;
}	/* namespace Matedit */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MATEDIT)
using namespace Matedit;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MateditHPP
