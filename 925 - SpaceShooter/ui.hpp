#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class UI : public sf::Drawable
{
private:
	sf::Texture score_frame_texture_;
	sf::Font font_;

	sf::RectangleShape big_frame_;

	std::optional<sf::Sprite> score_frame_;
	std::optional<sf::Text> score_label_;
	std::optional<sf::Text> score_;

	sf::Texture life_icon_max_;
	sf::Texture life_icon_actual_;

	int actual_life_ = 0;
	int max_life_ = 0;

	void SetScore(int);
	void SetLife(int, int);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Load(sf::RenderWindow&);
	void Update();


};

