#ifndef TDEFINE_H
#define TDEFINE_H

#include <time.h>
#include <cstdlib>
#include "TVector.h"
#include "SOIL.h"
#pragma comment(lib, "lib/SOIL.lib")

static GLfloat random_double(GLfloat x) { return 2 * x * rand() / RAND_MAX - x; }

const GLfloat PI = 3.141592635897;
const GLfloat EPS = 1e-4;
const GLfloat LightAmb[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 环境光
const GLfloat LightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 漫射光
const GLfloat LightPos[] = { 7.0f, 7.0f, 0.0f, 1.0f };	// 漫射光位置
const int stop_sphere_size = 6;
const int move_sphere_size = 6;
const int box_len = 4;

extern int now_height;
extern int now_width;
extern bool keys[];									// Array Used For The Keyboard Routine

#define new_color(name, r, g, b) const GLfloat name[3] = {r/255.0, g/255.0, b/255.0}

namespace TColor {
	const GLfloat white[3] = { 1.0f, 1.0f, 1.0f };
	const GLfloat black[3] = { 0.0f, 0.0f, 0.0f };
	const GLfloat red[3] = { 1.0f, 0.0f, 0.0f };
	const GLfloat green[3] = { 0.0f, 1.0f, 0.0f };
	const GLfloat blue[3] = { 0.0f, 0.0f, 1.0f };
	const GLfloat voilet[3] = { 1.0f, 0.0f, 1.0f };
	const GLfloat yellow[3] = { 1.0f, 1.0f, 0.0f };
	new_color(orange, 255, 165, 0);
	new_color(golden, 255, 215, 0);
	new_color(thistle, 216, 191, 216);
	new_color(royal_blue, 65, 105, 255);
	new_color(hot_pink, 255, 105, 180);
	new_color(crimson_red, 220, 20, 60);
	new_color(pink, 255, 192, 203);
	new_color(dodgerBlue1, 30, 144, 255);
}

#endif