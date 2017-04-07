//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScreenEffect.h
//!
//! @brief  ��ʌ��ʃN���X�̒�`
//!
//! @date   2017/04/07
//!
//! @author �җ���
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include "..\ObjectBase.h"

class ScreenEffect : public ObjectBase
{
public:
	// �����^�C�v
	enum Type
	{
		Fade
	};
private:
	// �ݒ莞��
	int m_setting_time;
	// �v���p�̎���
	int m_time;

	// ������
	ScreenEffect();
public:
	// �j��
	~ScreenEffect();

	// �G�t�F�N�g�̐���
	const ScreenEffect& Create(Type type);

	// �����蔻��͍s��Ȃ�
	bool Collision(const ObjectBase& obj) override { return false; };

	// �X�V
	void Update() override;

	// ���W�X�V
	void Move() override;

	// �`��
	void Render() const override;

};
