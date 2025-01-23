#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL) {
    return INVALID_MATRIX;
  }
  if (A->rows != A->columns) {
    return CALC_ERROR;
  }

  if (A->rows <= 0 && A->columns <= 0) {
    return INVALID_MATRIX;
  }

  matrix_t transpose, calc_comlements;
  double a_determinant = 0.0;

  s21_determinant(A, &a_determinant);

  if (fabs(a_determinant) < ACCURACY) {
    return CALC_ERROR;
  }

  s21_create_matrix(A->rows, A->columns, result);
  s21_calc_complements(A, &calc_comlements);
  s21_transpose(&calc_comlements, &transpose);
  s21_mult_number(&transpose, 1 / a_determinant, result);
  s21_remove_matrix(&transpose);
  s21_remove_matrix(&calc_comlements);
  return OK;
}
