//
// Created by kunal on 3/3/18.
//
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "constants.h"
#include "functionalities.h"
#include "shapes.h"

using namespace std;


bool poleCollided[3];
bool stopEverything = false;
unsigned int Tries, Goals;
vector<float> currentTextColor = {1, 1, 1, 1};

bool isDay;
bool isPause = false;

void showScore();

void updatePos(PhysicalState &p, double t) {
    p.timePassed += t;

    {//Collision with Pole0
        if (p.positionCurrent.z < POLE_HEIGHT && p.positionCurrent.z > 0.0) {
            axes t = {-POLE_LENGTH / 2, GOAL_POST_Y, p.positionCurrent.z};
            if ((distanceBW(t, p.positionCurrent) <= BALL_RADIUS + POLE_RADIUS) && !poleCollided[0]) {
                poleCollided[0] = true;
                double alpha, beta, theta;
                beta = atan(p.velocityCurrent.y / p.velocityCurrent.x);
                axes vec;
                for (int i = 0; i < 3; ++i) {
                    vec[i] = t[i] - p.positionCurrent[i];
                }
                alpha = atan(vec.y / vec.x);
                theta = PI / 2.0 - beta + 2 * alpha;
                double v = p.velocityCurrent.x * p.velocityCurrent.x + p.velocityCurrent.y * p.velocityCurrent.y;
                v = sqrt(v);
                p.velocityCurrent.y = -v * cos(theta) * p.elasticity;
                p.velocityCurrent.x = v * sin(theta) * p.elasticity;
            } else if ((distanceBW(t, p.positionCurrent) <= BALL_RADIUS + POLE_RADIUS) && poleCollided[0]) {
                poleCollided[0] = false;
            }
        }
    }
    {//Collision with Pole2
        if (p.positionCurrent.z < POLE_HEIGHT && p.positionCurrent.z > 0.0) {
            axes t = {POLE_LENGTH / 2, GOAL_POST_Y, p.positionCurrent.z};
            if ((distanceBW(t, p.positionCurrent) <= BALL_RADIUS + POLE_RADIUS) && !poleCollided[2]) {
                poleCollided[2] = true;
                double alpha, beta, theta;
                beta = atan(p.velocityCurrent.y / p.velocityCurrent.x);
                axes vec;
                for (int i = 0; i < 3; ++i) {
                    vec[i] = t[i] - p.positionCurrent[i];
                }
                alpha = atan(vec.y / vec.x);
                theta = PI / 2.0 - beta + 2 * alpha;
                double v = p.velocityCurrent.x * p.velocityCurrent.x + p.velocityCurrent.y * p.velocityCurrent.y;
                v = sqrt(v);
                p.velocityCurrent.y = v * cos(theta) * p.elasticity;
                p.velocityCurrent.x = -v * sin(theta) * p.elasticity;

            } else if ((distanceBW(t, p.positionCurrent) <= BALL_RADIUS + POLE_RADIUS) && poleCollided[2]) {
                poleCollided[2] = false;
            }
        }
    }
    {//Collision with Pole1
        if (p.positionCurrent.x < POLE_LENGTH / 2 + POLE_RADIUS &&
            p.positionCurrent.x > -POLE_LENGTH / 2 - POLE_RADIUS) {
            axes t = {p.positionCurrent.x, GOAL_POST_Y, POLE_RADIUS + POLE_HEIGHT};
            if ((distanceBW(t, p.positionCurrent) <= BALL_RADIUS + POLE_RADIUS) && !poleCollided[1]) {
                poleCollided[1] = true;
                double alpha, beta, theta;
                beta = atan(p.velocityCurrent.y / p.velocityCurrent.z);
                axes vec;
                for (int i = 0; i < 3; ++i) {
                    vec[i] = t[i] - p.positionCurrent[i];
                }
                alpha = atan(vec.y / vec.z);
                theta = PI / 2.0 - beta + 2 * alpha;
                double v = p.velocityCurrent.z * p.velocityCurrent.z + p.velocityCurrent.y * p.velocityCurrent.y;
                v = sqrt(v);
                p.velocityCurrent.y = v * cos(theta) * p.elasticity;
                p.velocityCurrent.z = -v * sin(theta) * p.elasticity;
            } else if ((distanceBW(t, p.positionCurrent) <= BALL_RADIUS + POLE_RADIUS) && poleCollided[1]) {
                poleCollided[1] = false;
            }
        }
    }

    {//Collision with Defender
        if (p.positionCurrent.x < defender.state.positionCurrent.x + defender.width / 2.0 &&
            p.positionCurrent.x > defender.state.positionCurrent.x - defender.width / 2.0 &&
            p.positionCurrent.z < defender.height &&
            p.positionCurrent.y + BALL_RADIUS / 2.0 + DEFENDER_THICKNESS / 2.0 >= GOAL_POST_Y && !determineSphere) {
            p.velocityCurrent.y *= -p.elasticity;
        }
    }

    {   // Gravity and ground bouncing effects
        for (int i = 0; i < 3; ++i) {
            p.positionCurrent[i] =
                    p.velocityCurrent[i] * t + 0.5 * p.accelerationCurrent[i] * t * t + p.positionCurrent[i];
            p.velocityCurrent[i] = p.velocityCurrent[i] + p.accelerationCurrent[i] * t;
        }
        if (p.positionCurrent[2] <= 0) {
            p.positionCurrent[2] = 0;
            p.velocityCurrent[2] = -p.velocityCurrent[2];
            for (int i = 0; i < 3; ++i) {
                p.velocityCurrent[i] = p.elasticity * p.velocityCurrent[i];
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (fabs(p.velocityCurrent[i]) <= THRESHOLD_ZERO) {
                p.velocityCurrent[i] = 0;
            }
        }
        if (fabs(p.positionCurrent[2]) <= THRESHOLD_ZERO) {
            p.positionCurrent[2] = 0;
        }
    }
    if (p.positionCurrent.y + BALL_RADIUS > 20.0 || p.positionCurrent.y - BALL_RADIUS < -20.0) {
        p.velocityCurrent.y = -p.velocityCurrent.y;
    }
    if (p.positionCurrent.x + BALL_RADIUS > 20.0 || p.positionCurrent.x - BALL_RADIUS < -20.0) {
        p.velocityCurrent.x = -p.velocityCurrent.x;
    }
}


void renderBitmapString(
        float x,
        float y,
        float z,
        void *font,
        char *string) {

    char *c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void updatePosCallBack(int _) {
    if (currentMode != SHOOTING && currentlyWaiting) {
        currentMode = SHOOTING;
        currentlyWaiting = false;
    }
    float fps = 60;
    if (currentMode == SHOOTING) {
        updatePos(sphere, 1.0 / fps);
        glutTimerFunc(100 / fps, updatePosCallBack, 0);
    }
}

axes cameraPos;
axes tempCameraPos;

// The pause menu changes the cameraPos coordinates. 
// To ensure we go back to where we were present initially, we use tempCameraPos

void drawHockeyStick(float innerRadius, float outerRadius, int numSides) {
    float x , y;
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= numSides; ++i) {
        float angle = -i *  PI / numSides;
        x = cos(angle);
        y = sin(angle);

        glNormal3f(x, y, 0);
        glVertex3f(round(innerRadius*x)/400, round(0.0), round(innerRadius*y)/400);
        glVertex3f(round(outerRadius*x)/400, round(0.0), round(outerRadius*y)/400);
    }

    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-round(innerRadius*x)/400, round(0.0), round(innerRadius*y)/400);
    glVertex3f(-round(innerRadius*x)/400, round(0.0), round(innerRadius*y + 500)/400);
    // glEnd();

    // glBegin(GL_QUAD_STRIP);
    glVertex3f(-round(outerRadius*x)/400, round(0.0), round(outerRadius*y)/400);
    glVertex3f(-round(outerRadius*x)/400, round(0.0), round(outerRadius*y + 500)/400);
    glEnd();
}

