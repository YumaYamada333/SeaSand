//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.h
//!
//! @brief  �N���A�V�[���̃w�b�_�t�@�C��
//!
//! @date   2016/12/12
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"

class Clear : public GameBase 
{
private:
	// �v���C�̃X�R�A(�ǂ����Ŏ擾)
	int m_score;
	// ����
	float m_time;
	// �w�i����
	Texture* m_message_image;
	// �w�i�摜
	Texture* m_back_image;
	Texture* m_back1_image;
	// ����
	Texture* m_score_number_image;
public:
	Clear();
	~Clear();
	void Update();
	void Render();
};
