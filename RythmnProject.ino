#include <TVout.h>
#include <fontALL.h>
#include "schematic.h"
#include "TVOlogo.h"

TVout TV;
// O indicates off
int buttonSwitchOne = 0; // buttonOne
int buttonSwitchTwo = 0; // buttonTwo
int buttonSwitchThree = 0;

int testScore = 0; // holds the score

double x = 8.25; //first column's X
double x2 = 38.125; // second column's X
double x3 = 67.875; //third column's X

double y = 10;
double y2 = 10;
double y3 = 10;

const int buttonOne = 2; 
const int buttonTwo = 4;
const int buttonThree = 6;

double speedController = 0; // controls the speed

//start of setup function
void setup() {
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
  pinMode(buttonOne,INPUT);
  pinMode(buttonTwo,INPUT);
  pinMode(buttonThree,INPUT);

  drawMenu();


   // TV.clear_screen();

  // createGUI(); // create table
  
}// end of setup function


// start of loop function
void loop() {
  createGUI(); // create table
    
  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);

  readButtonOne(x, y, buttonSwitchOne);
  readButtonTwo(x2, y2, buttonSwitchTwo);
  readButtonThree(x3,y3, buttonSwitchThree);

  TV.select_font(font4x6);

 TV.print(90,17, testScore); // display running score ---
 speedController = testScore/10;

 if(speedController <= 0 || speedController > 10)
 {
  speedController = 1;
 }

 y2 = y2 + speedController;
 createSquare(x,y++,10,10,1); // create moving square 1
 createSquare(x2,y2,10,10,1); // create moving square 2
 createSquare(x3,y3++,10,10,1); // create moving square 2

 if(y > 100) // sets y value back at 10
 {
   y = 10; // position of box
 }
 if(y2 > 100) // sets y2 value back at 10
 {
     y2= 10 ;  
 }
 if(y3 > 100) // sets y3 value back at 10
 {
    y3= 10 ;  
 }
 
  TV.delay(16);

//  TV.clear_screen(); // clear the moving square

} 
//end of loop function


void readButtonOne(double x, double y,int buttonOne) 
{ // open curly brace function
 if(buttonOne == HIGH) 
  { // first curly brace
    
      if(y <= 89 && y >= 78 && x == 8.25) // first square
      { // curly if y
          TV.print(5.25,0,"GREAT!");
          testScore++;
        } 
        else {
          TV.print(5.25,0,"MISS");
          testScore--;
        }
        
  } // end first curly brace
} // ending curly brace function

void readButtonTwo(double x2, double y2,int buttonTwo) 
{ // open curly brace function
 if(buttonTwo == HIGH) 
  { // first curly brace
    
        if ( y2<= 89 && y2 >= 78 && x2 == 38.125) // second square
        {
          TV.print(35.125,0,"GREAT!");
          testScore++;
        } 
        else {
          TV.print(35.125,0,"MISS");
          testScore--;
        }
        
  } // end first curly brace
} // ending curly brace function


void readButtonThree (double x3, double y3,int buttonThree) 
{ // open curly brace function
 if(buttonThree == HIGH) 
  { // first curly brace
    
      if(y3 <= 89 && y3 >= 78 && x3 == 67.875) // first square
      { // curly if y
          TV.print(64.875,0,"GREAT!");
          testScore++;
        } 
        else {
          TV.print(64.875,0,"MISS");
          testScore--;
        }
        
  } // end first curly brace
} // ending curly brace function


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
  TV.draw_line(28.75,8,28.75,94.5,WHITE);  //1st middle-line
  TV.draw_line(57.5,8,57.5,94.5,WHITE);  //2nd middle-line
  TV.draw_line(86.25,8,86.25,94.5,WHITE); //right-line
  TV.draw_line(0,8,86.25,8,WHITE); // top-line 
  TV.draw_line(0,94.5,86.25,94.5,WHITE); // bottom-line
  TV.draw_line(0,80,86.25,80,WHITE); // seperator  
  TV.print(90,10,"SCORE:"); // String Score ---
}

void drawMenu() {
  int z = 0;
  int w = 0;
  char volX =3;
  char volY = 3;
  TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(25, 15, "Arduino");
  TV.print(10, 35, "Rhythm Game");
  TV.select_font(font4x6);
  TV.print(30, 60, "Press Button");
  TV.print(30, 70, "to Start");

  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);
  
  while (buttonSwitchOne == LOW /*||  buttonSwitchTwo == LOW || buttonSwitchThree == LOW*/)
  {
      if(buttonSwitchOne == HIGH /*||  buttonSwitchTwo == HIGH || buttonSwitchThree == HIGH*/) 
      { // first curly brace
        TV.clear_screen();
        createGUI();
            
      } // end first curly brace
  }



  /*
  delay(1000);
  while(!button1Status) {
    processInputs();
    TV.delay_frame(3);
    if(x + volX < 1 || x + volX > TV.horz_res() - 1) volX = -volX;
    if(y + volY < 1 || y + volY > TV.vert_res() - 1) volY = -volY;
    if(TV.get_pixel(x + volX, y + volY)) {
      TV.set_pixel(x + volX, y + volY, 0);
    
      if(TV.get_pixel(x + volX, y - volY) == 0) {
        volY = -volY;
      }
      else if(TV.get_pixel(x - volX, y + volY) == 0) {
        volX = -volX;
      }
      else {
        volX = -volX;
        volY = -volY;
      }
    }
    TV.set_pixel(x, y, 0);
    x += volX;
    y += volY;
    TV.set_pixel(x, y, 1);
  }
 */

  TV.select_font(font4x6);
 // state = IN_GAMEA;
}


