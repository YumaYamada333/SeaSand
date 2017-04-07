/*-------------------------------------
汎用ライブラリ(Common.h)

date  :2016.08.19
Author:Miyu Hara
-------------------------------------*/

/* 二重インクルードの防止 */
#pragma once

/* マクロ */
// ※この2つは関数化できなかったので、マクロ化
#define DeleteMemory(p)      {delete   p; p=nullptr;}	// 安全にメモリを解放
#define DeleteArrayMemory(p) {delete[] p; p=nullptr;}	// 安全にメモリを解放(配列版)