#pragma once
#include "KamataEngine.h"
class ClearNumber 
{
public:
	// デストラクタ
	~ClearNumber();

	// 初期化
	void Initialize(uint32_t textureHandle);

	// 更新
	void Update(uint32_t number);

	// 描画
	void Draw();

private:
	// テクスチャー
	uint32_t textureHandle_;
	// スプライト
	KamataEngine::Sprite* sprite_[10] = {};
	// サイズ
	KamataEngine::Vector2 size = {100.0f, 200.0f};
};
