#include "stdafx.h"
#include "Coin.h"
#include "Player.h"
#include"Game.h"
Coin::Coin()
{
	
}
Coin::~Coin()
{

}
bool Coin::Start()
{
	//プレイヤーの情報を持ってくる
	player = FindGO<Player>("player");
	//ゲームの情報を持ってくる
	game = FindGO<Game>("game");
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/koin.tkm");
	modelRender.SetPosition(position);
	modelRender.SetScale(scale);
	rot.AddRotationDegY(360.0f);
	modelRender.SetRotation(rot);

	//音楽
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/koin.wav");
	
	

	return true;
}
void Coin::Update()
{

	if (!coinget)
	{
		Rotaition();
	}
	CoinGet();
	modelRender.SetRotation(rot);
	modelRender.SetPosition(position);
	modelRender.Update();
}
void Coin::Rotaition()
{
	rot.AddRotationDegY(10.0f);
	
}
void Coin::CoinGet()
{
	if (!coinget)
	{
		//ベクトルを計算
		diff = player->GetPosition() - position;
		switch (player->GrabityState) {
		case 0:
		case 1:
			//ベクトルの長さが140.0fより小さかったら
			if (diff.Length() <= 140.0f)
			{
				switch (player->GrabityState)
				{
				case 0:
					jumcoin = position.y;
					break;
				case 1:
					jumcoin = position.x;
					break;
				}
				jumpSpeed = 300.0f;
				coinget = true;
				game->coincount += 1;//コインの数をカウント
				soundSource = NewGO<SoundSource>(0);
				soundSource->Init(1);
				soundSource->Play(false);
			}
			break;
		case 2:
		case 3:
			//ベクトルの長さが160.0fより小さかったら
			if (diff.Length() <= 160.0f)
			{
				switch (player->GrabityState)
				{

				case 2:
					jumcoin = position.y;
					break;
				case 3:
					jumcoin = position.x;
					break;
				}
			jumpSpeed = 300.0f;
			coinget = true;
			game->coincount += 1;//コインの数をカウント	
			soundSource = NewGO<SoundSource>(1);
			soundSource->Init(1);
			soundSource->Play(false);
			}
			break;
		}
	}
	else {
		switch (player->GrabityState)
		{
		case 0:
			position.y += jumpSpeed * g_gameTime->GetFrameDeltaTime();
			jumpSpeed -= 980.0f * g_gameTime->GetFrameDeltaTime();
			qAddRot.SetRotation(Vector3::AxisY, 0.4f);
			rot.Multiply(qAddRot);
			//元の値より小さいなら
			if (jumcoin > position.y)
			{
				//自身の削除
				DeleteGO(this);
			}
			break;
		case 1:
			position.x -= jumpSpeed * g_gameTime->GetFrameDeltaTime();
			jumpSpeed -= 980.0f * g_gameTime->GetFrameDeltaTime();
			qAddRot.SetRotation(Vector3::AxisX, 0.4f);
			rot.Multiply(qAddRot);
			//元の値より大きいなら
			if (jumcoin < position.x)
			{
				//自身の削除
				DeleteGO(this);
			}
			break;
		case 2:
			position.y -= jumpSpeed * g_gameTime->GetFrameDeltaTime();
			jumpSpeed -= 980.0f * g_gameTime->GetFrameDeltaTime();
			qAddRot.SetRotation(Vector3::AxisY, 0.4f);
			rot.Multiply(qAddRot);
			//元の値より小さいなら
			if (jumcoin < position.y)
			{
				//自身の削除
				DeleteGO(this);
			}
			break;
		case 3:
			position.x += jumpSpeed * g_gameTime->GetFrameDeltaTime();
			jumpSpeed -= 980.0f * g_gameTime->GetFrameDeltaTime();
			qAddRot.SetRotation(Vector3::AxisX, 0.4f);
			rot.Multiply(qAddRot);
			//元の値より小さいなら
			if (jumcoin > position.x)
			{
				//自身の削除
				DeleteGO(this);
			}
			break;
		}
		}
}
void Coin::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}