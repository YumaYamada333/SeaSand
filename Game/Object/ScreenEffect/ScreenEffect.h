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
		FadeIn,
		FadeOut
	};

private:
	// �ݒ莞��
	int m_setting_time;
	// �v���p�̎���
	int m_time;
	// �I������
	bool m_is_finished;
	// RGBA
	DirectX::SimpleMath::Vector4 m_rgba;

	//// �g�p�����ʃG�t�F�N�g
	//void(*m_effect)();

	// �^�C�v
	Type m_type;

	// ������
	ScreenEffect(int time, DirectX::SimpleMath::Vector4 rgba, Type type);

public:
	// �j��
	~ScreenEffect();

	// �G�t�F�N�g�̐���
	static ScreenEffect* Create(Type type, int time, DirectX::SimpleMath::Vector4 rgba);

	// ����͍s��Ȃ�
	bool Collision(const ObjectBase& obj) override { return false; };

	// �X�V
	void Update() override;

	// ���W�X�V
	void Move() override;

	// �`��
	void Render() const override;

	// ��Ԃ̎擾
	bool IsFinished() const;

private:
	// �t�F�[�h�C��
	void FadeInAction();

	// �t�F�[�h�A�E�g
	void FadeOutAction();

};
