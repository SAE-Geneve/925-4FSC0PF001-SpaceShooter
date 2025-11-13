#include "enemy.hpp"
#include "entity_manager.hpp"

class EnemyManager : public EntityManager
{

	float elapsed_time_ = 0;
	float spawn_rate_ = 0.75f;

	void SpawnEntity(sf::Vector2f position) override;

public:
	void Update(const sf::RenderWindow&, float dt);

};

inline void EnemyManager::SpawnEntity(sf::Vector2f position) 
{
	// Ajouter dans le vecteur
	entities_.emplace_back(new Enemy());

	// mettre à la position de spawn
	entities_.back()->Load();
	entities_.back()->SetPosition(position);
}

inline void EnemyManager::Update(const sf::RenderWindow& window, float dt)
{
	EntityManager::Update(window, dt);

	elapsed_time_ += dt;

	if (elapsed_time_ >= spawn_rate_)
	{

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> pos_x(0.f, window.getSize().x); // distribution in range [1, 6]

		SpawnEntity({ static_cast<float>(pos_x(rng)), 0.f});
		elapsed_time_ = 0;
	}

}