#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Gost;
class Coin;
class Teki;
class Dassyu;
class Singou;
class Fade;
class Tuika;
class NextStage;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void GameRizaruto();
	bool Start();
	void Render(RenderContext& rc);
	//���̃v���O�����̊֐�
	Game* game=nullptr;
	BackGround* background=nullptr;
	Player* player=nullptr;
	GameCamera* gamecamera=nullptr;
	SkyCube* skycube = nullptr;
	Gost* gost = nullptr;
	Coin* coin = nullptr;
	Teki* teki=nullptr;
	Dassyu* dassyu = nullptr;
	Singou* singou = nullptr;
    SoundSource* soundsource = nullptr;
    Tuika* tuika=nullptr;
	Fade* fade=nullptr;
	NextStage* nextStage = nullptr;
	SoundSource* soundSource = nullptr;
	//�w�i
	int	skycubeType = enSkyCubeType_Night;
	int time = 0;
	int debag = 0;
	int debag2 = 0;
	int coinGet=0;
	int coinRe;
	FontRender fontRender;
	FontRender fontRender2;
	FontRender TimeRender;
	FontRender coinRender;
	SpriteRender startRender;
	SpriteRender koinRender;
	//���̃X�v���C�g
	SpriteRender yazirusi;
	Vector3 yazirusipos=Vector3::Zero;

	
	int timecount;
	int debagcount = 0;
	int debagcount2 = 0;
	Gost* gost1;
	LevelRender leverRender;
	int coincount=0;//�R�C���̖���
private:
	SpriteRender modelRender;
	Vector3 pos = Vector3::One;
	//��̏�����
	void Initsky();
	Vector3 syadou=Vector3({ 1.0f, 1.0f, 1.0f });
};

