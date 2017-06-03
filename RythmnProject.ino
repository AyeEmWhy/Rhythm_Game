/* Arduino Rhythm Game
 * 
 * Developers:
 *    Jiang, Amy
 *    Reti, Daniel
 *    Valenzuela, Princess Anne
 */

#define IN_GAME 0 // in game state 
#define IN_MENU 1 // in menu state
#define GAME_OVER 2 // game over state
#define YOU_WIN 3 // you win state

#include <TVout.h>
#include <fontALL.h>

TVout TV;

 double currentGoal = 100.0; // holds the current goal test score
 double prev_test_score = 0; // holds the previous score
 int moveY = 85; // Y position of score bar

double randomNumber; // holds random number

int state = IN_MENU; // sets the beginning state to menu screen

// O indicates off
int buttonSwitchOne = 0; // button one
int buttonSwitchTwo = 0; // button two
int buttonSwitchThree = 0; // button three

double testScore = 50; // holds the game score

double x = 8.25; //first column's X
double x2 = 38.125; // second column's X
double x3 = 67.875; //third column's X


double y = 15.0; // first column's Y
double y2 = 15.0; // second column's Y
double y3 = 15.0; // third column's Y
double velY[3] = {y,y2,y3};  //array for moving y values

const int buttonOne = 6; // button one
const int buttonTwo = 4; // button two
const int buttonThree = 2; // button three

double speedController = 0.0; // controls the speed

// start of setup function
void setup() {
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
  pinMode(buttonOne,INPUT);
  pinMode(buttonTwo,INPUT);
  pinMode(buttonThree,INPUT);
  drawMenu();
}
// end of setup function

// start of loop function
void loop() {
  /**SET THE STARTING MENU**/
  if(state == IN_MENU || state == YOU_WIN || state == GAME_OVER) {
    drawMenu();   
  }
  else {
  createGUI(); // create table
  /*************************/
  TV.print(90,17, testScore); // display running score 

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
  /********************/

  /**CREATE SQUARE**/
  createSquare(x,y,10,4,WHITE); // create moving square 1
  createSquare(x2,y2,10,4,WHITE); // create moving square 2
  createSquare(x3, y3, 10,4, WHITE);
  /*********************/

  /**DISPLAY SCOREBAR**/
  if(testScore >= currentGoal-10.0 && testScore <= currentGoal+10.0) {
    TV.print(95, moveY, "|__|");
    moveY -= 5;
    currentGoal += 50;
    prev_test_score = testScore;
  } 
  else if(testScore< currentGoal -50 && testScore < prev_test_score){
    moveY += 5;
   currentGoal -= 50;
   TV.print(95,moveY,"    ");      
  }
  /*************************/

  /**INCREASE SPEED**/
  speedGenerator(y,0);
  speedGenerator(y2,1);
  speedGenerator(y3,2);
  /*******************/
  }

  // IF GAME IS OVER
  if(testScore < -1) {
    delay(10000);
    state = GAME_OVER;
  }
  // IF USER WINS THE GAME
   if(testScore > 500)
  {
    delay(10000);
    state = YOU_WIN;
  }

  //AUTO DECREASE SCORE
  testScore = testScore - 0.02;
  TV.delay(16);
} 
//end of loop function

// start of createSquare function
void createSquare(int x, int y, int sizeX, int sizeY, int color) {
    TV.draw_rect(x,y,sizeX,sizeY,color,color);
    TV.draw_rect(x,y-5,sizeX,sizeY,BLACK,BLACK);
}
// end of createSquare function


// start of speedGenerator function
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
// end of speedGenerator function

/**FUNCTIONS TO READ BUTTONS**/
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
/*********************************************/

/**THIS FUNCTION CREATES THE GUI**/
// start of createGUI function
void createGUI() {
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
  TV.print(95, 33, "GOAL");
  TV.print(95, 40, "----");
}

 /**THIS FUNCTION DRAWS THE MENU**/
// start of drawMenu function
void drawMenu() {
   
  TV.select_font(font8x8);

  if(state == IN_MENU){
  TV.print(25, 15, "ARDUINO");
  TV.print(10, 35, "Rhythm Game");
  }
    
  if(state == YOU_WIN){
  TV.clear_screen();
  TV.print(25, 25, "YOU WIN");
  TV.print(20, 35, "THE GAME!");
  }
  
  if(state == GAME_OVER){
  TV.clear_screen();
  TV.print(22, 25, "YOU LOSE!");
  }
  
  TV.select_font(font4x6);
  TV.print(25, 60, "Press Any Button");
  TV.print(40, 70, "to Play");
    
  buttonSwitchOne = digitalRead(buttonOne);
  buttonSwitchTwo = digitalRead(buttonTwo);
  buttonSwitchThree = digitalRead(buttonThree);
  
      if(buttonSwitchOne == HIGH || buttonSwitchTwo == HIGH || buttonSwitchThree == HIGH)
      { 
       TV.clear_screen();
        state = 0;
      } 
        else {
          testScore = 50;
          prev_test_score = 0.0;
          moveY = 85;
          currentGoal = 100.0;
         if (state == 1)
           state = 1;
         if(state == 2) {
           state = 2;

         }
         if(state == 3) {
          state = 3;
         }
      }
}
// end of drawMenu function


