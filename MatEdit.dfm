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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
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
    Width = 216
    Height = 22
    AutoComplete = False
    Style = csOwnerDrawFixed
    ItemIndex = 0
    TabOrder = 1
    Text = #1040#1083#1102#1084#1080#1085#1080#1081
    OnChange = ComboBox1Change
    Items.Strings = (
      #1040#1083#1102#1084#1080#1085#1080#1081
      #1057#1090#1072#1083#1100
      #1057#1082#1072#1083#1100#1085#1099#1081' '#1075#1088#1091#1085#1090' 1'
      #1057#1082#1072#1083#1100#1085#1099#1081' '#1075#1088#1091#1085#1090' 2'
      #1057#1082#1072#1083#1100#1085#1099#1081' '#1075#1088#1091#1085#1090' 3'
      #1057#1082#1072#1083#1100#1085#1099#1081' '#1075#1088#1091#1085#1090' 4'
      #1057#1090#1077#1082#1083#1086#1087#1083#1072#1089#1090#1080#1082
      #1055#1077#1089#1086#1082
      #1042#1086#1079#1076#1091#1093
      #1057#1082#1072#1083#1072' '#1047#1091#1077#1074#1072)
  end
  object GEdit: TLabeledEdit
    Left = 8
    Top = 64
    Width = 105
    Height = 21
    EditLabel.Width = 7
    EditLabel.Height = 13
    EditLabel.Caption = 'G'
    TabOrder = 3
    Text = '0'
  end
  object ro0Edit: TLabeledEdit
    Left = 119
    Top = 64
    Width = 105
    Height = 21
    EditLabel.Width = 16
    EditLabel.Height = 13
    EditLabel.Caption = 'ro0'
    TabOrder = 4
    Text = '0'
  end
  object sigma0Edit: TLabeledEdit
    Left = 8
    Top = 104
    Width = 105
    Height = 21
    EditLabel.Width = 33
    EditLabel.Height = 13
    EditLabel.Caption = 'sigma0'
    TabOrder = 5
    Text = '0'
  end
  object sigma1Edit: TLabeledEdit
    Left = 119
    Top = 104
    Width = 105
    Height = 21
    EditLabel.Width = 33
    EditLabel.Height = 13
    EditLabel.Caption = 'sigma1'
    TabOrder = 6
    Text = '0'
  end
  object kEdit: TLabeledEdit
    Left = 8
    Top = 147
    Width = 105
    Height = 21
    EditLabel.Width = 5
    EditLabel.Height = 13
    EditLabel.Caption = 'k'
    TabOrder = 7
    Text = '0'
  end
  object k1Edit: TLabeledEdit
    Left = 119
    Top = 147
    Width = 105
    Height = 21
    EditLabel.Width = 11
    EditLabel.Height = 13
    EditLabel.Caption = 'k1'
    TabOrder = 8
    Text = '0'
  end
  object gammatepEdit: TLabeledEdit
    Left = 8
    Top = 184
    Width = 105
    Height = 21
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = 'gammatep'
    TabOrder = 9
    Text = '0'
  end
  object ctepEdit: TLabeledEdit
    Left = 119
    Top = 184
    Width = 105
    Height = 21
    EditLabel.Width = 21
    EditLabel.Height = 13
    EditLabel.Caption = 'ctep'
    TabOrder = 10
    Text = '0'
  end
  object alphaEdit: TLabeledEdit
    Left = 8
    Top = 224
    Width = 216
    Height = 21
    EditLabel.Width = 26
    EditLabel.Height = 13
    EditLabel.Caption = 'alpha'
    TabOrder = 11
    Text = '0'
  end
  object Button1: TButton
    Left = 8
    Top = 251
    Width = 216
    Height = 25
    Caption = #1047#1072#1087#1086#1084#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
    TabOrder = 12
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 240
    Top = 256
    Width = 121
    Height = 17
    Hint = #1042#1085#1080#1084#1072#1085#1080#1077'! '#1052#1086#1078#1077#1090' '#1080#1089#1087#1086#1088#1090#1080#1090#1100' '#1092#1072#1081#1083'! '#1051#1091#1095#1096#1077' '#1085#1077' '#1085#1072#1076#1086'!'
    Caption = #1047#1072#1087#1080#1089#1072#1090#1100' '#1074' '#1092#1072#1081#1083
    ParentShowHint = False
    ShowHint = True
    TabOrder = 13
  end
  object MatDB: TXMLDocument
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 152
    Top = 8
    DOMVendorDesc = 'ADOM XML v4'
  end
end
