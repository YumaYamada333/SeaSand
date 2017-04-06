//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#ifndef _GAMEMAIN_
#define EXTERN extern
#else
#define EXTERN
#endif

#include<windows.h>
#include<d3d11.h>
#include<SimpleMath.h>
#include"..\DirectXTK.h"
#include"..\Texture.h"
#include"..\ADX2Le.h"
#include"CueSheet_0.h"


// �萔�̒�` ==============================================================

// �Q�[���^�C�g��
#define GAME_TITLE "SeaSand"

// �Q�[�����
const int SCREEN_WIDTH = 640;    // ��[pixel]
const int SCREEN_HEIGHT = 480;   // ����[pixel]

//�@�񋓌^�錾
enum SCENE
{
	LOGO,
	TITLE,
	PLAY,
	CLEAR,
};

// �O���[�o���ϐ��̒�` ====================================================

EXTERN int g_key_code;			//�L�[���
EXTERN int g_key_old;			//�O�t���[���̃L�[���

EXTERN int g_scene;				//�V�[���Ǘ�
EXTERN int g_NextScene;			//���̃V�[��
EXTERN int g_init;				//�������Ǘ�

// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);

//�@���l�`�揈��
//void DrawNum(int x, int y, int n);

//�e�N�X�`���̕`��(�e�N�X�`�����Ȃ����߃R�����g�A�E�g)
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle);

//�����_���Q�b�g
int GetRand(int num);



