#pragma once
#include "collision/CollisionObject.h"
#include "Level3DRender/LevelRender.h"
class BackGround;
class Gost;
class Coin;
class Teki;
class Dassyu;
class Player;
class Tuika:public IGameObject
{
public:
	Tuika();
	~Tuika();
	bool Start();
	ModelRender modelRender;
	void Render(RenderContext& rc);
	void Update();
	void SetPosition(const Vector3& position)
	{
		m_pos = position * 10.0f;
	}
	void AddPosition(const Vector3& pos) {
		m_pos += pos;
	}
	//ƒŒƒxƒ‹‚Ì‰ñ“]
	void SetRotaition(const Quaternion& rotaition)
	{
		rot = rotaition;
	}
	void SetScale(const Vector3& scal)
	{
		Scale = scal * 10.0f;
	}
	//ƒRƒŠƒWƒ‡ƒ“
	CollisionObject *colliob;
	Vector3 colliPosi;
	Vector3 colliScale=Vector3(2000.0f,2000.0f,1000.0f);
	
	LevelRender  leverRender;
	BackGround* background = nullptr;
	Gost* gost = nullptr;
	Coin* coin = nullptr;
	Teki* teki = nullptr;
	Dassyu* dassyu = nullptr;
	Tuika* tuika = nullptr;
	Player* player = nullptr;

	float tuikaZahyou=1000.0f;
	Vector3 m_pos;
	Quaternion rot;
	Vector3 Scale;
	
	
};

