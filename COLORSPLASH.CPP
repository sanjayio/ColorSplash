/*
############################################################################
########################## COLOR SPLASH 1.0 ################################
############################################################################
A lite paint software created entirely on C++ environment using graphics.h
library file. This program tries to reproduce almost most of the features of
Microsoft Paint although Save and Print functions are missing. But this
program comes with additional brush tools and much more. Altogether it
provides a good painting experience.

This project was started on March 11, 2013 at 1700 hrs IST.

This project is programmed and designed by Sanjay Kumar A, founder,
seanunbound.com.

The official project website is given below:
	      http://www.seanunbound.com/colorsplash

The documentation, version and license information can be found in the above
URL. Please read through the documentaion and license before making mods to
the original source code.

#####Very important#####DO NOT REMOVE THE BELOW PARAGRAPH###################

This program is designed and programmed by Sanjay Kumar A. Henceforth the
complete rights remain with the me, Sanjay. Reproduction of the complete
program or any part of the program is allowed WITHOUT THE REMOVAL OF THIS
PARAGRAPH. For commercial uses please email me : sanjaykumara@aol.com

############################################################################

Hope you'll enjoy the product. For support, complaints and feedback please
contact me through my email : sanjaykumara@aol.com

Thank you for using Color Splash Ver.1.0. !!!

*/

// Beginning of the program
//initialising headers.

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>



void shapepanelinit()                   //shape panel initialisation.
{
   int left, top, c, color;

   left = 529;
   top = 5;

   color = getcolor();
   setcolor(WHITE);
   rectangle(522,0,635,getmaxy());
   setfillstyle(SOLID_FILL , WHITE);
   bar(522,0,635,getmaxy());

   for( c = 1 ; c <= 13 ; c++ )
   {
      setcolor(BLACK);
      setfillstyle(SOLID_FILL , BLACK);
      rectangle(left, top, left+100, top+25);
      bar(left+2, top+2, left+98,top+23);
      top += 30;                }
   setcolor(WHITE);
   outtextxy(530,5,"Bar");
   outtextxy(530,35,"Line");
   outtextxy(530,65,"Pixel");
   outtextxy(530,95,"Ellipse");
   outtextxy(530,125,"Freehand");
   outtextxy(530,155,"Rectangle");
   outtextxy(530,185,"Tunnel");
   outtextxy(530,215,"RectChain");
   outtextxy(530,245,"BarChain");
   outtextxy(530,275,"CircChain");
   outtextxy(530,305,"L.Brush");
   outtextxy(530,335,"S.Brush");
   outtextxy(530,365,"Eraser");
   setcolor(BLACK);
   setfillstyle(SOLID_FILL , GREEN);
   rectangle(left, top, left+100, top+25);
   bar(left+2, top+2, left+98,top+23);
   top += 30;
   outtextxy(530,395,"Clear");
   setcolor(BLACK);
   setfillstyle(SOLID_FILL , RED);
   rectangle(left, top, left+100, top+25);
   bar(left+2, top+2, left+98,top+23);
   top += 30;
   outtextxy(530,425,"Quit");
   setcolor(color);
}



union REGS i, o;              //variables for int86 fns.
int leftcolor[15];


void colorpanelinit()         //color panel initialisation.
{
   int left, top, c, color;

   left = 100;
   top = 436;

   color = getcolor();
   rectangle(4,431,635,457);
   setfillstyle(SOLID_FILL ,WHITE);
   bar(0,431,635,457);
   setcolor(BLACK);
   settextstyle(TRIPLEX_FONT,0,2);
   outtextxy(10,431,"Colors : ");

   for( c = 1 ; c <= 15 ; c++ )
   {
      setfillstyle(SOLID_FILL , BLACK);
      bar(left-2,top-2, left+18, top+18);
      setfillstyle(SOLID_FILL, c);
      bar(left, top, left+16, top+16);
      leftcolor[c-1] = left;
      left += 26;
   }

   setcolor(color);
}





int keyinput()                //reading keyboard input.
{
   union REGS i,o;

   i.h.ah = 0;
   int86(22,&i,&o);

   return ( o.h.ah );
}




void colorchange(int x, int y)         //fn to change default color.
{
   int c;

   for( c = 0 ; c <= 13 ; c++ )
   {
      if( x > leftcolor[c] && x < leftcolor[c+1] && y > 437 && y < 453 )
	 setcolor(c+1);
      if( x > leftcolor[14] && x < 505 && y > 437 && y < 453 )
	 setcolor(WHITE);
   }
}



char shapechange(int x, int y)   //fn to change default shape ie. freehand
{
   if ( x > 529 && x < 625 && y > 5 && y < 30 )
      return 'b';
   else if ( x > 529 && x < 625 && y > 35 && y < 60 )
      return 'l';
   else if ( x > 529 && x < 625 && y > 65 && y < 90 )
      return 'p';
   else if ( x > 529 && x < 625 && y > 95 && y < 120 )
      return 'e';
   else if ( x > 529 && x < 625 && y > 125 && y < 150 )
      return 'f';
   else if ( x > 529 && x < 625 && y > 155 && y < 180 )
      return 'r';
   else if ( x > 529 && x < 625 && y > 185 && y < 210 )
      return 't';
   else if ( x > 529 && x < 625 && y > 215 && y < 240 )
      return 'R';
   else if ( x > 529 && x < 625 && y > 245 && y < 270 )
      return 'B';
   else if ( x > 529 && x < 625 && y > 275 && y < 300 )
      return 'C';
   else if ( x > 529 && x < 625 && y > 305 && y < 330 )
      return 'U';
   else if ( x > 529 && x < 625 && y > 335 && y < 360 )
      return 'u';
   else if ( x > 529 && x < 625 && y > 365 && y < 390 )
      return 'E';
   else if ( x > 529 && x < 625 && y > 395 && y < 420 )
      return 'c';
   else if ( x > 529 && x < 625 && y > 425 && y < 450 )
      exit(0);
}


