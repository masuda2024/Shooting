#include "SkillBar.h"

using namespace KamataEngine;

// デストラクタ
SkillBar::~SkillBar()
{
	delete sprite_;
	delete sprite2_;
}

// 初期化
void SkillBar::Initialize(uint32_t textureHandle)
{
	textureHandle_ = textureHandle;
	// スプライト
	sprite_ = Sprite::Create(textureHandle_, {0, 60});
	sprite2_ = Sprite::Create(textureHandle_, {0, 60});
}

// 更新
void SkillBar::Update(uint32_t hp)
{
	sprite_->SetColor({0.1f, 0.1f, 0.1f, 0.7f});
	sprite_->SetSize({1280, 30});
	sprite2_->SetColor({1.0f, 1.0f, 0.0f, 0.5f});
	sprite2_->SetSize({(float)hp, 30});
}

// 描画
void SkillBar::Draw()
{
	sprite_->Draw();
	sprite2_->Draw();
}
