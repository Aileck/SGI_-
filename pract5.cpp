#include <iostream>
#include <freeglut.h>
#include <cmath>
#include <ctime>
#define PI 3.14159265358979323846

static GLint poligono;
static GLint circulo;
static GLint puntos;

float posz = 0;


time_t h, m, s;

void init()
{
	time_t now = time(0);
	//printf("%d", t);
	h = (now / 3600) % 24 + 1;
	m = (now / 60) % 60;
	s = now % 60;
	//printf("%d %d %d %d", h,m,s);
	poligono = glGenLists(1);	// Obtiene el identificador de la lista 
	glClear(GL_COLOR_BUFFER_BIT);
	glNewList(poligono, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_TRIANGLE_STRIP);


	glVertex3f(cos(0 * 2 * PI / 3 + (PI / 2)), sin(0 * 2 * PI / 3 + (PI / 2)), 0);
	glVertex3f(0.7 * cos(0 * 2 * PI / 3 + (PI / 2)), 0.7 * sin(0 * 2 * PI / 3 + (PI / 2)), 0);

	glVertex3f(cos(1 * 2 * PI / 3 + (PI / 2)), sin(1 * 2 * PI / 3 + (PI / 2)), 0);
	glVertex3f(0.7 * cos(1 * 2 * PI / 3 + (PI / 2)), 0.7 * sin(1 * 2 * PI / 3 + (PI / 2)), 0);

	glVertex3f(cos(2 * 2 * PI / 3 + (PI / 2)), sin(2 * 2 * PI / 3 + (PI / 2)), 0);
	glVertex3f(0.7 * cos(2 * 2 * PI / 3 + (PI / 2)), 0.7 * sin(2 * 2 * PI / 3 + (PI / 2)), 0);

	glVertex3f(cos(0 * 2 * PI / 3 + (PI / 2)), sin(0 * 2 * PI / 3 + (PI / 2)), 0);
	glVertex3f(0.7 * cos(0 * 2 * PI / 3 + (PI / 2)), 0.7 * sin(0 * 2 * PI / 3 + (PI / 2)), 0);

	glEnd();
	glBegin(GL_TRIANGLE_STRIP);


	glVertex3f(cos(0 * 2 * PI / 3 - (PI / 2)), sin(0 * 2 * PI / 3 - (PI / 2)), 0);
	glVertex3f(0.7 * cos(0 * 2 * PI / 3 - (PI / 2)), 0.7 * sin(0 * 2 * PI / 3 - (PI / 2)), 0);

	glVertex3f(cos(1 * 2 * PI / 3 - (PI / 2)), sin(1 * 2 * PI / 3 - (PI / 2)), 0);
	glVertex3f(0.7 * cos(1 * 2 * PI / 3 - (PI / 2)), 0.7 * sin(1 * 2 * PI / 3 - (PI / 2)), 0);

	glVertex3f(cos(2 * 2 * PI / 3 - (PI / 2)), sin(2 * 2 * PI / 3 - (PI / 2)), 0);
	glVertex3f(0.7 * cos(2 * 2 * PI / 3 - (PI / 2)), 0.7 * sin(2 * 2 * PI / 3 - (PI / 2)), 0);

	glVertex3f(cos(0 * 2 * PI / 3 - (PI / 2)), sin(0 * 2 * PI / 3 - (PI / 2)), 0);
	glVertex3f(0.7 * cos(0 * 2 * PI / 3 - (PI / 2)), 0.7 * sin(0 * 2 * PI / 3 - (PI / 2)), 0);

	glEnd();
	glFlush();
	glPopAttrib();
	glEndList();

	circulo = glGenLists(1);	// Obtiene el identificador de la lista 
	glClear(GL_COLOR_BUFFER_BIT);
	glNewList(circulo, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_POLYGON);

	for (int i = 0; i < 500; i = i + 1) {
		glVertex3f(cos(i * 2 * PI / 500 ), sin(i * 2 * PI / 500), 0);

	}


	glEnd();
	glFlush();
	glPopAttrib();
	glEndList();

	puntos = glGenLists(1);	// Obtiene el identificador de la lista 
	glClear(GL_COLOR_BUFFER_BIT);
	glNewList(puntos, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_POINTS);

	for (int i = 0; i < 12; i = i + 1) {
		glVertex3f(cos(i * 2 * PI / 12 ), sin(i * 2 * PI / 12), 0);

	}


	glEnd();
	glFlush();
	glPopAttrib();
	glEndList();
}



void display() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 1, 3, 0, 0, 0, 0, 1, 0);
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
		glColor3f(0.439, 0.502, 0.565);
		glRotated(0, 0, 0, 0);
		glCallList(circulo);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.412, 0.412, 0.412);
		glScalef(0.9,0.9,0.9);
		glTranslatef(0,0.01,0);
		glRotated(0, 0, 1, 0);
		glCallList(circulo);
	glPopMatrix();

	glPushMatrix();
		glPointSize(10);
		glScalef(0.8, 0.8, 0.8);
		glColor3f(0, 0, 0);
		glCallList(puntos);
	//glColor3f(1.0, 0.2, 0.2);
	glPopMatrix();


	float pto_total = 12 * 60 * 60;
	if (h > 12) {
		h = h - 12;
	}
	float pto_hora = h * 60 * 60 + m * 60;
	float por_hora = (pto_hora / pto_total) * 360;
	float por_min = (float)m / 60 * 360;
	float por_seg = (float)s * 360 / 60;

	glPushMatrix();
		glColor4f(1.0, 0.0, 1.0, 0.5);  
		glRotatef(por_hora - 90, 0, 0, -1);
		glTranslatef(0.25, 0, 0);
		glScalef(0.5, 0.03, 0.03);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor4f(0.0, 1.0, 0.0, 0.5);
		glRotatef(por_min - 90, 0, 0, -1);
		glTranslatef(0.35, 0, 0);
		glScalef(0.8, 0.03, 0.03);
		glutSolidCube(0.8);
	glPopMatrix();

	glPushMatrix();
		glColor4f(0.0, 0.0, 1.0, 0.5);  
		glRotatef(- por_seg + 90, 0.0, 0.0, 1.0);
		glTranslatef(0.35, 0, 0);
		glScalef(1.3, 0.03, 0.03);
		glutSolidCube(0.6);
	glPopMatrix();



	glPushMatrix();
		glColor3f(0, 0, 0);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(posz, posz, posz, 1.0);
		glutWireSphere(1.0, 6, 6);
	glPopMatrix();


	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	float razon = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	float eye = sqrt(2 * 2 + 1 * 1 + 3 * 3 ); //Punto ojo, raiz x*x + y*y + z*z
	float d = abs(0-eye);
	gluPerspective(2 * (asin(1 / d) * (180 / 3.1416)), razon, 1, 20);
	//gluPerspective(45, razon, 1, 10);
}

void onIdle(){
		time_t now = time(0);
		//printf("%d", t);
		h = (now / 3600) % 24 + 1;
		m = (now / 60) % 60;
		s = now % 60;

		//std::cout << posz << std::endl; //Consola
		posz += 0.01;

		glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); //Inicializa glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //Crear buffer
	glutInitWindowSize(500, 500); //Tamano ventana
	glutCreateWindow("Reloj"); //Crea ventana  + su titulo
	std::cout << "Reloj" << std::endl; //Consola
	glutDisplayFunc(display); //Funcion display
	glutReshapeFunc(reshape); //Funcion reshape
	glutIdleFunc(onIdle);
	init();
	glutMainLoop(); //Crear programass
}