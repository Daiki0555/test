#include "stdafx.h"
#include "BackGround.h"
#include "Tuika.h"
BackGround::BackGround()
{
	

}
BackGround::~BackGround()
{

}
bool BackGround::Start()
{
    //���f����ǂݍ���
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/asiba.tkm");
	//���W5�̕ύX
	modelRender.SetPosition(position);
    //�傫���̕ύX
	modelRender.SetScale(Scale);
	//��]�̕ύX
	modelRender.SetRotation(rot);
	//�傫���̕ύX�����邽�߂ɁA���f�����X�V
	modelRender.Update();
	return true;
}
void BackGround::Update()
{
	//�傫���̕ύX�����邽�߂ɁA���f�����X�V
	modelRender.Update();
}
void BackGround::Render(RenderContext& rc)
{
	//�w�i�̕`��
	modelRender.Draw(rc);
}