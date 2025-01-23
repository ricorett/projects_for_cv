#include "game_of_life.hpp"

int mainMenu(char main_menu) {
  std::cout << "   ***   Universe size and index of cell written in conf.  ***"
            << std::endl;
  std::cout
      << " \n ▄▄ •  ▄▄▄· • ▌ ▄ ·. ▄▄▄ .          ·▄▄▄    ▄▄▌  ▪  ·▄▄▄▄▄▄ .\n";
  std::cout
      << "▐█ ▀ ▪▐█ ▀█ ·██ ▐███▪▀▄.▀·    ▪     ▐▄▄·    ██•  ██ ▐▄▄·▀▄.▀·\n";
  std::cout
      << "▄█ ▀█▄▄█▀▀█ ▐█ ▌▐▌▐█·▐▀▀▪▄     ▄█▀▄ ██▪     ██▪  ▐█·██▪ ▐▀▀▪▄\n";
  std::cout
      << "▐█▄▪▐█▐█ ▪▐▌██ ██▌▐█▌▐█▄▄▌    ▐█▌.▐▌██▌.    ▐█▌▐▌▐█▌██▌.▐█▄▄▌\n";
  std::cout
      << "·▀▀▀▀  ▀  ▀ ▀▀  █▪▀▀▀ ▀▀▀      ▀█▄▀▪▀▀▀     .▀▀▀ ▀▀▀▀▀▀  ▀▀▀ \n\n";
  std::cout
      << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀\n";
  std::cout << "\t\tPress E to start\n\t\tPress Q to quit\n";
  std::cin >> main_menu;

  return main_menu;
}

void gameOverScreen() {
  std::cout << "    ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   "
               "█▓▓█████  ██▀███\n";
  std::cout << "   ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█  "
               " ▀ ▓██ ▒ ██▒\n";
  std::cout << "  ▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  "
               "█▒░▒███   ▓██ ░▄█ ▒\n";
  std::cout << "  ░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█ "
               " ▄ ▒██▀▀█▄  \n";
  std::cout << "  ░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  "
               "░▒████▒░██▓ ▒██▒\n";
  std::cout << "   ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ "
               "▒░ ░░ ▒▓ ░▒▓░\n";
  std::cout << "    ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ "
               "░  ░  ░▒ ░ ▒░\n";
  std::cout << "  ░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     "
               "░     ░░   ░ \n";
  std::cout << "        ░       ░  ░       ░      ░  ░       ░ ░        ░     "
               "░  ░   ░     \n";
  std::cout << "                                                       ░       "
               "            \n";
}

char **readFile(char *matrix[], int &rows, int &cols) {
  
  std::ifstream Config("game_config.txt");

  if (Config.is_open()) {
    
    Config >> rows >> cols;
    std::cout << rows << ' ' << cols << '\n';
    
    matrix = new char *[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new char[cols]();
    }

    int i = 0, j = 0;
    
    while (Config >> i >> j) {
      if (i <= rows || j <= cols) {
        matrix[i][j] = CELL;
      } else {
        break;
        std::cout << "OPEN CONFIG FILE ERROR.";
      }
    }
  }

  Config.close();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (matrix[i][j] != CELL) {
        matrix[i][j] = DEAD_CELL;
      }
    }
  }

  return matrix;
}

int isAlive(char **matrix, int x, int y) {

  if (matrix[x][y] == CELL) {
    return 1;
  }

  return 0;
}

int countAlive(char **matrix, int cell_alive) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (isAlive(matrix, i, j)) {
        cell_alive++;
      }
    }
  }
  
  return cell_alive;
}

void cpyMatrix(char *matrix[], char *new_matrix[]) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      new_matrix[i][j] = matrix[i][j];
    }
  }
}

void outputMatrix(char *matrix[], int &cell_alive, int &generation) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << matrix[i][j];
    }
    std::cout << std::endl;
  }
  
  cell_alive = 0;
  cell_alive = countAlive(matrix, cell_alive);
  
  std::cout << "Generation : " << generation << std::endl;
  std::cout << "Alive cells: " << cell_alive << std::endl;
}

int gameNoOver(int cell_alive) {
  if (cell_alive == 0) {
    return 0;
  }
  return 1;
}

bool worldStagnated(char *matrix[], char *new_matrix[]) {
  bool is_eq = true;
  
  for (int i = 0; i < rows && is_eq; ++i) {
    for (int j = 0; j < cols && is_eq; ++j) {
      if (matrix[i][j] != new_matrix[i][j]) {
        is_eq = false;
      }
    }
  }
  return is_eq;
}

int countNeighbours(char *matrix[], int y, int x) {
  int count = 0;

  for (int i = y - 1; i <= y + 1; i++) {
    for (int j = x - 1; j <= x + 1; j++) {
      if (matrix[(i + rows) % rows][(j + cols) % cols] == CELL) {
        ++count;
      }
    }
  }
  return count - (matrix[y][x] == CELL ? 1 : 0);
}

void killOrRevive(char *matrix[], char *new_matrix[], int y, int x) {
  int neighbours;
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      neighbours = countNeighbours(matrix, i, j);
      if (neighbours < 2) {
        new_matrix[i][j] = DEAD_CELL;
      } else if (neighbours > 3) {
        new_matrix[i][j] = DEAD_CELL;
      } else if (neighbours == 3) {
        new_matrix[i][j] = CELL;
      }
    }
  }
  x = 0;
  y = 0;
}

void deleteTwoDimArray(char *arr[]) {
  
  for (int i = 0; i < rows; i++) {
    delete[] arr[i];
  }
  
  delete[] arr;
}
