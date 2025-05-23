/*
    Copyright (C) 2021 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "acb.h"

PUSH_OPTIONS
DIAGNOSTIC_IGNORE_MAYBE_UNINITIALIZED

void
acb_dot_ui(acb_t res, const acb_t initial, int subtract, acb_srcptr x, slong xstep, const ulong * y, slong ystep, slong len, slong prec)
{
    arb_ptr t;
    slong i;
    ulong v;
    unsigned int bc;
    TMP_INIT;

    /* todo: fast fma and fmma (len=2) code */
    if (len <= 1)
    {
        if (initial == NULL)
        {
            if (len <= 0)
                acb_zero(res);
            else
            {
                acb_mul_ui(res, x, y[0], prec);
                if (subtract)
                    acb_neg(res, res);
            }
            return;
        }
        else if (len <= 0)
        {
            acb_set_round(res, initial, prec);
            return;
        }
    }

    TMP_START;
    t = TMP_ALLOC(sizeof(arb_struct) * len);

    for (i = 0; i < len; i++)
    {
        v = y[i * ystep];

        if (v == 0)
        {
            ARF_XSIZE(arb_midref(t + i)) = 0;
            ARF_EXP(arb_midref(t + i)) = ARF_EXP_ZERO;
        }
        else
        {
            bc = flint_clz(v);

            ARF_EXP(arb_midref(t + i)) = FLINT_BITS - bc;
            ARF_NOPTR_D(arb_midref(t + i))[0] = v << bc;
            ARF_XSIZE(arb_midref(t + i)) = ARF_MAKE_XSIZE(1, 0);
        }

        MAG_EXP(arb_radref(t + i)) = 0;
        MAG_MAN(arb_radref(t + i)) = 0;
    }

    arb_dot(((arb_ptr) res) + 0, (initial == NULL) ? NULL : ((arb_srcptr) initial) + 0, subtract, ((arb_srcptr) x) + 0, 2 * xstep, t, 1, len, prec);
    arb_dot(((arb_ptr) res) + 1, (initial == NULL) ? NULL : ((arb_srcptr) initial) + 1, subtract, ((arb_srcptr) x) + 1, 2 * xstep, t, 1, len, prec);

    TMP_END;
}

POP_OPTIONS
