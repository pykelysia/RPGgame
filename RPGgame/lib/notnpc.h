#ifndef _NOTNPC_H_
#define _NOTNPC_H_

#include "character.h"
#include "attack.h"
#include <vector>
#include "std.h"
namespace role {
	class Emeny : public character {

	};

	class Player : public character {
	private:
		int life;
		int attack;
		bool state;     // true: uping;  false: downing
						// if dont moving, state = downing;
		DWORD time;		// the start of jumping;
	public:
		Player(const std::string url);
		~Player();

		void ProcessEvent(ExMessage& msg);
		bool CheckCollusion(coll::Rectangle* __box) override;
		void Move();
		void Hurt();
		void Attack(std::vector<atk::Attack*> list);
	};
}

#endif // !_NOTNPC_H_
