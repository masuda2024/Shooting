#include "SkillBar.h"

using namespace KamataEngine;

// 初期化
void SkillBar::Initialize(uint32_t textureHandle)
{
	textureHandle_ = textureHandle;

	// 表示位置
	posY_ = 60.0f;

	// 色の設定
	backgroundColor_ = {0.1f, 0.1f, 0.1f, 0.7f};
	barColor_ = {1.0f, 1.0f, 0.0f, 0.5f};

	// スプライト生成
	sprite_ = Sprite::Create(textureHandle_, {0, posY_});
	sprite2_ = Sprite::Create(textureHandle_, {0, posY_});
}