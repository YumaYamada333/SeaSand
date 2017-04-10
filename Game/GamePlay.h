//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  �v���C�V�[���̃w�b�_�t�@�C��
//!
//! @date   2016/12/12
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"
#include "Object\Player.h"

class Food;

//�萔
const int FOOD_NUM = 4;		//��ʓ���1�x�ɏo�Ă���H�ނ̐�
const int BREAD_NUM = 5;	//�p���̎c�薇��

//�N���X
class Play:public GameBase
{
private:
	// �w�i�摜
	Texture* m_backplay_image;	// �w�i
	Player** m_bread;			// �H�p��
	Food* m_food[FOOD_NUM];
	int m_bread_num;			//�p���̎c�薇��
	bool m_wave_clear;			//1WAVE���I��������ǂ����̔���
	
	// screen�G�t�F�N�g
	ObjectBase* m_screen_effect;

	void InitBread();			// �p��������
	void ReleaseBread();		// �p���J��
	void FoodAwake();			// �H�ނ̏o��
	void UpdateWave();			// WAVE�̍X�V����

public:
	Play();
	~Play();
	void Update();
	void Render();

};
