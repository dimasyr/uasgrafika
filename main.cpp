#include <iostream>
#include <GL/glut.h>
#include "Camera.h"
#include <stdlib.h>
#include <math.h>      // For math routines (such as sqrt & trig).
#include <cstdio>


#define PI 3.14159265358979323846
#define GL_GENERATE_MIPMAP 0x8191
using namespace std;
//skala scale tiap kotak =2.5
//skala translate tiap kotak x=5, y dan z =1

//float posCamx=0, posCamy=0, posCamz=5, lookCamx=0, lookCamy=0, lookCamz=0;
GLuint green;
GLuint black;
GLuint air;
GLuint tanah;
GLuint pohontxt;
GLuint bungatxt;
GLuint sumurtxt;
GLuint jalantxt;
GLuint kuburantxt;
GLuint tugutxt;
GLuint tembok;
GLuint cagaksumur;
GLuint atap;
GLuint timbatxt;
GLuint backijo;
GLuint innalillahi;
GLuint stone;
GLuint gapurabawah;
GLuint gapuraatas;
GLuint nisan;
GLuint kayu;
GLuint daun;
GLuint silver;
GLuint rust;

GLUquadricObj *p = gluNewQuadric();

GLfloat xRotated, yRotated, zRotated, poskerx=0, poskery=0, poskerz=0;
GLdouble radius=1.5;

GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0}; //Black Color
GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
GLfloat qaRed[] = {1.0, 0.0, 0.0, 1.0}; //White Color
//GLfloat letakCahaya[][]

int px[500],pz[500],px2[500],pz2[500];

float cahayax=0.0, cahayay=0.0, cahayaz=0.0;
//static GLdouble viewer[]= {0.0, 0.0, 10.0};
static GLfloat theta = 0.0, speed = 0.55, speed2 = 2.35, theta2= 0.0;
float y=0;

Camera*	camera;

float textcoord[][2] = {
        {0, 1},
        {0, 0},
        {1, 0},
        {1, 1}
};

void display(void);
void reshape(int x, int y);

GLuint loadBmpFile(const char* fileName) {
    GLuint texture_id;
    unsigned char * pBitmapData;
    int	width, height,bpp;

    FILE				* fp;
	BITMAPFILEHEADER	bmpFH;
	BITMAPINFOHEADER	bmpIH;
	unsigned char		temp;

	fp = fopen( fileName, "rb" ); // rb = read binary
	if( fp == NULL )
		return( -1 );
	// read in the file header
	fread( ( void * )&bmpFH, sizeof( BITMAPFILEHEADER ), 1, fp );
	if( bmpFH.bfType != 0x4D42 ) {
		fclose( fp );
		return( -1 );
	}

	// read in the info header
	fread( ( void * )&bmpIH, sizeof( BITMAPINFOHEADER ), 1, fp );
	// move the file stream to teh start of the image data
	fseek( fp, bmpFH.bfOffBits, SEEK_SET );
	// set size in bytes
	bmpIH.biSizeImage = bmpIH.biHeight * bmpIH.biWidth * ( bmpIH.biBitCount / 8 );
	// allocate mem for the image data
	pBitmapData = new unsigned char[ bmpIH.biSizeImage ];
	if( pBitmapData == NULL ){
		// if there was trouble allocating the mem
		fclose( fp );
		return( -1 );
	}
	// read from the stream ( 1 byte at a time, biSizeImage times )
	fread( ( void * )pBitmapData, 1, bmpIH.biSizeImage, fp );
	if( pBitmapData == NULL ) {
		fclose( fp );
		return( -1 );
	}
	for( int c = 0; c < bmpIH.biSizeImage; c += 3 ) {
		// swap the red and blue bytes
		temp					= pBitmapData[ c ];
		pBitmapData[ c ]		= pBitmapData[ c + 2 ];
		pBitmapData[ c + 2 ]	= temp;
	}

	fclose( fp );

	width	= bmpIH.biWidth;
	height	= bmpIH.biHeight;
	bpp		= bmpIH.biBitCount;

	glGenTextures( 1, &texture_id );
	// bind and pass texure data into openGL
	glBindTexture( GL_TEXTURE_2D, texture_id );
	// set parameters to make mipmaps
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	// create the textures
	glTexImage2D( GL_TEXTURE_2D, 0,
				  GL_RGB, width, height, 0,
				  GL_RGB, GL_UNSIGNED_BYTE, pBitmapData );

    return texture_id;
}

GLfloat cvertices[8][3] = {{-0.5 , -0.5, 0.5},
                           { 0.5 , -0.5, 0.5},
                           { 0.5 ,  0.5, 0.5},
                           {-0.5 ,  0.5, 0.5},

                           {-0.5 , -0.5, -0.5},
                           { 0.5 , -0.5, -0.5},
                           { 0.5 ,  0.5, -0.5},
                           {-0.5 ,  0.5, -0.5}
                           };

