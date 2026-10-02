#include "Game.h"
#include <random>
#include <ctime>
#include <cstdlib>

using namespace KamataEngine;
using namespace MathUtility;



std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);



void Game::Initialize() 
{
	//デバッグカメラ生成
	debugCamera_ = new DebugCamera(1280, 720);


	#pragma region フェーズ・フェード
	// フェーズインから開始
	phase_ = Phase::kFadeIn;
	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
    #pragma endregion


	#pragma region 背景スクロール
	// ファイル名を指定してテクスチャを読み込む
	textureHandleStage_ = TextureManager::Load("Scenes/space.png");
	stage_ = new Stage();
	stage_->Initialize(textureHandleStage_);
	#pragma endregion


	// 制限時間
	textureHandleGraph_ = TextureManager::Load("white1x1.png");
	graphBar_ = new GraphBar();
	graphBar_->Initialize(textureHandleGraph_);



	//スキル
	textureHandleGraph_ = TextureManager::Load("white1x1.png");
	skillBar_ = new SkillBar();
	skillBar_->Initialize(textureHandleGraph_);




	#pragma region プレイヤー

	modelPlayer_ = Model::CreateFromOBJ("player");
	KamataEngine::Vector3 p_position = {-12.0f, -5.0f, 0.0f};
	player_ = new Player();
	player_->Initialize(modelPlayer_, &camera_, p_position);
	
	#pragma endregion
	
	
	

	#pragma region 敵

	modelEnemy_ = Model::CreateFromOBJ("Asteroid");
	
	
	
	for (int i = 0; i < enemyCount; i++)
	{
		Enemy* enemy = new Enemy();

		Vector3 e_pos = 
		{
			abs(distribution(randomEngine)) * 25.0f,
			abs(distribution(randomEngine)) * 20.0f, 
			0.0f
		};
		

		enemy->Initialize(modelEnemy_, &camera_, e_pos);

		enemies_.push_back(enemy);
	}
	
	
	

	#pragma endregion


	#pragma region スコア表示
	textureHandleNumber_ = TextureManager::Load("UI/number.png");//320 x 64
	drawNumber_ = new DrawNumber();
	drawNumber_->Initialize(textureHandleNumber_);
	#pragma endregion


	#pragma region UI

	// ESCのスプライト
	ESC_Handle_ = TextureManager::Load("UI/ESC.png");
	ESC_Sprite_ = KamataEngine::Sprite::Create(ESC_Handle_, {10, 100});

	ESC_Handle_2 = TextureManager::Load("UI/Pushed_ESC.png");
	ESC_Sprite_2 = KamataEngine::Sprite::Create(ESC_Handle_2, {10, 100});

	
	PoseUI_Handle_ = TextureManager::Load("UI/Pose_UI.png");
	PoseUI_Sprite_ = KamataEngine::Sprite::Create(PoseUI_Handle_, {448, 164});

	PoseUI_Handle_2 = TextureManager::Load("UI/Pushed_Pose_UI.png");
	PoseUI_Sprite_2 = KamataEngine::Sprite::Create(PoseUI_Handle_2, {448, 164});

	PoseUI2_Handle_ = TextureManager::Load("UI/Pose_UI_2.png");
	PoseUI2_Sprite_ = KamataEngine::Sprite::Create(PoseUI2_Handle_, {448, 364});

	PoseUI2_Handle_2 = TextureManager::Load("UI/Pushed_Pose_UI_2.png");
	PoseUI2_Sprite_2 = KamataEngine::Sprite::Create(PoseUI2_Handle_2, {448, 364});
	


	
    #pragma endregion

	

	#pragma region エフェクト


	// 乱数の初期化
	srand((unsigned)time(NULL));

	// 3Dモデルデータ生成
	modelEffect_ = Model::CreateFromOBJ("plane");

	// 最初のエフェクト生成
	//KamataEngine::Vector3 position = {0.0f, 0.0f, 0.0f};
	//KamataEngine::Vector3 position = e_position;
	//EffectBorn(position);


	#pragma endregion


	#pragma region テクスチャ



	textureHandle_ = TextureManager::Load("uvChecker.png");
	//textureHandle_ = TextureManager::Load("white1x1.png");
	

	#pragma endregion


	#pragma region 効果音

	//効果音ラボ/戦闘[2]/爆発1
	//explosion_ = Audio::GetInstance()->LoadWave("Sounds/sound/Explosion1.mp3");
	// 効果音ラボ/戦闘[2]/大爆発1
	explosion_ = Audio::GetInstance()->LoadWave("Sounds/sound/HugeExplosion2.mp3");
	// 効果音ラボ/戦闘[2]/大砲1
	cannon_ = Audio::GetInstance()->LoadWave("Sounds/sound/Cannon1.mp3");
	
	#pragma endregion

	worldTransform_.Initialize();
	camera_.Initialize();
}







