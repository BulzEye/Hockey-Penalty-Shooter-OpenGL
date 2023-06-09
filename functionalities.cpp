//
// Created by kunal on 4/3/18.
//

#include "functionalities.h"
#include "shapes.h"
#include <bits/stdc++.h>

using namespace std;


mode currentMode = ADJUSTING;
bool currentlyWaiting;
bool downKeys[127];
bool scoredGoal;
int goalCount, totalTries;
int mouseX, mouseY;
bool firstTime = true;
PhysicalState sphere, *determineSphere = NULL;

extern bool isDay;
extern axes cameraPos;

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    glFrustum(-1.0 * w / h, 1.0 * w / h, -1, 1, 2, 100);
    glMatrixMode(GL_MODELVIEW);
//    gluPerspective(45,                  //The camera angle
//                   (double) w / (double) h, //The width-to-height ratio
//                   1.0,                   //The near z clipping coordinate
//                   200.0);                //The far z clipping coordinate
}

double &axes::operator[](int index) {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            cout << "Out of Bound Axis!" << endl;
            exit(1);
    }
}

double distanceBW(axes axes1, axes axes2) {
    double sum = 0.0;
    double sqr;
    for (int i = 0; i < 3; ++i) {
        sqr = axes1[i] - axes2[i];
        sqr *= sqr;
        sum += sqr;
    }
    return sqrt(sum);
}


PhysicalState::PhysicalState() {
    positionInitial = positionCurrent = velocityInitial = velocityCurrent = accelerationCurrent = {0.0, 0.0, 0.0};
    timePassed = 0;
    elasticity = 1.0;
}

ostream &operator<<(ostream &out, PhysicalState &p) {
    out << "Current Position : " << endl;
    for (int i = 0; i < 3; ++i) {
        out << p.positionCurrent[i] << "    ";
    }
    out << endl;
    out << "Current Velocity : " << endl;
    for (int i = 0; i < 3; ++i) {
        out << p.velocityCurrent[i] << "    ";
    }
    out << endl;
    out << "Time Passed : ";
    out << p.timePassed << endl;
    return out;
}


bool isItGoal(PhysicalState ball) {
    if ((ball.positionCurrent.x <= -POLE_RADIUS + POLE_LENGTH / 2) &&
        (ball.positionCurrent.x >= +POLE_RADIUS - POLE_LENGTH / 2) &&
        (ball.positionCurrent.z <= POLE_HEIGHT) && (ball.positionCurrent.y > GOAL_POST_Y))
        return true;
    else
        return false;

}

void backgroundMusicPlayer(int _) {

//    if (currentMode != GOAL_ANIMATION)
    system("paplay resources/back.wav --volume 30000 &");
    glutTimerFunc(5 * 1000, backgroundMusicPlayer, 0);
}

//int LoadGLTexture(char *filename) {
//    GLuint texture = SOIL_load_OGL_texture
//            (
//                    filename,
//                    SOIL_LOAD_AUTO,
//                    SOIL_CREATE_NEW_ID,
//                    SOIL_FLAG_INVERT_Y
//            );
//
//
//    if (texture == 0)
//        return false;
//
//
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    return texture;
//}


