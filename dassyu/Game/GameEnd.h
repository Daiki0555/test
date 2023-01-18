#pragma once
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
class Title;
class GameEnd :public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	void Update();
	void Runk();
	void Render(RenderContext& rc);
	float alpha =0.5f;
	float runkScalse = 0.0f;
	float rendertime = 1.0f;
	int coinrizaruto;
	int metorRizarut;
	bool e_coinState = false;
	bool e_metorState = false;
	bool e_runkState = false;
	bool c_bg = false;
	bool m_bg=false;
	bool r_bg = false;
	bool e_bg = false;
	Vector3 rizascale = Vector3{0.0f,1.0f,1.0f};
	Vector3 rizascale2 = Vector3{ 0.0f,1.0f,1.0f };
	SpriteRender haikeiRender;
	SpriteRender spriteRender;
	SpriteRender spriteRender2;
	FontRender koinRender;
	FontRender metorRender;
	FontRender moziRender;
	FontRender RunkRender;
	Vector3 syadou = Vector3({ 1.0f, 1.0f, 1.0f });
	SoundSource* soundSource = nullptr;
	SoundSource* soundSource2 = nullptr;
	SoundSource* soundSource3 = nullptr;
	//ëºÇÃÉvÉçÉOÉâÉÄÇÃä÷êî
	Game* game = nullptr;
	BackGround* background = nullptr;
	Player* player = nullptr;
	GameCamera* gamecamera = nullptr;
	SkyCube* skycube = nullptr;
	Gost* gost = nullptr;
	Coin* coin = nullptr;
	Teki* teki = nullptr;
	Dassyu* dassyu = nullptr;
	Singou* singou = nullptr;
	SoundSource* soundsource = nullptr;
	Tuika* tuika = nullptr;
	Fade* fade = nullptr;
	NextStage* nextStage = nullptr;
	Title* title = nullptr;
};

