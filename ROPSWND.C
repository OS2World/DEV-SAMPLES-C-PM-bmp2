#pragma	title("ROP Viewer  --  Version 1  --  (ROPsWnd.C)")
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

/* Filename:   ROPsWnd.C						*/

/*  Version:   1							*/
/*  Created:   1995-08-06						*/
/*  Revised:   1995-08-14						*/

/* Routines:   static VOID CreateROPBitmap(HWND	hWnd);			*/
/*	       static VOID SizeBitmap(HWND hWnd);			*/
/*	       static VOID SizeBitmapStack(HWND	hWnd);			*/
/*	       MRESULT EXPENTRY	ROPsTestWndProc(HWND hWnd, ULONG msg,	*/
/*						MPARAM mp1, MPARAM mp2);*/


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

HBITMAP	hbmROP = 0;		   /* Bitmap Handle			*/
LONG	lScale = 100L;		   /* Scale Factor			*/
RECTL	rclDest;		   /* Destination Rectangle		*/
RECTL	rclImage;		   /* Image Rectangle			*/
POINTL	aptlArea[8];		   /* Shadow Points			*/
RECTL	rclROP;			   /* ROP Image	Rectangle		*/
LONG	cxROP;			   /* ROP Image	Width			*/
LONG	cyROP;			   /* ROP Image	Height			*/
LONG	cxImage;		   /* Bitmap Image Width		*/
LONG	cyImage;		   /* Bitmap Image Height		*/
LONG	lHorzRange;		   /* Horizontal Scroll	Bar Range	*/
LONG	lVertRange;		   /* Vertical Scroll Bar Range		*/
LONG	lHorzPos;		   /* Horizontal Scroll	Bar Position	*/
LONG	lVertPos;		   /* Vertical Scroll Bar Position	*/
LONG	cxWindow;		   /* Window Width			*/
LONG	cyWindow;		   /* Window Height			*/

LONG	iImage;			   /* Bitmap Image Index		*/

BOOL	fBitmapArray = TRUE;	   /* Bitmap Array Display Flag		*/

HWND	hwndHScroll;
HWND	hwndVScroll;

static VOID CreateROPBitmap(HWND hWnd);
static VOID SizeBitmap(HWND hWnd);
static VOID SizeBitmapStack(HWND hWnd);

#pragma	subtitle("   Module Purpose - Bitmap Sizing Function")
#pragma	page( )

/* --- CreateROPBitmap --------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	create the array of ROP	images.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     Nothing								*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID CreateROPBitmap(HWND hWnd)

{
BITMAPINFOHEADER  bmp;		   /* Bitmap Information Header		*/
BITMAPINFOHEADER2 bminfo2;	   /* Bitmap Information Header		*/
HBITMAP		  hbmConstruct;	   /* Bitmap Handle			*/
HDC		  hDC;		   /* Device Context Handle		*/
HPS		  hpsBitmap;	   /* Bitmap Presentation Space	Handle	*/
LONG		  cFormats;	   /* Formats Count			*/
LONG		  lROP = 0L;	   /* ROP Value				*/
PLONG		  plFormats;	   /* Formats Array			*/
POINTL		  aptl[4];	   /* Conversion Point			*/
RECTL		  rcl;		   /* Window Rectangle			*/
SIZEL		  sizl;		   /* Sizing Structure			*/
register INT i,	n;		   /* Loop Counters			*/

if ( hbmROP )
   GpiDeleteBitmap(hbmROP);

GpiQueryBitmapParameters(hbmView, &bmp);

		       /* Get bitmap device context handle for the main	*/
		       /* Client Window					*/

if ( !(hDC = DevOpenDC(hAB, OD_MEMORY, "*", 0L,	0L, 0L)) )
   return((HBITMAP)NULL);
		       /* Create bitmap	presentation space specifying	*/
		       /* entire map Client Window for size required	*/

