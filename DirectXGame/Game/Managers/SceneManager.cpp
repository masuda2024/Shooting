#include "SceneManager.h"

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

void SceneManager::ChangeScene(std::unique_ptr<BaseScene> newScene)
{
	scene_ = std::move(newScene);
}
