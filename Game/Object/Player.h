/*-------------------------------------
�v���C���[�N���X(Player.h)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* ���d�C���N���[�h�h�~ */
#pragma once

/* �C���N���[�h�t�@�C�� */
#include "ObjectBase.h"

/* �N���X�̒�` */
class Player :public ObjectBase
{
public:
	Player(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0);	// �R���X�g���N�^
	~Player();		// �f�X�g���N�^

};