void initialiseEverything() {
    ground.Type = WALL;
    axes temp;
    temp = {-20, -20, -BALL_RADIUS};
    ground.corners[0] = temp;
    temp = {-20, 20, -BALL_RADIUS};
    ground.corners[1] = temp;
    temp = {20, 20, -BALL_RADIUS};
    ground.corners[2] = temp;
    temp = {20, -20, -BALL_RADIUS};
    ground.corners[3] = temp;
    ground.color[0] = 1 / 255.0;
    ground.color[1] = 142 / 255.0;
    ground.color[2] = 14 / 255.0;


    poles[0].Type = L_POLE;
    poles[0].height = POLE_HEIGHT;
    poles[1].Type = U_POLE;
    poles[1].height = POLE_LENGTH / 2;
    poles[2].Type = R_POLE;
    poles[2].height = POLE_HEIGHT;

    temp = {0, 0, 0};
    aimArrow.start = temp;
    temp = {0, 2, 0};
    aimArrow.finish = temp;

    aimArrow.width = 0.2;


    aimArrow.zAngle = 0.0;
    aimArrow.yAngle = 0.0;
    aimArrow.length = 2.0;

    aimArrow.color[0] = 50 / 255.0;
    aimArrow.color[1] = 50 / 255.0;
    aimArrow.color[2] = 127 / 255.0;
    aimArrow.color[3] = 1.0;


    defender.color[0] = 250 / 255.0;
    defender.color[1] = 100 / 255.0;
    defender.color[2] = 100 / 255.0;
    defender.color[3] = 1.0;

    defender.width = DEFENDER_WIDTH;
    defender.height = 2.3;

    defender.state.velocityInitial.x = defender.state.velocityCurrent.x = DEFENDER_SPEED;
    defender.state.positionCurrent.x = 0.0;


    sphereCamera.xAngle = -90.0f;
    sphereCamera.zAngle = 15.0f;
    sphereCamera.distance = 5.0;
    sphereCamera.distance = 10;
    tempSphereCamera = sphereCamera;
    sphereCamera.xAngle = -90.0f;
    sphereCamera.zAngle = 35.0f;
    sphereCamera.distance = 13.0;
    for (int i = 0; i < 3; ++i) {
        sphere.positionCurrent[i] = sphere.velocityCurrent[i] = 0;
    }
    powerMeter = 0.0;
    currentMode = ADJUSTING;

    sphere.positionInitial.x = sphere.positionCurrent.x = 0.0;
    sphere.velocityCurrent[0] = sphere.velocityInitial[0] = 0;
    sphere.accelerationCurrent[2] = -9.8;
    toLookAt = sphere.positionCurrent;

    sphere.elasticity = BALL_ELASTICITY;
    stopEverything = false;

    if (determineSphere) {
        delete determineSphere;
        determineSphere = NULL;
    }
    system("paplay resources/whistle.wav &");
}

void initialiseEverythingCallback(int _) {
    stopEverything = true;
    initialiseEverything();
}

