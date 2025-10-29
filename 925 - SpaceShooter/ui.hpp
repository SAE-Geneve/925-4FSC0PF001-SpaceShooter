#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class UI : public sf::Drawable
{
private:
	sf::RectangleShape big_frame_;
	sf::RectangleShape score_frame_;

	std::optional<sf::Text> score_label_;
	std::optional<sf::Text> score_;

	sf::RectangleShape life_icon_;

	sf::Font font_;

	

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Load(sf::RenderWindow&);

};

