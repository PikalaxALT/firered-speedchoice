#ifndef GUARD_MATH_UTIL_H
#define GUARD_MATH_UTIL_H

fx16 mul_Q_8_8(fx16 x, fx16 y);
fx16 mul_Q_N_S(u8 s, fx16 x, fx16 y);
fx32 mul_Q_24_8(fx32 x, fx32 y);
fx16 div_Q_8_8(fx16 x, fx16 y);
fx16 div_Q_N_S(u8 s, fx16 x, fx16 y);
fx32 div_Q_24_8(fx32 x, fx32 y);
fx16 inv_Q_8_8(fx16 y);
fx16 inv_Q_N_S(u8 s, fx16 y);
fx32 inv_Q_24_8(fx32 y);

#endif //GUARD_MATH_UTIL_H
