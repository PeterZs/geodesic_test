#ifndef _TEST_
#define _TEST_

#include <math.h>
#include "object.h"
#include "camera.h"

object* myobject;
camera* mycamera;
int kind; 
int count;//���ռ���


void saveAsVTK();
void drawObject();
void keyboard(unsigned char key,int x,int y);
void reshape(int w,int h) ;
void init();
void lightControl();
void makeSmooth();
void display(void);
void drawObject();
void saveSceneImage();
void saveBmp(const char* name,int width,int height,unsigned char* data);
#endif
