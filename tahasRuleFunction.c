#include "board.h"

// become alive if neighbors == 2
// die if more then 4 neigbors
// move left if less then or equal 4 (2 excluded)

void	tahasRulesFunction(){
	uint8_t livingNeighbors = 0;
	for (uint32_t i = 0; i < ROWS; i++){
		for (uint32_t j = 0; j < COLS; j++){
			livingNeighbors = checkLivingNeighbors(j, i);
			if (livingNeighbors == 2 && !board[i][j])
				tmpBoard[i][j] = 1;
			else if (livingNeighbors > 4)
				tmpBoard[i][j] = 0;
			else if (livingNeighbors < 4 && board[i][j]){
				j != 0 && (tmpBoard[i][j - 1] = 1);
				tmpBoard[i][j] = 0;
			}
			else
				tmpBoard[i][j] = board[i][j];
		}
	}
}