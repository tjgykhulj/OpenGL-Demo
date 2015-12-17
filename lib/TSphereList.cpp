#include "TSphereList.h"

TSphereList::TSphereList(GLfloat l, int stop_size, int move_size) {	//l为墙壁-l~l的范围
	//创建曲面
	this->qObj = gluNewQuadric();							// 创建一个二次几何体
	gluQuadricNormals(this->qObj, GL_SMOOTH);				// 使用平滑法线
	gluQuadricTexture(this->qObj, GL_TRUE);					// 使用纹理
	//设置随机
	srand((unsigned)time(NULL));
	//设置静止球、动球数量，并初始化它们与母球
	this->l = l;
	this->stop_size = stop_size;
	this->move_size = move_size;
	this->size = stop_size + move_size + 1;
	this->sphere = new TSphere*[size];
	for (int i = 0; i < size - 1; i++)
	{
		GLfloat sx = 0, sz = 0;
		sphere[i] = new TSphere;
		if (i < stop_size) sphere[i]->setColor(TColor::royal_blue);
		else {
			sx = random_double(1) * 0.001;
			sz = random_double(1) * 0.001;
		}
		bool flag;
		do {						//不断随机位置，直到不与前面的球相交为止
			flag = false;
			sphere[i]->init(random_double(l - normal_r), random_double(l - normal_r), normal_r, sx, sz);
			for (int j = 0; j < i; j++)
				if (sphere[i]->isIntersect(sphere[j])) {
					flag = true; break;
				}
		} while (flag);
	}
	//设置金色飞球
	sphere[size - 1] = new TFlySphere;
	sphere[size - 1]->init(1, 2, golden_r);
	sphere[size - 1]->setColor(TColor::golden);
	//设置白色母球
	this->mother = new TSphere;
	this->mother->init(0, 0, mother_r, 0, 0);
	this->mother->setColor(TColor::white);
}

void TSphereList::display(bool hitFlag) {
	mother->display(qObj, l);
	for (int i = 0; i < size; i++) sphere[i]->display(qObj, l);
	if (!hitFlag) return;
	for (int i = 0; i < size; i++)
		if (mother->isIntersect(sphere[i]))	//碰撞检测
		{
			TVector C(mother->pos, sphere[i]->pos);	//计算两个圆心间的单位向量
			C = C / C.length();
			sphere[i]->pos = mother->pos + C*(mother->radius + sphere[i]->radius);	//利用向量将两圆从相交移为相切

			TVector A(mother->spd), B(sphere[i]->spd);
			TVector AC = C * (A * C);
			TVector BC = C * (B * C);
			GLfloat AM = pow(mother->radius, 3);
			GLfloat BM = pow(sphere[i]->radius, 3);
			TVector A2 = A - AC + (AC*(AM - BM) + BC * BM * 2) / (AM + BM);
			TVector B2 = B - BC + (BC*(BM - AM) + AC * AM * 2) / (AM + BM);
			mother->setSpd(A2.x, 0, A2.z);
			sphere[i]->setSpd(B2.x, 0, B2.z);
		}
}

void TSphereList::hitMother(const TVector &spd) {
	mother->setSpd(spd.x, 0, spd.z);
}
void TSphereList::resetMother() {
	this->mother->init(0, 0, mother_r, 0, 0);
}
