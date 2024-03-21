#include "board.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

uint8_t	**board;
uint8_t	**tmpBoard;

float	speed = 2;
bool	paused = 1;
double	timetoWait = 2;

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
	static char buff[100];
	static char *states[] = {"PAUSED", "RUNNING"};

	sprintf(buff, "Conway's Game of Life --%s-- --SPEED X%.2f--", states[paused], speed);
	return buff;
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
			updateBoard();
		handleKeyPress();
        EndDrawing();
	}
    CloseWindow();
	freeBoards();
    return 0;
}