/*
    Copyright (C) 2023, 2025 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "ulong_extras.h"
#include "gr_poly.h"

TEST_FUNCTION_START(gr_poly_divrem_newton_n_preinv, state)
{
    slong iter;

    for (iter = 0; iter < 1000; iter++)
    {
        int status;
        gr_ctx_t ctx;
        gr_poly_t A, B, Binv, Q, R, Q2, R2;

        gr_ctx_init_random(ctx, state);

        gr_poly_init(A, ctx);
        gr_poly_init(B, ctx);
        gr_poly_init(Binv, ctx);
        gr_poly_init(Q, ctx);
        gr_poly_init(R, ctx);
        gr_poly_init(Q2, ctx);
        gr_poly_init(R2, ctx);

        status = GR_SUCCESS;

        status |= gr_poly_randtest(A, state, 1 + n_randint(state, 6), ctx);
        status |= gr_poly_randtest(B, state, 1 + n_randint(state, 6), ctx);
        status |= gr_poly_randtest(Q, state, 1 + n_randint(state, 6), ctx);
        status |= gr_poly_randtest(R, state, 1 + n_randint(state, 6), ctx);

        if (n_randint(state, 3) == 0)
        {
            status |= gr_poly_mul(A, A, B, ctx);
            status |= gr_poly_add(A, A, R, ctx);
        }

        status |= gr_poly_reverse(Binv, B, B->length, ctx);
        status |= gr_poly_inv_series(Binv, Binv, B->length, ctx);

        /* different aliasing cases */
        switch (n_randint(state, 7))
        {
            case 0:
                status |= gr_poly_set(Q, A, ctx);
                status |= gr_poly_divrem_newton_n_preinv(Q, R, Q, B, Binv, ctx);
                break;
            case 1:
                status |= gr_poly_set(R, A, ctx);
                status |= gr_poly_divrem_newton_n_preinv(Q, R, R, B, Binv, ctx);
                break;
            case 2:
                status |= gr_poly_set(Q, B, ctx);
                status |= gr_poly_divrem_newton_n_preinv(Q, R, A, Q, Binv, ctx);
                break;
            case 3:
                status |= gr_poly_set(R, B, ctx);
                status |= gr_poly_divrem_newton_n_preinv(Q, R, A, R, Binv, ctx);
                break;
            case 4:
                status |= gr_poly_set(Q, Binv, ctx);
                status |= gr_poly_divrem_newton_n_preinv(Q, R, A, B, Q, ctx);
                break;
            case 5:
                status |= gr_poly_set(R, Binv, ctx);
                status |= gr_poly_divrem_newton_n_preinv(Q, R, A, B, R, ctx);
                break;
            default:
                status |= gr_poly_divrem_newton_n_preinv(Q, R, A, B, Binv, ctx);
                break;
        }

        if (status == GR_SUCCESS)
        {
            status |= gr_poly_divrem(Q2, R2, A, B, ctx);

            if (status == GR_SUCCESS && (gr_poly_equal(Q, Q2, ctx) == T_FALSE ||
                gr_poly_equal(R, R2, ctx) == T_FALSE))
            {
                flint_printf("FAIL\n\n");
                flint_printf("A = "); gr_poly_print(A, ctx); flint_printf("\n");
                flint_printf("B = "); gr_poly_print(B, ctx); flint_printf("\n");
                flint_printf("Q = "); gr_poly_print(Q, ctx); flint_printf("\n");
                flint_printf("R = "); gr_poly_print(R, ctx); flint_printf("\n");
                flint_printf("Q2 = "); gr_poly_print(Q2, ctx); flint_printf("\n");
                flint_printf("R2 = "); gr_poly_print(R2, ctx); flint_printf("\n");
                flint_abort();
            }
        }

        gr_poly_clear(A, ctx);
        gr_poly_clear(B, ctx);
        gr_poly_clear(Binv, ctx);
        gr_poly_clear(Q, ctx);
        gr_poly_clear(R, ctx);
        gr_poly_clear(Q2, ctx);
        gr_poly_clear(R2, ctx);

        gr_ctx_clear(ctx);
    }

    TEST_FUNCTION_END(state);
}
