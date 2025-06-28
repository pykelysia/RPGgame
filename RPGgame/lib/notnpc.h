#ifndef _NOTNPC_H_
#define _NOTNPC_H_

#include "base/character.h"
#include "attack.h"
#include <vector>
namespace role {

	class Player : public character {
	private:
		int life;
		bool state;     // true: uping;  false: downing
						// if dont moving, state = downing;
		DWORD time;		// the start of jumping;
	public:
		Player(const std::string url);
		~Player() override;

		void ProcessEvent(ExMessage& msg);
		bool CheckCollusion(coll::Rectangle* __box) override;
		void Move();
		void Hurt(int attack);
		bool CheckAlive() const;
		void Attack(std::vector<atk::Attack*>* list);
	};


	class Emeny : public character {
	private:
		int life;
		int attack;
		int start;
		int end;

	public:
		Emeny(const std::string url);
		~Emeny() override;

		bool CheckCollusion(coll::Rectangle* __box) override;  // Óë»·¾³Åö×²
		bool AttackPlayer(Player& __player);
		void Move();
		void Hurt(int __attack);
		bool CheckAlive() const;
	};
}

#endif // !_NOTNPC_H_
