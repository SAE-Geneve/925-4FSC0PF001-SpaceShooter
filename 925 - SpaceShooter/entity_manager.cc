#include "entity_manager.hpp"

#include <algorithm>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void EntityManager::Update(const sf::RenderWindow& window, float dt)
{

	erase_if(entities_, [&window](AutoEntity* p)
	{
		return p->GetPosition().y < 0 || p->GetPosition().y > window.getSize().y || p->StillAlive == false;
	}
	);

	for (auto& entity : entities_)
	{
		entity->Move(dt);
	}

}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& projectile : entities_)
	{
		target.draw(*projectile);
	}

}

std::vector<AutoEntity*>& EntityManager::GetEntities()
{
	return entities_;
}

