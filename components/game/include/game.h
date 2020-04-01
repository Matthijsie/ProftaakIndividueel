#ifndef game_H
#define game_H

#include <stdbool.h>

/**
 * @brief Allocates and initializes game resources and starts the game
 *
 */ 
void game_start();

/**
 * @brief Makes the player character jump into the air! :)
 *        No other inputs can be giving whilst the player is jumping
 * 
 */ 
void game_jump();

/**
 * @brief Stops the game and releases all game resources, then sends the score to the menu
 * 
 */ 
void game_stop();


bool game_is_running;       ///< Set to TRUE if a game is currently running

#endif