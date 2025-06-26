#include "std.h"
#include<graphics.h>
#include<math.h>

namespace mystd {
	TIME::TIME() {
		this->lastTime = GetTickCount();
		this->count = 0;
		this->time = this->lastTime;
	}
	Time TIME::Value() {
		this->Updata();
		return this->time;
	}
	void TIME::Updata() {
		DWORD mayTime = GetTickCount();
		if (mayTime < this->lastTime)
			count++;
		this->lastTime = mayTime;
		this->time = (Time)count * ULONG_MAX + this->lastTime;
	}
}