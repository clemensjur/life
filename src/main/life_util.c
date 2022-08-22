//
// Created by clemens on 08.09.20.
//

#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "perlin_noise.h"
#include "life_util.h"

const uint MAP_HEIGHT = 1024;
const uint MAP_WIDTH = 1024;
// Define where the map should be rendered at the start of the program
unsigned int OFFSET_Y = MAP_HEIGHT / 2;
unsigned int OFFSET_X = MAP_WIDTH / 2;

const char FIELD = ' ';

void life_init() {
    setlocale(LC_ALL, "");

    initscr(); // Initiate the default screen
    start_color(); // Allow for colored output
    noecho(); // Don't print keyboard input
    cbreak(); // Unbuffered input
    keypad(stdscr, TRUE); // Allow for special keys like ENTER, BACKSPACE, etc.
    curs_set(0);

    // Initialize all used color combinations
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_YELLOW);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);

    // Seed RNG for map generation
    time_t t;
    srand(time(&t));
}

void life_run(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH]) {

    life_map_draw(map, OFFSET_X, OFFSET_Y);

    int SCREEN_COLS, SCREEN_LINES;
    getmaxyx(stdscr, SCREEN_LINES, SCREEN_COLS);

    // Set height and width of the cursor when selecting cells
    int cursorLines = 1, cursorCols = 1;
    // Set cursor start position
    int cursorX = 1, cursorY = 1;

    int running = 1;
    int MODE_SELECT = 0;

    while (running) {
        switch (getch()) {
            case 'a':
                OFFSET_X -= 1;
                break;
            case 'd':
                OFFSET_X += 1;
                break;
            case 'w':
                OFFSET_Y -= 1;
                break;
            case 's':
                OFFSET_Y += 1;
                break;
            case KEY_UP:
                if (MODE_SELECT == 1) {
                    cursorLines--;
                } else cursorY--;
                break;
            case KEY_DOWN:
                if (MODE_SELECT == 1) {
                    cursorLines++;
                } else cursorY++;
                break;
            case KEY_LEFT:
                if (MODE_SELECT == 1) {
                    cursorCols--;
                } else cursorX--;
                break;
            case KEY_RIGHT:
                if (MODE_SELECT == 1) {
                    cursorCols++;
                } else cursorX++;
                break;
            case 'l':
                MODE_SELECT = !MODE_SELECT;
                break;
            case 'r':
                life_map_generate(map, rand() % 1000);
                clear();
                life_map_draw(map, OFFSET_X, OFFSET_Y);
                break;
            case 'q':
                endwin();
                running = 0;
            default:
                continue;
        }
        if (cursorCols < 1) cursorCols = 1;
        if (cursorX < 0) cursorX = 0;
        else if (cursorX > SCREEN_COLS - 1) cursorX = SCREEN_COLS - 1;

        if (cursorLines < 1) cursorLines = 1;
        if (cursorY < 0) cursorY = 0;
        else if (cursorY > SCREEN_LINES - 1) cursorY = SCREEN_LINES - 1;

        clear();
        life_map_draw(map, OFFSET_X, OFFSET_Y);

        for (int i = 0; i < cursorLines; ++i) {
            for (int j = 0; j < cursorCols; ++j) {
                mvaddch(cursorY + i, cursorX + j, ' ');
                refresh();
            }
        }
    }
}



void life_map_generate(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH], int rand) {
    float perlin;

//    time_t t;
//    srand(time(&t));

//    float frequency = (rand() % 1000) / 100000;
//    int depth = (rand() % 12) + 10;
    for (uint32_t i = 0; i < MAP_HEIGHT; ++i) {
        for (uint32_t j = 0; j < MAP_WIDTH; ++j) {
            perlin = perlin2d((float) (j + rand), (float) (i + rand), 0.01f, 10);
            if (perlin > 0.0f && perlin < 0.45f) {
                map[i][j] = WATER;
            } else if (perlin > 0.45f && perlin < 0.55f) {
                map[i][j] = DIRT;
            } else {
                map[i][j] = GRASS;
            }
        }
    }
}

void life_map_draw(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH], unsigned int offsetX, unsigned int offsetY) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    for (uint32_t i = 0; i < rows; ++i) {
        for (uint32_t j = 0; j < cols; ++j) {
            if ((i + offsetY >= 0 && i + offsetY <= MAP_HEIGHT) && (j + offsetX >= 0 && j + offsetX <= MAP_WIDTH)) {
                switch (map[i + offsetY][j + offsetX]) {
                    case WATER:
                        attron(COLOR_PAIR(1));
                        break;
                    case DIRT:
                        attron(COLOR_PAIR(2));
                        break;
                    case GRASS:
                        attron(COLOR_PAIR(3));
                        break;
                }
                mvaddch(i, j, FIELD);
                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(2));
                attroff(COLOR_PAIR(3));
            }
        }
    }
    refresh();
}

void life_map_print(FIELD_TYPE map[MAP_HEIGHT][MAP_WIDTH]) {
    for (uint32_t i = 0; i < MAP_HEIGHT; ++i) {
        for (uint32_t j = 0; j < MAP_WIDTH; ++j) {
            switch (map[i][j]) {
                case WATER:
                    printf("[WATER]");
                    break;
                case DIRT:
                    printf("[DIRT]");
                    break;
                case GRASS:
                    printf("[GRASS]");
                    break;
            }
        }
    }
}

