#include "SceneManager.h"


std::unique_ptr<BaseScene> SceneManager::CreateScene(SceneType sceneType, uint32_t score)
{
	std::unique_ptr<BaseScene> newScene;

	switch (sceneType)
	{
	case SceneType::kTitle:
		newScene = std::make_unique<Title>();
		break;

	case SceneType::kTutorial:
		newScene = std::make_unique<Tutorial>();
		break;

	case SceneType::kGame:
		newScene = std::make_unique<Game>();
		break;

	case SceneType::kClear:
	{
		auto clear = std::make_unique<Clear>();
		clear->SetScore(score);
		newScene = std::move(clear);
		break;
	}

	case SceneType::kOver:
		newScene = std::make_unique<Over>();
		break;

	default:
		return nullptr;
	}

	if (newScene) 
	{
		newScene->Initialize();
	}

	return newScene;
}

void SceneManager::Initialize()
{ 
	ChangeScene(SceneType::kTitle);
}

void SceneManager::Update() 
{
	if (scene_) 
	{
		scene_->Update();
	}
}

void SceneManager::Draw()
{
	if (scene_) 
	{
		scene_->Draw();
	}
}

void SceneManager::ChangeScene(SceneType nextScene, uint32_t score) 
{
	std::unique_ptr<BaseScene> newScene = CreateScene(nextScene, score);

	if (!newScene)
	{
		return;
	}

	scene_ = std::move(newScene);
	currentSceneType_ = nextScene;
}

void SceneManager::CheckSceneTransition()
{
	switch (currentSceneType_) 
	{
	case SceneType::kTitle:
	{
		auto* title = dynamic_cast<Title*>(scene_.get());

		if (title && title->IsFinishedT()) 
		{
			ChangeScene(SceneType::kTutorial);
		}
		break;
	}

	case SceneType::kTutorial: 
	{
		auto* tutorial = dynamic_cast<Tutorial*>(scene_.get());

		if (tutorial && tutorial->IsFinishedTU()) 
		{
			ChangeScene(SceneType::kGame);
		}
		break;
	}

	case SceneType::kGame:
	{
		auto* game = dynamic_cast<Game*>(scene_.get());

		if (game && game->IsFinishedGAME())
		{
			ChangeScene(SceneType::kOver);
		} else if (game && game->IsFinishedGAME2()) 
		{
			uint32_t score = game->GetScore();
			ChangeScene(SceneType::kClear, score);
		} else if (game && game->IsFinishedGAME3())
		{
			ChangeScene(SceneType::kTitle);
		}
		break;
	}

	case SceneType::kClear: 
	{
		auto* clear = dynamic_cast<Clear*>(scene_.get());

		if (clear && clear->IsFinishedC()) 
		{
			ChangeScene(SceneType::kTitle);
		} else if (clear && clear->IsFinishedC2()) {
			ChangeScene(SceneType::kGame);
		}
		break;
	}

	case SceneType::kOver:
	{
		auto* over = dynamic_cast<Over*>(scene_.get());

		if (over && over->IsFinishedO()) 
		{
			ChangeScene(SceneType::kTitle);
		} else if (over && over->IsFinishedO2()) {
			ChangeScene(SceneType::kGame);
		}
		break;
	}

	default:
		break;
	}
}

bool SceneManager::IsFinished() const
{
	if (currentSceneType_ == SceneType::kTitle)
	{
		auto* title = dynamic_cast<Title*>(scene_.get());

		return title && title->IsFinishedGame();
	}

	return false;
}


