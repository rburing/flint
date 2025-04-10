/*
    Copyright (C) 2010 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "nmod_vec.h"
#include "nmod_mat.h"

void
nmod_mat_set(nmod_mat_t B, const nmod_mat_t A)
{
    slong i;

    if (B == A || A->c == 0)
        return;

    for (i = 0; i < A->r; i++)
        _nmod_vec_set(nmod_mat_entry_ptr(B, i, 0), nmod_mat_entry_ptr(A, i, 0), A->c);
}
