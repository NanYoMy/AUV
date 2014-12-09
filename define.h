#ifndef DEFINE_H
#define DEFINE_H
#include <iostream>
#include <GL/glut.h>

#define debug(A) std::cout<<#A<<":"<<A<<std::endl;
#define log(A) std::cout<<A<<std::endl;
const int WIDTH =256;
const int HEIGHT =256;

void pilotView(GLdouble x, GLdouble y, GLdouble z, GLdouble roll, GLdouble pitch, GLdouble heading){


	glRotated(roll,0.0,0.0,1.0);
	glRotated(pitch,0.0,1.0,0.0);
	glRotated(heading,1.0,0.0,0.0);
	glTranslated(x,y,z);

}

#endif
