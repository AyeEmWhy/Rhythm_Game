#include <TVout.h>
#include <fontALL.h>
#include "schematic.h"
#include "TVOlogo.h"

TVout TV;
// O indicates off
int buttonSwitchOne = 0; // buttonOne
int buttonSwitchTwo = 0; // buttonTwo
int testScore = 0; // holds the score
int x = 10;
int x2 = 80;
double y = 10;
double box2y = 10;
void *boxPtr;
const int buttonOne = 4; 
const int buttonTwo = 2;
double speedController = 0; // controls the speed

//start of setup function
void setup() {
  pinMode(buttonOne,INPUT);
  pinMode(buttonTwo,INPUT);
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
  createGUI(); // create table
}
// end of setup function

// start of loop function
void loop() {
  createGUI(); // create table
    
  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);

  readButton(y, buttonSwitchOne);
  readButton(box2y, buttonSwitchTwo);
  
  TV.select_font(font4x6);

 TV.print(25,0, testScore); // display score
 speedController = testScore/10;

 if(speedController <= 0 || speedController > 10)
 {
  speedController = 1;
 }

 box2y = box2y+ speedController;
 createSquare(x,y++,10,10,1); // create moving square 1

 createSquare(x2,box2y,10,10,1); // create moving square 2
 if(y>100) // sets y value back at 10
 {
  y=10; // position of box
 }
 if(box2y>100) // sets y value back at 10
 {
 box2y= 10 ;  
 }
  TV.delay(16);

//  TV.clear_screen(); // clear the moving square

/*if(buttonSwitchOne == HIGH) 
{
  TV.print(75,30,"One!");
}
else if(buttonSwitchTwo == HIGH) 
{
  TV.print(75,60,"Two!");
}*/

} 
//end of loop function


void readButton(double y,int buttonSwitchTwo) 
{
  if(buttonSwitchTwo == HIGH) 
  { 
    // TV.draw_rect(10,82.5,10,10,WHITE); 
    if(y <= 89 && y >= 78) 
    {
        TV.print(75,0,"GREAT!");
      testScore++;
    } 
    else {
      TV.print(75,0,"MISS");
      testScore--;
    }
  }
}


void createSquare(int x, int y, int sizeX, int sizeY, int color) {
    TV.draw_rect(x,y,sizeX,sizeY,color);
    TV.draw_rect(x,y-2,sizeX,sizeY,BLACK);
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
  TV.draw_line(28.75,8,28.75,94.5,WHITE);  //middle-line
  TV.draw_line(57.5,8,57.5,94.5,WHITE);  //middle-line
  TV.draw_line(86.25,8,86.25,94.5,WHITE);  //middle-line

  TV.draw_line(86.25,8,86.25,94.5,WHITE); //right-line
  TV.draw_line(0,8,86.25,8,WHITE); // top-line 
  TV.draw_line(0,94.5,86.25,94.5,WHITE); // bottom-line
  TV.draw_line(0,80,86.25,80,WHITE); // seperator  
  TV.print(0,0,"SCORE:");
}