void normalize(float*v){
    float length =sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

    for(int i=0; i<3; i++)
    {
        v[i]=v[i]/length;
    }
}
float *cross_product(float*a, float*b){
    float* result = new float[3];
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] =  -(a[0] * b[2] - a[2] * b[0]);
    result[2] = a[0] * b[1] - a[1] * b[0];

    normalize(result);

    return result;
}
float *calculate_normal(float *a, float *b, float *c){
    float x[]={b[0]-a[0], b[1]-a[1], b[2]-a[2] };
    float y[]={c[0]-a[0], c[1]-a[1], c[2]-a[2] };

    float *result=cross_product(x,y);


    return result;
}
void pillarMenara(float posisiX, float posisiY, float posisiZ, float tinggi, float lebarBawah, float lebarAtas, float texture, GLint texture_id, int detail, float derajadY){
glPushMatrix();
glTranslatef(posisiX, posisiY, posisiZ);
glRotatef(derajadY, 0,1,0);
    float oldX, oldY, oldZ, oldX1, oldY1, oldZ1, X, Y, Z, X1, Y1, Z1;
    oldX=lebarBawah*cos(0* PI / 180.0);
    oldZ=lebarBawah*sin(0* PI / 180.0);
    oldX1=lebarAtas*cos(0* PI / 180.0);
    oldZ1=lebarAtas*sin(0* PI / 180.0);

        X=lebarBawah*cos(0* PI / 180.0);
        Z=lebarBawah*sin(0* PI / 180.0);
        X1=lebarAtas*cos(0* PI / 180.0);
        Z1=lebarAtas*sin(0* PI / 180.0);

        float sizeX, sizeY, texX=0, texY=0;

        sizeY=abs(sqrt(pow((X+posisiX)-(oldX+posisiX),2)+pow(abs((posisiY+tinggi)-(posisiY)),2)));

glBindTexture(GL_TEXTURE_2D, texture_id);
    for(int i=0; i<=360; i+=detail){
        X=lebarBawah*cos(i* PI / 180.0);
        Z=lebarBawah*sin(i* PI / 180.0);
        X1=lebarAtas*cos(i* PI / 180.0);
        Z1=lebarAtas*sin(i* PI / 180.0);



        GLfloat vertices[4][3]=
        {
            {oldX, 0, oldZ},
            {oldX1, tinggi, oldZ1},
            {X1, tinggi, Z1},
            {X, 0, Z}
        };



        glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[0], vertices[1], vertices[2]));
        sizeX=abs(sqrt(pow(abs((X+posisiX)-(oldX+posisiX)),2)+pow(abs((Z+posisiZ)-(oldZ+posisiZ)),2)));

                glTexCoord2f(texX/texture, texY/texture);
                //cout<<"awal "<<(texX+sizeX)/texture<<endl;
                glVertex3fv(vertices[0]);
                glTexCoord2f((texX)/texture, (texY+sizeY)/texture);

                glVertex3fv(vertices[1]);
                glTexCoord2f((texX+sizeX)/texture, (texY+sizeY)/texture);
                glVertex3fv(vertices[2]);

                //cout<<"akhir "<<texX/texture<<endl;
                glTexCoord2f((texX+sizeX)/texture, texY/texture);
                glVertex3fv(vertices[3]);
            //}
        glEnd();

        oldX=X;
        oldZ=Z;
        oldX1=X1;
        oldZ1=Z1;
        texX+=sizeX;
    }
    glPopMatrix();
}
void alaskubus(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat panjang, GLfloat lebar, GLfloat tinggi,
                  GLfloat texture_scale) {
    GLfloat vertices[][6][3] = {
            {//sisi bawah
                    {posX,           posY,          posZ},
                    {posX + panjang, posY,          posZ},
                    {posX + panjang, posY,          posZ - lebar},
                    {posX,           posY,          posZ - lebar},
            },
            {//sisi atas
                    {posX,           posY + tinggi, posZ},
                    {posX + panjang, posY + tinggi, posZ},
                    {posX + panjang, posY + tinggi, posZ - lebar},
                    {posX,           posY + tinggi, posZ - lebar},
            },
            {//sisi samping kiri
                    {posX,           posY,          posZ},
                    {posX,           posY,          posZ - lebar},
                    {posX,           posY + tinggi, posZ - lebar},
                    {posX,           posY + tinggi, posZ},
            },
            {//sisi samping kanan
                    {posX + panjang, posY,          posZ},
                    {posX + panjang, posY,          posZ - lebar},
                    {posX + panjang, posY + tinggi, posZ - lebar},
                    {posX + panjang, posY + tinggi, posZ},
            },
            {//sisi depan
                    {posX,           posY,          posZ},
                    {posX + panjang, posY,          posZ},
                    {posX + panjang, posY + tinggi, posZ},
                    {posX,           posY + tinggi, posZ},
            },
            {//sisi belakang
                    {posX,           posY,          posZ - lebar},
                    {posX + panjang, posY,          posZ - lebar},
                    {posX + panjang, posY + tinggi, posZ - lebar},
                    {posX,           posY + tinggi, posZ - lebar},
            }
    };
    for (int i = 0; i < 6; ++i) {
        glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[i][0], vertices[i][1], vertices[i][2]));
        for (int j = 0; j < 4; ++j) {
            if (i == 0 || i == 1)
                glTexCoord2f(vertices[i][j][0] / texture_scale, vertices[i][j][2] / texture_scale);
            else if (i == 2 || i == 3)
                glTexCoord2f(vertices[i][j][2] / texture_scale, vertices[i][j][1] / texture_scale);
            else
                glTexCoord2f(vertices[i][j][0] / texture_scale, vertices[i][j][1] / texture_scale);
            glVertex3fv(vertices[i][j]);
        }
        glEnd();
    }
}
void cube(float besar, float texture_scale){
    // Depan
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(cvertices[0], cvertices[1], cvertices[2]));
        glTexCoord2f(0,0);
        glVertex3f(cvertices[0][0]*besar, cvertices[0][1]*besar, cvertices[0][2]*besar);
        glTexCoord2f(1,0);
        glVertex3f(cvertices[1][0]*besar, cvertices[1][1]*besar, cvertices[1][2]*besar);
        glTexCoord2f(1,1);
        glVertex3f(cvertices[2][0]*besar, cvertices[2][1]*besar, cvertices[2][2]*besar);
        glTexCoord2f(0,1);
        glVertex3f(cvertices[3][0]*besar, cvertices[3][1]*besar, cvertices[3][2]*besar);

    glEnd();
    // Atas
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(cvertices[3], cvertices[2], cvertices[6]));
        glTexCoord2f(0,0);
        glVertex3f(cvertices[3][0]*besar, cvertices[3][1]*besar, cvertices[3][2]*besar);
        glTexCoord2f(1,0);
        glVertex3f(cvertices[2][0]*besar, cvertices[2][1]*besar, cvertices[2][2]*besar);
        glTexCoord2f(1,1);
        glVertex3f(cvertices[6][0]*besar, cvertices[6][1]*besar, cvertices[6][2]*besar);
        glTexCoord2f(0,1);
        glVertex3f(cvertices[7][0]*besar, cvertices[7][1]*besar, cvertices[7][2]*besar);
    glEnd();
    // Belakang
    glBegin(GL_QUADS);
         glNormal3fv(calculate_normal(cvertices[4], cvertices[5], cvertices[6]));
        glTexCoord2f(0,0);
        glVertex3f(cvertices[4][0]*besar, cvertices[4][1]*besar, cvertices[4][2]*besar);
        glTexCoord2f(1,0);
        glVertex3f(cvertices[5][0]*besar, cvertices[5][1]*besar, cvertices[5][2]*besar);
        glTexCoord2f(1,1);
        glVertex3f(cvertices[6][0]*besar, cvertices[6][1]*besar, cvertices[6][2]*besar);
        glTexCoord2f(0,1);
        glVertex3f(cvertices[7][0]*besar, cvertices[7][1]*besar, cvertices[7][2]*besar);
    glEnd();
    // Bawah
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(cvertices[0], cvertices[1], cvertices[5]));
        glTexCoord2f(0,0);
        glVertex3f(cvertices[0][0]*besar, cvertices[0][1]*besar, cvertices[0][2]*besar);
        glTexCoord2f(1,0);
        glVertex3f(cvertices[1][0]*besar, cvertices[1][1]*besar, cvertices[1][2]*besar);
        glTexCoord2f(1,1);
        glVertex3f(cvertices[5][0]*besar, cvertices[5][1]*besar, cvertices[5][2]*besar);
        glTexCoord2f(0,1);
        glVertex3f(cvertices[4][0]*besar, cvertices[4][1]*besar, cvertices[4][2]*besar);
    glEnd();
    // Kiri
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(cvertices[4], cvertices[0], cvertices[3]));
        glTexCoord2f(0,0);
        glVertex3f(cvertices[4][0]*besar, cvertices[5][1]*besar, cvertices[5][2]*besar);
        glTexCoord2f(1,0);
        glVertex3f(cvertices[0][0]*besar, cvertices[0][1]*besar, cvertices[0][2]*besar);
        glTexCoord2f(1,1);
        glVertex3f(cvertices[3][0]*besar, cvertices[3][1]*besar, cvertices[3][2]*besar);
        glTexCoord2f(0,1);
        glVertex3f(cvertices[7][0]*besar, cvertices[7][1]*besar, cvertices[7][2]*besar);
    glEnd();
    // Kanan
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(cvertices[5], cvertices[1], cvertices[2]));
        glTexCoord2f(0,0);
        glVertex3f(cvertices[5][0]*besar, cvertices[4][1]*besar, cvertices[4][2]*besar);
        glTexCoord2f(1,0);
        glVertex3f(cvertices[1][0]*besar, cvertices[1][1]*besar, cvertices[1][2]*besar);
        glTexCoord2f(1,1);
        glVertex3f(cvertices[2][0]*besar, cvertices[2][1]*besar, cvertices[2][2]*besar);
        glTexCoord2f(0,1);
        glVertex3f(cvertices[6][0]*besar, cvertices[6][1]*besar, cvertices[6][2]*besar);
    glEnd();

}
void idleFunc(void){
    //zRotated += 0.02;

    theta2 +=speed2;

    if((camera->pos.x>85) && (camera->pos.z < -85)){
      theta += speed;
    }

    if(theta2<=40){
        speed2 = 3.00;
    }
    else if((theta2 >40) && (theta2 <70) ){
        speed2 = 3.75;
    }
    else if((theta2 > 70) && (theta2 <110)){
        speed2 = 3.45;
    }
    else if((theta2>110) && (theta2 <140)){
        speed2 = 3.75;
    }
    else if((theta2>140) && (theta2 <=180)){
        speed2 = 3.00;
    }

//    theta2 += sin //theta = theta + speed
    if( theta > 360.0 ) theta -= 360.0;
    glutPostRedisplay();
}
void setLighting(){
    // Set lighting intensity and color
    GLfloat qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat qaDiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat qaSpecularLight[] = {0, 0,0,1};
    GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
    GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};

    // Light source position
    GLfloat qaLightPosition[]    = {cahayax, cahayay, cahayaz, 1};
    GLfloat qaLightPosition2[]    = {50, 6, -60, 0.7};

    // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

    // Set the light position
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition2);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}
void setMaterialijo(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
}
void setMaterialhitam(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaBlack);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaBlack);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaBlack);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
}
void setMaterialmerah(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaRed);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaRed);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaRed);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
}
void setMaterialputih(){
    float MatAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    float MatDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f  };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
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
void setmaterialWhiteRubber(){
    float MatAmbient[] = { 0.05f,0.05f,0.05f,1.0f };
    float MatDiffuse[] = { 0.5f,0.5f,0.5f,1.0f  };
    float MatSpecular[] = { 0.7f,0.7f,0.7f,1.0f };
    float MatShininess = 10.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
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
}/*
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
void setMaterialBrass(){
float mat_ambient[] ={ 0.329412f, 0.223529f, 0.027451f,1.0f };
float mat_diffuse[] ={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
float mat_specular[] ={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
float shine = 27.8974f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
void setMaterialBlackRubber(){
float mat_ambient[] ={ 0.0f, 0.0f, 0.0f, 1.0f };
float mat_diffuse[] ={ 0.09f, 0.09f, 0.09f, 1.0f };
float mat_specular[] ={ 0.70f, 0.70f, 0.70f, 1.0f };
float shine = 76.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}*/
void keys(unsigned char key, int x, int y){

///* Use x, X, y, Y, z, and Z keys to move viewer */

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
        camera = new Camera( 50.0, 2.7, 20.0, 50.0, 2.7, -50.0, 0.0, 1.0, 0.0 );
        break;
    default:
        break;
    }

