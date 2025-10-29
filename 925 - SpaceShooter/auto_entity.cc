#include "auto_entity.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

void AutoEntity::Load(std::string_view pathFile, sf::Vector2f direction, float speed)
{
	texture.loadFromFile(pathFile);

	//motor_.SetPosition({ 400, 600 });
	motor_.SetDirection(direction);
	motor_.SetSpeed(speed);

	rect_.setTexture(&texture);
	rect_.setSize({ static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y) });
	rect_.setOrigin({ static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f });

}

void AutoEntity::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}

sf::Vector2f AutoEntity::GetPosition()
{
	return rect_.getPosition();
}

void AutoEntity::SetDirection(sf::Vector2f direction)
{
	motor_.SetDirection(direction);
}


void AutoEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (StillAlive) {
		target.draw(rect_, states);
	}
}

sf::FloatRect AutoEntity::GetBounds()
{
	return rect_.getGlobalBounds();
}




