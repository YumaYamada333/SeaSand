//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once

#ifndef _GAMEMAIN_
#define EXTERN extern
#else
#define EXTERN
#endif

#include<windows.h>
#include<d3d11.h>
#include<SimpleMath.h>
#include"..\DirectXTK.h"
#include"..\Texture.h"
#include"..\ADX2Le.h"
#include"CueSheet_0.h"
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// 定数の定義 ==============================================================

// ゲームタイトル
#define GAME_TITLE "SeaSand"

// ゲーム画面
const int SCREEN_WIDTH = 640;    // 幅[pixel]
const int SCREEN_HEIGHT = 480;   // 高さ[pixel]

//　列挙型宣言
enum SCENE
{
	LOGO,
	TITLE,
	PLAY,
	CLEAR,
};

// グローバル変数の定義 ====================================================

EXTERN int g_key_code;			//キー情報
EXTERN int g_key_old;			//前フレームのキー情報

EXTERN int g_scene;				//シーン管理
EXTERN int g_NextScene;			//次のシーン
EXTERN int g_init;				//初期化管理

EXTERN int g_TimeCnt;				//時間カウンタ
EXTERN int g_Time;					//秒数

extern int g_score;		//スコア

// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);

//　数値描画処理
//void DrawNum(int x, int y, int n);
void DrawNum(int x, int y, int grp_x, int grp_y, int grp_w, int grp_h, int n, Texture* handle);

//テクスチャの描画(テクスチャがないためコメントアウト)
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle);

//ランダムゲット
int GetRand(int num);
