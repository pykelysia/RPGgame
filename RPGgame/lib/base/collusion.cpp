#include "collusion.h"
#include <math.h>
#include <iostream>

namespace coll {
#define Max(A, B) ((A) > (B) ? (A) : (B))
#define Min(A, B) ((A) < (B) ? (A) : (B))
#define U2(A) ((double)(A) * (double)(A))

	using std::sqrt;

	CollusionBox::CollusionBox(int x = 0, int y = 0) {
		this->point.x = x;
		this->point.y = y;
	}
	POINT CollusionBox::GetPoint() const { return this->point; }
	void CollusionBox::SetPoint(POINT p) { this->point = p; }
	void CollusionBox::SetOnlyOne(int t, char c) {
		switch (c)
		{
		case 'x':
			this->point.x = t;
		case 'y':
			this->point.y = t;
		default:
			break;
		}
	}
	int CollusionBox::UseCollusion(CollusionBox& __box){
		printf("there is no definition");
		return false;
	}

	CollusionRectangle::CollusionRectangle(int x = 0, int y = 0, int length = 0, int width = 0) {
		this->point.x = x;
		this->point.y = y;
		this->length = length;
		this->width = width;
	}
	int CollusionRectangle::GetLength() const { return this->length; }
	int CollusionRectangle::GetWidth() const { return this->width; }
	void CollusionRectangle::Reset(int length, int width) {
		this->length = length;
		this->width = width;
	}
	void CollusionRectangle::SetOne(int t, char c) {
		switch (c) {
		case 'l':
			this->length = t;
		case 'w':
			this->width = t;
		default:
			break;
		}
	}
	int CollusionRectangle::UseCollusion( CollusionRectangle& R) {
		POINT p = R.GetPoint();
		int X = this->length / 2 + R.GetLength() / 2;
		int Y = this->width / 2 + R.GetWidth() / 2;
		int deltaX = Max(this->point.x, p.x) - Min(this->point.x, p.x);
		int deltaY = Max(this->point.y, p.y) - Min(this->point.y, p.y);

		if (deltaX >= X) return 0;
		if (deltaY >= Y) return 0;
		if (deltaY < Y) {
			if (this->point.y > p.y)
				return dir::down;
			else
				return dir::up;
		}
		else {
		printf("@");
			if (this->point.x > p.x)
				return dir::right;
			else
				return dir::left;
		}
		return 0;
	}
}