# RPGgame

made by pyke-elysia;

## ***EasyX + cppJSON***

### ���


һ��RPG���͵�2DС��Ϸ����һ����飨���ܻ��аɣ��������ڻ�û�У���ˬ��ս�������ܻ��аɣ���������û�У���
˿��2D�ܿᣨ���ܻ��аɣ���������û�У���

### ע��

����Ŀʹ�����ⲿ���ļ�cppjson�������а�װ

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

#### 2025 / 6 / 28

ʵ��Emeny, Attack(��δ����)�������˲�����ײ����뷴�����ų�����Scene��ʵ���� delete/���� ʱǱ�ڵ��ڴ�������⡣

ʵ��Emeny
Emeny�๹�캯���е�jsonҪ������ļ�"RPGgame/src/character_test.json"�е�"emeny"

```
#include "lib/notnpc.h"
role::Emeny emenyExample("yourJSONconfigfile.json");
```

ʵ��Attack
Attack�๹�캯���е�jsonҪ������ļ�"RPGgame/src/attack.json"

```
#include "lib/attack.h"
atk::Attack attackExample("yourJSONconfigfile.json");
```