WinQueryWindowRect(hWnd, &rcl);
lHorzRange = (cxROP = sizl.cx =	bmp.cx * 16L + 150L) - (cxWindow = rcl.xRight -	rcl.xLeft);
lVertRange = (cyROP = sizl.cy =	bmp.cy * 16L + 150L) - (cyWindow = rcl.yTop - rcl.yBottom);

WinSendMsg(hwndVScroll,	SBM_SETSCROLLBAR, MPFROMSHORT(lVertPos),
	   MPFROM2SHORT(0, lVertRange));
WinSendMsg(hwndVScroll,	SBM_SETTHUMBSIZE, MPFROM2SHORT(cyWindow, cyROP), 0L);

WinSendMsg(hwndHScroll,	SBM_SETSCROLLBAR, MPFROMSHORT(lHorzPos),
	   MPFROM2SHORT(0, lHorzRange));
WinSendMsg(hwndHScroll,	SBM_SETTHUMBSIZE, MPFROM2SHORT(cxWindow, cxROP), 0L);

rclROP.xLeft   = 0L;
rclROP.yBottom = cyROP - cyWindow;
rclROP.xRight  = cxWindow;
rclROP.yTop    = cyROP;

cxImage	= bmp.cx + 10L;
cyImage	= bmp.cy + 10L;

if ( !(hpsBitmap = GpiCreatePS(hAB, hDC, &sizl,	PU_PELS	| GPIT_NORMAL |	GPIA_ASSOC)) )
   {
		       /* Error	occurred during	creation of		*/
		       /* presentation space, close device context	*/
   DevCloseDC(hDC);
   return((HBITMAP)NULL);
   }
		       /* Get the number of bitmap formats that	the	*/
		       /* display driver supports			*/

DevQueryCaps(hDC, CAPS_BITMAP_FORMATS, 1L, &cFormats);

		       /* Get the bitmap display formats.  The first	*/
		       /* set within the array will be the one that	*/
		       /* most closely matches the display device.	*/

GpiQueryDeviceBitmapFormats(hpsBitmap, cFormats	* 2L,
			    plFormats =	(PLONG)malloc(2UL * cFormats * sizeof(LONG)));

		       /* Create actual	bitmap storage for colour wheel	*/
		       /* having the default plane and bit count	*/

memset(&bminfo2, 0, sizeof(BITMAPINFOHEADER2));
bminfo2.cbFix	  = sizeof(BITMAPINFOHEADER2);
bminfo2.cx	  = (ULONG)sizl.cx;
bminfo2.cy	  = (ULONG)sizl.cy;
bminfo2.cPlanes	  = (USHORT)plFormats[0];
bminfo2.cBitCount = (USHORT)plFormats[1];

free(plFormats);

if ( !(hbmConstruct = GpiCreateBitmap(hpsBitmap, &bminfo2, 0L, 0L, 0L))	)
   {
		       /* Error	occurred during	creation of bitmap	*/
		       /* storage, destroy presentation	space created	*/
		       /* and close device context opened		*/

   GpiDestroyPS(hpsBitmap);
   DevCloseDC(hDC);
   return((HBITMAP)NULL);
   }
		       /* Set bitmap as	current	bitmap to use		*/

GpiSetBitmap(hpsBitmap,	hbmConstruct);

		       /* Draw the page					*/
GpiErase(hpsBitmap);

aptl[0].x = 0L;
aptl[0].y = sizl.cy - bmp.cy;
aptl[1].x = bmp.cx;
aptl[1].y = sizl.cy;

aptl[2].x = aptl[2].y =	0L;
aptl[3].x = bmp.cx;
aptl[3].y = bmp.cy;

GpiSetPattern(hpsBitmap, lPattern);

for ( i	= 0; i < 16; i++ )
   {
   for ( n = 0;	n < 16;	n++ )
       {
       rcl.xLeft   = aptl[0].x;
       rcl.xRight  = aptl[1].x + 1L;
       rcl.yBottom = aptl[0].y;
       rcl.yTop	   = aptl[1].y + 1L;
       WinFillRect(hpsBitmap, &rcl, lFillColour);
       GpiWCBitBlt(hpsBitmap, hbmView, 4L, aptl, lROP++, BBO_IGNORE);
       aptl[0].x += (bmp.cx + 10L);
       aptl[1].x += (bmp.cx + 10L);
       }
   aptl[0].y -=	(bmp.cy	+ 10L);
   aptl[1].y -=	(bmp.cy	+ 10L);
   aptl[0].x = 0L;
   aptl[1].x = bmp.cx;
   }
		       /* Set the bitmap to allow completion of	bitmap	*/
		       /* in memory					*/

