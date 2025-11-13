#include "ui.hpp"

#include "state_manager.hpp"

void UI::Load(sf::RenderWindow& window)
{

	life_icon_actual_.loadFromFile("data//sprites//bar_square_large_square.png");
	life_icon_max_.loadFromFile("data//sprites//bar_square_gloss_large_square.png");

	if (score_frame_texture_.loadFromFile("data//sprites//button_square_header_large_rectangle.png"))
	{
		score_frame_ = sf::Sprite(score_frame_texture_);
		score_frame_->setOrigin({ score_frame_texture_.getSize().x / 2.f, score_frame_texture_.getSize().y / 2.f});
		score_frame_->setPosition({ window.getSize().x / 2.f, 100});
		score_frame_->setScale({ 1.25f, 1.f });
	}


	if (font_.openFromFile("data//fonts//varino//Varino - Normal.ttf"))
	{
		score_label_ = sf::Text(font_);
		score_label_->setCharacterSize(40);
		score_label_->setFillColor(sf::Color::White);
		score_label_->setString("Score : ");
		score_label_->setPosition({ score_frame_->getPosition().x - score_label_->getLocalBounds().size.x, 50.f });

		score_ = sf::Text(font_);
		score_->setCharacterSize(40);
		score_->setFillColor(sf::Color::White);
		score_->setPosition({ score_frame_->getPosition().x, 50.f });
		score_->setString("0000");
	}

}

void UI::Update()
{
	SetScore(StateManager::GetScore());
	SetLife(StateManager::GetRemaingLives(), StateManager::GetLivesMax());
}


void UI::SetScore(int score)
{
	score_->setString(std::format("{:04d}", score));
}

void UI::SetLife(int actual_life, int max_life)
{
	actual_life_ = actual_life;
	max_life_ = max_life;
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	if (score_frame_.has_value()) target.draw(score_frame_.value());
	if (score_label_.has_value()) target.draw(score_label_.value());
	if (score_.has_value()) target.draw(score_.value());

	sf::Vector2u iconSize = life_icon_actual_.getSize();
	sf::Sprite sprite(life_icon_actual_);
	sprite.setOrigin({ static_cast<float>(life_icon_actual_.getSize().x), 0.0f });


	sf::Vector2f bottom_right_corner = score_frame_->getGlobalBounds().position + score_frame_->getGlobalBounds().size;

	for (int idx_life = 0; idx_life < max_life_; ++idx_life)
	{
		if (idx_life >= actual_life_)
		{
			sprite.setTexture(life_icon_max_);
		}

		sprite.setPosition({bottom_right_corner.x - 1.1f * iconSize.x * idx_life, bottom_right_corner.y - 1.1f * iconSize.y});
		target.draw(sprite);
	}
	
}



