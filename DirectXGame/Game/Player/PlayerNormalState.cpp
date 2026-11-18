#include "PlayerNormalState.h"

void PlayerNormalState::Initialize(Player*)
{

}

void PlayerNormalState::Update(Player* player)
{
	// 通常時の移動
	player->Move();

	// 通常弾攻撃
	player->Attack();
}