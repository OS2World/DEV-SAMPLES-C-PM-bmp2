
# MAKE file for Borland.MAK

# Revised:  1995-11-02

# Macro definitions

C_SW=-Ox -v- -w -c 
RC_SW=-r 


ROPs.Exe: AppDefs.Obj GetBmp.Obj OpenDlg.Obj\
        ROPs.Obj ROPs.Res ROPsWnd.Obj\
        Support.Obj ViewDlg.Obj
 TLink @Borland.Lnk
 rc ROPs.Res ROPs.Exe

AppDefs.Obj: AppDefs.C
 Bcc $(C_SW)-o$*.Obj AppDefs.C

GetBmp.Obj: GetBmp.C
 Bcc $(C_SW)-o$*.Obj GetBmp.C

OpenDlg.Obj: OpenDlg.C
 Bcc $(C_SW)-o$*.Obj OpenDlg.C

ROPs.Obj: ROPs.C
 Bcc $(C_SW)-o$*.Obj ROPs.C

ROPs.Res: ROPs.Rc
 Rc $(RC_SW) ROPs.Rc $*.Res

ROPsWnd.Obj: ROPsWnd.C
 Bcc $(C_SW)-o$*.Obj ROPsWnd.C

Support.Obj: Support.C
 Bcc $(C_SW)-o$*.Obj Support.C

ViewDlg.Obj: ViewDlg.C
 Bcc $(C_SW)-o$*.Obj ViewDlg.C

