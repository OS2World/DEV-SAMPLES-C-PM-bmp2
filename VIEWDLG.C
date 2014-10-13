#pragma	title("ROP Viewer  --  Version 1  --  (ViewDlg.C)")
#pragma	subtitle("   Module Purpose - Interface Definitions")

#define	INCL_GPI		   /* Include OS/2 PM GPI Interface	*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <malloc.h>
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>

#include "appdefs.h"
#include "rops.h"

/* This	module contains	routine	used to	handle the main	application	*/
/* client window.							*/

/* Filename:   ViewDlg.C						*/

/*  Version:   1							*/
/*  Created:   1995-08-06						*/
/*  Revised:   1995-10-02						*/

/* Routines:   MRESULT EXPENTRY	ViewDlgProc(HWND hWnd, ULONG msg,	*/
/*					    MPARAM mp1,	MPARAM mp2);	*/


/************************************************************************/
/************************************************************************/
/************************************************************************/
/* DISCLAIMER OF WARRANTIES:						*/
/* -------------------------						*/
/* The following [enclosed] code is sample code	created	by IBM		*/
/* Corporation and Prominare Inc.  This	sample code is not part	of any	*/
/* standard IBM	product	and is provided	to you solely for the purpose	*/
/* of assisting	you in the development of your applications.  The code	*/
/* is provided "AS IS",	without	warranty of any	kind.  Neither IBM nor	*/
/* Prominare shall be liable for any damages arising out of your	*/
/* use of the sample code, even	if they	have been advised of the	*/
/* possibility of such damages.						*/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*		       D I S C L A I M E R				*/
/* This	code is	provided on an as is basis with	no implied support.	*/
/* It should be	considered freeware that cannot	be rebundled as		*/
/* part	of a larger "*ware" offering without our consent.		*/
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Copyright ¸ International Business Machines Corp., 1995.		*/
/* Copyright ¸ 1995  Prominare Inc.  All Rights	Reserved.		*/

/* --------------------------------------------------------------------	*/

#define	ROP_SOURCE	   0xcc	   /* 1	1 0 0 1	1 0 0  */
#define	ROP_PATTERN	   0xf0	   /* 1	1 1 1 0	0 0 0  */
#define	ROP_DESTINATION	   0xaa	   /* 1	0 1 0 1	0 1 0  */

LONG  alROP[12];

