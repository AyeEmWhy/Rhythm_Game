#include <TVout.h>
#include <fontALL.h>
#include "schematic.h"
#include "TVOlogo.h"

TVout TV;
TVout Screen;

double randomNumber;


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
double velY[3] = {y,y2,y3};

const int buttonOne = 6; 
const int buttonTwo = 4;
const int buttonThree = 2;

double speedController = 0.0; // controls the speed

//start of setup function
boolean button1Status = false;

void setup() {
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
  pinMode(buttonOne,INPUT);
  pinMode(buttonTwo,INPUT);
  pinMode(buttonThree,INPUT);

  
  delay(1000);
  
}// end of setup function


// start of loop function
void loop() {
  //drawMenu();
  createGUI(); // create table
  TV.print(90,17, testScore); // display running score ---

  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);

  readButton(x, y,buttonSwitchOne);
  readButton(x2,y2,buttonSwitchTwo);
  readButton(x3,y3,buttonSwitchThree);

 speedController = testScore/10;

 if(speedController <= 0.0 || speedController > 5.0) {
  speedController = 1.0;
 }

 //y2 = y2 + speedController;
  y = y + velY[0];
  y2 = y2 + velY[1];
  y3 = y3 + velY[2];

  createSquare(x,y,10,10,1); // create moving square 1
  createSquare(x2,y2,10,10,1); // create moving square 2
  createSquare(x3,y3,10,10,1); // create moving square 2

  

  speedGenerator(y,0);
  speedGenerator(y2,1);
  speedGenerator(y3,2);


  TV.delay(16);


// TV.clear_screen(); // clear the moving square

} //end of loop function


void speedGenerator(double &y, int index) { //resets Y value to top if it passes y = 100
  if(y >= 100.0) { 
    y = 10.0;//when y value reaches end (100) reset y to top

    //generate randomNumber
    randomNumber = random(1.0,2.5);
    randomNumber += random(0.0,99.0)/100.0;
    TV.print(90,90, randomNumber); // display randomNumber
    velY[index] = randomNumber; 
  }
}

void readButton(double generalX, double y, int generalButton) 
{
   if (y < 78){
      if(generalButton == HIGH) {
        TV.print(generalX,0,"MISS");
        testScore--;
     }
    }
  else if(generalButton == HIGH && generalX == 8.25) { 
      if(y <= 89 && y >= 78){
        TV.print(8.25,0,"GREAT!");
        testScore++;
  } 
    else if(generalButton == HIGH && generalX == 38.125){
      if(y <= 89 && y >= 78 ) {
        TV.print(38.125,0,"GREAT!");
        testScore++;
      }
    }
    else if(generalButton == HIGH && generalX == 69.875){
      if(y <= 89 && y >= 78 ) {
        TV.print(69.875,0,"GREAT!");
        testScore++;
      }
    }
  }
}

int generateRandomSquares(){
    double x = 0.0;
    int randNumber = random(1,4);
    int columnSquareGenerator = random(1,4);

    if(randNumber == 1) {
      //create one square
      switch(columnSquareGenerator){
       case 1: x = 8.25; createSquare(x,y++,10,10,1); break;
       case 2: x = 38.125; createSquare(x,y++,10,10,1); break;
       case 3: x = 67.875; createSquare(x,y++,10,10,1); break;
      }
    }
    else if (randNumber == 2) {
      //create two squares
       switch(columnSquareGenerator){
       case 1: x = 8.25; createSquare(x,y++,10,10,1); break;
       case 2: x = 38.125; createSquare(x,y++,10,10,1); break;
       case 3: x = 67.875; createSquare(x,y++,10,10,1); break;
      }
    }
    else if(randNumber == 3) {
      //create three squares
    }
    
}

void createSquare(int x, int y, int sizeX, int sizeY, int color) {
    TV.draw_rect(x,y,sizeX,sizeY,color,color);
    TV.draw_rect(x,y-10,sizeX,sizeY,BLACK,BLACK);
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
  
  TV.draw_line(0,80,6.25,80,WHITE); // seperator  
  TV.draw_line(21.75,80,36.75,80,WHITE); // seperator  
  TV.draw_line(51.50,80,65.25,80,WHITE); // seperator  
  TV.draw_line(80.00,80,86.25,80,WHITE); // seperator  


  TV.print(90,10,"SCORE:"); // String Score ---
}

/**TEST CODE
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
  
  while (buttonSwitchOne == LOW )
  {
      if(buttonSwitchOne == HIGH )
      { // first curly brace
        TV.clear_screen();
       // loop();            
      } // end first curly brace
  }
}**/


