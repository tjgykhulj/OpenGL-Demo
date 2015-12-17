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
	glNewList(box, GL_COMPILE);				// 创建显示列表
	glBegin(GL_QUADS);						// 开始绘制
	glColor4f(1, 1, 1, 0.1);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-l, 0, l);	// 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(l, 0, l);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(l, h, l);		// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-l, h, l);	// 纹理和四边形的左上
	// 后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-l, 0, -l);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-l, h, -l);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(l, h, -l);	// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(l, 0, -l);	// 纹理和四边形的左下
	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(l, 0, -l);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(l, h, -l);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(l, h, l);		// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(l, 0, l);	// 纹理和四边形的左下
	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-l, 0, -l);	// 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-l, 0, l);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-l, h, l);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-l, h, -l);	// 纹理和四边形的左上
	// 底面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-l, 0, l);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-l, 0, -l);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(l, 0, -l);	// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(l, 0, l);	// 纹理和四边形的左下
	glEnd();
	glEndList();
}