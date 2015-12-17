#ifndef TSPHERE_LIST_H
#define TSPHERE_LIST_H

#include <gl\glut.h>
#include <time.h>
#include <cmath>
#include "TVector.h"
#include "TDefine.h"
#include "TSphere.h"

class TSphereList {
public:
	TSphereList(GLfloat l, int stop_size = 0, int move_size = 6);	//�����С��������������������
	void display(bool hitFlag);
	void hitMother(const TVector &spd);
	void resetMother();

	GLfloat mother_r = 0.2, golden_r = 0.1, normal_r = 0.2;
private:
	int stop_size, move_size;
	int size;
	TSphere **sphere;
	TSphere *mother;
	GLUquadricObj *qObj;								// ʹ�ö��μ����崴����
	GLfloat l;
};
#endif