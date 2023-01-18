#pragma once
class Player;
class Dassyu;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	Player* player = nullptr;
	Dassyu* dassyu=nullptr;
	Quaternion camerarot;
	Vector3 toCameraPos;//注視点から視点に向かう
	Vector3 ownCameraPos;//一人称用カメラ
	Vector3 pos;//カメラ座標
	Vector3 cameraPos=Vector3::Zero;

};

