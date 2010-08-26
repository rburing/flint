/*============================================================================

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

===============================================================================*/
/******************************************************************************

 Copyright (C) 2010 Fredrik Johansson

******************************************************************************/

#ifndef ARITH_H
#define ARITH_H

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"

typedef struct
{
    int sign;
    fmpz * p;
    fmpz * exp;
    long alloc;
    long length;
} fmpz_factor_struct;

typedef fmpz_factor_struct fmpz_factor_t[1];


void fmpz_factor_init(fmpz_factor_t factor);
void fmpz_factor_clear(fmpz_factor_t factor);
void fmpz_factor_print(fmpz_factor_t factor);

void _fmpz_factor_si(fmpz_factor_t factor, long n);
void _fmpz_factor_fit_length(fmpz_factor_t factor, long len);
void _fmpz_factor_append_ui(fmpz_factor_t factor, ulong p, ulong exp);
void _fmpz_factor_set_length(fmpz_factor_t factor, long newlen);
void _fmpz_factor_extend_factor_n(fmpz_factor_t factor, ulong n);

void fmpz_factor(fmpz_factor_t factor, fmpz_t n);
void fmpz_unfactor(fmpz_t n, fmpz_factor_t factor);

void fmpz_primorial(fmpz_t res, long n);
void fmpz_poly_ramanujan_tau(fmpz_poly_t res, long n);
void fmpz_ramanujan_tau(fmpz_t res, fmpz_t n);
void fmpz_divisors(fmpz_poly_t res, fmpz_t n);
void fmpz_divisor_sigma(fmpz_t res, fmpz_t n, ulong k);

#endif
