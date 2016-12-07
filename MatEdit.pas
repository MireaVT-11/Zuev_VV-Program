unit MatEdit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  System.Generics.Collections, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls, Xml.xmldom, Xml.XMLIntf,
  Xml.XMLDoc, Xml.adomxmldom, Vcl.Buttons;

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
    SpeedButton1: TSpeedButton;
    Button2: TButton;
    SpeedButton2: TSpeedButton;
    procedure ColorListBox1Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure LabeledEdit2Change(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
  private
    MaterialList: TList<TMaterial>;
  public
    matarr: TArray<TMaterial>;
    procedure ReadFromFile(path: UnicodeString);
    procedure ReinitList;
  end;

var
  Form1: TForm1;

function T2C(s: UnicodeString): TColor;
function C2T(cl: TColor): UnicodeString;

implementation

uses
  ExtendedUtils;

{$R *.dfm}

const
  DefMaterial: TMaterial = (G: 10E9; ro0: 1000; sigma0: 1E9; k: 5E9; alpha: 0; sigma1: 1E8; k1: 0; ctep: 10; gammatep: 1E-5;
    name: 'Новый материал'; Color: clGray);
  BlankXMl = '<?xml version="1.0" encoding="UTF-8"?> <materials/>';

var
  LastPath: UnicodeString;
  LastIndex: Integer;

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
        Exit(StringToColor('cl' + s))
    except
      Exit(0)
    end
  end;
  Exit(rgb[0] shl 16 + rgb[1] shl 8 + rgb[2])
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  t: TMaterial;
begin
  t.G := StrToFloat(GEdit.Text) * 1E9;
  t.ro0 := StrToFloat(ro0Edit.Text);
  t.sigma0 := StrToFloat(sigma0Edit.Text) * 1E9;
  t.k := StrToFloat(kEdit.Text) * 1E9;
  t.alpha := StrToFloat(alphaEdit.Text) * 1E9;
  t.sigma1 := StrToFloat(sigma1Edit.Text) * 1E9;
  t.k1 := StrToFloat(k1Edit.Text);
  t.ctep := StrToFloat(ctepEdit.Text);
  t.gammatep := StrToFloat(gammatepEdit.Text);
  t.Color := T2C(LabeledEdit2.Text);
  t.Name := ComboBox1.Text;
  MaterialList[LastIndex] := t;
  matarr := MaterialList.ToArray;
  ComboBox1.Items[LastIndex] := t.Name;
  ComboBox1.ItemIndex := LastIndex;
  ComboBox1Change(self);
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  i: Integer;
  t: TMaterial;
begin
  if Application.MessageBox
    ('Внимание: файл материалов будет перезаписан и в него будут внесены все изменения, которые были сделаны с момента запуска программы (кроме изменений материала "Воздух"). Продолжить?',
    'Запись в файл', MB_YESNO + MB_ICONWARNING) <> IDYES then
    Exit;
  Button1Click(self);
  MatDB.LoadFromXML(BlankXML);
  try
    for i := 1 to MaterialList.Count - 1 do
      with MatDB.Node.ChildNodes.Nodes['materials'].AddChild('material') do
      begin
        t := MaterialList[i];
        Attributes['name'] := t.Name;
        Attributes['color'] := C2T(t.Color);
        Attributes['alpha'] := FloatToStr(t.alpha);
        Attributes['g'] := FloatToStr(t.G);
        Attributes['ro0'] := FloatToStr(t.ro0);
        Attributes['k1'] := FloatToStr(t.k1);
        Attributes['k'] := FloatToStr(t.k);
        Attributes['sigma0'] := FloatToStr(t.sigma0);
        Attributes['sigma1'] := FloatToStr(t.sigma1);
        Attributes['c'] := FloatToStr(t.ctep);
        Attributes['gamma'] := FloatToStr(t.gammatep);
      end;
  finally
    MatDB.SaveToFile(LastPath);
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
  if ComboBox1.ItemIndex < 0 then
    Exit;
  LastIndex := ComboBox1.ItemIndex;
  SpeedButton2.Enabled := LastIndex > 0;
  t := MaterialList[LastIndex];
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

procedure TForm1.FormCreate(Sender: TObject);
begin
  MaterialList := TList<TMaterial>.Create;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  MaterialList.Free;
end;

procedure TForm1.FormShow(Sender: TObject);
var
  i: Integer;
begin
  ComboBox1.Items.Clear;
  for i := 0 to MaterialList.Count - 1 do
    ComboBox1.Items.Add(MaterialList[i].Name);
  ComboBox1.ItemIndex := 0;
  ComboBox1Change(self);
end;

procedure TForm1.LabeledEdit2Change(Sender: TObject);
begin
  Shape1.Brush.Color := T2C(LabeledEdit2.Text);
end;

procedure TForm1.ReadFromFile(path: UnicodeString);
var
  i: Integer;
  t: TMaterial;
begin
  LastPath := path;  
  try
    if FileExists(path) then
      MatDB.LoadFromFile(path)
    else
      MatDB.LoadFromXML(BlankXML);
    with MatDB.Node.ChildNodes.Nodes['materials'] do
    begin
      MaterialList.Clear;
      MaterialList.Add(DefMaterial);
      for i := 1 to ChildNodes.Count do
        with ChildNodes.Nodes[i - 1] do
          try
            t:=DefMaterial;
            t.Name := Attributes['name'];
            if HasAttribute('color') then
              t.Color := T2C(Attributes['color']);
            if HasAttribute('alpha') then
              t.alpha := StrToFloat(Attributes['alpha']);
            if HasAttribute('g') then
              t.G := StrToFloat(Attributes['g']);
            if HasAttribute('ro0') then
              t.ro0 := StrToFloat(Attributes['ro0']);
            if HasAttribute('k1') then
              t.k1 := StrToFloat(Attributes['k1']);
            if HasAttribute('k') then
              t.k := StrToFloat(Attributes['k']);
            if HasAttribute('sigma0') then
              t.sigma0 := StrToFloat(Attributes['sigma0']);
            if HasAttribute('sigma1') then
              t.sigma1 := StrToFloat(Attributes['sigma1']);
            if HasAttribute('c') then
              t.ctep := StrToFloat(Attributes['c']);
            if HasAttribute('gamma') then
              t.gammatep := StrToFloat(Attributes['gamma']);
            MaterialList.Add(t);
          except
            on e: Exception do
              Application.MessageBox(PWideChar('Ошибка при чтении данных из файла!'#13#10 + Xml), 'Ошибка в XML')
          end;
    end;
  finally
    matarr := MaterialList.ToArray;
  end;
end;

procedure TForm1.ReinitList;
begin
  MaterialList.Clear;
  MaterialList.AddRange(matarr);
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
  MaterialList.Add(DefMaterial);
  matarr := MaterialList.ToArray;
  ComboBox1.Items.Add(DefMaterial.Name);
  ComboBox1.ItemIndex := ComboBox1.Items.Count - 1;
  ComboBox1Change(self);
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
  if LastIndex = 0 then
    Exit;
  if Application.MessageBox('Внимание: удаление материала нельзя будет отменить. Продолжить?', PWideChar('Удаление материала "'+ComboBox1.Text+'"'), MB_YESNO + MB_ICONWARNING) <> IDYES then
    Exit;
  MaterialList.Delete(LastIndex);
  matarr := MaterialList.ToArray;
  ComboBox1.Items.Delete(LastIndex);
  ComboBox1.ItemIndex := LastIndex - 1;
  ComboBox1Change(self);
end;

{ TMaterial }

function TMaterial.ToString: UnicodeString;
begin
  Result := Result + name + ' |';
  Result := Result + ' G=' + GetScPref(G, 2, 'Па');
  Result := Result + '; ro0=' + GetScPref(ro0 * 1000, 2, 'г/м^3');
  Result := Result + '; sigma0=' + GetScPref(sigma0, 2, 'Па');
  Result := Result + '; sigma1=' + GetScPref(sigma1, 2, 'Па');
  Result := Result + '; k=' + GetScPref(k, 2, 'Па');
  Result := Result + '; k1=' + FloatToStr(k1);
  Result := Result + '; c=' + GetScPref(ctep, 4, 'Вт/(м·K)');
  Result := Result + '; gamma=' + FloatToStr(gammatep) + ' 1/K';
  Result := Result + '; alpha=' + GetScPref(alpha, 2, 'Па');
end;

end.
