#ifndef TBOX_H
#define TBOX_H

#include <gl\glut.h>

class TBox {
public:
	TBox(int len = 5);
	void display();
private:
	GLint	box, l, h;
	GLvoid BuildLists();
};

#endif