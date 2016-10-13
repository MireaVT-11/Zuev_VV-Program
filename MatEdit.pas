unit MatEdit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.Classes, Vcl.Graphics, System.Generics.Collections,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls;

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
    LabeledEdit6: TLabeledEdit;
    LabeledEdit7: TLabeledEdit;
    LabeledEdit8: TLabeledEdit;
    LabeledEdit9: TLabeledEdit;
    LabeledEdit10: TLabeledEdit;
    Button1: TButton;
    procedure ColorListBox1Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure LabeledEdit2Change(Sender: TObject);
  private
    { Private declarations }
  public
    matarr: array of TMaterial;
    procedure SetLen(n:Integer);
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

function C2T(cl:TColor):string;
var
  c: Integer;
  rgb: array [0 .. 3] of byte absolute c;
begin
  c := ColorToRGB(cl);
  Result := Format('%.2x%.2x%.2x', [rgb[0], rgb[1], rgb[2]]);
end;

function T2C(s:string):TColor;
var
  c: Integer;
  rgb: array [0 .. 3] of byte absolute c;
begin
  if not TryStrToInt('$'+s,c) then Exit(0);
  Result:=rgb[0]shl 16+rgb[1]shl 8+rgb[2];
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
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  ComboBox1.ItemIndex:=0;
  ComboBox1Change(self);
end;

procedure TForm1.LabeledEdit2Change(Sender: TObject);
begin
  Shape1.Brush.Color := T2C(LabeledEdit2.Text);
end;

procedure TForm1.SetLen(n: Integer);
begin
  SetLength(matarr,n);
end;

end.
