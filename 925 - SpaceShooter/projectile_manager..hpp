#include "entity_manager.hpp"
#include "projectile.hpp"

class ProjectileManager : public EntityManager
{

private:
	void SpawnEntity(sf::Vector2f position) override;

public:
	void Spawn(sf::Vector2f position);
	void Spawn(sf::Vector2f position, sf::Vector2f direction);

};
