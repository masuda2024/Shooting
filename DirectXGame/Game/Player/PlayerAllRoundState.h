#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerAllRoundState : public PlayerState
{
public:
	void Initialize(Player* player) override;

	void Update(Player* player) override;
};