void drawGoalPost() {

    {
        glPushMatrix();
        glTranslated(GOAL_POST_X - POLE_LENGTH / 2 + POLE_RADIUS, GOAL_POST_Y + 0, 0 - BALL_RADIUS);
        poles[0].draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(GOAL_POST_X + 0, GOAL_POST_Y + 0, POLE_HEIGHT + POLE_RADIUS - BALL_RADIUS);
        poles[1].draw();
        glPopMatrix();


        glPushMatrix();
        glTranslated(GOAL_POST_X + POLE_LENGTH / 2 - POLE_RADIUS, GOAL_POST_Y + 0, 0 - BALL_RADIUS);
        poles[2].draw();
        glPopMatrix();
    }

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


void cameraPosition(axes point, double distance, double zAngle, double xAngle) {
    gluLookAt(point.x + distance * (cos(DEG2GRAD(zAngle)) * cos(DEG2GRAD(xAngle))),
              point.y + distance * (cos(DEG2GRAD(zAngle)) * sin(DEG2GRAD(xAngle))),
              point.z + distance * sin(DEG2GRAD(zAngle)), point.x, point.y, point.z, 0, 0, 1);
                // printf("%f %f %f, %f %f %f\n", point.x + distance * (cos(DEG2GRAD(zAngle)) * cos(DEG2GRAD(xAngle))),
                // point.y + distance * (cos(DEG2GRAD(zAngle)) * sin(DEG2GRAD(xAngle))), 
                // point.z + distance * sin(DEG2GRAD(zAngle)), point.x, point.y, point.z);

}

camera::camera() {
    zAngle = xAngle = 0.0;
    distance = 5.0;
}

camera sphereCamera;
camera tempSphereCamera;
// The pause menu changes the sphereCamera coordinates. 
// To ensure we go back to where we were present initially, we use tempSphereCamera


void rainBox(double alpha = 0.7) {

    glBegin(GL_QUADS);
    glColor4f(1.0f, 0.0f, 0.0, alpha); //RED
    glVertex2f(-10.0, -20.0);
    glVertex2f(10.0, -20.0);

    glColor4f(1.0f, 1.0f, 0.0, alpha); //YELLOW
    glVertex2f(10.0, -10.0);
    glVertex2f(-10.0, -10.0);

    glVertex2f(-10.0, -10.0);
    glVertex2f(10.0, -10.0);


    glColor4f(0.0f, 1.0f, 0.0, alpha); //GREEN
    glVertex2f(10.0, 0.0);
    glVertex2f(-10.0, 0.0);
    glEnd();
}

void myShear() {
//    glRotatef(-45, 0.0, 0.0, 1.0);
    float m[] = {
            1.0, 0.0, 0.0, 0.0,
            1.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
    glMultMatrixf(m);
}

void drawBitmapText(char *string, float x, float y, float z)
{
    char *c;
    glRasterPos3f(x, y, z);//define position on the screen where to draw text.

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

double powerMeter = 0.0;

void drawPowerMeter() {


    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);

    glTranslatef(-10.0, -20.0 + powerMeter * 40, 0.0);

    glColor4f(0.1, 0.1, 0.1, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-10.0, -0.2);
    glVertex2f(5.0, -0.2);
    glVertex2f(5.0, 0.2);
    glVertex2f(-10.0, 0.2);
    glEnd();
    glBegin(GL_TRIANGLES);

    glVertex2f(5.0, -0.4);
    glVertex2f(8.0, 0.0);
    glVertex2f(5.0, 0.4);


    glEnd();
//
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


    glPopAttrib();
    glPopMatrix();
}

void drawString(float x, float y, float z, char *string) {
  // Save the current matrix
  glPushMatrix();

  // Translate to the appropriate starting point
  glTranslatef(x, y, z);
  glScalef(10.0f, 10.0f, 1.0f);

  // Note: We could change the line width with glLineWidth()

  // Render the characters
  for (char* c = string; *c != '\0'; c++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
  }

  // Another useful function
  //    int glutStrokeWidth(void *font, int character);

  // Retrieve the original matrix
  glPopMatrix();
}


void drawHUD() {
    glDisable(GL_LIGHTING);
//     if (currentMode == HELP) {

//         const char *instructions = R"INSTRUCT(
// INSTRUCTIONS
// You can use the mouse to look around.
// Use the +/- keys for zooming in/out.

// AIMING
// Press the Enter/Return key to enter Aiming Mode.
// Direct the arrow with the arrow keys to set up the
// direction of the shot.

// POWERING
// Press and hold Space after aiming to power up.
// Release Space to select the specified power level.
// Press the ESC key (when holding down SPACE) to cancel
// POWERING mode.

// Press ESC key to return to the previous mode or to exit the
// instructions.
// Press Q at any time to exit the game.

// I'm adding a new line, is it okay?
// )INSTRUCT";

//         glPushMatrix();
//         glRotatef(90 + sphereCamera.xAngle, 0, 0, 1);
//         glRotatef(-sphereCamera.zAngle, 1, 0, 0);

//         glTranslatef(0, -BALL_RADIUS, -BALL_RADIUS);

//         glColor4f(0, 0, 0, 0.8);
//         glBegin(GL_QUADS);
//         glVertex3f(-10, 0, -5);
//         glVertex3f(10, 0, -5);
//         glVertex3f(10, 0, 6);
//         glVertex3f(-10, 0, 6);
//         glEnd();
//         glScalef(0.5, 0.5, 0.5);
//         glTranslatef(0, -0.001, 9.5);

//         currentTextColor = {1.0, 1.0, 1.0, 1.0};
//         writeMultiLineText(instructions, font, CENTER);
//         glPopMatrix();
//     } 
    if(currentMode == PAUSE || currentMode == HELP) {
        const char *instructions = 
        // if mode is PAUSE then load appropriate instructions string
        ((currentMode == PAUSE) ? R"INSTRUCT(
PAUSE MENU



Press H for showing instructions
Press F to enter or exit full screen mode
Press Esc to return




Press Q to quit
)INSTRUCT" 

: //----------------------- OR if mode is HELP -----------------------

 R"INSTRUCT(
INSTRUCTIONS
You can use the mouse to look around.
Use the +/- keys (or the mouse scroll wheel) for zooming in/out.
Use I/K to move the camera towards / away from the goalpost.
Use J/L to move the camera to the left / right of the goalpost.
Use N to toggle Night Mode.

AIMING
Press the Enter/Return key to enter or exit Aiming Mode.
Direct the arrow with the arrow keys to set up the
direction of the shot.

POWERING
Press and hold Space after aiming to power up.
Release Space to select the specified power level.
Press the ESC key (when holding down SPACE) to cancel
POWERING mode.

Press ESC key to continue.
)INSTRUCT");

        cameraPos.x = cameraPos.y = cameraPos.z = 0.0;
        sphereCamera.distance = 13.0;
        sphereCamera.zAngle = 35.0;
        sphereCamera.xAngle = -90.0;
        // cameraPosition({0, 0, 0}, 15.0, 35.0, -90.0);
        
        // glPushMatrix();
        // glRotatef(90 + sphereCamera.xAngle, 0, 0, 1);
        // glRotatef(-sphereCamera.zAngle, 1, 0, 0);
        glPushMatrix();
        glRotatef(0, 0, 0, 1);
        glRotatef(-35.0, 1, 0, 0);
        
        if(currentMode == PAUSE)
            glTranslatef(0, -BALL_RADIUS-2, -BALL_RADIUS-1);
        else if(currentMode == HELP)
            glTranslatef(0, -BALL_RADIUS-2, -BALL_RADIUS);

        glColor4f(0, 0, 0, 0.9);
        glBegin(GL_QUADS);
        // glVertex3f(-10, 0, -5);
        // glVertex3f(10, 0, -5);
        // glVertex3f(10, 0, 6);
        // glVertex3f(-10, 0, 6);
        glVertex3f(-15, 0, -10);
        glVertex3f(15, 0, -10);
        glVertex3f(15, 0, 11);
        glVertex3f(-15, 0, 11);
        glEnd();
        if(currentMode == PAUSE)
            glScalef(0.6, 0.6, 0.6);
        else 
            glScalef(0.5, 0.5, 0.5);
        glTranslatef(0, -0.001, 9.5);

        currentTextColor = {1.0, 1.0, 1.0, 1.0};
        writeMultiLineText(instructions, font, CENTER);
        glPopMatrix();
    } 
    else if(currentMode == ADJUSTING || currentMode == AIMING) {
        const char *adj_instructions = "\n\n\n\n\n\n\n\n\n\n\n\n\n"
        "Esc: Pause, Enter: Aiming mode\n";
        const char *aim_instructions = "\n\n\n\n\n\n\n\n\n\n\n\n\n"
        "Esc: Pause, Space (hold): Power\n";
        // cameraPos.x = cameraPos.y = cameraPos.z = 0.0;
        // sphereCamera.distance = 13.0;
        // sphereCamera.zAngle = 35.0;
        // sphereCamera.xAngle = -90.0;
        // cameraPosition({0, 0, 0}, 15.0, 35.0, -90.0);
        
        glPushMatrix();
        glTranslatef(cameraPos.x, cameraPos.y, cameraPos.z);
        glTranslatef((sphereCamera.distance-6) * (cos(DEG2GRAD(sphereCamera.zAngle)) * cos(DEG2GRAD(sphereCamera.xAngle))),
        (sphereCamera.distance-6) * (cos(DEG2GRAD(sphereCamera.zAngle)) * sin(DEG2GRAD(sphereCamera.xAngle))),
        (sphereCamera.distance-6) * sin(DEG2GRAD(sphereCamera.zAngle)));
        glRotatef(90 + sphereCamera.xAngle, 0, 0, 1);
        glRotatef(-sphereCamera.zAngle, 1, 0, 0);
        // glPushMatrix();
        // glRotatef(0, 0, 0, 1);
        // glRotatef(-35.0, 1, 0, 0);
        glTranslatef(0, -2, -1);
        currentTextColor = {1.0, 1.0, 1.0, 1.0};

        glColor4f(0, 0, 0, 0.6);
        glBegin(GL_QUADS);
        // glVertex3f(-10, 0, -5);
        // glVertex3f(10, 0, -5);
        // glVertex3f(10, 0, 6);
        // glVertex3f(-10, 0, 6);
        float coords[] = {-2.5, 2.5, -0.5, -5}; // xStart, xEnd, zEnd, zBegin
        glVertex3f(coords[0], 0, coords[3]);
        glVertex3f(coords[1], 0, coords[3]);
        glVertex3f(coords[1], 0, coords[2]);
        glVertex3f(coords[0], 0, coords[2]);
        glEnd();
        glScalef(0.25, 0.25, 0.25);
        glTranslatef(0, -0.001, 9.5);
        // glTranslatef(0, -1, -10);

        if(currentMode == ADJUSTING)
            writeMultiLineText(adj_instructions, font, CENTER);
        else if(currentMode == AIMING)
            writeMultiLineText(aim_instructions, font, CENTER);

        glPopMatrix();
    } 
    else {   //HUD Render

        glDisable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-100.0, 100.0, -100.0, 100.0);       //glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//        glDisable(GL_CULL_FACE);

        glClear(GL_DEPTH_BUFFER_BIT);


        if (currentMode == POWERING) {   //Power Bar
            glPushMatrix();

            glTranslatef(90, 0, 0);


            glScalef(0.3, 4.0, 1.0);

            drawPowerMeter();


            rainBox();
            glScalef(1.0, -1.0, 0.0);
            rainBox();

            glPopMatrix();
        }
        // else if(currentMode == PAUSE) {
        //     glPushMatrix();

        //     // glTranslatef(90, 0, 0);


        //     // glScalef(0.3, 4.0, 1.0);
        //     // writeText("Hello", font, CENTER);
        //     glColor4f(0.2, 1.0, 0.0, 1.0);
        //     drawString(50, 0, 50, (char*)"Hello");
        //     // glScalef(0.2, 0.2, 0.0);

        //     glColor4f(0.2, 0.2, 0.2, 1.0);
        //     glBegin(GL_QUADS);
        //     glVertex2f(-100.0, -100.0);
        //     glVertex2f(-100.0, 100.0);
        //     glVertex2f(100.0, 100.0);
        //     glVertex2f(100.0, -100.0);
        //     glEnd();

        //     glPopMatrix();
        // }

// Making sure we can render 3d again

        glEnable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glPopAttrib();
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

    }
    glEnable(GL_LIGHTING);
}
void updateDefenderPosition(int _) {

    static float increment = 2.0f;
    static int done = 0;
    defender.armRot += increment;

    if (defender.armRot > 100.0 || defender.armRot < 0.0) {
        increment *= -1;
    }

    defender.state.timePassed += 1 / 60.0;
    double t = 1 / 60.0;
    defender.acceleration();

    if (currentMode == SHOOTING) {
        if (!done) {
//            cout<<sphere.velocityCurrent.x<<endl;
            if (sphere.velocityCurrent.x < 0) {
                defender.state.velocityCurrent.x = -DEFENDER_SPEED;
                done = 1;
            } else if (sphere.velocityCurrent.x > 0) {
                defender.state.velocityCurrent.x = DEFENDER_SPEED;
                done = 1;
            } else {
                defender.state.velocityCurrent.x = 0;
                done = 1;
            }
        }
        for (int i = 0; i < 3; ++i) {
            defender.state.positionCurrent[i] =
                    defender.state.velocityCurrent[i] * t + 0.5 * defender.state.accelerationCurrent[i] * t * t +
                    defender.state.positionCurrent[i];
            defender.state.velocityCurrent[i] =
                    defender.state.velocityCurrent[i] + defender.state.accelerationCurrent[i] * t;
        }
//    if (currentMode != NONE && currentMode != GOAL_ANIMATION){
//    }
    }
    else{
        done=0;
    };
    glutTimerFunc(1000 * 1 / 60.0, updateDefenderPosition, 1 / 60.0);
}