//Stadium
int south = 1,west = 2,east = 3;
void draw_seg1() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.5, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg2() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.5, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg3() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.5, 2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg4() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg5() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg6() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg7() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, -2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg8() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.5, -2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg9() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.5f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg10() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg11() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg12() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg13() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75f, 0.0f, 0.0f);
	glRotatef(-90.0f, 1.5f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg14() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(145.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_seg15() {
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}
}

void draw_seg16() {
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.5f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder);
}

void draw_disk()//creates seating for stadium as well as field
{
	GLUquadricObj *myDisk;
	myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_FILL);
	glPushMatrix();
	// glTranslatef(0.0f,3.0f,0.0f);
	// glTranslatef(0.0f,0.0f,0.0f);
	// glTranslatef(0.0f,5.0f,0.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-6.0f);
	gluDisk(myDisk, 33 ,34, 4, 1);
	glPopMatrix();
	gluDisk(myDisk, 33 ,34, 4, 1);
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-5.0f);
	gluDisk(myDisk, 32 ,33, 4, 1);
	glPopMatrix();
	gluDisk(myDisk, 32 ,33, 4, 1);
	glColor3f(0.4f, 0.4f, 0.4f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-4.0f);
	gluDisk(myDisk, 31 ,32, 4, 1);
	glPopMatrix();
	gluDisk(myDisk, 31 ,32, 4, 1);
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-3.0f);
	gluDisk(myDisk, 30 ,31, 4, 1);
	glPopMatrix();
	gluDisk(myDisk, 30 ,31, 4, 1);
	glColor3f(0.6f, 0.6f, 0.6f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-2.0f);
	gluDisk(myDisk, 28.3, 30, 4, 1);
	glPopMatrix();
	// glColor3f(0.1f, 1.0f, 0.1f);
	// gluDisk(myDisk, 0 ,8, 6, 1);//field
	// glColor3f(0.2f, 0.2f, 0.2f);
  	// ground.draw();
	gluDeleteQuadric(myDisk);
	glPopMatrix();

}

