/*   Copyright 2023 Gilbert Francois Duivesteijn
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef MATRIX_H
#define MATRIX_H 1

const char black = 30;
const char red = 31;
const char green = 32;
const char yellow = 33;
const char blue = 34;
const char magenta = 35;
const char cyan = 36;
const char white = 37;
const char brightred = 91;
const char brightgreen = 92;
const char brightyellow = 93;
const char brightblue = 94;
const char brightmagenta = 95;
const char brightcyan = 96;
const char brightwhite = 97;

/**
 * Setup the scene and allocate memory.
 */
void setup(void);

/**
 * Update the state of the scene.
 */
void update(void);

/**
 * Use propability to determine if a column should start to rain.
 * If the column is already in rain state, do nothing.
 */
void update_rain_state(void);

/**
 * Update the rain state of all columns.
 */
void update_rain_columns(void);

/**
 * Update the rain state of a column.
 * If the column is in rain state, update the rain state of the column.
 * If the column is not in rain state, do nothing.
 *
 * @param col The column to update.
 */
void update_rain_column(int col);

/**
 * Update the characters of a column in rain state.
 *
 * @param col The column to update.
 * @param start The start row of the rain.
 * @param length The length of the rain.
 * @param end The end row of the rain.
 */
void update_rain_column_chars(int col, int start, int length, int end);

/**
 * Update the colors of a column in rain state.
 *
 * @param col The column to update.
 * @param start The start row of the rain.
 * @param length The length of the rain.
 * @param end The end row of the rain.
 */
void update_rain_column_colors(int col, int start, int length, int end);

/**
 * Permutate a small number of characters at random locations in the whole screen.
 */
void update_rnd_char(void);

/**
 * Draw the scene.
 */
void draw(void);

/**
 * Free the allocated memory at the end of the program.
 */
void free_memory(void);

/**
 * Get a random integer between 0 and max.
 *
 * @param max The maximum value of the random integer.
 * @return A random integer between 0 and max.
 */
int rnd(int max);

/**
 * Get a printable random character.
 *
 * @return A printable random character.
 */
char get_char(void);

/**
 * Get the memory offset of a character in the screen buffer.
 *
 * @param row The row of the character.
 * @param col The column of the character.
 * @return The memory offset of the character.
 */
const unsigned long get_index(int row, int col);

/**
 * Try to determine the terminal size.
 */
void get_terminal_size(void);

/**
 * Restore terminal settings and message. Called by stdlib's exit function.
 */
void exit_message(void);

#endif
