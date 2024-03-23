#include "board.h"
#include <stdint.h>
#include <stdio.h>

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

void	updateBoard(void (*ruleFunction)(void)){
	static double lastUpdate = 0;

	double now = GetTime();
	if (now - lastUpdate < timetoWait)
		return ;
	ruleFunction();
	for (uint32_t i = 0; i < ROWS; i++){
		for (uint32_t j = 0; j < COLS; j++)
			board[i][j] = tmpBoard[i][j];
	}
	lastUpdate = GetTime();
}