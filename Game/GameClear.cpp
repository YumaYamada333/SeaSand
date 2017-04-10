//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.cpp
//!
//! @brief  �Q�[���N���A�����̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameClear.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

//----------------------------------------------------------------------
//! @brief �Q�[���N���A�R���X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Clear::Clear()
	: m_score(0)
	, m_time(0.0f)
{
	// �摜�ǂݍ���
	m_back_image = new Texture(L"Resources\\Images\\ResultBackImage.png");
	m_back1_image = new Texture(L"Resources\\Images\\Result.png");
	m_message_image = new Texture(L"Resources\\Images\\ResultMessage_Result.png");
	m_score_number_image = new Texture(L"Resources\\Images\\Number.png");

	// ���U���gBGM�Đ�
	ADX2Le::Play(CRI_CUESHEET_0_RESULTBGM);
}

//----------------------------------------------------------------------
//! @brief �Q�[���N���A�f�X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Clear::~Clear()
{
	auto Delete = [](Texture** t)
	{
		if (t)
		{
			delete (*t);
			*t = nullptr;
		}
	};
		
	Delete(&m_back_image);
	Delete(&m_message_image);

	// ���U���gBGM��~
	ADX2Le::Stop();
}

//----------------------------------------------------------------------
//! @brief �Q�[���N���A����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Clear::Update()
{
	if (g_init == 0)
	{
		g_init = 1;
		m_score = g_score;
	}

	// �^�C�g���Ɉڍs
	if (g_keyTracker->pressed.Space)
	{ 
		g_NextScene = TITLE;
	}

}

//----------------------------------------------------------------------
//! @brief �Q�[���N���A�`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Clear::Render()
{
	//wchar_t buf[256];
	RECT rect;
	//swprintf_s(buf, 256, L"CLEAR");

	//g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));

	//DrawRectTexture(0.0f, 0.0f, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, m_back_image);
	DrawRectTexture(0.0f, 0.0f, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, m_back1_image);
	//DrawRectTexture(0.0f, 0.0f, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, m_message_image);

	DrawNum(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3, 0.0f, 0.0f, 640.0f, 128.0f, m_score, m_score_number_image);
}
