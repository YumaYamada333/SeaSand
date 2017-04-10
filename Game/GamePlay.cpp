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
#include "Food\Food.h"
#include "Object\MessagePlate\MessagePlate.h"

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
	,m_bread_num(BREAD_NUM)
	,m_wave_clear(false)
	,m_time(0)
	,m_plate(nullptr)
{
	//�|�C���^�̏�����
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i] = nullptr;
	}

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

	//�H�ނ̔j��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		delete m_food[i];
	}
	//���b�Z�[�W�̔j��
	delete m_plate;
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
		//m_time++;
		//�v���[�g�̏o��
		if (m_plate == nullptr)
		{
			m_plate = new MessagePlate(START);
		}
		
		//�v���[�g����������
		if (m_plate->GetState() == MP_NONE)
		{
			//�v���[�g�̔j��
			delete m_plate;
			m_plate = nullptr;

			//�H�ނ̏o��
			FoodAwake();

			g_init = 1;
		}
	}

	m_bread[UP]->MoveReset();
	m_bread[DOWN]->MoveReset();

	/* �L�[���� */
	//TODO:�֐������
	if (!(m_bread[UP]->IsSand()))
	{
		if (g_key.Left)					// ���ړ�
		{
			m_bread[UP]->MoveLeft();
			m_bread[DOWN]->MoveLeft();
		}
		else if (g_key.Right)			// �E�ړ�
		{
			m_bread[UP]->MoveRight();
			m_bread[DOWN]->MoveRight();
		}
		else if (g_keyTracker->pressed.Space)			// �͂���
		{
			m_bread[UP]->Sand(UP);
			m_bread[DOWN]->Sand(DOWN);
		}
	

	m_bread[UP]->Update();
	m_bread[DOWN]->Update();
		
	}	
	//�H�ނ̍X�V
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//�H�ނ����݂��Ă����ԂȂ�
		if (m_food[i] != nullptr)
		{
			m_food[i]->Update();
		}
	}
	//���b�Z�[�W�̍X�V
	if (m_plate != nullptr)
	{
		m_plate->Update();
	}

	//�H�ނ̈ړ�
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//�H�ނ����݂��Ă����ԂȂ�
		if (m_food[i] != nullptr)
		{
			m_food[i]->Move();
		}
	}
	//���b�Z�[�W�̈ړ�
	if (m_plate != nullptr)
	{
		m_plate->Move();
	}

	//�p���ƐH�ނ�����������
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//�H�ނ����݂��Ă����ԂȂ�
		if (m_food[i] != nullptr)
		{
			if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_food[i]))) &&
				m_bread[UP]->IsSand())
			{
				m_food[i]->HitBread(*m_bread[UP]);
			}
			if (m_bread[DOWN]->Collision(*(dynamic_cast<ObjectBase*>(m_food[i]))) &&
				m_bread[DOWN]->IsSand())
			{
				m_food[i]->HitBread(*m_bread[DOWN]);
			}
		}
	}

	/* �p�����m�̂����蔻�� */
	if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_bread[DOWN]))))
	{
		m_bread[UP]->SetSpd(Vector2(0.0f, 0.0f));
		m_bread[DOWN]->SetSpd(Vector2(0.0f, 0.0f));
	}

	//WAVE�̍X�V
	UpdateWave();

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
	m_bread[UP]->Render();
	m_bread[DOWN]->Render();

	//�H�ނ̕`��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//�H�ނ����݂��Ă����ԂȂ�
		if (m_food[i] != nullptr)
		{
			m_food[i]->Render();
		}
	}

	//���b�Z�[�W�̕`��
	if (m_plate != nullptr)
	{
		m_plate->Render();
	}

	wchar_t buf[256];
	swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));
}

//----------------------------------------------------------------------
//! @brief WAVE�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Play::UpdateWave()
{
	//�ړ����̋������Ȃ���΃N���A
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//�H�ނ����݂��Ă����ԂȂ�
		if (m_food[i] != nullptr)
		{
			if (m_food[i]->GetState() == F_NONE)
			{
				m_wave_clear = true;
			}
			else
			{
				m_wave_clear = false;
			}
		}
	}
	//�N���A���̏���
	if (m_wave_clear)
	{
		//�v���[�g�̏o��
		if (m_plate == nullptr)
		{
			if (m_bread_num > 1)
			{
				m_plate = new MessagePlate(NEXT);
			}
			else
			{
				m_plate = new MessagePlate(FINISH);
			}
		}

		//�v���[�g����������WAVE�؂�ւ�
		if (m_plate->GetState() == MP_NONE)
		{
			//�v���[�g�̔j��
			delete m_plate;
			m_plate = nullptr;

			//�H�ނ̉��
			for (int i = 0; i < FOOD_NUM; i++)
			{
				delete m_food[i];
				m_food[i] = nullptr;
			}
			//�p���̖��������炷
			m_bread_num--;
			//�p���̖������c���Ă�����
			if (m_bread_num > 0)
			{
				//�H�ނ̍ďo��
				FoodAwake();
			}
			else
			{
				//�Q�[���I��
				g_NextScene = CLEAR;
			}
		}
	}
}

//----------------------------------------------------------------------
//! @brief �H�ނ��o��������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Play::FoodAwake()
{
	//�H�ނ��߂������C��
	int line_num = GetRand(F_LINE_NUM);
	//�H�ނ��W�܂鎞��
	int meet_time = GetRand(WAVE_TIME) + 1;
	//�H�ނ̏o��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//�H�ނ̎��
		int food_type = GetRand(FOOD_TYPE_NUM);
		//�o��
		m_food[i] = new Food(food_type, i, line_num, meet_time);
	}
	//wave���J�n
	m_wave_clear = false;
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

	const RECT    BREAD_RECT           = { 0,0,180,180 };
	const Vector2 BREAD_POS[BREAD_NUM] = { Vector2(100.0f,100.0f),Vector2(100.0f,400.0f) };

	/* �p������ */
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
