# RPGgame

made by pyke-elysia;

### ���

һ��RPG���͵�2DС��Ϸ����һ����飨���ܻ��аɣ��������ڻ�û�У���ˬ��ս�������ܻ��аɣ���������û�У���
˿��2D�ܿᣨ���ܻ��аɣ���������û�У���

### ��������

#### 2025 / 6 / 27

֮ǰ����������һ����������ɡ�

ʵ����Collusion��������Rectangle;

```
#include "lib/collusion.h"
coll::CollusionBox collusionBoxExample;
coll::CollusionRectangle collusionRectangleExample;  //typedef CollusionRectangle Rectangle
coll::Rectangle rectangleExample;                    //typedef CollusionRectangle Rectangle
```

ʵ�ֳ������ scene;
Scene�๹�캯���е�jsonҪ������ļ�"RPGgame/src/test.json"

```
#include "lib/scene.h"
scene::Scene sceneExample("yourJSONconfigfile.json");
```

ʵ������� player
Player�๹�캯���е�jsonҪ������ļ�"RPGgame/src/character_test.json"�е�"player"

```
#include "lib/notnpc.h"
role::Player playerExample("yourJSONconfigfile.json");
```