PSZ  apszROPs[ ] = {
"ROP00 ",
"ROP01 DPSoon",
"ROP02 DPSona",
"ROP03 PSon",
"ROP04 SDPona",
"ROP05 DPon",
"ROP06 PDSxnon",
"ROP07 PDSaon",
"ROP08 SDPnaa",
"ROP09 PDSxon",
"ROP0A DPna",
"ROP0B PSDnaon",
"ROP0C SPna",
"ROP0D PDSnaon",
"ROP0E PDSonon",
"ROP0F Pn",
"ROP10 PDSona",
"ROP11 DSon",
"ROP12 SDPxnon",
"ROP13 SDPaon",
"ROP14 DPSxnon",
"ROP15 DPSaon",
"ROP16 PSDPSanaxx",
"ROP17 SSPxDSxaxn",
"ROP18 SPxPDxa",
"ROP19 SDPSanaxn",
"ROP1A PDSPaox",
"ROP1B SDPSxaxn",
"ROP1C PSDPaox",
"ROP1D DSPDxaxn",
"ROP1E PDSox",
"ROP1F PDSoan",
"ROP20 DPSnaa",
"ROP21 SDPxon",
"ROP22 DSna",
"ROP23 SPDnaon",
"ROP24 SPxDSxa",
"ROP25 PDSPanaxn",
"ROP26 SDPSaox",
"ROP27 SDPSxnox",
"ROP28 DPSxa",
"ROP29 PSDPSaoxxn",
"ROP2A DPSana",
"ROP2B SSPxPDxaxn",
"ROP2C SPDSoax",
"ROP2D PSDnox",
"ROP2E PSDPxox",
"ROP2F PSDnoan",
"ROP30 PSna",
"ROP31 SDPnaon",
"ROP32 SDPSoox",
"ROP33 Sn",
"ROP34 SPDSaox",
"ROP35 SPDSxnox",
"ROP36 SDPox",
"ROP37 SDPoan",
"ROP38 PSDPoax",
"ROP39 SPDnox",
"ROP3A SPDSxox",
"ROP3B SPDnoan",
"ROP3C PSx",
"ROP3D SPDSonox",
"ROP3E SPDSnaox",
"ROP3F PSan",
"ROP40 PSDnaa",
"ROP41 DPSxon",
"ROP42 SDxPDxa",
"ROP43 SPDSanaxn",
"ROP44 SDna",
"ROP45 DPSnaon",
"ROP46 DSPDaox",
"ROP47 PSDPxaxn",
"ROP48 SDPxa",
"ROP49 PDSPDaoxxn",
"ROP4A DPSDoax",
"ROP4B PDSnox",
"ROP4C SPDana",
"ROP4D SSPxDSxoxn",
"ROP4E PDSPxox",
"ROP4F PDSnoan",
"ROP50 PDna",
"ROP51 DSPnaon",
"ROP52 DPSDaox",
"ROP53 SPDSxaxn",
"ROP54 DPSonon",
"ROP55 Dn",
"ROP56 DPSox",
"ROP57 DPSoan",
"ROP58 PDSPoax",
"ROP59 DPSnox",
"ROP5A DPx",
"ROP5B DPSDonox",
"ROP5C DPSDxox",
"ROP5D DPSnoan",
"ROP5E DPSDnaox",
"ROP5F DPan",
"ROP60 PDSxa",
"ROP61 DSPDSaoxxn",
"ROP62 DSPDoax",
"ROP63 SDPnox",
"ROP64 SDPSoax",
"ROP65 DSPnox",
"ROP66 DSx",
"ROP67 SDPSonox",
"ROP68 DSPDSonoxxn",
"ROP69 PDSxxn",
"ROP6A DPSax",
"ROP6B PSDPSoaxxn",
"ROP6C SDPax",
"ROP6D PDSPDoaxxn",
"ROP6E SDPSnoax",
"ROP6F PDSxnan",
"ROP70 PDSana",
"ROP71 SSDxPDxaxn",
"ROP72 SDPSxox",
"ROP73 SDPnoan",
"ROP74 DSPDxox",
"ROP75 DSPnoan",
"ROP76 SDPSnaox",
"ROP77 DSan",
"ROP78 PDSax",
"ROP79 DSPDSoaxxn",
"ROP7A DPSDnoax",
"ROP7B SDPxnan",
"ROP7C SPDSnoax",
"ROP7D DPSxnan",
"ROP7E SPxDSxo",
"ROP7F DPSaan",
"ROP80 DPSaa",
"ROP81 SPxDSxon",
"ROP82 DPSxna",
"ROP83 SPDSnoaxn",
"ROP84 SDPxna",
"ROP85 PDSPnoaxn",
"ROP86 DSPDSoaxx",
"ROP87 PDSaxn",
"ROP88 DSa",
"ROP89 SDPSnaoxn",
"ROP8A DSPnoa",
"ROP8B DSPDxoxn",
"ROP8C SDPnoa",
"ROP8D SDPSxoxn",
"ROP8E SSDxPDxax",
"ROP8F PDSanan",
"ROP90 PDSxna",
"ROP91 SDPSnoaxn",
"ROP92 DPSDPoaxx",
"ROP93 SPDaxn",
"ROP94 PSDPSoaxx",
"ROP95 DPSaxn",
"ROP96 DPSxx",
"ROP97 PSDPSonoxx",
"ROP98 SDPSonoxn",
"ROP99 DSxn",
"ROP9A DPSnax",
"ROP9B SDPSoaxn",
"ROP9C SPDnax",
"ROP9D DSPDoaxn",
"ROP9E DSPDSaoxx",
"ROP9F PDSxan",
"ROPA0 DPa",
"ROPA1 PDSPnaoxn",
"ROPA2 DPSnoa",
"ROPA3 DPSDxoxn",
"ROPA4 PDSPonoxn",
"ROPA5 PDxn",
"ROPA6 DSPnax",
"ROPA7 PDSPoaxn",
"ROPA8 DPSoa",
"ROPA9 DPSoxn",
"ROPAA D",
"ROPAB DPSono",
"ROPAC SPDSxax",
"ROPAD DPSDaoxn",
"ROPAE DSPnao",
"ROPAF DPno",
"ROPB0 PDSnoa",
"ROPB1 PDSPxoxn",
"ROPB2 SSPxDSxox",
"ROPB3 SDPanan",
"ROPB4 PSDnax",
"ROPB5 DPSDoaxn",
"ROPB6 DPSDPaoxx",
"ROPB7 SDPxan",
"ROPB8 PSDPxax",
"ROPB9 DSPDaoxn",
"ROPBA DPSnao",
"ROPBB DSno",
"ROPBC SPDSanax",
"ROPBD SDxPDxan",
"ROPBE DPSxo",
"ROPBF DPSano",
"ROPC0 PSa",
"ROPC1 SPDSnaoxn",
"ROPC2 SPDSonoxn",
"ROPC3 PSxn",
"ROPC4 SPDnoa",
"ROPC5 SPDSxoxn",
"ROPC6 SDPnax",
"ROPC7 PSDPoaxn",
"ROPC8 SDPoa",
"ROPC9 SPDoxn",
"ROPCA DPSDxax",
"ROPCB SPDSaoxn",
"ROPCC S",
"ROPCD SDPono",
"ROPCE SDPnao",
"ROPCF SPno",
"ROPD0 PSDnoa",
"ROPD1 PSDPxoxn",
"ROPD2 PDSnax",
"ROPD3 SPDSoaxn",
"ROPD4 SSPxPDxax",
"ROPD5 DPSanan",
"ROPD6 PSDPSaoxx",
"ROPD7 DPSxan",
"ROPD8 PDSPxax",
"ROPD9 SDPSaoxn",
"ROPDA DPSDanax",
"ROPDB SPxDSxan",
"ROPDC SPDnao",
"ROPDD SDno",
"ROPDE SDPxo",
"ROPDF SDPano",
"ROPE0 PDSoa",
"ROPE1 PDSoxn",
"ROPE2 DSPDxax",
"ROPE3 PSDPaoxn",
"ROPE4 SDPSxax",
"ROPE5 PDSPaoxn",
"ROPE6 SDPSanax",
"ROPE7 SPxPDxan",
"ROPE8 SSPxDSxax",
"ROPE9 DSPDSanaxxn",
"ROPEA DPSao",
"ROPEB DPSxno",
"ROPEC SDPao",
"ROPED SDPxno",
"ROPEE DSo",
"ROPEF SDPnoo",
"ROPF0 P",
"ROPF1 PDSono",
"ROPF2 PDSnao",
"ROPF3 PSno",
"ROPF4 PSDnao",
"ROPF5 PDno",
"ROPF6 PDSxo",
"ROPF7 PDSano",
"ROPF8 PDSao",
"ROPF9 PDSxno",
"ROPFA DPo",
"ROPFB DPSnoo",
"ROPFC PSo",
"ROPFD PSDnoo",
"ROPFE DPSoo",
"ROPFF"	};

