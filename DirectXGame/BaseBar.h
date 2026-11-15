#pragma once
#include "KamataEngine.h"

class BaseBar
{
public:
	virtual ~BaseBar() = default;

	// 初期化
	virtual void Initialize(uint32_t textureHandle) = 0;

	// 更新
	virtual void Update(uint32_t hp) = 0;

	// 描画
	virtual void Draw() = 0;

protected:
	// テクスチャ
	uint32_t textureHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Sprite* sprite2_ = nullptr;

	 // バーの設定
	float posY_ = 0.0f;
	float maxWidth_ = 1280.0f;

	// 背景色
	KamataEngine::Vector4 backgroundColor_;

	// ゲージ色
	KamataEngine::Vector4 barColor_;
};