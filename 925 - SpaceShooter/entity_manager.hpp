#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "enemy.hpp"
#include "projectile.hpp"

class EntityManager : public sf::Drawable
{

public:
	virtual void SpawnEntity(sf::Vector2f) = 0;
	void Update(const sf::RenderWindow&, float dt);
	std::vector<AutoEntity*>&  GetEntities();

protected:
	std::vector<AutoEntity*> entities_;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};