GpiSetBitmap(hpsBitmap,	(HDC)NULL);

		       /* Destroy the memory device context		*/

GpiAssociate(hpsBitmap,	(HDC)NULL);

		       /* Destroy the presentation spaces used		*/
GpiDestroyPS(hpsBitmap);
DevCloseDC(hDC);
		       /* Return the bitmap handle that	will be	used in	*/
		       /* painting the image on	the window		*/
hbmROP = hbmConstruct;
}
#pragma	subtitle("   Module Purpose - Bitmap Sizing Function")
#pragma	page( )

/* --- SizeBitmap -------------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	size the scaled	bitmap for the window.	*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND hWnd; = Window Handle					*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID SizeBitmap(HWND hWnd)

{
BITMAPINFOHEADER bmp;		   /* Bitmap Information Header		*/
RECTL		 rcl;		   /* Window Rectangle			*/
LONG		 cx;		   /* Bitmap Width			*/
LONG		 cy;		   /* Bitmap Height			*/

WinQueryWindowRect(hWnd, &rcl);

GpiQueryBitmapParameters(hbmView, &bmp);

cx = (bmp.cx * lScale) / 100L;
cy = (bmp.cy * lScale) / 100L;

rclDest.xRight = (rclDest.xLeft	  = ((rcl.xRight - rcl.xLeft) /	2L) - (cx / 2L)) + cx;
rclDest.yTop   = (rclDest.yBottom = ((rcl.yTop - rcl.yBottom) /	2L) - (cy / 2L)) + cy;

rclImage.xRight	= (rclImage.xLeft   = ((rcl.xRight - rcl.xLeft)	/ 2L) -	(bmp.cx	* 4L)) + bmp.cx	* 8L;
rclImage.yTop	= (rclImage.yBottom = ((rcl.yTop - rcl.yBottom)	/ 2L) -	(bmp.cy	* 4L)) + bmp.cy	* 8L;

rclImage.xLeft	 -= 3L;
rclImage.yBottom -= 3L;
rclImage.xRight	 += 3L;
rclImage.yTop	 += 3L;
		       /* Form the final boundary points		*/

aptlArea[0].x =	rclDest.xLeft  - 2L;
aptlArea[0].y =	rclDest.yTop   + 2L;
aptlArea[1].x =	rclDest.xRight + 2L;
aptlArea[1].y =	rclDest.yTop   + 2L;

aptlArea[2].x =	rclDest.xRight	+ 2L;
aptlArea[2].y =	rclDest.yBottom	- 2L;
aptlArea[3].x =	rclDest.xLeft	- 2L;
aptlArea[3].y =	rclDest.yBottom	- 2L;

aptlArea[4].x =	rclDest.xLeft  - 1L;
aptlArea[4].y =	rclDest.yTop   + 1L;
aptlArea[5].x =	rclDest.xRight + 1L;
aptlArea[5].y =	rclDest.yTop   + 1L;

aptlArea[6].x =	rclDest.xRight	+ 1L;
aptlArea[6].y =	rclDest.yBottom	- 1L;
aptlArea[7].x =	rclDest.xLeft	- 1L;
aptlArea[7].y =	rclDest.yBottom	- 1L;
}
#pragma	subtitle("   Module Purpose - Bitmap Stack Sizing Function")
#pragma	page( )

