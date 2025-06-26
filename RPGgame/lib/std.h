#pragma once
#include<math.h>

namespace mystd {

	typedef unsigned long long Time;

	class TIME {
	private:
		Time time;
		int count;
		unsigned long lastTime;
	public:
		TIME();
		Time Value();
		void Updata();
	};

}