#include "scene.h"
#include "json/json.h"
#include <string>
#include <fstream>
#include <cassert>
#include <graphics.h>

namespace scene {
	Object::Object(coll::POINT point, int length, int width, int diff) {
		this->point = point;
		this->length = length;
		this->width = width;
		this->CollBox = new coll::Rectangle(point.x, point.y, length - diff, width - diff);
	}
	Object::~Object() {
		//printf("before delete Obj\n");
		if(this->CollBox != nullptr)
			delete CollBox, this->CollBox = nullptr;
	}
	coll::Rectangle* Object::GetCollBox() const {
		return this->CollBox;
	}
	void Object::Draw() const {
		coll::POINT __point = this->point;
		__point.x -= this->length / 2;
		__point.y -= this->width / 2;
		setfillcolor(WHITE);
		fillrectangle(__point.x, __point.y, __point.x + length, __point.y + width);
	}

	Scene::Scene(const std::string url) {
		std::ifstream ifs;
		ifs.open(url);
		assert(ifs.is_open());

		Json::Reader reader;
		Json::Value root;

		if (!reader.parse(ifs, root, false)) {
			std::cout << "parse failed";
		}

		for (auto it : root["list"]) {
			coll::POINT __point = { it["pointx"].asInt(), it["pointy"].asInt() };
			int __length = it["length"].asInt();
			int __width = it["width"].asInt();
			int __diff = it["diff"].asInt();
			this->ObjList.push_back(new Object(__point, __length, __width, __diff));
		}

		for (auto it : root["emenylist"]) {
			this->EmyList.push_back(new role::Emeny(it.asString()));
		}

		ifs.close();
	}
	Scene::~Scene() {
		//printf("start to delete\n");
		for (int i = this->ObjList.size() - 1; i >= 0; i--) {
			auto it = this->ObjList[i];
			this->ObjList.pop_back();
			//printf("before delete OBJ\n");
			if(it != nullptr)
				delete it;
		}
		for (int i = this->EmyList.size() - 1; i >= 0; i--) {
			auto it = this->EmyList[i];
			//printf("before delete Emy\n");
			this->EmyList.pop_back();
			if (it != nullptr)
				delete it;
		}
	}

	void Scene::EmenyMove() {
		for (auto it : this->EmyList) {
			it->Move();
		}
	}

	void Scene::CheckCollusion(role::character& __character) {
		for (auto it : this->ObjList) {
			__character.CheckCollusion((it->GetCollBox()));
		}
	}
	void Scene::CheckCollusion() {
		for (auto __obj : this->ObjList)
			for (auto __emy : this->EmyList)
				__emy->CheckCollusion(__obj->GetCollBox());
	}
	void Scene::CheckCollusion(std::vector<atk::Attack*>& atkList) {
		for (auto __atk : atkList)
			for (auto __emy : this->EmyList)
				__atk->CheckCollusion(*(__emy));
	}
	void Scene::AttackPlayer(role::Player& player) {
		for (auto it : this->EmyList) {
			it->AttackPlayer(player);
		}
	}

	void Scene::CheckEmenyAlive() {
		for (auto it : this->EmyList) {
			if (!it->CheckAlive()) {
				auto T = it;
				std::swap(it, this->EmyList.back());
				this->EmyList.pop_back();
				if(T != nullptr)
				    delete T;
			}
		}
	}

	void Scene::Draw() {
		for (auto it : this->ObjList) {
			it->Draw();
		}
		for (auto it : this->EmyList) {
			it->Draw();
		}
	}
}