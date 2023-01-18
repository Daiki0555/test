#pragma once
class BackGround :public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	//描画関数
	void Render(RenderContext& rc);
	//モデルリンダー
	ModelRender modelRender;
	//当たり判定
	PhysicsStaticObject phyStaticObject;
	//レベルのポジション
	void SetPosition(const Vector3& pos)
	{
		position = pos * 10.0f;
		
	}
	void AddPosition(const Vector3& pos) {
		position += pos;
	}
	//レベルの回転
	void SetRotaition(const Quaternion& rotaition)
	{
		rot = rotaition;
	}
	void SetScale(const Vector3& scal)
	{
		Scale = scal * 10.0f;
	}

private:
	//場所
	Vector3 position;
	//大きさ
	Vector3 Scale;
	Quaternion rot;
	Quaternion rot2;

	bool playerDead = false; //プレイヤーが死んだフラグ
};

