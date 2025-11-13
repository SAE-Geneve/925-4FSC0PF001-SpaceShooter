#pragma once

#include "auto_entity.hpp"

namespace Weapons
{

	class Projectile : public AutoEntity
	{

	public:
		void Move(float) override;
		void Load() override;
	};

}