void Game::Update()
{

	#pragma region デバッグカメラ
	debugCamera_->Update();

	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_0))
	{
		isDebugCameraActive_ = !isDebugCameraActive_;
	}



	#endif // DEBUG
	// ChangePhase();
	if (isDebugCameraActive_)
	{
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.TransferMatrix();
		camera_.UpdateMatrix();
	}
	#pragma endregion


	if (gameActive) 
	{


		stage_->Update();



		#pragma region プレイヤーの更新

		player_->Update();
		graphBar_->Update(static_cast<uint32_t>(time_));
		time_-=0.5f;
		if (time_ < 0)
		{
			//time_ = 1280u;
			finishedGAME2_ = true;
		}

			#pragma region Playerのスキル攻撃
			skillBar_->Update(static_cast<uint32_t>(skill_));
			if (skill_ >= MaxSkill_)
			{
				skill_ = MaxSkill_;
				c_skillUp = false;
				skillActive_ = true;
			}

			if (skillActive_)
			{
				player_->Attack2();
				skill_ -= 5.0f;
			}

			if (skill_ == 0)
			{
				skillActive_ = false;
				c_skillUp = true;
			}
			#pragma endregion

		#pragma endregion

		

		#pragma region 敵の更新
		
		for (Enemy* enemies : enemies_)
		{
			enemies->Update();
		}
		
		enemies_.remove_if
		([](Enemy* enemies) {
			if (enemies->IsE_Dead()) 
			{
				delete enemies;
				return true;
			}
			return false;
		});
		
		while (enemies_.size() < enemyCount)
		{
			Enemy* enemy = new Enemy();

			Vector3 pos = 
			{
				distribution(randomEngine) * 25.0f,
				distribution(randomEngine) * 20.0f,
				0.0f
			};

			enemy->Initialize(modelEnemy_, &camera_, pos);

			enemies_.push_back(enemy);
		}

        #pragma endregion




		#pragma region スコア

		
		drawNumber_->Update(gameScore_);

		#pragma endregion 



		#pragma region エフェクト
		

			
		// エフェクト更新
		// effect_->Update();
		for (Effect* effect : effects_)
		{
			effect->Update();
		}

		// デスフラグの立ったエフェクトを削除
		effects_.remove_if
		([](Effect* effect) {
			if (effect->IsFinished()) 
			{
				delete effect;
				return true;
			}
			return false;
		});


		#pragma endregion

		
	}

	switch (phase_)
	{
	case Phase::kPlay: 
	{
		CheckAllCollisions();

		#pragma region 仮設コード
		
		/**/
		// ゲームクリア(仮)
		if (Input::GetInstance()->TriggerKey(DIK_C))
		{
		    phase_ = Phase::kEnemyDeath;
		}
		// ゲームオーバー(仮)
		if (Input::GetInstance()->TriggerKey(DIK_O))
		{
		    phase_ = Phase::kDeath;
		}
		
		#pragma endregion




		

		//ESCAPEキーを押してポーズ画面へ移行
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE))
		{
			phase_ = Phase::kPose;
		}



		break;
	}

	case Phase::kPose: 
	{

		gameActive = false;
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) 
		{
			phase_ = Phase::kPlay;
			gameActive = true;
		}
		if (Input::GetInstance()->TriggerKey(DIK_T)) 
		{
			phase_ = Phase::kFadeOut3;
		}
		break;
	}

	case Phase::kDeath: 
	{
		// フェードアウト開始
		phase_ = Phase::kFadeOut;
		fade_->Start(Fade::Status::FadeOut, 1.0f);

		break;
	}

	case Phase::kEnemyDeath:
	{
		// フェードアウト開始
		phase_ = Phase::kFadeOut2;
		fade_->Start(Fade::Status::FadeOut, 1.0f);

		break;
	}
	
	case Phase::kFadeIn:
	{	
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			phase_ = Phase::kPlay;
		}
		break;
	}
	
	case Phase::kFadeOut:
	{
		// フェード
		fade_->Update();
		if (fade_->IsFinished())
		{
			finishedGAME_ = true;
		}
		break;
	}
	
	case Phase::kFadeOut2:
	{
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			finishedGAME2_ = true;
		}
		break;
	}
	
	case Phase::kFadeOut3:
	{
		// フェード
		fade_->Update();
		if (fade_->IsFinished())
		{
			finishedGAME3_ = true;
		}
		break;
	}
	}

}


uint32_t Game::GetScore() const { return gameScore_; }


