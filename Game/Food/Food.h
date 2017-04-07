//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Food.h
//!
//! @brief  �t�[�h�N���X�̃w�b�_�t�@�C��
//!
//! @date   2017/04/07
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

//�w�b�_�̃C���N���[�h����������������������������������������������������������
#include "..\Object\ObjectBase.h"

//�萔��������������������������������������������������������������������������

//�H�ނ̎�ނ̐�
const int FOOD_TYPE_NUM = 2;

//�s���p�^�[���̐�
const int F_MOVE_TYPE_NUM = 3;

//1WAVE�̎���
const int WAVE_TIME = 6;

//�H�ނ̎��
enum FOOD_TYPE
{
	FISH,
	CLAB,
};

//�H�ނ̏��
enum FOOD_STATE
{
	F_NONE,		//���݂��Ȃ�
	F_MOVE,		//�����Ă���
	F_HIT,		//�p���ɓ������Ă���
};

//�N���X������������������������������������������������������������������������
class Food : public ObjectBase
{
private:
	int m_food_type;		//�H�ނ̎��
	int m_move_type;		//�H�ނ̈ړ��p�^�[��
	int m_num;				//���ڂ̐H�ނ�
	float m_line;			//�H�ނ��ڎw�����C��(x���W)

public:
	Food(int food_type, int move_type, int food_num, int m_line);	// �R���X�g���N�^
	~Food();				// �f�X�g���N�^
	void Update();			// �X�V����
	void Move();			// ���W�X�V
	void Result();			// ���茋��
	//void Render() const;	// �`��

private:
	void SetTexture();		//�e�N�X�`����ݒ肷��֐�
	void SetInitPos(int line_num);		//�H�ނ̈ړ��p�^�[�����Ƃɏ����ʒu��ݒ肷��֐�
};