#pragma once
class Player;
class Singou:public IGameObject
{
public:
	~Singou();
	bool Start();
	void Update();
	void SingouState();
	void Render(RenderContext& rc);
	int singou = 0;
	int singoucount = 4;//�M���̒l
	Player* player=nullptr;
	SpriteRender startRender;
	SoundSource* soundSource = nullptr;
	SoundSource* soundSource2 = nullptr;
};

