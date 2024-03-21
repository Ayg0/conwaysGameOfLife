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
void	handleMouseClick();
char	*formatTitle();