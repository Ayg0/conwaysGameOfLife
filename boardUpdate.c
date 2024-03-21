#include "board.h"
#include <stdint.h>
#include <stdio.h>

extern uint8_t	**board;
extern uint8_t	**tmpBoard;
extern double	timetoWait;

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

void	updateBoard(){
	uint8_t livingNeighbors = 0;
	static double lastUpdate = 0;

	double now = GetTime();
	printf("%f, %f, %f\n", now, lastUpdate, timetoWait);
	if (now - lastUpdate < timetoWait)
		return ;

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
	lastUpdate = GetTime();
}