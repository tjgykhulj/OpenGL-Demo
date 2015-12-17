#ifndef TCUE_H
#define TCUE_H

#include <gl\glut.h>
#include "TVector.h"
#include "TDefine.h"

class TCue {
public:
	TCue(GLfloat mother_r, GLfloat box_len);

	void reset();
	void display();
	void keepHolding();
	bool keepRelease();
	void setRot(GLfloat x, GLfloat y);
	const TVector &getSpd();
private:
	TVector spd;
	TVector rot;
	GLfloat base, dis, rate = 0.01;
	GLfloat radius = 0.04, len = 3;
};

#endif