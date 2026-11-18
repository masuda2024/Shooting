#include <Windows.h>
#include "KamataEngine.h"
using namespace KamataEngine;



#pragma region シーン

#include "Game/Scenes/Title.h"
#include "Game/Scenes/Tutorial.h"
#include "Game/Scenes/Game.h"
#include "Game/Scenes/Clear.h"
#include "Game/Scenes/Over.h"
#include "Game/Scenes/BaseScene.h"



enum class Scene 
{
	kUnknown = 0,
	kTitle,
	kTutorial,
	kGame,
	kClear,
	kOver,
};
Scene scene = Scene::kUnknown;
BaseScene* currentScene = nullptr;



void ChangeScene();
void UpdateScene();
void DrawScene();


#pragma endregion



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_22_マスダ_アキヒロ_撃ちまくれ");

	// DirectXCommonインスタンスを取得する
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	#pragma region シーンの初期化
	// 最初のシーンの初期化
	scene = Scene::kTitle;

	Title* newScene = new Title();
	newScene->Initialize();

	currentScene = newScene;
	#pragma endregion



	// メインループ
	while (true)
	{
		// エンジンの更新
		if (KamataEngine::Update())
		{
			break;
		}

		// シーン切り替え
		ChangeScene();

		// 現在シーン更新
		UpdateScene();


		#pragma region 描画

		// 描画開始
		dxCommon->PreDraw();

		// 現在シーンの描画
		DrawScene();

		// 描画終了
		dxCommon->PostDraw();

		#pragma endregion


		//ゲームを終了してウインドウを閉じる
		if (scene == Scene::kTitle && static_cast<Title*>(currentScene)->IsFinishedGame())
		{
			break;
		}
	}



	#pragma region 解放

	// シーンの解放
	delete currentScene;
	currentScene = nullptr;

	#pragma endregion

	
	// エンジンの終了処理
	KamataEngine::Finalize();


	return 0;
}

void UpdateScene()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}


void ChangeScene()
{
	switch (scene)
	{
	case Scene::kTitle:

		if (static_cast<Title*>(currentScene)->IsFinishedT()) 
		{
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kTutorial;

			Tutorial* newScene = new Tutorial();
			newScene->Initialize();

			currentScene = newScene;
		}

		break;

	case Scene::kTutorial:

		if (static_cast<Tutorial*>(currentScene)->IsFinishedTU()) {
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kGame;

			Game* newScene = new Game();
			newScene->Initialize();

			currentScene = newScene;
		}

		break;

	case Scene::kGame:

		if (static_cast<Game*>(currentScene)->IsFinishedGAME())
		{
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kOver;

			Over* newScene = new Over();
			newScene->Initialize();

			currentScene = newScene;
		} else if (static_cast<Game*>(currentScene)->IsFinishedGAME2()) {
			int score = static_cast<Game*>(currentScene)->GetScore();

			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kClear;

			Clear* newScene = new Clear();
			newScene->Initialize();
			newScene->SetScore(score);

			currentScene = newScene;
		} else if (static_cast<Game*>(currentScene)->IsFinishedGAME3()) {
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kTitle;

			Title* newScene = new Title();
			newScene->Initialize();

			currentScene = newScene;
		}

		break;

	case Scene::kClear:

		if (static_cast<Clear*>(currentScene)->IsFinishedC())
		{
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kTitle;

			Title* newScene = new Title();
			newScene->Initialize();

			currentScene = newScene;
		} else if (static_cast<Clear*>(currentScene)->IsFinishedC2()) {
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kGame;

			Game* newScene = new Game();
			newScene->Initialize();

			currentScene = newScene;
		}

		break;

	case Scene::kOver:

		if (static_cast<Over*>(currentScene)->IsFinishedO())
		{
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kTitle;

			Title* newScene = new Title();
			newScene->Initialize();

			currentScene = newScene;
		} else if (static_cast<Over*>(currentScene)->IsFinishedO2()) {
			delete currentScene;
			currentScene = nullptr;

			scene = Scene::kGame;

			Game* newScene = new Game();
			newScene->Initialize();

			currentScene = newScene;
		}

		break;
	}
}

void DrawScene() 
{
	if (currentScene)
	{
		currentScene->Draw();
	}
}