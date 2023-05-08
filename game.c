#include "game.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

#define PADDLE_HEIGHT 3
#define PADDLE_WIDTH 1

#define BALL_SIZE 1

void init_game_state(game_state_t *state) {
    state->ball_x = SCREEN_WIDTH / 2;
    state->ball_y = SCREEN_HEIGHT / 2;
    state->ball_vel_x = -1;
    state->ball_vel_y = 0;
    state->player1_y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    state->player2_y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    state->score1 = 0;
    state->score2 = 0;
}

void update_game_state(game_state_t *state) {
    // Update ball position
    state->ball_x += state->ball_vel_x;
    state->ball_y += state->ball_vel_y;

    // Bounce ball off top and bottom walls
    if (state->ball_y < 0 || state->ball_y >= SCREEN_HEIGHT) {
        state->ball_vel_y = -state->ball_vel_y;
    }

    // Check if ball hits left paddle
    if (state->ball_x == 1 && state->ball_y >= state->player1_y && state->ball_y < state->player1_y + PADDLE_HEIGHT) {
        state->ball_vel_x = -state->ball_vel_x;
    }

    // Check if ball hits right paddle
    if (state->ball_x == SCREEN_WIDTH - 2 && state->ball_y >= state->player2_y && state->ball_y < state->player2_y + PADDLE_HEIGHT) {
        state->ball_vel_x = -state->ball_vel_x;
    }

    // Check if ball goes out of bounds
    if (state->ball_x < 0) {
        state->score2++;
        init_game_state(state);
    } else if (state->ball_x >= SCREEN_WIDTH) {
        state->score1++;
        init_game_state(state);
    }
}

int is_game_over(game_state_t *state) {
    return state->score1 >= 10 || state->score2 >= 10;
}
