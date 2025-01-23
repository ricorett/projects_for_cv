#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <unistd.h>

#define CELL '*'
#define DEAD_CELL '-'

extern int cols, rows;

bool worldStagnated(char *matrix[], char *new_matrix[]);

int isAlive(char** matrix, int x, int y);
int mainMenu(char main_menu);
int countAlive(char** matrix, int cell_alive);
int gameNoOver(int cell_alive);
int countNeighbours(char* matrix[], int y, int x);

char** readFile(char* matrix[], int &rows, int &cols);

void deleteTwoDimArray(char*arr[]);
void killOrRevive(char* matrix[], char* new_matrix[], int y, int x);
void cpyMatrix(char *matrix[], char *new_matrix[]);
void gameOverScreen();
void outputMatrix(char*matrix[], int &cell_alive, int &generation);
