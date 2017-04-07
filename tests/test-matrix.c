#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

MatrixAlgo *matrix_providers[] = {
    &NaiveMatrixProvider,
};

int main()
{
    MatrixAlgo *algo = matrix_providers[0];

    Matrix dst, m, n, fixed;
    float value[16] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       1, 2, 3, 4,
                       5, 6, 7, 8
                      };
    algo->assign(&m, 4, 4, value);
    algo->assign(&n, 4, 4, value);
    algo->mul(&dst, &m, &n);


    float value_fix[16] = {34,  44,  54,  64,
                           82, 108, 134, 160,
                           34,  44,  54,  64,
                           82, 108, 134, 160
                          };
    algo->assign(&fixed, 4, 4, value_fix);

    if (algo->equal(&dst, &fixed))
        return 0;
    return -1;
}
