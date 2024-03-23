#include "board.h"

void	conwaysRulesFunction(){
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
}