/* --- SizeBitmapStack --------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	calculate the size and position	of	*/
/*     the bitmaps from	the bitmap array for the window.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND hWnd; = Window Handle					*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID SizeBitmapStack(HWND hWnd)

{
BITMAPINFOHEADER bmp;		   /* Bitmap Information Header		*/
RECTL		 rcl;		   /* Window Rectangle			*/
LONG		 cx;		   /* Bitmap Width			*/
LONG		 cy;		   /* Bitmap Height			*/
LONG		 xImage;	   /* Image Starting Point		*/
register INT i;			   /* Loop Counter			*/


WinQueryWindowRect(hWnd, &rcl);
	
for ( i	= 0, cx	= 10 * (cBitmaps - 1), cy = 0L;	i < cBitmaps; i++ )
   {
   GpiQueryBitmapParameters(abm[i].hbm,	&bmp);

   cx += bmp.cx;
   if (	bmp.cy > cy )
       cy = bmp.cy;
   }

rclImage.xRight	= (rclImage.xLeft   = ((rcl.xRight - rcl.xLeft)	/ 2L) -	(cx / 2L)) + cx;
rclImage.yTop	= (rclImage.yBottom = ((rcl.yTop - rcl.yBottom)	/ 2L) -	(cy / 2L)) + cy;

xImage = rclImage.xLeft;

rclImage.xLeft	 -= 3L;
rclImage.yBottom -= 3L;
rclImage.xRight	 += 3L;
rclImage.yTop	 += 3L;

for ( i	= 0; i < cBitmaps; i++ )
   {
   GpiQueryBitmapParameters(abm[i].hbm,	&bmp);

   abm[i].rclDest.xRight = (abm[i].rclDest.xLeft   = xImage) + bmp.cx;
   abm[i].rclDest.yTop	 = (abm[i].rclDest.yBottom = ((rcl.yTop	- rcl.yBottom) / 2L) - (bmp.cy / 2L)) +	bmp.cy;

		       /* Form the final boundary points		*/

   abm[i].aptlArea[0].x	= abm[i].rclDest.xLeft	- 2L;
   abm[i].aptlArea[0].y	= abm[i].rclDest.yTop	+ 2L;
   abm[i].aptlArea[1].x	= abm[i].rclDest.xRight	+ 2L;
   abm[i].aptlArea[1].y	= abm[i].rclDest.yTop	+ 2L;

   abm[i].aptlArea[2].x	= abm[i].rclDest.xRight	 + 2L;
   abm[i].aptlArea[2].y	= abm[i].rclDest.yBottom - 2L;
   abm[i].aptlArea[3].x	= abm[i].rclDest.xLeft	 - 2L;
   abm[i].aptlArea[3].y	= abm[i].rclDest.yBottom - 2L;

   abm[i].aptlArea[4].x	= abm[i].rclDest.xLeft	- 1L;
   abm[i].aptlArea[4].y	= abm[i].rclDest.yTop	+ 1L;
   abm[i].aptlArea[5].x	= abm[i].rclDest.xRight	+ 1L;
   abm[i].aptlArea[5].y	= abm[i].rclDest.yTop	+ 1L;

   abm[i].aptlArea[6].x	= abm[i].rclDest.xRight	 + 1L;
   abm[i].aptlArea[6].y	= abm[i].rclDest.yBottom - 1L;
   abm[i].aptlArea[7].x	= abm[i].rclDest.xLeft	 - 1L;
   abm[i].aptlArea[7].y	= abm[i].rclDest.yBottom - 1L;

   xImage += (bmp.cx + 10L);
   }
}
#pragma	subtitle("   Client Window - Client Window Procedure")
#pragma	page( )

/* --- ROPsTestWndProc --------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages sent to the	*/
/*     applications client window.					*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Window Handle					*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ROPsTestWndProc = Message Handling Result			*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY ROPsTestWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
CHAR			szTitle[300];  /* Title	Bar Text		*/
HPS			hPS;	   /* Presentation Space Handle		*/
LONG			lClrBack;  /* Colour Holder			*/
LONG			lClrFore;  /* Colour Holder			*/
LONG			lScrollInc;/* Scroll Increment			*/
PBITMAPARRAYFILEHEADER	pbafh;	   /* Bitmap Array File	Header Pointer	*/
PBITMAPARRAYFILEHEADER2	pbafh2;	   /* Bitmap Array File	Header Pointer	*/
PBITMAPFILEHEADER	pbfh;	   /* Bitmap File Header Pointer	*/
PBITMAPFILEHEADER2	pbfh2;	   /* Bitmap File Header Pointer	*/
PBITMAPINFO		pbmi;	   /* Bitmap Info Pointer		*/
PBITMAPINFO2		pbmi2;	   /* Bitmap Info Pointer		*/
POINTL			ptl;	   /* Pointer Position			*/
RECTL			rcl;	   /* Window Rectangle			*/
register INT i;			   /* Index				*/

