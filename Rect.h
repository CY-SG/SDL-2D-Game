#pragma once
#include"Math.h"
struct Rect {
public:
	int x, y;
	int w, h;
	Rect(int x_, int y_, int w_, int h_) {
		x = x_;
		y = y_;
		w = w_;
		h = h_;
	}
	Rect(Vec2 pos, Vec2 size) {
		x = pos.x;
		y = pos.y;
		w = size.x;
		h = size.y;
	}
};