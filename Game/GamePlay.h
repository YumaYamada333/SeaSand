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

//�N���X
class Play:public GameBase
{
private:
	static enum		// �p�����
	{
		UP,		// ��̃p��
		DOWN,	// ���̃p��
	};

	Player** m_bread;		// �H�p��
	
	void InitBread();		// �p��������
	void ReleaseBread();	// �p���J��

public:
	Play();
	~Play();
	void Update();
	void Render();
};
