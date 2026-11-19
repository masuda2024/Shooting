#include "PlayerNormalState.h"
#include "PlayerAllRoundState.h"
void PlayerNormalState::Initialize(Player*){}

void PlayerNormalState::Update(Player* player)
{
	// 範囲攻撃の発動要求があれば状態変更
	if (player->ConsumeAllRoundRequest()) 
	{
		player->ChangeState(std::make_unique<PlayerAllRoundState>());

		return;
	}

	// 通常時の移動
	player->Move();

	// 通常弾攻撃
	player->Attack();
}