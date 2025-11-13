#include "state_manager.hpp"

int StateManager::score_ = 0;
int StateManager::remaining_lives_ = 5;
int StateManager::lives_max_ = 5;

void StateManager::KillEnemy()
{
	score_ += 10;
}

void StateManager::LostLife()
{
	remaining_lives_ -= 1;
}

int StateManager::GetScore()
{
	return score_;
}

int StateManager::GetRemaingLives()
{
	return remaining_lives_;
}

int StateManager::GetLivesMax()
{
	return lives_max_;
}
