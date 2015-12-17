#include "TCue.h"

TCue::TCue(GLfloat mother_r, GLfloat box_len) 
	: base(mother_r), len((box_len-mother_r)*0.9), dis(0.1) 
{
}

void TCue::reset() {
	dis = 0.1;
	rot.set(0, 0, 0);
}

void TCue::display() {
	glPushMatrix();
	{
		static GLUquadricObj *q = 0;
		if (!q) q = gluNewQuadric();
		glColor4f(1, 1, 1, 1);
		glRotatef(rot.y, 0, 1, 0);
		glRotatef(rot.x, 1, 0, 0);
		glTranslatef(0, base, base + dis);
		gluCylinder(q, radius, radius, len, 32, 1);
	}
	glPopMatrix();
}
void TCue::keepHolding() {
	if (dis < 2) dis += 0.005;
	spd.set(-dis * sinf(rot.y / 180 * PI) * rate, 0, -dis * cos(rot.y / 180 * PI) * rate);	//ËÙ¶È
}
bool TCue::keepRelease() {
	if (dis >= 0.03) {
		dis -= 0.03; return true;
	}
	return false;
}

void TCue::setRot(GLfloat x, GLfloat y) {
	rot.set(x, y, 0);
}
const TVector& TCue::getSpd() { return spd; }