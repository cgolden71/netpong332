#ifndef GAME_H
#define GAME_H

typedef struct {
    int ball_x;
    int ball_y;
    int ball_vel_x;
    int ball_vel_y;
    int player1_y;
    int player2_y;
    int score1;
    int score2;
} game_state_t;

void init_game_state(game_state_t *state);

void update_game_state(game_state_t *state);

int is_game_over(game_state_t *state);

#endif