int convertToTexture(const char *filename) {
    ifstream textFile(filename);
    string destination(filename);
    destination += ".tx";
    if (!textFile) {
        cout << "File cannot be opened!" << endl;
        return -1;
    }
    unsigned color;
    vector<unsigned char> text;
    int w, h;
    textFile >> w >> h;
    while (textFile >> color) {
        text.push_back((color & 0xff000000) >> 24);
        text.push_back((color & 0x00ff0000) >> 16);
        text.push_back((color & 0x0000ff00) >> 8);
        text.push_back((color & 0x000000ff) >> 0);
    }
    unsigned char *colors = &text[0];
    ofstream dest(destination.c_str(), ios::out | ios::binary);
    unsigned int size = text.size();
    dest.write((char *) colors, text.size());
    dest.write((char *) &w, sizeof(w));
    dest.write((char *) &h, sizeof(h));
    dest.close();
    return 0;
}

GLuint loadTextureFile(const char *filename) {

    GLuint texture;
    glEnable(GL_DEPTH_TEST);
    ifstream textureFile(filename, ios::ate | ios::binary);
    int size = textureFile.tellg();
    size -= 2 * sizeof(int);  //widht, height stored at the end.
    textureFile.close();
    int w, h;
    textureFile.open(filename, ios::in | ios::binary);

    unsigned char *texel = new unsigned char[size];
    textureFile.read((char *) texel, size);
    textureFile.read((char *) &w, sizeof(w));
    textureFile.read((char *) &h, sizeof(h));
    assert(w * h == size / 4);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texel[0]);
    delete[] texel;
    return texture;
}