void Game::Draw() 
{ 
	//ID3D12GraphicsCommandList* commandList = DirectXCommon::GetInstance()->GetCommandList();
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();



	#pragma region スプライト(背景)

	Sprite::PreDraw(dxCommon->GetCommandList());

	stage_->Draw();

	
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	#pragma endregion




	#pragma region モデル

	Model::PreDraw();
	
	
	// ここに3Dモデルインスタンスの描画処理を記述する
	player_->Draw();

	

	for (Enemy* enemies : enemies_)
	{
		enemies->Draw();
	}
	


	#pragma region エフェクト描画
	
	
	

	// エフェクト描画
	for (Effect* effect : effects_)
	{
		effect->Draw(camera_);
	}
	

	#pragma endregion

	
	Model::PostDraw();
	
	#pragma endregion
	
	

	#pragma region スプライト(UI)

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	graphBar_->Draw();
	drawNumber_->Draw();


	skillBar_->Draw();



	#pragma region UI
	if (phase_ == Phase::kPlay || phase_ == Phase::kFadeIn || phase_ == Phase::kPose || phase_ == Phase::kDeath || phase_ == Phase::kEnemyDeath) 
	{
		ESC_Sprite_->Draw();

		if (Input::GetInstance()->PushKey(DIK_ESCAPE)) 
		{
			ESC_Sprite_2->Draw();
		}
	}

	// ポーズ画面
	if (phase_ == Phase::kPose)
	{
		PoseUI_Sprite_->Draw();
		PoseUI2_Sprite_->Draw();

		if (Input::GetInstance()->PushKey(DIK_ESCAPE)) 
		{
			PoseUI_Sprite_2->Draw();
		}

		if (Input::GetInstance()->PushKey(DIK_T))
		{
			PoseUI2_Sprite_2->Draw();
		}
	}

#pragma endregion

	// スプライト描画後処理
	Sprite::PostDraw();

	#pragma endregion

}


void Game::CheckAllCollisions()
{ 
	const std::list<P_Bullet*>& playerBullets = player_->GetBullets();
	const std::list<AllRound*>& allRounds = player_->GetRound();

	#pragma region[ プレイヤーの弾  <<===>>  敵 ]

	AABB aabb1, aabb2;
	for (P_Bullet* p_bullet : playerBullets)
	{
		aabb1 = p_bullet->GetAABB();
		for (Enemy* enemies : enemies_)
		{
			aabb2 = enemies->GetAABB();
			if (IsCollition(aabb1, aabb2)) 
			{
				p_bullet->OnCollition(enemies);
				enemies->OnCollition(p_bullet);

				//敵を倒してスコアを加算
				gameScore_ += 100;
				if (c_skillUp)
				{
					skill_ += 100.0f;
				}
				
				Audio::GetInstance()->PlayWave(explosion_);
				Audio::GetInstance()->PlayWave(cannon_);
				
				
				Vector3 position = enemies->GetPosition();
				EffectBorn(position);
				// エフェクトを作ったらタイマーをセットして、しばらく作れないようにする
				effectTimer_ = kEffectInterval;
			}
		}
	}
	#pragma endregion

	#pragma region[ プレイヤーの範囲攻撃  <<===>>  敵 ]


	AABB2 aabb3, aabb4;
	for (AllRound* allRound : allRounds)
	{
		for (int i = 0; i < 16; i++)
		{
			aabb3 = allRound->GetAABB2(i);
			for (Enemy* enemies : enemies_)
			{
				aabb4 = enemies->GetAABB2();
				if (IsCollition2(aabb3, aabb4)) 
				{

					allRound->OnCollition2(enemies);
					enemies->OnCollition2(allRound);

					// 敵を倒してスコアを加算
					gameScore_ += 1000;

					Audio::GetInstance()->PlayWave(explosion_);
					Audio::GetInstance()->PlayWave(cannon_);
				


					Vector3 position = enemies->GetPosition();
					EffectBorn(position);
					// エフェクトを作ったらタイマーをセットして、しばらく作れないようにする
					effectTimer_ = kEffectInterval;
				}
			}
		}
	}
	

	#pragma endregion



}


// エフェクト発生
void Game::EffectBorn(Vector3 position) 
{
	Vector3 color = {abs(distribution(randomEngine)), abs(distribution(randomEngine)), abs(distribution(randomEngine))};
	for (int32_t i = 0; i < 15; i++) 
	{
		Effect* effect = new Effect();
		float rotate = distribution(randomEngine) * 3.14f;
		//float size = 1.0f + abs(distribution(randomEngine)) * 4;
		float size = 0.1f + abs(distribution(randomEngine)) * 0.5f;
		effect->Initialize(modelEffect_, rotate, size, position, color);
		effects_.push_back(effect);
	}
}




Game::~Game() 
{ 
    delete debugCamera_;

	
	#pragma region エフェクトの解放
	// エフェクト
	for (Effect* effect : effects_)
	{
		delete effect;
	}
	effects_.clear();
	delete modelEffect_;
	#pragma endregion


	

	
	#pragma region UI

	delete ESC_Sprite_;
	delete ESC_Sprite_2;

	
	delete PoseUI_Sprite_;
	delete PoseUI_Sprite_2;

	delete PoseUI2_Sprite_;
	delete PoseUI2_Sprite_2;

	
	#pragma endregion




	delete stage_;
	delete drawNumber_;


	#pragma region プレイヤーの解放


	delete player_;
	delete graphBar_;
	delete skillBar_;


	#pragma endregion

	#pragma region 敵の解放

	
	for (Enemy* enemies : enemies_)
	{
		delete enemies;
	}
	
	
    #pragma endregion
}