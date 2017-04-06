//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.h
//!
//! @brief  �I�u�W�F�N�g�x�[�X�N���X�̒�`
//!
//! @date   ���t�@2017�N1��30��
//!
//! @author ����Җ�	Ryuna Tsuji
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�[�C���N���[�h
#include <d3d11.h>
#include <SimpleMath.h>
#include "..\..\DirectXTK.h"
#include "..\..\Texture.h"

//�@�N���X��`
class ObjectBase
{
protected:
	// �I�u�W�F�N�g�S�̂̊�_
	static const DirectX::SimpleMath::Vector2 objectPoint;

	// �O���t�B�b�N�n���h�� 
	Texture* mHandle;
	// ���摜
	RECT mGrp;
	// ��_
	DirectX::SimpleMath::Vector2 mCenter;
	// ���W
	DirectX::SimpleMath::Vector2 mPos;
	// ���x
	DirectX::SimpleMath::Vector2 mSpd;
	// ���
	int mState;		

public:
	// ������
	ObjectBase();
	ObjectBase(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0);

	// �j��
	virtual ~ObjectBase();

	// �n���h��
	const Texture* SetHandle(Texture* handle);
	const Texture* GetHandle() const;

	// ���摜
	const RECT& SetGrp(const RECT& rect);
	const RECT& ObjectBase::GetGrp() const;

	// ���W
	const DirectX::SimpleMath::Vector2 ObjectBase::SetPos(const DirectX::SimpleMath::Vector2& pos);
	const DirectX::SimpleMath::Vector2 ObjectBase::GetPos() const;

	// ���x
	const DirectX::SimpleMath::Vector2 SetSpd(const DirectX::SimpleMath::Vector2& spd);
	const DirectX::SimpleMath::Vector2 GetSpd() const;

	// ���
	int SetState(int state);
	int GetState() const;

	// ����
	virtual void Update();

	// �����蔻��
	virtual bool Collision(const ObjectBase& obj);

	// ���W�X�V
	virtual void Move();

	// ���茋��
	virtual void Result();

	// �`��
	virtual void Render() const;
};
