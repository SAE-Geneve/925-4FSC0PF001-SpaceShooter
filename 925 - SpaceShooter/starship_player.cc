#include "starship_player.hpp"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <numbers>

#include "state_manager.hpp"

using namespace sf;

constexpr float angleBase = 18.f;
constexpr float angle1 = (90.f - angleBase) * 2.f * std::numbers::pi / 360.f;
constexpr float angle2 = (90.f + angleBase) * 2.f * std::numbers::pi / 360.f;

const sf::Vector2f rightShootDir = sf::Vector2f(std::cos(angle1), -std::sin(angle1));
const sf::Vector2f leftShootDir = sf::Vector2f(std::cos(angle2), -std::sin(angle2));


void StarshipPlayer::SetObjectTexture(sf::RectangleShape& shape, sf::Texture& texture)
{
	shape.setTexture(&texture);
	shape.setTextureRect(sf::IntRect({ 0,0 }, { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) }));
	shape.setSize({ static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y) });
	shape.setOrigin({ static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f });

}

void StarshipPlayer::Load(sf::Vector2f spawnPosition)
{
	if (ship_texture_.loadFromFile("data\\sprites\\playerShip3_red.png"))
	{
		SetObjectTexture(ship_rect_, ship_texture_);
	}

	if (shield_texture_.loadFromFile("data\\sprites\\shield3.png"))
	{
		SetObjectTexture(shield_rect_, shield_texture_);
	}

	motor_.SetPosition(spawnPosition);
	motor_.SetDirection({ 0, 1 });
	motor_.SetSpeed(600);

}

void StarshipPlayer::Update(const sf::RenderWindow& window, const float dt)
{
	sf::Vector2f pos = motor_.Move(dt);
	ship_rect_.setPosition(pos);
	shield_rect_.setPosition(pos);

	projectile_manager_.Update(window, dt);

	shoot_counter_ += dt;
	shield_counter_ += dt;

	shield_on_ = shield_counter_ < shield_time_;
	// Find the right texture
	if (shield_on_)
	{
		float alphaRatio = std::fmod(shield_counter_ / (shield_time_ / 5), shield_time_ / 5);
		shield_rect_.setFillColor(sf::Color(255, 75, 50, 255 * alphaRatio));

		std::cout << "shield texture : " << shield_texture_idx_ << std::endl;
	}

}

bool StarshipPlayer::CheckCollisions(const std::vector<AutoEntity*>& others) const
{

	if (shield_on_) return false;

	for (auto& other : others) {

		if (other->StillAlive == false)
		{
			continue;
		}

		if (ship_rect_.getGlobalBounds().findIntersection(other->GetBounds()))
		{
			other->StillAlive = false;
			return true;
		}
	}

	return false;

}

void StarshipPlayer::CheckProjectileCollisions(const std::vector<AutoEntity*>& others)
{

	auto bullets = projectile_manager_.GetEntities();

	for (auto& bullet : bullets)
	{
		if (!bullet->StillAlive)
		{
			continue;
		}

		for (auto& other : others)
		{

			if (!other->StillAlive)
			{
				continue;
			}

			// KABOUM, on a shooté un truc
			if (bullet->GetBounds().findIntersection(other->GetBounds()))
			{
				other->StillAlive = false;
				bullet->StillAlive = false;

				StateManager::KillEnemy();

			}
		}
	}


}

void StarshipPlayer::HandleEvent()
{

	sf::Vector2f direction = { 0,0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
	{
		direction.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
	{
		direction.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		direction.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
		direction.x = 1;
	}


	if (shoot_counter_ > shoot_rate_)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
			{
				projectile_manager_.Spawn(ship_rect_.getPosition(), rightShootDir);
				projectile_manager_.Spawn(ship_rect_.getPosition(), leftShootDir);
				projectile_manager_.Spawn(ship_rect_.getPosition());
			}
			else
			{
				projectile_manager_.Spawn(ship_rect_.getPosition());
			}
			shoot_counter_ = 0;
		}
	}

	motor_.SetDirection(direction);
}

void StarshipPlayer::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}

void StarshipPlayer::SetShield(float time)
{
	shield_counter_ = 0.f;
	shield_time_ = time;
}


void StarshipPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sf::Sprite sprite(texture);
	target.draw(projectile_manager_);
	if (shield_on_)
	{
		target.draw(shield_rect_);
	}
	target.draw(ship_rect_);


}



