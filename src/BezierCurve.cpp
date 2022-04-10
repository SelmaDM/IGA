#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


static float min[] = { -1.0, -1.0, -1.0 };
static float max[] = { 1.0, 1.0, 1.0 };
static float orthoMax[3], orthoMin[3];
static int windowWidth, windowHeight;
double nbSegments;
static GLfloat points[100][3];
static int numPoints = 0;
static int selectedPoint = -1;

/**
 * Return the squared Euclidean distance between two points.
 */
GLfloat distanceSquared(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2,
                        GLfloat y2, GLfloat z2) {
  GLfloat d;

  d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);

  return d;
}

/**
 * Find the closest point controlling the curve.
 *
 * @param x   The x-coordinate to compare to
 * @param y   The y-coordinate to compare to
 * @param z   The z-coordinate to compare to
 */
int closestPointTo(GLfloat x, GLfloat y, GLfloat z) {
  GLfloat d, min;
  int index;

  index = -1;

  if (numPoints > 0) {
    min = distanceSquared(points[0][0], points[0][1], points[0][2], x, y, z);
    index = 0;

    for (int i = 1; i < numPoints; i++) {
      d = distanceSquared(points[i][0], points[i][1], points[i][2], x, y, z);

      if (d < min) {
        index = i;
        min = d;
      }
    }
  }

  return index;
}

/**
 * Convert from screen coordinates (in pixels) to model
 * coordinates.
 *
 * @param x   The x-coordinate in pixels (IN)
 * @param y   The y-coordinate in pixels (IN)
 * @param fx  The converted x coordinate (OUT)
 * @param fy  The converted y coordinate (OUT)
 */
void screen2ortho(int x, int y, GLfloat &fx, GLfloat &fy)
{
  fx = orthoMin[0] + (float)x/(float)windowWidth *
  (orthoMax[0] - orthoMin[0]);

  fy = orthoMin[1] + (float)(windowHeight - y)/(float)windowHeight *
  (orthoMax[1] - orthoMin[1]);
}

/**
 * The display callback
 */
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Make the Model-View matrix active
  glMatrixMode(GL_MODELVIEW);
  // Initialize the Model-View matrix
  glLoadIdentity();

  // Set the color
  glColor3f(1.0, 0.0, 0.0);
  // Set the point size
  glPointSize(3.);



  //[curve.
  //
  // Create and draw the curves for every 4 points
  for (int i = 0; (i + 3) < numPoints; i += 3) {
    // The evaluator with a stride of 3 and an order of 4
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &points[i][0]);

    // Draw the curve
   
    // Produce a set of uniformly spaced parameter values
    // Number of equal subdivisions over the range from u1 to u2
   
    glBegin(GL_LINE_STRIP);  // GL_POINTS can also be used
    {
      for (int i = 0; i < nbSegments; i++) {
      glEvalCoord1f(((float) i) / nbSegments);
      
      

      }
    }
    glEnd();
  }



  //]curve.

  //[points.
  // Show the points
  glBegin(GL_POINTS);
  {
    for (int i = 0; i < numPoints; i++) {
      if (i == selectedPoint) {
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
      } else {
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
      }
    }
    glEnd();
  }

  // Connect the points (using a piecewise linear curve)
  if (numPoints >= 2) {
    glColor3f(0.8, 0.2, 0.3);
    glBegin(GL_LINE_STRIP);
    {
      for (int i = 0; i < numPoints; i++) {
        glVertex3f(points[i][0], points[i][1], points[i][2]);
      }
    }
    glEnd();
  }
  //]points.

  glFlush();
  // Handle the double buffering
  glutSwapBuffers();
}

//[motion.
/**
 * The mouse drag callback
 *
 * @param x      The x-position of the mouse
 * @param y      The y-position of the mouse
 */
void motion(int x, int y) {
  GLfloat fx, fy;

  screen2ortho(x, y, fx, fy);

  if (selectedPoint >= 0) {
    points[selectedPoint][0] = fx;
    points[selectedPoint][1] = fy;

    glutPostRedisplay();
  }
}
//]motion.

//[mouse.
/**
 * The mouse callback (i.e., the function that is called
 * each time a mouse button is pressed or released).
 *
 * @param button The button (e.g., GLUT_LEFT_BUTTON)
 * @param state  The state (e.g., GLUT_UP or GLUT_DOWN)
 * @param x      The x-position of the mouse
 * @param y      The y-position of the mouse
 */
void mouse(int button, int state, int x, int y) {
  GLfloat fx, fy;

  screen2ortho(x, y, fx, fy);

  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      points[numPoints][0] = fx;
      points[numPoints][1] = fy;
      points[numPoints][2] = 0.;

      numPoints++;

      glutPostRedisplay();
    }
  } else if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
      selectedPoint = closestPointTo(fx, fy, 0.0);
    } else {
      selectedPoint = -1;
    }

    glutPostRedisplay();
  }
}
//]mouse.

/**
 * The reshape callback (i.e., the function that is called
 * each time the window is re-sized).
 *
 * @param width   The new width
 * @param height  The new height
 */
void reshape(int width, int height) {
  float max3D, min3D;
  GLfloat aspect;

  windowWidth = width;
  windowHeight = height;

  // Set the viewport
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);

  // Make the projection matrix current
  glMatrixMode(GL_PROJECTION);

  // Clear the projection matrix
  glLoadIdentity();

  // Find the largest and smallest values for all coordinates
  min3D = min[0];
  max3D = max[0];
  for (int i = 1; i < 3; i++) {
    if (min[i] < min3D)
      min3D = min[i];
    if (max[i] > max3D)
      max3D = max[i];
  }
  if (fabs(min3D) > max3D)
    max3D = fabs(min3D);
  min3D = -max3D;

  // Set the projection matrix (based on the aspect ratio)
  if (width <= height) {
    aspect = (GLfloat) height / (GLfloat) width;
    orthoMin[0] = min3D;
    orthoMax[0] = max3D;
    orthoMin[1] = min3D * aspect;
    orthoMax[1] = max3D * aspect;
    orthoMin[2] = min3D;
    orthoMax[2] = max3D;
  } else {
    aspect = (GLfloat) width / (GLfloat) height;
    orthoMin[0] = min3D * aspect;
    orthoMax[0] = max3D * aspect;
    orthoMin[1] = min3D;
    orthoMax[1] = max3D;
    orthoMin[2] = min3D;
    orthoMax[2] = max3D;
  }
  glOrtho(orthoMin[0], orthoMax[0], orthoMin[1], orthoMax[1], orthoMin[2],
          orthoMax[2]);

  // Make the Model-View matrix active
  glMatrixMode(GL_MODELVIEW);
}

/**
 * The entry point of the application.
 *
 * @param argc  The number of command line arguments
 * @param argv  The array of command line arguments
 * @return      A status code
 */
int main(int argc, char **argv) {
    std::cout <<"Please indicate the number of segments ";

    while(1)
    {
    scanf("%lf",&nbSegments);
    break;
    }
    windowWidth = 500;
    windowHeight = 500;  

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("Bezier Curve");

  // Callbacks
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMotionFunc(motion);
  glutMouseFunc(mouse);

  // Enable necesssary functionality
  glClearColor(0,0,0,0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  // Enable the 1-dimensional evaluator
  glEnable(GL_MAP1_VERTEX_3);

  // Start the event loop
  glutMainLoop();
}
