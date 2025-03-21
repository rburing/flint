/*
    Copyright (C) 2021 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include <string.h>
#include "fexpr.h"
#include "fexpr_builtin.h"

void
fexpr_set_symbol_str(fexpr_t res, const char * s)
{
    slong i, len;

    i = fexpr_builtin_lookup(s);

    if (i != -1)
    {
        res->data[0] = FEXPR_TYPE_SMALL_SYMBOL | (i << 16);
        return;
    }

    len = strlen(s);

    if (len <= FEXPR_SMALL_SYMBOL_LEN)
    {
        slong i;
        ulong data;

        data = FEXPR_TYPE_SMALL_SYMBOL;
        for (i = 0; i < len; i++)
            data |= (((ulong) s[i]) << ((i + 1) * 8));

        res->data[0] = data;
    }
    else
    {
        slong data_size;

        data_size = len + 1;
        data_size = (data_size + sizeof(ulong) - 1) / sizeof(ulong);

        fexpr_fit_size(res, data_size + 1);
        res->data[0] = FEXPR_TYPE_BIG_SYMBOL | ((data_size + 1) << FEXPR_TYPE_BITS);
        res->data[data_size] = 0;  /* zero pad for consistency */
        memcpy((char *) (res->data + 1), s, len + 1);
    }
}
