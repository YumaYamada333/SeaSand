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
#include "Food\Food.h"

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
{
	
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
	//�H�ނ̔j��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		delete m_food[i];
	}
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
		//�߂������C��
		int line_num = GetRand(F_LINE_NUM);
		//�H�ނ̏o��
		for (int i = 0; i < FOOD_NUM; i++)
		{
			//�H�ނ̎��
			int food_type = GetRand(FOOD_TYPE_NUM);
			//�H�ނ̍s���p�^�[��
			int move_type = GetRand(F_MOVE_TYPE_NUM);
			m_food[i] = new Food(food_type, move_type, i, line_num);
		}

		g_init = 1;
	}	
	//�H�ނ̍X�V
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i]->Update();
	}

	//�H�ނ̈ړ�
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i]->Move();
	}
	/*if (g_mouse.leftButton)
	{
		g_NextScene = CLEAR;
	}*/
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
	wchar_t buf[256];

	swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));

	//�H�ނ̕`��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i]->Render();
	}
}
