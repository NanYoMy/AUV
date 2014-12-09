#include <GL/glut.h>
#include "define.h"
#include "texture.h"

extern const int WIDTH;
extern const int HEIGHT;
int x=0,y=0,z=-10,roll=0,pitch=0,heading=0;
static GLuint texName;
static int s_h=WIDTH,s_w=HEIGHT;
/*if we declare a arry point in GLubyte***, then we should new all the memeory from heap*/
GLubyte* texImage[WIDTH][HEIGHT];

void logParameter(){

	debug(x);
	debug(z);
	debug(y);
	debug(heading);
	debug(roll);
	debug(pitch);


}


void readImage(){

	//i haven't delete it ,memory leak here
	for(int i=0;i<HEIGHT;i++){

		for(int j=0;j<WIDTH;j++){

			texImage[i][j]=new GLubyte[4];
		}
	}

	for(int i=0;i<WIDTH;i++){ 

		for(int j=0;j<HEIGHT;j++){

			texImage[i][j][0]=0;
			texImage[i][j][1]=0;
			texImage[i][j][2]=0;
			texImage[i][j][3]=0;

		}		

	}


}

void init(){


	readImage();
	glClearColor(0.0,0.0,0.0,0.0);
	//why always use shademode
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_SCISSOR_TEST);

	makeLand(texImage,WIDTH,HEIGHT,2);



}

void makeTexture(){


	//make textrue
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D,texName);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,WIDTH,HEIGHT,0,GL_RGBA,GL_UNSIGNED_BYTE,texImage);



}

void display(void){


	makeTexture();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);

	glPushMatrix();

	//glTranslatef(x,y,z);


	glBegin(GL_QUADS);

	glTexCoord2f(0.0,0.0);
	glVertex3f(-3,-3,0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-3,3,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(3,3,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(3,-3,0);

	glEnd();

	glPopMatrix();
}


void keyboard(unsigned char key,int x_mouse,int y_mouse){

	log("------------------");
	log("step into keyboard");

	logParameter();

	switch(key){

		case 'w':{

					 log("before modify y");
					 debug(y)
					 y=y-1;
					 log("after modify y");
					 debug(y)
					 glutPostRedisplay();
					 break;
				 }

		case 's':{
					 y=y+1;
					 debug(y)
					 log("hit s  key");
					 glutPostRedisplay();
					 break;
				 }
		case 'a':{
					 x=x-1;
					 debug(x)
					 glutPostRedisplay();
					 break;
				 }
		case 'd':{
					 x=x+1;
					 debug(x)
					 glutPostRedisplay();
					 break;
				 }
		case 'q':{
					 z=z+1;
					 glutPostRedisplay();
					 break;
				 }
		case 'e':{
					 z=z-1;
					 glutPostRedisplay();
					 break;
				 }
		case 'u':{
					 heading=(heading+10)%360;
					 glutPostRedisplay();
					 break;
				 }
		case 'j':{
					 heading=(heading-10)%360;
					 glutPostRedisplay();
					 break;
				 }
		case 'i':{
					 roll=(roll+10)%360;
					 glutPostRedisplay();
					 break;
				 }
		case 'k':{
					 roll=(roll-10)%360;
					 glutPostRedisplay();
					 break;
				 }
		case 'o':{
					 pitch=(pitch+10)%360;
					 glutPostRedisplay();
					 break;
				 }
		case 'l':{
					 pitch=(pitch-10)%360;
					 glutPostRedisplay();
					 break;
				 }
		case 'r':{
					 x=0;
					 z=-10;
					 y=0;
					 heading=0;
					 pitch=0;
					 roll=0;
					 glutPostRedisplay();
					 break;
				 }
		default: break;


	}

	log("after modify parameter");
	logParameter();



}
//the reshape method must involk before display!!
void reshape(int w, int h){

	s_h=h;
	s_w=w;

}

void displayTwo(){

	int h=s_h;
	int w=s_w;
	glViewport(0,0,(GLsizei)h/2,(GLsizei)w);
	glScissor(0,0,(GLsizei)h/2,(GLsizei)w);
	//set the projection 
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60.0,(GLfloat)h/(GLfloat)w,1.0,200.0);
	//set the model
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pilotView(x,y,z,heading,pitch,roll);
	//gluLookAt(0.0,0.0,-5.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	display();

	glViewport((GLsizei)h/2,0,(GLsizei)h/2,(GLsizei)w);
	glScissor((GLsizei)h/2,0,(GLsizei)h/2,(GLsizei)w);
	//set the projection 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,(GLfloat)h/(GLfloat)w,1.0,200.0);
	//set the model
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pilotView(x,y,z,heading,pitch,roll);
	//gluLookAt(0.0,0.0,-5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	display();

	glutSwapBuffers();

}

int main(int argc,char** argv){

	logParameter();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(displayTwo);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;

}

