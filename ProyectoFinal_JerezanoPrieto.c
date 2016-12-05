#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CEN 0
#define DER 1
#define IZQ 2

//Elaborado por:
//Jerezano Balderas Fernando Rafael
//Prieto Bautista Diego

//Parametros lookAT
float x=10,y=10,z=25;

//Atributos Cubo
int cubo=1;
float pos_cubo_x=0;
float pos_cubo_z=-200;
float inc_cubo_z=0.100;
float inc_inc_cubo = 0.005;

//Atributos esfera
int saltar = 1;
float pos_esfera_x = 0;
float pos_esfera_y= 0;
float inc_esfera_y = 0;

void dibuja_carriles(){

    glLoadIdentity();
    gluLookAt(x,y,z,0,0,0,x,y+1,z);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3f(-60,0,150);
    glVertex3f(-60,0,-150);
    glVertex3f(-20,0,150);
    glVertex3f(-20,0,-150);

    glVertex3f(20,0,150);
    glVertex3f(20,0,-150);

    glVertex3f(60,0,150);
    glVertex3f(60,0,-150);
    glEnd();
}

void dibuja_cubo(){
    glLoadIdentity();
    gluLookAt(x,y,z,0,0,0,x,y+1,z);
    glColor3f(0.8,0.8,0.8);

    if(cubo==1){
        //Genera un numero aleatoria entre 0 y 2
        //para saber en cual carril se va a dibujar
        int r = rand()%3;

        switch(r){
            case IZQ://Izquierda
                pos_cubo_x = -40;
                break;
            case CEN://Centro
                pos_cubo_x = 0;
                break;
            case DER://Derecha
                pos_cubo_x = 40;
                break;
        }
        cubo = 0;
    }
    glTranslatef(pos_cubo_x,0,pos_cubo_z);
    glutSolidCube(15);

}

void dibuja_esfera(){
    glLoadIdentity();
    gluLookAt(x,y,z,0,0,0,x,y+1,z);
    glColor3f(0,0,0);

    glTranslatef(pos_esfera_x,pos_esfera_y,150);
    glRotatef(45,1,1,1);
    glutWireSphere(15,15,15);
}

void dibuja_ejes(){
	glBegin(GL_LINES);

	//Eje X
	//Rojo
	glColor3f(1.0,0.0,0.0 );
	glVertex3f(-200,0,0);
	glVertex3f(200,0,0);

	//Eje Y
	//Verde
    glColor3f(0.0,1.0,0.0 );
	glVertex3f(0,-200,0);
	glVertex3f(0,200,0);

	//Eje Z
	//Azul
	glColor3f(0.0,0.0,1.0);
	glVertex3f(0,0,-200);
	glVertex3f(0,0,200 );

	glEnd();
}

void display(){

    glLoadIdentity();
    gluLookAt(x,y,z,0,0,0,x,y+1,z);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    dibuja_ejes();
    dibuja_carriles();
    dibuja_cubo();
    dibuja_esfera();


    pos_cubo_z += inc_cubo_z;
    if(pos_cubo_z>=200){
        pos_cubo_z = -200;
        inc_cubo_z += inc_inc_cubo;
        cubo = 1;
    }

    pos_esfera_y+=inc_esfera_y;
    if(pos_esfera_y<0){
        inc_esfera_y = 0;
        saltar = 1;
    }
    if(pos_esfera_y>=25){
        inc_esfera_y *= -1;
    }
    glFlush ();
	glutSwapBuffers();


}

void keyboard(unsigned char key, int x, int y){

    switch(key){
        case '1':
            //Izquierda
            pos_esfera_x = -40;
            break;
        case '2':
            //Centro
            pos_esfera_x = 0;
            break;
        case '3':
            //Derecha
            pos_esfera_x = 40;
            break;
        case '4':
            if(saltar){
                inc_esfera_y = 0.050;
                saltar = 0;
            }
            break;
    }
}

void reshape(int width, int height){
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-200,200,-200,200,-200,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void init(){
	glClearColor(1,1,1,0);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv){
    srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Esferita rodando");

	init();
	glutDisplayFunc(display);

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}

