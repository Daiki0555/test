#include "stdafx.h"
#include "Singou.h"
#include "Player.h"
Singou::~Singou()
{
	
}
bool Singou::Start()
{
	player = FindGO<Player>("player");
	startRender.Init("Assets/modelData/singou/singou0.dds", 550.0f, 250.0f);
	startRender.SetPosition({ 0.0f, 300.0f, 0.0f });
	startRender.Update();
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kaunto.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/re-sustart.wav");
	return true;
}
void Singou::Update()
{
	singou = player->Gametime;
	if (singou != singoucount)
	{
		singoucount = singou;
		SingouState();
	}
	startRender.Update();
}
void Singou::SingouState()
{
	switch (singou)
	{
	case 3:
		startRender.Init("Assets/modelData/singou/singou1.dds", 550.0f, 250.0f);
		soundSource = NewGO<SoundSource>(0);
		soundSource->Init(2);
		soundSource->SetVolume(3.0f);
		soundSource->Play(false);
		break;
	case 2:
		startRender.Init("Assets/modelData/singou/singou2.dds", 550.0f, 250.0f);
		soundSource = NewGO<SoundSource>(0);
		soundSource->Init(2);
		soundSource->SetVolume(3.0f);
		soundSource->Play(false);
		break;
	case 1:
		startRender.Init("Assets/modelData/singou/singou3.dds", 550.0f, 250.0f);
		soundSource = NewGO<SoundSource>(0);
		soundSource->Init(2);
		soundSource->SetVolume(3.0f);
		soundSource->Play(false);
		break;
	case 0:
		startRender.Init("Assets/modelData/singou/singou4.dds", 550.0f, 250.0f);
		soundSource2 = NewGO<SoundSource>(0);
		soundSource2->Init(3);
		soundSource2->Play(false);
		break;
	case -1:
		DeleteGO(this);
		break;
	}
}
void Singou::Render(RenderContext& rc)
{
	startRender.Draw(rc);
}
