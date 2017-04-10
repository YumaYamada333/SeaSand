//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScreenEffect.cpp
//!
//! @brief  ��ʌ��ʃN���X�̃����o��`
//!
//! @date   2017/04/07
//!
//! @author �җ���
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include "ScreenEffect.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//�O���[�o���ϐ��������������������������������������������������������������|

//�֐��̒�`�����������������������������������������������������������������|
//----------------------------------------------------------------------
//! @brief ��ʌ��ʐ���
//!
//! @param[in] �Ȃ�
//----------------------------------------------------------------------
ScreenEffect::ScreenEffect(int time, Vector4 rgba, Type type)
	: m_setting_time(time)
	, m_time(0)
	, m_rgba(rgba)
	, m_type(type)
	, m_is_finished(false)
{
	m_grp = { 0,0,640,480 };
	m_handle = new Texture(L"Resources\\Images\\BlackImage.png");
}

//----------------------------------------------------------------------
//! @brief ��ʌ��ʔj��
//----------------------------------------------------------------------
ScreenEffect::~ScreenEffect()
{

}

//----------------------------------------------------------------------
//! @brief ����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
ScreenEffect* ScreenEffect::Create(Type type, int time, Vector4 rgba)
{
	ScreenEffect* effect = nullptr;

	effect = new ScreenEffect(time, rgba, type);

	return effect;
}

//----------------------------------------------------------------------
//! @brief ����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ScreenEffect::Update()
{
	// �G�t�F�N�g���Ƃɏ���
	switch (m_type)
	{
	case ScreenEffect::FadeIn:
		if (m_rgba.w > 0.0f)
		{
			m_rgba.w -= static_cast<float>(m_time) / m_setting_time;
		}
		else m_is_finished = true;
		break;
	case ScreenEffect::FadeOut:
		if (m_rgba.w < 1.0f)
		{
			m_rgba.w += static_cast<float>(m_time) / m_setting_time;
		}

		break;
	default:
		break;
	}

	m_time++;
}

//----------------------------------------------------------------------
//! @brief ���W�X�V
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ScreenEffect::Move()
{
	ObjectBase::Move();
}

//----------------------------------------------------------------------
//! @brief ��ʌ��ʕ`��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ScreenEffect::Render() const
{
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &m_grp
		, m_rgba, 0.0f, m_center, Vector2(1.0f, 1.0f));

}

//----------------------------------------------------------------------
//! @brief ��Ԃ̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
bool ScreenEffect::IsFinished() const
{
	return m_is_finished;
}

//----------------------------------------------------------------------
//! @brief �t�F�[�h�C��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ScreenEffect::FadeInAction()
{
	m_rgba.z -= static_cast<float>(m_time) / m_setting_time;
}

//----------------------------------------------------------------------
//! @brief �t�F�[�h�A�E�g
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ScreenEffect::FadeOutAction()
{
	m_rgba.z += static_cast<float>(m_time) / m_setting_time;
}
