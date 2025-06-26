#include<graphics.h>
#include<stdio.h>
#include "lib/std.h"
#include "lib/scene.h"

int main() {

	initgraph(1280, 640);

	mystd::TIME time;

	scene::Scene test("src/test.json");

	while (true) {
	//	//记录时间
		mystd::Time startTime = time.Value();

		test.Draw();

	//	//控制帧率
		mystd::Time endTime = time.Value();
		mystd::Time delta = endTime - startTime;
		if (delta < 1000 / 144) {
			Sleep(DWORD(1000 / 144 - delta));
		}
	}

	closegraph();

	//coll::CollusionBox a();
	//coll::CollusionRectangle b(1,2,2,2);

	return 0;  
}