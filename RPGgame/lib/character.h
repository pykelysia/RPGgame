#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "collusion.h"
#include "json/json.h"
#include <string>
#include <graphics.h>

namespace role {
	struct Velocity {
		int x;
		int y;
	};

	class character {
	protected:
		coll::POINT point;
		int length;
		int width;
		coll::Rectangle* collBox;
		Velocity velocity;
	public:
		character(const std::string url);
		character(coll::POINT point = {0, 0}, int length = 0, int width = 0, int diff = 10);
		~character();

		virtual bool CheckCollusion(coll::Rectangle* __box);
		void Move();
		void Draw();
	};
}

#endif // ! _CHARACTER_H_