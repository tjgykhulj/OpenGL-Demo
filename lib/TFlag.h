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
	GLfloat ***points;		// Points网格顶点数组
	GLfloat *scopes;		// 表示深度随x值的起伏

	const GLfloat fineness = 40;			// 表示细微程度
	const GLfloat cue_radius = 0.02;		//指定旗杆半径
	const GLfloat scope = 1.0 / 4;			//控制旗波动时的幅度
	const int scope_len = fineness * 2;
	const GLfloat flag_w = 1.5, flag_h = flag_w*0.618;		//指定旗子的宽高

	const int count_limit = 16;		// 指定旗形波浪的运动速度
	int count;				// 当count==wiggle_count时波一下
};

#endif