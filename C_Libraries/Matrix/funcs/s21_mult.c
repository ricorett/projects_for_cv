#include "../s21_matrix.h"
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result) {
    return INVALID_MATRIX;
  }

  if ((A->rows == 0 && A->columns == 0) || (B->rows == 0 && B->columns == 0)) {
    return INVALID_MATRIX;
  }
  if (A->columns != B->rows) {
    return CALC_ERROR;
  }

  s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A || !result) {
    return INVALID_MATRIX;
  }

  if (A->rows == 0 && A->columns == 0) {
    return INVALID_MATRIX;
  }

  s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = (long double)A->matrix[i][j] * (long double)number;
    }
  }

  return OK;
}
