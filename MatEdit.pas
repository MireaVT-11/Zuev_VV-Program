unit MatEdit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  System.Generics.Collections, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls, Xml.xmldom, Xml.XMLIntf,
  Xml.Win.msxmldom, Xml.XMLDoc, Xml.adomxmldom;

type
  TMaterial = record
    G, ro0, sigma0, k, alpha, sigma1, k1, ctep, gammatep: Extended;
    Name: UnicodeString;
    Color: Integer;
    function ToString: UnicodeString;
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
    MatDB: TXMLDocument;
    CheckBox1: TCheckBox;
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
    procedure ReadFromFile(path:UnicodeString);
  end;

var
  Form1: TForm1;

function T2C(s: UnicodeString): TColor;
function C2T(cl: TColor): UnicodeString;

implementation

uses
  ExtendedUtils;

{$R *.dfm}

var
  LastPath: UnicodeString;

function C2T(cl: TColor): UnicodeString;
var
  c: Integer;
  rgb: array [0 .. 3] of byte absolute c;
begin
  c := ColorToRGB(cl);
  Result := Format('%.2x%.2x%.2x', [rgb[0], rgb[1], rgb[2]]);
end;

function T2C(s: UnicodeString): TColor;
var
  c: Integer;
  rgb: array [0 .. 3] of byte absolute c;
begin
  if not TryStrToInt('$' + s, c) then
  begin
    try
      if s.StartsWith('cl') then
        Exit(StringToColor(s))
      else
        Exit(StringToColor('cl'+s));
    except
      Exit(0);
    end;
  end;
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
  if CheckBox1.Checked and (i > 0) then
    begin
      try
        MatDB.LoadFromFile(LastPath);
        with MatDB.Node.ChildNodes.Nodes['materials'].ChildNodes.Nodes[i - 1] do
          try
            Attributes['name'] := matarr[i].Name;
            Attributes['color'] := C2T(matarr[i].Color);
            Attributes['alpha'] := FloatToStr(matarr[i].alpha);
            Attributes['g'] := FloatToStr(matarr[i].G);
            Attributes['ro0'] := FloatToStr(matarr[i].ro0);
            Attributes['k1'] := FloatToStr(matarr[i].k1);
            Attributes['k'] := FloatToStr(matarr[i].k);
            Attributes['sigma0'] := FloatToStr(matarr[i].sigma0);
            Attributes['sigma1'] := FloatToStr(matarr[i].sigma1);
            Attributes['c'] := FloatToStr(matarr[i].ctep);
            Attributes['gamma'] := FloatToStr(matarr[i].gammatep);
            MatDB.SaveToFile(LastPath);
          except
          end;
      finally

      end;
    end;
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
var
  i:Integer;
begin
  ComboBox1.Items.Clear;
  for i := 0 to Length(matarr)-1 do
    ComboBox1.Items.Add(matarr[i].Name);
  ComboBox1.ItemIndex := 0;
  ComboBox1Change(self);
end;

procedure TForm1.LabeledEdit2Change(Sender: TObject);
begin
  Shape1.Brush.Color := T2C(LabeledEdit2.Text);
end;

procedure TForm1.ReadFromFile(path: UnicodeString);
var
  i:Integer;
begin
  LastPath := path;
  try
    MatDB.LoadFromFile(path);
    with MatDB.Node.ChildNodes.Nodes['materials'] do
    begin
      SetLength(matarr, ChildNodes.Count + 1);
      for i := 1 to ChildNodes.Count do
        with ChildNodes.Nodes[i - 1] do
        try
          matarr[i].Name := Attributes['name'];
          matarr[i].Color := T2C(Attributes['color']);
          matarr[i].alpha := StrToFloat(Attributes['alpha']);
          matarr[i].G := StrToFloat(Attributes['g']);
          matarr[i].ro0 := StrToFloat(Attributes['ro0']);
          matarr[i].k1 := StrToFloat(Attributes['k1']);
          matarr[i].k := StrToFloat(Attributes['k']);
          matarr[i].sigma0 := StrToFloat(Attributes['sigma0']);
          matarr[i].sigma1 := StrToFloat(Attributes['sigma1']);
          matarr[i].ctep := StrToFloat(Attributes['c']);
          matarr[i].gammatep := StrToFloat(Attributes['gamma']);
        except
          on e:Exception do
            Application.MessageBox(PWideChar('Ошибка при чтении данных из файла!'#13#10 + XML),'Ошибка в XML')
        end;
    end;
  finally
  end;
end;

procedure TForm1.SetLen(n: Integer);
begin
  SetLength(matarr, n);
end;

{ TMaterial }

function TMaterial.ToString: UnicodeString;
begin
  Result := Result + Name + ' |';
  Result := Result + ' G=' + GetScPref(G, 2, 'Па');
  Result := Result + '; ro0=' + GetScPref(ro0*1000, 2, 'г/м^3');
  Result := Result + '; sigma0=' + GetScPref(sigma0, 2, 'Па');
  Result := Result + '; sigma1=' + GetScPref(sigma1, 2, 'Па');
  Result := Result + '; k=' + GetScPref(k, 2, 'Па');
  Result := Result + '; k1=' + FloatToStr(k1);
  Result := Result + '; c=' + GetScPref(ctep, 4, 'Вт/(м·K)');
  Result := Result + '; gamma=' + FloatToStr(gammatep) + ' 1/K';
  Result := Result + '; alpha=' + GetScPref(alpha, 2, 'Па');
end;

end.
