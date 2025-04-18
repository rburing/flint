/*
    Copyright (C) 2010 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz.h"
#include "fmpz_mat.h"

void
fmpz_mat_randtest(fmpz_mat_t mat, flint_rand_t state, flint_bitcnt_t bits)
{
    slong r, c, i, j;

    r = mat->r;
    c = mat->c;

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            fmpz_randtest(fmpz_mat_entry(mat, i, j), state, bits);
}
