
# MAKE file for IBM.MAK

# Revised:  1995-11-02

# Macro definitions

C_SW=-G4 -O+ -W1 -C
RC_SW=-r


ROPs.Exe: AppDefs.Obj GetBmp.Obj OpenDlg.Obj\
        ROPs.Obj ROPs.Res ROPsWnd.Obj\
        Support.Obj ViewDlg.Obj
 icc /B"/EXEPACK" @IBM.Lnk
 rc ROPs.Res ROPs.Exe

AppDefs.Obj: AppDefs.C
 Icc $(C_SW) -Fo$*.Obj AppDefs.C

GetBmp.Obj: GetBmp.C
 Icc $(C_SW) -Fo$*.Obj GetBmp.C

OpenDlg.Obj: OpenDlg.C
 Icc $(C_SW) -Fo$*.Obj OpenDlg.C

ROPs.Obj: ROPs.C
 Icc $(C_SW) -Fo$*.Obj ROPs.C

ROPs.Res: ROPs.Rc
 Rc $(RC_SW) ROPs.Rc $*.Res

ROPsWnd.Obj: ROPsWnd.C
 Icc $(C_SW) -Fo$*.Obj ROPsWnd.C

Support.Obj: Support.C
 Icc $(C_SW) -Fo$*.Obj Support.C

ViewDlg.Obj: ViewDlg.C
 Icc $(C_SW) -Fo$*.Obj ViewDlg.C

