#pragma once
#include "collision/CollisionObject.h"
class Player;
class Tuika;
class Gost:public IGameObject
{
public:
	Gost();
	~Gost();
	bool Start();
	void Update();
	//ModelRender modelRender;
	CollisionObject* colliOb;
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& pos)
	{
		position = pos*10.0f;
		
	}
	void AddPosition(const Vector3& pos) {
		position += pos;
	}
	void SetRotation(const Quaternion& rotation)
	{
		rot = rotation;
	}
	void SetScale(const Vector3& scal)
	{
		Scale = scal*10.0f;
	}
	Player* player = nullptr;
	Tuika* tuika = nullptr;
private:
	Vector3 position;
	Vector3 Scale;
	Quaternion rot;
};

