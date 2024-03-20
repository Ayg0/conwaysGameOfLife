#include "raylib.h"
#include "board.h"
#include <math.h>
#include <stdio.h>

bool paused = 1;
float speed = 1;
uint8_t **board;
uint8_t **tmpBoard;

void	drawBoard(uint32_t cols, uint32_t rows, uint32_t size){
	uint32_t width, height;

	width = height = size - paused;
	for (uint32_t i = 0; i < rows; i++){
		for (uint32_t j = 0; j < cols; j++){
			if (board[i][j])
				DrawRectangle(j * size, i * size, width, height, BLACK);
			else
				DrawRectangle(j * size, i * size, width, height, WHITE);
		}
	}
}

uint8_t getCellValue(int32_t x, int32_t y){
	if (x == -1 || x == COLS || y == -1 || y == ROWS)
		return 0;
	return (board[y][x]);
}

uint8_t	checkLivingNeighbors(int32_t x, int32_t y){
	uint8_t livingNeighbors = 0;

	livingNeighbors += getCellValue(x - 1, y);
	livingNeighbors += getCellValue(x + 1, y);

	livingNeighbors += getCellValue(x, y + 1);
	livingNeighbors += getCellValue(x - 1, y + 1);
	livingNeighbors += getCellValue(x + 1, y + 1);

	livingNeighbors += getCellValue(x, y - 1);
	livingNeighbors += getCellValue(x - 1, y - 1);
	livingNeighbors += getCellValue(x + 1, y - 1);

	return livingNeighbors;
}

void	changeBoard(){
	uint8_t livingNeighbors = 0;

	for (uint32_t i = 0; i < ROWS; i++){
		for (uint32_t j = 0; j < COLS; j++){
			livingNeighbors = checkLivingNeighbors(j, i);
			if (livingNeighbors < 2 || livingNeighbors > 3)
				tmpBoard[i][j] = 0;
			else if (livingNeighbors == 3)
				tmpBoard[i][j] = 1;
			else
				tmpBoard[i][j] = board[i][j];

		}
	}
	for (uint32_t i = 0; i < ROWS; i++){
		for (uint32_t j = 0; j < COLS; j++)
			board[i][j] = tmpBoard[i][j];
	}
}

void boardsInit(){
	board = malloc(sizeof(uint8_t *) * ROWS);
	for (uint32_t i = 0; i < ROWS; i++)
		board[i] = malloc(COLS);
	tmpBoard = malloc(sizeof(uint8_t *) * ROWS);
	for (uint32_t i = 0; i < ROWS; i++)
		tmpBoard[i] = malloc(COLS);

	for (uint32_t i = 0; i < ROWS; i++){
		for (uint32_t j = 0; j < COLS; j++){
			board[i][j] = 0;
		}
	}
}

void freeBoards(){
	for (uint32_t i = 0; i < ROWS; i++)
		free(board[i]);
	free(board);
	for (uint32_t i = 0; i < ROWS; i++)
		free(tmpBoard[i]);
	free(tmpBoard);
}

char *formatTitle(){
	static char buff[100] = {};
	static char *states[] = {"PAUSED", "RUNNING"};

	sprintf(buff, "Conway's Game of Life --%s-- --SPEED X%.2f--", states[paused], speed);
	return buff;
}

void handleKeyPress(){
	int key = GetCharPressed();
	if (key == 'P' || key == 'p'){
		paused = !paused;
		SetWindowTitle(formatTitle());
	}
	if (paused && key == 'n')
		changeBoard();
	if (key == '+' || key == '-'){
		key == '+' ? speed += 0.2 : key == '-' ? speed -= 0.2 : speed;
		speed = speed > 2 ? 2 : speed < 0.2 ? 0.2 : speed;
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

int main(void)
{
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;
    InitWindow(screenWidth, screenHeight, formatTitle());
	SetTargetFPS(60);
	boardsInit();
    while (!WindowShouldClose())
    {
        BeginDrawing();
		ClearBackground(BLACK);
		drawBoard(COLS, ROWS, 10);
		if (paused)
			handleMouseClick();
		else
			changeBoard();
		handleKeyPress();
		usleep(floor(100000 / speed));
        EndDrawing();
	}
    CloseWindow();
	freeBoards();
    return 0;
}