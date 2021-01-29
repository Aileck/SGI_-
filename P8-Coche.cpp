
#define PROYECTO "ISGI::S1E09::Adios Mundo"
#include <sstream>
#include <iostream> // Biblioteca de entrada salida
#include <freeglut.h> // Biblioteca grafica
#include <../Utilidades.h>	
static GLint ruta;
float posX, posZ = 0;
float velocidad = 0;
float giro = 0;
int A = 10, T = 100;
int loopPanel = 1;
bool primeraVez = true;
static GLuint carretera, desert, panel1, panel2, panel3,pata;
GLint anchura = 4;
GLfloat dir_central[] = { 0,-1,0 };
bool alambrico,niebla ,nocturno = false;
int frame = 0;



// Modo Alambrico o Solido

void loadTexture()

{

	glBindTexture(GL_TEXTURE_2D, desert);
	loadImageFile((char*)"desert.jpg");
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, desert);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void loadBackground()
// Funcion de carga de la textura actual como fondo de la ventana
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
	glLoadIdentity();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING); 
	glEnable(GL_TEXTURE_2D); 
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glBegin(GL_POLYGON); 
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix(); 
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	cout << "Flecha izquierda / derecha: giro del veh¨ªculo" << endl;
	cout << "Flecha arriba / abajo : aumento / disminuci¨®n de la velocidad" << endl;
	cout << "S / s : Activa / desactiva un modelo simple en al¨¢mbrico de la pr¨¢ctica 6 sin luces ni texturas" << endl;
	cout << "L / l : Cambia entre modo diurno / nocturno" << endl;
	cout << "N / n: Cambia el estado de la niebla (on/off)" << endl;

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &carretera);
	glBindTexture(GL_TEXTURE_2D, carretera);
	loadImageFile((char*)"road.jpg");

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &panel1);
	glBindTexture(GL_TEXTURE_2D, panel1);
	loadImageFile((char*)"ari.jpg");

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &panel2);
	glBindTexture(GL_TEXTURE_2D, panel2);
	loadImageFile((char*)"tt.jpg");

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &panel3);
	glBindTexture(GL_TEXTURE_2D, panel3);
	loadImageFile((char*)"teaparty.jpg");


	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &pata);
	glBindTexture(GL_TEXTURE_2D, pata);
	loadImageFile((char*)"pata.jpg");

	//glEnable(GL_TEXTURE_2D);
	//glGenTextures(1, &desert);
	//glBindTexture(GL_TEXTURE_2D, desert);
	//loadImageFile((char*)"desert.jpg");
	GLfloat LunaAmbiental[] = { 0.05,0.05,0.05,1 };
	GLfloat LunaDifusa[] = { 0.05,0.05,0.05,1 };
	GLfloat LunaEspecular[] = { 0.00,0.00,0.00,1 };

	GLfloat VehAmbiental[] = { 0.2,0.2,0.2,1 };
	GLfloat VehDifusa[] = { 1,1,1,1 };
	GLfloat VehEspecular[] = { 0.3,0.3,0.3,1 };

	GLfloat FarolAmbiental[] = { 0.00,0.00,0.00,1 };
	GLfloat FarolDifusa[] = { 0.5,0.5,0.2,1 };
	GLfloat FarolEspecular[] = { 0.00,0.00,0.00,1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, LunaAmbiental);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LunaDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LunaEspecular);

	glLightfv(GL_LIGHT1, GL_AMBIENT, VehAmbiental);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, VehDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, VehEspecular);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);

	glLightfv(GL_LIGHT2, GL_AMBIENT, FarolAmbiental);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, FarolDifusa);
	glLightfv(GL_LIGHT2, GL_SPECULAR, FarolEspecular);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);

	glLightfv(GL_LIGHT3, GL_AMBIENT, FarolAmbiental);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, FarolDifusa);
	glLightfv(GL_LIGHT3, GL_SPECULAR, FarolEspecular);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);

	glLightfv(GL_LIGHT4, GL_AMBIENT, FarolAmbiental);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, FarolDifusa);
	glLightfv(GL_LIGHT4, GL_SPECULAR, FarolEspecular);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);

	glLightfv(GL_LIGHT5, GL_AMBIENT, FarolAmbiental);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, FarolDifusa);
	glLightfv(GL_LIGHT5, GL_SPECULAR, FarolEspecular);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);

}

