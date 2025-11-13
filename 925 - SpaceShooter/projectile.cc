#include "projectile.hpp"

namespace Weapons
{

	void Projectile::Move(float dt)
	{
		motor_.SetSpeed(1.1f * motor_.GetSpeed());

		rect_.setPosition(motor_.Move(dt));

		float angle = std::atan2(motor_.GetDirection().x, -motor_.GetDirection().y);
		rect_.setRotation(sf::radians(angle));

	}

	void Projectile::Load()
	{
		AutoEntity::Load("data\\sprites\\laserBlue01.png", { 0, -1 }, 1500);
	}

}