//mouse ptr functions - begin

void showmouseptr()
{
   i.x.ax = 1;
   int86(0x33,&i,&o);
}

void hidemouseptr()
{
   i.x.ax = 2;
   int86(0x33,&i,&o);
}

void restrictmouseptr( int x1, int y1, int x2, int y2)
{
   i.x.ax = 7;
   i.x.cx = x1;
   i.x.dx = x2;
   int86(0x33,&i,&o);

   i.x.ax = 8;
   i.x.cx = y1;
   i.x.dx = y2;
   int86(0x33,&i,&o);
}

void getmousepos(int *button,int *x,int *y)
{
   i.x.ax = 3;
   int86(0x33,&i,&o);

   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}

//mouse ptr fns - end

main()
{
   int gd = DETECT,gm;

   int maxx,maxy,x,y,button,prevx,prevy,temp1,temp2,key,color;
   char ch = 'f' ;            // default free-hand drawing

   initgraph(&gd,&gm,"C:\\TC\\BGI");    //graphics initialisation.

   maxx = getmaxx();
   maxy = getmaxy();

   setcolor(WHITE);             //settin the white background.
   setfillstyle(SOLID_FILL,WHITE);
   rectangle(0,0,maxx-4,maxy-2);
   bar(0,0,maxx-4,maxy-2);

   setcolor(BLACK);
   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
   outtextxy(maxx/2-310,maxy-27,"ESC To quit | F1 To clear the screen. Created by Sanjay");

   colorpanelinit();         //initialisation of the color
   shapepanelinit();         //and shape panel.

   setviewport(1,1,maxx-1,maxy-1,1);

   restrictmouseptr(1,1,maxx-1,maxy-1);    //restricting mouse pointer
   showmouseptr();                         //movement.
   rectangle(2,2,518,427);
   setviewport(1,1,519,428,1);

   while(1)
   {
      if(kbhit())
      {
	 key = keyinput();

	 if( key == 1 )           //checking if keystroke is ESC.
	 {
	    closegraph();
	    exit(0);
	 }
      }

      getmousepos(&button,&x,&y);

      if( button == 1 )
      {
	 if( x > 4 && x < 635 && y > 431 && y < 457 )
	    colorchange( x, y );
	 else if ( x > 529 && x < 625 && y > 0 && y < 480 )
	     ch = shapechange( x, y );

	 temp1 = x ;
	 temp2 = y ;

	 if ( ch == 'f' )                //freehand drawing.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       line(temp1,temp2,x,y);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }

	 if (ch == 'E' )                 //eraser tool.
	 {
	    hidemouseptr();
	    while( button == 1)
	    {
		setcolor(WHITE);
		circle(temp1,temp2,random(10));
		temp1=x;
		temp2=y;
		getmousepos(&button , &x , &y);
	    }
	    showmouseptr();
	 }

	 if ( ch == 'C' )          //circle chain tool.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       circle(temp1,temp2,5);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }


	 if ( ch == 'u' )              //small brush tool.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       circle(temp1,temp2,random(5));
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }

	 if ( ch == 'U' )       //large brush tool.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       circle(temp1,temp2,random(10));
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }


	 if ( ch == 't' )               //Tunnel fn.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       circle(temp1,temp2,temp2-temp1);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }

	 if ( ch == 'B' )             //Bar Chain tool.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       color = getcolor();
	       setfillstyle(SOLID_FILL , color);
	       bar(temp1,temp2,x,y);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }

	 if ( ch == 'R' )              //Rectangular chain tool.
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       rectangle(temp1,temp2,x,y);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }


	 while( button == 1)
	    getmousepos(&button,&x,&y);

	 /* to avoid interference of mouse while drawing */
	 hidemouseptr();


	 if( ch == 'p')                  //pixel tool.
	    putpixel(x,y,getcolor());

	 else if ( ch == 'b' )         //bar tool.
	 {
	    setfillstyle(SOLID_FILL,getcolor());
	    bar(temp1,temp2,x,y);
	 }
	 else if ( ch == 'l')           //line tool.
	    line(temp1,temp2,x,y);
	 else if ( ch == 'e')           //ellipse tool.
	    ellipse(temp1,temp2,0,360,abs(x-temp1),abs(y-temp2));
	 else if ( ch == 'r' )            //rectangle tool.
	    rectangle(temp1,temp2,x,y);
	 else if ( ch == 'c' )           //clear button process.
	 {
	    setfillstyle(SOLID_FILL, WHITE);
	    ch = 'f';          // setting to freehand drawing
	    clearviewport();
	    color = getcolor();
	    setcolor(BLACK);
	    bar(0,0,518,427);
	    rectangle(2,2,518,427);
	    setcolor(color);
	 }

	 showmouseptr();
      }
   }
}