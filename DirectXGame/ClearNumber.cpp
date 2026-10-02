#include "ClearNumber.h"
using namespace KamataEngine;


// デストラクタ
ClearNumber::~ClearNumber() 
{
	for (int i = 0; i < 10; i++)
	{
		delete sprite_[i];
	}
}

// 初期化
void ClearNumber::Initialize(uint32_t textureHandle)
{
	textureHandle_ = textureHandle;
	// スプライト
	for (int i = 0; i < 10; i++)
	{
		sprite_[i] = Sprite::Create(textureHandle_, {140.0f + size.x * i, 270});
	}
}

// 更新
void ClearNumber::Update(uint32_t number)
{
	for (int i = 0; i < 10; i++)
	{
		sprite_[i]->SetSize(size);
		sprite_[i]->SetTextureRect({0, 0}, size);
	}

	(void)number;

	// 最初に割る数値
	int32_t digit = 1000000000LL;
	// 5桁分ループ
	for (int i = 0; i < 10; i++) 
	{
		// 今の桁の数値を取り出す
		int nowNumber = number / digit;
		// 今の桁の数値の部分を切り出すようにする
		sprite_[i]->SetTextureRect({size.x * nowNumber, 0}, {size.x, size.y});

		// 残りの桁の数値にする
		number %= digit;
		// 桁をずらす
		digit /= 10;
	}
}

// 描画
void ClearNumber::Draw() 
{
	for (int i = 0; i < 10; i++)
	{
		sprite_[i]->Draw();
	}
}
