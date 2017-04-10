//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.h
//!
//! @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
//!
//! @date   2016/12/12
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"

class Title:public GameBase
{
private:
	// �w�i�摜
	Texture* m_titleback_image;
	//�^�C�g�����S
	Texture* m_titlelogo_image;
	Texture* m_titlesteat_image;

public:
	Title();
	~Title();
	void Update();
	void Render();

};



