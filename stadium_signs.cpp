#include <GL/glut.h>
#include <bits/stdc++.h>
#include "constants.h"
#include "functionalities.h"
#include "shapes.h"

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