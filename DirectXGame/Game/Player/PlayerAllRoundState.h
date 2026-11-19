#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerAllRoundState : public PlayerState
{
public:
	void Initialize(Player* player) override;

	void Update(Player* player) override;

private:
	int timer_ = 0;

	static constexpr int kDuration = 180;
};
