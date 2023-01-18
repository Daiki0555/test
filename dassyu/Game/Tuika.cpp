#include "stdafx.h"
#include "Tuika.h"
#include"BackGround.h"
#include"Coin.h"
#include"Gost.h"
#include"Teki.h"
#include"Dassyu.h"
#include "Player.h"
Tuika::Tuika()
{
}
Tuika::~Tuika()
{
	
}
bool Tuika::Start()
{
	player = FindGO<Player>("player");
	//モデルの作成と設定
	modelRender.Init("Assets/modelData/asiba.tkm");
	modelRender.SetPosition(m_pos);
	modelRender.SetRotation(rot);
	modelRender.SetScale(Scale);
	//コリジョンの作成
	colliob = NewGO<CollisionObject>(0);
	colliob->CreateBox(m_pos,//座標
		Quaternion::Identity,//回転
		colliScale);
	colliob->SetName("nextst");
	colliob->SetIsEnableAutoDelete(false);

	return true;
}
void Tuika::Update()
{
	modelRender.Update();
}

void Tuika::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}