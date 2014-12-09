#ifndef TEXTURE_H
#define TEXTURE_H
#include "define.h"
#include <GL/glut.h>

extern const int WIDTH;
extern const int HEIGHT;

void makeLand(GLubyte* data[WIDTH][HEIGHT],int width,int height,int lineWidth){

	int left=(width-lineWidth)/2;
	int right=(width+lineWidth)/2;


	for(int i=left;i<right;i++){

		for(int j=0;j<height;j++){

			data[i][j][0]=255;
			data[i][j][1]=0;
			data[i][j][2]=0;
			data[i][j][3]=GLubyte(255);

		}		

	}

}

void makeLand2(GLubyte* data[WIDTH][HEIGHT],int width,int height,int lineWidth){

	int c=0;
	for(int i=0;i<height;i++){

		for(int j=0;j<width;j++){

			c=(((i&0x8)==0)^((j&0x8)==0))*255;
			data[i][j][0]=c;
			data[i][j][1]=c;
			data[i][j][2]=c;
			data[i][j][3]=c;

		}		

	}
}
#endif
