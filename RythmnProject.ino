#define IN_GAME 0 // in game state 
#define IN_MENU 1 // in menu state
#define GAME_OVER 2 // game over state
#define YOU_WIN 3 // you win state

#include <TVout.h>
#include <fontALL.h>

TVout TV;
TVout Screen;

/**TESTING**/
 double current = 100.0;
 double prev_test_score = 0;
 int moveY = 85;
/*****/
double randomNumber;

unsigned char cx, cy;
int state = IN_MENU;
const int size = 10;

// O indicates off
int buttonSwitchOne = 0; // buttonOne
int buttonSwitchTwo = 0; // buttonTwo
int buttonSwitchThree = 0;

double testScore = 50; // holds the score

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
  /**SET THE STARTING MENU**/
  if(state == IN_MENU) {
    drawMenu();
  }
  else {
  createGUI(); // create table
  /*************************/
  TV.print(90,17, testScore); // display running score ---


  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);

  readButtonOne(x, y,buttonSwitchOne);
  readButtonTwo(x2,y2,buttonSwitchTwo);
  readButtonThree(x3,y3,buttonSwitchThree);

  /**CHANGE VELOCITY**/
  y = y + velY[0];
  y2 = y2 + velY[1];
  y3 = y3 + velY[2];
  /*************************/

  
  /**CREATE SQUARE**/
  createSquare(x,y,10,4,WHITE); // create moving square 1
  createSquare(x2,y2,10,4,WHITE); // create moving square 2
  createSquare(x3, y3, 10,4, WHITE);
  /*************************/

  /**DISPLAY SCOREBAR**/
   if(testScore >= 500)
  {
     TV.print(95,65," __ "); 
    TV.clear_screen();  
    state = YOU_WIN;

  }
  if(testScore >= current-10.0 && testScore <= current+10.0) {
    TV.print(95, moveY, "|__|");
    moveY -= 5;
    current += 50;
    prev_test_score = testScore;
  } 
  else if(testScore< current -50 && testScore < prev_test_score){
    moveY += 5;
   current -= 50;
   TV.print(95,moveY,"    ");      
  }
  /*************************/
  
  speedGenerator(y,0);
  speedGenerator(y2,1);
  speedGenerator(y3,2);
  }
  TV.delay(16);
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
          testScore = testScore + 1.5;
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
          testScore = testScore + 1.5;
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
          testScore = testScore + 1.5;
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

// start of youWin() screen
void youWin() {
    //testScore = 0;
    //TV.clear_screen();
    TV.select_font(font8x8);
    TV.print(20, 25, "AWESOME!");
    TV.print(20, 35, "YOU WIN!");
    TV.select_font(font4x6);
    TV.print(28, 60, "Press Any Button");
    TV.print(30, 70, "to play again");
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
        youWin();
      }
}

// start of gameOver() screen
void gameOver() {
    testScore = 0;
    //TV.clear_screen();
    TV.select_font(font8x8);
    TV.print(20, 25, "GAME OVER!");
    TV.select_font(font4x6);
    TV.print(28, 60, "Press Any Button");
    TV.print(30, 70, "to play again");
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
        gameOver();
      }
}
// end of gameOver screen