LONG iROPView;
LONG cROPView;
RECTL		 rcl;		   /* Window Rectangle			*/
RECTL		 rclPattern;	   /* Window Rectangle			*/
POINTL		 aptl[4];	   /* Display Points			*/
BOOL fClr = TRUE;
POINTL aptlPattern[2];

LONG alPattern[	] = { PATSYM_DENSE1, PATSYM_DENSE2, PATSYM_DENSE3, PATSYM_DENSE4, PATSYM_DENSE5, PATSYM_DENSE6,	PATSYM_DENSE7,
		      PATSYM_DENSE8, PATSYM_VERT, PATSYM_HORIZ,	PATSYM_DIAG1, PATSYM_DIAG2, PATSYM_DIAG3, PATSYM_DIAG4,	PATSYM_NOSHADE,
		      PATSYM_SOLID, PATSYM_HALFTONE, PATSYM_HATCH, PATSYM_DIAGHATCH, PATSYM_BLANK };

ULONG ulPatternTable[ ]	= { 0x00010001,	0x00020001, 0x00030001,	0x00040001, 0x00050001,
			    0x00010002,	0x00020002, 0x00030002,	0x00040002, 0x00050002,
			    0x00010003,	0x00020003, 0x00030003,	0x00040003, 0x00050003,
			    0x00010004,	0x00020004, 0x00030004,	0x00040004, 0x00050004 };

#pragma	subtitle("   Module Purpose - Dialog Procedure")
#pragma	page( )

/* --- ViewROPDlgProc ---------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages for the dialog	*/
/*     procedure.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Dialog Window Handle				*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ViewROPDlgProc =	Message	Handling Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

LONG cBuildROPList(const PSZ pszROP, const LONG	lROP)

{
CHAR szOpAnd[12];		   /* Operation				*/
CHAR szOpCode[12];		   /* Operation	code			*/
PCHAR pch;			   /* String Position			*/
LONG  lValue1;			   /* Value Holder			*/
register INT i,	k, n;		   /* Indices				*/

