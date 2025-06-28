#include "notnpc.h"
#include <fstream>
#include <cassert>

namespace role {

#define abs(A) ((A) > 0 ? (A) : -(A))

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
		this->state = false;
		this->time = 0;
		ifs.close();
	}
	Player::~Player() {
		//printf("before delete player->collBox\n");
		if(this->collBox != nullptr)
			delete this->collBox, this->collBox = nullptr;
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
	void Player::Hurt(int __attack) {
		//printf("hurt: %d\n", __attack);
		this->life -= __attack;
	}
	bool Player::CheckAlive() const {
		return this->life > 0 ? true : false;
	}
	void Player::Attack(std::vector<atk::Attack*>* list) {
		list->push_back(new atk::Attack("src/attack", "attack_1"));
	}

	Emeny::Emeny(const std::string url) {
		std::ifstream ifs;
		ifs.open(url);
		assert(ifs.is_open());

		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(ifs, root, false)) {
			std::cout << "parse failed";
		}

		Json::Value emeny = root["emeny_test"];
		this->point = { emeny["point"][0].asInt(), emeny["point"][1].asInt() };
		this->length = emeny["length"].asInt();
		this->width = emeny["width"].asInt();
		int __diff = emeny["diff"].asInt();
		int __length = this->length - __diff;
		int __width = this->width - __diff;
		this->collBox = new coll::Rectangle(this->point.x, this->point.y, __length, __width);

		this->velocity = { 1, 1 };
		this->life = emeny["life"].asInt();
		this->attack = emeny["attack"].asInt();
		this->start = emeny["start"].asInt();
		this->end = emeny["end"].asInt();
		ifs.close();
	}
	Emeny::~Emeny() {
		if(this->collBox != nullptr)
			delete this->collBox, this->collBox = nullptr;
	}

	bool Emeny::CheckCollusion(coll::Rectangle* __box) {
		int __dir = __box->UseCollusion(*(this->collBox));
		switch (__dir) {
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
	bool Emeny::AttackPlayer(Player& __player) {
		coll::Rectangle R = *(__player.GetCollBox());
		int deltaX = this->collBox->GetPoint().x - R.GetPoint().x;
		int deltaY = this->collBox->GetPoint().y - R.GetPoint().y;
		deltaX = abs(deltaX);
		deltaY = abs(deltaY);
		int X = this->collBox->GetLength() / 2 + R.GetLength() / 2;
		int Y = this->collBox->GetWidth() / 2 + R.GetWidth() / 2;
		if (deltaX < X && deltaY < Y) {
			__player.Hurt(this->attack);
			return true;
		}
		return false;
	}
	void Emeny::Move() {
		this->point.x += this->velocity.x * 3;
		this->point.y += this->velocity.y * 5;
		this->collBox->SetPoint(coll::POINT{ this->point.x, this->point.y });
		int now = this->point.x;
		if (this->velocity.x > 0 && now >= this->end)
			this->velocity.x = -this->velocity.x;
		if (this->velocity.x < 0 && now <= this->start)
			this->velocity.x = -this->velocity.x;
	}
	void Emeny::Hurt(int __attack) {
		this->life -= __attack;
	}
	bool Emeny::CheckAlive() const {
		return this->life > 0 ? true : false;
	}
}