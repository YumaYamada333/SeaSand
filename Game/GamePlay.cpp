//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  �Q�[���v���C�����̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GamePlay.h"
#include <cassert>		// assert

#include "../Common.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//�O���[�o���ϐ��������������������������������������������������������������|
int g_count;


//�֐��̒�`�����������������������������������������������������������������|
//----------------------------------------------------------------------
//! @brief �v���C�R���X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Play::Play()
	:m_bread(nullptr)
{
	InitBread();
}

//----------------------------------------------------------------------
//! @brief �v���C�f�X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Play::~Play()
{
	ReleaseBread();
}

//----------------------------------------------------------------------
//! @brief �Q�[���v���C����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Play::Update()
{
	//�V�[���̍ŏ��Ɉ�񂾂��s������������
	if (g_init == 0)
	{
		g_init = 1;
	}	

	if (g_mouse.leftButton)
	{
		g_NextScene = CLEAR;
	}
}

//----------------------------------------------------------------------
//! @brief �Q�[���v���C�`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Play::Render()
{
	m_bread[UP]->Render();
	m_bread[DOWN]->Render();

	wchar_t buf[256];
	swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));
}

/*------------------------------------
Play::InitPlayer

summary:�p��������
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Play::InitBread()
{
	// TODO:�p���̊e�p�����[�^�[�͂����ŕύX�I
	const int BREAD_NUM = 2;			// �p���̐�
	Texture* bread_handle = new Texture(L"Resources/Images/bread.png");
	assert(bread_handle != nullptr);

	const RECT    BREAD_RECT           = { 0,0,100,20 };
	const Vector2 BREAD_POS[BREAD_NUM] = { Vector2(100.0f,100.0f),Vector2(100.0f,400.0f) };

	/* �v���C���[���� */
	m_bread = new Player*[BREAD_NUM];	// ���I�z��m��
	m_bread[UP]   = new Player(bread_handle, BREAD_RECT, BREAD_POS[UP]);
	m_bread[DOWN] = new Player(bread_handle, BREAD_RECT, BREAD_POS[DOWN]);

}

/*------------------------------------
Play::ReleaseBread

summary:�p�����
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Play::ReleaseBread()
{
	DeleteMemory(m_bread[UP]);
	DeleteMemory(m_bread[DOWN]);
	DeleteArrayMemory(m_bread);
}
