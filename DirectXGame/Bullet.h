#pragma once
#include "KamataEngine.h"

class Enemy;
class Bullet
{
public:
	virtual void Update() = 0;
	
	virtual void Draw(const KamataEngine::Camera& camera) = 0;
	
	// 消滅判定
	virtual bool IsDead() const = 0;
	

	
	
	virtual ~Bullet() = default;
};