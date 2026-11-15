#include "BaseBar.h"

using namespace KamataEngine;

// デストラクタ
BaseBar::~BaseBar() 
{
	delete sprite_;
	delete sprite2_;

	sprite_ = nullptr;
	sprite2_ = nullptr;
}

// 更新
void BaseBar::Update(uint32_t hp) 
{
	if (!sprite_ || !sprite2_) 
	{
		return;
	}

	sprite_->SetColor(backgroundColor_);
	sprite_->SetSize({maxWidth_, 30});

	sprite2_->SetColor(barColor_);
	sprite2_->SetSize({(float)hp, 30});
}

// 描画
void BaseBar::Draw() 
{
	if (!sprite_ || !sprite2_)
	{
		return;
	}

	sprite_->Draw();
	sprite2_->Draw();
}