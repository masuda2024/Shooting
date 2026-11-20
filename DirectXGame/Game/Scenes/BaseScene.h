#pragma once

class BaseScene 
{
public:
	virtual ~BaseScene() = default;
	
	// シーンの初期化
	virtual void Initialize() = 0;

	// シーンの更新
	virtual void Update() = 0;

	// シーンの描画
	virtual void Draw() = 0;
};