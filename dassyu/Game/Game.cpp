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
#include "Fade.h"
#include "NextStage.h"
Game::Game()
{

}
Game::~Game() 
{
	//プレイヤーを削除する
	DeleteGO(player);
	//ゲームカメラを削除する
	DeleteGO(gamecamera);
	QueryGOs<BackGround>("asiba", [&](BackGround* background)
		{
			DeleteGO(background);
			return true;
		});
	QueryGOs<Coin>("coin", [&](Coin* coin)
		{
			DeleteGO(coin);
			return true;
		});
	QueryGOs<Gost>("gost", [&](Gost* gost)
		{
			DeleteGO(gost);
			return true;
		});
	QueryGOs<Teki>("inseki", [&](Teki* teki)
		{
			DeleteGO(teki);
			return true;
		});
	QueryGOs<Dassyu>("dassyu", [&](Dassyu* dassyu)
		{
			DeleteGO(dassyu);
			return true;
		});
	QueryGOs<Tuika>("tuika", [&](Tuika* tuika)
		{
			DeleteGO(tuika);
			return true;
		});
	//BGMの削除
	DeleteGO(soundSource);
	DeleteGO(skycube);
}
bool Game::Start()
{
	// 前面描画の終了
	g_renderingEngine->SetIsLate(false);
	g_renderingEngine->SetAmbient({ 12.5f,12.50f,12.50f });
	g_renderingEngine->SetDirectionLight
	(0,Vector3{ 0.0f,-0.5f,-0.5f }, Vector3{ 1.0f,1.0f,1.0f });
	g_renderingEngine->SetCascadeNearAreaRates(0.3f, 0.8f, 1.0f);


	//コインの描画
	koinRender.Init("Assets/modelData/koinsp.dds", 700.0f, 550.0f);
	koinRender.SetPosition({ 600.0f, -350.0f, 0.0f });
	coinRender.SetPosition({ 650.0f, -250.0f, 0.0f });
	coinRender.SetScale(4.0f);
	coinRender.SetShadowParam(true, 5.0f, syadou);
	coinRender.SetColor({ 1.0f,0.7f,0.10f,1.0f});

	fontRender.SetPosition({ 600.0f,-350.0f,0.0f });
	fontRender.SetScale(2.0f);
	fontRender2.SetPosition({ 600.0f,-250.0f,0.0f });
	fontRender2.SetScale(2.0f);
	
	
	TimeRender.SetPosition({ 0.0f,350.0f,0.0f });
	TimeRender.SetScale(5.0f);
	//次のステージについての情報
	nextStage = NewGO<NextStage>(0,"nextstage");

	leverRender.Init("Assets/level/stage.tkl",
		[&](LevelObjectData& objData)
		{  
			//名前がstaggeだったら
			if (objData.EqualObjectName(L"asiba") == true)
			{
				//背景のオブジェクトを作成する
				background = NewGO<BackGround>(0, "asiba");
				background->SetPosition(objData.position);
				background->SetRotaition(objData.rotation);
				background->SetScale(objData.scale);
				return true;
			}
			else if (objData.EqualObjectName(L"hantei") == true)
			{
				gost = NewGO<Gost>(0, "gost");
				gost->SetPosition(objData.position);
				gost->SetRotation(objData.rotation);
				gost->SetScale(objData.scale);
				return true;
			}
			else if (objData.EqualObjectName(L"koin") == true)
			{
				coin = NewGO<Coin>(0, "coin");
				coin->SetPosition(objData.position);
				coin->SetScale(objData.scale);
				coin->SetRotaition(objData.rotation);
				return true;
			}
			else if (objData.EqualObjectName(L"inseki") == true)
			{
				teki = NewGO<Teki>(0, "inseki");
				teki->SetPosition(objData.position);
				teki->SetScale(objData.scale);
				teki->SetRotation(objData.rotation);
				return true;
			}
			else if (objData.EqualObjectName(L"dasyu") == true)
			{
				dassyu = NewGO<Dassyu>(0, "dassyu");
				dassyu->SetPosition(objData.position);
				dassyu->SetScale(objData.scale);
				dassyu->SetRotation(objData.rotation);
				return true;
			}
			else if (objData.EqualObjectName(L"sakuseiasiba") == true)
			{
				tuika = NewGO<Tuika>(0, "tuika");
				tuika->SetPosition(objData.position);
				tuika->SetRotaition(objData.rotation);
				tuika->SetScale(objData.scale);
				return true;
			}
			return true;
		});
	
	player = NewGO<Player>(0, "player");
	player = FindGO<Player>("player");
	gamecamera = NewGO<GameCamera>(0, "gamecamera");
	singou = NewGO<Singou>(0, "singou");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/BGM.wav");
	soundSource = NewGO<SoundSource>(0);
	//ResistWaveFileBankで指定した番号。
	soundSource->Init(6);
	//BGMは曲をループさせる。
	soundSource->Play(true);
	Initsky();
	//当たり判定の可視化
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();	
	
	//矢印の描画
	yazirusi.Init("Assets/modelData/yazirusi/yazirusi0.DDS", 700.0f, 550.0f);
	//矢印のポジション
	yazirusipos = player->position;
	yazirusipos.z = 10.0f;
	yazirusi.SetPosition(yazirusipos);
    
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();
	return true;
}
void Game::Update()
{
	coinGet = coincount;
	wchar_t coinRe[256];
	swprintf_s(coinRe, 256, L"%d", coinGet);
	coinRender.SetText(coinRe);

	if (player->rakkaState==false) {
        skycube->SetPosition(player->position);
	}
	yazirusi.SetPosition(yazirusipos);
	yazirusi.Update();
	koinRender.Update();
	skycube->Update();
}
void Game::GameRizaruto()
{

}
void Game::Initsky()
{
	
	DeleteGO(skycube);
	skycube = NewGO<SkyCube>(0, "skycube");
	skycube->SetLuminance(0.2f);
	skycube->SetType((EnSkyCubeType)skycubeType);
	// 環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(skycube->GetTextureFilePath(), 1.0f);
	skycube->SetScale(400.0f);
	skycube->Update();
	// 明度率を設定する。
	g_renderingEngine->SetSceneMiddleGray(0.08f);
}

void Game::Render(RenderContext& rc)
{
	yazirusi.Draw(rc);
	if (player->timeState == false)
	{
		koinRender.Draw(rc);
		coinRender.Draw(rc);
	}
	
}
