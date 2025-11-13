#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include "entity_manager.hpp"
#include "auto_entity.hpp"
#include "motor.h"
#include "projectile_manager..hpp"


class StarshipPlayer : public sf::Drawable
{
	// Ship
	sf::Texture ship_texture_;
	sf::RectangleShape ship_rect_;

	// Shield
	sf::Texture shield_texture_;
	sf::RectangleShape shield_rect_;
	bool shield_on_ = true;
	int shield_texture_idx_ = 0;
	float shield_counter_ = 0.f;
	float shield_time_ = 0.f;

	// Motor
	Motor motor_;

	// Projectiles
	Weapons::ProjectileManager projectile_manager_;
	float shoot_counter_ = 0.f;
	float shoot_rate_ = 0.25f;

	static void SetObjectTexture(sf::RectangleShape&, sf::Texture&);

public:
	void Load(sf::Vector2f);
	void Update(const sf::RenderWindow&, float);
	bool CheckCollisions(const std::vector<AutoEntity*>& others) const;
	void CheckProjectileCollisions(const std::vector<AutoEntity*>& others);

	void HandleEvent();

	void SetPosition(sf::Vector2f);
	void SetShield(float time);

protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

};

