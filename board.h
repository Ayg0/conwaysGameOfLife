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

void	updateBoard();
void	handleKeyPress();
void handleMouseClick(uint32_t size);
char	*formatTitle();
void	drawCell(uint32_t x, uint32_t y, uint32_t size, uint32_t length, Color color);