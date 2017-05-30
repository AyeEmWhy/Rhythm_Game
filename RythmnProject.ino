#define IN_GAME 0 //in game state 
#define IN_MENU 1 //in menu state
#define GAME_OVER 2 //game over state

#include <TVout.h>
#include <fontALL.h>

TVout TV;
TVout Screen;

double randomNumber;

unsigned char cx, cy;
int state = IN_MENU;

const int size = 10;

// O indicates off
int buttonSwitchOne = 0; // buttonOne
int buttonSwitchTwo = 0; // buttonTwo
int buttonSwitchThree = 0;

int scoreKeeper = 85;
int scoreKeeperColor = 0;



int testScore = 0; // holds the score

double x = 8.25; //first column's X
double x2 = 38.125; // second column's X
double x3 = 67.875; //third column's X


double y = 15.0;
double y2 = 15.0;
double y3 = 15.0;


double velY[3] = {y,y2,y3};  //array for moving y values

const int buttonOne = 6; 
const int buttonTwo = 4;
const int buttonThree = 2;

double speedController = 0.0; // controls the speed

//start of setup function

void setup() {
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
  pinMode(buttonOne,INPUT);
  pinMode(buttonTwo,INPUT);
  pinMode(buttonThree,INPUT);
  //drawMenu();
    Serial.begin(9600);
  TV.clear_screen();  
  delay(1000);
}// end of setup function

// start of loop function
void loop() {

  if(state == IN_MENU) {
    drawMenu();
  }
  else {
  createGUI(); // create table
  TV.print(90,17, testScore); // display running score ---


  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);

  readButtonOne(x, y,buttonSwitchOne);
  readButtonTwo(x2,y2,buttonSwitchTwo);
  readButtonThree(x3,y3,buttonSwitchThree);

  y = y + velY[0];
  y2 = y2 + velY[1];
  y3 = y3 + velY[2];

  createSquare(x,y,10,4,WHITE); // create moving square 1
  createSquare(x2,y2,10,4,WHITE); // create moving square 2
  createSquare(x3, y3, 10,4, WHITE);

    bool checkIfIncrease = false;

  if(testScore - scoreKeeper < 0 ) {
    checkIfIncrease = false;
  }
  else {
    checkIfIncrease = true;
  }
  if(checkIfIncrease) {
    TV.draw_rect(98,85,10, 3,WHITE,BLACK); // SMILIY square
   
  } else {
        TV.draw_rect(98,85,12, 3,BLACK,BLACK); // SMILIY square 
  }
  /*
  else if(testScore <= 100)
    TV.draw_rect(98,82,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 150)
    TV.draw_rect(98,79,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 200)
    TV.draw_rect(98,76,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 250)
    TV.draw_rect(98,73,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 300)
    TV.draw_rect(98,70,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 350)
    TV.draw_rect(98,67,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 400)
    TV.draw_rect(98,64,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 450)
    TV.draw_rect(98,61,10, 3,WHITE,BLACK); // SMILIY square 
 else if(testScore <= 500)
    TV.draw_rect(98,58,10, 3,WHITE,BLACK); // SMILIY square 

  */

   

  speedGenerator(y,0);
  speedGenerator(y2,1);
  speedGenerator(y3,2);

  }
  TV.delay(16);

  scoreKeeper = testScore;
//}



// TV.clear_screen(); // clear the moving square

} //end of loop function

void createSquare(int x, int y, int sizeX, int sizeY, int color) {
    TV.draw_rect(x,y,sizeX,sizeY,color,color);
    TV.draw_rect(x,y-5,sizeX,sizeY,BLACK,BLACK);
}

void speedGenerator(double &y, int index) { //resets Y value to top if it passes y = 100
  if(y >= 95.00) { 
    y = 15.0;//when y value reaches end (100) reset y to top
    //generate randomNumber
    randomNumber = random(1.0,2.5);
    randomNumber += random(0.0,99.9)/100.0;
   // TV.print(90,90, randomNumber); // display randomNumber
    velY[index] = randomNumber; //change speed 
  }
}



void readButtonOne(double x, double y,int buttonOne) 
{ // open curly brace function
 if(buttonOne == HIGH) 
  { // first curly brace
      if(y <= 89 && y >= 78 && x == 8.25) // first square
      { // curly if y
          TV.print(5.25,0,"GREAT!");
          testScore = testScore + 3;
        } 
        else {
          TV.print(5.25,0,"MISS! ");
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
          TV.print(35.125,0,"MISS! ");
          testScore--;
        }
        
  } // end first curly brace
} // ending curly brace function


void readButtonThree (double x3, double y3,int buttonThree) 
{ // open curly brace function
 if(buttonThree == HIGH) 
  { // first curly brace
    
      if(y3 <= 95 && y3 >= 72 && x3 == 67.875) // first square
      { // curly if y
          TV.print(64.875,0,"GREAT!");
          testScore = testScore + 3;
        } 
        else {
          TV.print(64.875,0,"MISS! ");
          testScore--;
        }
        
  } // end first curly brace
} // ending curly brace function


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

// -----------------------------------------------

// function to display menu
void drawMenu() {
  int z = 0;
  int w = 0;
  char volX =3;
  char volY = 3;
 // TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(25, 15, "Arduino");
  TV.print(10, 35, "Rhythm Game");
  TV.select_font(font4x6);
  TV.print(30, 60, "Press Any Button");
  TV.print(30, 70, "to Start");
  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);
  
  delay(1000);

      if(buttonSwitchOne == HIGH || buttonSwitchTwo == HIGH || buttonSwitchThree == HIGH  )
      { // first curly brace
        TV.clear_screen();
        state = IN_GAME;
      } // end first curly brace
      else {
        state = IN_MENU;
      }
}
// end of drawMenu function


