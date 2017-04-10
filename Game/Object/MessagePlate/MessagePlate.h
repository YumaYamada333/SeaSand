//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   MessagePlate.h
//!
//! @brief  ���b�Z�[�W�̃w�b�_�t�@�C��
//!
//! @date   2017/04/10
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
//�w�b�_�̃C���N���[�h����������������������������������������������������������
#include "..\ObjectBase.h"

//�萔��������������������������������������������������������������������������
//���
enum PLATE_TYPE
{
	START,
	NEXT,
	FINISH,
};

//���
enum PLATE_STATE
{
	MP_NONE,
	MP_MOVE,
};

//�N���X������������������������������������������������������������������������
class MessagePlate : public ObjectBase
{
private:
	int m_time;		//����
	int m_type;		//���

public:
	MessagePlate(int type);
	~MessagePlate();
	void Update();

private:
	void SetTexture();		//�e�N�X�`����ݒ肷��֐�
	void SetInitPos();		//�����ʒu��ݒ肷��֐�
};