void onKey(unsigned char tecla, int x, int y)
// Funcion de atencion al teclado
{
	switch (tecla) {
	case 's':
	case 'S': {
		if(alambrico == false){
			glPushMatrix();
			glClearColor(0, 0, 0, 1);
			//glEnable(GL_LIGHTING);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColorMaterial(GL_FRONT, GL_DIFFUSE);
			glDisable(GL_TEXTURE_2D);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
			alambrico = true;
			nocturno = false;
			niebla = false;
		}
		else{
			glPushMatrix();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDisable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
			alambrico = false;
		}

		break;
	}

	case 'L': 
	case 'l': {
		if (nocturno == false) {

			glPushMatrix();
			glClearColor(0, 0, 0, 1);
			glEnable(GL_LIGHTING);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColorMaterial(GL_FRONT, GL_DIFFUSE);

			glPopMatrix();
			nocturno = true;
			alambrico = false;
			niebla = false;
		}
		else {
			glDisable(GL_LIGHTING);
			nocturno = false;
		}
		break;
	}
	case 'N':
	case 'n': {
		if (niebla == false) {

			glPushMatrix();
			glEnable(GL_FOG);
			static GLfloat cniebla[] = { 1,1,1,1 };
			glFogfv(GL_FOG_COLOR,cniebla);
			glFogf(GL_FOG_DENSITY,0.3);
			glPopMatrix();
			niebla = true;
			alambrico = false;
			nocturno = false;
		}
		else {
			glDisable(GL_FOG);
			niebla = false;
		}
		break;
	}

	case 27: //esc
		exit(0);
	}
	glutPostRedisplay();
}
void display()
// Funcion de atencion al dibujo
{
	if (niebla == true) {
		glClearColor(1, 1, 1, 1);
	}
	else {
		
		glClearColor(0, 0, 0, 1);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	GLfloat Pos_light1[] = { 0.00,0.00,0.00};
	GLfloat Pos_light2[] = { 0.00,0.00,0.00};
	GLfloat Pos_light3[] = { 0.00,0.00,0.00};
	GLfloat Pos_light4[] = { 0.00,0.00,0.00};

	bool primer_light1 = false;
	bool primer_light2 = false;


	if (nocturno == true) {
		//Luz
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		//glEnable(GL_LIGHT3);
		//glEnable(GL_LIGHT4);
		//glEnable(GL_LIGHT5);

		GLfloat dir_apunta[] = { 0,-1,0 };

		GLfloat pos_luna[] = { 0,10,0,0 };
		glLightfv(GL_LIGHT0, GL_POSITION, pos_luna);

		GLfloat pos_farol[] = { 0,	2, -5, 1 }; //Puntal

		glLightfv(GL_LIGHT1, GL_POSITION, pos_farol);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_apunta);



		
	};

	//gluLookAt(posX, 100, posZ, sin(giro) + posX, 0, cos(giro) + posZ, 0, 1, 0);
	gluLookAt(posX, 1, posZ, sin(giro) + posX, 1, cos(giro) + posZ, 0, 1, 0);


	if (alambrico == false && nocturno == false && niebla == false) {
		loadTexture();
		loadBackground();
	}

	
	//Genera camino
	for (int i = posZ; i < posZ + 100; i++) {
		//printf("%d", posZ + 100);
		GLfloat	v0[3] = { A * sin((i + 1) * ((2 * PI) / T)) - anchura,0, i + 1 };
		GLfloat v1[3] = { A * sin((i + 1) * ((2 * PI) / T)) + anchura,0, i + 1 };
		GLfloat v3[3] = { A * sin(i * ((2 * PI) / T)) - anchura,0,i };
		GLfloat v2[3] = { A * sin(i * ((2 * PI) / T)) + anchura,0,i };
		
		//Una copia
		GLfloat	aux0[3] = { A * sin((i + 1) * ((2 * PI) / T)) - anchura,0, i + 1 };
		GLfloat aux1[3] = { A * sin((i + 1) * ((2 * PI) / T)) + anchura,0, i + 1 };
		GLfloat aux3[3] = { A * sin(i * ((2 * PI) / T)) - anchura,0,i };
		GLfloat aux2[3] = { A * sin(i * ((2 * PI) / T)) + anchura,0,i };

		

		//quad(v0, v1, v2, v3, 10, 5);
		if (alambrico) {
			glPolygonMode(GL_BACK, GL_LINE);
			glPolygonMode(GL_FRONT, GL_LINE);
		}
		else {
			glPolygonMode(GL_BACK, GL_FILL);
			glPolygonMode(GL_FRONT, GL_FILL);
		}
		glBindTexture(GL_TEXTURE_2D, carretera);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		quadtex(v0, v1, v2, v3, 0,1,0,1,10, 5);

		//Panel anuncio
		if (i % 25 == 0) {


			//Posicionar
			v0[1] = { 4 }; // xz
			v1[1] = { 4 }; // xy
			v3[1] = { 8 }; // sz
			v2[1] = { 8 }; // sy
			v3[0] = v0[0];
			v2[0] = v1[0];
			v3[2] = v0[2];
			v2[2] = v1[2];




			glBindTexture(GL_TEXTURE_2D, panel1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

			//glPushMatrix();
			quadtex(v1, v0, v3, v2, 0, 1, 0, 1, 10, 5);
			//glPopMatrix();


			//Patas
			v3[1] = { 0 }; // sz
			v2[1] = { 0 }; // sy
			v3[0] = v1[0]; // sz
			v2[0] = v1[0]-1; // sy
			v0[0] = v1[0]- 1; // sy
			glBindTexture(GL_TEXTURE_2D, pata);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			//glPushMatrix();
			quadtex(v0, v1, v3, v2, 0, 1, 0, 1, 10, 5);
			//glPopMatrix();
			
			v0[0] = aux0[0];
			v0[1] = aux0[1];
			v0[2] = aux0[2];

			v1[0] = aux1[0];
			v1[1] = aux1[1];
			v1[2] = aux1[2];

			v2[0] = aux2[0];
			v2[1] = aux2[1];
			v2[2] = aux2[2];

			v3[0] = aux3[0];
			v3[1] = aux3[1];
			v3[2] = aux3[2];

			//Luces
			if(primer_light1 == false) { 
				//cout << frame;
				//quadtex(v0, v1, v3, v2, 0, 1, 0, 1, 10, 5);
				v0[1] = { 20 }; 
				v1[1] = { 20 }; // xz
				v2[1] = { 20 }; // xz
				v3[1] = { 20 }; // xz

				//Pos_light1[0] = v3[0];
				//Pos_light1[1] = v3[1];
				//Pos_light1[2] = v3[2];
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central);
				glLightfv(GL_LIGHT2, GL_POSITION, v0);
				glLightfv(GL_LIGHT2, GL_POSITION, v1);
				glLightfv(GL_LIGHT2, GL_POSITION, v2);
				glLightfv(GL_LIGHT2, GL_POSITION, v3);
				primer_light1 = true;
			}



			v0[1] = aux0[1];
			v1[1] = aux1[1];
			v2[1] = aux2[1];
			v3[1] = aux3[1];
		/*
		*  La otra pata comporta rara...
		* 
			v3[1] = { 0 }; // sz
			v2[1] = { 0 }; // sy
			v0[1] = { 0 }; // sz
			v1[1] = { 0 }; // sy
			v3[0] = v0[0]; // sz
			v2[0] = v0[0] ; // sy
			v1[0] = v0[0] ; // sy

			glPushMatrix();
			quadtex(v0, v1, v3, v2, 0, 1, 0, 1, 10, 5);
			glPopMatrix();
			*/
		}
		if (i % 50 == 0) {


			//Posicionar
			v0[1] = { 4 };
			v1[1] = { 4 };
			v3[1] = { 8 };
			v2[1] = { 8 };
			v3[0] = v0[0];
			v2[0] = v1[0];
			v3[2] = v0[2];
			v2[2] = v1[2];


				glBindTexture(GL_TEXTURE_2D, panel2);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				glPushMatrix();
				quadtex(v1, v0, v3, v2, 0, 1, 0, 1, 10, 5);
				glPopMatrix();

				//Patas
				v3[1] = { 0 }; // sz
				v2[1] = { 0 }; // sy
				v3[0] = v1[0]; // sz
				v2[0] = v1[0] - 1; // sy
				v0[0] = v1[0] - 1; // sy
				glBindTexture(GL_TEXTURE_2D, pata);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				//glPushMatrix();
				quadtex(v0, v1, v3, v2, 0, 1, 0, 1, 10, 5);
				//glPopMatrix();

				v0[0] = aux0[0];
				v0[1] = aux0[1];
				v0[2] = aux0[2];

				v1[0] = aux1[0];
				v1[1] = aux1[1];
				v1[2] = aux1[2];

				v2[0] = aux2[0];
				v2[1] = aux2[1];
				v2[2] = aux2[2];

				v3[0] = aux3[0];
				v3[1] = aux3[1];
				v3[2] = aux3[2];

				//Luces
				if (primer_light2 == false) {
					//cout << frame;
					//quadtex(v0, v1, v3, v2, 0, 1, 0, 1, 10, 5);
					v0[1] = { 20 };
					v1[1] = { 20 }; // xz
					v2[1] = { 20 }; // xz
					v3[1] = { 20 }; // xz

					//Pos_light1[0] = v3[0];
					//Pos_light1[1] = v3[1];
					//Pos_light1[2] = v3[2];
					glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central);
					glLightfv(GL_LIGHT3, GL_POSITION, v0);
					glLightfv(GL_LIGHT3, GL_POSITION, v1);
					glLightfv(GL_LIGHT3, GL_POSITION, v2);
					glLightfv(GL_LIGHT3, GL_POSITION, v3);
					primer_light2 = true;
				}



				v0[1] = aux0[1];
				v1[1] = aux1[1];
				v2[1] = aux2[1];
				v3[1] = aux3[1];



		}
		if (i % 75 == 0) {
			//Posicionar
			v0[1] = { 4 };
			v1[1] = { 4 };
			v3[1] = { 8 };
			v2[1] = { 8 };
			v3[0] = v0[0];
			v2[0] = v1[0];
			v3[2] = v0[2];
			v2[2] = v1[2];


			glBindTexture(GL_TEXTURE_2D, panel3);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glPushMatrix();
			quadtex(v1, v0, v3, v2, 0, 1, 0, 1, 10, 5);
			glPopMatrix();
			//Patas
			v3[1] = { 0 }; // sz
			v2[1] = { 0 }; // sy
			v3[0] = v1[0]; // sz
			v2[0] = v1[0] - 1; // sy
			v0[0] = v1[0] - 1; // sy
			glBindTexture(GL_TEXTURE_2D, pata);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			//glPushMatrix();
			quadtex(v0, v1, v3, v2, 0, 1, 0, 1, 10, 5);
			//glPopMatrix();

			v0[0] = aux0[0];
			v0[1] = aux0[1];
			v0[2] = aux0[2];

			v1[0] = aux1[0];
			v1[1] = aux1[1];
			v1[2] = aux1[2];

			v2[0] = aux2[0];
			v2[1] = aux2[1];
			v2[2] = aux2[2];

			v3[0] = aux3[0];
			v3[1] = aux3[1];
			v3[2] = aux3[2];

			//Luces

			v0[1] = { 20 }; // xz
			v1[1] = { 20 }; // xy
			v3[1] = { 20 }; // sz
			v2[1] = { 20 }; // sy

			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central);


			glLightfv(GL_LIGHT4, GL_POSITION, v1);
			glLightfv(GL_LIGHT4, GL_POSITION, v2);
			glLightfv(GL_LIGHT4, GL_POSITION, v0);
			glLightfv(GL_LIGHT4, GL_POSITION, v3);



			v0[1] = aux0[1];
			v1[1] = aux1[1];
			v2[1] = aux2[1];
			v3[1] = aux3[1];

		}
	}
	//printf(" LightX %d ", Pos_light1[0]);
	//printf(" LightZ %d ", Pos_light1[3]);
	//printf(" PosX %d ", posX);
	//printf(" PosZ %d \n", posZ);
	//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central);
	//glLightfv(GL_LIGHT2, GL_POSITION, Pos_light1);
	//frame = frame + 1;
	//Genera fondo
	//glPushMatrix();
	//GLfloat	v0[3] = { 200+posX,-0.01, -200};
	//GLfloat	v1[3] = { 200 + posX,-0.01, 200};
	//GLfloat	v2[3] = { -200 + posX,-0.01, 200 };
	//GLfloat	v3[3] = { -200 + posX,-0.01, -200 };
	
	//glBindTexture(GL_TEXTURE_2D, desert);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	//quad(v0, v1, v2, v3, 500, 500);

	//glPopMatrix();
	//loadTexture();
	//loadBackground();

}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{

	glViewport(0, 0, w, h);
	float ra = float(w) / float(h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ra, 1, 100);
}

