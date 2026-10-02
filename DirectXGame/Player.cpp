#include "Player.h"

using namespace KamataEngine;
using namespace MathUtility;


#pragma region 行列計算

// 行列の積
Matrix4x4 Multiply2(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	result.m[0][0] = {(m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) + (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0])};
	result.m[0][1] = {(m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) + (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1])};
	result.m[0][2] = {(m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) + (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2])};
	result.m[0][3] = {(m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) + (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3])};

	result.m[1][0] = {(m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) + (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0])};
	result.m[1][1] = {(m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) + (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1])};
	result.m[1][2] = {(m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) + (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2])};
	result.m[1][3] = {(m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) + (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3])};

	result.m[2][0] = {(m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) + (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0])};
	result.m[2][1] = {(m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) + (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1])};
	result.m[2][2] = {(m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) + (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2])};
	result.m[2][3] = {(m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) + (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3])};

	result.m[3][0] = {(m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) + (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0])};
	result.m[3][1] = {(m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) + (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1])};
	result.m[3][2] = {(m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) + (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2])};
	result.m[3][3] = {(m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) + (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3])};

	return result;
}

Matrix4x4 Inverse2(const Matrix4x4& m)
{
	Matrix4x4 result = {};
	float determinant =
	    m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
	    m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] - m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
	    m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
	    m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
	    m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
	    m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	if (determinant == 0.0f)
	{
		return result;
	}

	float InDit = 1.0f / determinant;

	result.m[0][0] = InDit * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
	                          m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
	result.m[0][1] = InDit * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
	                          m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
	result.m[0][2] = InDit * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
	                          m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
	result.m[0][3] = InDit * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
	                          m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);
	result.m[1][0] = InDit * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
	                          m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
	result.m[1][1] = InDit * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
	                          m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
	result.m[1][2] = InDit * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
	                          m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
	result.m[1][3] = InDit * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
	                          m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);
	result.m[2][0] = InDit * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
	                          m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
	result.m[2][1] = InDit * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
	                          m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
	result.m[2][2] = InDit * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
	                          m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
	result.m[2][3] = InDit * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
	                          m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);
	result.m[3][0] = InDit * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
	                          m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
	result.m[3][1] = InDit * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
	                          m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
	result.m[3][2] = InDit * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
	                          m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
	result.m[3][3] = InDit * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
	                          m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);
	return result;
}

Matrix4x4 MakeRotateMatrix(const Vector3& rotation)
{
	float cosX = cosf(rotation.x);
	float sinX = sinf(rotation.x);

	float cosY = cosf(rotation.y);
	float sinY = sinf(rotation.y);

	float cosZ = cosf(rotation.z);
	float sinZ = sinf(rotation.z);

	// X回転
	Matrix4x4 rotX = {1, 0, 0, 0, 0, cosX, sinX, 0, 0, -sinX, cosX, 0, 0, 0, 0, 1};

	// Y回転
	Matrix4x4 rotY = {cosY, 0, -sinY, 0, 0, 1, 0, 0, sinY, 0, cosY, 0, 0, 0, 0, 1};

	// Z回転
	Matrix4x4 rotZ = {cosZ, sinZ, 0, 0, -sinZ, cosZ, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	// Z → X → Y の順で合成
	Matrix4x4 result = Multiply2(Multiply2(rotZ, rotX), rotY);

	return result;
}

#pragma endregion


void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position)
{
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	worldTransform_.translation_ = position;

	// カーソル
	modelCursor_ = Model::CreateFromOBJ("Cursor", true);
	// 3Dレティクルのワールド変換を初期化
	worldTransform3DReticle_.Initialize();
	worldTransform3DReticle_.translation_ = position;
	worldTransform3DReticle_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// シングルトンインスタンスを取得する
	input_ = KamataEngine::Input::GetInstance();
}



