#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "game.h"
#include "sppbtp.h"

#define PORT 8888

int main(int argc, char *argv[]) {
    int sock, valread;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    game_state_t game_state;
    int player_id = -1;
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }

    // Initialize game state
    init_game_state(&game_state);

    // Main game loop
    while (!is_game_over(&game_state)) {
        // Receive game state from server
        if (player_id == -1) {
            // First message from server is player ID
            valread = read(sock, buffer, 1024);
            player_id = atoi(buffer);
            printf("You are player %d\n", player_id);
        } else {
            // Subsequent messages contain game state
            valread = read(sock, buffer, 1024);
            unpack_game_state(buffer, &game_state);
        }

        // Update game state
        update_game_state(&game_state);

        // Send game state to server
        pack_game_state(&game_state, buffer);
        send(sock, buffer, strlen(buffer), 0);
    }

    // Game over
    close(sock);
    printf("Game over\n");
    return 0;
}
