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
	GLuint	texture[3];							// 使用三个纹理
	TBox *box;
	TCue *cue;
	TFlag *flag[2];
	TSphereList *list;

	bool hitFlag = false;		//是否已击杆
	bool clickHold = false;		//是否保持按住鼠标
	bool isClicked = false; // 是否点击鼠标
	bool isDragging = false; // 是否拖动

	void ProcessKeyboard();
	int InitGL(GLvoid);
	int DrawGLScene(GLvoid);
private:
	GLuint LoadTex(LPTSTR Filename);
};

#endif