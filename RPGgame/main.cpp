#include<graphics.h>
#include<stdio.h>
//#include "lib/std.h"
#include "lib/collusion.h"

int main() {

	//initgraph(1280, 640);

	//while (true) {
	//	//��¼ʱ��
	//	mystd::TIME start = mystd::GetTimeCount();



	//	//����֡��
	//	mystd::TIME end = mystd::GetTimeCount();
	//	auto delta = end - start;
	//	if (delta < 1000 / 144) {
	//		Sleep(DWORD(1000 / 144 - delta));
	//	}
	//}

	//closegraph();

	coll::CollusionBox a();
	coll::CollusionRectangle b(1,2,2,2);

	return 0;  
}