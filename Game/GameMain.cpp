//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// ヘッダファイルの読み込み ================================================
#define _GAMEMAIN_
#include "GameMain.h"
#include "GameBase.h"
#include "GamePlay.h"
#include "GameTitle.h"
#include "GameClear.h"
#include "GameLogo.h"
#include <ctime>
using namespace DirectX::SimpleMath;
using namespace DirectX;


// プロトタイプ宣言 ====================================================

// グローバル変数の定義 ====================================================
GameBase* base;

// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	//画像の読み込み
	g_TitleImage = new Texture(L"Resources\\Images\\TitleImage.png");	//タイトル画像

	//音の読み込み
	ADX2Le::Initialize("Resources\\Sounds\\SeeSand.acf");
	ADX2Le::LoadAcb("Resources\\Sounds\\WorkUnit_0\\CueSheet_0.acb", "Resources\\Sounds\\WorkUnit_0\\CueSheet_0.awb");

	g_key_old = 0;

	// TODO:最後はLogoに戻す
	//base =new Play();
	base = new Title();

	g_NextScene = g_scene;

}

//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//音
	ADX2Le::Update();

	//シーン管理
	if (g_NextScene != g_scene)
	{
		g_scene = g_NextScene;
		delete base;
		g_init = 0;


		//シーンごとの呼び出し
		switch (g_scene)
		{
		case LOGO:
			base = new Logo();
			break;

		case TITLE:
			base = new Title();
			break;

		case PLAY:
			base = new Play();
			break;

		case CLEAR:
			base = new Clear();
			break;
		}
	}

	g_key_old = g_key_code;
	base->Update();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{

	base->Render();
	
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	
	delete base;
	ADX2Le::Finalize();
}

//----------------------------------------------------------------------
//! @brief 数値描画処理(テクスチャがないためコメントアウト)
//!
//! @param[in] xy座標，数値n, Texture
//!
//! @return なし
//----------------------------------------------------------------------
void DrawNum(int x, int y, int grp_x, int grp_y, int grp_w, int grp_h, int n, Texture* handle)
{
	int w = n;		//計算用
	int i = 0;		//文字数

	struct Rect
	{
		int left;
		int top;
		int right;
		int bottom;
	};

	Rect rect = {grp_x, grp_y, grp_x + grp_w, grp_y + grp_h};

	float width = static_cast<float>(rect.right - rect.left);
	float height = static_cast<float>(rect.bottom - rect.top);
	Vector2 grp(static_cast<float>(rect.left), static_cast<float>(rect.top));
	const int number_size = static_cast<int>(width / 10);

	if (w == 0)
	{
		DrawRectTexture(x, y, static_cast<int>(grp.x), static_cast<int>(grp.y), static_cast<int>(number_size), static_cast<int>(height), handle);
	}
	else
	{
		while (w)
		{
			DrawRectTexture(x - i * number_size, y, static_cast<int>(grp.x) + (w % 10) * number_size, static_cast<int>(grp.y), number_size, static_cast<int>(height), handle);
			w = w / 10;
			i++;
		}
	}

}

//----------------------------------------------------------------------
//! @brief テクスチャの描画
//!
//! @param[in] xy座標，画像の始点xy, 画像の大きさwh, テクスチャ
//!
//! @return なし
//----------------------------------------------------------------------
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle)
{
	//rect = { leftupX, leftupY, rightdownX, rightdownY };
	RECT rect = { tex_x, tex_y, tex_x + tex_w, tex_y + tex_h };

	//Draw(テクスチャ, 場所 , 大きさ, 色合い, 回転(ラジアン), 回転するときの中心座標 , 拡大倍率)
	g_spriteBatch->Draw(handle->m_pTexture, Vector2((float)pos_x, (float)pos_y), &rect, 
							Colors::White, 0.0f, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
}

//----------------------------------------------------------------------
//! @brief ランダムで数字を出す(int)
//!
//! @param[in]　最大値 + 1
//!
//! @return なし
//----------------------------------------------------------------------
int GetRand(int num)
{
	return rand() % num;
}





