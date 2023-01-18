#pragma once

#include "collision/CollisionObject.h"

class BackGround;
class Gost;
class Coin;
class Teki;
class Dassyu;
class Singou;
class Tuika;
class NextStage;
class GameEnd;
class Game;
class Player :public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move();//�ړ�
	void Jump();//�W�����v
	void Grabity();//�d��
	void Grabityky();//�d�͂̏ꏊ�w��
	void Rot();//��]
	void Anime();//�A�j���[�V����
	void Render(RenderContext& rc);
	//�����o�ϐ�
	ModelRender modelRender;
	//���W�f�[�^
	Vector3 position = Vector3::One;//�L�����N�^�[�̍��W
	Vector3 collisionPosition = Vector3::Zero;//�R���W�����̍��W
	//�N�H�[�^�j�I��
	Quaternion rotation;//�L�����̉�]
	Quaternion collirot;//�R���W�����̉�]
	enum EnAnimationClip {//�A�j���[�V����
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Down,
		enAnimationClip_Num,
	};
	const Vector3& GetPosition()const
	{
		return position;
	}

	void SetPosition(const Vector3 &pos) 
	{
		position = pos;
	}

	AnimationClip animClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v

	
	Vector3 moveSpeed = Vector3::Zero;
	int playerState = 0;//�v���C���[�X�e�C�g
	int GrabityState = 0;//�d�͂̕��� 0=�� 1=�E 2=�� 3=��
	Vector3 stickL=Vector3::Zero;
	
	Game* game;
	CollisionObject* collisionObject;//�R���W����
	BackGround* backGround;//�w�i
	Gost* gost;//����
	Dassyu* dassyu;//�_�b�V��
	Singou* singou;
	Tuika* tuika = nullptr;
	PointLight* pointLight = nullptr;
	NextStage* nextStage=nullptr;
	GameEnd* gameend;
	SoundSource* soundSource = nullptr;
	float rezarutoTime = 0.50f;
	float rezarutoTime2 = 0.50f;
	float Gametime = 6.0f;
	float rakkaTime = 1.0f;
	float speed = 20.0f;//�v���C���[�̑��x
	float addSpeed=0.0f;
	float decgcount = 0;
	bool rakkaState = false;
	bool nextState = false;//���̃X�e�[�W���������ꂽ���ǂ���
	bool idouState = false;//���������ǂ���
	bool rezarutoState = false;
	bool timeState = false;
	Vector3 lightPosition;
	bool hitState = false;
}; 

