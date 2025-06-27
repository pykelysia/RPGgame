#ifndef _SCENE_H_
#define _SCENE_H_

#include "collusion.h"
#include "character.h"
#include<vector>
#include<string>

namespace scene {

	class Object {
	private:
		coll::POINT point;
		int length;  // usual bigger than 10
		int width;   // usual bigger than 10
		coll::Rectangle* CollBox;
	public:
		Object(coll::POINT point = { 0, 0 }, int length = 0, int width = 0, int diff = 0);
		~Object();
		coll::Rectangle* GetCollBox() const;
		void Draw();
	};
	class Scene {
	private:
		std::vector<Object*> ObjList;
	public:
		Scene(const std::string url);
		~Scene();

		void CheckCollusion(role::character& __character);
		// character.CheckCollusion( auto it : this->ObjList )

		void Draw();
	};
}

#endif // !_SCENE_H_