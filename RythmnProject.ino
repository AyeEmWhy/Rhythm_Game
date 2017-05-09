#include <TVout.h>
#include <fontALL.h>
#include "schematic.h"
#include "TVOlogo.h"

TVout TV;

int testScore = 0;
int x = 10;
double y = 10;
double box2y = y;
void setup() {
  TV.begin(NTSC,120,96); //TV, X coor , Y coor
  TV.select_font(font4x6);

 
 /*NOTE: draw_line accepts doubles*/
 //X0,Y0,X1,Y1,COLOR
 // (0,0) upper-left
 // (0,94.5) bottom-left
 // (115, 94.5) //bottom-right 
 // (115, 0) upper-right
  TV.draw_line(0,8,0,94.5,WHITE); //left-line 
  TV.draw_line(57.5,8,57.5,94.5,WHITE);  //middle-line
  TV.draw_line(115,8,115,94.5,WHITE); //right-line
  TV.draw_line(0,8,115,8,WHITE); // top-line 
  TV.draw_line(0,94.5,115,94.5,WHITE); // bottom-line
  TV.draw_line(0,80,115,80,WHITE); // seperator  
  TV.print(0,0,"SCORE:");

}

void loop() {

  TV.select_font(font4x6);

 
 /*NOTE: draw_line accepts doubles*/
 //X0,Y0,X1,Y1,COLOR
 // (0,0) upper-left
 // (0,94.5) bottom-left
 // (115, 94.5) //bottom-right 
 // (115, 0) upper-right
  TV.draw_line(0,8,0,94.5,WHITE); //left-line 
  TV.draw_line(57.5,8,57.5,94.5,WHITE);  //middle-line
  TV.draw_line(115,8,115,94.5,WHITE); //right-line
  TV.draw_line(0,8,115,8,WHITE); // top-line 
  TV.draw_line(0,94.5,115,94.5,WHITE); // bottom-line
  TV.draw_line(0,80,115,80,WHITE); // seperator  
  TV.print(0,0,"SCORE:");
box2y = box2y+4;
 testScore++;
 TV.print(25,0, testScore);
 TV.draw_rect(x,y++,10,10,WHITE);
 TV.draw_rect(80,box2y,10,10,WHITE);
  delay(100);
  TV.clear_screen();


}
/*void rectRefresh() {
 obj.draw_rect(x,y,20,20,WHITE,BLACK);

}*/
void intro() {
/*unsigned char w,l,wb;
  int index;
  w = pgm_read_byte(TVOlogo);
  l = pgm_read_byte(TVOlogo+1);
  if (w&7)
    wb = w/8 + 1;
  else
    wb = w/8;
  index = wb*(l-1) + 2;
  for ( unsigned char i = 1; i < l; i++ ) {
    TV.bitmap((TV.hres() - w)/2,0,TVOlogo,index,w,i);
    index-= wb;
    TV.delay(50);
  }
  for (unsigned char i = 0; i < (TV.vres() - l)/2; i++) {
    TV.bitmap((TV.hres() - w)/2,i,TVOlogo);
    TV.delay(50);
  }
  TV.delay(3000);
  TV.clear_screen();
}

void printcube() {
  //calculate 2d points
  for(byte i = 0; i < 8; i++) {
    cube2d[i][0] = (unsigned char)((cube3d[i][0] * view_plane / cube3d[i][2]) + (TV.hres()/2));
    cube2d[i][1] = (unsigned char)((cube3d[i][1] * view_plane / cube3d[i][2]) + (TV.vres()/2));
  }
  TV.delay_frame(1);
  TV.clear_screen();
  draw_cube();
}

void zrotate(float q) {
  float tx,ty,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    ty = cube3d[i][1] - yOff;
    temp = tx * cos(q) - ty * sin(q);
    ty = tx * sin(q) + ty * cos(q);
    tx = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][1] = ty + yOff;
  }
}

void yrotate(float q) {
  float tx,tz,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    tz = cube3d[i][2] - zOff;
    temp = tz * cos(q) - tx * sin(q);
    tx = tz * sin(q) + tx * cos(q);
    tz = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][2] = tz + zOff;
  }
}

void xrotate(float q) {
  float ty,tz,temp;
  for(byte i = 0; i < 8; i++) {
    ty = cube3d[i][1] - yOff;
    tz = cube3d[i][2] - zOff;
    temp = ty * cos(q) - tz * sin(q);
    tz = ty * sin(q) + tz * cos(q);
    ty = temp;
    cube3d[i][1] = ty + yOff;
    cube3d[i][2] = tz + zOff;
  }
}

void draw_cube() {
  TV.draw_line(cube2d[0][0],cube2d[0][1],cube2d[1][0],cube2d[1][1],WHITE);
  TV.draw_line(cube2d[0][0],cube2d[0][1],cube2d[2][0],cube2d[2][1],WHITE);
  TV.draw_line(cube2d[0][0],cube2d[0][1],cube2d[4][0],cube2d[4][1],WHITE);
  TV.draw_line(cube2d[1][0],cube2d[1][1],cube2d[5][0],cube2d[5][1],WHITE);
  TV.draw_line(cube2d[1][0],cube2d[1][1],cube2d[3][0],cube2d[3][1],WHITE);
  TV.draw_line(cube2d[2][0],cube2d[2][1],cube2d[6][0],cube2d[6][1],WHITE);
  TV.draw_line(cube2d[2][0],cube2d[2][1],cube2d[3][0],cube2d[3][1],WHITE);
  TV.draw_line(cube2d[4][0],cube2d[4][1],cube2d[6][0],cube2d[6][1],WHITE);
  TV.draw_line(cube2d[4][0],cube2d[4][1],cube2d[5][0],cube2d[5][1],WHITE);
  TV.draw_line(cube2d[7][0],cube2d[7][1],cube2d[6][0],cube2d[6][1],WHITE);
  TV.draw_line(cube2d[7][0],cube2d[7][1],cube2d[3][0],cube2d[3][1],WHITE);
  TV.draw_line(cube2d[7][0],cube2d[7][1],cube2d[5][0],cube2d[5][1],WHITE);
*/}
