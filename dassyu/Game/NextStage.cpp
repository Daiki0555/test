#include "stdafx.h"
#include "NextStage.h"
#include"BackGround.h"
#include"Gost.h"
#include"Coin.h"
#include"Teki.h"
#include"Dassyu.h"
#include"Player.h"
#include"Tuika.h"
NextStage::NextStage()
{
}
NextStage::~NextStage()
{
	QueryGOs<BackGround>("asiba", [&](BackGround* background)
		{
			DeleteGO(background);
			return true;
		});
	QueryGOs<Coin>("coin", [&](Coin* coin)
		{
			DeleteGO(coin);
			return true;
		});
	QueryGOs<Gost>("gost", [&](Gost* gost)
		{
			DeleteGO(gost);
			return true;
		});
	QueryGOs<Teki>("inseki", [&](Teki* teki)
		{
			DeleteGO(teki);
			return true;
		});
	QueryGOs<Dassyu>("dassyu", [&](Dassyu* dassyu)
		{
			DeleteGO(dassyu);
			return true;
		});
	QueryGOs<Tuika>("tuika", [&](Tuika* tuika)
		{
			DeleteGO(tuika);
			return true;
		});
}
bool NextStage::Start()
{
	return true;
}
void NextStage::Update()
{

}
void NextStage::NextSt(Vector3 pos)
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	QueryGOs<BackGround>("asiba", [&](BackGround* background)
	{
		DeleteGO(background);
		return true;
	});
	QueryGOs<Coin>("coin", [&](Coin* coin)
	{
		DeleteGO(coin);
		return true;
	});
	QueryGOs<Gost>("gost", [&](Gost* gost)
		{
			DeleteGO(gost);
			return true;
		});
	QueryGOs<Teki>("inseki", [&](Teki* teki)
		{
			DeleteGO(teki);
			return true;
		});
	QueryGOs<Dassyu>("dassyu", [&](Dassyu* dassyu)
		{
			DeleteGO(dassyu);
			return true;
		});
	QueryGOs<Tuika>("tuika", [&](Tuika* tuika)
		{
			DeleteGO(tuika);
			return true;
		});

	//新しくステージの作成
	leverRender = new LevelRender;
	stagerand=rand() % 2 + 1;
	switch (stagerand)
	{
	case 1:
		leverRender->Init("Assets/level/stage.tkl",
			[&](LevelObjectData& objData)
			{
				//名前がstaggeだったら
				if (objData.EqualObjectName(L"asiba") == true)
				{
					//背景のオブジェクトを作成する
					background = NewGO<BackGround>(0, "asiba");
					background->SetPosition(objData.position);
					background->AddPosition(pos);
					background->SetRotaition(objData.rotation);
					background->SetScale(objData.scale);
					return true;
				}
				else if (objData.EqualObjectName(L"hantei") == true)
				{
					gost = NewGO<Gost>(0, "gost");
					gost->SetPosition(objData.position);
					gost->AddPosition(pos);
					gost->SetRotation(objData.rotation);
					gost->SetScale(objData.scale);
					return true;
				}
				else if (objData.EqualObjectName(L"koin") == true)
				{
					coin = NewGO<Coin>(0, "coin");
					coin->SetPosition(objData.position);
					coin->AddPosition(pos);
					coin->SetScale(objData.scale);
					coin->SetRotaition(objData.rotation);
					return true;
				}
				else if (objData.EqualObjectName(L"inseki") == true)
				{
					teki = NewGO<Teki>(0, "inseki");
					teki->SetPosition(objData.position);
					teki->AddPosition(pos);
					teki->SetScale(objData.scale);
					teki->SetRotation(objData.rotation);
					return true;
				}
				else if (objData.EqualObjectName(L"dasyu") == true)
				{
					dassyu = NewGO<Dassyu>(0, "dassyu");
					dassyu->SetPosition(objData.position);
					dassyu->AddPosition(pos);
					dassyu->SetScale(objData.scale);
					dassyu->SetRotation(objData.rotation);
					return true;
				}
				else if (objData.EqualObjectName(L"sakuseiasiba") == true)
				{
					tuika = NewGO<Tuika>(0, "tuika");
					tuika->SetPosition(objData.position);
					tuika->AddPosition(pos);
					tuika->SetRotaition(objData.rotation);
					tuika->SetScale(objData.scale);
					return true;
				}
				return true;
			});
		break;
	case 2:
		leverRender->Init("Assets/level/stage2.tkl",
			[&](LevelObjectData& objData)
			{
				//名前がstaggeだったら
				if (objData.EqualObjectName(L"asiba") == true)
				{
					//背景のオブジェクトを作成する
					background = NewGO<BackGround>(0, "asiba");
					background->SetPosition(objData.position);
					background->AddPosition(pos);
					background->SetRotaition(objData.rotation);
					background->SetScale(objData.scale);
					return true;
				}
				else if (objData.EqualObjectName(L"hantei") == true)
				{
					gost = NewGO<Gost>(0, "gost");
					gost->SetPosition(objData.position);
					gost->AddPosition(pos);
					gost->SetRotation(objData.rotation);
					gost->SetScale(objData.scale);
					return true;
				}
				else if (objData.EqualObjectName(L"koin") == true)
				{
					coin = NewGO<Coin>(0, "coin");
					coin->SetPosition(objData.position);
					coin->AddPosition(pos);
					coin->SetScale(objData.scale);
					coin->SetRotaition(objData.rotation);
					return true;
				}
				else if (objData.EqualObjectName(L"inseki") == true)
				{
					teki = NewGO<Teki>(0, "inseki");
					teki->SetPosition(objData.position);
					teki->AddPosition(pos);
					teki->SetScale(objData.scale);
					teki->SetRotation(objData.rotation);
					return true;
				}
				else if (objData.EqualObjectName(L"dasyu") == true)
				{
					dassyu = NewGO<Dassyu>(0, "dassyu");
					dassyu->SetPosition(objData.position);
					dassyu->AddPosition(pos);
					dassyu->SetScale(objData.scale);
					dassyu->SetRotation(objData.rotation);
					return true;
				}
				else if (objData.EqualObjectName(L"sakuseiasiba") == true)
				{
					tuika = NewGO<Tuika>(0, "tuika");
					tuika->SetPosition(objData.position);
					tuika->AddPosition(pos);
					tuika->SetRotaition(objData.rotation);
					tuika->SetScale(objData.scale);
					return true;
				}
				return true;
			});
		break;
	}
	
	// 削除
	delete leverRender;
}