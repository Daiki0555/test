#pragma once
class Game;
class Player;

class Coin:public IGameObject
{
public:
	Coin();
	~Coin();
	bool Start();
	void Update();
	void Rotaition();
	void CoinGet();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& pos)
	{
		position = pos * 10.0f;
	
	}
	void AddPosition(const Vector3& pos) {
		position += pos;
	}
	void SetScale(const Vector3& scal)
	{
		scale = scal*7.0f;

	}
	void SetRotaition(const Quaternion& rotaition)
	{
		rot = rotaition;
	}
	int State = 0;
	bool coinState = true;
	ModelRender modelRender;
	Quaternion rot;
	Quaternion qAddRot;
	SoundSource* soundSource = nullptr;
	Vector3 position;//座標
	Vector3 scale;//大きさ
	Vector3 diff;//ベクトル
	Player* player = nullptr;
	Game* game = nullptr;
	bool coinget = false;
	float jumpSpeed = 0.0f;
	float jumcoin = 0.0f;
};

