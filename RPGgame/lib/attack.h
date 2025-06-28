#ifndef _BULLET_H_
#define _BULLET_H_

#include "base/collusion.h"
#include <wtypes.h>

namespace role {
	class Emeny;
}

namespace atk {
	class Attack {
	private:
		coll::POINT point;
		int length;
		int width;
		int power;
		DWORD time;
		coll::Rectangle* collBox;
	public:
		Attack(const std::string url, const std::string name);
		~Attack();

		void CheckCollusion(role::Emeny& __character);

		bool CheckAlive();

		void Draw() const;
	};
}

#endif // !_BULLET_H_