//   if(key == 'b' || key == 'B') spin = !spin;



   if(key == '1') cahayax-= 5.0f;
   if(key == '2') cahayax+= 5.0f;
   if(key == '3') cahayay-= 5.0f;
   if(key == '4') cahayay+= 5.0f;
   if(key == '5') cahayaz-= 5.0f;
   if(key == '6') cahayaz+= 5.0f;




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
    //1
    GLfloat vertices[3][3]=
    {
        {0.02,3,0},
        {5,5,-5},
        {0.02,3,-10}
    };
    //atap kiri
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices[0],vertices[1],vertices[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices[x][0],vertices[x][1]);
            glVertex3fv(vertices[x]);
        }
    glEnd();
    glPopMatrix();
    //2
    GLfloat vertices2[3][3]=
    {
        {9.98,3,0},
        {5,5,-5},
        {9.98,3,-9.98}
    };
    //atap kanan
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices2[0],vertices2[1],vertices2[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices[x][0],vertices[x][1]);
            glVertex3fv(vertices2[x]);
        }
    glEnd();
    glPopMatrix();
    //3
    GLfloat vertices3[3][3]=
    {
        {0.02,3,-9.98},
        {5,5,-5},
        {9.98,3,-9.98}
    };
    //atap belakang
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices3[0],vertices3[1],vertices3[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices[x][0],vertices[x][1]);
            glVertex3fv(vertices3[x]);
        }
    glEnd();
    glPopMatrix();
    //4
    GLfloat vertices4[3][3]=
    {
        {0.02,3,0},
        {5,5,-5},
        {9.98,3,0}
    };
    //atap depan
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices4[0],vertices4[1],vertices4[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices[x][0],vertices[x][1]);
            glVertex3fv(vertices4[x]);
        }
    glEnd();
    glPopMatrix();
}
void atapRumahKeranda2(float r, float g, float b){
    //1
    GLfloat vertices[3][3]=
    {
        {-0.02,3,0},
        {5,5.02,-5},
        {-0.02,3,-10.02}
    };
    //atap kiri
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices[0],vertices[1],vertices[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices[x][0],vertices[x][1]);
            glVertex3fv(vertices[x]);
        }
    glEnd();
    glPopMatrix();
    //2
    GLfloat vertices2[3][3]=
    {
        {10.02,3,0},
        {5,5.02,-5},
        {10.02,3,-10.02}
    };
    //atap kanan
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices2[0],vertices2[1],vertices2[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices2[x][0],vertices2[x][1]);
            glVertex3fv(vertices2[x]);
        }
    glEnd();
    glPopMatrix();
    //3
    GLfloat vertices3[3][3]=
    {
        {-0.02,3,-10.02},
        {5,5.02,-5},
        {10.02,3,-10.02}
    };
    //atap belakang
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices3[0],vertices3[1],vertices3[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices3[x][0],vertices3[x][1]);
            glVertex3fv(vertices3[x]);
        }
    glEnd();
    glPopMatrix();
    //4
    GLfloat vertices4[3][3]=
    {
        {-0.02,3,0},
        {5,5.02,-5},
        {10.02,3,0}
    };
    //atap depan
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices4[0],vertices4[1],vertices4[2]));
        for(int x=0;x<3;x++){
            glTexCoord2f(vertices4[x][0],vertices4[x][1]);
            glVertex3fv(vertices4[x]);
        }
    glEnd();
    glPopMatrix();
}
void tebalAtapKeranda(){
    //1
    GLfloat vertices[4][3]=
    {
        {-0.02,3,0},
        {-0.02,3.05,0},
        {10.02,3.05,0},
        {10.02,3,0}
    };
    //depan
    glPushMatrix();
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[0],vertices[1],vertices[2]));
        for(int x=0;x<4;x++){
            glVertex3fv(vertices[x]);
        }
    glEnd();
    glPopMatrix();
    //2
    GLfloat vertices2[4][3]=
    {
        {-0.02,3,-10.02},
        {-0.02,3.05,-10.02},
        {10.02,3.05,-10.02},
        {10.02,3,-10.02}
    };
    //belakang
    glPushMatrix();
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices2[0],vertices2[1],vertices2[2]));
        for(int x=0;x<4;x++){
            glVertex3fv(vertices2[x]);
        }
    glEnd();
    glPopMatrix();
    //3
    GLfloat vertices3[4][3]=
    {
        {-0.02,3,-10.02},
        {-0.02,3,0},
        {-0.02,3.05,0},
        {-0.02,3.05,-10.02}
    };
    //kiri
    glPushMatrix();
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices3[0],vertices3[1],vertices3[2]));
        for(int x=0;x<4;x++){
            glVertex3fv(vertices3[x]);
        }
    glEnd();
    glPopMatrix();
    //4
    GLfloat vertices4[4][3]=
    {
        {10.02,3,-10.02},
        {10.02,3,0},
        {10.02,3.05,0},
        {10.02,3.05,-10.02}
    };
    //kanan
    glPushMatrix();
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices4[0],vertices4[1],vertices4[2]));
        for(int x=0;x<4;x++){
            glVertex3fv(vertices4[x]);
        }
    glEnd();
    glPopMatrix();
}
void atapSegitiga(float flx, float fly, float flz,
                  float frx, float fry, float frz,
                  float brx, float bry, float brz,
                  float blx, float bly, float blz,
                  float midx, float midy, float midz){
    //atap kiri vertices
    GLfloat vertices[3][3]=
    {
        {flx,fly,flz},
        {midx,midy,midz},
        {blx,bly,blz}
    };
    //atap kiri
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices[0],vertices[1],vertices[2]));
        for(int x=0;x<3;x++){
            glVertex3fv(vertices[x]);
        }
    glEnd();
    glPopMatrix();
    //atap kanan vertices
    GLfloat vertices2[3][3]=
    {
        {frx,fry,frz},
        {midx,midy,midz},
        {brx,bry,brz}
    };
    //atap kanan
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices2[0],vertices2[1],vertices2[2]));
        for(int x=0;x<3;x++){
            glVertex3fv(vertices2[x]);
        }
    glEnd();
    glPopMatrix();
    //atap belakang vertices
    GLfloat vertices3[3][3]=
    {
        {blx,bly,blz},
        {midx,midy,midz},
        {brx,bry,brz}
    };
    //atap belakang
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices3[0],vertices3[1],vertices3[2]));
        for(int x=0;x<3;x++){
            glVertex3fv(vertices3[x]);
        }
    glEnd();
    glPopMatrix();
    //atap depan vertices
    GLfloat vertices4[3][3]=
    {
        {flx,fly,flz},
        {midx,midy,midz},
        {frx,fry,frz}
    };
    //atap depan
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glNormal3fv(calculate_normal(vertices4[0],vertices4[1],vertices4[2]));
        for(int x=0;x<3;x++){
            glVertex3fv(vertices4[x]);
        }
    glEnd();
    glPopMatrix();
}
void tugu(){
    //body
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(0,1,0);
    glScalef(1,2,1);
    cube(1, 10);
    glPopMatrix();
    //body atas
    glPushMatrix();
    glColor3f(1,0.2,0.5);
    glTranslatef(0,2.05,0);
    glScalef(1.2,0.1,1.2);
    cube(1,10);
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
    glBindTexture(GL_TEXTURE_2D, tugutxt);
    tugu();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //baris kiri
    float z=-4.5;
    for(int ctr=0;ctr<19;ctr++){
        glPushMatrix();
        glTranslatef(0,0,z);
        glBindTexture(GL_TEXTURE_2D, tugutxt);
        tugu();
        glBindTexture(GL_TEXTURE_2D, -1);
        glPopMatrix();
        z-=5;
    }
    //belakang kiri
    glPushMatrix();
    glTranslatef(0,0,-99);
    glBindTexture(GL_TEXTURE_2D, tugutxt);
    tugu();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    //depan kanan
    glPushMatrix();
    glTranslatef(99,0,0);
    glBindTexture(GL_TEXTURE_2D, tugutxt);
    tugu();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //baris kanan
    z=-4.5;
    for(int ctr=0;ctr<19;ctr++){
        glPushMatrix();
        glTranslatef(99,0,z);
        glBindTexture(GL_TEXTURE_2D, tugutxt);
        tugu();
        glBindTexture(GL_TEXTURE_2D,-1);
        glPopMatrix();
        z-=5;
    }
    //belakang kanan
    glPushMatrix();
    glTranslatef(99,0,-99);
    glBindTexture(GL_TEXTURE_2D, tugutxt);
    tugu();
    glBindTexture(GL_TEXTURE_2D,-1);
    glPopMatrix();
    // baris belakang
    float x=4.5;
    for(int ctr=0;ctr<19;ctr++){
        glPushMatrix();
        glTranslatef(x,0,-99);
        glBindTexture(GL_TEXTURE_2D, tugutxt);
        tugu();
        glBindTexture(GL_TEXTURE_2D,-1);
        glPopMatrix();
        x+=5;
    }
    //baris depan kiri
    x=4.5;
    for(int ctr=0;ctr<8;ctr++){
        glPushMatrix();
        glTranslatef(x,0,0);
        glBindTexture(GL_TEXTURE_2D, tugutxt);
        tugu();
        glBindTexture(GL_TEXTURE_2D,-1);
        glPopMatrix();
        x+=5;
    }
    //naris depan kanan
    x=94.5;
    for(int ctr=0;ctr<8;ctr++){
        glPushMatrix();
        glTranslatef(x,0,0);
       glBindTexture(GL_TEXTURE_2D, tugutxt);
        tugu();
        glBindTexture(GL_TEXTURE_2D,-1);
        glPopMatrix();
        x-=5;
    }
}
void pagar(){
    //kiri
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(0.5,0.625,-50);
    glScalef(1,2.5,199);
    glBindTexture(GL_TEXTURE_2D, kuburantxt);
    cube(0.5, 5);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //kanan
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(99.5,0.625,-50);
    glScalef(1,2.5,199);
     glBindTexture(GL_TEXTURE_2D, kuburantxt);
    cube(0.5, 10);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //belakang
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(50,0.625,-99.5);
    glRotatef(90,0,1,0);
    glScalef(1,2.5,199);
     glBindTexture(GL_TEXTURE_2D, kuburantxt);
    cube(0.5, 5);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //depan kiri
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(20,0.625,-0.5);
    glRotatef(90,0,1,0);
    glScalef(1,2.5,79);
     glBindTexture(GL_TEXTURE_2D, gapuraatas);
    cube(0.5,10);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //depan kanan
    glPushMatrix();
    glColor3f(0.5,0.1,0.7);
    glTranslatef(80,0.625,-0.5);
    glRotatef(90,0,1,0);
    glScalef(1,2.5,79);
     glBindTexture(GL_TEXTURE_2D, gapuraatas);
    cube(0.5,5);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
}
void posisiLampu(float x, float y, float z){
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(x,y,z);
    glutSolidSphere(0.2,100,100);
    glPopMatrix();
}

