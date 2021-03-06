#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdbool.h>

/* predefined shortcut */
#define DECLARE_MATRIX(col, row) \
    typedef struct { float values[col][row]; } Mat ## col ## x ## row
DECLARE_MATRIX(3, 3);
DECLARE_MATRIX(4, 4);

typedef struct {
    int row, col;
    float *values;
} Matrix;

typedef struct {
    void (*assign) (Matrix *thiz, int row, int col, float *value);
    bool (*equal) (const Matrix *l, const Matrix *r);
    bool (*mul) (Matrix *dst, const Matrix *l, const Matrix *r);
    Matrix *(*create) (int row, int col);
} MatrixAlgo;

/* Available matrix providers */
extern MatrixAlgo NaiveMatrixProvider;

#endif /* MATRIX_H_ */
