#ifndef TSPHERE_H
#define TSPHERE_H

#include <gl\glut.h>
#include <cmath>
#include "TVector.h"
#include "TDefine.h"

class TSphere {
public:
	TVector pos, spd;
	GLfloat angle, zrot_spd, zrot;
	GLfloat color[4];
	GLfloat radius;

	TSphere();
	void init(GLfloat X, GLfloat Z, GLfloat R, GLfloat sx = 0, GLfloat sz = 0);
	void setSpd(GLfloat sx, GLfloat sz, GLfloat sy=0);
	void setColor(const GLfloat c[3]);
	void display(GLUquadricObj *q, GLfloat box_len);
	bool isIntersect(TSphere *sth);
protected:
	virtual void move(GLfloat box_len);
};

class TFlySphere : public TSphere 
{
public:
	TFlySphere(int size = 1000);
protected:
	void move(GLfloat);
private:
	bool sleep = false;
	GLuint count = 0;

	int rand_size;
	int rand_pos = 0;
	GLfloat *random;

	void change_status();
};

#endif