#include "TFlag.h"

void TFlag::setColor(const GLfloat c[3]) { this->color = c; }

TFlag::TFlag(TVector pos, GLfloat height, const GLfloat color[3]) : count(0)
{
	this->pos = pos;
	this->height = height;
	this->color = color;

	scopes = new GLfloat[scope_len];	//ӳ�䵽sin(-PI��PI֮��)��ֵ
	for (int x = 0; x < scope_len; x++) {
		GLfloat t = (((x + 1) / (GLfloat)scope_len * 2.0) - 1) * PI;
		scopes[x] = sin(t);
	}

	points = new GLfloat**[(int)fineness];
	for (int x = 0; x < fineness; x++)
	{
		points[x] = new GLfloat*[(int)fineness];
		for (int y = 0; y < fineness; y++)
		{
			points[x][y] = new GLfloat[3];
			points[x][y][0] = (((x+1) / fineness) - 1) * flag_w;
			points[x][y][1] = (((y+1) / fineness) - 1) * flag_h;
			points[x][y][2] = scopes[x] * scope;
		}
	}
}

void TFlag::display() 
{
	float float_x, float_y, float_xb, float_yb;
	glPushMatrix();
	{
		glColor3fv(TColor::thistle);
		glTranslatef(pos.x, pos.y, pos.z);	//�ƶ����˵�λ��
		static GLUquadricObj *q = 0;
		if (!q) q = gluNewQuadric();
		glRotatef(-90, 1, 0, 0);
		gluCylinder(q, cue_radius, cue_radius, height, 20, 1);
		glRotatef(90, 1, 0, 0);

		glColor4fv(color);
		glTranslatef(-cue_radius, height, -points[(int)fineness - 1][0][2]);
		glBegin(GL_QUADS);					// �ı��λ��ƿ�ʼ
		for (int x = 0; x < fineness - 1; x++)				// �� X ƽ�� 0-44 ѭ��(45��)
		{
			for (int y = 0; y < fineness - 1; y++)			// �� Y ƽ�� 0-44 ѭ��(45��)
			{
				float_x = float(x) / fineness;		// ����X����ֵ
				float_y = float(y) / fineness;		// ����Y����ֵ
				float_xb = float(x + 1) / fineness;		// X����ֵ+0.0227f
				float_yb = float(y + 1) / fineness;		// Y����ֵ+0.0227f

				glTexCoord2f(float_x, float_y);	// ��һ���������� (���½�)
				glVertex3fv(points[x][y]);
				glTexCoord2f(float_x, float_yb);	// �ڶ����������� (���Ͻ�)
				glVertex3fv(points[x][y + 1]);
				glTexCoord2f(float_xb, float_yb);	// �������������� (���Ͻ�)
				glVertex3fv(points[x + 1][y + 1]);
				glTexCoord2f(float_xb, float_y);	// ���ĸ��������� (���½�)
				glVertex3fv(points[x + 1][y]);
			}
		}
		glEnd();					// �ı��λ��ƽ���
		if (++count == count_limit) {
			count = 0;
			GLfloat hold = scopes[0];	//����scopes����������
			for (int x = 0; x < scope_len - 1; x++) scopes[x] = scopes[x + 1];
			scopes[scope_len - 1] = hold;

			for (int x = 0; x < fineness; x++)
				for (int y = 0; y < fineness; y++) points[x][y][2] = scopes[x] * scope;
		}
	}
	glPopMatrix();
}

void TFlag::updateScopes(FUNC1 func) {
	for (int x = 0; x < scope_len; x++) scopes[x] = func(scopes[x]);
}
void TFlag::updateScopes(FUNC2 func, GLfloat c) {
	for (int x = 0; x < scope_len; x++) scopes[x] = func(scopes[x], c);
}