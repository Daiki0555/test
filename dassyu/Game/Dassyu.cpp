#include "stdafx.h"
#include "Dassyu.h"
#include "Player.h"
#include "Tuika.h"
#include "Teki.h"
#include "GameCamera.h"
Dassyu::~Dassyu()
{

}
bool Dassyu::Start()
{
	player = FindGO<Player>("player");
	gacame = FindGO<GameCamera>("gamecamera");
	tuika = FindGO<Tuika>("tuika");
	teki = FindGO<Teki>("inseki");
	modelRender.Init("Assets/modelData/dassyu/dassyu.tkm");
	modelRender.SetPosition(position);
	modelRender.SetRotation(rot);
	modelRender.SetScale(Scale);
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/dassyu.wav");
	
	return true;
}
void Dassyu::Update()
{
	Vector3 diff = player->GetPosition() - position;
	//ƒ_ƒbƒVƒ…”Ô‚ð“¥‚ñ‚¾‚©‚ÂDassyuState‚ªtrue‚È‚ç‚Î
	if (diff.Length() <= 200.0f && dasyuBG == false) {
		soundSource = NewGO<SoundSource>(0);
		soundSource->Init(14);
		soundSource->Play(false);
		dasyuBG = true;
	}
	if (diff.Length() <= 200.0f){	
		player->speed +=1.2f;
		gacame->dassyu = this;
		DassyuState = false;
	}
	
	if (DassyuState == false) {
		DassyuTime -= g_gameTime->GetFrameDeltaTime();
	}
	//DassyuTime‚ª0.0•b‚¢‚©‚É‚È‚Á‚½‚ç
	if (DassyuTime <= 0.0f) {
		DassyuState = true;
		if (player->hitState == false)
		{
			player->speed = 20.0f;
		}
		DassyuTime = 3.0f;
	}

	modelRender.Update();
}
void Dassyu::Render(RenderContext& rc)
{
	modelRender.Draw(rc);

}