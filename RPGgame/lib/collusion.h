#ifndef _COLLUSION_H_
#define _COLLUSION_H_
#include <iostream>
namespace coll {
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
		void SetOnlyOne(int t, char c);//c in 'l' and 'w'
		bool UseCollusion(const CollusionRectangle& R);
		bool UseCollusion(const CollusionCircle& C);
	} Rectangle;
	
	typedef class CollusionCircle : public CollusionBox {
	private:
		double radius;
	public:
		CollusionCircle(int x, int y, double radius);
		double GetRadius() const;
		void Reset(double radius);
		bool UseCollusion(const CollusionRectangle& R);
		bool UseCollusion(const CollusionCircle& C);
	} Circle;
}
#endif // !_COLLUSION_H_