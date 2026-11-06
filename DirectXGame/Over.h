#pragma once
#include "Fade.h"
#include "KamataEngine.h"
class Over 
{
public:

	// 終了フラグ
	bool IsFinishedO() const { return finishedO_; }
	// リトライ
	
	bool IsFinishedO2() const { return finishedO_2; }

	void Initialize();
	void Update();
	void Draw();

	// デストラクタ
	~Over();
	
private:
	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	enum class Phase
	{
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};
	
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	#pragma region UI

	uint32_t OverFontHandle_ = 0;
	KamataEngine::Sprite* OverFontSprite_ = nullptr;

	
	uint32_t UI_R_Handle_ = 0;
	KamataEngine::Sprite* UI_RSprite_ = nullptr;
	uint32_t UI_R_Handle_2 = 0;
	KamataEngine::Sprite* UI_RSprite_2 = nullptr;

	uint32_t UI_T_Handle_ = 0;
	KamataEngine::Sprite* UI_TSprite_ = nullptr;
	uint32_t UI_T_Handle_2 = 0;
	KamataEngine::Sprite* UI_TSprite_2 = nullptr;

	#pragma endregion

	// フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	uint32_t Botan_ = 0;

	bool finishedO_ = false;
	bool finishedO_2 = false;
	
};