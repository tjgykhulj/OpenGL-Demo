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

int TCore::InitGL(GLvoid)                              // 此处开始对OpenGL进行所有设置  
{
	if (!(texture[0] = LoadTex("Wall.bmp")) ||				// 载入地板图像
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

	glShadeModel(GL_SMOOTH);                        // 启用阴影平滑   
	glEnable(GL_BLEND);								// 打开混合
	glEnable(GL_COLOR_MATERIAL);					//材质跟踪当前绘图色  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);						// 启用深度测试  
	glEnable(GL_TEXTURE_2D);						// 启用纹理映射      
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);								// 设置深度缓存  
	glDepthFunc(GL_LEQUAL);                         // 所作深度测试的类型  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // 告诉系统对透视进行修正  


	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glEnable(GL_LIGHT0);

	return TRUE;                                // 初始化 OK  
}

int TCore::DrawGLScene(GLvoid)									// Draw Everything
{
	if (!hitFlag) {	//还未击杆前判断鼠标点击
		if (isClicked) {
			clickHold = true;	//点下鼠标并按住
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

	glBindTexture(GL_TEXTURE_2D, texture[2]);			//设置旗纹理
	for (int i = 0; i < 2; i++) flag[i]->display();

	glBindTexture(GL_TEXTURE_2D, texture[1]);			//设置球的纹理
	list->display(hitFlag);		//打击后才有碰撞效果

	glBindTexture(GL_TEXTURE_2D, texture[0]);			//设置盒子纹理
	if (!hitFlag) cue->display();
	glDepthMask(GL_FALSE);	//设为只读，用于绘制半透明
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
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//在s方向上的缠绕方式
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//在t方向上的缠绕方式
	return texture;
}