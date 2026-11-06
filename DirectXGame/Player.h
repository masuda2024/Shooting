#pragma once
#include "KamataEngine.h"
#include "P_Bullet.h"
#include "AllRound.h"
#include <numbers>
#include <list>


class Player 
{
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

	// デストラクタ
	~Player();

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	// 弾の攻撃
	void Attack();

	// 範囲攻撃
	void Attack2();

	// 弾のリストを取得（読み取り専用）
	const std::list<P_Bullet*>& GetBullets() const { return p_bullets_; }

	// 範囲攻撃のリストを取得（読み取り専用）
	const std::list<AllRound*>& GetRound() const { return allRounds_; }

	// 当たり判定サイズ
	static inline const float kWidth = 1.5f;
	static inline const float kHeight = 1.0f;

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// 3Dレティクル用ワールド変換
	KamataEngine::WorldTransform worldTransform3DReticle_;

	// キーボード入力
	KamataEngine::Input* input_ = nullptr;

	// カーソルモデル
	KamataEngine::Model* modelCursor_ = nullptr;

	// テクスチャ
	uint32_t textureHandle_ = 0;

	// 通常弾
	std::list<P_Bullet*> p_bullets_;

	// 範囲攻撃
	std::list<AllRound*> allRounds_;

	// 発射タイマー
	int32_t fireTimer_ = 0;

	// 発射間隔
	static const int kFireInterval = 30;
};
