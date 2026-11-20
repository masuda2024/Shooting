#include <Windows.h>
#include <memory>

#include "KamataEngine.h"
using namespace KamataEngine;

#include "Game/Managers/SceneManager.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_22_マスダ_アキヒロ_撃ちまくれ");

	// DirectXCommonインスタンスを取得する
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// SceneManagerの生成
	SceneManager sceneManager;

	// 最初のシーンを初期化
	sceneManager.Initialize();

	// メインループ
	while (true)
	{
		// エンジンの更新
		if (KamataEngine::Update())
		{
			break;
		}

		// シーン遷移の確認
		sceneManager.CheckSceneTransition();

		// シーン更新
		sceneManager.Update();

		#pragma region 描画

		// 描画開始
		dxCommon->PreDraw();

		 // シーン描画
		sceneManager.Draw();

		// 描画終了
		dxCommon->PostDraw();

		#pragma endregion


		// ゲーム終了判定
		if (sceneManager.IsFinished())
		{
			break;
		}
	}


	// エンジンの終了処理
	KamataEngine::Finalize();


	return 0;
}