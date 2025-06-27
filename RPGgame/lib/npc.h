#ifndef _NPC_H_
#define _NPC_H_

#include "character.h"

namespace role {
	typedef class NoPlayerCharacter : public character {
	private:
	public:
		bool CheckCollusion(coll::Rectangle& __box) override;
	} npc;
}

#endif // !_NPC_H_
