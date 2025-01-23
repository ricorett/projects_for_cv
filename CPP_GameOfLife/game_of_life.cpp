#include "game_of_life.hpp"


int rows = 0, cols = 0;

int main() {
  int generation = 0, cell_alive = 0, y = 0, x = 0;
  char main_menu;
  char **matrix, **new_matrix;
  
  main_menu = mainMenu(main_menu);
  main_menu = std::tolower(main_menu);

  if (main_menu == 'e') {
    matrix = readFile(matrix, rows, cols);
    outputMatrix(matrix, cell_alive, generation);
    cell_alive = countAlive(matrix, cell_alive);
    
    new_matrix = new char *[rows];
    for (int i = 0; i < rows; i++) {
      new_matrix[i] = new char[cols]();
    }
    
    cpyMatrix(matrix, new_matrix);
    
    std::system("clear");
    
      while (1) {
        killOrRevive(matrix, new_matrix, y, x);
        generation++;
        outputMatrix(new_matrix, cell_alive, generation);
        sleep(1);
        std::system("clear");
        if (!gameNoOver(cell_alive) || worldStagnated(matrix, new_matrix)) {
          break;
        }
        cpyMatrix(new_matrix, matrix);
      }
    
    if (!gameNoOver(cell_alive)) {
    
      std::cout << std::endl << "All cells are dead!\n\n";
      sleep(1);
    
    } else if (worldStagnated(matrix, new_matrix)) {
    
      std::cout << std::endl << "World stagnated!\n\n";
      sleep(1);
    }
                                        
    gameOverScreen();

    sleep(1);
    std::system("clear");
    
    deleteTwoDimArray(matrix);
    deleteTwoDimArray(new_matrix);
  
  } else if (main_menu == 'q') {
    
    gameOverScreen();
    sleep(3);
    std::system("clear");
  
  } else {
    
    std::cout << "WRONG INPUT TRY AGAIN.\n\n";
    sleep(2);
    std::system("clear");
  
  }

  return 0;
}
