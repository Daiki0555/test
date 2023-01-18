#include "stdafx.h"
#include "Teki.h"
#include "Player.h"
#include "Tuika.h"
Teki::Teki()
{
	

}
Teki::~Teki()
{

}
bool Teki:: Start()
{

	//プレイヤーを呼び出す
	m_player = FindGO<Player>("player");
	tuika = FindGO<Tuika>("tuika");
	
	//敵の読み込み
	modelRender.Init("Assets/modelData/isi/teki.tkm");
	modelRender.SetPosition(m_position);
	modelRender.SetRotation(rot);
	modelRender.SetScale(Scale);
	//エフェクトを読み込む
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/bakuha.efk");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/bakuhatu.wav");
	
	//ポイントライトを作成する
	pointLight = new PointLight;
	pointLight->Init();
	//ポイントライトの色
	pointLight->SetColor(Vector3(1.5f, 0.5, 0.4f));
	//ポイントライトの影響範囲
	pointLight->SetRange(800.0f);
	pointLight->SetAffectPowParam(3.0f);

	return true;
}
void Teki::Update()
{
	Move();
	r += 0.05f;
	rot.SetRotation({ -1.0f, -1.0f, 0.0f }, r);
	modelRender.SetRotation(rot);
	modelRender.SetPosition(m_position);
	modelRender.Update();
	lightPosition = m_position;
	pointLight->SetPosition(lightPosition);
	pointLight->Update();
}
void Teki::Move()
{
	//敵からプレイヤーに向かって伸びるベクトルを計算する。
	toPlayer = m_player->position - m_position;
	distToPlayer = toPlayer.Length();
	if (distToPlayer<= 4500.0f) {
		m_position.z-= 20.0f;
		//プレイヤーの距離が近いなら
		if (distToPlayer <= 250.0f) {
			//エフェクトを生成
			m_effectEmitter = NewGO<EffectEmitter>(0);
			m_effectEmitter->Init(0);
			m_effectEmitter->SetScale({ 50.0f,50.0f,50.0f });
			m_effectEmitter->Play();
			soundSource = NewGO<SoundSource>(5);
			soundSource->Init(5);
			soundSource->Play(false);
			Vector3 efPos = m_position;
			m_effectEmitter->SetPosition(efPos);
			m_player->speed = 0.0;
			m_player->hitState = true;
			DeleteGO(this);
		}
	}
	
	
}
void Teki::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}