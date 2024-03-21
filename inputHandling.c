#include "board.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

extern float	speed;
extern bool		paused;
extern uint8_t	**board;
extern uint8_t	**tmpBoard;
extern double	timetoWait;
extern Color colors[];


void handleKeyPress(){
	int key = GetCharPressed();
	if (key == 'P' || key == 'p'){
		paused = !paused;
		SetWindowTitle(formatTitle());
	}
	if (paused && key == 'n')
		updateBoard();
	if (key == '+' || key == '-'){
		key == '+' ? speed += 0.5 : key == '-' ? speed -= 0.5 : speed;
		speed = speed > 10 ? 10 : speed < 0.5 ? 0.5 : speed;
		printf("timeToWait = %f\n", timetoWait);
		timetoWait = 1 / speed;
		printf("timeToWait = %f\n", timetoWait);
		SetWindowTitle(formatTitle());
	}
}

void handleMouseClick(uint32_t size){
	Vector2 ballPosition = GetMousePosition();
	int x = floor(ballPosition.x / 10);
	int y = floor(ballPosition.y / 10);
	int status = -1;
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		status = 1;
	else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		status = 0;

    if ((status != -1) && x >= 0 && x < COLS && y >= 0 && y < ROWS){
		board[y][x] = status;
		drawCell(x, y, size, size - paused, colors[status]);
	}
}