#include <iostream>
#include <GL/glut.h>
#include "Camera.h"
#include <math.h>      // For math routines (such as sqrt & trig).
#define PI 3.14159265358979323846
using namespace std;
//float posCamx=0, posCamy=0, posCamz=5, lookCamx=0, lookCamy=0, lookCamz=0;
GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1.5;

GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0}; //Black Color
GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
GLfloat qaRed[] = {1.0, 0.0, 0.0, 1.0}; //White Color

static GLdouble viewer[]= {0.0, 0.0, 10.0};
static GLfloat theta = 0.0, speed = 0.05;
Camera*	camera;

void display(void);
void reshape(int x, int y);

void idleFunc(void)
{

     zRotated += 0.02;

    display();
}
void setLighting()
{
    // Set lighting intensity and color
    GLfloat qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat qaDiffuseLight[] = {1.0, 1.0, 0.8, 1.0};
    GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
    GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};

    // Light source position
    GLfloat qaLightPosition[]    = {0, 2, 2.5, 0.5};

    // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void setMaterialijo(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
}

void setmaterialPerl(){
    float MatAmbient[] = { 0.25f, 0.20725f, 0.20725f, 0.922f};
    float MatDiffuse[] = { 1.0f, 0.829f, 0.829f, 0.922f  };
    float MatSpecular[] = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
    float MatShininess = 11.264f;
    float black[] = {0.0f,0.0f,0.0f,1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
}

void setMaterialJade(){
    float mat_ambient[] ={ 0.135f, 0.2225f, 0.1575f, 0.95f };
    float mat_diffuse[] ={0.54f, 0.89f, 0.63f, 0.95f };
    float mat_specular[] ={0.316228f, 0.316228f, 0.316228f, 0.95f };
    float shine = 12.8f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

void setMaterialBronze(){
float mat_ambient[] ={0.25f, 0.148f, 0.06475f, 1.0f  };
float mat_diffuse[] ={0.4f, 0.2368f, 0.1036f, 1.0f };
float mat_specular[] ={0.774597f, 0.458561f, 0.200621f, 1.0f };
float shine =76.8f ;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

void setMaterialTin(){
float mat_ambient[] ={ 0.105882f, 0.058824f, 0.113725f, 1.0f };
float mat_diffuse[] ={0.427451f, 0.470588f, 0.541176f, 1.0f };
float mat_specular[] ={0.333333f, 0.333333f, 0.521569f, 1.0f };
float shine = 9.84615f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

void keys(unsigned char key, int x, int y)
{

///* Use x, X, y, Y, z, and Z keys to move viewer */
//
//   if(key == 'x') viewer[0]-= 1.0;
//   if(key == 'X') viewer[0]+= 1.0;
//   if(key == 'y') viewer[1]-= 1.0;
//   if(key == 'Y') viewer[1]+= 1.0;
//   if(key == 'z') viewer[2]-= 1.0;
//   if(key == 'Z') viewer[2]+= 1.0;

switch( key )
    {
    case 27:
    case 'q':
        exit(0);
        break;
    case 'a':
        camera->LookUp(2.0f);
        break;
    case 'z':
        camera->LookUp(-2.0f);
        break;
    case 's':
        camera->MoveUp(2.0f);
        break;
    case 'x':
        camera->MoveUp(-2.0f);
        break;
    case 'd':
        camera->Move(2.0f);
        break;
    case 'c':
        camera->Move(-2.0f);
        break;
    case '.':
        camera->Rotate(0.0f,0.1f,0.0f );
        break;
    case ',':
        camera->Rotate(0.0f,-0.1f,0.0f );
        break;
    case 'r':
        camera = new Camera( 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
        break;
    default:
        break;
    }

//   if(key == 'b' || key == 'B') spin = !spin;

   if(key == '-') speed-= 0.05;
   if(key == '+') speed+= 0.05;

/*
   if(key == '1') LightPosition[0]-= 20.0f;
   if(key == '2') LightPosition[0]+= 20.0f;
   if(key == '3') LightPosition[1]-= 20.0f;
   if(key == '4') LightPosition[1]+= 20.0f;
   if(key == '5') LightPosition[2]-= 20.0f;
   if(key == '6') LightPosition[2]+= 20.0f;
*/

   if(key == 'q' || key == 'Q') exit(0);

   display();
}

void specialkeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        camera->Rotate(0.0f,0.02f,0.0f );
        break;
    case GLUT_KEY_LEFT:
        camera->Rotate(0.0f,-0.02f,0.0f );
        break;
    case GLUT_KEY_UP:
        camera->Move( 2.0f );
        break;
    case GLUT_KEY_DOWN:
        camera->Move( -2.0f );
        break;
    case GLUT_KEY_PAGE_UP:
        camera->LookUp(2.0f);
        break;
    case GLUT_KEY_PAGE_DOWN:
        camera->LookUp(-2.0f);
        break;
    case GLUT_KEY_HOME:
        camera->MoveUp(2.0f);
        break;
    case GLUT_KEY_END:
        camera->MoveUp(-2.0f);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}


void bolabola(){
    float xx=-5, yy=0, zz=-5;
    for(int x=0; x<9;x++){
        if(x==0){
            setmaterialPerl();
            glPushMatrix();
            glTranslatef(xx,yy,zz);
            glutSolidSphere(radius,25,25);
            glPopMatrix();
        }
        else if(x%3==0){
            xx=-5;
            zz+=5;
            setMaterialJade();
            glPushMatrix();
            glTranslatef(xx,yy,zz);
            glutSolidSphere(radius,25,25);
            glPopMatrix();
        }
        if(x%2==0){
            setmaterialPerl();
            glPushMatrix();
            glTranslatef(xx,yy,zz);
            glutSolidSphere(radius,25,25);
            glPopMatrix();
        }
        else{
            setMaterialJade();
            glPushMatrix();
            glTranslatef(xx,yy,zz);
            glutSolidSphere(radius,25,25);
            glPopMatrix();
        }
        xx+=5;
    }
}

void tusuk(){
    GLUquadric* qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluCylinder(qobj, 0.2, 0.1, 25.0, 20, 20);
}

void garis2bawah(){

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->Update();

    setLighting();

    // Set material properties
    setMaterialijo();
    // built-in (glut library) function , draw you a sphere.
    bolabola();

    setMaterialBronze();
    glPushMatrix();
    glTranslatef(0, 0, -5);
    tusuk();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5, 0, -5);
    tusuk();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5, 0, -5);
    tusuk();
    glPopMatrix();

    // Flush buffers to screen

    glFlush();
    glutSwapBuffers();
    // sawp buffers called because we are using double buffering
   // glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    if (w <= h)
//	glOrtho(-400.0, 400.0, -400.0*(GLfloat)h/(GLfloat)w,
//	    400.0*(GLfloat)h/(GLfloat)w, -400.0, 400.0);
//    else
//	glOrtho(-400.0*(GLfloat)w/(GLfloat)h,
//	    400.0*(GLfloat)w/(GLfloat)h, -400.0, 400.0, -400.0, 400.0);

    gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 5000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(500,500);
    glutCreateWindow("Tugas Shading");
    camera = new Camera( 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
    glClearColor (0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
	glutSpecialFunc(specialkeys);
    glutIdleFunc(idleFunc);
    glutMainLoop();

    delete camera;
    return 0;
}
