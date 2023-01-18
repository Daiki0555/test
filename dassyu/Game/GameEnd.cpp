#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "nature/SkyCube.h"
#include "graphics/RenderingEngine.h"
#include "Gost.h"
#include "Coin.h"
#include "Teki.h"
#include "Dassyu.h"
#include "Singou.h"
#include "Tuika.h"
#include "Title.h"
#include "Fade.h"
#include "NextStage.h"
#include "GameEnd.h"
GameEnd::GameEnd()
{
	//ÉfÅ[É^Çè¡Ç∑ÇΩÇﬂÇÃFindGO
	game = FindGO<Game>("game");
	background = FindGO<BackGround>("asiba");
	gost = FindGO<Gost>("gost");
	coin = FindGO<Coin>("coin");
	teki = FindGO<Teki>("inseki");
	dassyu = FindGO<Dassyu>("dassyu");
	tuika = FindGO<Tuika>("tuika");
	player = FindGO<Player>("player");
	gamecamera = FindGO<GameCamera>("gamecamera");
	nextStage = FindGO<NextStage>("nextstage");
	fade = FindGO<Fade>("fade");

	haikeiRender.Init("Assets/modelData/gameend/kurohaikei.DDS", 1980, 1080);
	haikeiRender.SetMulColor({ 1.0f, 1.0f, 1.0f, alpha });
	spriteRender.Init("Assets/modelData/gameend/rizaruto1.DDS",1980, 1080);
	spriteRender.SetPivot(Vector2(0.0f, 0.0f));
	spriteRender.SetPosition(Vector3(-1800.0f, -300.0f, 0.0f));
	spriteRender.SetScale(rizascale);
	
	spriteRender2.Init("Assets/modelData/gameend/rizaruto1.DDS", 1980, 1080);
	spriteRender2.SetPivot(Vector2(0.0f, 0.0f));
	spriteRender2.SetPosition(Vector3(-1800.0f, -650.0f, 0.0f));
	spriteRender2.SetScale(rizascale);
	
	koinRender.SetPosition(-750.0f, 350.0f, 0.0f);
	koinRender.SetColor(1.0f, 0.7f, 0.10f, 1.0f);
	koinRender.SetShadowParam(true, 5.0f, syadou);
	koinRender.SetPivot(1.0f, 0.0f);
	koinRender.SetScale(5.0f);

	metorRender.SetPosition(-750.0f, 0.0f, 0.0f);
	metorRender.SetColor(1.0f, 0.7f, 0.10f, 1.0f);
	metorRender.SetShadowParam(true, 5.0f, syadou);
	metorRender.SetPivot(1.0f, 0.0f);
	metorRender.SetScale(5.0f);

	RunkRender.SetPosition(200.0f, 200.0f, 0.0f);
	RunkRender.SetColor(1.0f, 0.7f, 0.10f, 1.0f);
	RunkRender.SetShadowParam(true, 5.0f, syadou);
	RunkRender.SetPivot(0.50f, 0.50f);
	RunkRender.SetScale(runkScalse);

	g_soundEngine->ResistWaveFileBank(15, "Assets/sound/rizaruto.wav");
	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/rizarutoBGM.wav");
	g_soundEngine->ResistWaveFileBank(17, "Assets/sound/zannen.wav");
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/crunk.wav");
	g_soundEngine->ResistWaveFileBank(19, "Assets/sound/brunk.wav");
	g_soundEngine->ResistWaveFileBank(20, "Assets/sound/arunk.wav");
	g_soundEngine->ResistWaveFileBank(21, "Assets/sound/srunk.wav");
	spriteRender.Update();
	spriteRender2.Update();
}
GameEnd::~GameEnd()
{
	
}
void GameEnd::Update()
{
	wchar_t e_coin[255];
	swprintf_s(e_coin, 255, L"%dñá",coinrizaruto);
	koinRender.SetText(e_coin);

	wchar_t e_metor[255];
	swprintf_s(e_metor, 255, L"%dm", metorRizarut);
	metorRender.SetText(e_metor);
	if (rizascale.x <= 1.0f && c_bg == false)
	{
		soundSource2 = NewGO<SoundSource>(0);
		soundSource2->Init(15);
		soundSource2->Play(false);
	}
	if (rizascale.x <= 1.0f)
	{
		rizascale.x += 0.05;
	}
	else
	{
		e_coinState = true;
	}
	if (e_coinState == true && rizascale2.x <= 1.0f)
	{
		if (m_bg == false)
		{
			soundSource2 = NewGO<SoundSource>(0);
			soundSource2->Init(15);
			soundSource2->Play(false);
			m_bg = true;
		}
	}
	if (e_coinState == true&& rizascale2.x <= 1.0f)
	{
		rizascale2.x += 0.05;
	}
	else if(rizascale2.x >= 1.0f)
	{
		e_metorState = true;
	}
	if (e_metorState==true)
	{
		rendertime -= g_gameTime->GetFrameDeltaTime();
		
	}
	if (rendertime <= 0.0f)
	{
		e_runkState = true;
		Runk();
	}
	
	spriteRender.SetScale(rizascale);
	spriteRender2.SetScale(rizascale2);
	spriteRender.Update();
	spriteRender2.Update();
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		g_renderingEngine->SetIsLate(true);
		g_renderingEngine->SetAmbient({ 6.5f,6.5f,6.5f });
		g_renderingEngine->SetDirectionLight
		(0, Vector3{ 0.0f,0.1f,-1.0f }, Vector3{ 6.50f,6.50f,6.50f });
		fade->m_currentAlpha = 1.0f;
	
		g_camera3D->SetPosition(0.0f, 50.0f, -200.0f);
		g_camera3D->Update();
		NewGO<Title>(0, "title");
		title = FindGO<Title>("title");
		title->unityState = false;
		title->setumeiState = false;
		DeleteGO(game);
		DeleteGO(this);
	}
}
void GameEnd::Runk()
{
	wchar_t e_runk[255];
	if (metorRizarut > 1000)
	{
		swprintf_s(e_runk, 255, L"S");
		if (r_bg == false)
		{
			soundSource3 = NewGO<SoundSource>(0);
			soundSource3->Init(21);
			soundSource3->Play(false);
			r_bg = true;
		}
	}
	else if (metorRizarut > 700)
	{
		swprintf_s(e_runk, 255, L"A");
		if (r_bg == false)
		{
			soundSource3 = NewGO<SoundSource>(0);
			soundSource3->Init(20);
			soundSource3->Play(false);
			r_bg = true;
		}
	}
	else if (metorRizarut > 400)
	{
		swprintf_s(e_runk, 255, L"B");
		if (r_bg == false)
		{
			soundSource3 = NewGO<SoundSource>(0);
			soundSource3->Init(19);
			soundSource3->Play(false);
			r_bg = true;
		}
	}
	else if (metorRizarut > 200)
	{
		swprintf_s(e_runk, 255, L"C");
		if (r_bg == false)
		{
			soundSource3 = NewGO<SoundSource>(0);
			soundSource3->Init(18);
			soundSource3->Play(false);
			r_bg = true;
		}
	}
	else
	{
		if (r_bg == false)
		{
			soundSource3 = NewGO<SoundSource>(0);
			soundSource3->Init(17);
			soundSource3->Play(false);
			r_bg = true;
		}
		swprintf_s(e_runk, 255, L"E");
	}
	if (runkScalse <= 10.0f)
	{
		runkScalse += 1.0f;
	}
	RunkRender.SetScale(runkScalse);
	RunkRender.SetText(e_runk);
}
void GameEnd::Render(RenderContext& rc)
{
	
	haikeiRender.Draw(rc);
	spriteRender.Draw(rc);
	spriteRender2.Draw(rc);
	if (e_coinState == true)
	{
		koinRender.Draw(rc);
	}
	if (e_metorState == true)
	{
		metorRender.Draw(rc);
	}
	if (e_runkState == true)
	{
		RunkRender.Draw(rc);
	}
	
}