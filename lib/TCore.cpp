#include "TCore.h"

void TCore::ProcessKeyboard()									// Process Keyboard Results
{
	if (keys['R']) {
		pos.set(0, -2, -10);
		rot.set(0, 0, 0);
	}
	if (keys['A']) pos.x += 0.01f;
	if (keys['D']) pos.x -= 0.01f;
	if (keys['W']) pos.y -= 0.01f;
	if (keys['S']) pos.y += 0.01f;
	if (keys['Q']) pos.z -= 0.01f;
	if (keys['E']) pos.z += 0.01f;
	if (keys[VK_UP]) rot.x += 0.05f;
	if (keys[VK_DOWN]) rot.x -= 0.05f;
	if (keys[VK_RIGHT]) rot.y -= 0.05f;
	if (keys[VK_LEFT]) rot.y += 0.05f;
	if (keys[VK_SPACE]) {
		list->resetMother();
		cue->reset();
		hitFlag = false;
	}
}

GLfloat add(GLfloat a, GLfloat b) {
	return a + b;
}

int TCore::InitGL(GLvoid)                              // �˴���ʼ��OpenGL������������  
{
	if (!(texture[0] = LoadTex("Wall.bmp")) ||				// ����ذ�ͼ��
		!(texture[1] = LoadTex("Ball.bmp")) ||
		!(texture[2] = LoadTex("Flag.bmp"))) return false;

	pos.set(0, -2, -12);
	rot.set(5, 0, 0);

	box = new TBox(box_len);
	list = new TSphereList(box_len, stop_sphere_size, move_sphere_size);
	cue = new TCue(list->mother_r, box_len);
	flag[0] = new TFlag(TVector(5, 0, 0), 5, TColor::dodgerBlue1);
	flag[1] = new TFlag(TVector(-5, 0, 0), 5, TColor::pink);
	flag[1]->updateScopes(add, 0.5);
	flag[1]->updateScopes(pow, 3);

	glShadeModel(GL_SMOOTH);                        // ������Ӱƽ��   
	glEnable(GL_BLEND);								// �򿪻��
	glEnable(GL_COLOR_MATERIAL);					//���ʸ��ٵ�ǰ��ͼɫ  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);						// ������Ȳ���  
	glEnable(GL_TEXTURE_2D);						// ��������ӳ��      
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);								// ������Ȼ���  
	glDepthFunc(GL_LEQUAL);                         // ������Ȳ��Ե�����  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // ����ϵͳ��͸�ӽ�������  


	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glEnable(GL_LIGHT0);

	return TRUE;                                // ��ʼ�� OK  
}

int TCore::DrawGLScene(GLvoid)									// Draw Everything
{
	if (!hitFlag) {	//��δ����ǰ�ж������
		if (isClicked) {
			clickHold = true;	//������겢��ס
			cue->keepHolding();
		}
		else if (clickHold && !cue->keepRelease()) {
			clickHold = false;
			hitFlag = true;
			list->hitMother(cue->getSpd());
		}
	}
	// Clear Screen, Depth Buffer & Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, 1, 0, 0);
	glRotatef(rot.y, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, texture[2]);			//����������
	for (int i = 0; i < 2; i++) flag[i]->display();

	glBindTexture(GL_TEXTURE_2D, texture[1]);			//�����������
	list->display(hitFlag);		//����������ײЧ��

	glBindTexture(GL_TEXTURE_2D, texture[0]);			//���ú�������
	if (!hitFlag) cue->display();
	glDepthMask(GL_FALSE);	//��Ϊֻ�������ڻ��ư�͸��
	box->display();
	glDepthMask(GL_TRUE);

	return TRUE;										// Everything Went OK
}

GLuint TCore::LoadTex(LPTSTR Filename)
{
	GLuint texture = SOIL_load_OGL_texture(Filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture == 0) return 0;
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	//glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//��s�����ϵĲ��Ʒ�ʽ
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//��t�����ϵĲ��Ʒ�ʽ
	return texture;
}