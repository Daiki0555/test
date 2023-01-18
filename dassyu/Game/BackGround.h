#pragma once
class BackGround :public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	//�`��֐�
	void Render(RenderContext& rc);
	//���f�������_�[
	ModelRender modelRender;
	//�����蔻��
	PhysicsStaticObject phyStaticObject;
	//���x���̃|�W�V����
	void SetPosition(const Vector3& pos)
	{
		position = pos * 10.0f;
		
	}
	void AddPosition(const Vector3& pos) {
		position += pos;
	}
	//���x���̉�]
	void SetRotaition(const Quaternion& rotaition)
	{
		rot = rotaition;
	}
	void SetScale(const Vector3& scal)
	{
		Scale = scal * 10.0f;
	}

private:
	//�ꏊ
	Vector3 position;
	//�傫��
	Vector3 Scale;
	Quaternion rot;
	Quaternion rot2;

	bool playerDead = false; //�v���C���[�����񂾃t���O
};

