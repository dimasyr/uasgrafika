#include <iostream>
#include <GL/glut.h>
#include "Camera.h"
#include <math.h>      // For math routines (such as sqrt & trig).
#define PI 3.14159265358979323846
using namespace std;
//skala scale tiap kotak =2.5
//skala translate tiap kotak x=5, y dan z =1

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

void idleFunc(void){

     zRotated += 0.02;

    display();
}
void setLighting(){
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
void keys(unsigned char key, int x, int y){

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
        camera->LookUp(0.6f);
        break;
    case 'z':
        camera->LookUp(-0.6f);
        break;
    case 'f':
        camera->LookUp(0.1f);
        break;
    case 'v':
        camera->LookUp(-0.1f);
        break;
    case 's':
        camera->MoveUp(1.0f);
        break;
    case 'x':
        camera->MoveUp(-1.0f);
        break;
    case 'g':
        camera->MoveUp(0.1f);
        break;
    case 'b':
        camera->MoveUp(-0.1f);
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
void specialkeys(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        camera->Rotate(0.0f,0.06f,0.0f );
        break;
    case GLUT_KEY_LEFT:
        camera->Rotate(0.0f,-0.06f,0.0f );
        break;
    case GLUT_KEY_UP:
        camera->Move( 0.6f );
        break;
    case GLUT_KEY_DOWN:
        camera->Move( -0.6f );
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
void garis2frontback(){
    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(100.0,0,0);
    glEnd();
    for(int i=0;i<20;i++){
        glTranslatef(0,0,-5);
        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(100.0,0,0);
        glEnd();
    }
    glPopMatrix();
}
void garis2leftright(){
    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,-100.0);
    glEnd();
    for(int i=0;i<20;i++){
        glTranslatef(5,0,0);
        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,-100.0);
        glEnd();
    }
    glPopMatrix();
}
void atapRumahKeranda(float r, float g, float b){
    //atap kiri
    glColor3f(r,g,b);
    glPushMatrix();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.02,3,0);
        glVertex3f(5,5,-5);
        glVertex3f(0.02,3,-10);
    glEnd();
    glPopMatrix();
    //atap kanan

    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(9.98,3,0);
        glVertex3f(5,5,-5);
        glVertex3f(9.98,3,-9.98);
    glEnd();
    glPopMatrix();
    //atap belakang
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.02,3,-9.98);
        glVertex3f(5,5,-5);
        glVertex3f(9.98,3,-9.98);
    glEnd();
    glPopMatrix();
    //atap depan
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.02,3,0);
        glVertex3f(5,5,-5);
        glVertex3f(9.98,3,0);
    glEnd();
    glPopMatrix();
}
void atapRumahKeranda2(float r, float g, float b){
    //atap kiri
    glColor3f(r,g,b);
    glPushMatrix();

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.02,3,0);
        glVertex3f(5,5.02,-5);
        glVertex3f(-0.02,3,-10.02);
    glEnd();
    glPopMatrix();
    //atap kanan
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(10.02,3,0);
        glVertex3f(5,5.02,-5);
        glVertex3f(10.02,3,-10.02);
    glEnd();
    glPopMatrix();
    //atap belakang
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.02,3,-10.02);
        glVertex3f(5,5.02,-5);
        glVertex3f(10.02,3,-10.02);
    glEnd();
    glPopMatrix();
    //atap depan
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.02,3,0);
        glVertex3f(5,5.02,-5);
        glVertex3f(10.02,3,0);
    glEnd();
    glPopMatrix();
}
void tebalAtapKeranda(){
    //depan
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.02,3,0);
    glVertex3f(-0.02,3.05,0);
    glVertex3f(10.02,3.05,0);
    glVertex3f(10.02,3,0);
    glEnd();
    glPopMatrix();
    //belakang
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.02,3,-10.02);
    glVertex3f(-0.02,3.05,-10.02);
    glVertex3f(10.02,3.05,-10.02);
    glVertex3f(10.02,3,-10.02);
    glEnd();
    glPopMatrix();
    //kiri
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.02,3,-10.02);
    glVertex3f(-0.02,3,0);
    glVertex3f(-0.02,3.05,0);
    glVertex3f(-0.02,3.05,-10.02);
    glEnd();
    glPopMatrix();
    //kanan
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(10.02,3,-10.02);
    glVertex3f(10.02,3,0);
    glVertex3f(10.02,3.05,0);
    glVertex3f(10.02,3.05,-10.02);
    glEnd();
    glPopMatrix();
}
void atapSegitiga(float flx, float fly, float flz,
                  float frx, float fry, float frz,
                  float brx, float bry, float brz,
                  float blx, float bly, float blz,
                  float midx, float midy, float midz){
    //atap kiri
    glColor3f(0.3,0.5,0.6);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glVertex3f(flx,fly,flz);
        glVertex3f(midx,midy,midz);
        glVertex3f(blx,bly,blz);
    glEnd();
    glPopMatrix();
    //atap kanan
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(frx,fry,frz);
        glVertex3f(midx,midy,midz);
        glVertex3f(brx,bry,brz);
    glEnd();
    glPopMatrix();
    //atap belakang
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(blx,bly,blz);
        glVertex3f(midx,midy,midz);
        glVertex3f(brx,bry,brz);
    glEnd();
    glPopMatrix();
    //atap depan
    glPushMatrix();
    //glColor3f(1,0.5,0.2);
    glBegin(GL_TRIANGLES);
        glVertex3f(flx,fly,flz);
        glVertex3f(midx,midy,midz);
        glVertex3f(frx,fry,frz);
    glEnd();
    glPopMatrix();
}
void tugu(){
    //body
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(0,1,0);
    glScalef(1,2,1);
    glutSolidCube(1);
    glPopMatrix();
    //body atas
    glPushMatrix();
    glColor3f(1,0.2,0.5);
    glTranslatef(0,2.05,0);
    glScalef(1.2,0.1,1.2);
    glutSolidCube(1);
    glPopMatrix();
    //atap
    glPushMatrix();
    glTranslatef(-0.5,0,0.5);
    atapSegitiga(-0.1,2.1,0.1,1.1,2.1,0.1,1.1,2.1,-1.1,-0.1,2.1,-1.1,0.5,2.5,-0.5);
    glPopMatrix();
}
void tuguPojok2(){
    //depan kiri
    glPushMatrix();
    glTranslatef(0,0,0);
    tugu();
    glPopMatrix();
    //baris kiri
    float z=-4.5;
    for(int ctr=0;ctr<19;ctr++){
        glPushMatrix();
        glTranslatef(0,0,z);
        tugu();
        glPopMatrix();
        z-=5;
    }
    //belakang kiri
    glPushMatrix();
    glTranslatef(0,0,-99);
    tugu();
    glPopMatrix();

    //depan kanan
    glPushMatrix();
    glTranslatef(99,0,0);
    tugu();
    glPopMatrix();
    //baris kanan
    z=-4.5;
    for(int ctr=0;ctr<19;ctr++){
        glPushMatrix();
        glTranslatef(99,0,z);
        tugu();
        glPopMatrix();
        z-=5;
    }
    //belakang kanan
    glPushMatrix();
    glTranslatef(99,0,-99);
    tugu();
    glPopMatrix();
    // baris belakang
    float x=4.5;
    for(int ctr=0;ctr<19;ctr++){
        glPushMatrix();
        glTranslatef(x,0,-99);
        tugu();
        glPopMatrix();
        x+=5;
    }
    //baris depan kiri
    x=4.5;
    for(int ctr=0;ctr<8;ctr++){
        glPushMatrix();
        glTranslatef(x,0,0);
        tugu();
        glPopMatrix();
        x+=5;
    }
    //naris depan kanan
    x=94.5;
    for(int ctr=0;ctr<8;ctr++){
        glPushMatrix();
        glTranslatef(x,0,0);
        tugu();
        glPopMatrix();
        x-=5;
    }
}
void pagar(){
    //kiri
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(0.5,0.625,-50);
    glScalef(1,2.5,200);
    glutSolidCube(0.5);
    glPopMatrix();
    //kanan
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(99.5,0.625,-50);
    glScalef(1,2.5,200);
    glutSolidCube(0.5);
    glPopMatrix();
    //belakang
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(50,0.625,-99.5);
    glRotatef(90,0,1,0);
    glScalef(1,2.5,200);
    glutSolidCube(0.5);
    glPopMatrix();
    //depan kiri
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(20,0.625,-0.5);
    glRotatef(90,0,1,0);
    glScalef(1,2.5,80);
    glutSolidCube(0.5);
    glPopMatrix();
    //depan kanan
    //depan kiri
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(80,0.625,-0.5);
    glRotatef(90,0,1,0);
    glScalef(1,2.5,80);
    glutSolidCube(0.5);
    glPopMatrix();
}
void posisiLampu(float x, float y, float z){
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(x,y,z);
    glutSolidSphere(0.2,100,100);
    glPopMatrix();
}
void rumahKeranda(){
    //tembok kiri
    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(0,1,-5);
    glScalef(0.02,2,5);
    glutSolidCube(2);
    glPopMatrix();
    //tembok kanan
    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(10,1,-5);
    glScalef(0.02,2,5);
    glutSolidCube(2);
    glPopMatrix();
    //tembok belakang
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(5,1,-10);
    glScalef(5,2,0.02);
    glutSolidCube(2);
    glPopMatrix();
    //atap
    atapRumahKeranda(1,0.5,0.2);

    glPushMatrix();
    glTranslatef(0,0.05,0);
    atapRumahKeranda2(0.5,0.5,0.2);
    glPopMatrix();
    tebalAtapKeranda();
}
void drawHalfSphere(int scaley, int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][3];

   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }

   glBegin(GL_QUADS);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();
 }
