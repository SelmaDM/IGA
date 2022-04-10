#include <iostream>
#include <GL/glut.h>

#include <cmath>

using namespace std;

GLfloat interPoints[4][3];
float inverseMBxMp[4][4] = { {1, 0, 0, 0},{-0.833, 3, -1.5, 0.333},{0.333, -1.5, 3, -0.8333},{0, 0, 0, 1} };

GLfloat p4[4][4][3] =
{ {{0.0,-0.9,0.0},{-0.8,-0.7,0.6},{-0.8,-0.4,0.8},{0.0,0.0,0.9}},
{{-0.8,-0.5,-0.3},{-0.8,-0.3,0.1},{-0.8,-0.1,0.5},{-0.8,0.2,0.6}},
{{-0.8,-0.2,-0.5},{-0.8,-0.1,-0.3},{-0.8,0.3,0.2},{-0.8,0.6,0.2}},
{{0.0,0.0,-0.9},{-0.8,0.4,-0.8},{-0.8,0.7,-0.6},{0.0,0.9,0.0}} };


int mode;
const float COLOR[] = { 0.5, 0.2, 0.5 };
bool camera = false;

void init()
{
	glClearColor(COLOR[0], COLOR[1], COLOR[2], COLOR[3]);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (camera)
		{
			glRotatef(60, 0.0, 1.0, 0.0);
		}
		else
		{
			glRotatef(-60.0, 0.0, 1.0, 0.0);
		}
		//Grid 
		glColor3f(0.8, 0.8, 0.1);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &p4[0][0][0]);
		//glEvalMesh2(GL_FILL, 0, 20, 0, 20);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		
		//Control points 
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 0; j <= 3; j++)
			{
				glColor3f(1.0, 0.5, 0.0);
				glPointSize(6);
				glBegin(GL_POINTS);
				glVertex3f(p4[i][j][0], p4[i][j][1], p4[i][j][2]);
				glEnd();
			}
		}
		//Control polygone
		glColor3f(0.0, 0.7, 1.0);
		glBegin(GL_LINES);
		glVertex3f(p4[0][0][0], p4[0][0][1], p4[0][0][2]);
		glVertex3f(p4[3][0][0], p4[3][0][1], p4[3][0][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p4[0][3][0], p4[0][3][1], p4[0][3][2]);
		glVertex3f(p4[3][3][0], p4[3][3][1], p4[3][3][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p4[3][0][0], p4[3][0][1], p4[3][0][2]);
		glVertex3f(p4[3][3][0], p4[3][3][1], p4[3][3][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p4[0][3][0], p4[0][3][1], p4[0][3][2]);
		glVertex3f(p4[0][0][0], p4[0][0][1], p4[0][0][2]);
		glEnd();

	glutSwapBuffers();
	return;
}

void menu(int choose)
{
	if (choose != 5)
	{
		mode = choose;
		glutPostRedisplay();
	}

}

int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("Bezier Surface");
	glutCreateMenu(menu);
	glutAddMenuEntry("Exit", 5);

	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

}
