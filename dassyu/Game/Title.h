#pragma once
class Fade;
class Game;
class Title :public IGameObject
{
public:
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Game* game = nullptr;
	Fade* fade = nullptr;
	float alpha = 2.0f;
	float asobialpha = 2.0f;
	bool isWaitFadeout = false;
	bool titleState = false;
	bool unityState = false;
	bool setumeiState = false;
	bool gameloopState = false;
	SoundSource* soundSource = nullptr;
	SoundSource* soundSource2 = nullptr;
	Vector3 modelPos=Vector3{ 100.0f, -50.0f, 0.0f };
	Vector3 modelScale = Vector3{ 1.5f,1.5f,1.5f };
	Quaternion rot;
	SpriteRender titleRender;
	SpriteRender gastRender;//ゲームスタートの文字
	SpriteRender asobiRender;//遊び方の文字
	SpriteRender botanRender;
	SpriteRender kuroiro;
	SpriteRender setumeiRender;
	ModelRender titleModel;
	enum EnAnimationClip {//アニメーション
		enAnimationClip_Clear,
		enAnimationClip_Num,
	};
	AnimationClip animClips[enAnimationClip_Num];//アニメーションクリップ
};

