#pragma once
#include <memory>
#include "../Scenes/BaseScene.h"

#include "../Scenes/Title.h"
#include "../Scenes/Tutorial.h"
#include "../Scenes/Game.h"
#include "../Scenes/Clear.h"
#include "../Scenes/Over.h"

enum class SceneType
{
	kUnknown = 0,
	kTitle,
	kTutorial,
	kGame,
	kClear,
	kOver,
};

class SceneManager 
{
public:
	void Initialize();
	void Update();
	void Draw();

	void ChangeScene(SceneType nextScene, uint32_t score = 0);

	SceneType GetCurrentSceneType() const { return currentSceneType_; }

	void CheckSceneTransition();
	bool IsFinished() const;

private:
	// Factory Pattern：シーンの生成
	std::unique_ptr<BaseScene> CreateScene(SceneType sceneType, uint32_t score = 0);

private:
	std::unique_ptr<BaseScene> scene_;
	SceneType currentSceneType_ = SceneType::kUnknown;
};