void lingkaran(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat jari_jari, GLfloat detail,
                      GLfloat keutuhan, GLfloat texture_scale) {
    keutuhan = (keutuhan > 1) ? 1 : keutuhan;
    glBegin(GL_POLYGON);
    for (GLfloat sudut = -detail; sudut < 360 * keutuhan; sudut += detail) {
        GLfloat x = jari_jari * cos((sudut + detail) * M_PI / 180);
        GLfloat z = jari_jari * sin((sudut + detail) * M_PI / 180);
        glNormal3f(posX + x, posY, posZ + z);
        glTexCoord2f(x / texture_scale, z / texture_scale);
        glVertex3f(posX + x, posY, posZ + z);
    }
    glEnd();
}
void pipa(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat jari_jari_bawah, GLfloat jari_jari_atas, GLfloat tinggi,
            GLfloat detail, GLfloat keutuhan, GLfloat texture_scale) {
    keutuhan = (keutuhan > 1) ? 1 : keutuhan;
    GLfloat Xsebelum = jari_jari_bawah;
    GLfloat Zsebelum = 0;
    int jumlahLooping = 0;
    for (GLfloat sudut = 0; sudut < 360 * keutuhan; sudut += detail) {
        GLfloat XsebelumAtas = jari_jari_atas * cos((sudut) * M_PI / 180);
        GLfloat ZsebelumAtas = jari_jari_atas * sin((sudut) * M_PI / 180);
        GLfloat Xsesudah = jari_jari_bawah * cos((sudut + detail) * M_PI / 180);
        GLfloat Zsesudah = jari_jari_bawah * sin((sudut + detail) * M_PI / 180);
        GLfloat XsesudahAtas = jari_jari_atas * cos((sudut + detail) * M_PI / 180);
        GLfloat ZsesudahAtas = jari_jari_atas * sin((sudut + detail) * M_PI / 180);
        GLfloat vertices[][3] = {
                {Xsebelum + posX,     posY,          Zsebelum + posZ},
                {Xsesudah + posX,     posY,          Zsesudah + posZ},
                {XsesudahAtas + posX, posY + tinggi, ZsesudahAtas + posZ},
                {XsebelumAtas + posX, posY + tinggi, ZsebelumAtas + posZ}
        };

        glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[0], vertices[1], vertices[2]));
        for (int i = 0; i < 4; ++i) {
            glTexCoord2f(vertices[i][0] / texture_scale, vertices[i][1] / texture_scale);
            glVertex3fv(vertices[i]);
        }
        glEnd();
        Xsebelum = Xsesudah;
        Zsebelum = Zsesudah;
        jumlahLooping++;
    }
}
void tabung(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat jari_jari_bawah, GLfloat jari_jari_atas,
              GLfloat tinggi, GLfloat detail, GLfloat keutuhan, bool tutup_atas, bool tutup_bawah,
              GLfloat texture_scale) {
    if (tutup_atas)
        lingkaran(posX, posY + tinggi, posZ, jari_jari_atas, detail, keutuhan, texture_scale);

    pipa(posX, posY, posZ, jari_jari_bawah, jari_jari_atas, tinggi, detail, keutuhan, texture_scale);

    if (tutup_bawah)
        lingkaran(posX, posY, posZ, jari_jari_bawah, detail, keutuhan, texture_scale);

    if (keutuhan < 1) {
        GLfloat vertices[][3] = {
                {posX + jari_jari_bawah, posY,          posZ},
                {posX + (jari_jari_bawah * cos(360 * keutuhan * M_PI / 180)), posY, posZ + (jari_jari_bawah *sin(360 *keutuhan *M_PI / 180))},
                {posX + (jari_jari_atas * cos(360 * keutuhan * M_PI / 180)),  posY + tinggi,
                                                                                             posZ + (jari_jari_atas *
                                                                                                     sin(360 *
                                                                                                         keutuhan *
                                                                                                         M_PI / 180))},
                {posX + jari_jari_atas,                                       posY + tinggi, posZ}
        };
        glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[0], vertices[1], vertices[2]));
        for (int i = 0; i < 4; ++i) {
            glTexCoord2f(vertices[i][0] / texture_scale, vertices[i][1] / texture_scale);
            glVertex3fv(vertices[i]);
        }
        glEnd();
    }
}
void tulisan(){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex3f(0,1,0);
    glTexCoord2f(1,0);
    glVertex3f(1,1,0);
    glTexCoord2f(1,1);
    glVertex3f(1,2,0);
    glTexCoord2f(0,1);
    glVertex3f(0,2,0);
    glEnd();
    glPopMatrix();

}
void lampu(){
    glPushMatrix();
    glColor3f(1,1,1);
    tabung(3.0, 0.0, -6, 0.3, 0.2, 0.4, 6, 1, true, true, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3d(1,0,0);
    glTranslated(3.0,2.3,-6);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.3, 0.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, black);
    tabung(3.0, 0.0, -6, 0.07, 0.07, 2.0, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glRotated(90, -1.0, 0.0, 0.0);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(3.0,2.54,-6);
    glutSolidSphere(0.5,25,25);
    glPopMatrix();
 }

void jalan(){
    glPushMatrix();
    //glTranslatef(7.5, 0.0, -49.75);
    //glScalef(3.0, 0.1, 33.15);
    glBindTexture(GL_TEXTURE_2D, jalantxt);
	//cube(3);
	alaskubus(2.9, -0.3, 0.0, 9.0, 100, 0.5, 3);
	glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
}

void lingkarsumur (){
    glPushMatrix();
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    pillarMenara(0.0, 0.0, -5.0, 1, 1, 1,100, sumurtxt, 1, 0);
    glColor3f(0.4, 0.8, 0.8);
    pillarMenara(0.0, 1, -5.0, 0, 1, 1.5, 100, sumurtxt, 1, 0);
    pillarMenara(0.0, 0.0, -5.0, 1, 1.5, 1.5, 100, sumurtxt, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    glBindTexture(GL_TEXTURE_2D, air);
    lingkaran(0.0, 0.5, -5.0, 1, 6, 1, 1);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

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
    glTranslatef(0.0, 0.0, 1.0);


    for(int i =0; i<29; i++)
    {
        glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(verticessemak[0],verticessemak[1],verticessemak[2]));
        for (int j=0; j<3; j++)
        {
            // glTexCoord2f(verticessemak[i][j][0],verticessemak[i][j][1]);
            glVertex3fv(verticessemak[facessemak[i][j]]);
        }
        glEnd();
    }
    glPopMatrix();
}
void tanaman(float x, float y, float z, float derajat) {
 float vertices[][3] = {
  {-0.246384, 2.693530, 1.615931},
  {0.098775, -0.067124, 1.000000},
  {-1.000000, -0.067124, 1.000000},
  {-0.672412, 3.809398, -0.273997},
  {-0.712837, 2.879008, 0.502897},
  {-0.052556, 1.932876, 1.000000},
  {-0.713979, 1.932876, 1.000000},
  {-0.289925, 3.369208, 0.655194},
  {-0.732071, 2.227654, 1.615931},
  {-0.037175, 0.932876, 1.000000},
  {-0.770481, 2.408063, 2.277118},
  {-0.856990, 0.932876, 1.000000},
  {-0.114210, 1.568212, 0.485011},
  {-0.565919, 1.852364, 0.485010},
  {-0.117792, 1.419556, 1.486446},
  {-0.426033, 1.987123, -0.429155},
  {-0.937606, 1.419556, 1.486446},
  {-0.869725, 1.208880, 2.124065},
 };
 float normals[][3] = {
  {-0.000000, -0.000000, 1.000000},
  {-0.721400, 0.462100, 0.515800},
  {-0.263600, 0.298100, 0.917400},
  {-0.285500, 0.703000, -0.651400},
  {-0.673600, 0.702200, -0.230700},
  {0.119900, 0.536700, 0.835200},
  {0.521500, 0.829000, 0.202000},
  {0.000000, 0.706900, -0.707300},
  {-0.000000, 0.949500, 0.313700},
 };
 int faces[][4][3] = {
  {{10, NULL, 1}, {6, NULL, 1}, {7, NULL, 1}, {12, NULL, 1}, },
  {{5, NULL, 2}, {8, NULL, 2}, {4, NULL, 2}, },
  {{7, NULL, 3}, {6, NULL, 3}, {8, NULL, 3}, {5, NULL, 3}, },
  {{6, NULL, 4}, {7, NULL, 4}, {9, NULL, 4}, {1, NULL, 4}, },
  {{9, NULL, 5}, {11, NULL, 5}, {1, NULL, 5}, },
  {{2, NULL, 1}, {10, NULL, 1}, {12, NULL, 1}, {3, NULL, 1}, },
  {{12, NULL, 6}, {10, NULL, 6}, {13, NULL, 6}, {14, NULL, 6}, },
  {{14, NULL, 7}, {13, NULL, 7}, {16, NULL, 7}, },
  {{10, NULL, 8}, {12, NULL, 8}, {17, NULL, 8}, {15, NULL, 8}, },
  {{17, NULL, 9}, {18, NULL, 9}, {15, NULL, 9}, },
 };
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,green);
    glTranslatef(x, y, z);
    glRotatef(derajat,0,1,0);
    glScalef(20,20,20);
 for (int i = 0; i < (sizeof(faces))/ sizeof(faces[0]); ++i) {
  glBegin(GL_POLYGON);
  for (int j = 0; j < (sizeof(faces[0]))/ sizeof(faces[0][0]); ++j) {
   if (faces[i][j][0] != NULL) {
                glTexCoord2f(vertices[faces[i][j][0] - 1][0],vertices[faces[i][j][0] - 1][1]);
    glVertex3fv(vertices[faces[i][j][0] - 1]);
    if (faces[i][j][2] != NULL) {
     glNormal3fv(normals[faces[i][j][2] - 1]);
    }
   }
  }
  glEnd();
 }
 glPopMatrix();
}

