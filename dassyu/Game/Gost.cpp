#include "stdafx.h"
#include "Gost.h"
#include "Player.h"
#include "Tuika.h"
Gost::Gost()
{
	
}
Gost::~Gost()
{
	QueryGOs<CollisionObject>("m_gost", [&](CollisionObject* colliOb)
		{
			DeleteGO(colliOb);
			return true;
		});
	
}
bool Gost::Start()
{
	player = FindGO<Player>("player");
	colliOb = NewGO<CollisionObject>(0);
	colliOb->CreateBox(position,
		rot,
		Vector3(170.0f,1200.0f,300.0f)/*Vector3(170.0f,1500.0f,300.0f)*/);
	colliOb->SetName("m_gost");
	colliOb->SetIsEnableAutoDelete(false);

	return true;
}
void Gost::Update()
{
	//modelRender.SetPosition(position);
	//modelRender.Update();
	
}

void Gost::Render(RenderContext& rc)
{
	//modelRender.Draw(rc);
}