const float chalkwidth = POLE_RADIUS;

void chalkHRectangle(axes start, axes end) {
    glBegin(GL_QUADS);
    glVertex3f(start.x, start.y - chalkwidth / 2.0, 0);
    glVertex3f(start.x, start.y + chalkwidth / 2.0, 0);
    glVertex3f(end.x, end.y + chalkwidth / 2.0, 0);
    glVertex3f(end.x, end.y - chalkwidth / 2.0, 0);
    glEnd();
}

void chalkVRectangle(axes start, axes end) {
    glBegin(GL_QUADS);
    glVertex3f(start.x - chalkwidth / 2.0, start.y, 0);
    glVertex3f(start.x + chalkwidth / 2.0, start.y, 0);
    glVertex3f(end.x + chalkwidth / 2.0, end.y, 0);
    glVertex3f(end.x - chalkwidth / 2.0, end.y, 0);
    glEnd();
}

void drawChalkLines() {
    glPushAttrib(GL_LINE_WIDTH);
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();

    glColor3f(0.9, 0.9, 0.9);
    glTranslatef(0, 0, 0.0001 - BALL_RADIUS);
//    glLineWidth(POLE_RADIUS / 1.5);
    GLUquadric *quad = gluNewQuadric();
    gluDisk(quad, 0, chalkwidth / 1.5, 25, 6);
    gluDeleteQuadric(quad);
    axes start = {ground.corners[1].x + 2, GOAL_POST_Y, 0};
    axes end = {ground.corners[2].x - 2, GOAL_POST_Y, 0};
    chalkHRectangle(start, end);
    start.y = -start.y;
    end.y = -end.y;
    chalkHRectangle(start, end);
    start = {ground.corners[1].x + 2, GOAL_POST_Y + chalkwidth / 2.0, 0};
    end = {ground.corners[0].x + 2, -GOAL_POST_Y - chalkwidth / 2.0, 0};
    chalkVRectangle(start, end);
    start.x = -start.x;
    end.x = -end.x;
    chalkVRectangle(start, end);
    glPopMatrix();
    glPopAttrib();
    glPopAttrib();
}

