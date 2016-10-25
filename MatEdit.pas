unit MatEdit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  System.Generics.Collections, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls;

type
  TMaterial = record
    G, ro0, sigma0, k, alpha, sigma1, k1, ctep, gammatep: Extended;
    Name: ansistring;
    Color: Integer;
  end;

  TForm1 = class(TForm)
    ColorListBox1: TColorListBox;
    LabeledEdit2: TLabeledEdit;
    ComboBox1: TComboBox;
    Label1: TLabel;
    Shape1: TShape;
    GEdit: TLabeledEdit;
    ro0Edit: TLabeledEdit;
    sigma0Edit: TLabeledEdit;
    sigma1Edit: TLabeledEdit;
    kEdit: TLabeledEdit;
    k1Edit: TLabeledEdit;
    gammatepEdit: TLabeledEdit;
    ctepEdit: TLabeledEdit;
    alphaEdit: TLabeledEdit;
    Button1: TButton;
    procedure ColorListBox1Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure LabeledEdit2Change(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    matarr: array of TMaterial;
    procedure SetLen(n: Integer);
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

function C2T(cl: TColor): string;
var
  c: Integer;
  rgb: array [0 .. 3] of byte absolute c;
begin
  c := ColorToRGB(cl);
  Result := Format('%.2x%.2x%.2x', [rgb[0], rgb[1], rgb[2]]);
end;

function T2C(s: string): TColor;
var
  c: Integer;
  rgb: array [0 .. 3] of byte absolute c;
begin
  if not TryStrToInt('$' + s, c) then
    Exit(0);
  Result := rgb[0] shl 16 + rgb[1] shl 8 + rgb[2];
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  i: Integer;
begin
  i := ComboBox1.ItemIndex;
  matarr[i].G := StrToFloat(GEdit.Text) * 1E9;
  matarr[i].ro0 := StrToFloat(ro0Edit.Text);
  matarr[i].sigma0 := StrToFloat(sigma0Edit.Text) * 1E9;
  matarr[i].k := StrToFloat(kEdit.Text) * 1E9;
  matarr[i].alpha := StrToFloat(alphaEdit.Text) * 1E9;
  matarr[i].sigma1 := StrToFloat(sigma1Edit.Text) * 1E9;
  matarr[i].k1 := StrToFloat(k1Edit.Text);
  matarr[i].ctep := StrToFloat(ctepEdit.Text);
  matarr[i].gammatep := StrToFloat(gammatepEdit.Text);
  matarr[i].Color := T2C(LabeledEdit2.Text);
  ComboBox1Change(self);
end;

procedure TForm1.ColorListBox1Click(Sender: TObject);
begin
  LabeledEdit2.Text := C2T(ColorListBox1.Colors[ColorListBox1.ItemIndex]);
end;

procedure TForm1.ComboBox1Change(Sender: TObject);
var
  t: TMaterial;
begin
  t := matarr[ComboBox1.ItemIndex];
  LabeledEdit2.Text := C2T(t.Color);
  GEdit.Text := FloatToStr(t.G / 1E9);
  ro0Edit.Text := FloatToStr(t.ro0);
  sigma0Edit.Text := FloatToStr(t.sigma0 / 1E9);
  kEdit.Text := FloatToStr(t.k / 1E9);
  alphaEdit.Text := FloatToStr(t.alpha / 1E9);
  sigma1Edit.Text := FloatToStr(t.sigma1 / 1E9);
  k1Edit.Text := FloatToStr(t.k1);
  ctepEdit.Text := FloatToStr(t.ctep);
  gammatepEdit.Text := FloatToStr(t.gammatep);
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  ComboBox1.ItemIndex := 0;
  ComboBox1Change(self);
end;

procedure TForm1.LabeledEdit2Change(Sender: TObject);
begin
  Shape1.Brush.Color := T2C(LabeledEdit2.Text);
end;

procedure TForm1.SetLen(n: Integer);
begin
  SetLength(matarr, n);
end;

end.
