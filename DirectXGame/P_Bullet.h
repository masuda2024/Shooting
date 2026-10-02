#pragma once
#include "KamataEngine.h"
#include "MyMath.h"


class Enemy;
class P_Bullet
{
public:

	#pragma region 基本構成

	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);
	void Update();
	void Draw(const KamataEngine::Camera& camera);

	#pragma endregion

	KamataEngine::Model* model_P_Bullet_ = nullptr;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;




	// 速度
	KamataEngine::Vector3 PB_velocity_;
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	

	#pragma region 状態

	// 寿命
	static const int32_t kLifeTime = 30 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_pb_ = false;
	bool IsDead_PB() const { return isDead_pb_; }

	#pragma endregion

	#pragma region 衝突判定の準備

	// 当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	#pragma endregion


	

	#pragma region 衝突判定 [ プレイヤーの弾  <<===>>  敵 ]
	
	
	// AABBを取得
	AABB GetAABB();
	// 衝突応答
	void OnCollition(const Enemy* enemy);
	
	
	#pragma endregion


private:
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_;

	KamataEngine::Vector3 velocity_ = {};



	


	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

};