void lingkaran(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat jari_jari, GLfloat detail,
                       GLfloat keutuhan) {
    keutuhan = (keutuhan > 1) ? 1 : keutuhan;
    glBegin(GL_POLYGON);
    int jumlahLooping = 0;
    for (GLfloat sudut = -detail; sudut <= 360 * keutuhan; sudut += detail) {
        GLfloat x = jari_jari * cos((sudut + detail) * M_PI / 180);
        GLfloat z = jari_jari * sin((sudut + detail) * M_PI / 180);
        //cout<<x<<" "<<posY<<" "<<z<<endl;
        glColor3ub(128, 64, 0);
        //glNormal3f(posX + x, posY, posZ + z);
        glVertex3f(posX + x, posY, posZ + z);
        jumlahLooping++;
    }
    glEnd();
}
void pipa(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat jari_jari_bawah, GLfloat jari_jari_atas, GLfloat tinggi,
             GLfloat detail, GLfloat keutuhan) {
    keutuhan = (keutuhan > 1) ? 1 : keutuhan;
    GLfloat Xsebelum = jari_jari_bawah;
    GLfloat Zsebelum = 0;
    int jumlahLooping = 0;
    for (GLfloat sudut = 0; sudut <= 360 * keutuhan; sudut += detail) {
        GLfloat XsebelumAtas = jari_jari_atas * cos((sudut) * M_PI / 180);
        GLfloat ZsebelumAtas = jari_jari_atas * sin((sudut) * M_PI / 180);
        GLfloat Xsesudah = jari_jari_bawah * cos((sudut + detail) * M_PI / 180);
        GLfloat Zsesudah = jari_jari_bawah * sin((sudut + detail) * M_PI / 180);
        GLfloat XsesudahAtas = jari_jari_atas * cos((sudut + detail) * M_PI / 180);
        GLfloat ZsesudahAtas = jari_jari_atas * sin((sudut + detail) * M_PI / 180);
        glBegin(GL_POLYGON);
        glColor3ub(128, 64, 0);
        //glNormal3f(Xsebelum + posX, posY, Zsebelum + posZ);
        glVertex3f(Xsebelum + posX, posY, Zsebelum + posZ);
        //glNormal3f(Xsesudah + posX, posY, Zsesudah + posZ);
        glVertex3f(Xsesudah + posX, posY, Zsesudah + posZ);
        //glNormal3f(XsesudahAtas + posX, posY + tinggi, ZsesudahAtas + posZ);
        glVertex3f(XsesudahAtas + posX, posY + tinggi, ZsesudahAtas + posZ);
        //glNormal3f(XsebelumAtas + posX, posY + tinggi, ZsebelumAtas + posZ);
        glVertex3f(XsebelumAtas + posX, posY + tinggi, ZsebelumAtas + posZ);
        glEnd();
        Xsebelum = Xsesudah;
        Zsebelum = Zsesudah;
        jumlahLooping++;
    }
}
void tabung(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat jari_jari_bawah, GLfloat jari_jari_atas,
               GLfloat tinggi, GLfloat detail, GLfloat keutuhan, bool tutup_atas, bool tutup_bawah) {
    if (tutup_atas)
        lingkaran(posX, posY + tinggi, posZ, jari_jari_atas, detail, keutuhan);

    pipa(posX, posY, posZ, jari_jari_bawah, jari_jari_atas, tinggi, detail, keutuhan);

    if (tutup_bawah)
        lingkaran(posX, posY, posZ, jari_jari_bawah, detail, keutuhan);

    if (keutuhan < 1) {
        glBegin(GL_POLYGON);
        glColor3ub(125, 167, 200);
        //glNormal3f(posX + jari_jari_bawah, posY, posZ);
        glVertex3f(posX + jari_jari_bawah, posY, posZ);
        glColor3ub(50, 69, 100);
        //glNormal3f(posX + (jari_jari_bawah * cos(360 * keutuhan * M_PI / 180)), posY,posZ + (jari_jari_bawah * sin(360 * keutuhan * M_PI / 180)));
        glVertex3f(posX + (jari_jari_bawah * cos(360 * keutuhan * M_PI / 180)), posY,
                   posZ + (jari_jari_bawah * sin(360 * keutuhan * M_PI / 180)));
        glColor3ub(125, 167, 200);
        //glNormal3f(posX + (jari_jari_atas * cos(360 * keutuhan * M_PI / 180)), posY + tinggi, posZ + (jari_jari_atas * sin(360 * keutuhan * M_PI / 180)));
        glVertex3f(posX + (jari_jari_atas * cos(360 * keutuhan * M_PI / 180)), posY + tinggi,
                   posZ + (jari_jari_atas * sin(360 * keutuhan * M_PI / 180)));
        glColor3ub(50, 69, 100);
        //glNormal3f(posX + jari_jari_atas, posY + tinggi, posZ);
        glVertex3f(posX + jari_jari_atas, posY + tinggi, posZ);
        glEnd();
    }
}
 void lampu(){
    glPushMatrix();
    glColor3d(1,0,0);
    glTranslated(3.0,2.3,-6);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 0.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    tabung(3.0, 0.0, -6, 0.07, 0.07, 2.0, 6, 1, true, true);
    glRotated(90, -1.0, 0.0, 0.0);

    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(3.0,2.54,-6);
    glutSolidSphere(0.5,25,25);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,0);
    tabung(3.0, 0.0, -6, 0.3, 0.3, 0.2, 6, 1, true, true);
    glRotated(90, -1.0, 0.0, 0.0);
    glPopMatrix();
 }
