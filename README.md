# RPGgame

made by pyke-elysia;

## ***EasyX + cppJSON***

### 简介


一个RPG类型的2D小游戏，有一点剧情（可能会有吧，反正现在还没有），爽快战斗（可能会有吧，反正现在没有），
丝滑2D跑酷（可能会有吧，反正现在没有）。

### 注意

本项目使用了外部库文件cppjson，需自行安装

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

#### 2025 / 6 / 28

实现Emeny, Attack(尚未测试)。更新了部分碰撞检测与反馈，排除了在Scene类实例在 delete/析构 时潜在的内存溢出问题。

实现Emeny
Emeny类构造函数中的json要求详见文件"RPGgame/src/character_test.json"中的"emeny"

```
#include "lib/notnpc.h"
role::Emeny emenyExample("yourJSONconfigfile.json");
```

实现Attack
Attack类构造函数中的json要求详见文件"RPGgame/src/attack.json"

```
#include "lib/attack.h"
atk::Attack attackExample("yourJSONconfigfile.json");
```