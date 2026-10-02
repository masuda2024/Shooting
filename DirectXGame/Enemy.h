#pragma once
#include "KamataEngine.h"

#include <numbers>
#include "MyMath.h"

class P_Bullet;
class AllRound;
class Enemy 
{
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void Update();
	void Draw();
	~Enemy();
	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();
	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

	static inline const float kWidth = 3.0f;
	static inline const float kHeight = 4.0f;




	#pragma region 衝突判定 [ プレイヤーの弾  <<===>>  敵 ]

	// AABBを取得
	AABB GetAABB();
	// 衝突応答
	void OnCollition(const P_Bullet* playerBullet);

	#pragma endregion

	#pragma region 衝突判定 [ プレイヤーの弾  <<===>>  敵 ]

	// AABBを取得
	AABB2 GetAABB2();
	// 衝突応答
	void OnCollition2(const AllRound* allRound);

    #pragma endregion

	uint32_t respawnTimer = 120;
	bool E_Dead_ = false;
	bool IsE_Dead() const { return E_Dead_; }


private:

	// モデル
	KamataEngine::Model* model_ = nullptr;
	// カメラ
	KamataEngine::Camera* camera_;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

};
