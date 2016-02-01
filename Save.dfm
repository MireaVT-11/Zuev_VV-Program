object saveForm: TsaveForm
  Left = 489
  Top = 140
  BorderStyle = bsDialog
  Caption = 'Save'
  ClientHeight = 75
  ClientWidth = 144
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 3
    Top = 5
    Width = 50
    Height = 13
    Caption = #1056#1072#1079#1084#1077#1088#1099':'
  end
  object Label2: TLabel
    Left = 69
    Top = 24
    Width = 7
    Height = 24
    Caption = '*'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 19
    Top = 50
    Width = 105
    Height = 17
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 24
    Width = 55
    Height = 21
    TabOrder = 1
    Text = '0'
  end
  object Edit2: TEdit
    Left = 82
    Top = 23
    Width = 55
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object SavePictureDialog1: TSavePictureDialog
    DefaultExt = '.bmp'
    Left = 8
    Top = 72
  end
end