GLuint convertAndLoadTexture(const char *filename) {
    convertToTexture(filename);
    string dest(filename);
    dest += ".tx";
    return loadTextureFile(dest.c_str());
}

GLuint groundTexture, defenderTexture, leftArm, rightArm, font, ads;

void start2DTexture(GLuint texture, bool lightingDisabled) {

    glPushAttrib(GL_CURRENT_BIT);
    if (lightingDisabled)
        glDisable(GL_LIGHTING);
    // if (lightingDisabled) {
    //     glDisable(GL_LIGHT0);
    //     glDisable(GL_LIGHT1);
    //     glDisable(GL_LIGHT2);
    //     glEnable(GL_LIGHT3);
    //     glEnable(GL_LIGHT4);
    //     glEnable(GL_LIGHTING);
    // }



    glDepthMask(GL_FALSE);
    glPushMatrix();
    // GLfloat mat_amb[] = { 0.7, 0.7, 0.7, 1.0 };
    // GLfloat mat_dif[] = { 1.0, 1.0, 1.0, 1.0 };
    // // GLfloat mat_spc[] = { 1.0, 1.0, 1.0, 1.0 };
    // // GLfloat mat_shin[] = { 50.0 };
    // glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
    // // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spc);
    // // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shin);

    // if(!isDay) {
    //     glEnable(GL_COLOR_MATERIAL);
    // }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_BLEND);
    // glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); 
    // glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
//    glEnable(GL_TEXTURE_GEN_T);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 1.0, 1.0, 1.0);//Replace this alpha for transparency
}

void end2DTexture(bool lightingDisabled) {

//    glDisable(GL_BLEND);
    if (lightingDisabled)
        glEnable(GL_LIGHTING);
    // if (lightingDisabled) {
    //     glEnable(GL_LIGHT0);
    //     glEnable(GL_LIGHT1);
    //     glEnable(GL_LIGHT2);
    //     glDisable(GL_LIGHT3);
    //     glDisable(GL_LIGHT4);
    //     glEnable(GL_LIGHTING);
    // }

//    glDisable(GL_TEXTURE_GEN_S); //disable texture coordinate generation
//    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopAttrib();
    glDepthMask(GL_TRUE);
}

