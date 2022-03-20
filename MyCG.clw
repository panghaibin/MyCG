; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyCGView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyCG.h"
LastPage=0

ClassCount=5
Class1=CMyCGApp
Class2=CMyCGDoc
Class3=CMyCGView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CMyCGApp]
Type=0
HeaderFile=MyCG.h
ImplementationFile=MyCG.cpp
Filter=N

[CLS:CMyCGDoc]
Type=0
HeaderFile=MyCGDoc.h
ImplementationFile=MyCGDoc.cpp
Filter=N

[CLS:CMyCGView]
Type=0
HeaderFile=MyCGView.h
ImplementationFile=MyCGView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_BZR_DRAW_SPLINE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_BZR_DEL_POINT




[CLS:CAboutDlg]
Type=0
HeaderFile=MyCG.cpp
ImplementationFile=MyCG.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_LINE_PRE_DDA
Command2=ID_LINE_PRE_MIDPOINT
Command3=ID_LINE_PRE_BH
Command4=ID_LINE_DRAW_DDA
Command5=ID_LINE_DRAW_MIDPOINT
Command6=ID_LINE_DRAW_BH
Command7=ID_CIRCLE_PRE_MIDPOINT
Command8=ID_CIRCLE_PRE_BH
Command9=ID_ELLIPSE_PRE_MIDPOINT
Command10=ID_CIRCLE_DRAW_MIDPOINT
Command11=ID_CIRCLE_DRAW_BH
Command12=ID_ELLIPSE_DRAW_MIDPOINT
Command13=ID_FILL_FOR_DRAW
Command14=ID_FILL_SET_COLOR
Command15=ID_FILL_SCAN
Command16=ID_FILL_EDGE
Command17=ID_FILL_SEED
Command18=ID_CUT_LINE_BY_CS
Command19=ID_CUT_POLY_BY_SH
Command20=ID_TRANS_FOR_DRAW
Command21=ID_TRANS_SET_CNTR
Command22=ID_TRANS_MOVE
Command23=ID_TRANS_ROT
Command24=ID_TRANS_SCALE
Command25=ID_BZR_ADD_POINT
Command26=ID_BZR_MOVE_POINT
Command27=ID_BZR_DEL_POINT
Command28=ID_BZR_DRAW_SPLINE
Command29=ID_MENU_CLEAR_SCREEN
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

