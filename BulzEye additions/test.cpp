#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<pair<float, float> > coords;
const int n = 4;
const float transX = 10, transY = 10;
const float rotFac = 0.03;
double scaleFac = 1.3;
const pair<float, float> scalingAbout = {500, 500};
double xi, yi;

void handleKey(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': {
            
        }
    }
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y) {

}

void handleDrag(int x, int y) {
    
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LIGHTING);

    // Set up light source parameters
    GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_dif[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat light_spc[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc);
    glEnable(GL_LIGHT0);

    // Set up material properties
    GLfloat mat_amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_dif[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_spc[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shin[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spc);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shin);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(-3.0, 0.8, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColor3f(0.54f, 0.27f, 0.07f);


    glBegin(GL_POLYGON);
    glVertex3d(1, 0, 1);
    glVertex3d(-1, 0, 1);
    glVertex3d(-1, 0, -1);
    glVertex3d(1, 0, -1);
    glEnd();

    glFlush();
}

void menuFunc(int value) {
    cout << value << endl;
}

int main(int argc, char** argv) {
    coords.push_back({400, 400});
    coords.push_back({400, 600});
    coords.push_back({600, 600});
    coords.push_back({600, 400});

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowSize(1280, 1440);
    glutInitWindowPosition(1280, 0);

    glutCreateWindow("Q1");

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 800/600.0, 0.1, 100.0);

    glClearColor(0.3, 0.92, 1.0, 1.0);

    // gluOrtho2D(0.0, 1000.0, 0.0, 1125.0);
    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKey);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleDrag);

    int menuID = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Menu Item 1", 1);
    glutAddMenuEntry("Menu Item 2", 2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}