#ifndef TFLAG_H
#define TFLAG_H

#include "TVector.h"
#include "TDefine.h"

typedef GLfloat(FUNC1)(GLfloat);
typedef GLfloat(FUNC2)(GLfloat, GLfloat);

class TFlag {
public:
	TFlag(TVector pos, GLfloat height, const GLfloat c[] = TColor::thistle);
	void display();
	void setColor(const GLfloat[3]);
	void updateScopes(FUNC1);
	void updateScopes(FUNC2, GLfloat);
	void powScopes(GLfloat);
private:
	TVector pos;
	GLfloat height;
	const GLfloat *color;
	GLfloat ***points;		// Points���񶥵�����
	GLfloat *scopes;		// ��ʾ�����xֵ�����

	const GLfloat fineness = 40;			// ��ʾϸ΢�̶�
	const GLfloat cue_radius = 0.02;		//ָ����˰뾶
	const GLfloat scope = 1.0 / 4;			//�����첨��ʱ�ķ���
	const int scope_len = fineness * 2;
	const GLfloat flag_w = 1.5, flag_h = flag_w*0.618;		//ָ�����ӵĿ��

	const int count_limit = 16;		// ָ�����β��˵��˶��ٶ�
	int count;				// ��count==wiggle_countʱ��һ��
};

#endif