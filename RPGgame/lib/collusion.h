#ifndef _COLLUSION_H_
#define _COLLUSION_H_
#include <iostream>
namespace coll {
	enum dir {
		up = 1,
		down,
		left,
		right
	};
	struct POINT {
		int x;
		int y;
	};
	//碰撞箱的基准坐标
	//是体积箱的中心坐标
	class CollusionBox {
	protected:
		POINT point;
	public:
		CollusionBox(int x, int y);
		POINT GetPoint() const;
		void SetPoint(POINT p);
		void SetOnlyOne(int t, char c);//c in 'x' and 'y'
		virtual int UseCollusion(CollusionBox& __box);
	};

	class CollusionRectangle;
	class CollusionCircle;

	typedef class CollusionRectangle : public CollusionBox {
	private:
		int length;//x
		int width;//y
	public:
		CollusionRectangle(int x, int y, int length, int width);
		int GetLength() const;//x
		int GetWidth() const;//y
		void Reset(int length, int width);//(x, y)
		void SetOne(int t, char c);//c in 'l' and 'w'
		int UseCollusion(CollusionRectangle& R);
	} Rectangle;
}
#endif // !_COLLUSION_H_