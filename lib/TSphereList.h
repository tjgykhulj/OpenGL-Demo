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
	TSphereList(GLfloat l, int stop_size = 0, int move_size = 6);	//箱体大小、鬼球数量、动球数量
	void display(bool hitFlag);
	void hitMother(const TVector &spd);
	void resetMother();

	GLfloat mother_r = 0.2, golden_r = 0.1, normal_r = 0.2;
private:
	int stop_size, move_size;
	int size;
	TSphere **sphere;
	TSphere *mother;
	GLUquadricObj *qObj;								// 使用二次几何体创建球
	GLfloat l;
};
#endif