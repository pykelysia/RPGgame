# RPGgame

made by pyke-elysia;

### 简介

一个RPG类型的2D小游戏，有一点剧情（可能会有吧，反正现在还没有），爽快战斗（可能会有吧，反正现在没有），
丝滑2D跑酷（可能会有吧，反正现在没有）。

### 开发过程

#### 2025 / 6 / 27

之前开发的内容一并放在这里吧。

实现了Collusion及其子类Rectangle;

```
#include "lib/collusion.h"
coll::CollusionBox collusionBoxExample;
coll::CollusionRectangle collusionRectangleExample;  //typedef CollusionRectangle Rectangle
coll::Rectangle rectangleExample;                    //typedef CollusionRectangle Rectangle
```

实现场景搭建类 scene;
Scene类构造函数中的json要求详见文件"RPGgame/src/test.json"

```
#include "lib/scene.h"
scene::Scene sceneExample("yourJSONconfigfile.json");
```

实现玩家类 player
Player类构造函数中的json要求详见文件"RPGgame/src/character_test.json"中的"player"

```
#include "lib/notnpc.h"
role::Player playerExample("yourJSONconfigfile.json");
```