void draw_cylinder()//creates stadium
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glPushMatrix();
	// glTranslatef(0.0f,3.0f,0.0f);
	// glTranslatef(0.0f,0.0f,0.0f);
	// glTranslatef(0.0f,5.0f, 0.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	gluCylinder(myCylinder, 34, 34, 7, 4, 1);
	glColor3f(0.3f, 0.3f, 0.3f);
	gluCylinder(myCylinder, 33, 33, 6, 4, 1);
	glColor3f(0.4f, 0.4f, 0.4f);
	gluCylinder(myCylinder, 32, 32, 5, 4, 1);
	glColor3f(0.5f, 0.5f, 0.5f);
	gluCylinder(myCylinder, 31, 31, 4, 4, 1);
	glColor3f(0.6f, 0.6f, 0.6f);
	gluCylinder(myCylinder, 30, 30, 3, 4, 1);
  glColor3f(0.7f, 0.7f, 0.7f);
  gluCylinder(myCylinder, 28.3, 28.3, 2, 4, 1);
	gluDeleteQuadric(myCylinder);
	glPopMatrix();

}



void draw_signs()//creates signs
{
	GLUquadricObj *myDisk;
	myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_FILL);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(30.0f,1.0f,1.0f,0.0f);
	glTranslatef(-1,2,-6);
	gluDisk(myDisk, 0 ,4, 4, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-30.0f,1.0f,1.0f,0.0f);
	glTranslatef(1.5,-1,-7);
	gluDisk(myDisk, 0 ,4, 4, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f,1.0f,1.0f,0.0f);
	glTranslatef(4,-3,-10);
	gluDisk(myDisk, 0 ,4, 4, 1);
	glPopMatrix();
}


