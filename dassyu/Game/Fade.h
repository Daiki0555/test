#pragma once
class Fade:public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start();
	void Update();
	void LoadUpdate();
	void Render(RenderContext& rc);
	SpriteRender spriteRender;
	ModelRender loadRender;
	Quaternion rot;
	int loadTime = 13;
	int loadcount=0;//loadを切り替えるもの
	int loadAtai = 13;//loadcountに合わせる値
	enum EnAnimationClip {//アニメーション
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animClips[enAnimationClip_Num];//アニメーションクリップ
	//フェードイン
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	//フェードアウト
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}
	//フェード中
	const bool IsFade()const
	{
		return m_state != enState_Idle;
	}
	//α値を取得
	const float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}
	float m_currentAlpha = 1.0f;//現在のα地。
private:
	enum EnState {
		enState_FadeIn, //フェードイン
		enState_FadeOut,//フェードアウト
		enState_Idle,
	};
	EnState m_state = enState_Idle;//状態
	
};

