#pragma once
class Player;
class Tuika;
class Teki:public IGameObject
{
public:
	Teki();
	~Teki();
	bool Start();
	void Update();
	void Move();

	void Render(RenderContext& rc);
	ModelRender modelRender;//���f�������_�[
	Player* m_player;
	Tuika* tuika = nullptr;
	void SetPosition(const Vector3& pos)
	{
		m_position = pos * 10.0f;
	}
	void AddPosition(const Vector3& pos) {
		m_position += pos;
	}
	void SetRotation(const Quaternion& rotation)
	{
		rot = rotation;
	}
	void SetScale(const Vector3& scal)
	{
		Scale.x = scal.x * 7.0f;
		Scale.y = scal.y * 5.0f;
		Scale.z = scal.z * 7.0f;
	}
	Vector3 toPlayer;//�v���C���[�ɑ΂���x�N�g��
	float distToPlayer;//�v���C���[�Ƃ̋���
	EffectEmitter* m_effectEmitter = nullptr;//�G�t�F�N�g
	float tekispeed = 20.0f;//�G�̃X�s�[�h
	SoundSource* soundSource = nullptr;
	PointLight* pointLight = nullptr;
	Vector3 lightPosition;
private:
	Vector3 m_position = Vector3::Zero;//�G�̍��W
	Vector3 Scale;//�G�̑傫��
	Quaternion rot;//�G�̉�]
	float r = 0.0f;
};

