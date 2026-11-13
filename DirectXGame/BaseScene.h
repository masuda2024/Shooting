#pragma once

class BaseScene 
{
public:
	virtual ~BaseScene() = default;

	// シーンの更新
	virtual void Update() = 0;

	// シーンの描画
	virtual void Draw() = 0;
};