switch ( msg )
   {
/************************************************************************/
/* Window being	created, perform window	initialization			*/
/************************************************************************/

   case	WM_CREATE :

       hptrWait	 = WinQuerySysPointer(HWND_DESKTOP, SPTR_WAIT,	FALSE);
       hptrArrow = WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW,	FALSE);

       cxScreen	= WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);

       hmenuROPs = WinWindowFromID(WinQueryWindow(hWnd,	QW_PARENT), FID_MENU);
       hwndHScroll = WinWindowFromID(WinQueryWindow(hWnd, QW_PARENT), FID_HORZSCROLL);
       hwndVScroll = WinWindowFromID(WinQueryWindow(hWnd, QW_PARENT), FID_VERTSCROLL);

		       /************************************************/
		       /* PDSGetTemplate is used to allow controls in  */
		       /* windows.  Do not remove this function	if you */
		       /* intend to include controls within the	window.*/
		       /************************************************/

       PDSGetTemplate(hWnd, WIN_ROPSTEST);
       break;

/************************************************************************/
/* Window being	sized							*/
/************************************************************************/

   case	WM_SIZE	:
       if ( cBitmaps )
	   SizeBitmapStack(hWnd);

       WinQueryWindowRect(hWnd,	&rcl);

       if ( (lHorzRange	= cxROP	- (cxWindow = rcl.xRight - rcl.xLeft)) < 0L )
	   {
	   lHorzRange =	0L;
	   rclROP.xLeft	 = 0L;
	   rclROP.xRight = cxROP;
	   }
       else
	   rclROP.xRight = rclROP.xLeft	+ cxWindow;
       if ( (lVertRange	= cyROP	- (cyWindow = rcl.yTop - rcl.yBottom)) < 0L )
	   {
	   lVertRange =	0L;
	   rclROP.yBottom  = 0L;
	   rclROP.yTop	   = cyROP;
	   }
       else
	   rclROP.yBottom = (rclROP.yTop = cyROP - lVertPos) - cyWindow;

       WinSendMsg(hwndVScroll, SBM_SETSCROLLBAR, MPFROMSHORT(lVertPos),
		  MPFROM2SHORT(0, lVertRange));
       WinSendMsg(hwndVScroll, SBM_SETTHUMBSIZE, MPFROM2SHORT(cyWindow,	cyROP),	0L);

       WinSendMsg(hwndHScroll, SBM_SETSCROLLBAR, MPFROMSHORT(lHorzPos),
		  MPFROM2SHORT(0, lHorzRange));
       WinSendMsg(hwndHScroll, SBM_SETTHUMBSIZE, MPFROM2SHORT(cxWindow,	cxROP),	0L);
       WinInvalidateRect(hWnd, NULL, FALSE);
       break;

/************************************************************************/
/* Perform menu	initialization						*/
/************************************************************************/

   case	WM_INITMENU :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	IDM_DISPLAY :
	       WinSendMsg(hmenuROPs, MM_SETITEMATTR, MPFROM2SHORT(IDM_BITMAPARRAY, TRUE),
			  MPFROM2SHORT(MIA_CHECKED, fBitmapArray ? MIA_CHECKED : 0));
	       WinSendMsg(hmenuROPs, MM_SETITEMATTR, MPFROM2SHORT(IDM_ROPARRAY,	TRUE),
			  MPFROM2SHORT(MIA_CHECKED, fBitmapArray ? 0 : MIA_CHECKED));
	       break;

	   case	IDM_FILE :
	       break;

	   }
       break;

