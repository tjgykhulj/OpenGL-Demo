#ifndef TCORE_H
#define TCORE_H

#include <windows.h>									// Header File For Windows
#include <gl\glut.h>
#include "TVector.h"
#include "TSphereList.h"
#include "TCue.h"
#include "TBox.h"
#include "TFlag.h"

class TCore {
public:
	TVector pos;
	TVector rot;
	GLuint	texture[3];							// ʹ����������
	TBox *box;
	TCue *cue;
	TFlag *flag[2];
	TSphereList *list;

	bool hitFlag = false;		//�Ƿ��ѻ���
	bool clickHold = false;		//�Ƿ񱣳ְ�ס���
	bool isClicked = false; // �Ƿ������
	bool isDragging = false; // �Ƿ��϶�

	void ProcessKeyboard();
	int InitGL(GLvoid);
	int DrawGLScene(GLvoid);
private:
	GLuint LoadTex(LPTSTR Filename);
};

#endif