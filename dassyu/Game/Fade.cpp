#include "stdafx.h"
#include "Fade.h"
namespace
{
	const Vector3 SCALE = Vector3(2.16f, 2.16f, 1.0f);
	const Vector3 POSITION = Vector3(-140.0f, 10.0f, 0.0f);
}
Fade::Fade()
{

}
Fade::~Fade()
{

}
bool Fade::Start()
{
	//キャラクターのロード
	animClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	//ワンショット再生で停止する。
	animClips[enAnimationClip_Run].SetLoopFlag(true);
	rot.SetRotationDegY(-90.0f);
	loadRender.IniTranslucent("Assets/modelData/unityChan.tkm", animClips, enAnimationClip_Num, enModelUpAxisY);
	loadRender.PlayAnimation(enAnimationClip_Run);
	
	
	spriteRender.Init("Assets/modelData/Load/load1.DDS" ,1024, 512);
	spriteRender.SetScale(SCALE);
	spriteRender.SetPosition(POSITION);
	
	loadRender.SetPosition(Vector3(100.0f, -100.0f, 0.0f));
	loadRender.SetRotation(rot);
	spriteRender.Update();
	loadRender.Update();
	
	return true;
}
void Fade::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 1.0f * g_gameTime->GetFrameDeltaTime();
		// 前面描画の準備
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += 1.0f * g_gameTime->GetFrameDeltaTime();
		// 前面描画の準備
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:

		break;
	}
	spriteRender.Update();
	loadRender.Update();
	
}
void Fade::LoadUpdate()
{

}
void Fade::Render(RenderContext& rc)
{
	if (m_currentAlpha > 0.0f)
	{
		spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		spriteRender.Draw(rc);
		loadRender.Draw(rc);
	}
}