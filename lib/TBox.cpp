#include "TBox.h"

TBox::TBox(int len) {
	l = len;
	h = l / 2;
	BuildLists();
}
void TBox::display() {
	glCallList(box);
}

GLvoid TBox::BuildLists() {
	box = glGenLists(1);
	glNewList(box, GL_COMPILE);				// ������ʾ�б�
	glBegin(GL_QUADS);						// ��ʼ����
	glColor4f(1, 1, 1, 0.1);
	// ǰ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-l, 0, l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(l, 0, l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(l, h, l);		// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-l, h, l);	// ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-l, 0, -l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-l, h, -l);	// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(l, h, -l);	// ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(l, 0, -l);	// ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(l, 0, -l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(l, h, -l);	// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(l, h, l);		// ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(l, 0, l);	// ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-l, 0, -l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-l, 0, l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-l, h, l);	// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-l, h, -l);	// ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-l, 0, l);	// ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-l, 0, -l);	// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(l, 0, -l);	// ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(l, 0, l);	// ������ı��ε�����
	glEnd();
	glEndList();
}