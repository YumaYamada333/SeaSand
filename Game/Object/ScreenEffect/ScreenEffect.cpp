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
ScreenEffect::ScreenEffect()
	: m_setting_time(0)
	, m_time(0)
{

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
const ScreenEffect& ScreenEffect::Create(Type type)
{
	switch (type)
	{
	default:
		break;
	}
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
	float a = 
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &m_grp
		, Vector4(1.0f, 1.0f,1.0f, a), 0.0f, m_center, Vector2(1.0f, 1.0f));

}