void onIdle() {

	//cout << "ejecutaidle";

	posX += velocidad * sin(giro) /40;
	posZ += velocidad * cos(giro) /40;

	std::stringstream title;
	if (alambrico == true) {
		title << "Modo Alambrico. Velocidad: " << velocidad;
	}
	else if (nocturno == true){
		title << "Modo nocturno. Velocidad: " << velocidad;
	}
	else if (niebla == true) {
		title << "Modo bajo visibilidad. Velocidad: " << velocidad;
	}
	else {
		title << "Proyecto conducci¨®n. Velocidad: " << velocidad;
	}
	glutSetWindowTitle(title.str().c_str());

	//gluLookAt(posX, 100, posZ, sin(giro) + posX, 0, cos(giro) + posZ, 0, 1, 0);
	glutSwapBuffers();
	glutPostRedisplay();
}

void onSpecialKey(int tecla, int x, int y)
// Listener de las flechas de movimiento
{
	primeraVez = false;
	switch (tecla) {
	case GLUT_KEY_UP: {
		velocidad += 0.1;
		break;
	}
	case GLUT_KEY_DOWN: {
		if (velocidad >= 0.01f)
			velocidad -= 0.1;
		else
			velocidad = 0;
		break;
	}
	case GLUT_KEY_LEFT: {
		giro += 0.017; //Suma 1 grado
		break;
	}
	case GLUT_KEY_RIGHT: {
		giro -= 0.017;
		break;
	}
	}

	glutPostRedisplay();
}


void main(int argc, char** argv)
// Programa principal
{
	FreeImage_Initialise();
	glutInit(&argc, argv); // Inicializacion de GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Alta de buffers a usar
	glutInitWindowSize(940, 780); // Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO); // Creacion de la ventana con su titulo
	std::cout << PROYECTO << " running" << std::endl; // Mensaje por consola
	glutDisplayFunc(display); //Funcion display
	glutReshapeFunc(reshape); //Funcion reshape
	glutIdleFunc(onIdle);
	init();
	glutKeyboardFunc(onKey);
	glutSpecialFunc(onSpecialKey);
	glutMainLoop(); //Crear programass
	FreeImage_DeInitialise();
}