if ( (pch = strpbrk(pszROP, "oxan")) !=	NULL )
   {
   memcpy(szOpCode, pszROP, (UINT)(n = (INT)(pch - pszROP)));
   for ( i = n - 1, k =	0; i >=	0; i--,	k++ )
       szOpAnd[k] = szOpCode[i];
   szOpAnd[n] =	(CHAR)0;
   strcpy(szOpCode, pch++);
   if (	(*pch == 'P') || (*pch == 'S') || (*pch	== 'D')	)
       {
       alROP[0]	= lROP;
       return(1);
       }
   }
i = k =	n = 0;

switch ( szOpAnd[i++] )
   {
   case	'D' :
       lValue1 = ROP_DESTINATION;
       break;
   case	'P' :
       lValue1 = ROP_PATTERN;
       break;
   case	'S' :
       lValue1 = ROP_SOURCE;
       break;
   }

while (	szOpCode[k] )
   {
   switch ( szOpCode[k++] )
       {
       case 'o'	:
	   switch ( szOpAnd[i++] )
	       {
	       case 'D'	:
		   lValue1 |= ROP_DESTINATION;
		   break;
	       case 'P'	:
		   lValue1 |= ROP_PATTERN;
		   break;
	       case 'S'	:
		   lValue1 |= ROP_SOURCE;
		   break;
	       }
	   break;

       case 'x'	:
	   switch ( szOpAnd[i++] )
	       {
	       case 'D'	:
		   lValue1 ^= ROP_DESTINATION;
		   break;
	       case 'P'	:
		   lValue1 ^= ROP_PATTERN;
		   break;
	       case 'S'	:
		   lValue1 ^= ROP_SOURCE;
		   break;
	       }
	   break;

       case 'a'	:
	   switch ( szOpAnd[i++] )
	       {
	       case 'D'	:
		   lValue1 &= ROP_DESTINATION;
		   break;
	       case 'P'	:
		   lValue1 &= ROP_PATTERN;
		   break;
	       case 'S'	:
		   lValue1 &= ROP_SOURCE;
		   break;
	       }
	   break;

       case 'n'	:
	   lValue1 = ~lValue1 &	0x000000ff;
	   break;
       }

   alROP[n++] =	lValue1;
   }

return(n);
}
#pragma	subtitle("   Module Purpose - Dialog Procedure")
#pragma	page( )

/* --- ViewROPDlgProc ---------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages for the dialog	*/
/*     procedure.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Dialog Window Handle				*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ViewROPDlgProc =	Message	Handling Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY ViewROPDlgProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
HPS		 hPS;		   /* Presentation Space Handle		*/
BITMAPINFOHEADER bmp;		   /* Bitmap Information Header		*/
MRESULT		 mr;		   /* Message Return			*/
LONG		 lClr;		   /* RGB Colour			*/
register INT i;			   /* Loop Counter			*/

switch ( msg )
   {

/************************************************************************/
/* Perform dialog initialization					*/
/************************************************************************/

   case	WM_INITDLG :
       WinSetDlgItemText(hWnd, IT_ROPSELECTED, apszROPs[lRop]);
       WinSendDlgItemMsg(hWnd, CB_CLEARBACKGROUND, BM_SETCHECK,	MPFROMLONG(fClr), 0L);
       if ( (lRop == 0L) || (lRop == 255L) )
	   for ( i = cROPView =	0; i < 7; i++ )
	       WinEnableWindow(WinWindowFromID(hWnd, PB_VIEW1 +	i), FALSE);
       else
	   {
	   for ( i = cROPView =	cBuildROPList(&apszROPs[lRop][6], lRop); i < 7;	i++ )
	       WinEnableWindow(WinWindowFromID(hWnd, PB_VIEW1 +	i), FALSE);
	   WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView	= 0L]][6]);
	   }
       WinQueryWindowRect(hWnd,	&rcl);

       GpiQueryBitmapParameters(hbmView, &bmp);

       aptl[0].x = rcl.xRight -	bmp.cx - 15L;
       aptl[0].y = (rcl.yTop - rcl.yBottom) / 2L - bmp.cy / 2L;
       aptl[1].x = rcl.xRight -	15L;
       aptl[1].y = aptl[0].y + bmp.cy;

       aptl[2].x = aptl[2].y = 0L;
       aptl[3].x = bmp.cx;
       aptl[3].y = bmp.cy;

       rcl.xLeft   = aptl[0].x;
       rcl.xRight -= 14L;
       rcl.yBottom = aptl[0].y;
       rcl.yTop	   = aptl[1].y + 1L;

       rclPattern.xLeft	 = (aptlPattern[0].x = rcl.xLeft - 70L)	- 1L;
       rclPattern.xRight = (aptlPattern[1].x = rcl.xLeft - 50L)	+ 1L;
       rclPattern.yBottom = aptlPattern[0].y = rcl.yBottom;
       rclPattern.yTop = aptlPattern[1].y = rcl.yTop;
       break;

