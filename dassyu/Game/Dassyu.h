#pragma once
class Player;
class Tuika;
class GameCamera;
class Teki;
class Dassyu:public IGameObject
{
public:
	~Dassyu();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender modelRender;
	Player* player;
	GameCamera* gacame;
	Tuika* tuika = nullptr;
	Teki* teki = nullptr;
	SoundSource* soundSource = nullptr;
	//���x���̃|�W�V����
	void SetPosition(const Vector3& pos)
	{
		position = pos * 10.0f;

	}
	void AddPosition(const Vector3& pos) {
		position += pos;
	}
	//���x���̉�]
	void SetRotation(const Quaternion& rotaition)
	{
		rot = rotaition;
	}
	void SetScale(const Vector3& scal)
	{
		Scale = scal * 10.0f;
	}
	bool DassyuState = true;
	bool dasyuBG = false;
	float DassyuTime = 3.0f;
private:
	Vector3 position;
	Quaternion rot;
	Vector3 Scale;

};