void jalan(){
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(7.5, 0.0, -49.75);
    glScalef(5.0, -0.2, 33.15);
	glutSolidCube(3);
    glPopMatrix();
}
void tabungtebal(float posisiX, float posisiY, float posisiZ, float tinggi, float lebarBawah, float lebarAtas){

    float oldX, oldY, oldZ, oldX1, oldY1, oldZ1, X, Y, Z, X1, Y1, Z1;
    oldX=lebarBawah*cos(0* PI / 180.0);
    oldZ=lebarBawah*sin(0* PI / 180.0);
    oldX1=lebarAtas*cos(0* PI / 180.0);
    oldZ1=lebarAtas*sin(0* PI / 180.0);

    for(int i=0; i<=360; i++){
        X=lebarBawah*cos(i* PI / 180.0);
        Z=lebarBawah*sin(i* PI / 180.0);
        X1=lebarAtas*cos(i* PI / 180.0);
        Z1=lebarAtas*sin(i* PI / 180.0);
        glBegin(GL_POLYGON);
        glNormal3f(oldX+posisiX, posisiY, oldZ+posisiZ);
        glVertex3f(oldX+posisiX, posisiY, oldZ+posisiZ);
        glNormal3f(oldX1+posisiX, posisiY+tinggi, oldZ1+posisiZ);
        glVertex3f(oldX1+posisiX, posisiY+tinggi, oldZ1+posisiZ);
        glNormal3f(X1+posisiX, posisiY+tinggi, Z1+posisiZ);
        glVertex3f(X1+posisiX, posisiY+tinggi, Z1+posisiZ);
        glNormal3f(X+posisiX, posisiY, Z+posisiZ);
        glVertex3f(X+posisiX, posisiY, Z+posisiZ);
        glEnd();
        oldX=X;
        oldZ=Z;
        oldX1=X1;
        oldZ1=Z1;
    }
}
void sumur (){
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    tabungtebal(0.0, 0.0, -5.0, 0.9, 1, 1);
    glColor3f(0.4, 0.8, 0.8);
    tabungtebal(0.0, 1, -5.0, 0, 0.9, 1.5);
    tabungtebal(0.0, 0.0, -5.0, 1, 1.5, 1.5);
    glPopMatrix();
}
float verticessemak[][3] = {
    {0, 0, 0},
    {-1.022434, 0.248791, -0.095557},
    {-0.476122, -0.652270, 0.788318},
    {0.473428, -0.705925, 0.624071},
    {-0.781381, -0.671891, -0.404078},
    {0.282202, -0.994406, -0.247732},
    {0.029852, -0.490258, -0.925941},
    {0.936297, -0.492541, -0.269424},
    {0.405108, 0.258762, -0.948066},
    {0.539645, 0.868872, -0.188019},
    {1.065255, 0.142590, -0.094934},
    {-0.096856, 0.792813, -0.702258},
    {0.708869, 0.119915, 0.821170},
    {-0.563573, 0.875689, 0.008611},
    {0.247114, 0.884328, 0.569624},
    {-0.586108, 0.305673, -0.833709},
    {-0.535167, 0.434908, 0.841142}
};
int facessemak[][3] = {
    {1, 4, 2},
    {1, 15, 4},
    {5, 2, 4},
    {2, 5, 3},
    {4, 6, 5},
    {6, 15, 8},
    {7, 6, 8},
    {12, 7, 10},
    {15, 11, 8},
    {8, 9, 10},
    {9, 8, 11},
    {12, 10, 9},
    {14, 11, 13},
    {15, 1, 13},
    {14, 13, 16},
    {14, 16, 12},
    {13, 1, 16},
    {16, 2, 12},
    {3, 12, 2},
    {16, 1, 2},
    {3, 5, 7},
    {4, 15, 6},
    {12, 3, 7},
    {5, 6, 7},
    {7, 8, 10},
    {14, 12, 9},
    {14, 9, 11},
    {13, 11, 15}
};
void semak (){
    glPushMatrix();
    glColor3f(0.3, 1.0, 0.35);
    glTranslatef(0.0, 0.0, 1.0);

    for(int i =0; i<29; i++)
    {
        glBegin(GL_POLYGON);
        for (int j=0; j<3; j++)
        {
            glVertex3fv(verticessemak[facessemak[i][j]]);
        }
        glEnd();
    }
    glPopMatrix();
}
void cabang (){
    glBegin(GL_POLYGON);
    glVertex3f(-0.867347, 4.156862, -0.877226);
    glTexCoord2f(-0.533322, -0.063494);
    glNormal3f(-0.0294, 0.0825, 0.9962);
    glVertex3f(-1.549831, -1.333189, -1.189907);
    glTexCoord2f(-0.663534, -1.947878);
    glNormal3f(-0.7994, -0.0221, 0.6004);
    glVertex3f(0.068850, -1.330682, -1.163511);
    glTexCoord2f(-0.085394, -1.899305);
    glNormal3f(0.7051, 0.0091, 0.7090);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.139305, -1.329350, -2.389079);
    glTexCoord2f(-1.809854, -1.901812);
    glNormal3f(0.8146, 0.0855, -0.5737);
    glVertex3f(-0.825127, 3.416767, -2.306097);
    glTexCoord2f(-1.207530, -0.328829);
    glNormal3f(0.0134, 0.1093, -0.9939);
    glVertex3f(-0.405093, 7.576131, -1.667079);
    glTexCoord2f(-1.366466, 1.409555);
    glNormal3f(0.9643, 0.1263, 0.2328);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.825127, 3.416767, -2.306097);
    glTexCoord2f(-1.207530, -0.328829);
    glNormal3f(0.0134, 0.1093, -0.9939);
    glVertex3f(0.139305, -1.329350, -2.389079);
    glTexCoord2f(-1.809854, -1.901812);
    glNormal3f(0.8146, 0.0855, -0.5737);
    glVertex3f(-1.194680, -1.335544, -2.802517);
    glTexCoord2f(-1.301689, -1.966942);
    glNormal3f(-0.4872, 0.0731, -0.8702);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.825127, 3.416767, -2.306097);
    glTexCoord2f(-1.207530, -0.328829);
    glNormal3f(0.0134, 0.1093, -0.9939);
    glVertex3f(-1.194680, -1.335544, -2.802517);
    glTexCoord2f(-1.301689, -1.966942);
    glNormal3f(-0.4872, 0.0731, -0.8702);
    glVertex3f(-1.273815, 4.966448, -1.905464);
    glTexCoord2f(-1.001325, 0.260186);
    glNormal3f(-0.8903, -0.0124, -0.4552);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.273815, 4.966448, -1.905464);
    glTexCoord2f(-1.001325, 0.260186);
    glNormal3f(-0.8903, -0.0124, -0.4552);
    glVertex3f(-1.549831, -1.333189, -1.189907);
    glTexCoord2f(-0.663534, -1.947878);
    glNormal3f(-0.7994, -0.0221, 0.6004);
    glVertex3f(-1.241564, 10.488920, -1.723966);
    glTexCoord2f(-0.616457, 2.163076);
    glNormal3f(-0.0169, 0.3064, 0.9518);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.405093, 7.576131, -1.667079);
    glTexCoord2f(-1.366466, 1.409555);
    glNormal3f(0.9643, 0.1263, 0.2328);
    glVertex3f(-0.825127, 3.416767, -2.306097);
    glTexCoord2f(-1.207530, -0.328829);
    glNormal3f(0.0134, 0.1093, -0.9939);
    glVertex3f(-0.795685, 9.595210, -2.187923);
    glTexCoord2f(-1.168897, 1.857249);
    glNormal3f(0.8455, 0.2055, -0.4929);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.405093, 7.576131, -1.667079);
    glTexCoord2f(-0.438391, 1.211348);
    glNormal3f(0.9643, 0.1263, 0.2328);
    glVertex3f(-0.867347, 4.156862, -0.877226);
    glTexCoord2f(-0.533322, -0.063494);
    glNormal3f(-0.0294, 0.0825, 0.9962);
    glVertex3f(0.068850, -1.330682, -1.163511);
    glTexCoord2f(-0.085394, -1.899305);
    glNormal3f(0.7051, 0.0091, 0.7090);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.241564, 10.488920, -1.723966);
    glTexCoord2f(-0.616457, 2.163076);
    glNormal3f(-0.0169, 0.3064, 0.9518);
    glVertex3f(-0.405093, 7.576131, -1.667079);
    glTexCoord2f(-0.438391, 1.211348);
    glNormal3f(0.9643, 0.1263, 0.2328);
    glVertex3f(-0.795685, 9.595210, -2.187923);
    glTexCoord2f(-0.639500, 2.276476);
    glNormal3f(0.8455, 0.2055, -0.4929);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.273815, 4.966448, -1.905464);
    glTexCoord2f(-1.001325, 0.260186);
    glNormal3f(-0.8903, -0.0124, -0.4552);
    glVertex3f(-1.241564, 10.488920, -1.723966);
    glTexCoord2f(-0.616457, 2.163076);
    glNormal3f(-0.0169, 0.3064, 0.9518);
    glVertex3f(-1.497546, 12.075701, -2.270085);
    glTexCoord2f(-0.873673, 2.614623);
    glNormal3f(-0.1498, 0.9814, -0.1202);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.165520, 4.155225, -1.444837);
    glTexCoord2f(1.206063, 1.067046);
    glNormal3f(0.4497, -0.0319, 0.8926);
    glVertex3f(-0.382338, 2.649861, -1.163238);
    glTexCoord2f(0.195214, 1.139014);
    glNormal3f(0.2910, -0.5509, 0.7821);
    glVertex3f(2.107894, 3.679790, -1.906483);
    glTexCoord2f(1.088579, 0.903820);
    glNormal3f(0.6841, -0.7204, -0.1139);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.165520, 4.155225, -1.444837);
    glTexCoord2f(1.206063, 1.067046);
    glNormal3f(0.4497, -0.0319, 0.8926);
    glVertex3f(2.813925, 4.959329, -1.961447);
    glTexCoord2f(1.591357, 0.990463);
    glNormal3f(0.7366, 0.6666, -0.1147);
    glVertex3f(-0.735174, 3.805076, -1.511302);
    glTexCoord2f(0.302792, 1.571407);
    glNormal3f(-0.4280, 0.8867, 0.1750);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.107894, 3.679790, -1.906483);
    glTexCoord2f(1.088579, 0.903820);
    glNormal3f(0.6841, -0.7204, -0.1139);
    glVertex3f(-0.372852, 2.667495, -2.123113);
    glTexCoord2f(0.222313, 0.704706);
    glNormal3f(0.1201, -0.5833, -0.8033);
    glVertex3f(1.648500, 3.852098, -2.328539);
    glTexCoord2f(0.994547, 0.703304);
    glNormal3f(0.1120, -0.0696, -0.9913);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.648500, 3.852098, -2.328539);
    glTexCoord2f(0.994547, 0.703304);
    glNormal3f(0.1120, -0.0696, -0.9913);
    glVertex3f(-0.372852, 2.667495, -2.123113);
    glTexCoord2f(0.222313, 0.704706);
    glNormal3f(0.1201, -0.5833, -0.8033);
    glVertex3f(-0.735174, 3.805076, -1.511302);
    glTexCoord2f(0.297768, 0.330467);
    glNormal3f(-0.4280, 0.8867, 0.1750);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.735174, 3.805076, -1.511302);
    glTexCoord2f(0.297768, 0.330467);
    glNormal3f(-0.4280, 0.8867, 0.1750);
    glVertex3f(2.813925, 4.959329, -1.961447);
    glTexCoord2f(1.591357, 0.990463);
    glNormal3f(0.7366, 0.6666, -0.1147);
    glVertex3f(1.648500, 3.852098, -2.328539);
    glTexCoord2f(0.994547, 0.703304);
    glNormal3f(0.1120, -0.0696, -0.9913);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.813925, 4.959329, -1.961447);
    glTexCoord2f(1.591357, 0.990463);
    glNormal3f(0.7366, 0.6666, -0.1147);
    glVertex3f(2.107894, 3.679790, -1.906483);
    glTexCoord2f(1.088579, 0.903820);
    glNormal3f(0.6841, -0.7204, -0.1139);
    glVertex3f(1.648500, 3.852098, -2.328539);
    glTexCoord2f(0.994547, 0.703304);
    glNormal3f(0.1120, -0.0696, -0.9913);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.812376, 6.360534, -3.691374);
    glTexCoord2f(2.026264, -1.136874);
    glNormal3f(0.1641, -0.3381, -0.9267);
    glVertex3f(-0.505065, 5.389382, -1.817205);
    glTexCoord2f(1.620303, -1.859209);
    glNormal3f(0.8845, 0.4416, -0.1506);
    glVertex3f(-0.899091, 4.796803, -1.949262);
    glTexCoord2f(1.921075, -1.948997);
    glNormal3f(-0.0275, -0.7895, -0.6132);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.230624, 6.383121, -3.138590);
    glTexCoord2f(2.252466, -1.219074);
    glNormal3f(-0.9615, -0.2199, 0.1649);
    glVertex3f(-1.314994, 5.324448, -1.388715);
    glTexCoord2f(2.288047, -1.973339);
    glNormal3f(-0.7947, 0.1306, 0.5928);
    glVertex3f(-2.358844, 7.328835, -3.891964);
    glTexCoord2f(2.249823, -0.754844);
    glNormal3f(-0.3836, 0.7522, -0.5357);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.812376, 6.360534, -3.691374);
    glTexCoord2f(2.026264, -1.136874);
    glNormal3f(0.1641, -0.3381, -0.9267);
    glVertex3f(-2.358844, 7.328835, -3.891964);
    glTexCoord2f(2.057909, -0.728233);
    glNormal3f(-0.3836, 0.7522, -0.5357);
    glVertex3f(-0.505065, 5.389382, -1.817205);
    glTexCoord2f(1.620303, -1.859209);
    glNormal3f(0.8845, 0.4416, -0.1506);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.358844, 7.328835, -3.891964);
    glTexCoord2f(2.057909, -0.728233);
    glNormal3f(-0.3836, 0.7522, -0.5357);
    glVertex3f(-1.314994, 5.324448, -1.388715);
    glTexCoord2f(1.449443, -1.789781);
    glNormal3f(-0.7947, 0.1306, 0.5928);
    glVertex3f(-0.505065, 5.389382, -1.817205);
    glTexCoord2f(1.620303, -1.859209);
    glNormal3f(0.8845, 0.4416, -0.1506);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.211318, 5.061069, 0.583011);
    glTexCoord2f(0.832274, -0.965809);
    glNormal3f(-0.2943, -0.6480, 0.7024);
    glVertex3f(-2.445951, 5.771827, 0.355042);
    glTexCoord2f(0.616434, -0.879462);
    glNormal3f(-0.8162, 0.3992, -0.4177);
    glVertex3f(-1.988993, 4.358886, -0.335544);
    glTexCoord2f(0.769342, -1.361228);
    glNormal3f(-0.7027, -0.6960, 0.1477);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.465203, 5.108954, -0.333683);
    glTexCoord2f(0.362867, -1.240861);
    glNormal3f(0.6837, 0.7295, -0.0189);
    glVertex3f(-2.445951, 5.771827, 0.355042);
    glTexCoord2f(0.616434, -0.879462);
    glNormal3f(-0.8162, 0.3992, -0.4177);
    glVertex3f(-2.319730, 7.460398, 2.323781);
    glTexCoord2f(0.704244, 0.017786);
    glNormal3f(-0.0751, 0.7102, 0.7000);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.812376, 6.360534, -3.691374);
    glTexCoord2f(2.026264, -1.136874);
    glNormal3f(0.1641, -0.3381, -0.9267);
    glVertex3f(-2.230624, 6.383121, -3.138590);
    glTexCoord2f(2.252466, -1.219074);
    glNormal3f(-0.9615, -0.2199, 0.1649);
    glVertex3f(-2.358844, 7.328835, -3.891964);
    glTexCoord2f(2.057909, -0.728233);
    glNormal3f(-0.3836, 0.7522, -0.5357);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.444197, 3.615060, -1.263279);
    glTexCoord2f(1.063951, -1.972365);
    glNormal3f(0.4187, -0.5753, 0.7027);
    glVertex3f(-2.211318, 5.061069, 0.583011);
    glTexCoord2f(0.832274, -0.965809);
    glNormal3f(-0.2943, -0.6480, 0.7024);
    glVertex3f(-1.988993, 4.358886, -0.335544);
    glTexCoord2f(0.769342, -1.361228);
    glNormal3f(-0.7027, -0.6960, 0.1477);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.988993, 4.358886, -0.335544);
    glTexCoord2f(0.769342, -1.361228);
    glNormal3f(-0.7027, -0.6960, 0.1477);
    glVertex3f(-1.260430, 3.859101, -1.904382);
    glTexCoord2f(0.547809, -1.930855);
    glNormal3f(-0.6914, -0.1329, -0.7102);
    glVertex3f(-0.444197, 3.615060, -1.263279);
    glTexCoord2f(1.063951, -1.972365);
    glNormal3f(0.4187, -0.5753, 0.7027);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.198746, 9.063770, -2.746028);
    glTexCoord2f(1.579810, 2.874998);
    glNormal3f(0.3366, 0.7303, -0.5944);
    glVertex3f(-0.587266, 7.963510, -1.609305);
    glTexCoord2f(1.148377, 2.466696);
    glNormal3f(0.6799, 0.3969, 0.6166);
    glVertex3f(-0.617416, 7.676767, -1.962022);
    glTexCoord2f(1.287044, 2.350152);
    glNormal3f(0.4672, -0.5377, -0.7018);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.437030, 6.185566, -1.487890);
    glTexCoord2f(0.237108, 1.914098);
    glNormal3f(0.6758, -0.7308, 0.0958);
    glVertex3f(-0.611861, 6.696321, -1.724902);
    glTexCoord2f(0.187827, 1.708268);
    glNormal3f(0.2697, 0.7772, -0.5685);
    glVertex3f(0.618646, 7.318822, -0.290189);
    glTexCoord2f(0.959415, 1.767317);
    glNormal3f(0.6502, 0.4346, 0.6232);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.216627, 5.211133, -2.559260);
    glTexCoord2f(2.508584, 0.630887);
    glNormal3f(0.3372, 0.8551, -0.3939);
    glVertex3f(0.590186, 3.866176, -1.602036);
    glTexCoord2f(1.912028, 0.410644);
    glNormal3f(-0.0333, 0.5898, 0.8069);
    glVertex3f(0.836874, 3.589821, -1.911068);
    glTexCoord2f(2.068260, 0.295536);
    glNormal3f(0.9320, -0.2998, -0.2038);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.216627, 5.211133, -2.559260);
    glTexCoord2f(2.508584, 0.630887);
    glNormal3f(0.3372, 0.8551, -0.3939);
    glVertex3f(0.461928, 3.699703, -2.101837);
    glTexCoord2f(2.244734, 0.238035);
    glNormal3f(-0.5514, 0.0230, -0.8339);
    glVertex3f(0.590186, 3.866176, -1.602036);
    glTexCoord2f(2.426336, 0.211321);
    glNormal3f(-0.0333, 0.5898, 0.8069);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.216627, 5.211133, -2.559260);
    glTexCoord2f(2.508584, 0.630887);
    glNormal3f(0.3372, 0.8551, -0.3939);
    glVertex3f(0.836874, 3.589821, -1.911068);
    glTexCoord2f(2.068260, 0.295536);
    glNormal3f(0.9320, -0.2998, -0.2038);
    glVertex3f(0.461928, 3.699703, -2.101837);
    glTexCoord2f(2.244734, 0.238035);
    glNormal3f(-0.5514, 0.0230, -0.8339);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.399175, 4.666963, 1.380207);
    glTexCoord2f(0.605516, 2.811071);
    glNormal3f(0.3221, -0.1228, 0.9387);
    glVertex3f(-1.669177, 4.984135, -0.135957);
    glTexCoord2f(0.687101, 2.314106);
    glNormal3f(0.8776, 0.4760, -0.0567);
    glVertex3f(-2.074593, 4.976092, -0.026591);
    glTexCoord2f(0.754215, 2.398861);
    glNormal3f(-0.6966, 0.5537, 0.4561);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.399175, 4.666963, 1.380207);
    glTexCoord2f(0.605516, 2.811071);
    glNormal3f(0.3221, -0.1228, 0.9387);
    glVertex3f(-1.958344, 4.616738, -0.073936);
    glTexCoord2f(0.824103, 2.544950);
    glNormal3f(-0.1932, -0.9752, 0.1080);
    glVertex3f(-1.669177, 4.984135, -0.135957);
    glTexCoord2f(0.874108, 2.737725);
    glNormal3f(0.8776, 0.4760, -0.0567);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.399175, 4.666963, 1.380207);
    glTexCoord2f(0.605516, 2.811071);
    glNormal3f(0.3221, -0.1228, 0.9387);
    glVertex3f(-2.074593, 4.976092, -0.026591);
    glTexCoord2f(0.754215, 2.398861);
    glNormal3f(-0.6966, 0.5537, 0.4561);
    glVertex3f(-1.958344, 4.616738, -0.073936);
    glTexCoord2f(0.824103, 2.544950);
    glNormal3f(-0.1932, -0.9752, 0.1080);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.067270, 5.702630, -2.549646);
    glTexCoord2f(2.227261, -0.143612);
    glNormal3f(0.7696, -0.4544, -0.4486);
    glVertex3f(-1.451593, 5.726283, -2.570899);
    glTexCoord2f(2.271672, -0.275721);
    glNormal3f(-0.9000, -0.0703, -0.4303);
    glVertex3f(-1.045056, 6.768772, -3.591383);
    glTexCoord2f(2.770040, -0.003104);
    glNormal3f(0.1145, 0.6708, -0.7328);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.394543, 8.728384, -0.441430);
    glTexCoord2f(1.960986, 1.463654);
    glNormal3f(-0.3488, 0.5241, 0.7770);
    glVertex3f(-1.096891, 7.808803, -1.658592);
    glTexCoord2f(2.467383, 1.147650);
    glNormal3f(-0.9207, -0.3847, 0.0655);
    glVertex3f(-0.650121, 7.825992, -1.449333);
    glTexCoord2f(2.537439, 1.329308);
    glNormal3f(0.6247, -0.2930, 0.7238);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.394543, 8.728384, -0.441430);
    glTexCoord2f(1.960986, 1.463654);
    glNormal3f(-0.3488, 0.5241, 0.7770);
    glVertex3f(-0.853013, 8.163962, -1.747187);
    glTexCoord2f(2.350960, 1.017403);
    glNormal3f(0.0203, 0.9208, -0.3896);
    glVertex3f(-1.096891, 7.808803, -1.658592);
    glTexCoord2f(2.467383, 1.147650);
    glNormal3f(-0.9207, -0.3847, 0.0655);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.650121, 7.825992, -1.449333);
    glTexCoord2f(2.537439, 1.329308);
    glNormal3f(0.6247, -0.2930, 0.7238);
    glVertex3f(-0.853013, 8.163962, -1.747187);
    glTexCoord2f(2.558421, 1.486096);
    glNormal3f(0.0203, 0.9208, -0.3896);
    glVertex3f(-1.394543, 8.728384, -0.441430);
    glTexCoord2f(2.015130, 1.436738);
    glNormal3f(-0.3488, 0.5241, 0.7770);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.051056, 7.189873, -1.698019);
    glTexCoord2f(2.199726, -0.379434);
    glNormal3f(0.2127, 0.8815, 0.4216);
    glVertex3f(-1.037442, 6.943398, -2.059374);
    glTexCoord2f(2.186924, -0.219751);
    glNormal3f(0.1458, -0.0415, -0.9884);
    glVertex3f(-2.465093, 7.822194, -2.306898);
    glTexCoord2f(1.564606, -0.386213);
    glNormal3f(-0.8034, 0.5151, -0.2986);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.619251, 3.742969, -2.052844);
    glTexCoord2f(1.942797, 1.853112);
    glNormal3f(0.4194, 0.7316, -0.5375);
    glVertex3f(0.613229, 3.435482, -1.710121);
    glTexCoord2f(2.045094, 1.782811);
    glNormal3f(0.6009, -0.2391, 0.7627);
    glVertex3f(1.692837, 2.550531, -2.838055);
    glTexCoord2f(2.386315, 2.371786);
    glNormal3f(0.6623, -0.5265, -0.5330);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.350393, 3.255892, -1.933458);
    glTexCoord2f(2.176824, 1.729762);
    glNormal3f(-0.5580, -0.8054, -0.2000);
    glVertex3f(0.619251, 3.742969, -2.052844);
    glTexCoord2f(2.411538, 1.675306);
    glNormal3f(0.4194, 0.7316, -0.5375);
    glVertex3f(1.692837, 2.550531, -2.838055);
    glTexCoord2f(2.386315, 2.371786);
    glNormal3f(0.6623, -0.5265, -0.5330);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.549831, -1.333189, -1.189907);
    glTexCoord2f(-0.663534, -1.947878);
    glNormal3f(-0.7994, -0.0221, 0.6004);
    glVertex3f(-0.867347, 4.156862, -0.877226);
    glTexCoord2f(-0.533322, -0.063494);
    glNormal3f(-0.0294, 0.0825, 0.9962);
    glVertex3f(-1.241564, 10.488920, -1.723966);
    glTexCoord2f(-0.616457, 2.163076);
    glNormal3f(-0.0169, 0.3064, 0.9518);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.068850, -1.330682, -1.163511);
    glTexCoord2f(-0.085394, -1.899305);
    glNormal3f(0.7051, 0.0091, 0.7090);
    glVertex3f(0.139305, -1.329350, -2.389079);
    glTexCoord2f(0.180385, -1.872847);
    glNormal3f(0.8146, 0.0855, -0.5737);
    glVertex3f(-0.405093, 7.576131, -1.667079);
    glTexCoord2f(-0.438391, 1.211348);
    glNormal3f(0.9643, 0.1263, 0.2328);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.273815, 4.966448, -1.905464);
    glTexCoord2f(-1.001325, 0.260186);
    glNormal3f(-0.8903, -0.0124, -0.4552);
    glVertex3f(-1.194680, -1.335544, -2.802517);
    glTexCoord2f(-1.301689, -1.966942);
    glNormal3f(-0.4872, 0.0731, -0.8702);
    glVertex3f(-1.549831, -1.333189, -1.189907);
    glTexCoord2f(-0.663534, -1.947878);
    glNormal3f(-0.7994, -0.0221, 0.6004);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.273815, 4.966448, -1.905464);
    glTexCoord2f(-1.001325, 0.260186);
    glNormal3f(-0.8903, -0.0124, -0.4552);
    glVertex3f(-1.497546, 12.075701, -2.270085);
    glTexCoord2f(-0.873673, 2.614623);
    glNormal3f(-0.1498, 0.9814, -0.1202);
    glVertex3f(-0.825127, 3.416767, -2.306097);
    glTexCoord2f(-1.207530, -0.328829);
    glNormal3f(0.0134, 0.1093, -0.9939);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.497546, 12.075701, -2.270085);
    glTexCoord2f(-0.873673, 2.614623);
    glNormal3f(-0.1498, 0.9814, -0.1202);
    glVertex3f(-0.795685, 9.595210, -2.187923);
    glTexCoord2f(-1.168897, 1.857249);
    glNormal3f(0.8455, 0.2055, -0.4929);
    glVertex3f(-0.825127, 3.416767, -2.306097);
    glTexCoord2f(-1.207530, -0.328829);
    glNormal3f(0.0134, 0.1093, -0.9939);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.405093, 7.576131, -1.667079);
    glTexCoord2f(-0.438391, 1.211348);
    glNormal3f(0.9643, 0.1263, 0.2328);
    glVertex3f(-1.241564, 10.488920, -1.723966);
    glTexCoord2f(-0.616457, 2.163076);
    glNormal3f(-0.0169, 0.3064, 0.9518);
    glVertex3f(-0.867347, 4.156862, -0.877226);
    glTexCoord2f(-0.533322, -0.063494);
    glNormal3f(-0.0294, 0.0825, 0.9962);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.795685, 9.595210, -2.187923);
    glTexCoord2f(-0.639500, 2.276476);
    glNormal3f(0.8455, 0.2055, -0.4929);
    glVertex3f(-1.497546, 12.075701, -2.270085);
    glTexCoord2f(-0.873673, 2.614623);
    glNormal3f(-0.1498, 0.9814, -0.1202);
    glVertex3f(-1.241564, 10.488920, -1.723966);
    glTexCoord2f(-0.616457, 2.163076);
    glNormal3f(-0.0169, 0.3064, 0.9518);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.735174, 3.805076, -1.511302);
    glTexCoord2f(0.302792, 1.571407);
    glNormal3f(-0.4280, 0.8867, 0.1750);
    glVertex3f(-0.382338, 2.649861, -1.163238);
    glTexCoord2f(0.195214, 1.139014);
    glNormal3f(0.2910, -0.5509, 0.7821);
    glVertex3f(2.165520, 4.155225, -1.444837);
    glTexCoord2f(1.206063, 1.067046);
    glNormal3f(0.4497, -0.0319, 0.8926);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.107894, 3.679790, -1.906483);
    glTexCoord2f(1.088579, 0.903820);
    glNormal3f(0.6841, -0.7204, -0.1139);
    glVertex3f(-0.382338, 2.649861, -1.163238);
    glTexCoord2f(0.195214, 1.139014);
    glNormal3f(0.2910, -0.5509, 0.7821);
    glVertex3f(-0.372852, 2.667495, -2.123113);
    glTexCoord2f(0.222313, 0.704706);
    glNormal3f(0.1201, -0.5833, -0.8033);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.107894, 3.679790, -1.906483);
    glTexCoord2f(1.088579, 0.903820);
    glNormal3f(0.6841, -0.7204, -0.1139);
    glVertex3f(2.813925, 4.959329, -1.961447);
    glTexCoord2f(1.591357, 0.990463);
    glNormal3f(0.7366, 0.6666, -0.1147);
    glVertex3f(2.165520, 4.155225, -1.444837);
    glTexCoord2f(1.206063, 1.067046);
    glNormal3f(0.4497, -0.0319, 0.8926);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.260430, 3.859101, -1.904382);
    glTexCoord2f(0.547809, -1.930855);
    glNormal3f(-0.6914, -0.1329, -0.7102);
    glVertex3f(-2.445951, 5.771827, 0.355042);
    glTexCoord2f(0.616434, -0.879462);
    glNormal3f(-0.8162, 0.3992, -0.4177);
    glVertex3f(-1.465203, 5.108954, -0.333683);
    glTexCoord2f(0.362867, -1.240861);
    glNormal3f(0.6837, 0.7295, -0.0189);
    glVertex3f(-0.256945, 4.253136, -1.606416);
    glTexCoord2f(0.203904, -1.951937);
    glNormal3f(0.6678, 0.7415, 0.0648);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.260430, 3.859101, -1.904382);
    glTexCoord2f(0.547809, -1.930855);
    glNormal3f(-0.6914, -0.1329, -0.7102);
    glVertex3f(-1.988993, 4.358886, -0.335544);
    glTexCoord2f(0.769342, -1.361228);
    glNormal3f(-0.7027, -0.6960, 0.1477);
    glVertex3f(-2.445951, 5.771827, 0.355042);
    glTexCoord2f(0.616434, -0.879462);
    glNormal3f(-0.8162, 0.3992, -0.4177);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.444197, 3.615060, -1.263279);
    glTexCoord2f(1.063951, -1.972365);
    glNormal3f(0.4187, -0.5753, 0.7027);
    glVertex3f(-0.256945, 4.253136, -1.606416);
    glTexCoord2f(1.338947, -1.934119);
    glNormal3f(0.6678, 0.7415, 0.0648);
    glVertex3f(-1.465203, 5.108954, -0.333683);
    glTexCoord2f(1.191695, -1.298243);
    glNormal3f(0.6837, 0.7295, -0.0189);
    glVertex3f(-2.211318, 5.061069, 0.583011);
    glTexCoord2f(0.832274, -0.965809);
    glNormal3f(-0.2943, -0.6480, 0.7024);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.319730, 7.460398, 2.323781);
    glTexCoord2f(0.704244, 0.017786);
    glNormal3f(-0.0751, 0.7102, 0.7000);
    glVertex3f(-2.211318, 5.061069, 0.583011);
    glTexCoord2f(0.832274, -0.965809);
    glNormal3f(-0.2943, -0.6480, 0.7024);
    glVertex3f(-1.465203, 5.108954, -0.333683);
    glTexCoord2f(1.191695, -1.298243);
    glNormal3f(0.6837, 0.7295, -0.0189);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.211318, 5.061069, 0.583011);
    glTexCoord2f(0.832274, -0.965809);
    glNormal3f(-0.2943, -0.6480, 0.7024);
    glVertex3f(-2.319730, 7.460398, 2.323781);
    glTexCoord2f(0.704244, 0.017786);
    glNormal3f(-0.0751, 0.7102, 0.7000);
    glVertex3f(-2.445951, 5.771827, 0.355042);
    glTexCoord2f(0.616434, -0.879462);
    glNormal3f(-0.8162, 0.3992, -0.4177);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.198746, 9.063770, -2.746028);
    glTexCoord2f(1.579810, 2.874998);
    glNormal3f(0.3366, 0.7303, -0.5944);
    glVertex3f(-1.006221, 8.033410, -1.807889);
    glTexCoord2f(1.547382, 2.261355);
    glNormal3f(-0.8400, 0.5214, -0.1503);
    glVertex3f(-0.587266, 7.963510, -1.609305);
    glTexCoord2f(1.672948, 2.241722);
    glNormal3f(0.6799, 0.3969, 0.6166);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.198746, 9.063770, -2.746028);
    glTexCoord2f(1.579810, 2.874998);
    glNormal3f(0.3366, 0.7303, -0.5944);
    glVertex3f(-0.617416, 7.676767, -1.962022);
    glTexCoord2f(1.287044, 2.350152);
    glNormal3f(0.4672, -0.5377, -0.7018);
    glVertex3f(-1.006221, 8.033410, -1.807889);
    glTexCoord2f(1.547382, 2.261355);
    glNormal3f(-0.8400, 0.5214, -0.1503);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.618646, 7.318822, -0.290189);
    glTexCoord2f(0.927849, 1.705899);
    glNormal3f(0.6502, 0.4346, 0.6232);
    glVertex3f(-0.611861, 6.696321, -1.724902);
    glTexCoord2f(0.430303, 2.293682);
    glNormal3f(0.2697, 0.7772, -0.5685);
    glVertex3f(-0.880610, 6.548549, -1.289841);
    glTexCoord2f(0.338155, 2.150959);
    glNormal3f(-0.6290, 0.2862, 0.7228);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.437030, 6.185566, -1.487890);
    glTexCoord2f(0.237108, 1.914098);
    glNormal3f(0.6758, -0.7308, 0.0958);
    glVertex3f(0.618646, 7.318822, -0.290189);
    glTexCoord2f(0.927849, 1.705899);
    glNormal3f(0.6502, 0.4346, 0.6232);
    glVertex3f(-0.880610, 6.548549, -1.289841);
    glTexCoord2f(0.338155, 2.150959);
    glNormal3f(-0.6290, 0.2862, 0.7228);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.941651, 3.010202, -0.521079);
    glTexCoord2f(1.219444, 2.184462);
    glNormal3f(0.6538, -0.3217, 0.6849);
    glVertex3f(0.978565, 3.759707, -1.854390);
    glTexCoord2f(1.904776, 2.125485);
    glNormal3f(0.7941, 0.5463, -0.2665);
    glVertex3f(0.645007, 3.708727, -1.576262);
    glTexCoord2f(1.921765, 2.238736);
    glNormal3f(-0.4076, 0.4466, 0.7965);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.941651, 3.010202, -0.521079);
    glTexCoord2f(1.219444, 2.184462);
    glNormal3f(0.6538, -0.3217, 0.6849);
    glVertex3f(0.720091, 3.282272, -1.778549);
    glTexCoord2f(1.826525, 1.899883);
    glNormal3f(-0.1376, -0.9873, -0.0800);
    glVertex3f(0.978565, 3.759707, -1.854390);
    glTexCoord2f(1.904776, 2.125485);
    glNormal3f(0.7941, 0.5463, -0.2665);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.941651, 3.010202, -0.521079);
    glTexCoord2f(1.269191, 2.155520);
    glNormal3f(0.6538, -0.3217, 0.6849);
    glVertex3f(0.645007, 3.708727, -1.576262);
    glTexCoord2f(1.720834, 1.714523);
    glNormal3f(-0.4076, 0.4466, 0.7965);
    glVertex3f(0.720091, 3.282272, -1.778549);
    glTexCoord2f(1.826525, 1.899883);
    glNormal3f(-0.1376, -0.9873, -0.0800);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.533100, 4.701955, -0.342601);
    glTexCoord2f(2.499901, 0.236813);
    glNormal3f(0.4000, 0.7797, -0.4817);
    glVertex3f(-1.529479, 4.605387, -0.495885);
    glTexCoord2f(2.621113, 0.213498);
    glNormal3f(0.4000, 0.7797, -0.4817);
    glVertex3f(-1.860904, 4.796040, -0.462516);
    glTexCoord2f(2.791479, 0.276933);
    glNormal3f(0.4000, 0.7797, -0.4817);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.826233, 6.208210, 0.033123);
    glTexCoord2f(1.990513, 2.835753);
    glNormal3f(-0.5882, 0.8087, 0.0057);
    glVertex3f(-1.968872, 5.347178, -0.031078);
    glTexCoord2f(2.345872, 2.497056);
    glNormal3f(0.6542, 0.6766, -0.3380);
    glVertex3f(-2.253538, 5.161633, -0.051930);
    glTexCoord2f(2.417036, 2.624530);
    glNormal3f(-0.7465, -0.3632, -0.5576);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.968872, 5.347178, -0.031078);
    glTexCoord2f(2.469139, 2.838256);
    glNormal3f(0.6542, 0.6766, -0.3380);
    glVertex3f(-2.826233, 6.208210, 0.033123);
    glTexCoord2f(1.990513, 2.835753);
    glNormal3f(-0.5882, 0.8087, 0.0057);
    glVertex3f(-2.158098, 5.235932, 0.160441);
    glTexCoord2f(2.449708, 2.735004);
    glNormal3f(-0.1815, 0.0040, 0.9834);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.826233, 6.208210, 0.033123);
    glTexCoord2f(1.990513, 2.835753);
    glNormal3f(-0.5882, 0.8087, 0.0057);
    glVertex3f(-2.253538, 5.161633, -0.051930);
    glTexCoord2f(2.417036, 2.624530);
    glNormal3f(-0.7465, -0.3632, -0.5576);
    glVertex3f(-2.158098, 5.235932, 0.160441);
    glTexCoord2f(2.449708, 2.735004);
    glNormal3f(-0.1815, 0.0040, 0.9834);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.314994, 5.324448, -1.388715);
    glTexCoord2f(2.288047, -1.973339);
    glNormal3f(-0.7947, 0.1306, 0.5928);
    glVertex3f(-2.230624, 6.383121, -3.138590);
    glTexCoord2f(2.252466, -1.219074);
    glNormal3f(-0.9615, -0.2199, 0.1649);
    glVertex3f(-1.812376, 6.360534, -3.691374);
    glTexCoord2f(2.026264, -1.136874);
    glNormal3f(0.1641, -0.3381, -0.9267);
    glVertex3f(-0.899091, 4.796803, -1.949262);
    glTexCoord2f(1.921075, -1.948997);
    glNormal3f(-0.0275, -0.7895, -0.6132);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.877529, 5.985208, -2.799964);
    glTexCoord2f(2.955870, 1.835218);
    glNormal3f(-0.5437, 0.8358, -0.0769);
    glVertex3f(-1.690146, 6.113536, -2.730050);
    glTexCoord2f(2.983919, 1.960406);
    glNormal3f(-0.5437, 0.8358, -0.0769);
    glVertex3f(-1.649241, 6.123441, -2.911571);
    glTexCoord2f(2.900631, 1.721090);
    glNormal3f(-0.5437, 0.8358, -0.0769);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.067270, 5.702630, -2.549646);
    glTexCoord2f(2.227261, -0.143612);
    glNormal3f(0.7696, -0.4544, -0.4486);
    glVertex3f(-1.045056, 6.768772, -3.591383);
    glTexCoord2f(2.770040, -0.003104);
    glNormal3f(0.1145, 0.6708, -0.7328);
    glVertex3f(-1.128173, 5.896754, -2.400779);
    glTexCoord2f(2.210763, -0.032341);
    glNormal3f(0.3452, 0.7455, 0.5701);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.045056, 6.768772, -3.591383);
    glTexCoord2f(2.770040, -0.003104);
    glNormal3f(0.1145, 0.6708, -0.7328);
    glVertex3f(-1.451593, 5.726283, -2.570899);
    glTexCoord2f(2.271672, -0.275721);
    glNormal3f(-0.9000, -0.0703, -0.4303);
    glVertex3f(-1.128173, 5.896754, -2.400779);
    glTexCoord2f(2.358441, -0.399846);
    glNormal3f(0.3452, 0.7455, 0.5701);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-2.465093, 7.822194, -2.306898);
    glTexCoord2f(1.564606, -0.386213);
    glNormal3f(-0.8034, 0.5151, -0.2986);
    glVertex3f(-1.037442, 6.943398, -2.059374);
    glTexCoord2f(2.186924, -0.219751);
    glNormal3f(0.1458, -0.0415, -0.9884);
    glVertex3f(-1.301611, 6.760573, -1.676179);
    glTexCoord2f(2.102832, -0.019424);
    glNormal3f(-0.7278, -0.5933, 0.3440);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.051056, 7.189873, -1.698019);
    glTexCoord2f(1.969819, 0.141089);
    glNormal3f(0.2127, 0.8815, 0.4216);
    glVertex3f(-2.465093, 7.822194, -2.306898);
    glTexCoord2f(1.564606, -0.386213);
    glNormal3f(-0.8034, 0.5151, -0.2986);
    glVertex3f(-1.301611, 6.760573, -1.676179);
    glTexCoord2f(2.102832, -0.019424);
    glNormal3f(-0.7278, -0.5933, 0.3440);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.350393, 3.255892, -1.933458);
    glTexCoord2f(2.176824, 1.729762);
    glNormal3f(-0.5580, -0.8054, -0.2000);
    glVertex3f(1.692837, 2.550531, -2.838055);
    glTexCoord2f(2.386315, 2.371786);
    glNormal3f(0.6623, -0.5265, -0.5330);
    glVertex3f(0.613229, 3.435482, -1.710121);
    glTexCoord2f(2.045094, 1.782811);
    glNormal3f(0.6009, -0.2391, 0.7627);
    glEnd();

}
void posisicabang (){
    glPushMatrix();
    glColor3f(0.7, 0.5, 0.1 );
    glTranslatef(0.0, 0.0, 1.0);
	cabang();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 5.0, 0.2 );
    semak();
    glPopMatrix();
}

