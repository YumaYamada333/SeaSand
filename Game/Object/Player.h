/*-------------------------------------
�v���C���[�N���X(Player.h)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* ���d�C���N���[�h�h�~ */
#pragma once

/* �C���N���[�h�t�@�C�� */
#include "ObjectBase.h"
#include "../../Common.h"

/* �N���X�̒�` */
class Player :public ObjectBase
{
public:
	Player(Texture* handle = nullptr, const RECT& grp = RECT(), const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0, BREAD_TYPE type = BREAD_TYPE::UP);	// �R���X�g���N�^
	~Player();		// �f�X�g���N�^

	void Update() override;								// �X�V
	void Render() const override;

	void MoveLeft();	// ���ړ�
	void MoveRight();	// �E�ړ�
	void MoveReset();	// �ړ����Z�b�g

	void Sand();		// �͂���
	bool IsSand();		// �͂���ł�H(�ړ��̂݁B���͕�)

	void Enter();		// ����
	bool IsEnter();		// ���ꒆ�H
	void Exit();		// �ޏ�
	bool IsExit();		// �ޏꒆ�H

private:
	/* �����o�֐� */
	void Move() override;		// �ړ�

	bool IsEnterComplete();		// ���ꊮ�������H
	bool IsExitComplete();		// �ޏꊮ�������H(�p������ʊO�ɏo��)

	/* �����o�ϐ� */
	static const float SPEED_X;		// ���x�w
	static const float SPEED_Y;		// ���x�x

	static const int SCREEN_WIDTH;

	BREAD_TYPE m_type;		// �p���^�C�v

	bool m_is_enter;	// ���ꒆ�H
	bool m_is_exit;		// �ޏꒆ�H

};