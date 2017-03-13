object MQCForm: TMQCForm
  Left = 686
  Top = 386
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  ClientHeight = 444
  ClientWidth = 560
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object EList: TListView
    Left = 8
    Top = 8
    Width = 401
    Height = 428
    Checkboxes = True
    Columns = <
      item
        Caption = #1053#1072#1079#1074#1072#1085#1080#1077
        Width = 200
      end
      item
        Caption = #1057#1090#1072#1090#1091#1089
        Width = 177
      end>
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnSelectItem = EListSelectItem
    OnItemChecked = EListItemChecked
  end
  object AddBtn: TButton
    Left = 415
    Top = 8
    Width = 134
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 1
    OnClick = AddBtnClick
  end
  object DelBtn: TButton
    Left = 415
    Top = 39
    Width = 134
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    Enabled = False
    TabOrder = 2
    OnClick = DelBtnClick
  end
  object EditBtn: TButton
    Left = 415
    Top = 101
    Width = 134
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100
    Enabled = False
    TabOrder = 3
  end
  object DubBtn: TButton
    Left = 415
    Top = 70
    Width = 134
    Height = 25
    Caption = #1044#1091#1073#1083#1080#1088#1086#1074#1072#1090#1100
    Enabled = False
    TabOrder = 4
    OnClick = DubBtnClick
  end
  object LoadBtn: TButton
    Left = 415
    Top = 149
    Width = 134
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 5
    OnClick = LoadBtnClick
  end
  object SaveBtn: TButton
    Left = 415
    Top = 180
    Width = 134
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 6
    OnClick = SaveBtnClick
  end
  object AbNowBtn: TButton
    Left = 415
    Top = 324
    Width = 134
    Height = 25
    Caption = #1055#1088#1077#1088#1074#1072#1090#1100' '#1090#1077#1082#1091#1097#1077#1077
    Enabled = False
    TabOrder = 7
    OnClick = AbNowBtnClick
  end
  object AbAllBtn: TButton
    Left = 415
    Top = 355
    Width = 134
    Height = 25
    Caption = #1055#1088#1077#1088#1074#1072#1090#1100' '#1074#1089#1105
    Enabled = False
    TabOrder = 8
    OnClick = AbAllBtnClick
  end
  object StartBtn: TButton
    Left = 415
    Top = 400
    Width = 134
    Height = 36
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 9
    OnClick = StartBtnClick
  end
  object HideGraphCBox: TCheckBox
    Left = 415
    Top = 301
    Width = 137
    Height = 17
    Caption = #1057#1082#1088#1099#1090#1100' '#1075#1088#1072#1092#1080#1082#1091
    Checked = True
    State = cbChecked
    TabOrder = 10
  end
  object FileSaveDialog: TFileSaveDialog
    DefaultExtension = '*.xbcq'
    FavoriteLinks = <>
    FileTypes = <
      item
        DisplayName = 'XML-'#1092#1072#1081#1083' '#1086#1095#1077#1088#1077#1076#1080' '#1088#1072#1089#1095#1105#1090#1072
        FileMask = '*.xbcq'
      end
      item
        DisplayName = 'XML-'#1092#1072#1081#1083
        FileMask = '*.xml'
      end>
    OkButtonLabel = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Options = [fdoOverWritePrompt, fdoStrictFileTypes]
    Title = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1092#1072#1081#1083#1072' '#1086#1095#1077#1088#1077#1076#1080' '#1088#1072#1089#1095#1105#1090#1072
    Left = 432
    Top = 224
  end
  object FileOpenDialog: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <
      item
        DisplayName = 'XML-'#1092#1072#1081#1083' '#1086#1095#1077#1088#1077#1076#1080' '#1088#1072#1089#1095#1105#1090#1072
        FileMask = '*.xml;*.xbcq'
      end
      item
        DisplayName = #1042#1089#1077' '#1092#1072#1081#1083#1099
        FileMask = '*.*'
      end>
    OkButtonLabel = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    Options = []
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1086#1095#1077#1088#1077#1076#1080' '#1088#1072#1089#1095#1105#1090#1072
    Left = 488
    Top = 240
  end
  object XML: TXMLDocument
    Options = [doNodeAutoCreate, doNodeAutoIndent, doAttrNull, doAutoPrefix, doNamespaceDecl]
    Left = 432
    Top = 272
    DOMVendorDesc = 'ADOM XML v4'
  end
end
