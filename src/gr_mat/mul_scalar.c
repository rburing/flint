/*
    Copyright (C) 2022 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "gr_vec.h"
#include "gr_mat.h"

int
gr_mat_mul_scalar(gr_mat_t res, const gr_mat_t mat, gr_srcptr x, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_vec_mul_scalar(GR_MAT_ENTRY(res, i, 0, sz), GR_MAT_ENTRY(mat, i, 0, sz), c, x, ctx);

    return status;
}

int
gr_mat_scalar_mul(gr_mat_t res, gr_srcptr x, const gr_mat_t mat, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_scalar_mul_vec(GR_MAT_ENTRY(res, i, 0, sz), x, GR_MAT_ENTRY(mat, i, 0, sz), c, ctx);

    return status;
}

int
gr_mat_mul_scalar_other(gr_mat_t res, const gr_mat_t mat, gr_srcptr x, gr_ctx_t x_ctx, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_vec_mul_scalar_other(GR_MAT_ENTRY(res, i, 0, sz), GR_MAT_ENTRY(mat, i, 0, sz), c, x, x_ctx, ctx);

    return status;
}

int
gr_mat_scalar_other_mul(gr_mat_t res, gr_srcptr x, gr_ctx_t x_ctx, const gr_mat_t mat, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_scalar_other_mul_vec(GR_MAT_ENTRY(res, i, 0, sz), x, x_ctx, GR_MAT_ENTRY(mat, i, 0, sz), c, ctx);

    return status;
}

int
gr_mat_mul_ui(gr_mat_t res, const gr_mat_t mat, ulong x, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_vec_mul_scalar_ui(GR_MAT_ENTRY(res, i, 0, sz), GR_MAT_ENTRY(mat, i, 0, sz), c, x, ctx);

    return status;
}

int
gr_mat_mul_si(gr_mat_t res, const gr_mat_t mat, slong x, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_vec_mul_scalar_si(GR_MAT_ENTRY(res, i, 0, sz), GR_MAT_ENTRY(mat, i, 0, sz), c, x, ctx);

    return status;
}

int
gr_mat_mul_fmpz(gr_mat_t res, const gr_mat_t mat, const fmpz_t x, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_vec_mul_scalar_fmpz(GR_MAT_ENTRY(res, i, 0, sz), GR_MAT_ENTRY(mat, i, 0, sz), c, x, ctx);

    return status;
}

int
gr_mat_mul_fmpq(gr_mat_t res, const gr_mat_t mat, const fmpq_t x, gr_ctx_t ctx)
{
    slong i, r, c;
    int status = GR_SUCCESS;
    slong sz = ctx->sizeof_elem;

    r = gr_mat_nrows(res, ctx);
    c = gr_mat_ncols(res, ctx);

    if (c != 0)
        for (i = 0; i < r; i++)
            status |= _gr_vec_mul_scalar_fmpq(GR_MAT_ENTRY(res, i, 0, sz), GR_MAT_ENTRY(mat, i, 0, sz), c, x, ctx);

    return status;
}
