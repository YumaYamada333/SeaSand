/*-------------------------------------
�v���C���[�N���X(Player.h)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* ���d�C���N���[�h�h�~ */
#pragma once

/* �C���N���[�h�t�@�C�� */
#include "ObjectBase.h"

/* �g�p����^ */
enum  BREAD_TYPE;

/* �N���X�̒�` */
class Player :public ObjectBase
{
public:
	Player(Texture* handle = nullptr, const RECT& grp = RECT(), const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0);	// �R���X�g���N�^
	~Player();		// �f�X�g���N�^

	void Update() override;		// �X�V

	void MoveLeft();	// ���ړ�
	void MoveRight();	// �E�ړ�
	void MoveReset();	// �ړ����Z�b�g

	void Sand(BREAD_TYPE type);	// �͂���
	bool IsSand();				// �͂���ł�H(�ړ��̂݁B���͕�)

private:
	/* �����o�֐� */
	void Move()   override;		// �ړ�
	
	/* �����o�ϐ� */
	static const float SPEED_X;		// ���x�w
	static const float SPEED_Y;		// ���x�x
};