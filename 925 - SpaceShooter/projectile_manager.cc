#include "projectile.hpp"
#include "projectile_manager..hpp"

void ProjectileManager::SpawnEntity(sf::Vector2f position)
{
	// Ajouter dans le vecteur
	entities_.emplace_back(new Projectile());

	// mettre à la position de spawn
	entities_.back()->Load();
	entities_.back()->SetPosition(position);
}

void ProjectileManager::Spawn(sf::Vector2f position)
{
	SpawnEntity(position);
}

void ProjectileManager::Spawn(sf::Vector2f position, sf::Vector2f direction)
{
	SpawnEntity(position);
	entities_.back()->SetDirection(direction);
}




