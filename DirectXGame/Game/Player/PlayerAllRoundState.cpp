#include "PlayerAllRoundState.h"

void PlayerAllRoundState::Initialize(Player*) {}

void PlayerAllRoundState::Update(Player* player)
{
	// 範囲攻撃
	player->Attack2();
}