void updatescreen()//changes the sign writing
{

	if (south == 1) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,10,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg9();draw_seg11();draw_seg16();//R
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,10,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,10,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(29,10,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,3,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg10();draw_seg12();//T
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,3,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg7();draw_seg8();
		draw_seg10();draw_seg12();//I
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,3,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg12();//D
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(29,3,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
	}
	if(south == 2) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,10,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg6();draw_seg7();draw_seg8();draw_seg11();//G
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(27,10,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,3,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg11();draw_seg12();//B
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(24,3,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(28,3,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(32,3,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();

	}
	if(south == 3) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,10,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,10,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();
		draw_seg6();draw_seg15();draw_seg16();//W
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,10,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(29,10,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg9();
		draw_seg11();draw_seg12();//Y
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,3,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,3,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
	}
	if (west == 1) {

		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg9();draw_seg11();draw_seg16();//R
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,30);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg9();draw_seg11();//F
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,30);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg10();draw_seg12();//T
		glPopMatrix();

	}
	if(west == 2) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,20);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//H
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,28);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,32);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg3();draw_seg4();draw_seg5();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//2
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,28);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//4
		glPopMatrix();
	}
	if(west == 3) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,20);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();
		draw_seg6();draw_seg15();draw_seg16();//W
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,28);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,32);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg9();
		draw_seg11();draw_seg12();//Y
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,28);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
	}
	if (east == 1) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,10,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg9();draw_seg11();draw_seg16();//R
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,10,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,10,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-18,10,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,4,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg10();draw_seg12();//T
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,4,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg7();draw_seg8();
		draw_seg10();draw_seg12();//I
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,4,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg12();//D
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-17.5,4,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
	}
	if(east == 2) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,10,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//H
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,10,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,10,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-18,10,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,5,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,5,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//4
		glPopMatrix();
	}
	if(east == 3) {
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,10,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,10,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();
		draw_seg6();draw_seg15();draw_seg16();//W
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,10,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-18,10,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg9();
		draw_seg11();draw_seg12();//Y
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,5,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,5,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
	}

}


axes lookDist = {0, 0, 20};

