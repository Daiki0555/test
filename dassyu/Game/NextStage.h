#pragma once
#include "Level3DRender/LevelRender.h"
class BackGround;
class Gost;
class Coin;
class Teki;
class Dassyu;
class Player;
class Tuika;
class NextStage:public IGameObject
{
public:
	NextStage();
	~NextStage();
	bool Start();
	void Update();
	void NextSt(Vector3 pos);
	int stagerand=1;
	BackGround* background = nullptr;
	Gost* gost = nullptr;
	Coin* coin = nullptr;
	Teki* teki = nullptr;
	Dassyu* dassyu = nullptr;
	Tuika* tuika = nullptr;
	Player* player = nullptr;
	LevelRender* leverRender;
};

