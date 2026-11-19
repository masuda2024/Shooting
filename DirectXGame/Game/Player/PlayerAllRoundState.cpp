#include "PlayerAllRoundState.h"
#include "PlayerNormalState.h"
void PlayerAllRoundState::Initialize(Player*)
{ 
	timer_ = 0; 
}

void PlayerAllRoundState::Update(Player* player)
{
	// 範囲攻撃
	player->Attack2();
	// タイマー
	timer_++;

	// 180フレーム経過したら通常状態へ
	if (timer_ >= kDuration)
	{
		player->ChangeState(std::make_unique<PlayerNormalState>());

		return;
	}
}