void balok ()
{
glBegin(GL_POLYGON);
    glPushMatrix();
    //depan
    glBegin(GL_POLYGON);
        glColor3f(1,0,0);
        glVertex3f(-0.5,0.5,0);
        glVertex3f(0.5,0.5,0);
        glVertex3f(0.5,-0.5,0);
        glVertex3f(-0.5,-0.5,0);
    glEnd();
    //kanan

    glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex3f(0.5,0.5,0);
        glVertex3f(0.5,0.5,-1);
        glVertex3f(0.5,-0.5,-1);
        glVertex3f(0.5,-0.5,0);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
        glColor3f(0,0,1);
        glVertex3f(-0.5,0.5,0);
        glVertex3f(-0.5,0.5,-1);
        glVertex3f(-0.5,-0.5,-1);
        glVertex3f(-0.5,-0.5,0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        glVertex3f(-0.5,0.5,-1);
        glVertex3f(0.5,0.5,-1);
        glVertex3f(0.5,-0.5,-1);
        glVertex3f(-0.5,-0.5,-1);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
        glColor3f(0,1,1);
        glVertex3f(-0.5,0.5,0);
        glVertex3f(0.5,0.5,0);
        glVertex3f(0.5,0.5,-1);
        glVertex3f(-0.5,0.5,-1);
    glEnd();
    //bawah
        glBegin(GL_POLYGON);
        glColor3f(1,0,1);
        glVertex3f(-0.5,-0.5,0);
        glVertex3f(0.5,-0.5,0);
        glVertex3f(0.5,-0.5,-1);
        glVertex3f(-0.5,-0.5,-1);
    glEnd();
    glPopMatrix();

    glEnd();

}

void trapesium(){
    //Sisi depan belakang
    glBegin(GL_POLYGON);
        glNormal3f(-2.0, 0.0, -2.0);
        glVertex3f(0.0, 0.0, -2.0);
        glNormal3f(2.0, 0.0, -2.0);
        glVertex3f(2.0, 0.0, -2.0);
        glNormal3f(2.0, 4.0, -2.0);
        glVertex3f(2.0, 4.0, -2.0);
        glNormal3f(1.0, 4.0, -2.0);
        glVertex3f(1.0, 4.0, -2.0);
        glNormal3f(-2.0, 1.0, -2.0);
        glVertex3f(-2.0, 1.0, -2.0);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(-2.0, 0.0, 2.0);
        glVertex3f(-2.0, 0.0, 2.0);
        glNormal3f(2.0, 0.0, 2.0);
        glVertex3f(2.0, 0.0, 2.0);
        glNormal3f(2.0, 4.0, 2.0);
        glVertex3f(2.0, 4.0, 2.0);
        glNormal3f(1.0, 4.0, 2.0);
        glVertex3f(1.0, 4.0, 2.0);
        glNormal3f(-2.0, 1.0, 2.0);
        glVertex3f(-2.0, 1.0, 2.0);
    glEnd();

    //Penutup samping
    glBegin(GL_QUADS);
        glNormal3f(1.0, 4.0, 2.0);
        glVertex3f(1.0, 4.0, 2.0);
        glNormal3f(1.0, 4.0, -2.0);
        glVertex3f(1.0, 4.0, -2.0);
        glNormal3f(-2.0, 1.0, -2.0);
        glVertex3f(-2.0, 1.0, -2.0);
        glNormal3f(-2.0, 1.0, 2.0);
        glVertex3f(-2.0, 1.0, 2.0);
    glEnd();

    // Penutup kiri
    glBegin(GL_QUADS);
        glNormal3f(-2.0, 1.0, 2.0);
        glVertex3f(-2.0, 1.0, 2.0);
        glNormal3f(-2.0, 1.0, -2.0);
        glVertex3f(-2.0, 1.0, -2.0);
        glNormal3f(-2.0, 0.0, -2.0);
        glVertex3f(-2.0, 0.0, -2.0);
        glNormal3f(-2.0, 0.0, 2.0);
        glVertex3f(-2.0, 0.0, 2.0);
    glEnd();

    //Penutup Bawah
    glBegin(GL_QUADS);
        glNormal3f(-2.0, 0.0, -2.0);
        glVertex3f(-2.0, 0.0, -2.0);
        glNormal3f(-2.0, 0.0, 2.0);
        glVertex3f(-2.0, 0.0, 2.0);
        glNormal3f(2.0, 0.0, 2.0);
        glVertex3f(2.0, 0.0, 2.0);
        glNormal3f(2.0, 0.0, -2.0);
        glVertex3f(2.0, 0.0, -2.0);
    glEnd();

    //Penutup Kanan
    glBegin(GL_QUADS);
        glNormal3f(2.0, 0.0, 2.0);
        glVertex3f(2.0, 0.0, 2.0);
        glNormal3f(2.0, 0.0, -2.0);
        glVertex3f(2.0, 0.0, -2.0);
        glNormal3f(2.0, 4.0, -2.0);
        glVertex3f(2.0, 4.0, -2.0);
        glNormal3f(2.0, 4.0, 2.0);
        glVertex3f(2.0, 4.0, 2.0);
    glEnd();

    //Penutup Atas
    glBegin(GL_QUADS);
        glNormal3f(2.0, 4.0, -2.0);
        glVertex3f(2.0, 4.0, -2.0);
        glNormal3f(2.0, 4.0, 2.0);
        glVertex3f(2.0, 4.0, 2.0);
        glNormal3f(1.0, 4.0, 2.0);
        glVertex3f(1.0, 4.0, 2.0);
        glNormal3f(1.0, 4.0, -2.0);
        glVertex3f(1.0, 4.0, -2.0);
    glEnd();
}
void kuburan()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(6.0, 0.9, 2.0);
    balok();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5,0.3,0.5);
    glTranslatef(14.0, 4.8, -32.0);
    trapesium();
    glPopMatrix();

}



void alas(){
    glPushMatrix();
    glColor3f(0.3, 0.7, 0.35);
    glTranslatef(50,-0.2,-50);
    glScalef(50,0.2,50);
    glutSolidCube(2);
    glPopMatrix();
}
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->Update();
    /*
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
    */
    garis2frontback();
    garis2leftright();
//    posisiLampu(5,5,-5);
    glPushMatrix();
    glTranslatef(80,1,-60);
    rumahKeranda();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5,0,-0.5);
    tuguPojok2();
    glPopMatrix();
    pagar();

    glPushMatrix();
    glTranslatef(42.5,0,0);
    jalan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 0, 5);
    lampu();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -5);
    sumur();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, 1, -10);
    posisicabang();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 1, -15);
    kuburan();
    glPopMatrix();
    glPushMatrix();
    alas();
    glPopMatrix();



    // Flush buffers to screen

    glFlush();
    glutSwapBuffers();
    // sawp buffers called because we are using double buffering
   // glutSwapBuffers();
}
void reshape(int w, int h){
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
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(1366,768);
    glutCreateWindow("Tugas Shading");
    camera = new Camera( 0.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
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
