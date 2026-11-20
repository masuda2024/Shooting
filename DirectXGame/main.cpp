#include <Windows.h>
#include <memory>

#include "KamataEngine.h"
using namespace KamataEngine;





#include "Game/Scenes/Title.h"
#include "Game/Scenes/Tutorial.h"
#include "Game/Scenes/Game.h"
#include "Game/Scenes/Clear.h"
#include "Game/Scenes/Over.h"
#include "Game/Scenes/BaseScene.h"

#pragma region シーン

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
// 現在のシーン
std::unique_ptr<BaseScene> currentScene = nullptr;

void SetScene(Scene nextScene, uint32_t score = 0);
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

	// シーンの初期化
	// 最初のシーンを設定
	SetScene(Scene::kTitle);


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


		// ゲームを終了してウインドウを閉じる
		if (scene == Scene::kTitle && static_cast<Title*>(currentScene.get())->IsFinishedGame())
		{
			break;
		}
	}



	// シーンの解放
	currentScene.reset();

	
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


void SetScene(Scene nextScene, uint32_t score)
{
	std::unique_ptr<BaseScene> newScene;

	switch (nextScene) 
	{
	case Scene::kTitle:
	{
		auto title = std::make_unique<Title>();
		title->Initialize();
		newScene = std::move(title);
		break;
	}

	case Scene::kTutorial: 
	{
		auto tutorial = std::make_unique<Tutorial>();
		tutorial->Initialize();
		newScene = std::move(tutorial);
		break;
	}

	case Scene::kGame: 
	{
		auto game = std::make_unique<Game>();
		game->Initialize();
		newScene = std::move(game);
		break;
	}

	case Scene::kClear:
	{
		auto clear = std::make_unique<Clear>();
		clear->Initialize();
		clear->SetScore(score);
		newScene = std::move(clear);
		break;
	}

	case Scene::kOver:
	{
		auto over = std::make_unique<Over>();
		over->Initialize();
		newScene = std::move(over);
		break;
	}

	default:
		return;
	}

	// シーンを切り替える
	currentScene = std::move(newScene);

	scene = nextScene;
}

void ChangeScene()
{
	switch (scene)
	{
	case Scene::kTitle:

		if (static_cast<Title*>(currentScene.get())->IsFinishedT()) {
			SetScene(Scene::kTutorial);
		}

		break;

	case Scene::kTutorial:

		if (static_cast<Tutorial*>(currentScene.get())->IsFinishedTU()) {
			SetScene(Scene::kGame);
		}

		break;

	case Scene::kGame:

		if (static_cast<Game*>(currentScene.get())->IsFinishedGAME()) {
			SetScene(Scene::kOver);
		} else if (static_cast<Game*>(currentScene.get())->IsFinishedGAME2()) {
			uint32_t score = static_cast<Game*>(currentScene.get())->GetScore();

			SetScene(Scene::kClear, score);
		} else if (static_cast<Game*>(currentScene.get())->IsFinishedGAME3()) {
			SetScene(Scene::kTitle);
		}

		break;

	case Scene::kClear:

		if (static_cast<Clear*>(currentScene.get())->IsFinishedC()) {
			SetScene(Scene::kTitle);
		} else if (static_cast<Clear*>(currentScene.get())->IsFinishedC2()) {
			SetScene(Scene::kGame);
		}

		break;

	case Scene::kOver:

		if (static_cast<Over*>(currentScene.get())->IsFinishedO()) {
			SetScene(Scene::kTitle);
		} else if (static_cast<Over*>(currentScene.get())->IsFinishedO2()) {
			SetScene(Scene::kGame);
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