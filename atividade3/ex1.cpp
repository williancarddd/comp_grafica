#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

GLfloat fAspect = 1;
GLfloat escala = 1.0;
GLfloat rotacao = 0.0;
GLfloat translacao = 0.0;

void Desenha(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100,fAspect,0.5,500);
  //glFrustum(0.4, 0.4, 0.4,0.4,0.3,0.8);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(40,60,100, 0,0,0, 0,1,0);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0,0,1);
  //glutWireCube(50);
  glTranslatef(translacao,0,0);
  glRotatef(rotacao,1,1,1);
  glScalef(escala,escala,escala);
  glutWireTeapot(30);
  //glutWireTorus(30, 50,10,10);
  //glutWireSphere(30,10,10);
  //glutWireCone(30, 50,10,10);
  glFlush();     
}

void Teclado (unsigned char key, int x, int y)
{	
  switch(key){
    case 'a':
      escala = escala + 0.1;
      break;
    case 'A':
      escala = escala - 0.1;
      break;
    case 'r':
      rotacao = translacao + 0.1;
      break;
    case 'R':
      rotacao = translacao -0.1;
      break;
    case 't':
      translacao += 0.06;
      printf("%f\n", translacao);
      break;
    case 'T':
      translacao -= 0.06;
      break;
  }
  glutPostRedisplay();
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glLineWidth(2.0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(5,5); 
	glutInitWindowSize(450,450); 
 	glutCreateWindow("Desenho de um cubo");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc (Teclado);
	glutMainLoop();
	return 0;
}