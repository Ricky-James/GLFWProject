#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:

	Vector2 pos = { 0.f, -0.875f }; //Center co-ord for paddle
	const float paddleWidth = 0.15f;
	const float paddleHeight = 0.02f;
	const float paddleSpeed = 0.03f;

public:

	void drawPaddle() const;
	Paddle operator++(const int x);
	Paddle operator--(const int x);

};

