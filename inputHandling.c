#include "board.h"

extern float	speed;
extern bool		paused;
extern uint8_t	**board;
extern uint8_t	**tmpBoard;
extern double	timetoWait;

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
		timetoWait = 1 / speed;
		SetWindowTitle(formatTitle());
	}
}

void handleMouseClick(){
	Vector2 ballPosition = GetMousePosition();
	int x = floor(ballPosition.x / 10);
	int y = floor(ballPosition.y / 10);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
			board[y][x] = !board[y][x];
	}
}