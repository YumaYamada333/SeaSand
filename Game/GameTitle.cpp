//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.cpp
//!
//! @brief  �^�C�g�������̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameTitle.h"
#include "Object\ScreenEffect\ScreenEffect.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//----------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Title::Title()
{
	// �^�C�g��BGM�Đ�
	ADX2Le::Play(CRI_CUESHEET_0_TITLEBGM, 1.0f, true);
	// �摜�ǂݍ���
	m_titleback_image = new Texture(L"Resources\\Images\\TitleBackImage.png");
	m_titlelogo_image = new Texture(L"Resources\\Images\\TitleLogo.png");
	m_titlesteat_image = new Texture(L"Resources\\Images\\TitleSteat.png");
	
	// �J�E���^������
	m_next_scene_cnt = 0;

}

//----------------------------------------------------------------------
//! @brief �f�X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Title::~Title()
{
	ADX2Le::Stop();

	if (m_screen_effect)
	{
		delete m_screen_effect;
	}
}

//----------------------------------------------------------------------
//! @brief �^�C�g������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Title::Update()
{
	if (g_init == 0)
	{
		g_init = 1;
		g_TimeCnt = 0;
	}

	// screen���ʂ̍X�V
	if (m_screen_effect)
	{
		m_screen_effect->Update();
		if (dynamic_cast<ScreenEffect*>(m_screen_effect)->IsFinished())
		{
			g_NextScene = PLAY;
		}
		return;
	}

	g_TimeCnt++;
	//�X�y�[�X�L�[�_�ŗp
	if (g_TimeCnt > 120)
	{
		g_TimeCnt = 0;
	}

	if (g_keyTracker->pressed.Space)
	{
		// ��ʌ��ʂ̐���
		m_screen_effect = ScreenEffect::Create(ScreenEffect::Type::FadeOut, 1.5f * 60, Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	}

	// screen���ʂ̍��W�ύX
	if (m_screen_effect)
	{
		m_screen_effect->Move();
	}

}

//----------------------------------------------------------------------
//! @brief �^�C�g���`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Title::Render()
{
	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p
	//wchar_t buf[256];	//������ҏW�p
	DrawRectTexture(0.0f, 0.0f, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, m_titleback_image);
	DrawRectTexture(0.0f, 0.0f, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, m_titlelogo_image);
	

	/*rect = { 0, 160, 256, 224 };
	g_spriteBatch->Draw(g_TitleImage->m_pTexture, Vector2(0, 192),
		&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(2.5, 2.5));*/
	rect = { 0, 224, 150, 256 };
	if (g_TimeCnt < 60)
	{
		g_spriteBatch->Draw(m_titlesteat_image->m_pTexture, Vector2(250, 380),
			&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
	}
	/*swprintf_s(buf, 256, L"TITLE");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));*/

	// screen�G�t�F�N�g�̕`��
	if (m_screen_effect)
	{
		m_screen_effect->Render();
	}

}