/************************************************************************/
/* Process control selections						*/
/************************************************************************/

   case	WM_CONTROL :
       switch (	SHORT2FROMMP(mp1) )
	   {

/************************************************************************/
/* Button clicked notification						*/
/************************************************************************/

	   case	BN_CLICKED :
	       switch (	SHORT1FROMMP(mp1) )
		   {
		   case	CB_CLEARBACKGROUND :
		       fClr = (BOOL)LONGFROMMR(WinSendDlgItemMsg(hWnd, CB_CLEARBACKGROUND,
								 BM_QUERYCHECK,	0L, 0L));
		       break;
		   }
	       break;
	   }
       break;

/************************************************************************/
/* Process push	button selections					*/
/************************************************************************/

   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	PB_BACKGROUND :
	       iROPView	= -1;
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW7 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 6]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW6 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 5]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW5 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 4]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW4 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 3]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW3 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 2]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW2 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 1]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	PB_VIEW1 :
	       WinSetDlgItemText(hWnd, IT_ROPVIEW, &apszROPs[alROP[iROPView = 0]][6]);
	       WinInvalidateRect(hWnd, &rcl, FALSE);
	       break;
	   case	DID_OPTIONS :
	       if ( WinDlgBox(HWND_DESKTOP, hwndROPsFrame, (PFNWP)OptionsDlgProc,
			      (HMODULE)NULL, DLG_OPTIONS, NULL)	)
		   {
		   WinInvalidateRect(hWnd, &rcl, FALSE);
		   WinInvalidateRect(hWnd, &rclPattern,	FALSE);
		   }
	       break;

	   case	DID_OK :
	       WinDismissDlg(hWnd, TRUE);
	       break;

	   }
       break;

   case	WM_PAINT :
       mr = WinDefDlgProc(hWnd,	msg, mp1, mp2);
       hPS = WinGetPS(hWnd);
       if ( fClr )
	   lClr	= GpiQueryRGBColor(hPS,	LCOLOPT_REALIZED, lFillColour);
       GpiCreateLogColorTable(hPS, 0L, LCOLF_RGB, 0L, 0L, (PLONG)NULL);

       GpiSetPattern(hPS, lPattern);
       GpiMove(hPS, aptlPattern);
       GpiBox(hPS, DRO_FILL, &aptlPattern[1], 0L, 0L);

       if ( fClr )
	   WinFillRect(hPS, &rcl, lClr);
       if ( iROPView > -1 )
	   GpiWCBitBlt(hPS, hbmView, 4L, aptl, alROP[iROPView],	BBO_IGNORE);
       WinReleasePS(hPS);
       return(mr);

