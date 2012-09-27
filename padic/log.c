/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Sebastian Pancratz
 
******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "padic.h"
#include "ulong_extras.h"

long _padic_log_bound(long v, long N, long p)
{
    long b, c;

    c = N - n_flog(v, p);
    b = c + n_clog(c, p) + 1;

    /*
        Now $i v - \ord_p(i) \geq N$ for all $i \geq b$.  We work 
        backwards to find the first $i$ such that this fails, then 
        using that the function is strictly increasing for $i \geq 2$.
     */

    while (--b >= 2)
    {
        long t = b * v - n_clog(b, p) - N;

        if (t < 0)
            return b + 1;
    }

    return 2;
}

void _padic_log(fmpz_t z, const fmpz_t y, long v, const fmpz_t p, long N)
{
    if (N < (1L << 9) / (long) fmpz_bits(p))
    {
        _padic_log_rectangular(z, y, v, p, N);
    }
    else
    {
        _padic_log_balanced(z, y, v, p, N);
    }
}

int padic_log(padic_t rop, const padic_t op, const padic_ctx_t ctx)
{
    const fmpz *p = ctx->p;
    const long N  = padic_prec(rop);

    if (padic_val(op) < 0)
    {
        return 0;
    }
    else
    {
        fmpz_t x;
        int ans;

        fmpz_init(x);

        padic_get_fmpz(x, op, ctx);
        fmpz_sub_ui(x, x, 1);
        fmpz_neg(x, x);

        if (fmpz_is_zero(x))
        {
            padic_zero(rop);
            ans = 1;
        }
        else
        {
            fmpz_t t;
            long v;

            fmpz_init(t);
            v = fmpz_remove(t, x, p);
            fmpz_clear(t);

            if (v >= 2 || (!fmpz_equal_ui(p, 2) && v >= 1))
            {
                if (v >= N)
                {
                    padic_zero(rop);
                }
                else
                {
                    _padic_log(padic_unit(rop), x, v, p, N);
                    padic_val(rop) = 0;
                    _padic_canonicalise(rop, ctx);
                }
                ans = 1;
            }
            else
            {
                ans = 0;
            }
        }

        fmpz_clear(x);
        return ans;
    }
}

