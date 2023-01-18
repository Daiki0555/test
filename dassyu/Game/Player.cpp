#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"
#include "Gost.h"
#include"Dassyu.h"
#include "Singou.h"
#include"Teki.h"
#include"Tuika.h"
#include "NextStage.h"
#include "GameEnd.h"
#include <cmath>

Player::Player()
{
	
}
Player::~Player()
{
}
bool Player::Start()
{
	//Gostの情報を持ってくる
	gost = FindGO<Gost>("gost");
	singou = FindGO<Singou>("singou");
	tuika = FindGO<Tuika>("tuika");
	nextStage = FindGO<NextStage>("nextstage");
	game = FindGO<Game>("game");

	//アニメーションクリップのロード。
	animClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animClips[enAnimationClip_Down].Load("Assets/animData/KneelDown.tka");
	//ループフラグを設定する。<-走りアニメーションはループフラグを設定していないので
	//ワンショット再生で停止する。
	animClips[enAnimationClip_Run].SetLoopFlag(true);
	animClips[enAnimationClip_Idle].SetLoopFlag(true);
	animClips[enAnimationClip_Walk].SetLoopFlag(true);
	animClips[enAnimationClip_Jump].SetLoopFlag(false);
	animClips[enAnimationClip_Down].SetLoopFlag(false);
	
	modelRender.Init("Assets/modelData/unityChan.tkm", animClips, enAnimationClip_Num, enModelUpAxisY);
	
	//効果音
	//音楽
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/zyuryokuhennkou.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/rakka.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/jump.wav");
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/tuika.wav");
	modelRender.SetPosition(position);
	modelRender.PlayAnimation(enAnimationClip_Idle);
	
	collisionObject = NewGO<CollisionObject>(0);
	collisionPosition = position;
	collisionObject->CreateBox(collisionPosition,//座標
		Quaternion::Identity,//回転
		Vector3(1.0f, //200.0f
			120.0f , 1.0f));//大きさ
	collisionObject->SetName("playerColision");
	collisionObject->SetIsEnableAutoDelete(false);
	
	//ポイントライトを作成する
	pointLight = new PointLight;
	pointLight->Init();
	//ポイントライトの色
	pointLight->SetColor(Vector3(1.5f, 1.5f, 1.5f));
	//ポイントライトの影響範囲
	pointLight->SetRange(800.0f);
	pointLight->SetAffectPowParam(1.0f);
	return true;
}