/************************************************************************/
/* Process key press from keyboard					*/
/************************************************************************/

   case	WM_CHAR	:
       if ( CHARMSG(&msg)->fs &	KC_VIRTUALKEY )
	   switch ( CHARMSG(&msg)->vkey	)
	       {
	       case VK_PAGEUP :
		   WinSendMsg(hWnd, WM_VSCROLL,	MPFROMSHORT(FID_VERTSCROLL), MPFROM2SHORT(0, SB_PAGEUP));
		   return(0L);

	       case VK_PAGEDOWN	:
		   WinSendMsg(hWnd, WM_VSCROLL,	MPFROMSHORT(FID_VERTSCROLL), MPFROM2SHORT(0, SB_PAGEDOWN));
		   return(0L);
	       }
		       /************************************************/
		       /* PDSKeyProc is	used to	allow controls in      */
		       /* windows.  Do not remove this function	if you */
		       /* intend to include controls within the	window.*/
		       /************************************************/

       return(PDSKeyProc(hWnd, msg, mp1, mp2));

/************************************************************************/
/* Button 2 being depressed						*/
/************************************************************************/

   case	WM_BUTTON2DOWN :
       if ( !fBitmapArray && hbmROP )
	   {
	   lHorzPos = SHORT1FROMMR(WinSendMsg(hwndHScroll, SBM_QUERYPOS, 0L, 0L));
	   lVertPos = SHORT1FROMMR(WinSendMsg(hwndVScroll, SBM_QUERYPOS, 0L, 0L));

	   lRop	= (lVertPos + (cyWindow	- SHORT2FROMMP(mp1))) /	cyImage	* 16 + (lHorzPos + SHORT1FROMMP(mp1)) /	cxImage;
	   WinDlgBox(HWND_DESKTOP, hwndROPsFrame, (PFNWP)ViewROPDlgProc,
		     (HMODULE)NULL, DLG_VIEWROP, NULL);
	   }
       break;

/************************************************************************/
/* Process vertical scroll requests					*/
/************************************************************************/

   case	WM_VSCROLL :
       lVertPos	= SHORT1FROMMR(WinSendMsg(hwndVScroll, SBM_QUERYPOS, 0L, 0L));
       switch (	HIUSHORT(mp2) )
	   {
	   case	SB_LINEUP :
	       lScrollInc = -cyImage;
	       break;

	   case	SB_LINEDOWN :
	       lScrollInc = cyImage;
	       break;

	   case	SB_PAGEUP :
	       lScrollInc = -cyWindow;
	       break;

	   case	SB_PAGEDOWN :
	       lScrollInc = cyWindow;
	       break;

	   case	SB_SLIDERPOSITION :
	   case	SB_SLIDERTRACK :
	       lScrollInc = SHORT1FROMMP(mp2) -	lVertPos;
	       break;

	   default :
	       return(0L);
	   }

       if ( lScrollInc = max(-lVertPos,	min(lScrollInc,	lVertRange - lVertPos))	)
	   {
	   rclROP.yBottom = (rclROP.yTop = cyROP - (lVertPos +=	lScrollInc)) - cyWindow;
	   WinInvalidateRect(hWnd, NULL, FALSE);
	   WinSendMsg(hwndVScroll, SBM_SETPOS, MPFROM2SHORT(lVertPos, 0), 0L);
	   }
       break;

