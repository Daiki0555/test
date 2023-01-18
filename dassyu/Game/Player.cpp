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
	//Gost�̏��������Ă���
	gost = FindGO<Gost>("gost");
	singou = FindGO<Singou>("singou");
	tuika = FindGO<Tuika>("tuika");
	nextStage = FindGO<NextStage>("nextstage");
	game = FindGO<Game>("game");

	//�A�j���[�V�����N���b�v�̃��[�h�B
	animClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animClips[enAnimationClip_Down].Load("Assets/animData/KneelDown.tka");
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
	animClips[enAnimationClip_Run].SetLoopFlag(true);
	animClips[enAnimationClip_Idle].SetLoopFlag(true);
	animClips[enAnimationClip_Walk].SetLoopFlag(true);
	animClips[enAnimationClip_Jump].SetLoopFlag(false);
	animClips[enAnimationClip_Down].SetLoopFlag(false);
	
	modelRender.Init("Assets/modelData/unityChan.tkm", animClips, enAnimationClip_Num, enModelUpAxisY);
	
	//���ʉ�
	//���y
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/zyuryokuhennkou.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/rakka.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/jump.wav");
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/tuika.wav");
	modelRender.SetPosition(position);
	modelRender.PlayAnimation(enAnimationClip_Idle);
	
	collisionObject = NewGO<CollisionObject>(0);
	collisionPosition = position;
	collisionObject->CreateBox(collisionPosition,//���W
		Quaternion::Identity,//��]
		Vector3(1.0f, //200.0f
			120.0f , 1.0f));//�傫��
	collisionObject->SetName("playerColision");
	collisionObject->SetIsEnableAutoDelete(false);
	
	//�|�C���g���C�g���쐬����
	pointLight = new PointLight;
	pointLight->Init();
	//�|�C���g���C�g�̐F
	pointLight->SetColor(Vector3(1.5f, 1.5f, 1.5f));
	//�|�C���g���C�g�̉e���͈�
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
	
	// �ړ�����
	position += moveSpeed;
	//�R���W�����ʒu�̒���
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
	//�X�s�[�h���Z�b�g�����邩�ǂ���
	if (rakkaState) {
		rakkaTime -= g_gameTime->GetFrameDeltaTime();
	}
}
//�L�����̈ړ�
void Player::Move()
{
	if (rakkaState == false) {

		switch (GrabityState)
		{
		case 0:	// �d�͂���
			if (position.y <= 0.0f)
			{
				moveSpeed.x = 0.0f;
				stickL.x = g_pad[0]->GetLStickXF();
				//�ړ��̐���
				if (position.x<321.0f && position.x>-326.0f)
				{
					//�ړ����x�ɓ��͗ʂ����Z
					moveSpeed.x += stickL.x * 20.0f;
				}
				//250���傫���Ȃ�
				else if (position.x >= 320.0f)
				{
					//250�ɖ߂��@
					position.x = 320.0f;
				}
				//-350��菬�����Ȃ�
				else if (position.x <= -325.0f)
				{
					//-355�ɖ߂��@
					position.x = -325.0f;
				}
				//�v���C���[�̍��W���O�ɂ���
				position.y = 0.0f;
				moveSpeed.y = 0.0f;
				idouState = false;//���������ǂ���
			}
			break;
		case 1:	// �d�͂��E
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
				idouState = false;//���������ǂ���
			}
			break;
		case 2:	// �d�͂���
			if (position.y >= 630.0f)
			{
				moveSpeed.x = 0.0f;
				stickL.x = g_pad[0]->GetLStickXF();
				//�ړ����x�ɓ��͗ʂ����Z
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
				idouState = false;//���������ǂ���
			}
			break;
		case 3:	// �d�͂���
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
				idouState = false;//���������ǂ���
			}
			break;

		}

	}

	 //��ɑO�i����
	if (rakkaState == true && rakkaTime > 0.0f) {
		moveSpeed.z = speed / 2.0f;
	}
	else if(!rakkaState) {
		moveSpeed.z = speed+addSpeed;
	}

}
//�W�����v
void Player::Jump()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		switch (GrabityState)
		{
		case 0:	// �d�͂���
			if (moveSpeed.y == 0.0f)
			{
				moveSpeed.y = 70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		case 1:	// �d�͂��E
			if (moveSpeed.x == 0.0f)
			{
				moveSpeed.x = -70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		case 2:	// �d�͂���
			if (moveSpeed.y == 0.0f)
			{
				moveSpeed.y = -70.0f;
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(12);
				soundSource->Play(false);
			}
			break;
		case 3:	// �d�͂���
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
//�L�����̉�]
void Player::Rot()
{
	switch (GrabityState)
	{
	case 0:	// �d�͂���
		rotation.SetRotationDegZ(0.0f);
		collirot.SetRotationDegZ(0.0f);
		break;
	case 1:	// �d�͂��E
		rotation.SetRotationDegZ(90.0f);
		collirot.SetRotationDegZ(90.0f);
		break;
	case 2:	// �d�͂���
		rotation.SetRotationDegZ(180.0f);
		collirot.SetRotationDegZ(180.0f);
		break;
	case 3:	// �d�͂���
		rotation.SetRotationDegZ(270.0f);
		collirot.SetRotationDegZ(270.0f);
		break;
	}
	modelRender.SetRotation(rotation);
	collisionObject->SetRotation(collirot);
}
//�d��
void Player::Grabity()
{
	if (!rakkaState) {
		switch (GrabityState)
		{
		case 0:	// �d�͂���
			if (moveSpeed.y != 0.0f)
			{
			moveSpeed.y -= 8.8f;
			}
			break;
		case 1:	// �d�͂��E
			if (moveSpeed.x != 0.0f)
			{
				moveSpeed.x += 8.8f;
			}
			break;
		case 2:	// �d�͂���
			if (moveSpeed.y != 0.0f)
			{
				moveSpeed.y += 8.8f;
			}
			break;
		case 3:	// �d�͂���
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
		case 0:	// �d�͂���
			moveSpeed.y -= 0.8f;
			break;
		case 1:	// �d�͂��E
			moveSpeed.x += 0.8f;
			break;
		case 2:	// �d�͂���
			moveSpeed.y += 0.8f;
			break;
		case 3:	// �d�͂���
			moveSpeed.x -= 0.8f;
			break;
		}
	}
	
}
//�d�͕���
void Player::Grabityky()
{
	if (idouState == false)
	{
		switch (GrabityState)
		{
		case 0:
			// �d�͂���
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(4);
				soundSource->Play(false);
				GrabityState = 1;
				idouState = true;//�������̔���ɂ���
			// �d�͕ύX
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
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
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
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
			if (moveSpeed.y == 0.0f) {
				moveSpeed.x = 0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.y);
				moveSpeed.y = 0.0f;
			}
		}
		break;
	case 1:	// �d�͂��E
		if (g_pad[0]->IsTrigger(enButtonDown)) {//���Ɉړ�
			GrabityState = 0;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
			if (moveSpeed.x == 0.0f) {
				moveSpeed.y = 0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.x);
				moveSpeed.x = 0.0f;
			}
		}
		//��Ɉړ�
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			GrabityState = 2;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//�������̔���ɂ���
			if (moveSpeed.x	== 0.0f) {
				moveSpeed.y = -0.1f;
			}
			else {
				moveSpeed.y = -abs(moveSpeed.x);
				moveSpeed.x = 0.0f;
			}
		}
		//���Ɉړ�
		if (g_pad[0]->IsTrigger(enButtonLeft)) {
			GrabityState = 3;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//�������̔���ɂ���
			if (moveSpeed.x == 0.0f) {
				moveSpeed.x = 0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.x);
			}
		}
		break;
	case 2:	// �d�͂���
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			GrabityState = 0;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
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
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
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
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
			if (moveSpeed.y == 0.0f) {
				moveSpeed.x = 0.1f;
			}
			else {
				moveSpeed.x = -abs(moveSpeed.y);
				moveSpeed.y = 0.0f;
			}
		}
		break;
	case 3:	// �d�͂���
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			GrabityState = 0;
			soundSource = NewGO<SoundSource>(0);
			soundSource->Init(4);
			soundSource->Play(false);
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
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
			idouState = true;//�������̔���ɂ���
			// �d�͕ύX
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
			idouState = true;//�������̔���ɂ���
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
		//�W�����v���Ă���Ȃ�
		if (moveSpeed.x != 0.0f)
		{
			modelRender.PlayAnimation(enAnimationClip_Jump);
		}
		//�i��ł���Ȃ�
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