void Player::Update()
{
	
	
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("m_gost");
	for (auto collision : collisions)
	{
		if (collisionObject->IsHit(collision) ==true)
		{
			
			if (rakkaState == false) {
				moveSpeed = Vector3::Zero;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(11);
				soundSource->Play(false);
				rezarutoState = true;

			}
			rakkaState = true;
		}
	}

	const auto& nextcollisions = g_collisionObjectManager->FindCollisionObjects("nextst");
	for (auto nextcollision : nextcollisions)
	{
		if (collisionObject->IsHit(nextcollision) == true)
		{
			nextState = true;
			nextStage->NextSt(collisionObject->GetPosition());
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(13);
			soundSource->Play(false);
			addSpeed += 2.0f;
			nextcollision->Dead();
		}
	}
	Gametime -= g_gameTime->GetFrameDeltaTime();
	if (Gametime <= 0.0f) {
		DeleteGO(singou);
		if (rakkaState == false) {
			Rot();
			Grabityky();
		}
		Move();
		Jump();
		Anime();
		Grabity();

	}
	if (rezarutoState == true)
	{
		rezarutoTime -= g_gameTime->GetFrameDeltaTime();
	}
	if (rezarutoTime <= 0.0f && timeState == false)
	{
		game->soundSource->Dead();
		gameend = NewGO<GameEnd>(0, "gameend");
		gameend = FindGO<GameEnd>("gameend");
		gameend->coinrizaruto = game->coincount;
		gameend->metorRizarut= position.z/100;
		timeState = true;
	}
	if (hitState == true && timeState == false)
	{
		game->soundSource->Dead();
		gameend = NewGO<GameEnd>(0, "gameend");
		gameend = FindGO<GameEnd>("gameend");
		gameend->coinrizaruto = game->coincount;
		gameend->metorRizarut = position.z / 100;
		timeState = true;
	}
	
	// 移動する
	position += moveSpeed;
	//コリジョン位置の調整
	collisionPosition = position-moveSpeed;

	switch (GrabityState)
	{
	case 0:
		collisionPosition.y = position.y+50.0f;
		break;
	case 1:
		collisionPosition.x = position.x - 50.0f;
		break;
	case 2:
		collisionPosition.y = position.y - 50.0f;
		break;
	case 3:
		collisionPosition.x = position.x + 50.0f;
		break;
	}
	lightPosition = position;
	lightPosition.z = position.z + -100.0f;
	
	pointLight->SetPosition(lightPosition);
	pointLight->Update();
	
	modelRender.SetPosition(position);
	modelRender.Update();
	
	collisionObject->SetPosition(collisionPosition);
	//スピードリセットさせるかどうか
	if (rakkaState) {
		rakkaTime -= g_gameTime->GetFrameDeltaTime();
	}
}
//キャラの移動
void Player::Move()
{
	if (rakkaState == false) {

		switch (GrabityState)
		{
		case 0:	// 重力が下
			if (position.y <= 0.0f)
			{
				moveSpeed.x = 0.0f;
				stickL.x = g_pad[0]->GetLStickXF();
				//移動の制限
				if (position.x<321.0f && position.x>-326.0f)
				{
					//移動速度に入力量を加算
					moveSpeed.x += stickL.x * 20.0f;
				}
				//250より大きいなら
				else if (position.x >= 320.0f)
				{
					//250に戻す　
					position.x = 320.0f;
				}
				//-350より小さいなら
				else if (position.x <= -325.0f)
				{
					//-355に戻す　
					position.x = -325.0f;
				}
				//プレイヤーの座標を０にする
				position.y = 0.0f;
				moveSpeed.y = 0.0f;
				idouState = false;//落下中かどうか
			}
			break;
		case 1:	// 重力が右
			if (position.x >= 360.0f)
			{
				moveSpeed.y = 0.0f;
				stickL.y = g_pad[0]->GetLStickYF();
				if (position.y > 19.0f && position.y < 591.0f) {
					moveSpeed.y += stickL.y * 20.0f;
				}
				else if (position.y >= 590.0f)
				{
					position.y = 590.0f;
				}
				else if (position.y <= 20.0f) {
					position.y = 20.0f;
				}

				position.x = 360.0f;
				moveSpeed.x = 0.0f;
				idouState = false;//落下中かどうか
			}
			break;
		case 2:	// 重力が上
			if (position.y >= 630.0f)
			{
				moveSpeed.x = 0.0f;
				stickL.x = g_pad[0]->GetLStickXF();
				//移動速度に入力量を加算
				if (position.x<321.0f && position.x>-336.0f)
				{
					moveSpeed.x += stickL.x * 20.0f;
				}
				else if (position.x >= 320.0f)
				{
					position.x = 320.0f;
				}
				else if (position.x <= -335.0f)
				{
					position.x = -335.0f;
				}
				position.y = 630.0f;
				moveSpeed.y = 0.0f;
				idouState = false;//落下中かどうか
			}
			break;
		case 3:	// 重力が左
			if (position.x <= -360.0f)
			{
				moveSpeed.y = 0.0f;
				stickL.y = g_pad[0]->GetLStickYF();
				if (position.y > 19.0f && position.y < 591.0f) {
					moveSpeed.y += stickL.y * 20.0f;
				}
				else if (position.y >= 590.0f)
				{
					position.y = 590.0f;
				}
				else if (position.y <= 20.0f) {
					position.y = 20.0f;
				}
				position.x = -360.0f;
				moveSpeed.x = 0.0f;
				idouState = false;//落下中かどうか
			}
			break;

		}

	}

	 //常に前進する
	if (rakkaState == true && rakkaTime > 0.0f) {
		moveSpeed.z = speed / 2.0f;
	}
	else if(!rakkaState) {
		moveSpeed.z = speed+addSpeed;
	}

}
//ジャンプ
void Player::Jump()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		switch (GrabityState)
		{
		case 0:	// 重力が下
			if (moveSpeed.y == 0.0f)
			{
				moveSpeed.y = 70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		case 1:	// 重力が右
			if (moveSpeed.x == 0.0f)
			{
				moveSpeed.x = -70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		case 2:	// 重力が上
			if (moveSpeed.y == 0.0f)
			{
				moveSpeed.y = -70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		case 3:	// 重力が左
			if (moveSpeed.x == 0.0f)
			{
				moveSpeed.x = 70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		}
	}

}
//キャラの回転
void Player::Rot()
{
	switch (GrabityState)
	{
	case 0:	// 重力が下
		rotation.SetRotationDegZ(0.0f);
		collirot.SetRotationDegZ(0.0f);
		break;
	case 1:	// 重力が右
		rotation.SetRotationDegZ(90.0f);
		collirot.SetRotationDegZ(90.0f);
		break;
	case 2:	// 重力が上
		rotation.SetRotationDegZ(180.0f);
		collirot.SetRotationDegZ(180.0f);
		break;
	case 3:	// 重力が左
		rotation.SetRotationDegZ(270.0f);
		collirot.SetRotationDegZ(270.0f);
		break;
	}
	modelRender.SetRotation(rotation);
	collisionObject->SetRotation(collirot);
}
//重力
void Player::Grabity()
{
	if (!rakkaState) {
		switch (GrabityState)
		{
		case 0:	// 重力が下
			if (moveSpeed.y != 0.0f)
			{
			moveSpeed.y -= 8.8f;
			}
			break;
		case 1:	// 重力が右
			if (moveSpeed.x != 0.0f)
			{
				moveSpeed.x += 8.8f;
			}
			break;
		case 2:	// 重力が上
			if (moveSpeed.y != 0.0f)
			{
				moveSpeed.y += 8.8f;
			}
			break;
		case 3:	// 重力が左
			if (moveSpeed.x != 0.0f)
			{
				moveSpeed.x -= 8.8f;
			}
			break;
		}
	}
	else {
		switch (GrabityState)
		{
		case 0:	// 重力が下
			moveSpeed.y -= 0.8f;
			break;
		case 1:	// 重力が右
			moveSpeed.x += 0.8f;
			break;
		case 2:	// 重力が上
			moveSpeed.y += 0.8f;
			break;
		case 3:	// 重力が左
			moveSpeed.x -= 0.8f;
			break;
		}
	}
	
}
//重力方向
void Player::Grabityky()
{
	if (idouState == false)
	{
		switch (GrabityState)
		{
		case 0:
			// 重力が下
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(4);
				soundSource->Play(false);
				GrabityState = 1;
				idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.y == 0.0f) {
				moveSpeed.x = -0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.y);
				moveSpeed.y = 0.0f;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			GrabityState = 2;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.y == 0.0f) {
				moveSpeed.y = -0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.y);
				
			}
		}
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			GrabityState = 3;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.y == 0.0f) {
				moveSpeed.x = 0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.y);
				moveSpeed.y = 0.0f;
			}
		}
		break;
	case 1:	// 重力が右
		if (g_pad[0]->IsTrigger(enButtonDown)) {//下に移動
			GrabityState = 0;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.x == 0.0f) {
				moveSpeed.y = 0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.x);
				moveSpeed.x = 0.0f;
			}
		}
		//上に移動
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			GrabityState = 2;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			if (moveSpeed.x	== 0.0f) {
				moveSpeed.y = -0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.x);
				moveSpeed.x = 0.0f;
			}
		}
		//左に移動
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			GrabityState = 3;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			if (moveSpeed.x == 0.0f) {
				moveSpeed.x = 0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.x);
			}
		}
		break;
	case 2:	// 重力が上
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			GrabityState = 0;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.y == 0.0f) {
				moveSpeed.y = 0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.y); 
			}
		}
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			GrabityState = 1;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.y == 0.0f) {
				moveSpeed.x = -0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.y);
				moveSpeed.y = 0.0f;
			}	
		}
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			GrabityState = 3;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.y == 0.0f) {
				moveSpeed.x = 0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.y);
				moveSpeed.y = 0.0f;
			}
		}
		break;
	case 3:	// 重力が左
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			GrabityState = 0;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.x == 0.0f) {
				moveSpeed.y = 0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.x);
				moveSpeed.x = 0.0f;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonRight)) {
			GrabityState = 1;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			// 重力変更
			if (moveSpeed.x == 0.0f) {
				moveSpeed.x = -0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.x);
			}
		}
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			GrabityState = 2;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//落下中の判定にする
			if (moveSpeed.x == 0.0f) {
				moveSpeed.y = -0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.x);
				moveSpeed.x = 0.0f;
			}
		}
		break;
	}
	}
	
}
void Player::Anime()
{
	switch (GrabityState)
	{
	case 0:
	case 2:
		if (moveSpeed.y != 0.0f)
		{
			modelRender.PlayAnimation(enAnimationClip_Jump);
		}
		else if (moveSpeed.z != 0.0f)
		{
			modelRender.PlayAnimation(enAnimationClip_Run);
		}
		break;
	case 1:
	case 3:
		//ジャンプしているなら
		if (moveSpeed.x != 0.0f)
		{
			modelRender.PlayAnimation(enAnimationClip_Jump);
		}
		//進んでいるなら
		else if (moveSpeed.z != 0.0f)
		{
			modelRender.PlayAnimation(enAnimationClip_Run);
		}
		break;
	}
}
void Player::Render(RenderContext& rc)
{
	if (hitState == false)
	{
		modelRender.Draw(rc);
	}
	

}