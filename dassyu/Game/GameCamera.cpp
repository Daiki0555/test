#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"
#include "Dassyu.h"
GameCamera::GameCamera()
{

}
GameCamera::~GameCamera()
{

}
bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	toCameraPos.Set(0.0f, 150.0f, -400.0f);
	//�v���C���[�C���X�^���X��T��
	player = FindGO<Player>("player");
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);
	return true;
}
void GameCamera::Update()
{
	if (player->rakkaState) {
		return;
	}

		//�J������->�X�V
		//�����_���X�V����
		Vector3 target = player->position;
		//�d�͂���̎��ɃJ���������ɓ�����
		switch (player->GrabityState)
		{
		case 0:
			target.y += 10.0f;
			break;
		case 1:
			target.y -= 10.0f;
			target.x -= 50.0f;
			break;
		case 2:
			target.y -= 200.0f;
			break;
		case 3:
			target.y -= 10.0f;
			target.x += 50.0f;
			break;
		}
		if (dassyu != nullptr) {
			if (dassyu->DassyuState == false) {
				target.z = player->position.z + 100.0f;
			}
		}
		pos = target + toCameraPos;
		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
		g_camera3D->SetNear(1.0f);
		//�J�����̍X�V
	    g_camera3D->Update();
	}
	