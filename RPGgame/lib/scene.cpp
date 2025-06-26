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
		delete CollBox;
	}
	coll::Rectangle Object::GetCollBox() const {
		return *(this->CollBox);
	}
	void Object::Draw() {
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

		ifs.close();
	}
	Scene::~Scene() {
		for (auto it : this->ObjList) {
			delete it;
		}
	}
	void Scene::Draw() {
		for (auto it : this->ObjList) {
			it->Draw();
		}
	}
}