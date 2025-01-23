#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL) {
    return INVALID_MATRIX;
  }

  if (rows <= 0 || columns <= 0) {
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
    return INVALID_MATRIX;
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc(rows, sizeof(double *));
  if (result == NULL) {
    return INVALID_MATRIX;
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      s21_remove_matrix(result);
      return INVALID_MATRIX;
    }
  }

  return OK;
}
