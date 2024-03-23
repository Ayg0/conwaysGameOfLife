#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "raylib.h"

#define SIZE 10
#define COLS 108
#define ROWS 72
#define SCREENWIDTH 1080
#define SCREENHEIGHT 720

extern float	speed;
extern bool		paused;
extern uint8_t	**board;
extern uint8_t	**tmpBoard;
extern double	timetoWait;
extern Color colors[];
typedef void (*ruleFunction)();
extern uint32_t selectedRule;
extern ruleFunction rules[];

void	updateBoard(void (*ruleFunction)(void));
char	*formatTitle();
void	handleKeyPress();
void	handleMouseClick(uint32_t size);
void	drawCell(uint32_t x, uint32_t y, uint32_t size, uint32_t length, Color color);

uint8_t getCellValue(int32_t x, int32_t y);
uint8_t	checkLivingNeighbors(int32_t x, int32_t y);

// rules
void	conwaysRulesFunction();
void	tahasRulesFunction();