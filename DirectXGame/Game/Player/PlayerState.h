#pragma once
class Player;

class PlayerState
{
public:
	virtual ~PlayerState() = default;

	virtual void Initialize(Player*) {}

	virtual void Update(Player* player) = 0;

	virtual void Draw(Player*) {}
};