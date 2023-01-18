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

	//�v���C���[���Ăяo��
	m_player = FindGO<Player>("player");
	tuika = FindGO<Tuika>("tuika");
	
	//�G�̓ǂݍ���
	modelRender.Init("Assets/modelData/isi/teki.tkm");
	modelRender.SetPosition(m_position);
	modelRender.SetRotation(rot);
	modelRender.SetScale(Scale);
	//�G�t�F�N�g��ǂݍ���
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/bakuha.efk");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/bakuhatu.wav");
	
	//�|�C���g���C�g���쐬����
	pointLight = new PointLight;
	pointLight->Init();
	//�|�C���g���C�g�̐F
	pointLight->SetColor(Vector3(1.5f, 0.5, 0.4f));
	//�|�C���g���C�g�̉e���͈�
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
	//�G����v���C���[�Ɍ������ĐL�т�x�N�g�����v�Z����B
	toPlayer = m_player->position - m_position;
	distToPlayer = toPlayer.Length();
	if (distToPlayer<= 4500.0f) {
		m_position.z-= 20.0f;
		//�v���C���[�̋������߂��Ȃ�
		if (distToPlayer <= 250.0f) {
			//�G�t�F�N�g�𐶐�
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