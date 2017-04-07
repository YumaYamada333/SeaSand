//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#define _GAMEMAIN_
#include "GameMain.h"
#include "GameBase.h"
#include "GamePlay.h"
#include "GameTitle.h"
#include "GameClear.h"
#include "GameLogo.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

// �v���g�^�C�v�錾 ====================================================

// �O���[�o���ϐ��̒�` ====================================================
GameBase* base;

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{


	//���̓ǂݍ���
	/*ADX2Le::Initialize("Resources\\Sounds\\demo.acf");
	ADX2Le::LoadAcb("Resources\\Sounds\\CueSheet_0.acb", "Resources\\Sounds\\CueSheet_0.awb");*/

	g_key_old = 0;

	// TODO:�Ō��Logo�ɖ߂�
	base =new Play();
	g_NextScene = g_scene;

}




//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//��
	//ADX2Le::Update();

	//�V�[���Ǘ�
	if (g_NextScene != g_scene)
	{
		g_scene = g_NextScene;
		delete base;
		g_init = 0;


		//�V�[�����Ƃ̌Ăяo��
		switch (g_scene)
		{
		case LOGO:
			base = new Logo();
			break;

		case TITLE:
			base = new Title();
			break;

		case PLAY:
			base = new Play();
			break;

		case CLEAR:
			base = new Clear();
			break;
		}
	}

	g_key_old = g_key_code;
	base->Update();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{

	base->Render();
	
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	//ADX2Le::Finalize();
	
	delete base;
}


//----------------------------------------------------------------------
//! @brief ���l�`�揈��(�e�N�X�`�����Ȃ����߃R�����g�A�E�g)
//!
//! @param[in] xy���W�C���lw
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
//void DrawNum(int x, int y, int n)
//{
//	int w = n;		//�v�Z�p
//	int i = 0;		//������
//
//	if (w == 0)
//	{
//		DrawRectTexture(x, y, 0, 48, 25, 32, g_PongImage);
//	}
//	else
//	{
//		while (w)
//		{
//			DrawRectTexture(x - i * 25, y, (w % 10) * 25, 48, 25, 32, g_PongImage);
//			w = w / 10;
//			i++;
//		}
//	}
//
//}

//----------------------------------------------------------------------
//! @brief �e�N�X�`���̕`��
//!
//! @param[in] xy���W�C�摜�̎n�_xy, �摜�̑傫��wh, �e�N�X�`��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle)
{
	//rect = { leftupX, leftupY, rightdownX, rightdownY };
	RECT rect = { tex_x, tex_y, tex_x + tex_w, tex_y + tex_h };

	//Draw(�e�N�X�`��, �ꏊ , �傫��, �F����, ��](���W�A��), ��]����Ƃ��̒��S���W , �g��{��)
	g_spriteBatch->Draw(handle->m_pTexture, Vector2((float)pos_x, (float)pos_y), &rect, 
							Colors::White, 0.0f, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
}

//----------------------------------------------------------------------
//! @brief �����_���Ő������o��(int)
//!
//! @param[in]�@�ő�l + 1
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int GetRand(int num)
{
	return rand() % num;
}





