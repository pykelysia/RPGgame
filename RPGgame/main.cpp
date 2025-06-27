#include<graphics.h>
#include<stdio.h>
#include "lib/std.h"
#include "lib/scene.h"
#include "lib/notnpc.h"

int main() {

	initgraph(1280, 640, 1);

	mystd::TIME time;

	scene::Scene test("src/test.json");
	role::Player player("src/character_test.json");

	ExMessage msg;
	BeginBatchDraw();

	while (true) {

		cleardevice();

	//	//记录时间
		mystd::Time startTime = time.Value();

		while (peekmessage(&msg)) {
			player.ProcessEvent(msg);
		}

		player.Move();
		test.CheckCollusion(player);
		test.Draw();
		player.Draw();

		FlushBatchDraw();

	//	//控制帧率
		mystd::Time endTime = time.Value();
		mystd::Time delta = endTime - startTime;
		if (delta < 1000 / 144) {
			Sleep(DWORD(1000 / 144 - delta));
		}
	}

	EndBatchDraw();

	closegraph();

	//coll::CollusionBox a();
	//coll::CollusionRectangle b(1,2,2,2);

	return 0;  
}