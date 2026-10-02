#pragma once
#include "KamataEngine.h"


#include "MyMath.h"
#include <list>
#include "Fade.h"



#include "Effect.h"



#include "Stage.h"

#include"Player.h"
#include "GraphBar.h"
#include "SkillBar.h"


#include "Enemy.h"


#include"DrawNumber.h"

class Game 
{
public:

	void Initialize();
	void Update();
	void Draw();
	~Game();

	#pragma region ゲームの状態管理

	bool gameActive = true;


	// 終了フラグ
	
	// デス(オーバー)フラグのgetter
	bool finishedGAME_ = false;
	bool IsFinishedGAME() const { return finishedGAME_; } // ゲームオーバー

	// 敵を倒した場合の(クリア)フラグ
	bool finishedGAME2_ = false;
	bool IsFinishedGAME2() const { return finishedGAME2_; } ////ゲームクリア

	// タイトルに戻る
	bool finishedGAME3_ = false;
	bool IsFinishedGAME3() const { return finishedGAME3_; } ////ゲームクリア


	#pragma endregion

	
	// エフェクト生成
	void EffectBorn(KamataEngine::Vector3 position);


	

	// 衝突判定
	void CheckAllCollisions();


	//デバッグカメラ
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;


	uint32_t GetScore() const;

private:
	
	
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// カメラ
	KamataEngine::Camera camera_;
	


	// テクスチャハンドル
	uint32_t textureHandleStage_ = 0;
	// クラス
	Stage* stage_ = nullptr;




	#pragma region エフェクト

	KamataEngine::Model* modelEffect_ = nullptr;
	// エフェクト一覧
	std::list<Effect*> effects_;

	uint32_t OFF_Effect = true;
	uint32_t ON_Effect = false;

	// エフェクト発生の間隔（例: 30フレームに1回 = 約0.5秒に1回）
	const int kEffectInterval = 60;
	// 発射タイマー
	int effectTimer_ = 0;


	#pragma endregion

	


	// 制限時間
	GraphBar* graphBar_ = nullptr;
	uint32_t textureHandleGraph_ = 0;
	float time_ = 1280.0f;
	

	// スキル
	SkillBar* skillBar_ = nullptr;
	float skill_ = 0.0f;
	float MaxSkill_ = 1280.0f;
	bool skillActive_ = false;
	bool c_skillUp = true;


	#pragma region プレイヤー


	Player* player_ = nullptr;
	// 3Dモデル
	KamataEngine::Model* modelPlayer_ = nullptr;


	#pragma endregion

	

	#pragma region 敵

	//Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;
	// 3Dモデル
	KamataEngine::Model* modelEnemy_ = nullptr;

	int32_t enemyCount = 10;
    #pragma endregion










	// スコア
	uint32_t textureHandleNumber_ = 0;
	DrawNumber* drawNumber_ = nullptr;
	int gameScore_ = 0;
	

    
	#pragma region UI・ポーズ画面

	// ESC
	uint32_t ESC_Handle_ = 0;
	KamataEngine::Sprite* ESC_Sprite_ = nullptr;

	// ESC
	uint32_t ESC_Handle_2 = 0;
	KamataEngine::Sprite* ESC_Sprite_2 = nullptr;

	// ポーズ画面時のUI
	uint32_t PoseUI_Handle_ = 0;
	KamataEngine::Sprite* PoseUI_Sprite_ = nullptr;

	uint32_t PoseUI_Handle_2 = 0;
	KamataEngine::Sprite* PoseUI_Sprite_2 = nullptr;

	uint32_t PoseUI2_Handle_ = 0;
	KamataEngine::Sprite* PoseUI2_Sprite_ = nullptr;

	uint32_t PoseUI2_Handle_2 = 0;
	KamataEngine::Sprite* PoseUI2_Sprite_2 = nullptr;





	#pragma endregion

	#pragma region 効果音

	uint32_t explosion_ = 0;
	uint32_t cannon_ = 0;

	#pragma endregion

	#pragma region フェーズ・フェード

	// ゲームのフェーズ(型)
	enum class Phase 
	{
		kFadeIn, // フェードイン
		kPlay,   // ゲームプレイ
		kPose,
		kDeath,      // プレイヤーのデス演出
		kEnemyDeath, // 敵のデス演出
		kFadeOut,    // フェードアウト(オーバー)
		kFadeOut2,   // フェードアウト(クリア)
		kFadeOut3,   // フェードアウト(タイトルに戻る)
	};

	// ゲームの現在フェーズから開始
	Phase phase_;

	// フェーズの切り替え
	// void ChangePhase();

	// フェード
	Fade* fade_ = nullptr;
	#pragma endregion

};
