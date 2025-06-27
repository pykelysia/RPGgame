#include "character.h"
#include <iostream>
#include <graphics.h>

namespace role {
	character::character(coll::POINT point, int length, int width, int diff) {
		this->point = point;
		this->length = length;
		this->width = width;
		this->velocity = { 0, 1 };
		this->collBox = new coll::Rectangle(point.x, point.y, length - diff, width - diff);
	}
	character::~character() {
		delete this->collBox;
	}
	bool character::CheckCollusion(coll::Rectangle* __box) {
		int _dir = __box->UseCollusion(*(this->collBox));
		switch (_dir) {
		case coll::dir::up:
			this->velocity.y = -this->velocity.y;
			break;
		case coll::dir::down:
			this->velocity.y = 0;
			break;
		case coll::dir::left:
		case coll::dir::right:
			this->velocity.x = 0;
			break;
		default:
			break;
		}
		return true;
	}

	void character::Move() {
		this->point.y += velocity.y;
		this->collBox->SetOnlyOne(this->point.y, 'y');
	}

	void character::Draw() {
		coll::POINT __point = this->point;
		__point.x -= this->length / 2;
		__point.y -= this->width / 2;
		setfillcolor(RED);
		fillrectangle(__point.x, __point.y, __point.x + length, __point.y + width);
	}
}