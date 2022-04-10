#include <GL/glut.h>
#include <stdio.h>


class BezierCurve
{
	public:

	GLfloat distanceSquared(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	int 	closestPointTo(GLfloat, GLfloat, GLfloat);
	void 	screen2ortho(int, int, GLfloat, GLfloat);
	void 	display();
	void 	motion(int, int);
	void 	mouse(int, int, int, int);
	void 	reshape(int, int);

};