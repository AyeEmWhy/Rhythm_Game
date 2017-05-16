#include <TVout.h>
#include <fontALL.h>
#include "schematic.h"
#include "TVOlogo.h"

TVout TV;
int buttonSwitch = 0; //0 INDICATES OFF
int buttonSwitchTwo = 0;
int testScore = 0;
int x = 10;
int x2 = 80;
double y = 10;
double box2y = 10;


void setup() {
  pinMode(2,INPUT);
  //pinMode(3,INPUT);
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
}

void loop() {
  createGUI(); // create table
  buttonSwitch = digitalRead(2);
  buttonSwitchTwo = digitalRead(4);
  //buttonSwitchTwo = digitalRead(2);
  //readButton(y, buttonSwitch);
  readButton(box2y, buttonSwitchTwo);
  TV.select_font(font4x6);

 TV.print(25,0, testScore); // display score
 createSquare(x,y++,10,10,1); // create moving square 1
 createSquare(x2,box2y++,10,10,1); // create moving square 2
 if(y>100) // sets y value back at 10
 {
  y=10;
  
 }
 if(box2y>100) // sets y value back at 10
 {
 box2y=10;
  
 }
  TV.delay(16);
  TV.clear_screen(); // clear the moving square
}

void readButton(double y,int buttonSwitch) 
{
  if(buttonSwitch == HIGH) 
  { 
    // TV.draw_rect(10,82.5,10,10,WHITE); 
    if(y <= 89 && y >= 78) 
    {
        TV.print(75,0,"GREAT!");
      testScore++;
    } 
    else {
      TV.print(75,0,"MISS");
      //testScore--;
    }
  }
}


void createSquare(int x, int y, int sizeX, int sizeY, int color) {
    TV.draw_rect(x,y,sizeX,sizeY,color);
}



void createGUI() {
 /**THIS FUNCTION CREATES THE GUI**/
 /*NOTE: draw_line accepts doubles*/
 //X0,Y0,X1,Y1,COLOR
 // (0,0) upper-left
 // (0,94.5) bottom-left
 // (115, 94.5) //bottom-right 
 // (115, 0) upper-right
   TV.select_font(font4x6);
  TV.draw_line(0,8,0,94.5,WHITE); //left-line 
  TV.draw_line(57.5,8,57.5,94.5,WHITE);  //middle-line
  TV.draw_line(115,8,115,94.5,WHITE); //right-line
  TV.draw_line(0,8,115,8,WHITE); // top-line 
  TV.draw_line(0,94.5,115,94.5,WHITE); // bottom-line
  TV.draw_line(0,80,115,80,WHITE); // seperator  
  TV.print(0,0,"SCORE:");

}

