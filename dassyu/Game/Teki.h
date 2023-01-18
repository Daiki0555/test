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
	ModelRender modelRender;//モデルリンダー
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
	Vector3 toPlayer;//プレイヤーに対するベクトル
	float distToPlayer;//プレイヤーとの距離
	EffectEmitter* m_effectEmitter = nullptr;//エフェクト
	float tekispeed = 20.0f;//敵のスピード
	SoundSource* soundSource = nullptr;
	PointLight* pointLight = nullptr;
	Vector3 lightPosition;
private:
	Vector3 m_position = Vector3::Zero;//敵の座標
	Vector3 Scale;//敵の大きさ
	Quaternion rot;//敵の回転
	float r = 0.0f;
};

