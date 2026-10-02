#pragma once
#include "KamataEngine.h"
#include "P_Bullet.h"
#include"AllRound.h"
#include <numbers>



class Player 
{
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();


	~Player();

	// キーボード入力
	KamataEngine::Input* input_ = nullptr;


	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();


	// カーソル
	KamataEngine::Model* modelCursor_ = nullptr;
	



	// 弾
	void Attack();
	std::list<P_Bullet*> p_bullets_;
	


	#pragma region 範囲攻撃
	
	
	// 発射タイマー
	int32_t fireTimer_ = 0;
	// 発射間隔
	static const int kFireInterval = 30;

	
	
	void Attack2();
	std::list<AllRound*> allRounds_;
	
    #pragma endregion




	





	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 1.5f;
	static inline const float kHeight = 1.0f;



	const std::list<P_Bullet*>& GetBullets() const { return p_bullets_; }


	const std::list<AllRound*>& GetRound() const { return allRounds_; }



private:
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// カメラ
	KamataEngine::Camera* camera_;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	
	
	
	
	// 3Dレティクル用ワールド変換
	KamataEngine::WorldTransform worldTransform3DReticle_;

	




	// テクスチャー
	uint32_t textureHandle_;
};
