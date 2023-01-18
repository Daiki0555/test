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
	int loadcount=0;//load��؂�ւ������
	int loadAtai = 13;//loadcount�ɍ��킹��l
	enum EnAnimationClip {//�A�j���[�V����
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v
	//�t�F�[�h�C��
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	//�t�F�[�h�A�E�g
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}
	//�t�F�[�h��
	const bool IsFade()const
	{
		return m_state != enState_Idle;
	}
	//���l���擾
	const float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}
	float m_currentAlpha = 1.0f;//���݂̃��n�B
private:
	enum EnState {
		enState_FadeIn, //�t�F�[�h�C��
		enState_FadeOut,//�t�F�[�h�A�E�g
		enState_Idle,
	};
	EnState m_state = enState_Idle;//���
	
};

