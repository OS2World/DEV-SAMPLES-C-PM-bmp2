
# MAKE file for WATCOM.MAK

# Revised:  1995-11-02

# Macro definitions

C_SW=-ms -4s -s -ox -zp4 -w1 
RC_SW=-r 


ROPs.Exe: AppDefs.Obj GetBmp.Obj OpenDlg.Obj\
        ROPs.Obj ROPs.Res ROPsWnd.Obj\
        Support.Obj ViewDlg.Obj
 WLink @WATCOM.Lnk
 Rc ROPs.Res ROPS.Exe

AppDefs.Obj: AppDefs.C
 Wcl386 $(C_SW)-fo=$*.Obj AppDefs.C

GetBmp.Obj: GetBmp.C
 Wcl386 $(C_SW)-fo=$*.Obj GetBmp.C

OpenDlg.Obj: OpenDlg.C
 Wcl386 $(C_SW)-fo=$*.Obj OpenDlg.C

ROPs.Obj: ROPs.C
 Wcl386 $(C_SW)-fo=$*.Obj ROPs.C

ROPs.Res: ROPs.Rc
 Rc $(RC_SW) ROPs.Rc $*.Res

ROPsWnd.Obj: ROPsWnd.C
 Wcl386 $(C_SW)-fo=$*.Obj ROPsWnd.C

Support.Obj: Support.C
 Wcl386 $(C_SW)-fo=$*.Obj Support.C

ViewDlg.Obj: ViewDlg.C
 Wcl386 $(C_SW)-fo=$*.Obj ViewDlg.C

