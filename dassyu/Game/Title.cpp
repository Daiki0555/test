#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
Title::~Title()
{
	DeleteGO(soundSource);
	DeleteGO(this);
}
bool Title::Start()
{
	rot.AddRotationY(180.0f);
	g_renderingEngine->SetIsLate(true);
	//�^�C�g��
	titleRender.Init("Assets/modelData/Title/title.dds", 1920,1080);
	
	//���f��
	//�L�����N�^�[�̃��[�h
	animClips[enAnimationClip_Clear].Load("Assets/animData/clear.tka");
	//�����V���b�g�Đ��Œ�~����B
	animClips[enAnimationClip_Clear].SetLoopFlag(true);
	titleModel.IniTranslucent("Assets/modelData/unityChan.tkm", animClips, enAnimationClip_Num, enModelUpAxisY);
	titleModel.PlayAnimation(enAnimationClip_Clear);
	titleModel.SetPosition(modelPos);
	titleModel.SetScale(modelScale);
	titleModel.SetRotation(rot);
	
	//�Q�[���X�^�[�g
	gastRender.Init("Assets/modelData/Title/GameStart.DDS", 1920, 1080);
	gastRender.SetPosition({ -350.0f,-150.0f,0.0f });
	//�V�ѕ�
	asobiRender.Init("Assets/modelData/Title/asobikata.DDS", 1920, 1080);
	asobiRender.SetPosition({ -480.0f,-400.0f,0.0f });
	//�{�^��
	botanRender.Init("Assets/modelData/Title/button.dds", 1293, 646);
	botanRender.SetPosition(Vector3(0.0f, -220.0f, 0.0f));
	setumeiRender.Init("Assets/modelData/setumei.DDS",1920, 1080);

	//BGM
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/title.wav");
	soundSource = NewGO<SoundSource>(0);
	//ResistWaveFileBank�Ŏw�肵���ԍ��B
	soundSource->Init(9);
	//BGM�͋Ȃ����[�v������B
	soundSource->Play(true);
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/kettei.wav");

	//�t�F�[�h�C��
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();
	return true;
}
void Title::Update()
{

	if (isWaitFadeout) {
		if (!fade->IsFade())
		{
			gameloopState = true;
			NewGO<Game>(0, "game");
			//���g���폜����B
			DeleteGO(this);
		}
	}
	else {
		//A�{�^������������B
		if (g_pad[0]->IsTrigger(enButtonA)&&titleState == false) {
			unityState = true;
			isWaitFadeout = true;
			soundSource2 = NewGO<SoundSource>(0);
			//ResistWaveFileBank�Ŏw�肵���ԍ��B
			soundSource2->Init(10);
			soundSource2->Play(false);
			fade->StartFadeOut();
		}
	}
	if (g_pad[0]->IsTrigger(enButtonA) && titleState == true)
	{
		setumeiState = true;
	}
	if (g_pad[0]->IsTrigger(enButtonB) && setumeiState == true)
	{
		setumeiState = false;
	}

	//�^�C�g���̓�����
	if (titleState == false)
	{
		//���l��ω�������
		if (isWaitFadeout)
		{
			alpha += g_gameTime->GetFrameDeltaTime() * 20.5f;
		}
		else
		{
			alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
		}
	}
	else
	{
		//���l��ω�������
		if (isWaitFadeout)
		{
			asobialpha += g_gameTime->GetFrameDeltaTime() * 20.5f;
		}
		else
		{
			asobialpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
		}
	}

	//�^�C�g����ʂ̐ؑ�
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		if (titleState == false)
		{
			titleState = true;
			alpha = 2.0f;
		}
		else if (titleState == true)
		{
			titleState = false;
			asobialpha = 2.0f;
		}
	}
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		if (titleState == false)
		{
			titleState = true;
			alpha = 2.0f;
		}
		else if (titleState == true)
		{
			titleState = false;
			asobialpha = 2.0f;
		}
	}
	
	gastRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(alpha))));

	asobiRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(asobialpha))));
	//�摜�̍X�V
	asobiRender.Update();
	titleRender.Update();
	gastRender.Update();
	botanRender.Update();
	titleModel.Update();
}
void Title::Render(RenderContext& rc)
{
	//�摜�̕`��
	titleRender.Draw(rc);
	if (unityState == false&&setumeiState==false)
	{
		titleModel.Draw(rc);
	}
	gastRender.Draw(rc);
	asobiRender.Draw(rc);
	if (setumeiState == true)
	{
		setumeiRender.Draw(rc);
	}
	
	//botanRender.Draw(rc);
}