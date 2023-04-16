#include <GL/glut.h>
#include <GL/glu.h>

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw a red triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    // Flush the rendering pipeline
    glFlush();
}

int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set up the window
    glutInitWindowSize(800, 600);
    glutCreateWindow("My OpenGL Application");

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 800/600.0, 0.1, 100.0);

    // Set the background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Set the display callback function
    glutDisplayFunc(display);

    // Start the main loop
    glutMainLoop();
    return 0;
}