 #include<stdio.h>
 #include<graphics.h>
 #include<conio.h>
 #include<stdlib.h>
 #include<time.h>
 #include<dos.h>

void main()
{
char ch;
int gd=0,gm;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
setbkcolor(BLACK);

 setcolor(BROWN);
 setfillstyle(1,BROWN);

rectangle(290,200,370,235);
rectangle(290,235,370,270);
rectangle(290,270,370,305);
rectangle(290,305,370,340);

floodfill(300,100,BROWN);
floodfill(300,200,BROWN);
floodfill(300,350,BROWN);
floodfill(300,400,BROWN);
settextstyle(1,0,3);

      setcolor(WHITE);
      outtextxy(300,200,"START");
      outtextxy(295,235,"ABOUT");
      outtextxy(300,270,"HELP");
	outtextxy(300,310,"EXIT");
       settextstyle(9,0,5);
 setcolor(WHITE);
 outtextxy(180,100,"WELCOME");
 settextstyle(1,0,1);
 outtextxy(130,350,"please enter H key for help");
a:
ch=getch();
if( ch==115 || ch==83)   // ascii value of s or S
	{
		game();
	}
else if (ch==104 || ch==72)// ascii value of h or H
	{
		help();
	}
else if(ch==97 || ch==65)// ascii value of a or A
	{
		about();
	}
else if(ch==101 || ch== 69)// ascii value of e Or E
	{
		goto ll;
	}
else{
	printf("Please enter valid key" );
	goto a;
	}

ll:

}


 int game()
 {

 int gd=0,gm;
 int x=150,y=325,r=10;
 int randnum,gameover=0;
 int Score=0;
 int Highscore=0;
 char Scoretext[25];
 char Highscoretext[25];
 //for checking if ball touched ellipse or not
 int check=0;
 //for file handling
 FILE *fp;
 //for ellipse
 int x1=622,y1=200,y2;
 int start_angle=0,end_angle=360;
 int x_rad=50,y_rad=15;

 char ch;
 initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
 setbkcolor(BLACK);
 setcolor(BROWN);
 setfillstyle(1,BROWN);
 rectangle(0,0,639,100);
 rectangle(0,339,639,439);
 floodfill(1,340,BROWN);
 floodfill(1,1,BROWN);

 //reading highscore from file
 fp = fopen("highscore.txt","r"); // it doesn't create file
 //if file doesn't exist
 if(fp == NULL){
	fp = fopen("highscore.txt","w"); //it create highscore.txt file
	putw(Highscore,fp); // writing highscore in file
	fclose(fp); // closing file
 }
 // if file exists
 else{
	Highscore = getw(fp); //read highscore
	fclose(fp); // closing file
 }

 //for initial position of obstacle
      srand(time(NULL));
      randnum=random(200);
      settextstyle(1,0,3);
      setcolor(WHITE);
      outtextxy(100,200,"Please Enter any key to start game");
      getch();
      setcolor(BLACK);
      outtextxy(100,200,"Please Enter any key to start game");

 //for keyboard input
	delay(1);
	 while(1)
		 {
			 if(kbhit())
			 {
			     ch=getch();
			       if(ch==27)
				  {
				    closegraph();
					exit(1);
				  }
			 else if(ch==32 && gameover==0)
			     {
				 setcolor(BLACK);
				 circle(x,y,r);
				 setfillstyle(1,BLACK);
				 floodfill(x,y,BLACK);
				 y-=50;
				 if(y-r<=103)
				 {
				 gameover=1;
				    y=113;
				 }

			      }
			  }

	       setcolor(WHITE);
	       settextstyle(1,0,3);
	       sprintf(Scoretext,"Score: %d",Score);
	       sprintf(Highscoretext,"High score: %d",Highscore);
	       outtextxy(530,15,Scoretext);
	       outtextxy(300,15,Highscoretext);


       //for moving ball downward
       if(y+r<337 && gameover==0)
       {
		    setcolor(BLACK);
		    circle(x,y,r);
		    setfillstyle(1,BLACK);
		    floodfill(x,y,BLACK);
		    y++;
       }



	 //for drawing a ball
	   setcolor(RED);
	   circle(x,y,r);
	   setfillstyle(1,RED);
	   floodfill(x,y,RED);



	   //for drawing an obstacle
	 setcolor(13  );
	 ellipse(x1,y1,start_angle,end_angle,x_rad,y_rad);
	 x1=x1-1;
	delay(4);
	 setcolor(BLACK);
	 ellipse(x1+1,y1,start_angle,end_angle,x_rad,y_rad);
	      if(gameover==0)
	      {

		 x1=x1-1;

	      }
		 if(x1<0)
		 {
		 x1=622;
		randnum=random(150);
		 y1=200-randnum;
		 if(y1<=150)
		 {
			y1=300;
		 }
		 check = 0 ;  // reseting check for next ellipse
		}


	   //if ball x position is between end point of ellipse and y position of ball is equal to y position of ellipse
	   // true -> ball touched the ellipse
	   if ( (x+r>=x1-x_rad && x-r<=x1+x_rad) && y==y1){
		check=1;
		setcolor(BROWN);
		outtextxy(530,15,Scoretext);
		Score=Score+1;
	   }

	   // if ellipse x position is less than ball position and check is false
	   if(!check && x1+x_rad<x-r){
		gameover = 1;
	   }
	   if(gameover)
	   {
	   setcolor(RED);
	   settextstyle(1,0,4);
	   outtextxy(200,225,"Game Over");
	   getch();
	      end();
		h:
		setcolor(RED);
		ch=getch();

		if (ch==121 || ch==89)// ascii value for Y or y
			{
				game();
			}
		else if(ch==78 || ch==110)// ascii value for N or n
			{
				main();
			}
		else

			{
				printf("INVALID INPUT");
				goto h;
			}
	   //writing score in file if score>highscore
	   if(Score>Highscore){
		fp = fopen("highscore.txt","w");
		putw(Score,fp);
		fclose(fp);
	   }
	   break; //1
	   }
      }
      getch();//2
 return 0;
}

