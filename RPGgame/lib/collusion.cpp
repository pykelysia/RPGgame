#include "collusion.h"
#include <math.h>

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
	void CollusionRectangle::SetOnlyOne(int t, char c) {
		switch (c) {
		case 'l':
			this->length = t;
		case 'w':
			this->width = t;
		default:
			break;
		}
	}
	bool CollusionRectangle::UseCollusion(const CollusionRectangle& R) {
		POINT p = R.GetPoint();
		int deltaX = Max(this->point.x, p.x) - Min(this->point.x, p.x);
		int deltaY = Max(this->point.y, p.y) - Min(this->point.y, p.y);
		if (deltaX > this->length / 2 + R.GetLength() / 2)
			return false;
		if (deltaY > this->width / 2 + R.GetWidth() / 2)
			return false;
		return true;
	}
	bool CollusionRectangle::UseCollusion(const CollusionCircle& C) {
		POINT p = C.GetPoint();
		int deltaX = Max(this->point.x, p.x) - Min(this->point.x, p.x);
		int deltaY = Max(this->point.y, p.y) - Min(this->point.y, p.y);
		if (deltaX > this->length / 2 + C.GetRadius())
			return false;
		if (deltaY > this->width / 2 + C.GetRadius())
			return false;

		deltaX -= this->length / 2, deltaY -= this->width / 2;
		if (deltaX > 0 && deltaY > 0){
			double l = sqrt(U2(deltaX) + U2(deltaY));
			if (l > C.GetRadius())
				return false;
		}
		return true;
	}

	CollusionCircle::CollusionCircle(int x = 0, int y = 0, double radius = 0) {
		this->point.x = x;
		this->point.y = y;
		this->radius = radius;
	}
	double CollusionCircle::GetRadius() const { return this->radius; }
	void CollusionCircle::Reset(double radius) { this->radius = radius; }
	bool CollusionCircle::UseCollusion(const CollusionRectangle& R) {
		POINT p = R.GetPoint();
		int deltaX = Max(this->point.x, p.x) - Min(this->point.x, p.x);
		int deltaY = Max(this->point.y, p.y) - Min(this->point.y, p.y);
		if (deltaX > this->radius + R.GetLength() / 2)
			return false;
		if (deltaY > this->radius + R.GetWidth() / 2)
			return false;

		deltaX -= R.GetLength()/ 2, deltaY -= R.GetWidth() / 2;
		if (deltaX > 0 && deltaY > 0) {
			double l = sqrt(U2(deltaX) + U2(deltaY));
			if (l > this->radius)
				return false;
		}
		return true;
	}
	bool CollusionCircle::UseCollusion(const CollusionCircle& C) {
		int deltaX = Max(this->point.x, C.point.x) - Min(this->point.x, C.point.x);
		int deltaY = Max(this->point.y, C.point.y) - Min(this->point.y, C.point.y);
		double delta = sqrt(U2(deltaX) + U2(deltaY));
		if (delta > this->radius + C.radius)
			return false;
		return true;
	}
}