void balok (){
glBegin(GL_POLYGON);

    glPushMatrix();

    GLfloat vertices[4][3]=
    {
        {-0.5,0.5,0},
        {0.5,0.5,0},
        {0.5,-0.5,0},
        {-0.5,-0.5,0}
    };

    GLfloat vertices2[4][3]=
    {
        {0.5,0.5,0},
        {0.5,0.5,-1},
        {0.5,-0.5,-1},
        {0.5,-0.5,0}
    };

    GLfloat vertices3[4][3]=
    {
        {-0.5,0.5,0},
        {-0.5,0.5,-1},
        {-0.5,-0.5,-1},
        {-0.5,-0.5,0}
    };

    //1 depan
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[0],vertices[1],vertices[2]));
        for(int x=0;x<4;x++){
                glTexCoord2f(vertices[x][0], vertices[x][1]);
            glVertex3fv(vertices[x]);
        }
    glEnd();
    //2 kanan
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices2[0],vertices2[1],vertices2[2]));
        for(int x=0;x<4;x++){
                glTexCoord2f(vertices[x][0], vertices[x][1]);
            glVertex3fv(vertices2[x]);
        }
    glEnd();
    //3 kiri
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices3[0],vertices3[1],vertices3[2]));
        for(int x=0;x<4;x++){
                glTexCoord2f(vertices[x][0], vertices[x][1]);
            glVertex3fv(vertices3[x]);
        }
    glEnd();

    GLfloat vertices4[4][3]=
    {
        {-0.5,0.5,-1},
        {0.5,0.5,-1},
        {0.5,-0.5,-1},
        {-0.5,-0.5,-1}
    };

    //4 belakang
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices4[0],vertices4[1],vertices4[2]));
        for(int x=0;x<4;x++){
                glTexCoord2f(vertices[x][0], vertices[x][1]);
            glVertex3fv(vertices4[x]);
        }
    glEnd();

    GLfloat vertices5[4][3]=
    {
        {-0.5,0.5,0},
        {0.5,0.5,0},
        {0.5,0.5,-1},
        {-0.5,0.5,-1}
    };

    //5 atas
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices5[0],vertices5[1],vertices5[2]));
        for(int x=0;x<4;x++){
                glTexCoord2f(vertices[x][0], vertices[x][1]);
            glVertex3fv(vertices5[x]);
        }
    glEnd();

    GLfloat vertices6[4][3]=
    {
        {-0.5,-0.5,0},
        {0.5,-0.5,0},
        {0.5,-0.5,-1},
        {-0.5,-0.5,-1}
    };

    //6 bawah
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices6[0],vertices6[1],vertices6[2]));
        for(int x=0;x<4;x++){
                glTexCoord2f(vertices[x][0], vertices[x][1]);
            glVertex3fv(vertices6[x]);
        }
    glEnd();
    glPopMatrix();

    glEnd();

}
void rumahKeranda(){
    //tembok kiri
    glPushMatrix();
    glTranslatef(1,1.5,-5.1);
    glTranslatef(85,0,-85);
    glScalef(0.25,3.1,8.9);
     glBindTexture(GL_TEXTURE_2D, tembok);
    cube(1,10);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    //tembok kanan
    glPushMatrix();
    glTranslatef(9,1.5,-5.1);
    glTranslatef(85,0,-85);
    glScalef(0.25,3.1,8.9);
     glBindTexture(GL_TEXTURE_2D, tembok);
    cube(1,10);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    //tembok belakang
    glPushMatrix();
    //setMaterialBrass();
    glTranslatef(5,1.5,-9.66);
    glTranslatef(85,0,-85);
    glRotatef(90,0,1,0);
    glScalef(0.25,3.1,8.25);
     glBindTexture(GL_TEXTURE_2D, tembok);
    cube(1,10);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //atap
    glPushMatrix();
    glTranslatef(85,0,-85);
     glBindTexture(GL_TEXTURE_2D, atap);
    atapRumahKeranda(1,0.5,0.2);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0.05,0);
    glTranslatef(85,0,-85);
     glBindTexture(GL_TEXTURE_2D, atap);
    atapRumahKeranda2(0.5,0.5,0.2);
     glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(85,0,-85);
    tebalAtapKeranda();
    glPopMatrix();

    //tali
    glPushMatrix();
    glTranslatef(85,0,-85);
    tabung(5, 3.5, -5, 0.03, 0.03, 1.5, 6, 1, true, true, 10);
    glPopMatrix();

    //vitingan
    glPushMatrix();
    glTranslatef(5,3.309,-5);
    glTranslatef(85,0,-85);
    glRotatef(-90,1,0,0);
    glutSolidCone(0.5,0.2,50,50);
    glPopMatrix();

    //lampunya
    glPushMatrix();
    setMaterialputih();
    glTranslatef(5,3.4,-5);
    glTranslatef(85,0,-85);
    glutSolidSphere(0.1,50,50);
    glPopMatrix();
}