void draw() {
    glLoadIdentity(); //Reset the drawing perspective
    // if(currentMode == PAUSE) {
    //     // NOTE: This code currently doesn't do anything! Just saying in case someone checks this in the future.
    //     // gluLookAt(lookDist[0], lookDist[1], lookDist[2], 0, 0, 0, 0, 0, 1);
    //     gluLookAt(0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    //     glBegin(GL_POLYGON);
    //     glVertex3f(1, 1, 0);
    //     glVertex3f(1, -1, 0);
    //     glVertex3f(-1, -1, 0);
    //     glVertex3f(-1, 1, 0);
    //     glEnd();
    //     // cameraPosition({0, 0, 5}, sphereCamera.distance, sphereCamera.zAngle, sphereCamera.xAngle);
    // }
    // else {
        cameraPosition(cameraPos, sphereCamera.distance, sphereCamera.zAngle, sphereCamera.xAngle);
    // }
    if (firstTime) {
        glutWarpPointer(WIDTH / 2, HEIGHT);
        firstTime = false;
    }

    // LIGHT0: located behind camera, directed slantly towards the ball
    //         parallel ray light source

    GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 0.7f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {0.0f, -100.0f, 100.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    // LIGHT1: adds a yellowish tinge to the background
    //         ambient light source

    GLfloat lightColor1[] = {0.3f, 0.3f, 0.1f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, -1.0f, -1.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor1);

    // LIGHT2: positioned behind goalpost in the direction of ball
    //         parallel ray light source

    GLfloat lightColor2[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos2[] = {0.0f, 100.0f, 0.10f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

    // LIGHT3: intended to be spotlight (in night mode) from left front corner
    //         parallel ray light source

    // cout << ground.corners[0][0] << endl;
    GLfloat spotlightl_pos[] = {(float)ground.corners[1][0], (float)ground.corners[1][1], (float)ground.corners[1][2]+30, 1.0f};
    GLfloat spotlightl_color[] = {1.0f, 1.0f, 1.0f, 0.7f}; //Color (0.5, 0.5, 0.5)
    glLightfv(GL_LIGHT3, GL_POSITION, spotlightl_pos);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, spotlightl_color);

    GLfloat spotlightr_pos[] = {(float)ground.corners[2][0], (float)ground.corners[2][1], (float)ground.corners[2][2]+30, 1.0f};
    GLfloat spotlightr_color[] = {1.0f, 1.0f, 1.0f, 0.7f}; //Color (0.5, 0.5, 0.5)
    glLightfv(GL_LIGHT4, GL_POSITION, spotlightr_pos);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, spotlightr_color);

    if(isDay) // if it is day then set background color to blue
        glClearColor(137 / 255.0, 206 / 255.0, 255 / 255.0, 0);
    else // if it is night then set background color to black
    // (sorta black, it's not completely pitch black, just a very dark shade of grey actually)
    // (cuz we never get pitch black skies anyways. (sigh) Pollution ;-;)
        glClearColor(13 / 255.0, 13 / 255.0, 13 / 255.0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective


//    glColor3f(1, 0, 0);
//    glBegin(GL_LINES);
//    glVertex3f(0, 0, 0);
//    glVertex3f(5, 0, 0);
//    glColor3f(0, 1, 0);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 5, 0);
//    glColor3f(0, 0, 1);
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 0, 5);
//    glEnd();


// drawing stadium

  	draw_disk();
  	draw_cylinder();
  	draw_signs();
    updatescreen();
  	glFlush();
  	// glutSwapBuffers();



//hockey stick drawing
    glPushMatrix();
    // int x1 = sphere.positionCurrent.x, y1 = sphere.positionCurrent.y - 0.2, z1 = sphere.positionCurrent.z + 0.2;
    glColor3f(1.0, 0.0, 1.0);
    // glTranslatef(x1, y1, z1);
    glTranslatef(0, 0 - 0.2, 0 + 0.2);
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    drawHockeyStick(70.0, 100.0, 50);
    glPopMatrix();



    // draw the ball
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(sphere.positionCurrent.x, sphere.positionCurrent.y, sphere.positionCurrent.z);
    glutSolidSphere(BALL_RADIUS, 20, 20);
    glPopMatrix();

//    glTranslatef(0,0,0);
//        glScalef(2.0,2.0,1.0);

    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);
    glColor4f(1.0, 1.0, 1.0, 0.7);
    drawGoalPost();

    glPopAttrib();
    glPopMatrix();

    if (currentMode == POWERING || currentMode == AIMING) {
        aimArrow.drawWithAngles();
    }
    drawChalkLines();

//    renderBitmapString(0, 0, 0.5, GLUT_BITMAP_HELVETICA_18, "HELLO");

    //Draw all transparent textured objects here:


    ground.draw(isDay);
    defender.draw(isDay);
    showScore();

    showMsg();

//    loadTextureFile("");
    drawHUD();


    glutSwapBuffers();
    glutPostRedisplay();
}

