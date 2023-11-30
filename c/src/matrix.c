//   Copyright 2023 Gilbert Francois Duivesteijn
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "matrix.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

int is_running = 1;
int width = 80;
int height = 24;
int n_permutations = 12;
int p_rain = 8;
int n_darktrail = 3;
int sleep_ms = 30;

int *drop_col;
int *drop_speed;
int *drop_speed_counter;
int *drop_start;
int *drop_length;
char *nametable_buffer;
char *colortable_buffer;

void setup(void) {

    get_terminal_size();
    // Change probability of rain and darktrail based on terminal size.
    n_permutations = height / 2;
    p_rain = width / 16;
    n_darktrail = height / 8;

    drop_col = (int *)malloc(width * sizeof(int));
    drop_speed = (int *)malloc(width * sizeof(int));
    drop_speed_counter = (int *)malloc(width * sizeof(int));
    drop_start = (int *)malloc(width * sizeof(int));
    drop_length = (int *)malloc(width * sizeof(int));
    nametable_buffer = (char *)malloc(width * height * sizeof(char));
    colortable_buffer = (char *)malloc(width * height * sizeof(char));

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int k = col + row * width;
            nametable_buffer[k] = 0x20;
        }
    }
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int k = col + row * width;
            colortable_buffer[k] = black;
        }
    }
    for (int i = 0; i < width; i++) {
        drop_col[i] = 0;
        drop_speed[i] = 0;
        drop_speed_counter[i] = 0;
        drop_start[i] = 0;
        drop_length[i] = 0;
    }
}

void update(void) {
    update_rain_state();
    update_rain_columns();
    update_rnd_char();
}

void update_rain_state(void) {
    int col = rnd(p_rain * width);
    if (col < width) {
        int is_raining = drop_col[col];
        if (is_raining == 0) {
            drop_col[col] = 1;
            drop_speed[col] = rnd(7) + 1;
            drop_speed_counter[col] = 0;
            drop_start[col] = 0;
            drop_length[col] = height / 2 + rnd(height / 2);
        }
    }
}

void update_rain_columns(void) {
    for (int i = 0; i < width; i++) {
        if (drop_col[i] == 1) {
            if (drop_speed_counter[i] < drop_speed[i]) {
                drop_speed_counter[i]++;
            } else {
                drop_speed_counter[i] = 0;
                update_rain_column(i);
            }
        }
    }
}

void update_rain_column(int col) {
    int start = drop_start[col];
    int length = drop_length[col];
    int end = start - length;
    if (end > height) {
        drop_col[col] = 0;
        drop_speed[col] = 0;
        drop_speed_counter[col] = 0;
        drop_start[col] = 0;
        return;
    }
    update_rain_column_chars(col, start, length, end);
    update_rain_column_colors(col, start, length, end);
    drop_start[col]++;
}

void update_rain_column_chars(int col, int start, int length, int end) {
    if (start < height) {
        const unsigned long k = get_index(start, col);
        char c = get_char();
        nametable_buffer[k] = c;
    }
    if (end >= 1) {
        const unsigned long k = get_index((end - 1), col);
        nametable_buffer[k] = 0x20;
    }
}

void update_rain_column_colors(int col, int start, int length, int end) {
    if (start < height) {
        const unsigned long k = get_index(start, col);
        colortable_buffer[k] = white;
    }
    if (start - 1 >= 0 && start - 1 < height) {
        const unsigned long k = get_index(start - 1, col);
        colortable_buffer[k] = cyan;
    }
    if (start - 2 >= 0 && start - 2 < height) {
        const unsigned long k = get_index(start - 2, col);
        colortable_buffer[k] = brightgreen;
    }
    for (int t = 0; t < n_darktrail; t++) {
        if (end + t >= 0 && end + t < height) {
            const unsigned long k = get_index(end + t, col);
            colortable_buffer[k] = green;
        }
    }
}

void update_rnd_char(void) {
    int k = width * height;
    for (int i = 0; i < n_permutations; i++) {
        int j = rnd(k);
        if (nametable_buffer[j] != 0x20) {
            char c = get_char();
            nametable_buffer[j] = c;
        }
    }
}

void draw(void) {
    printf("\x1b[H");
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            printf("\033[%d;%dm%c", colortable_buffer[row * width + col],
                   black + 10, nametable_buffer[row * width + col]);
        }
        if (row < height - 1) {
            printf("\033[0m\n");
        }
        // Hide cursor.
        printf("\033[?25l");
    }
}

void free_memory(void) {
    free(nametable_buffer);
    free(drop_col);
    free(drop_speed);
    free(drop_speed_counter);
    free(drop_start);
    free(drop_length);
}

int rnd(int max) { return (int)(0.5f + (float)max * rand() / (float)RAND_MAX); }

char get_char(void) {
    char c = (char)rnd(94);
    c = c + 32;
    return c;
}

const unsigned long get_index(int row, int col) {
    if (row < 0 || row >= height) {
        printf("Out of range error. row: %d\n", row);
        exit(EXIT_FAILURE);
    }
    if (col < 0 || col >= width) {
        printf("Out of range error. col: %d\n", col);
        exit(EXIT_FAILURE);
    }
    const unsigned long k = row * width + col;
    if (k >= width * height) {
        printf("Out of range error. row: %d, col: %d, k: %lu\n", row, col, k);
        exit(EXIT_FAILURE);
    }
    return k;
}

void get_terminal_size(void) {
    int term_rows = 0;
    int term_cols = 0;
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    term_cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    term_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#elif defined(TIOCGSIZE)
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    term_cols = ts.ts_cols;
    term_rows = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    term_cols = ts.ws_col;
    term_rows = ts.ws_row;
#endif
    if (term_rows != 0 && term_cols != 0) {
        height = term_rows;
        width = term_cols;
    }
}

void signal_handler(int signal) { is_running = 0; }

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    setup();
    while (is_running) {
        update();
        draw();
#if defined(_WIN32)
        Sleep(sleep_ms);
#else
        usleep(sleep_ms * 1000);
#endif
    }
    // User pressed Ctrl-C, end the event loop.
    free_memory();
    // Reset colors and cursor.
    printf("\033[0m\033[?25h\n");
    printf("\nFollow the white rabbit...\n");
    exit(EXIT_SUCCESS);
}