void gerbangKiri(){
    //badan
    glPushMatrix();
    glTranslatef(42,2.5,-0.2);
    glScalef(2,3,2);
    glBindTexture(GL_TEXTURE_2D,gapurabawah);
    cube(1,10);
    glBindTexture(GL_TEXTURE_2D,-1);
    //balok();
    glPopMatrix();

    //gelang bawah
    glPushMatrix();
    glTranslatef(42,0.5,0);
    glScalef(2.5,1,2.5);
    glBindTexture(GL_TEXTURE_2D, gapuraatas);
    cube(1,10);
    glBindTexture(GL_TEXTURE_2D, -1);
    //balok();
    glPopMatrix();

    float ty=3.8, tz=0, sty=0.3, stz=-0.15;
    float sxz=2.5, selisihxz=0.3;

    for(int x=0;x<8;x++ ){
        glPushMatrix();
        glTranslatef(42,ty,tz);
        glScalef(sxz,0.5,sxz);
         glBindTexture(GL_TEXTURE_2D, gapuraatas);
        cube(1,10);
         glBindTexture(GL_TEXTURE_2D, -1);
        //balok();
        glPopMatrix();
        sxz-=selisihxz;

        ty+=sty;
        tz+=stz;
    }
}
void gerbangKanan(){
    //badan
    glPushMatrix();
    glTranslatef(58,2.5,-0.2);
    glScalef(2,3,2);
    glBindTexture(GL_TEXTURE_2D,gapurabawah);
    cube(1,10);
    glBindTexture(GL_TEXTURE_2D,-1);
    //balok();
    glPopMatrix();

    //gelang bawah
    glPushMatrix();
    glTranslatef(58,0.5,0);
    glScalef(2.5,1,2.5);
    glBindTexture(GL_TEXTURE_2D, gapuraatas);
    cube(1,10);
    glBindTexture(GL_TEXTURE_2D, -1);
    //balok();
    glPopMatrix();

    float ty=3.8, tz=0, sty=0.3, stz=-0.15;
    float sxz=2.5, selisihxz=0.3;

    for(int x=0;x<8;x++ ){
        glPushMatrix();
        glTranslatef(58,ty,tz);
        glScalef(sxz,0.5,sxz);
        glBindTexture(GL_TEXTURE_2D, gapuraatas);
        cube(1,10);
         glBindTexture(GL_TEXTURE_2D, -1);
        //balok();
        glPopMatrix();
        sxz-=selisihxz;

        ty+=sty;
        tz+=stz;
    }
}
void trapesium(){
 //glBegin(GL_POLYGON);
 glPushMatrix();
    //Sisi depan belakang
    GLfloat vertices[5][3]=
    {
        {-2.0, 0.0, -2.0},
        {2.0, 0.0, -2.0},
        {2.0, 4.0, -2.0},
        {1.0, 4.0, -2.0},
        {-2.0, 1.0, -2.0}
    };

    GLfloat vertices2[5][3]=
    {
        {-2.0, 0.0, 2.0},
        {2.0, 0.0, 2.0},
        {2.0, 4.0, 2.0},
        {1.0, 4.0, 2.0},
        {-2.0, 1.0, 2.0}
    };

    GLfloat vertices3[4][3]=
    {
        {1.0, 4.0, 2.0},
        {1.0, 4.0, -2.0},
        {-2.0, 1.0, -2.0},
        {-2.0, 1.0, 2.0}
    };

    GLfloat vertices4[4][3]=
    {
        {-2.0, 1.0, 2.0},
        {-2.0, 1.0, -2.0},
        {-2.0, 0.0, -2.0},
        {-2.0, 0.0, 2.0}
    };

    GLfloat vertices5[4][3]=
    {
        {-2.0, 0.0, -2.0},
        {-2.0, 0.0, 2.0},
        {2.0, 0.0, 2.0},
        {2.0, 0.0, -2.0}
    };

    GLfloat vertices6[4][3]=
    {
        {2.0, 0.0, 2.0},
        {2.0, 0.0, -2.0},
        {2.0, 4.0, -2.0},
        {2.0, 4.0, 2.0}
    };

    GLfloat vertices7[4][3]=
    {
        {2.0, 4.0, -2.0},
        {2.0, 4.0, 2.0},
        {1.0, 4.0, 2.0},
        {1.0, 4.0, -2.0}
    };

    //1 sisi kanan
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices[0],vertices[1],vertices[2]));
        for(int x=0;x<5;x++){
            glTexCoord2f(vertices[x][2], vertices[x][1]);
            glVertex3fv(vertices[x]);
        }
    glEnd();
    //2 sisi kiri
    glBegin(GL_POLYGON);
        glNormal3fv(calculate_normal(vertices2[0],vertices2[1],vertices2[2]));
        for(int x=0;x<5;x++){
            glTexCoord2f(vertices2[x][2], vertices2[x][1]);
            glVertex3fv(vertices2[x]);
        }
    glEnd();
    //3
    //Penutup samping
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(vertices3[0],vertices3[1],vertices3[2]));
        for(int x=0;x<4;x++){
            glTexCoord2f(vertices3[x][0], vertices3[x][1]);
            glVertex3fv(vertices3[x]);
        }
    glEnd();
    //4
    // Penutup kiri
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(vertices4[0],vertices4[1],vertices4[2]));
        for(int x=0;x<4;x++){
            glTexCoord2f(vertices4[x][0], vertices4[x][1]);
            glVertex3fv(vertices4[x]);
        }
    glEnd();
    //5
    //Penutup Bawah
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(vertices5[0],vertices5[1],vertices5[2]));
        for(int x=0;x<4;x++){
            glTexCoord2f(vertices5[x][0], vertices5[x][1]);
            glVertex3fv(vertices5[x]);
        }
    glEnd();
    //6
    //Penutup Kanan
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(vertices6[0],vertices6[1],vertices6[2]));
        for(int x=0;x<4;x++){
            glTexCoord2f(vertices6[x][0], vertices6[x][1]);
            glVertex3fv(vertices6[x]);
        }
    glEnd();
    //7
    //Penutup Atas
    glBegin(GL_QUADS);
        glNormal3fv(calculate_normal(vertices7[0],vertices7[1],vertices7[2]));
        for(int x=0;x<4;x++){
            glTexCoord2f(vertices7[x][0], vertices7[x][1]);
            glVertex3fv(vertices7[x]);
        }
    glEnd();
    glPopMatrix();
    //glEnd();
}
void kuburan(){

    glPushMatrix();
    //glTranslatef(-0.37, 0.2, 0.0);
    //glScalef(3.8, 0.5, 1.2);
    glBindTexture(GL_TEXTURE_2D, kuburantxt);
    alaskubus(-0.37, 0.2, 0.0, 3.5, 1.2, 0.5, 1);
    //cube(1);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0.7, -0.6);
    glScalef(0.13,0.15,0.3);
    glRotatef(180, 0.0, 1.0, 0.0 );
    glBindTexture(GL_TEXTURE_2D, kuburantxt);
    trapesium();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

}