void showScore() {
    glPushMatrix();
    glTranslatef(0, GOAL_POST_Y, POLE_HEIGHT + BALL_RADIUS);

    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(-POLE_LENGTH / 2.0 - BALL_RADIUS / 2.0, 0.0001, 0);
    glColor4f(125 / 255.0, 178 / 255.0, 209 / 255.0, 0.5);
    glScalef(POLE_LENGTH + BALL_RADIUS, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-POLE_LENGTH / 2.0 - BALL_RADIUS / 2.0, 0.0001, 1);
//    glColor4f(133/255.0, 193/255.0, 162/255.0,0.8);
    glColor4f(178 / 255.0, 255 / 255.0, 215 / 255.0, 0.5);
    glScalef(POLE_LENGTH + BALL_RADIUS, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
    currentTextColor = {24 / 255.0, 163 / 255.0, 24 / 255.0, 1.0};
    glTranslatef(-POLE_LENGTH / 2, 0, 1);
//    glScalef(FONT_SIZE,FONT_SIZE,1.0);
    writeText("GOALS", font, LEFT);
    glPopMatrix();

    glPushMatrix();
    currentTextColor = {32 / 255.0, 140 / 255.0, 32 / 255.0, 1.0};
    glTranslatef(POLE_LENGTH / 2, 0, 1);
//    glScalef(FONT_SIZE,FONT_SIZE,FONT_SIZE);
    writeText(to_string(Goals), font, RIGHT);
    glPopMatrix();

    glPushMatrix();
    currentTextColor = {27 / 255.0, 92 / 255.0, 145 / 255.0, 1.0};
    glTranslatef(-POLE_LENGTH / 2, 0, 0);
//    glScalef(FONT_SIZE,FONT_SIZE,1.0);
    writeText("TRIES", font, LEFT);
    glPopMatrix();

    glPushMatrix();
    currentTextColor = {0.1, 0.1, 1.0, 1.0};
    glTranslatef(POLE_LENGTH / 2, 0, 0);
//    glScalef(FONT_SIZE,FONT_SIZE,FONT_SIZE);
    writeText(to_string(Tries), font, RIGHT);
    glPopMatrix();


    glPopMatrix();
}

void incrementPowerMeter(int _) {
    static int up = 1;
    if (powerMeter >1.0 || powerMeter < 0.0) {
        up *= -1;
    }
    if (!currentlyWaiting && currentMode == POWERING) {
        powerMeter += up * 0.015;
        glutTimerFunc(1000 * 1 / 60.0, incrementPowerMeter, 0);
    }
}


void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y) {    //The current mouse coordinates
    if (currentMode != HELP) {
        switch (key) {
            case '+':
                sphereCamera.distance -= 0.1f;
                sphereCamera.distance += (sphereCamera.distance < MIN_SPHERE_CAMERA_DISTANCE ? 0.1f : 0);
//            cout<<sphereCamera.distance<<endl;

                break;
            case '-':
                sphereCamera.distance += 0.1f;
                sphereCamera.distance -= (sphereCamera.distance > MAX_SPHERE_CAMERA_DISTANCE ? 0.1f : 0);
//            cout<<sphereCamera.distance<<endl;
                break;

            case 'i':
                if(cameraPos[1] < ground.corners[2][1]) {
                    cameraPos[1] += 0.2;
                }
                break;

            case 'k':
                if(cameraPos[1] > ground.corners[0][1]) {
                    cameraPos[1] -= 0.2;
                }
                break;

            case 'j':
                if(cameraPos[0] > ground.corners[0][0]) {
                    cameraPos[0] -= 0.2;
                }
                break;

            case 'l':
                if(cameraPos[0] < ground.corners[2][0]) {
                    cameraPos[0] += 0.2;
                }
                break;

            case 'z':
                cout << "Detected!" << endl;
                if(currentMode == PAUSE) currentMode = ADJUSTING;
                else currentMode = PAUSE;
        }
    } else {
        if (key == 27) {
            currentMode = ADJUSTING;
        }
    }
    downKeys[key] = true;
    if (currentMode == ADJUSTING) {
        switch (key) {
            case '\r':
                currentMode = AIMING;
                break;
            case EXIT_KEY: //Escape key
                exit(0); //Exit the program
        }
    }
    if (currentMode == AIMING) {
        switch (key) {
            case ' ':
                currentMode = POWERING;
                glutTimerFunc(1000 * 1 / 60.0, incrementPowerMeter, 0);
                break;
            case 27: //Escape key
                currentMode = ADJUSTING;
        }
    }
    if(key == 'n') {
        isDay = !isDay;
        if(isDay) {
            glEnable(GL_LIGHT0); //Enable light #0
            glEnable(GL_LIGHT1); //Enable light #1
            glEnable(GL_LIGHT2); //Enable light #2
            glDisable(GL_LIGHT3); //Disable light #3
            glDisable(GL_LIGHT4); //Disable light #4
        }
        else {
            glDisable(GL_LIGHT0); //Disable light #0
            glDisable(GL_LIGHT1); //Disable light #1
            glDisable(GL_LIGHT2); //Disable light #2
            glEnable(GL_LIGHT3); //Enable light #3
            glEnable(GL_LIGHT4); //Enable light #4
        }
    }

    if(currentMode==PAUSE) {
        printf("%f, %f, %f\n", cameraPos.x, cameraPos.y, cameraPos.z);
        printf("%f, %f, %f\n", sphereCamera.distance, sphereCamera.zAngle, sphereCamera.xAngle);
        switch(key) {
            case '+':
                lookDist[2] += 0.2;
                printf("%f %f %f", lookDist[0], lookDist[1], lookDist[2]);
                break;
            
            case '-':
                lookDist[2] -= 0.2;
                break;

            case EXIT_KEY:
                exit(0);
        }
    }
}

