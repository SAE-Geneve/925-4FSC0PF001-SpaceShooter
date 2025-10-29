#pragma once

#include "auto_entity.hpp"

class Projectile : public AutoEntity
{

public:
	void Move(float) override;
	void Load() override;
};

inline void Projectile::Move(float dt)
{
	rect_.setPosition(motor_.Move(dt));

	float angle = std::atan2(motor_.GetDirection().x, -motor_.GetDirection().y);
	rect_.setRotation(sf::radians(angle));

}

inline void Projectile::Load()
{
	AutoEntity::Load("data\\sprites\\laserBlue01.png", { 0, -1 }, 600);
}