/************************************************************************/
/* Process horizontal scroll requests					*/
/************************************************************************/

   case	WM_HSCROLL :
       lHorzPos	= SHORT1FROMMR(WinSendMsg(hwndHScroll, SBM_QUERYPOS, 0L, 0L));
       switch (	HIUSHORT(mp2) )
	   {
	   case	SB_LINELEFT :
	       lScrollInc = -cxImage;
	       break;

	   case	SB_LINERIGHT :
	       lScrollInc = cxImage;
	       break;

	   case	SB_PAGELEFT :
	       lScrollInc = -cxWindow;
	       break;

	   case	SB_PAGERIGHT :
	       lScrollInc = cxWindow;
	       break;

	   case	SB_SLIDERPOSITION :
	   case	SB_SLIDERTRACK :
	       lScrollInc = SHORT1FROMMP(mp2) -	lHorzPos;
	       break;

	   default :
	       return(0L);
	   }

       if ( lScrollInc = max(-lHorzPos,	min(lScrollInc,	lHorzRange - lHorzPos))	)
	   {
	   rclROP.xRight = (rclROP.xLeft = (lHorzPos +=	lScrollInc)) + cxWindow;
	   WinInvalidateRect(hWnd, NULL, FALSE);
	   WinSendMsg(hwndHScroll, SBM_SETPOS, MPFROM2SHORT(lHorzPos, 0), 0L);
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
/* Process menu	and button selections					*/
/************************************************************************/

   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	IDM_OPTIONS :
	       if ( WinDlgBox(HWND_DESKTOP, hwndROPsFrame, (PFNWP)OptionsDlgProc,
			      (HMODULE)NULL, DLG_OPTIONS, NULL)	)
		   {
		   WinSetPointer(HWND_DESKTOP, hptrWait);
		   CreateROPBitmap(hWnd);
		   WinInvalidateRect(hWnd, NULL, FALSE);
		   WinSetPointer(HWND_DESKTOP, hptrArrow);
		   }
	       break;
	   case	IDM_OPEN :
	       if ( WinDlgBox(HWND_DESKTOP, hwndROPsFrame, (PFNWP)OpenBitmapDlgProc,
			      (HMODULE)NULL, DLG_OPENBITMAP, NULL) )
		   {
		   WinSetPointer(HWND_DESKTOP, hptrWait);
		   hbmView = hbmGetBitmap(szBitmapFile);
		   SizeBitmap(hWnd);
		   if (	cBitmaps )
		       SizeBitmapStack(hWnd);
		   CreateROPBitmap(hWnd);
		   WinInvalidateRect(hWnd, NULL, FALSE);
		   strcat(memcpy(szTitle, "Bitmap Viewer - ", 17), szBitmapFile);
		   if (	fWindowsBitmap )
		       strcat(szTitle, " [Windows 3.x format]");
		   else
		       if ( f20Bitmap )
			   strcat(szTitle, " [OS/2 2.x format]");
		       else
			   strcat(szTitle, " [OS/2 1.x format]");
		   WinSetWindowText(hwndROPsFrame, szTitle);
		   WinSetPointer(HWND_DESKTOP, hptrArrow);
		   }
	       break;

	   case	IDM_ROPARRAY :
	       fBitmapArray = FALSE;
	       WinInvalidateRect(hWnd, NULL, FALSE);
	       break;

	   case	IDM_BITMAPARRAY	:
	       fBitmapArray = TRUE;
	       WinInvalidateRect(hWnd, NULL, FALSE);
	       break;
	   }
       break;

/************************************************************************/
/* Erase window	background						*/
/************************************************************************/

   case	WM_ERASEBACKGROUND :
       WinQueryWindowRect(hWnd,	&rcl);
       WinFillRect((HPS)LONGFROMMP(mp1), &rcl, CLR_PALEGRAY);
       break;

