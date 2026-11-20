#pragma once
#include <memory>
#include "../Scenes/BaseScene.h"
class SceneManager 
{
public:
	// シーンの更新
	void Update();

	// シーンの描画
	void Draw();

	// シーン変更
	void ChangeScene(std::unique_ptr<BaseScene> newScene);

private:
	// 現在のシーン
	std::unique_ptr<BaseScene> scene_;
};
