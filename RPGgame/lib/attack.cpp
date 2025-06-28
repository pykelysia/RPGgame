#include "attack.h"
#include "json/json.h"
#include <fstream>
#include <cassert>
#include <graphics.h>
#include "notnpc.h"

namespace atk {
	Attack::Attack(const std::string url, const std::string name) {
		std::ifstream ifs;
		ifs.open(url);
		assert(ifs.is_open());

		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(ifs, root, false)) {
			std::cout << "parse failed";
		}

		Json::Value __atkData = root[name];
		this->point = { __atkData["point"][0].asInt(), __atkData["point"][1].asInt() };
		this->length = __atkData["length"].asInt();
		this->width = __atkData["width"].asInt();
		this->power = __atkData["power"].asInt();
		this->time = GetTickCount();
		int diff = __atkData["diff"].asInt();
		this->collBox = new coll::Rectangle(this->point.x, this->point.y, this->length - diff, this->width - diff);

		ifs.close();
	}
	Attack::~Attack() {
		if(this->collBox != nullptr)
			delete this->collBox, this->collBox = nullptr;
	}

	void Attack::CheckCollusion(role::Emeny& __character) {

		coll::Rectangle R = *(__character.GetCollBox());
		int deltaX = this->collBox->GetPoint().x - R.GetPoint().x;
		int deltaY = this->collBox->GetPoint().y - R.GetPoint().y;
		deltaX = abs(deltaX);
		deltaY = abs(deltaY);
		int X = this->collBox->GetLength() / 2 + R.GetLength() / 2;
		int Y = this->collBox->GetWidth() / 2 + R.GetWidth() / 2;
		if (deltaX < X && deltaY < Y) {
			__character.Hurt(this->power);
		}
	}

	bool Attack::CheckAlive() {
		DWORD T = GetTickCount();
		if (T - this->time >= 200)
			return false;
		return true;
	}

	void Attack::Draw() const {
		coll::POINT __point = this->point;
		__point.x -= this->length / 2;
		__point.y -= this->width / 2;
		setfillcolor(RED);
		fillrectangle(__point.x, __point.y, __point.x + length, __point.y + width);
	}
}