// 更新
void Player::Update() 
{





	#pragma region プレイヤーの移動

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A))
	{
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) 
	{
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_W)) 
	{
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_S))
	{
		move.y -= kCharacterSpeed;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	// 移動限界座標
	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 20.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	#pragma endregion

	Attack();
	
		
    


	#pragma region 弾

	for (P_Bullet* p_bullet : p_bullets_)
	{
		p_bullet->Update();
	}

	p_bullets_.remove_if
	([](P_Bullet* p_bullet) {
		if (p_bullet->IsDead_PB()) 
		{
			delete p_bullet;
			return true;
		}
		return false;
	});

	#pragma endregion

	#pragma region 範囲攻撃

	for (AllRound* allRound : allRounds_) 
	{
		allRound->Update();
	}

	allRounds_.remove_if
	([](AllRound* allRound){
		if (allRound->IsDead_AR()) 
		{
			delete allRound;
			return true;
		}
		return false;
	});

	#pragma endregion

	#pragma region カーソルをマウス座標に合わせる

	POINT mousePos;
	GetCursorPos(&mousePos);

	HWND hwnd = KamataEngine::WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePos);

	// 画面サイズ
	float screenWidth = 1280.0f;
	float screenHeight = 720.0f;

	// NDC変換（-1～1）
	float ndcX = (mousePos.x / screenWidth) * 2.0f - 1.0f;
	float ndcY = 1.0f - (mousePos.y / screenHeight) * 2.0f;

	// カメラ空間
	float tanFov = tanf(camera_->fovAngleY * 0.5f);

	Vector3 rayDirCamera;
	rayDirCamera.x = ndcX * camera_->aspectRatio * tanFov;
	rayDirCamera.y = ndcY * tanFov;
	rayDirCamera.z = 1.0f; // ←重要

	rayDirCamera = Normalize(rayDirCamera);

	// カメラ回転
	Matrix4x4 rotMat = MakeRotateMatrix(camera_->rotation_);

	// ワールド方向
	Vector3 rayDir = TransformNormal(rayDirCamera, rotMat);
	rayDir = Normalize(rayDir);

	// カメラ位置
	Vector3 camPos = camera_->translation_;

	// レティクル位置
	const float kDistance = 50.0f;
	worldTransform3DReticle_.translation_ = camPos + rayDir * kDistance;

	// 行列更新
	worldTransform3DReticle_.TransferMatrix();

	#pragma endregion




	// 行列更新
	worldTransform3DReticle_.matWorld_ = MakeAffineMatrix(worldTransform3DReticle_.scale_, worldTransform3DReticle_.rotation_, worldTransform3DReticle_.translation_);
	worldTransform3DReticle_.TransferMatrix();

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw()
{
	model_->Draw(worldTransform_, *camera_);
	modelCursor_->Draw(worldTransform3DReticle_, *camera_);
	for (P_Bullet* p_bullet : p_bullets_)
	{
		p_bullet->Draw(*camera_);
	}
	for (AllRound* allRound : allRounds_)
	{
		allRound->Draw(*camera_);
	}
}

Player::~Player() 
{
	// 弾の解放
	for (P_Bullet* p_bullet : p_bullets_) 
	{
		delete p_bullet;
	}
	for (AllRound* allRound : allRounds_)
	{
		delete allRound;
	}
	delete modelCursor_;
}


void Player::Attack() 
{
	if (input_->IsTriggerMouse(0))
	{

		const float kBulletSpeed = 1.0f;

		Vector3 velocity(kBulletSpeed, 0, 0);

		// velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		velocity = worldTransform3DReticle_.translation_ - worldTransform_.translation_;
		velocity = Normalize(velocity) * kBulletSpeed;

		// 弾生成
		P_Bullet* newBullet = new P_Bullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		p_bullets_.push_back(newBullet);
	}
}


void Player::Attack2()
{ 
	
	

	// 発射タイマーカウントダウン
	fireTimer_--;
	// 指定時間に達した
	if (fireTimer_ <= 0)
	{
		// 弾を発射
		AllRound* newAllRound = new AllRound();
		newAllRound->Initialize(model_, worldTransform_.translation_);

		allRounds_.push_back(newAllRound);
	


		// 発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}



	
}



KamataEngine::Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}