/************************************************************************/
/* Paint client	window							*/
/************************************************************************/

   case	WM_PAINT :
       GpiCreateLogColorTable(hPS = WinBeginPaint(hWnd,	(HPS)NULL, &rcl), 0UL, LCOLF_RGB, 0L, 0L, (PLONG)NULL);

		       /* Display the bitmap array images side-by-side	*/
       if ( fBitmapArray )
	   {
	   WinFillRect(hPS, &rcl, RGBCLR_PALEGRAY);
	   for ( i = 0;	i < cBitmaps; i++ )
	       {
		       /* Check	to see if the image is a 2-colour which	*/
		       /* menas	that the colours have to be set		*/
		       /* explicitely					*/

	       if ( abm[i].cColours == 2L )
		   {
		   lClrBack = lClrFore = 0L;

		       /* Check	to see if a 2.x	format bitmap since the	*/
		       /* the structures are slightly different		*/

		   if (	f20Bitmap )
		       {
		       /* Locate the bitmap information	structure	*/

		       if ( (cBitmaps == 1) && !fBitmapArray )
			   {
			   pbfh2 = (PBITMAPFILEHEADER2)abm[i].pb;
			   pbmi2 = (PBITMAPINFO2)&pbfh2->bmp2;
			   }
		       else
			   {
			   pbafh2 = (PBITMAPARRAYFILEHEADER2)abm[i].pb;
			   pbmi2 = (PBITMAPINFO2)&pbafh2->bfh2.bmp2;
			   }
			   /* Transfer the RGB info to the colour	*/
			   /* holders					*/

		       memcpy(&lClrBack, &pbmi2->argbColor[0], 3);
		       memcpy(&lClrFore, &pbmi2->argbColor[1], 3);
		       }
		   else
		       {
		       /* Locate the bitmap information	structure	*/

		       if ( (cBitmaps == 1) && !fBitmapArray )
			   {
			   pbfh	= (PBITMAPFILEHEADER)abm[i].pb;
			   pbmi	= (PBITMAPINFO)&pbfh->bmp;
			   }
		       else
			   {
			   pbafh = (PBITMAPARRAYFILEHEADER)abm[i].pb;
			   pbmi	= (PBITMAPINFO)&pbafh->bfh.bmp;
			   }
			   /* Transfer the RGB info to the colour	*/
			   /* holders					*/

		       memcpy(&lClrBack, &pbmi->argbColor[0], 3);
		       memcpy(&lClrFore, &pbmi->argbColor[1], 3);
		       }
			   /* Draw the 2-colour	bitmap using the	*/
			   /* provided colours from the	bitmap		*/

		   WinDrawBitmap(hPS, abm[i].hbm, (PRECTL)NULL,	(PPOINTL)(PVOID)&abm[i].rclDest,
				 lClrFore, lClrBack, DBM_NORMAL);
		   }
	       else
			   /* Draw the bitmap from the array		*/

		   WinDrawBitmap(hPS, abm[i].hbm, (PRECTL)NULL,	(PPOINTL)(PVOID)&abm[i].rclDest,
				 RGB_WHITE, RGB_BLACK, DBM_NORMAL);

			   /* Draw the 3-D frame around	the image	*/

	       GpiSetColor(hPS,	RGBCLR_SHADOW);
	       GpiMove(hPS, &abm[i].aptlArea[7]);
	       GpiPolyLine(hPS,	2L, &abm[i].aptlArea[4]);

	       GpiSetColor(hPS,	RGB_WHITE);
	       GpiPolyLine(hPS,	2L, &abm[i].aptlArea[6]);

	       GpiSetColor(hPS,	RGB_BLACK);
	       GpiMove(hPS, &abm[i].aptlArea[3]);
	       GpiPolyLine(hPS,	2L, &abm[i].aptlArea[0]);

	       GpiSetColor(hPS,	RGBCLR_PALEGRAY);
	       GpiPolyLine(hPS,	2L, &abm[i].aptlArea[2]);
	       }
	   }
       else
	   {
	   if (	(rclROP.xRight < cxWindow) || (rclROP.yTop < cyWindow) )
	       WinFillRect(hPS,	&rcl, RGBCLR_PALEGRAY);
	   ptl.x = ptl.y = 0L;
	   WinDrawBitmap(hPS, hbmROP, &rclROP, &ptl, 0L, 0L, DBM_NORMAL);
	   }
       WinEndPaint(hPS);
       break;

/************************************************************************/
/* Window being	destroyed, perform clean-up operations			*/
/************************************************************************/

   case	WM_DESTROY :
       for ( i = 0; i <	cBitmaps; i++ )
	   GpiDeleteBitmap(abm[i].hbm);

       if ( hbmROP )
	   GpiDeleteBitmap(hbmROP);

       if ( pb )
	   free(pb);
       break;

			/* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
