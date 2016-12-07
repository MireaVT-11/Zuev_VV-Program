object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = #1048#1079#1084#1077#1085#1077#1085#1080#1077' '#1089#1074#1086#1081#1089#1090#1074' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
  ClientHeight = 281
  ClientWidth = 369
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 6
    Width = 105
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
  end
  object Shape1: TShape
    Left = 337
    Top = 20
    Width = 24
    Height = 22
  end
  object SpeedButton1: TSpeedButton
    Left = 201
    Top = 20
    Width = 23
    Height = 23
    Caption = '+'
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 176
    Top = 20
    Width = 23
    Height = 23
    Caption = #8211
    OnClick = SpeedButton2Click
  end
  object ColorListBox1: TColorListBox
    Left = 240
    Top = 48
    Width = 121
    Height = 197
    TabStop = False
    Style = [cbStandardColors, cbExtendedColors]
    TabOrder = 0
    OnClick = ColorListBox1Click
  end
  object LabeledEdit2: TLabeledEdit
    Left = 240
    Top = 21
    Width = 91
    Height = 21
    EditLabel.Width = 26
    EditLabel.Height = 13
    EditLabel.Caption = #1062#1074#1077#1090
    TabOrder = 2
    OnChange = LabeledEdit2Change
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 21
    Width = 165
    Height = 21
    AutoComplete = False
    TabOrder = 1
    OnChange = ComboBox1Change
  end
  object GEdit: TLabeledEdit
    Left = 8
    Top = 64
    Width = 105
    Height = 21
    EditLabel.Width = 37
    EditLabel.Height = 13
    EditLabel.Hint = #1052#1086#1076#1091#1083#1100' '#1089#1076#1074#1080#1075#1072
    EditLabel.Caption = 'G ('#1043#1055#1072')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 3
    Text = '0'
  end
  object ro0Edit: TLabeledEdit
    Left = 119
    Top = 64
    Width = 105
    Height = 21
    EditLabel.Width = 47
    EditLabel.Height = 13
    EditLabel.Hint = #1053#1072#1095#1072#1083#1100#1085#1072#1103' '#1087#1083#1086#1090#1085#1086#1089#1090#1100
    EditLabel.Caption = #961#8320' ('#1082#1075'/'#1084#179')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 4
    Text = '0'
  end
  object sigma0Edit: TLabeledEdit
    Left = 8
    Top = 104
    Width = 105
    Height = 21
    EditLabel.Width = 40
    EditLabel.Height = 13
    EditLabel.Hint = #1053#1072#1095#1072#1083#1100#1085#1099#1081' '#1087#1088#1077#1076#1077#1083' '#1090#1077#1082#1091#1095#1077#1089#1090#1080
    EditLabel.Caption = #963#8320' ('#1043#1055#1072')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 5
    Text = '0'
  end
  object sigma1Edit: TLabeledEdit
    Left = 119
    Top = 104
    Width = 105
    Height = 21
    EditLabel.Width = 40
    EditLabel.Height = 13
    EditLabel.Hint = #1055#1088#1077#1076#1077#1083' '#1090#1077#1082#1091#1095#1077#1089#1090#1080' '#1087#1088#1080' '#1088#1072#1079#1088#1091#1096#1077#1085#1080#1080
    EditLabel.Caption = #963#8321' ('#1043#1055#1072')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 6
    Text = '0'
  end
  object kEdit: TLabeledEdit
    Left = 8
    Top = 147
    Width = 105
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Hint = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1086#1073#1098#1105#1084#1085#1086#1075#1086' '#1089#1078#1072#1090#1080#1103
    EditLabel.Caption = 'K ('#1043#1055#1072')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 7
    Text = '0'
  end
  object k1Edit: TLabeledEdit
    Left = 119
    Top = 147
    Width = 105
    Height = 21
    EditLabel.Width = 9
    EditLabel.Height = 13
    EditLabel.Hint = #1050#1083#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1091#1075#1083#1072' '#1074#1085#1091#1090#1088#1077#1085#1085#1077#1075#1086' '#1090#1088#1077#1085#1080#1103
    EditLabel.Caption = 'k'#8321
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 8
    Text = '0'
  end
  object gammatepEdit: TLabeledEdit
    Left = 8
    Top = 184
    Width = 105
    Height = 21
    EditLabel.Width = 32
    EditLabel.Height = 13
    EditLabel.Hint = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1090#1077#1087#1083#1086#1074#1086#1075#1086' '#1088#1072#1089#1096#1080#1088#1077#1085#1080#1103
    EditLabel.Caption = #947' (K'#8315#185')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 9
    Text = '0'
  end
  object ctepEdit: TLabeledEdit
    Left = 119
    Top = 184
    Width = 105
    Height = 21
    EditLabel.Width = 56
    EditLabel.Height = 13
    EditLabel.Hint = #1058#1077#1087#1083#1086#1087#1088#1086#1074#1086#1076#1085#1086#1089#1090#1100
    EditLabel.Caption = 'c ('#1042#1090'/('#1084#183'K))'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 10
    Text = '0'
  end
  object alphaEdit: TLabeledEdit
    Left = 8
    Top = 224
    Width = 216
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Hint = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1088#1072#1079#1091#1087#1088#1086#1095#1085#1077#1085#1080#1103
    EditLabel.Caption = #945' ('#1043#1055#1072')'
    EditLabel.ParentShowHint = False
    EditLabel.ShowHint = True
    TabOrder = 11
    Text = '0'
  end
  object Button1: TButton
    Left = 8
    Top = 251
    Width = 216
    Height = 25
    Caption = #1047#1072#1087#1086#1084#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1084#1072#1090#1077#1088#1080#1072#1083#1072
    Default = True
    TabOrder = 12
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 240
    Top = 251
    Width = 121
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
    TabOrder = 13
    OnClick = Button2Click
  end
  object MatDB: TXMLDocument
    Options = [doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    XML.Strings = (
      '')
    Left = 320
    Top = 224
    DOMVendorDesc = 'ADOM XML v4'
  end
end
