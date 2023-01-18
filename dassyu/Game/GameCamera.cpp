#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"
#include "Dassyu.h"
GameCamera::GameCamera()
{

}
GameCamera::~GameCamera()
{

}
bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	toCameraPos.Set(0.0f, 150.0f, -400.0f);
	//プレイヤーインスタンスを探す
	player = FindGO<Player>("player");
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	return true;
}
void GameCamera::Update()
{
	if (player->rakkaState) {
		return;
	}

		//カメラの->更新
		//注視点を更新する
		Vector3 target = player->position;
		//重力が上の時にカメラを下に動かす
		switch (player->GrabityState)
		{
		case 0:
			target.y += 10.0f;
			break;
		case 1:
			target.y -= 10.0f;
			target.x -= 50.0f;
			break;
		case 2:
			target.y -= 200.0f;
			break;
		case 3:
			target.y -= 10.0f;
			target.x += 50.0f;
			break;
		}
		if (dassyu != nullptr) {
			if (dassyu->DassyuState == false) {
				target.z = player->position.z + 100.0f;
			}
		}
		pos = target + toCameraPos;
		//メインカメラに注視点と視点を設定する
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
		g_camera3D->SetNear(1.0f);
		//カメラの更新
	    g_camera3D->Update();
	}
	