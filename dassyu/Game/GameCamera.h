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
	Vector3 toCameraPos;//�����_���王�_�Ɍ�����
	Vector3 ownCameraPos;//��l�̗p�J����
	Vector3 pos;//�J�������W
	Vector3 cameraPos=Vector3::Zero;

};

