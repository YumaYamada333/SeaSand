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
#include <ctime>
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
	srand(static_cast<unsigned int>(time(nullptr)));
	//�摜�̓ǂݍ���
	g_TitleImage = new Texture(L"Resources\\Images\\TitleImage.png");	//�^�C�g���摜

	//���̓ǂݍ���
	ADX2Le::Initialize("Resources\\Sounds\\SeeSand.acf");
	ADX2Le::LoadAcb("Resources\\Sounds\\WorkUnit_0\\CueSheet_0.acb", "Resources\\Sounds\\WorkUnit_0\\CueSheet_0.awb");

	g_key_old = 0;

	// TODO:�Ō��Logo�ɖ߂�
	//base =new Play();
	base = new Title();

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
	ADX2Le::Update();

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
	
	delete base;
	ADX2Le::Finalize();
}

//----------------------------------------------------------------------
//! @brief ���l�`�揈��(�e�N�X�`�����Ȃ����߃R�����g�A�E�g)
//!
//! @param[in] xy���W�C���ln, Texture
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawNum(int x, int y, int grp_x, int grp_y, int grp_w, int grp_h, int n, Texture* handle)
{
	int w = n;		//�v�Z�p
	int i = 0;		//������

	struct Rect
	{
		int left;
		int top;
		int right;
		int bottom;
	};

	Rect rect = {grp_x, grp_y, grp_x + grp_w, grp_y + grp_h};

	float width = static_cast<float>(rect.right - rect.left);
	float height = static_cast<float>(rect.bottom - rect.top);
	Vector2 grp(static_cast<float>(rect.left), static_cast<float>(rect.top));
	const int number_size = static_cast<int>(width / 10);

	if (w == 0)
	{
		DrawRectTexture(x, y, static_cast<int>(grp.x), static_cast<int>(grp.y), static_cast<int>(number_size), static_cast<int>(height), handle);
	}
	else
	{
		while (w)
		{
			DrawRectTexture(x - i * number_size, y, static_cast<int>(grp.x) + (w % 10) * number_size, static_cast<int>(grp.y), number_size, static_cast<int>(height), handle);
			w = w / 10;
			i++;
		}
	}

}

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





