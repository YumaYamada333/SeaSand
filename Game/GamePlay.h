//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  �v���C�V�[���̃w�b�_�t�@�C��
//!
//! @date   2017/04/07
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"
#include "Object\Player.h"

class Food;

//�萔��������������������������������������������������������������������������
const int FOOD_NUM = 4;		//��x�ɏo������H�ނ̐�

//�N���X������������������������������������������������������������������������
class Play:public GameBase
{
private:
	Player** m_bread;		// �H�p��
	Food* m_food[FOOD_NUM];
	
	void InitBread();		// �p��������
	void ReleaseBread();	// �p���J��

public:
	Play();
	~Play();
	void Update();
	void Render();
};
