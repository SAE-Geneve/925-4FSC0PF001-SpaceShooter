#include "ui.hpp"

void UI::Load(sf::RenderWindow& window)
{

	font_.openFromFile("data\\fonts\\varino\\Varino - Normal.ttf");

	score_label_ = sf::Text(font_);

	score_label_->setCharacterSize(18);
	score_label_->setFillColor(sf::Color::White);
	score_label_->setPosition({ window.getSize().x / 2.f, 50.f });
	score_label_->setString("Score :");



}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (score_label_.has_value())
	{
		target.draw(score_label_.value());
	}
	
}


