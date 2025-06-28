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

		//��¼ʱ��
		mystd::Time startTime = time.Value();

		//������Ϣ
		while (peekmessage(&msg)) {
			player->ProcessEvent(msg);
		}

		//�������
		player->Move();
		test->EmenyMove();

		//�����ײ
		test->CheckCollusion(*player);      // ȷ��player�뻷������ײ
		test->CheckCollusion();			  // ȷ��emeny��npc�뻷������ײ
		test->CheckCollusion(atkList);    // ���attack��emeny����ײ
		test->AttackPlayer(*player);        // ���emeny��player����ײ

		//��������
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

		// ��ͼ
		cleardevice();

		test->Draw();
		player->Draw();
		for (auto it : atkList) {
			it->Draw();
		}

		FlushBatchDraw();

		//����֡��
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