void kuburanrotate()
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(5, -0.2, -15);
    glRotatef(90, 0.0, 1.0, 0.0);
    kuburan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.9, 0.3, -15.5);
    glRotatef(180, 0.0, 1.0, 0.0);
    glRotatef(-41, 1.0, 0.0, 0.0);
    glScalef(1, 0.5, 1.0);
    glBindTexture(GL_TEXTURE_2D,nisan);
    tulisan();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    glPopMatrix();
}

void timba ()
{
    //tabung(10.0, 1.2, -8.6, 0.3, 0.5, 0.7, 6, 1, false, true);
    glBindTexture(GL_TEXTURE_2D, timbatxt);
    tabung(5.0, 0, -5, 0.6, 1, 1.5, 6, 1, false, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);

    glPushMatrix();
    //glColor3f(1.0, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    tabung(1.45, -4.1, -5, 0.1, 0.1, 0.2, 6, 1, false, true, 10);
    tabung(1.45, -6.1, -5, 0.1, 0.1, 0.2, 6, 1, false, true, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 2.5, -5);
    glScalef(2.1, 0.1 ,0.1);
    cube(1,10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0, 0.0, 1.0 );
    glTranslatef(2, -4.01, -5);
    glScalef(1, 0.1 ,0.1);
    cube(1,10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0, 0.0, 1.0 );
    glTranslatef(2, -6.01, -5);
    glScalef(1, 0.1 ,0.1);
    cube(1,10);
    glPopMatrix();
}