/************************************************************************/
/* Close requested, exit dialogue					*/
/************************************************************************/

   case	WM_CLOSE :
       WinDismissDlg(hWnd, FALSE);
       break;

			/* Pass	through	unhandled messages		*/
   default :
       return(WinDefDlgProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
#pragma	subtitle("   Module Purpose - Dialog Procedure")
#pragma	page( )

/* --- OptionsDlgProc ---------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages for the dialogue	*/
/*     procedure.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Dialog Window Handle				*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     OptionsDlgProc =	Message	Handling Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY OptionsDlgProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
POWNERITEM poi;			   /* Owner Item Pointer		*/
HPS  hPS;			   /* Presentation Space Handle		*/
LONG lClr;
POINTL ptl;			   /* Drawing Point			*/
register INT i,	n;		   /* Loop Counter			*/


switch ( msg )
   {

/************************************************************************/
/* Perform dialog initialization					*/
/************************************************************************/

   case	WM_INITDLG :
       for ( i = 0; i <	20; i++	)
	   WinSendDlgItemMsg(hWnd, VS_PATTERNS,	VM_SETITEMATTR,	MPFROMLONG(ulPatternTable[i]),
			     MPFROM2SHORT(VIA_TEXT | VIA_OWNERDRAW, TRUE));
       switch (	lPattern )
	   {
	   case	PATSYM_DENSE1 :
	   case	PATSYM_DENSE2 :
	   case	PATSYM_DENSE3 :
	   case	PATSYM_DENSE4 :
	   case	PATSYM_DENSE5 :
	   case	PATSYM_DENSE6 :
	   case	PATSYM_DENSE7 :
	   case	PATSYM_DENSE8 :
	   case	PATSYM_VERT :
	   case	PATSYM_HORIZ :
	   case	PATSYM_DIAG1 :
	   case	PATSYM_DIAG2 :
	   case	PATSYM_DIAG3 :
	   case	PATSYM_DIAG4 :
	   case	PATSYM_NOSHADE :
	   case	PATSYM_SOLID :
	   case	PATSYM_HALFTONE	:
	   case	PATSYM_HATCH :
	   case	PATSYM_DIAGHATCH :
	       WinSendDlgItemMsg(hWnd, VS_PATTERNS, VM_SELECTITEM, MPFROMLONG(ulPatternTable[lPattern -	1]), 0L);
	       break;

	   case	PATSYM_BLANK :
	       WinSendDlgItemMsg(hWnd, VS_PATTERNS, VM_SELECTITEM, MPFROMLONG(ulPatternTable[19]), 0L);
	       break;
	   }

       for ( i = 1, lClr = CLR_WHITE; i	<= 3; i++ )
	   for ( n = 1;	n <= 6;	n++ )
	       {
	       WinSendDlgItemMsg(hWnd, VS_COLOURS, VM_SETITEM,
				 MPFROM2SHORT(i, n), MPFROMLONG(lClr));
	       if ( lFillColour	== lClr++ )
		   WinSendDlgItemMsg(hWnd, VS_COLOURS, VM_SELECTITEM, MPFROM2SHORT(i, n), 0L);
	       }
       break;

/************************************************************************/
/* Close requested, exit dialogue					*/
/************************************************************************/

   case	WM_CLOSE :
       WinDismissDlg(hWnd, FALSE);
       break;

/************************************************************************/
/* Process push	button selections					*/
/************************************************************************/

   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	DID_CANCEL :
	       WinDismissDlg(hWnd, FALSE);
	       break;
	   case	DID_OK :
	       i = (INT)LONGFROMMR(WinSendDlgItemMsg(hWnd, VS_PATTERNS,	VM_QUERYSELECTEDITEM, 0L, 0L));
	       lPattern	= alPattern[(LOUSHORT(i) - 1) *	5 + (HIUSHORT(i) - 1)];
	       i = (INT)LONGFROMMR(WinSendDlgItemMsg(hWnd, VS_COLOURS, VM_QUERYSELECTEDITEM, 0L, 0L));
	       lFillColour = (LOUSHORT(i) - 1) * 6 + HIUSHORT(i) - 1 + CLR_WHITE;
	       WinDismissDlg(hWnd, TRUE);
	       break;

	   }
       break;

/************************************************************************/
/* Process control selections						*/
/************************************************************************/

   case	WM_CONTROL :
       switch (	SHORT2FROMMP(mp1) )
	   {
	   }
       break;

/************************************************************************/
/* Draw	a list box item							*/
/************************************************************************/

   case	WM_DRAWITEM :
		       /* Point	to Owner Item information	       */

       poi = (POWNERITEM)mp2;
       if ( poi->idItem	== VDA_ITEM )
	   {
	   ptl.x = poi->rclItem.xLeft +	1L;
	   ptl.y = poi->rclItem.yBottom	+ 1L;
	   i = (LOUSHORT(poi->hItem) - 1) * 5 +	(HIUSHORT(poi->hItem) -	1);
	   GpiSetPattern(poi->hps, alPattern[(LOUSHORT(poi->hItem) - 1)	* 5 + (HIUSHORT(poi->hItem) - 1)]);
	   GpiMove(poi->hps, &ptl);
	   ptl.x = poi->rclItem.xRight - 1L;
	   ptl.y = poi->rclItem.yTop - 1L;
	   GpiBox(poi->hps, DRO_FILL, &ptl, 0L,	0L);
	   return(MRFROMLONG(TRUE));
	   }
       return(0L);

/************************************************************************/
/************************************************************************/

   case	WM_MEASUREITEM :
		       /* Return height	of list	box item.  The extents */
		       /* for the list box item	is derived from	the    */
		       /* maximum baseline extents of the system font  */
		       /* queried through the initialization routines. */

       return(MRFROMLONG(15));

			/* Pass	through	unhandled messages		*/
   default :
       return(WinDefDlgProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
