//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.cpp
//!
//! @brief  �I�u�W�F�N�g�x�[�X�N���X�̃����o��`
//!
//! @date   ���t�@2017�N1��30��
//!
//! @author ����Җ�	Ryuna Tsuji
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�[�C���N���[�h
#include "ObjectBase.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;

// ��_(����0.0f �` 1.0f�E��)
const Vector2 ObjectBase::objectPoint = Vector2(0.5f, 0.5f);

//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̏�����
//!
//! @param[in] �I�u�W�F�N�g�̏��
//----------------------------------------------------------------------
ObjectBase::ObjectBase()
{
}

ObjectBase::ObjectBase(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 spd, int state)
	: mHandle(handle)
	, mGrp(grp)
	, mCenter(Vector2(static_cast<float>(grp.right - grp.left), static_cast<float>(grp.bottom - grp.top)) * objectPoint)
	, mPos(pos)
	, mSpd(spd)
	, mState(state)
{
}

//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̔j��
//----------------------------------------------------------------------
ObjectBase::~ObjectBase()
{

}

//----------------------------------------------------------------------
//! @brief �e�N�X�`���̃Z�b�g
//!
//! @param[in] �e�N�X�`��
//!
//! @return ���݂̃e�N�X�`��
//----------------------------------------------------------------------
const Texture* ObjectBase::SetHandle(Texture* handle)
{
	return 	mHandle = handle;
}

//----------------------------------------------------------------------
//! @brief �e�N�X�`���̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return ���݂̃e�N�X�`��
//----------------------------------------------------------------------
const Texture* ObjectBase::GetHandle() const
{
	return mHandle;
}

//----------------------------------------------------------------------
//! @brief ��`�̃Z�b�g
//!
//! @param[in] ��`(RECT)
//!
//! @return ���݂̋�`
//----------------------------------------------------------------------
const RECT& ObjectBase::SetGrp(const RECT& rect)
{
	return mGrp = rect;
}

//----------------------------------------------------------------------
//! @brief ��`�̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return ���݂̋�`
//----------------------------------------------------------------------
const RECT& ObjectBase::GetGrp() const
{
	return mGrp;
}

//----------------------------------------------------------------------
//! @brief ���W�̃Z�b�g
//!
//! @param[in] ���W
//!
//! @return ���݂̍��W
//----------------------------------------------------------------------
const Vector2 ObjectBase::SetPos(const Vector2& pos)
{
	return mPos = pos;
}

//----------------------------------------------------------------------
//! @brief ���W�̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return ���݂̍��W
//----------------------------------------------------------------------
const Vector2 ObjectBase::GetPos() const
{
	return mPos;
}

//----------------------------------------------------------------------
//! @brief ���x�̃Z�b�g
//!
//! @param[in] ���x
//!
//! @return ���݂̑��x
//----------------------------------------------------------------------
const Vector2 ObjectBase::SetSpd(const Vector2& spd)
{
	return mSpd = spd;
}

//----------------------------------------------------------------------
//! @brief ���x�̎擾
//!
//! @param[in] ���x
//!
//! @return ���݂̑��x
//----------------------------------------------------------------------
const Vector2 ObjectBase::GetSpd() const
{
	return mSpd;
}

//----------------------------------------------------------------------
//! @brief ��Ԃ̃Z�b�g
//!
//! @param[in] ���
//!
//! @return ���݂̏��
//----------------------------------------------------------------------
int ObjectBase::SetState(int state)
{
	return mState = state;
}

//----------------------------------------------------------------------
//! @brief ��Ԃ̎擾
//!
//! @param[in] �Ȃ�
//!
//! @return ��Ԃ̎擾
//----------------------------------------------------------------------
int ObjectBase::GetState() const
{
	return mState;
}

//----------------------------------------------------------------------
//! @brief ����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Update()
{
	
}

//----------------------------------------------------------------------
//! @brief �X�V
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Move()
{
	// ���W�X�V
	mPos += mSpd;
}

//----------------------------------------------------------------------
//! @brief ���茋��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Result()
{
}

//----------------------------------------------------------------------
//! @brief �����蔻��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
bool ObjectBase::Collision(const ObjectBase& obj)
{
	int width = (mGrp.right - mGrp.left) / 2;
	int height = (mGrp.bottom - mGrp.top) / 2;
	RECT collisionBox = 
	{
		static_cast<LONG>(mPos.x - width),
		static_cast<LONG>(mPos.y - height),
		static_cast<LONG>(mPos.x + width),
		static_cast<LONG>(mPos.y + height)
	};

	width = (obj.mGrp.right - obj.mGrp.left) / 2;
	height = (obj.mGrp.bottom - obj.mGrp.top) / 2;
	RECT collisionObj =
	{
		static_cast<LONG>(obj.mPos.x - width),
		static_cast<LONG>(obj.mPos.y - height),
		static_cast<LONG>(obj.mPos.x + width),
		static_cast<LONG>(obj.mPos.y + height)
	};


	if (collisionBox.left < collisionObj.right &&
		collisionBox.top < collisionObj.bottom &&
		collisionBox.right > collisionObj.left &&
		collisionBox.bottom > collisionObj.top)
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
//! @brief �`��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ObjectBase::Render() const
{
	g_spriteBatch->Draw(mHandle->m_pTexture, mPos, &mGrp
		, Colors::White, 0.0f, mCenter, Vector2(1.0f, 1.0f));
}
