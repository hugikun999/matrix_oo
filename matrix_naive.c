#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#define ROW(x) \
	x->row

#define COL(x) \
	x->col

static void assign(Matrix *thiz, int row, int col, float *value)
{
    thiz->row = row;
    thiz->col = col;

    thiz->values = (float *)malloc(row * col * sizeof(float));
    for (int i = 0; i < col; i++)
        for (int j = 0; j < row; j++)
            *(thiz->values + i * row + j) = *(value + i * row + j);
}

static const float epsilon = 1 / 10000.0;

static bool equal(const Matrix *l, const Matrix *r)
{
    if(ROW(l) != ROW(r) || COL(l) != COL(r))
        return false;

    for (int i = 0; i < ROW(l); i++)
        for (int j = 0; j < COL(l); j++)
            if (*(l->values + i * ROW(l) + j) + epsilon < *(r->values + i * ROW(r) + j) ||
                    *(r->values + i * ROW(r) + j) + epsilon < *(l->values + i * ROW(r) + j))
                return false;
    return true;
}

bool mul(Matrix *dst, const Matrix *l, const Matrix *r)
{
    if(ROW(l) != COL(r))
        return false;

    dst->values = (float *) malloc(COL(l) * ROW(r) * sizeof(float));
    memset(dst->values, sizeof(float), sizeof(float) * COL(l) * ROW(r));

    for (int i = 0; i < COL(l); i++)
        for (int j = 0; j < ROW(r); j++)
            for (int k = 0; k < ROW(l); k++)
                *(dst->values + i * COL(l) + j) += *(l->values + i * COL(l) + k) *
                                                   *(r->values + k * COL(l) + j);
    dst->row = COL(l);
    dst->col = ROW(r);

    return true;
}

MatrixAlgo NaiveMatrixProvider = {
    .assign = assign,
    .equal = equal,
    .mul = mul,
};