int help()
{
char ch;
clrscr();
 setbkcolor(BLACK);
 setcolor(BROWN);
settextstyle(3,0,1);
outtextxy(30,20,"1.Press SPACE to move ball.");
outtextxy(30,50,"2.Make sure that the BALL passes through the ring.");
outtextxy(30,80,"3.enter s key to start game.");
outtextxy(30,110,"3.Press Y for yes.");
outtextxy(30,140,"4.Press N for No.");
outtextxy(30,170,"5.Press R to return to menu.");
outtextxy(30,200,"6.ENJOY the Game and beat the HIGHSCORE.");

b:
 ch=getch();
 if(ch==114 || ch==82) // ascii value of r or R
	{
		main();
	}
 else
	{
		printf("Please Enter Valid key");
		goto b;
	}

 return 0;
}


int about()
{
char ch;
clrscr();
 setbkcolor(BLACK);
 setcolor(BROWN);
settextstyle(3,0,1);
outtextxy(25,20,"About DUNKSHOT");
outtextxy(25,50,"A 2D simple graphics game which typically involves players controlling");
outtextxy(25,70,"the ball and leading it through the rings.The rings come randomly to");
outtextxy(25,90,"the platform.");
outtextxy(25,130,"To score points, players must lead the ball through the rings.Players ");
outtextxy(25,150,"loose the game if the ball touches the upper rectangle or doesn't ");
outtextxy(25,170," enter into the rings.");


c:
ch=getch();// input is taken from user to return to main menu
if(ch==114 || ch==82)  // ascii value of r And R
	{
		main();
	}
else
	{
		printf("Please enter VALID key");
		goto c;
	}
  return 0;
}


int end()
{
char ch;
clrscr();
setbkcolor(BLACK);
setcolor(RED);
settextstyle(1,0,3);
outtextxy(100,200,"Do you want to beat highscore again?");
outtextxy(250,260,"Yes or No");
return 0;

}