void sumur()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, sumurtxt);
    lingkarsumur();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    glPushMatrix();

    glRotatef(90, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(90, 0.0, 0.0, 1.0);
    pillarMenara(-4.9, -1.9, -4.1 , 4.0, 0.06, 0.06, 10,rust,1, 90);

    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8, 2.0, -4.9);
    glScalef(0.6, 4.5 , 0.6);
    glBindTexture(GL_TEXTURE_2D, kuburantxt);
    cube(1,10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, 2.0, -4.9);
    glScalef(0.6, 4.5 , 0.6);
    glBindTexture(GL_TEXTURE_2D, kuburantxt);
    cube(1,10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 1.01, -1.8);
    glScalef(0.4,0.4,0.4);
    timba();
    glPopMatrix();

}
void alas(){
    glPushMatrix();
    //glTranslatef(50,-0.165,-50);
    //glScalef(100,0.335,100);
    glBindTexture(GL_TEXTURE_2D, tanah);
    alaskubus(-20, -0.4,20, 140, 140, 0.4, 5);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
}
void keranda(){
    //papan
    glPushMatrix();
    glTranslatef(7,0.96,-2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glScalef(1.5,0.07,3.5);
    glBindTexture(GL_TEXTURE_2D, silver);
    balok();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //papan bawah
    glPushMatrix();
    glTranslatef(7,0.88,-2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glScalef(1.4,0.1,3.5);
    glBindTexture(GL_TEXTURE_2D, silver);
    balok();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    //pegangan kiri
    glPushMatrix();
    glTranslatef(1.25,-4.44,-6.2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90,1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, silver);
    tabung(5, 0.0, -5.4 , 0.05, 0.05, 5, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //pegangan kanan
    glPushMatrix();
    glTranslatef(2.75,-4.44,-6.2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90,1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, silver);
    tabung(5, 0.0, -5.4 , 0.05, 0.05, 5, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //kaki kanan belakang
    glPushMatrix();
    glTranslatef(0,0.22,0);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glBindTexture(GL_TEXTURE_2D, silver);
    tabung(7.7, 0.0, -5.4 , 0.03, 0.03, 0.7, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glRotated(90, -1.0, 0.0, 0.0);
    glPopMatrix();
    //kaki kiri belakang
    glPushMatrix();
    glTranslatef(0,0.22,0);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glBindTexture(GL_TEXTURE_2D, silver);
    tabung(6.3, 0.0, -5.4 , 0.03, 0.03, 0.7, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glRotated(90, -1.0, 0.0, 0.0);
    glPopMatrix();
    //kaki kanan depan
    glPushMatrix();
    glTranslatef(0,0.22,0);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glBindTexture(GL_TEXTURE_2D, silver);
    tabung(7.7, 0.0, -2.1 , 0.03, 0.03, 0.7, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glRotated(90, -1.0, 0.0, 0.0);
    glPopMatrix();
    //kaki kiri depan
    glPushMatrix();
    glTranslatef(0,0.22,0);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glBindTexture(GL_TEXTURE_2D, silver);
    tabung(6.3, 0.0, -2.1 , 0.03, 0.03, 0.7, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glRotated(90, -1.0, 0.0, 0.0);
    glPopMatrix();
    //roda depan kiri
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(6.3,0.11,-2.1);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, black);
	glutSolidTorus(0.05,0.07,10,110);
	glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //roda depan kanan
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(7.7,0.11,-2.1);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, black);
	glutSolidTorus(0.05,0.07,10,110);
	glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //roda belakang kanan
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(7.7,0.11,-5.4);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, black);
	glutSolidTorus(0.05,0.07,10,110);
	glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //roda belakang kiri
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(6.3,0.11,-5.4);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, black);
	glutSolidTorus(0.05,0.07,10,110);
	glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //ujung depan kiri
    glPushMatrix();
    //setMaterialBrass();
    glTranslatef(6.25,0.955,-1.2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
	glutSolidTorus(0.06,0.01,10,110);
    glPopMatrix();
    //ujung belakang kiri
    glPushMatrix();
//    setMaterialBrass();
    glTranslatef(6.25,0.955,-6.2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
	glutSolidTorus(0.06,0.01,10,110);
    glPopMatrix();
    //ujung depan kanan
    glPushMatrix();
    //setMaterialBrass();
    glTranslatef(7.75,0.955,-1.2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
	glutSolidTorus(0.06,0.01,10,110);
    glPopMatrix();
    //ujung belakang kanan
    glPushMatrix();
    //setMaterialBrass();
    glTranslatef(7.75,0.955,-6.2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
	glutSolidTorus(0.06,0.01,10,110);
    glPopMatrix();

    //kotak
    glPushMatrix();
    //setMaterialijo();
    glTranslatef(7,1.17,-2);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glScalef(1.14,0.47,3.489);
    glBindTexture(GL_TEXTURE_2D, backijo);
    balok();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();

    //lengkungan
    glPushMatrix();
    glTranslatef(2,-4.2,-5.485);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90,1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, backijo);
    tabung(5, 0.0, -5.6 , 0.57, 0.57, 3.479, 6, 1, true, true, 10);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //tulisan kiri
    glPushMatrix();
    glTranslatef(6.429,0.4,-5.465);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(-90,0,1,0);
    glScalef(3.463,0.5,1);
    glBindTexture(GL_TEXTURE_2D, innalillahi);
    tulisan();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
    //tulisan kanan
    glPushMatrix();
    glTranslatef(7.575,0.4,-2.02);
    glTranslatef(85,0,-85);
    glTranslatef(0.0, 0.0, sin(theta*PI/180.0)*2.0);
    glRotatef(90,0,1,0);
    glScalef(3.463,0.5,1);
    glBindTexture(GL_TEXTURE_2D, innalillahi);
    tulisan();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
}
void pocong(){
    //wajah
    if(theta2>180){
        theta2=0;
    }
    y=sin(theta2*PI/180.0)*0.7;
    //cout<<"theta= "<<theta2<<" dan y= "<<y<<endl;

    glPushMatrix();
    setMaterialhitam();
    glTranslatef(0,2.3,0.01);
    glTranslatef(0.0, y, 0.0);
    glScalef(1,1.1,1);
    glutSolidSphere(0.3459,50,50);
    glPopMatrix();
    //mata kiri
    glPushMatrix();
    setMaterialmerah();
    glTranslatef(0.1,2.35,0.3);
    glTranslatef(0.0, y, 0.0);
    glScalef(1,1,1);
    glutSolidSphere(0.055,50,50);
    glPopMatrix();
    //mata kanan
    glPushMatrix();
    setMaterialmerah();
    glTranslatef(-0.1,2.35,0.3);
    glTranslatef(0.0, y, 0.0);
    glScalef(1,1,1);
    glutSolidSphere(0.055,50,50);
    glPopMatrix();
    //kepala
    glPushMatrix();
    setMaterialputih();
    glTranslatef(0,2.3,0);
    glTranslatef(0.0, y, 0.0);
    glScalef(1,1.1,1);
    glutSolidSphere(0.35,50,50);
    glPopMatrix();
    //kuncup
    glPushMatrix();
    setMaterialputih();
    glTranslatef(0,2.96,0);
    glTranslatef(0.0, y, 0.0);
    glRotatef(90,1,0,0);
    glutSolidCone(0.2,0.3,7,7);
    glPopMatrix();
    //badan
    glPushMatrix();
    setMaterialputih();
    glTranslatef(0,1,0);
    glTranslatef(0.0, y, 0.0);
    glScalef(0.85,2,1);
    glutSolidSphere(0.5,50,50);
    glPopMatrix();
}

void batang ()
{
    //batang
    glBindTexture(GL_TEXTURE_2D, kayu);
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    glPushMatrix();
    glColor3ub(104, 70, 14);
    glRotatef(270, 1, 0,0);
    gluCylinder(pObj, 4, 0.7, 30, 25, 25);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, kayu);
}

void ranting()
{

    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    glPushMatrix();
    glColor3ub(104, 70, 14);
    glTranslatef(0, 27,0);
    glRotatef(330, 1, 0,0);
    glBindTexture(GL_TEXTURE_2D, kayu);
    gluCylinder(pObj, 0.6, 0.1, 15, 25, 25);
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();


    //daun
    glPushMatrix();
    glColor3ub(18, 118, 13);
    glScaled(5, 5,5);
    glTranslatef(0, 7, 3);
    glBindTexture(GL_TEXTURE_2D, daun);
    glutSolidDodecahedron();
    glBindTexture(GL_TEXTURE_2D, -1);
    glPopMatrix();
}

void Pohon ()
{
    glPushMatrix();
    glTranslatef(-160, 0, -60);
    glRotatef(90, 0, 1,0);
    batang();
    ranting();


    glPushMatrix();
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(0,25,25);
    glRotatef(250, 1, 0,0);
    ranting();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.8, 1.8, 1.8);
    glTranslatef(0,-6,21.5);
    glRotatef(-55, 1, 0,0);
    ranting();
    glPopMatrix();
    glPopMatrix();


}

void pss()
{
    //sisi kiri
    float z=15.5;
    for(int a=0;a<19;a++){
        z-=5;
        float j=34;
        for (int b = 0; b<13; b++)
        {
            glPushMatrix();
            glTranslatef(j,0,z);
            kuburanrotate();
            glPopMatrix();
            j-=3;
        }

    }

    //sisi kanan
    float k=94;
    for(int c=0;c<13;c++){
        k-=3;
        float l=10;
        for (int d= 0; d<15; d++)
        {
            glPushMatrix();
            glTranslatef(k,0,l);
            kuburanrotate();
            glPopMatrix();
            l-=5;
        }

    }

}

void psslampu()
{
    //lampu kiri
    float z=-15;
    for(int a=0;a<3;a++){
        glPushMatrix();
        glTranslatef(42, 0, z);
        lampu();
        glPopMatrix();
        z-=25;
    }

    //lampu kanan
    float k=-15;
    for(int b=0;b<3;b++){
        glPushMatrix();
        glTranslatef(52, 0, k);
        lampu();
        glPopMatrix();
        k-=25;
    }
}

void rerumputan(){
    for(int y=0;y<500;y++){
    glPushMatrix();
    glTranslatef(px[y],0,pz[y]);
    glScalef(0.005,0.005,0.005);
    tanaman(0,0,0,50);
    glPopMatrix();
    }
}
void rerumputan2(){
    for(int y=0;y<500;y++){
    glPushMatrix();
    glTranslatef(px2[y],0,pz2[y]);
    glScalef(0.005,0.005,0.005);
    tanaman(0,0,0,50);
    glPopMatrix();
    }
}

void randomPosisiRumput(){
    for(int x=0;x<500;x++){
    px[x]=rand()%45+1;
    pz[x]=(rand()%100)-100;
    }
}
void randomPosisiRumput2(){
    for(int x=0;x<500;x++){
    px2[x]=rand()%45+55;
    pz2[x]=(rand()%100)-100;
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->Update();

    setLighting();
    //posisiLampu(cahayax,cahayay,cahayaz);

    glPushMatrix();
    psslampu();
    glPopMatrix();

    glPushMatrix();
    rerumputan();
    rerumputan2();
    glPopMatrix();



    glPushMatrix();
    alas();
    glPopMatrix();

    glPushMatrix();
    keranda();
    glPopMatrix();



    //setmaterialPerl();


    glPushMatrix();
    alas();
    glPopMatrix();

    //garis2frontback();
    //garis2leftright();
    //posisiLampu(5,5,-5);

    glPushMatrix();
    //setMaterialTin();
    rumahKeranda();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    pss();
    //kuburanrotate();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,0,-0.5);
    tuguPojok2();
    glPopMatrix();

    glPushMatrix();
    pagar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(42.5,0,0);
    //setmaterialPerl();
    jalan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 0, 5);
    //lampu();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(80, 0, -85);
    sumur();
    glPopMatrix();

    //posisi pohon
    glPushMatrix();
    glTranslatef(90, 0, -83);
    glScalef(0.1,0.1,0.1);
    Pohon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(78, 0, -83);
    glScalef(0.1,0.1,0.1);
    Pohon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(84, 0, -83);
    glScalef(0.1,0.1,0.1);
    Pohon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(44, 0, -83);
    glScalef(0.1,0.1,0.1);
    Pohon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(24, 0, -27.5);
    glScalef(0.1,0.1,0.1);
    Pohon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(73, 0, -45);
    glScalef(0.1,0.1,0.1);
    Pohon();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0.0, 1.0, 0.0);
    glTranslatef(-43.50,0,-41.75);
    gerbangKiri();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(-56.55,0,58.25);
    gerbangKanan();
    glPopMatrix();



    if((camera->pos.x>87) && (camera->pos.z < -87)){
    glPushMatrix();
    glTranslatef(90,0,-87);
    glRotatef(180,0,1,0);
    pocong();
    glPopMatrix();
    }

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
    camera = new Camera( 50.0, 2.7, 20.0, 50.0, 2.7, -50.0, 0.0, 1.0, 0.0 );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glClearColor(0.55, 0.8, 1.0, 1.0);

    randomPosisiRumput();
    randomPosisiRumput2();
    //texture
	glEnable(GL_TEXTURE_2D);

	tanah = loadBmpFile("tanah.bmp");
	//bungatxt = loadBmpFile("hijau.bmp");
	jalantxt = loadBmpFile("jalan.bmp");
	sumurtxt = loadBmpFile("sumur.bmp");
	kuburantxt = loadBmpFile("marmer.bmp");
	pohontxt = loadBmpFile("wooden.bmp");
	tugutxt = loadBmpFile("brick.bmp");
	tembok = loadBmpFile("tembok.bmp");
	cagaksumur = loadBmpFile("metaltex.bmp");
	atap = loadBmpFile("genteng.bmp");
	timbatxt = loadBmpFile("wood.bmp");
	backijo = loadBmpFile("ijo_text.bmp");
	innalillahi = loadBmpFile("innalillahi_text.bmp");
	stone = loadBmpFile("stone.bmp");
	gapurabawah = loadBmpFile("gapurabawah.bmp");
	gapuraatas = loadBmpFile("gapuraatas.bmp");
	nisan = loadBmpFile("nisan.bmp");
	kayu = loadBmpFile("pohon3.bmp");
	daun = loadBmpFile("merah.bmp");
	silver = loadBmpFile("silver.bmp");
	air = loadBmpFile("air.bmp");
	black = loadBmpFile("black.bmp");
	rust = loadBmpFile("rust.bmp");
	green = loadBmpFile("green.bmp");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutSpecialFunc(specialkeys);
    glutIdleFunc(idleFunc);
    glutMainLoop();

    delete camera;
    return 0;
}
