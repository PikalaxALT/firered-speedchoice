#include "global.h"

fx16 mul_Q_8_8(fx16 x, fx16 y)
{
    s32 result;

    result = x;
    result *= y;
    result /= 256;
    return result;
}

fx16 mul_Q_N_S(u8 s, fx16 x, fx16 y)
{
    s32 result;

    result = x;
    result *= y;
    result /= (1 << s);
    return result;
}

fx32 mul_Q_24_8(fx32 x, fx32 y)
{
    s64 result;

    result = x;
    result *= y;
    result /= 256;
    return result;
}

fx16 div_Q_8_8(fx16 x, fx16 y)
{
    if (y == 0)
    {
        return 0;
    }
    return (x << 8) / y;
}

fx16 div_Q_N_S(u8 s, fx16 x, fx16 y)
{
    if (y == 0)
    {
        return 0;
    }
    return (x << s) / y;
}

fx32 div_Q_24_8(fx32 x, fx32 y)
{
    s64 _x;

    if (y == 0)
    {
        return 0;
    }
    _x = x;
    _x *= 256;
    return _x / y;
}

fx16 inv_Q_8_8(fx16 y)
{
    s32 x;

    x = 0x10000;
    return x / y;
}

fx16 inv_Q_N_S(u8 s, fx16 y)
{
    s32 x;

    x = 0x100 << s;
    return x / y;
}

fx32 inv_Q_24_8(fx32 y)
{
    s64 x;

    x = 0x10000;
    return x / y;
}
