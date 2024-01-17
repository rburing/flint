/*
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "fq_zech.h"

TEST_FUNCTION_START(fq_zech_mul, state)
{
    slong ix, jx;
    int result;

    for (ix = 0; ix < 100 * flint_test_multiplier(); ix++)
    {
        fq_zech_ctx_t ctx;

        fq_zech_ctx_init_randtest(ctx, state, 1);

        /* Check aliasing: a = a * b */
        for (jx = 0; jx < 10; jx++)
        {
            fq_zech_t a, b, c;

            fq_zech_init(a, ctx);
            fq_zech_init(b, ctx);
            fq_zech_init(c, ctx);

            fq_zech_randtest(a, state, ctx);
            fq_zech_randtest(b, state, ctx);

            fq_zech_mul(c, a, b, ctx);
            fq_zech_mul(a, a, b, ctx);

            result = (fq_zech_equal(a, c, ctx));
            if (!result)
            {
                flint_printf("FAIL:\n\n");
                flint_printf("a = "), fq_zech_print_pretty(a, ctx), flint_printf("\n");
                flint_printf("b = "), fq_zech_print_pretty(b, ctx), flint_printf("\n");
                flint_printf("c = "), fq_zech_print_pretty(c, ctx), flint_printf("\n");
                flint_abort();
            }

            fq_zech_clear(a, ctx);
            fq_zech_clear(b, ctx);
            fq_zech_clear(c, ctx);
        }

        /* Check aliasing: b = a * b */
        for (jx = 0; jx < 10; jx++)
        {
            fq_zech_t a, b, c;

            fq_zech_init(a, ctx);
            fq_zech_init(b, ctx);
            fq_zech_init(c, ctx);

            fq_zech_randtest(a, state, ctx);
            fq_zech_randtest(b, state, ctx);

            fq_zech_mul(c, a, b, ctx);
            fq_zech_mul(b, a, b, ctx);

            result = (fq_zech_equal(b, c, ctx));
            if (!result)
            {
                flint_printf("FAIL:\n\n");
                flint_printf("a = "), fq_zech_print_pretty(a, ctx), flint_printf("\n");
                flint_printf("b = "), fq_zech_print_pretty(b, ctx), flint_printf("\n");
                flint_printf("c = "), fq_zech_print_pretty(c, ctx), flint_printf("\n");
                flint_abort();
            }

            fq_zech_clear(a, ctx);
            fq_zech_clear(b, ctx);
            fq_zech_clear(c, ctx);
        }

        /* Check aliasing: a = a * a */
        for (jx = 0; jx < 10; jx++)
        {
            fq_zech_t a, c;

            fq_zech_init(a, ctx);
            fq_zech_init(c, ctx);

            fq_zech_randtest(a, state, ctx);

            fq_zech_mul(c, a, a, ctx);
            fq_zech_mul(a, a, a, ctx);

            result = (fq_zech_equal(a, c, ctx));
            if (!result)
            {
                flint_printf("FAIL:\n\n");
                flint_printf("a = "), fq_zech_print_pretty(a, ctx), flint_printf("\n");
                flint_printf("c = "), fq_zech_print_pretty(c, ctx), flint_printf("\n");
                flint_abort();
            }

            fq_zech_clear(a, ctx);
            fq_zech_clear(c, ctx);
        }

        /* Check that a * b == b * a */
        for (jx = 0; jx < 10; jx++)
        {
            fq_zech_t a, b, c1, c2;

            fq_zech_init(a, ctx);
            fq_zech_init(b, ctx);
            fq_zech_init(c1, ctx);
            fq_zech_init(c2, ctx);

            fq_zech_randtest(a, state, ctx);
            fq_zech_randtest(b, state, ctx);

            fq_zech_mul(c1, a, b, ctx);
            fq_zech_mul(c2, b, a, ctx);

            result = (fq_zech_equal(c1, c2, ctx));
            if (!result)
            {
                flint_printf("FAIL:\n\n");
                flint_printf("a  = "), fq_zech_print_pretty(a, ctx), flint_printf("\n");
                flint_printf("b  = "), fq_zech_print_pretty(b, ctx), flint_printf("\n");
                flint_printf("c1 = "), fq_zech_print_pretty(c1, ctx), flint_printf("\n");
                flint_printf("c2 = "), fq_zech_print_pretty(c2, ctx), flint_printf("\n");
                flint_abort();
            }

            fq_zech_clear(a, ctx);
            fq_zech_clear(b, ctx);
            fq_zech_clear(c1, ctx);
            fq_zech_clear(c2, ctx);
        }

        /* Check that (a * b) * c == a * (b * c) */
        for (jx = 0; jx < 10; jx++)
        {
            fq_zech_t a, b, c, lhs, rhs;

            fq_zech_init(a, ctx);
            fq_zech_init(b, ctx);
            fq_zech_init(c, ctx);
            fq_zech_init(lhs, ctx);
            fq_zech_init(rhs, ctx);

            fq_zech_randtest(a, state, ctx);
            fq_zech_randtest(b, state, ctx);
            fq_zech_randtest(c, state, ctx);

            fq_zech_mul(lhs, a, b, ctx);
            fq_zech_mul(lhs, lhs, c, ctx);
            fq_zech_mul(rhs, b, c, ctx);
            fq_zech_mul(rhs, a, rhs, ctx);

            result = (fq_zech_equal(lhs, rhs, ctx));
            if (!result)
            {
                flint_printf("FAIL (a * b) * c == a * (b * c) :\n\n");
                fq_zech_ctx_print(ctx);
                flint_printf("\n");
                flint_printf("a   = "), fq_zech_print_pretty(a, ctx), flint_printf("\n");
                flint_printf("b   = "), fq_zech_print_pretty(b, ctx), flint_printf("\n");
                flint_printf("c   = "), fq_zech_print_pretty(c, ctx), flint_printf("\n");
                flint_printf("lhs = "), fq_zech_print_pretty(lhs, ctx), flint_printf("\n");
                flint_printf("rhs = "), fq_zech_print_pretty(rhs, ctx), flint_printf("\n");
                flint_abort();
            }

            fq_zech_clear(a, ctx);
            fq_zech_clear(b, ctx);
            fq_zech_clear(c, ctx);
            fq_zech_clear(lhs, ctx);
            fq_zech_clear(rhs, ctx);
        }

        fq_zech_ctx_clear(ctx);
    }

    TEST_FUNCTION_END(state);
}
