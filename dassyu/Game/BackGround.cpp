#include "stdafx.h"
#include "BackGround.h"
#include "Tuika.h"
BackGround::BackGround()
{
	

}
BackGround::~BackGround()
{

}
bool BackGround::Start()
{
    //モデルを読み込む
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/asiba.tkm");
	//座標5の変更
	modelRender.SetPosition(position);
    //大きさの変更
	modelRender.SetScale(Scale);
	//回転の変更
	modelRender.SetRotation(rot);
	//大きさの変更させるために、モデルを更新
	modelRender.Update();
	return true;
}
void BackGround::Update()
{
	//大きさの変更させるために、モデルを更新
	modelRender.Update();
}
void BackGround::Render(RenderContext& rc)
{
	//背景の描画
	modelRender.Draw(rc);
}