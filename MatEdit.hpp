﻿// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MatEdit.pas' rev: 30.00 (Windows)

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
	System::AnsiString Name;
	int Color;
};


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
	Vcl::Extctrls::TLabeledEdit* kEdit;
	Vcl::Extctrls::TLabeledEdit* k1Edit;
	Vcl::Extctrls::TLabeledEdit* gammatepEdit;
	Vcl::Extctrls::TLabeledEdit* ctepEdit;
	Vcl::Extctrls::TLabeledEdit* alphaEdit;
	Vcl::Stdctrls::TButton* Button1;
	void __fastcall ColorListBox1Click(System::TObject* Sender);
	void __fastcall ComboBox1Change(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall LabeledEdit2Change(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	
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