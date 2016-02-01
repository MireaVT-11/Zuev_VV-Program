object graficForm: TgraficForm
  Left = 428
  Top = 368
  Caption = 'graficForm'
  ClientHeight = 492
  ClientWidth = 516
  Color = clBtnFace
  Constraints.MinHeight = 530
  Constraints.MinWidth = 450
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 46
    Height = 13
    Caption = #1060#1091#1085#1082#1094#1080#1103
  end
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 75
    Height = 13
    Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077
  end
  object Chart1: TChart
    Left = 0
    Top = 100
    Width = 469
    Height = 401
    Cursor = crArrow
    BackWall.Brush.Style = bsClear
    BackWall.Color = clWhite
    Legend.ColorWidth = 10
    Legend.Shadow.HorizSize = 1
    Legend.Shadow.VertSize = 1
    Legend.Symbol.Width = 10
    Legend.TopPos = 12
    PrintProportional = False
    Title.Font.Height = -12
    Title.Text.Strings = (
      'TChart')
    Title.TextFormat = ttfHtml
    BottomAxis.Title.Caption = #1059#1079#1083#1099
    BottomAxis.Title.Font.Height = -13
    BottomAxis.TitleSize = 3
    Chart3DPercent = 1
    LeftAxis.LabelsSeparation = 1
    LeftAxis.LabelStyle = talValue
    LeftAxis.MaximumRound = True
    LeftAxis.MinimumRound = True
    LeftAxis.RoundFirstLabel = False
    RightAxis.Title.Caption = #1059#1079#1083#1099
    View3D = False
    Zoom.AnimatedSteps = 100
    Color = clWhite
    TabOrder = 0
    OnDblClick = Chart1DblClick
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TLineSeries
      Legend.Visible = False
      Marks.Style = smsValue
      Marks.Callout.Length = 9
      Marks.DrawEvery = 3
      SeriesColor = clBlack
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      OutLine.Visible = True
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      Legend.Visible = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = clFuchsia
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series3: TLineSeries
      Legend.Visible = False
      Active = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = 8454143
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series4: TLineSeries
      Legend.Visible = False
      Active = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = 16777088
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series5: TLineSeries
      Legend.Visible = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = 4194432
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      OutLine.Style = psDash
      OutLine.Visible = True
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series6: TLineSeries
      Legend.Visible = False
      Active = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = clPurple
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series7: TLineSeries
      Legend.Visible = False
      Active = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = 8421440
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series8: TLineSeries
      Legend.Visible = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = clBlue
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      OutLine.Style = psDot
      OutLine.Visible = True
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series9: TLineSeries
      Legend.Visible = False
      Active = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = clAqua
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series10: TLineSeries
      Legend.Visible = False
      Active = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = 4091771
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series11: TLineSeries
      Legend.Visible = False
      Marks.Style = smsXValue
      Marks.Callout.Length = 9
      SeriesColor = clGreen
      ShowInLegend = False
      Brush.BackColor = clDefault
      DrawStyle = dsCurve
      LinePen.Width = 3
      OutLine.Style = psDashDot
      OutLine.Visible = True
      Pointer.Dark3D = False
      Pointer.HorizSize = 2
      Pointer.InflateMargins = False
      Pointer.Style = psSmallDot
      Pointer.VertSize = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loDescending
    end
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 24
    Width = 281
    Height = 21
    Style = csDropDownList
    TabOrder = 1
    OnChange = ComboBox1Change
    Items.Strings = (
      #1050#1086#1086#1088#1076#1080#1085#1072#1090#1099' '#1091#1079#1083#1086#1074' '#1087#1086' R'
      #1050#1086#1086#1088#1076#1080#1085#1072#1090#1099' '#1091#1079#1083#1086#1074' '#1087#1086' Z'
      #1057#1082#1086#1088#1086#1089#1090#1080' '#1091#1079#1083#1086#1074' '#1087#1086' R'
      #1057#1082#1086#1088#1086#1089#1090#1080' '#1091#1079#1083#1086#1074' '#1087#1086' Z'
      #1055#1086#1083#1085#1099#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epsrr'
      #1055#1086#1083#1085#1099#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epszz'
      #1055#1086#1083#1085#1099#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epsrz'
      #1055#1086#1083#1085#1099#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epstt'
      #1055#1083#1072#1089#1090#1080#1095#1077#1089#1082#1080#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epsrrp'
      #1055#1083#1072#1089#1090#1080#1095#1077#1089#1082#1080#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epszzp'
      #1055#1083#1072#1089#1090#1080#1095#1077#1089#1082#1080#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epsrzp'
      #1055#1083#1072#1089#1090#1080#1095#1077#1089#1082#1080#1077' '#1076#1077#1092#1086#1088#1072#1094#1080#1080' epsttp'
      #1053#1072#1087#1088#1103#1078#1077#1085#1080#1103' sigmarr'
      #1053#1072#1087#1088#1103#1078#1077#1085#1080#1103' sigmarz'
      #1053#1072#1087#1088#1103#1078#1077#1085#1080#1103' sigmazz'
      #1053#1072#1087#1088#1103#1078#1077#1085#1080#1103' sigmatt'
      #1048#1085#1090#1077#1085#1089#1080#1074#1085#1086#1089#1090#1100' '#1087#1083#1072#1089#1090#1080#1095#1077#1089#1082#1080#1093' '#1076#1077#1092#1086#1088#1084#1072#1094#1080#1081' sqI2p'
      #1055#1086#1083#1085#1072#1103' '#1086#1073#1098#1105#1084#1085#1072#1103' '#1076#1077#1092#1086#1088#1084#1072#1094#1080#1103' tet'
      #1055#1083#1072#1089#1090#1080#1095#1077#1089#1082#1072#1103' '#1086#1073#1098#1105#1084#1085#1072#1103' '#1076#1077#1092#1086#1088#1084#1072#1094#1080#1103' tetp'
      #1069#1085#1077#1088#1075#1080#1103' ener'
      #1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' T'
      #1055#1083#1072#1089#1090#1080#1095#1077#1089#1082#1072#1103' '#1095#1072#1089#1090#1100' '#1087#1088#1080#1088#1086#1089#1090#1072' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' T_plast'
      #1059#1087#1088#1091#1075#1072#1103' '#1095#1072#1089#1090#1100' '#1087#1088#1080#1088#1086#1089#1090#1072' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' T_elast')
  end
  object ComboBox2: TComboBox
    Left = 8
    Top = 72
    Width = 281
    Height = 21
    Style = csDropDownList
    ItemIndex = 3
    TabOrder = 2
    Text = #1041#1086#1082#1086#1074#1072#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1091#1076#1072#1088#1085#1080#1082#1072
    OnChange = ComboBox2Change
    Items.Strings = (
      #1062#1077#1085#1090#1088' '#1084#1080#1096#1077#1085#1080
      #1062#1077#1085#1090#1088' '#1091#1076#1072#1088#1085#1080#1082#1072
      #1041#1086#1082#1086#1074#1072#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1084#1080#1096#1077#1085#1080
      #1041#1086#1082#1086#1074#1072#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1091#1076#1072#1088#1085#1080#1082#1072
      #1058#1099#1083#1100#1085#1072#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1084#1080#1096#1077#1085#1080
      #1058#1099#1083#1100#1085#1072#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1091#1076#1072#1088#1085#1080#1082#1072
      #1042#1077#1088#1093#1085#1103#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1084#1080#1096#1077#1085#1080
      #1042#1077#1088#1093#1085#1103#1103' '#1089#1090#1086#1088#1086#1085#1072' '#1091#1076#1072#1088#1085#1080#1082#1072)
  end
  object BitBtn1: TBitBtn
    Left = 320
    Top = 6
    Width = 121
    Height = 20
    Caption = #1055#1077#1095#1072#1090#1100
    TabOrder = 3
    OnClick = BitBtn1Click
  end
  object Button1: TButton
    Left = 320
    Top = 30
    Width = 121
    Height = 20
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
    TabOrder = 4
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 320
    Top = 64
    Width = 97
    Height = 17
    Caption = #1048#1085#1090#1077#1088#1087#1086#1083#1103#1094#1080#1103
    Checked = True
    State = cbChecked
    TabOrder = 5
    OnClick = CheckBox1Click
  end
  object PrintDialog1: TPrintDialog
    Left = 280
    Top = 56
  end
  object SavePictureDialog1: TSavePictureDialog
    DefaultExt = '.bmp'
    FileName = 'Graph1.bmp'
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    InitialDir = '%USERPROFILE%/Desktop'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 296
    Top = 120
  end
end
