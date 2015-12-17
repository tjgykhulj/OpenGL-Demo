#ifndef TVECTOR_H
#define TVECTOR_H

#include <gl\glut.h>
#include <cmath>

struct TVector {
	GLfloat x, y, z;

	TVector();
	TVector(GLfloat X, GLfloat Y, GLfloat Z);
	TVector(TVector &v1, TVector &v2);
	void set(GLfloat X, GLfloat Y, GLfloat Z);

	GLfloat length();

	GLfloat operator *(TVector &sth);
	TVector operator +(TVector &sth);
	TVector operator -(TVector &sth);
	TVector operator *(GLfloat k);
	TVector operator /(GLfloat k);

	GLfloat &operator [](GLint k);
};

#endif