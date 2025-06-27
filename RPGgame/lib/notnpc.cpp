#include "notnpc.h"
#include <fstream>
#include <cassert>

namespace role {

	#define stateToNum(A) ((A) ? (1) : (-1))

	Player::Player(const std::string url) {
		std::ifstream ifs;
		ifs.open(url);
		assert(ifs.is_open());

		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(ifs, root, false)) {
			std::cout << "parse failed";
		}

		Json::Value player_test = root["player_test"];
		this->point = { player_test["point"][0].asInt(), player_test["point"][1].asInt() };
		this->length = player_test["length"].asInt();
		this->width = player_test["width"].asInt();
		int __diff = player_test["diff"].asInt();
		int __length = this->length - __diff;
		int __width = this->width - __diff;
		this->collBox = new coll::Rectangle(this->point.x, this->point.y, __length, __width);

		this->velocity = { 0, 1 };
		this->life = player_test["life"].asInt();
		this->attack = player_test["attack"].asInt();
		this->state = false;
		this->time = 0;
		ifs.close();
	}
	Player::~Player() {
		delete this->collBox;
	}
	void Player::ProcessEvent(ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode)
			{
			case VK_UP:
				if (this->velocity.y == 0) {
					this->state = true;
					this->velocity.y = -1;
					this->time = GetTickCount();
				}
				break;
			case VK_LEFT:
				if (this->velocity.x < 0)
					break;
				this->velocity.x = -1;
				break;
			case VK_RIGHT:
				if (this->velocity.x > 0)
					break;
				this->velocity.x = 1;
				break;
			default:
				break;
			}
		}
		else if (msg.message == WM_KEYUP) {
			switch (msg.vkcode)
			{
			case VK_LEFT:
				if (this->velocity.x != -1)
					break;
				this->velocity.x += 1;
				break;
			case VK_RIGHT:
				if (this->velocity.x != 1)
					break;
				this->velocity.x -= 1;
				break;
			default:
				break;
			}
		}
	}
	bool Player::CheckCollusion(coll::Rectangle* __box) {

		int __dir = __box->UseCollusion(*(this->collBox));
		switch (__dir) {
		case coll::dir::up:
			if (this->velocity.y < 0) {
				this->velocity.y = -this->velocity.y;
				this->state = false;
			}
			break;
		case coll::dir::down:
			if (this->velocity.y > 0)
				this->velocity.y = 0;
			break;
		case coll::dir::left:
			if (this->velocity.x < 0)
				this->velocity.x = 0;
			break;
		case coll::dir::right:
			if (this->velocity.x > 0)
				this->velocity.x = 0;
			break;
		default:
			break;
		}
		return true;
	}
	void Player::Move() {
		if (state) {
			DWORD temptime = GetTickCount();
			if (temptime - this->time >= 500) {
				this->state = false;
				this->velocity.y = -this->velocity.y;
			}
		}
		this->point.x += this->velocity.x * 5;
		this->point.y += this->velocity.y * 5;
		this->collBox->SetPoint({ this->point.x, this->point.y });
	}
}