void idle() {
    if (!currentlyWaiting) {
        if (currentMode == POWERING && !downKeys[' ']) {
            sphere.velocityCurrent[0] = sphere.velocityInitial[0] =
                    cos(DEG2GRAD(aimArrow.zAngle)) * sin(DEG2GRAD(aimArrow.yAngle)) * BALL_MAX_SPEED * powerMeter;
            sphere.velocityCurrent[1] = sphere.velocityInitial[1] =
                    cos(DEG2GRAD(aimArrow.zAngle)) * cos(DEG2GRAD(aimArrow.yAngle)) * BALL_MAX_SPEED * powerMeter;
            sphere.velocityCurrent[2] = sphere.velocityInitial[2] =
                    sin(DEG2GRAD(aimArrow.zAngle)) * BALL_MAX_SPEED * powerMeter + BALL_MIN_SPEED;
            if (powerMeter >= 1.0)
                powerMeter = 1.0;
            glutTimerFunc(10, updatePosCallBack, 0);
            currentlyWaiting = true;
        }
        if (currentMode == POWERING && downKeys[27]) {
            currentMode = AIMING;
            powerMeter = 0.0;
        }
        if (currentMode == SHOOTING) {
            if (sphere.positionCurrent.y <= GOAL_POST_Y)
                toLookAt = sphere.positionCurrent;
        }
        if (currentMode == SHOOTING) {
            if (sphere.positionCurrent.y > GOAL_POST_Y || sphere.velocityCurrent.y <= 0) {
                if (!determineSphere && !stopEverything) {
                    determineSphere = new PhysicalState;
                    *determineSphere = sphere;
//                    cout << *determineSphere;
                    scoredGoal = isItGoal(*determineSphere);
                    if (scoredGoal) {
                        Goals++;
                        system("paplay resources/goal.wav&");
                    }

                    rotateMsg(0);
                    glutTimerFunc(1000 * RESET_TIME, initialiseEverythingCallback, 0);
                    Tries++;
                }
            }
        }
        if (currentMode == POWERING) {
        }
    }
    glutPostRedisplay();
}

axes toLookAt;

void handleUpKeypress(unsigned char key, int x, int y) {
    downKeys[key] = false;
}

void handleSpecialKeypress(int key, int x, int y) {
//    if (currentMode == ADJUSTING || currentMode == REPLAY) {
//        switch (key) {
//            case GLUT_KEY_UP:
//                sphereCamera.zAngle += 1.0f;
//                break;
//            case GLUT_KEY_DOWN:
//                sphereCamera.zAngle -= 1.0f;
//                break;
//            case GLUT_KEY_LEFT:
//                sphereCamera.xAngle -= 1.0f;
//                break;
//            case GLUT_KEY_RIGHT:
//                sphereCamera.xAngle += 1.0f;
//                break;
//        }
//    }
    if (currentMode == AIMING) {
//    glTranslatef(36.0, 0, 0);
//    glScalef(-1.0, 1.0, 1.0);
//    glColor4f(0.1, 0.1, 0.1, 1.0);
//    glBegin(GL_QUADS);
//    glVertex2f(-10.0, -0.2);
//    glVertex2f(5.0, -0.2);
//    glVertex2f(5.0, 0.2);
//    glVertex2f(-10.0, 0.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//
//    glVertex2f(5.0, -0.4);
//    glVertex2f(8.0, 0.0);
//    glVertex2f(5.0, 0.4);
//    glEnd();
//
//    glColor3f(0.3, 0.3, 1.0);
//    glTranslatef(18, 0, 0);
//    glBegin(GL_LINES);
//    glVertex2f(-10, 0);
//    glVertex2f(10.0, 0);
//    glEnd();
        const float increment=2.0f;
        switch (key) {
            case GLUT_KEY_UP:
                aimArrow.zAngle += (aimArrow.zAngle>50?0:increment);
                break;
            case GLUT_KEY_DOWN:
                aimArrow.zAngle -= (aimArrow.zAngle<0.01?0:increment);
                break;
            case GLUT_KEY_LEFT:
                aimArrow.yAngle -= (aimArrow.yAngle<-60?0:increment);
                break;
            case GLUT_KEY_RIGHT:
                aimArrow.yAngle += (aimArrow.yAngle>60?0:increment);
                break;
        }
    }
}

