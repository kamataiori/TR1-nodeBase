#pragma once
#include "Vector2.h"
#include "Result.h"
#include <Result.h>

struct Line
{
	Vector2 Start;
	Vector2 End;
	unsigned int color;
};

struct SplitLine
{
	Vector2 Start;
	Vector2 End;
	unsigned int color;
};

struct Particle {
	Vector2 pos[500];
	Vector2 acceleration[500];
	bool isShot[500];
	int radius[500];
};

struct BackGround {
	//座標
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;

	//中心点
	Vector2 center;

	//縦幅
	float heghtlength;

	//横幅
	float widelength;
};

struct PaBackGround {
	//座標
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;

	//中心点
	Vector2 center;

	//縦幅
	float heghtlength;

	//横幅
	float widelength;
};

struct Box
{
	//座標
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;

	//中心点
	Vector2 center;

	//縦幅
	float heghtlength;

	//横幅
	float widelength;

};
