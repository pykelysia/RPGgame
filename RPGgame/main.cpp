#include<graphics.h>
#include<stdio.h>
#include "lib/std.h"
#include "lib/scene.h"
#include "lib/notnpc.h"
#include "lib/attack.h"

int main() {

	initgraph(1280, 640, 1);

	mystd::TIME time;

	scene::Scene* test = new scene::Scene("src/test.json");
	role::Player* player = new role::Player("src/character_test.json");
	std::vector<atk::Attack*> atkList;


	ExMessage msg;
	BeginBatchDraw();

	while (true) {

		//记录时间
		mystd::Time startTime = time.Value();

		//接收信息
		while (peekmessage(&msg)) {
			player->ProcessEvent(msg);
		}

		//处理计算
		player->Move();
		test->EmenyMove();

		//检测碰撞
		test->CheckCollusion(*player);      // 确保player与环境的碰撞
		test->CheckCollusion();			  // 确保emeny和npc与环境的碰撞
		test->CheckCollusion(atkList);    // 检测attack和emeny的碰撞
		test->AttackPlayer(*player);        // 检测emeny和player的碰撞

		//检测存活情况
		if (!player->CheckAlive()) {
			break;
		}
		test->CheckEmenyAlive();
		for (int i = 0; i < atkList.size(); i++) {
			auto it = atkList[i];
			if (!it->CheckAlive()) {
				std::swap(atkList[i], atkList.back());
				atkList.pop_back();
				if(it != nullptr)
					delete it;
			}
		}

		// 绘图
		cleardevice();

		test->Draw();
		player->Draw();
		for (auto it : atkList) {
			it->Draw();
		}

		FlushBatchDraw();

		//控制帧率
		mystd::Time endTime = time.Value();
		mystd::Time delta = endTime - startTime;
		if (delta < 1000 / 144) {
			Sleep(DWORD(1000 / 144 - delta));
		}
	}

	EndBatchDraw();

	closegraph();
	//printf("END_______");

	delete player;
	delete test;
	//printf("--------------------------------------------");

	return 0;  
}