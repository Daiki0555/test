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
	void Move();//移動
	void Jump();//ジャンプ
	void Grabity();//重力
	void Grabityky();//重力の場所指定
	void Rot();//回転
	void Anime();//アニメーション
	void Render(RenderContext& rc);
	//メンバ変数
	ModelRender modelRender;
	//座標データ
	Vector3 position = Vector3::One;//キャラクターの座標
	Vector3 collisionPosition = Vector3::Zero;//コリジョンの座標
	//クォータニオン
	Quaternion rotation;//キャラの回転
	Quaternion collirot;//コリジョンの回転
	enum EnAnimationClip {//アニメーション
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

	AnimationClip animClips[enAnimationClip_Num];//アニメーションクリップ

	
	Vector3 moveSpeed = Vector3::Zero;
	int playerState = 0;//プレイヤーステイト
	int GrabityState = 0;//重力の方向 0=下 1=右 2=上 3=左
	Vector3 stickL=Vector3::Zero;
	
	Game* game;
	CollisionObject* collisionObject;//コリジョン
	BackGround* backGround;//背景
	Gost* gost;//透明
	Dassyu* dassyu;//ダッシュ
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
	float speed = 20.0f;//プレイヤーの速度
	float addSpeed=0.0f;
	float decgcount = 0;
	bool rakkaState = false;
	bool nextState = false;//次のステージが生成されたかどうか
	bool idouState = false;//落下中かどうか
	bool rezarutoState = false;
	bool timeState = false;
	Vector3 lightPosition;
	bool hitState = false;
}; 