void writeMultiLineText(string text, int texture, alignment align) {
    std::stringstream iss(text);

    while (iss.good()) {
        std::string SingleLine;
        getline(iss, SingleLine, '\n');
        writeText(SingleLine, texture, align);
        glTranslated(0, 0, -1);
    }
}

float writeText(string text, int texture, alignment align) {
    start2DTexture(texture);
    glColor4fv(&currentTextColor[0]);
    int w, h;
    int miplevel = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
    float translatex = (w / 128.0) / h, translatey = 0, translatez = 0;
    //    glPushMatrix();
//    glPushAttrib(GL_CURRENT_BIT);
//
//
//    glColor4fv(color);
    if (align == CENTER) {
//        float transx = text.size()*translatex/2.0;
        glTranslated(0 - ((text.size()) * translatex / 2.0), 0, 0);
    } else if (align == RIGHT) {
        float transx = text.size() * translatex;
        glTranslated(0 - ((text.size()) * translatex / 1.0), 0, 0);
    }
    for (char chr: text) {
        glBegin(GL_QUADS);
        glTexCoord2f(chr / 128.0, 1);
        glVertex3f(0, 0, 0);

        glTexCoord2f((chr + 1) / 128.0, 1);
        glVertex3f((translatex), 0, 0);

        glTexCoord2f((chr + 1) / 128.0, 0);
        glVertex3f((translatex), 0, 1);

        glTexCoord2f(chr / 128.0, 0.0);
        glVertex3f(0, 0, 1);

        glEnd();

        glTranslatef(translatex, translatey, translatez);
    }

    glEnd();

    end2DTexture();
    return (2 * w / 128.0) / h;
}


int textRotX;

void rotateMsg(int _) {
    textRotX = (textRotX + 3) % 360;

    if (textRotX != 0) {
        glutTimerFunc(1, rotateMsg, 0);
    }
}


void showMsg() {
    glPushMatrix();

    float col[] = {132 / 255.0, 121 / 255.0, 150 / 255.0, 0.7};
//    float col[] = {1,0,0,1};

    float distance = sphereCamera.distance - 4;

    float colin[] = {1.0, 1.0, 1.0, 0.7};
    glTranslatef(distance * (cos(DEG2GRAD(sphereCamera.zAngle)) * cos(DEG2GRAD(sphereCamera.xAngle))),
                 distance * (cos(DEG2GRAD(sphereCamera.zAngle)) * sin(DEG2GRAD(sphereCamera.xAngle))),
                 distance * sin(DEG2GRAD(sphereCamera.zAngle)));
    // glTranslatef(toLookAt.x, toLookAt.y, toLookAt.z);
    glTranslatef(cameraPos.x, cameraPos.y, cameraPos.z);
    glRotatef(90 + sphereCamera.xAngle + textRotX, 0, 0, 1);
    glRotatef(-sphereCamera.zAngle, 1, 0, 0);
    glScalef(0.75, 0.75, 0.75);

    bool toWrite = true;

    string msg = "MISS!";

    currentTextColor = {1.0, 0.3, 0.3, 1};
    if (determineSphere) {
        if (isItGoal(*determineSphere)) {
            msg = "GOAL!";
            currentTextColor = {0.3, 1.0, 0.3, 1};
        }
    }
    if (!determineSphere) {
        msg = "";
        toWrite = false;
    }
    if (toWrite) {
        GLUquadric *quad = gluNewQuadric();
        glPushMatrix();
        glColor4fv(col);
        glScalef(2, 0.5, 1);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quad, 1, 1, 1, 40, 40);
        gluDisk(quad, 0.9, 1, 40, 40);
        glColor4fv(colin);
        gluDisk(quad, 0, 0.9, 40, 40);

        glPopMatrix();

        glPushMatrix();

        glPushMatrix();
        glColor4fv(col);
        glScalef(2, 0.5, 1);
        glTranslatef(0, -1, 0);
        glRotatef(90, 1, 0, 0);
        gluDisk(quad, 0.9, 1, 40, 40);
        glColor4fv(colin);
        gluDisk(quad, 0, 0.9, 40, 40);
        glPopMatrix();
        gluDeleteQuadric(quad);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0, .001, -0.5);
        glRotatef(180, 0, 0, 1);
        writeText(msg, font, CENTER);

        glPopMatrix();


        glPushMatrix();
        glTranslatef(0, -0.501, -0.5);
        writeText(msg, font, CENTER);
        glPopMatrix();

    }
    glPopMatrix();
}