template<typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void handlePassiveMouse(int x, int y) {
//    if (currentMode == ADJUSTING) {
    if (currentMode != HELP && currentMode != PAUSE) {
        sphereCamera.xAngle = -90 + (x - WIDTH / 2) * 270 / WIDTH;
        sphereCamera.zAngle = 45 + -1 * (y) * 30 / HEIGHT;
    }
}

void handleMouse(int button, int state, int x, int y) {
    if(state == GLUT_UP) {
//         switch(button) {
//             case 3: // scroll up
//                 sphereCamera.distance -= 0.1f;
//                 sphereCamera.distance += (sphereCamera.distance < MIN_SPHERE_CAMERA_DISTANCE ? 0.1f : 0);
// //            cout<<sphereCamera.distance<<endl;

//                 break;

//             case 4: // scroll down
//                 sphereCamera.distance += 0.1f;
//                 sphereCamera.distance -= (sphereCamera.distance > MAX_SPHERE_CAMERA_DISTANCE ? 0.1f : 0);
// //            cout<<sphereCamera.distance<<endl;
//                 break;
//         }
        cout << x << " " << y << endl;
        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        // Get the viewport, modelview, and projection matrices
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        // Convert the 2D mouse coordinates into 3D world coordinates
        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        // Print the 3D world coordinates
        printf("Clicked at (%f, %f, %f)\n", posX, posY, posZ);
    }
}

void myInit(void) {
    // glClearColor(137 / 255.0, 206 / 255.0, 255 / 255.0, 0);
    glClearColor(13 / 255.0, 13 / 255.0, 13 / 255.0, 0);
//    glOrtho(0, WIDTH, 0, HEIGHT, 0, 500);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    isDay = true;
    glEnable(GL_LIGHTING); //Enable lighting


    cameraPos[0] = cameraPos[1] = cameraPos[2] = 0.0;

    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_LIGHT2); //Enable light #2
    glDisable(GL_LIGHT3); //Disable light #3
    glDisable(GL_LIGHT4); //Disable light #4
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    glShadeModel(GL_SMOOTH);
    backgroundMusicPlayer(0);
    updateDefenderPosition(0);
    // glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_MULTISAMPLE);

}

int main(int argc, char *argv[]) {
//    convertToTexture("resources/texture.txt", "resources/texture.texture");
    initialiseEverything();
    currentMode = HELP;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(WINDOW_NAME);
    // glutFullScreen();
    glutReshapeFunc(handleResize);
    glutIdleFunc(idle);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleUpKeypress);
    glutSpecialFunc(handleSpecialKeypress);
    glutPassiveMotionFunc(handlePassiveMouse);
//    groundTexture = LoadBMP("resources/grass.bmp");
    groundTexture = convertAndLoadTexture("resources/grass.txt");
    defenderTexture = convertAndLoadTexture("resources/defender.txt");
    font = convertAndLoadTexture("resources/fonts/Ubuntu Mono Nerd Font Complete Mono.txt");
    ads = convertAndLoadTexture("resources/ads.txt");
    leftArm = convertAndLoadTexture("resources/left_arm.txt");
    rightArm = convertAndLoadTexture("resources/right_arm.txt");
    glutMouseFunc(handleMouse);
    glutDisplayFunc(draw);
    myInit();
    glutMainLoop();

    return 0;
}
