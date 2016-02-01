object newMaterialForm: TnewMaterialForm
  Left = 303
  Top = 303
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1085#1086#1074#1086#1075#1086' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
  ClientHeight = 349
  ClientWidth = 201
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 3
    Top = 8
    Width = 108
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
  end
  object Label2: TLabel
    Left = 3
    Top = 48
    Width = 52
    Height = 13
    Caption = #1087#1083#1086#1090#1085#1086#1089#1090#1100
  end
  object Label3: TLabel
    Left = 3
    Top = 88
    Width = 92
    Height = 13
    Caption = 'G - '#1084#1086#1076#1091#1083#1100' '#1089#1076#1074#1080#1075#1072
  end
  object Label4: TLabel
    Left = 3
    Top = 128
    Width = 189
    Height = 13
    Caption = 'sigma0 - '#1085#1072#1095#1072#1083#1100#1085#1099#1081' '#1087#1088#1077#1076#1077#1083' '#1090#1077#1082#1091#1095#1077#1089#1090#1080
  end
  object Label5: TLabel
    Left = 3
    Top = 168
    Width = 103
    Height = 13
    Caption = 'K - '#1082#1086#1101#1092'. '#1086#1073'. '#1089#1078#1072#1090#1080#1103
  end
  object Label6: TLabel
    Left = 3
    Top = 208
    Width = 26
    Height = 13
    Caption = 'alpha'
  end
  object Label7: TLabel
    Left = 3
    Top = 248
    Width = 33
    Height = 13
    Caption = 'sigma1'
  end
  object Label8: TLabel
    Left = 128
    Top = 302
    Width = 25
    Height = 13
    Caption = #1062#1074#1077#1090
  end
  object Button1: TButton
    Left = 3
    Top = 296
    Width = 75
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 0
    OnClick = Button1Click
  end
  object NameEdit: TEdit
    Left = 3
    Top = 24
    Width = 190
    Height = 21
    TabOrder = 1
  end
  object densEdit: TEdit
    Left = 3
    Top = 64
    Width = 190
    Height = 21
    TabOrder = 2
  end
  object GEdit: TEdit
    Left = 3
    Top = 104
    Width = 190
    Height = 21
    TabOrder = 3
  end
  object sigma0Edit: TEdit
    Left = 3
    Top = 144
    Width = 190
    Height = 21
    TabOrder = 4
  end
  object kEdit: TEdit
    Left = 3
    Top = 184
    Width = 190
    Height = 21
    TabOrder = 5
  end
  object sigma1Edit: TEdit
    Left = 3
    Top = 264
    Width = 190
    Height = 21
    TabOrder = 6
  end
  object alphaEdit: TEdit
    Left = 3
    Top = 224
    Width = 190
    Height = 21
    TabOrder = 7
  end
  object Panel1: TPanel
    Left = 160
    Top = 296
    Width = 25
    Height = 25
    BevelOuter = bvLowered
    Color = clGreen
    TabOrder = 8
    OnClick = Panel1Click
  end
  object ColorDialog1: TColorDialog
    Left = 96
    Top = 288
  end
end
