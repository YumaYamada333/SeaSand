/*-------------------------------------
�ėp���C�u����(Common.h)

date  :2016.08.19
Author:Miyu Hara
-------------------------------------*/

/* ��d�C���N���[�h�̖h�~ */
#pragma once

/* �}�N�� */
// ������2�͊֐����ł��Ȃ������̂ŁA�}�N����
#define DeleteMemory(p)      {delete   p; p=nullptr;}	// ���S�Ƀ����������
#define DeleteArrayMemory(p) {delete[] p; p=nullptr;}	// ���S�Ƀ����������(�z���)