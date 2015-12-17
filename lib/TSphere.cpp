#include "TSphere.h"

TSphere::TSphere() {
	setColor(TColor::crimson_red); color[3] = 0.8;
};

void TSphere::init(GLfloat X, GLfloat Z, GLfloat R, GLfloat sx, GLfloat sz)
{
	radius = R; zrot = 0;
	pos.set(X, R+EPS, Z);
	setSpd(sx, 0, sz);
}

void TSphere::setSpd(GLfloat sx, GLfloat sy, GLfloat sz)
{
	spd.set(sx, sy, sz);
	angle = atan2f(-sz, sx) * 180 / PI;
	zrot_spd = -spd.length() / radius * 180 / PI;
}

void TSphere::setColor(const GLfloat c[3])
{
	for (int i = 0; i < 3; i++) color[i] = c[i];
}

void TSphere::display(GLUquadricObj *q, GLfloat l) {
	glPushMatrix();
	{
		glColor4fv(color);
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(angle, 0, 1, 0);
		glRotatef(zrot, 0, 0, 1);

		gluSphere(q, radius, 32, 16);					// ������
		/*
		glBindTexture(GL_TEXTURE_2D, texture[2]);				// ����Ϊ��������
		glColor4f(1.0f, 1.0f, 1.0f, 0.4f);					// ʹ��alphaΪ40%�İ�ɫ
		glEnable(GL_BLEND);						// ���û��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// ��ԭ��ɫ��40%��Ŀ����ɫ���
		glEnable(GL_TEXTURE_GEN_S);						// ʹ����ӳ��
		glEnable(GL_TEXTURE_GEN_T);
		gluSphere(q, radius, 32, 16);					// �������壬�����
		glDisable(GL_TEXTURE_GEN_S);					// ��OpenGL�ص�Ĭ�ϵ�����
		glDisable(GL_TEXTURE_GEN_T);
		*/
	}
	glPopMatrix();
	move(l);
}

bool TSphere::isIntersect(TSphere *sth) {
	GLfloat dis2 = 0;
	for (int i = 0; i < 3; i++) dis2 += pow(pos[i] - sth->pos[i], 2);
	return sqrt(dis2) <= radius + sth->radius;
}

void TSphere::move(GLfloat l) {
	zrot += zrot_spd;
	GLfloat temp = l - radius;
	for (int i = 0; i < 3; i++) {
		pos[i] += spd[i];
		if (pos[i] <= -temp || pos[i] >= temp)
		{
			spd[i] = -spd[i];
			setSpd(spd.x, 0, spd.z);
			if (pos[i] >= temp) pos[i] = temp - EPS; else pos[i] = -temp + EPS;
		}
	}
}



TFlySphere::TFlySphere(int size) :TSphere() {
	sleep = false;
	rand_size = size;
	random = new GLfloat[rand_size];
	for (int i = 0; i < rand_size; i++) random[i] = random_double(1)*0.003;
}

void TFlySphere::move(GLfloat l) {
	GLfloat temp = l - radius;
	count++;
	if ((count & 127) == 0) {			//ÿ��xx�ε���״̬������yy�εı�����������Ϣ����������ٶ�
		if ((count & 4095) == 0)
			change_status();
		else
			if (!sleep)
				for (int i = 0; i < 3; i++) spd[i] += random[rand_pos++], rand_pos %= rand_size;
			else {
				spd.x *= 0.9; spd.y -= 0.001;
				spd.z *= 0.9;
				zrot_spd = -sqrt(spd.x*spd.x + spd.z*spd.z) / radius * 180 / PI;
			}
	}
	zrot += zrot_spd;
	for (int i = 0; i < 3; i++) {
		pos[i] += spd[i];
		if (pos[i] >= temp || pos[i] <= -temp) {
			spd[i] = -spd[i] / 2;
			if (sleep) setSpd(spd.x, 0, spd.z);
			if (pos[i] <= -temp) pos[i] = -temp + EPS; else pos[i] = temp - EPS;
		}
	}
	if (pos.y < radius) {
		pos.y = radius;
		if (!sleep) spd.y = -spd.y / 2;
	}
}

void TFlySphere::change_status() {
	sleep = !sleep;
	zrot_spd = angle = 0;
	spd.y = -0.005;
	if (sleep) 
		angle = atan2f(-spd.z, spd.x) * 180 / PI;
}