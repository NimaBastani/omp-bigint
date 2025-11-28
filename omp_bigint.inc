// omp_bigint.inc
#if defined _OMP_BIGINT_INCLUDED
    #endinput
#endif
#define _OMP_BIGINT_INCLUDED

enum eBigIntParts
{
    BIGINT_LO, // low 32 bits (unsigned)
    BIGINT_HI  // high 32 bits (signed)
};

// ----------------------------------------------------
// Natives: conversion
// ----------------------------------------------------
native BigInt_FromInt(BigInt:value[], v);
native BigInt_ToInt(const BigInt:value[]);

native BigInt_FromParts(BigInt:value[], lo, hi);
native BigInt_GetParts(const BigInt:value[], &lo, &hi);

native bool:BigInt_FromString(BigInt:value[], const str[]);
native BigInt_ToString(const BigInt:value[], dest[], size = sizeof dest);

// ----------------------------------------------------
// Natives: arithmetic BigInt <-> BigInt
// ----------------------------------------------------
native BigInt_Add(BigInt:dst[], const BigInt:src[]);
native BigInt_Sub(BigInt:dst[], const BigInt:src[]);
native BigInt_Mul(BigInt:dst[], const BigInt:src[]);
native bool:BigInt_Div(BigInt:dst[], const BigInt:src[]); // false on div0
native bool:BigInt_Mod(BigInt:dst[], const BigInt:src[]); // false on div0

// ----------------------------------------------------
// Natives: arithmetic BigInt <-> 32-bit int
// ----------------------------------------------------
native BigInt_AddInt(BigInt:dst[], v);
native BigInt_SubInt(BigInt:dst[], v);
native BigInt_MulInt(BigInt:dst[], v);
native bool:BigInt_DivInt(BigInt:dst[], v);  // false on div0
native bool:BigInt_ModInt(BigInt:dst[], v);  // false on div0

// ----------------------------------------------------
// Natives: comparisons
// ----------------------------------------------------
native BigInt_Cmp(const BigInt:a[], const BigInt:b[]);      // -1, 0, 1
native BigInt_CmpInt(const BigInt:a[], v);                  // -1, 0, 1

// ----------------------------------------------------
// Small helper macros/sugar
// ----------------------------------------------------
#define new_bigint(%0)                new BigInt:%0[eBigIntParts]
#define new_bigint_array(%0,%1)       new BigInt:%0[%1][eBigIntParts]

#define BigInt_SetInt(%0,%1)          BigInt_FromInt(%0, %1)
#define BigInt_SetParts(%0,%1,%2)     BigInt_FromParts(%0, %1, %2)

#define BigInt_Eq(%0,%1)              (BigInt_Cmp(%0,%1) == 0)
#define BigInt_Ne(%0,%1)              (BigInt_Cmp(%0,%1) != 0)
#define BigInt_Gt(%0,%1)              (BigInt_Cmp(%0,%1) > 0)
#define BigInt_Ge(%0,%1)              (BigInt_Cmp(%0,%1) >= 0)
#define BigInt_Lt(%0,%1)              (BigInt_Cmp(%0,%1) < 0)
#define BigInt_Le(%0,%1)              (BigInt_Cmp(%0,%1) <= 0)

#define BigInt_EqInt(%0,%1)           (BigInt_CmpInt(%0,%1) == 0)
#define BigInt_NeInt(%0,%1)           (BigInt_CmpInt(%0,%1) != 0)
#define BigInt_GtInt(%0,%1)           (BigInt_CmpInt(%0,%1) > 0)
#define BigInt_GeInt(%0,%1)           (BigInt_CmpInt(%0,%1) >= 0)
#define BigInt_LtInt(%0,%1)           (BigInt_CmpInt(%0,%1) < 0)
#define BigInt_LeInt(%0,%1)           (BigInt_CmpInt(%0,%1) <= 0)

/**************************************************/

//========================== BigInt Handle + Operations by NimaBastani ==========================

#define MAX_BIGINT_POOL 2048
static BigInt:g_BigIntPool[MAX_BIGINT_POOL][eBigIntParts];
static bool:g_BigIntPoolUsed[MAX_BIGINT_POOL];
static g_BigIntPoolNext = 0;

stock BigIntHandle:BigIntHandle_Alloc()
{
    new start = g_BigIntPoolNext;
    for (new i = 0; i < MAX_BIGINT_POOL; i++)
    {
        new idx = (start + i) % MAX_BIGINT_POOL;
        if (!g_BigIntPoolUsed[idx])
        {
            g_BigIntPoolUsed[idx] = true;
            g_BigIntPoolNext = (idx + 1) % MAX_BIGINT_POOL;
            BigInt_FromInt(g_BigIntPool[idx], 0);
            return BigIntHandle:idx;
        }
    }
    return BigIntHandle:-1; // Pool full
}

stock BigIntHandle_Free(BigIntHandle:handle)
{
    if (_:handle >= 0 && _:handle < MAX_BIGINT_POOL)
    {
        g_BigIntPoolUsed[_:handle] = false;
    }
}

stock BigIntHandle:BigInt_ToHandle(const BigInt:value[])
{
    new BigIntHandle:h = BigIntHandle_Alloc();
    if (_:h >= 0)
    {
        BigInt_Copy(g_BigIntPool[_:h], value);
    }
    return h;
}

stock BigInt_FromHandle(BigIntHandle:handle, BigInt:value[])
{
    if (_:handle >= 0 && _:handle < MAX_BIGINT_POOL && g_BigIntPoolUsed[_:handle])
    {
        BigInt_Copy(value, g_BigIntPool[_:handle]);
    }
}

stock BigIntHandle_ToInt(BigIntHandle:handle)
{
    if (_:handle >= 0 && _:handle < MAX_BIGINT_POOL && g_BigIntPoolUsed[_:handle])
    {
        return BigInt_ToInt(g_BigIntPool[_:handle]);
    }
    return 0;
}

stock BigInt_Copy(BigInt:dst[], const BigInt:src[])
{
    dst[BIGINT_LO] = src[BIGINT_LO];
    dst[BIGINT_HI] = src[BIGINT_HI];
}

stock BigIntHandle:BigIntHandle_FromInt(v)
{
    new BigIntHandle:h = BigIntHandle_Alloc();
    if (_:h >= 0)
    {
        BigInt_FromInt(g_BigIntPool[_:h], v);
    }
    return h;
}
stock BigIntHandle:operator+(BigIntHandle:oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        BigInt_Add(g_BigIntPool[_:result], g_BigIntPool[_:oper2]);
    }
    return result;
}

stock BigIntHandle:operator+(BigIntHandle:oper1, oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        BigInt_AddInt(g_BigIntPool[_:result], oper2);
    }
    return result;
}

stock BigIntHandle:operator+(oper1, BigIntHandle:oper2)
{
    return oper2 + oper1;
}

stock BigIntHandle:operator-(BigIntHandle:oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        BigInt_Sub(g_BigIntPool[_:result], g_BigIntPool[_:oper2]);
    }
    return result;
}

stock BigIntHandle:operator-(BigIntHandle:oper1, oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        BigInt_SubInt(g_BigIntPool[_:result], oper2);
    }
    return result;
}

stock BigIntHandle:operator-(oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        BigInt_FromInt(g_BigIntPool[_:result], oper1);
        BigInt_Sub(g_BigIntPool[_:result], g_BigIntPool[_:oper2]);
    }
    return result;
}

stock BigIntHandle:operator*(BigIntHandle:oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        BigInt_Mul(g_BigIntPool[_:result], g_BigIntPool[_:oper2]);
    }
    return result;
}

stock BigIntHandle:operator*(BigIntHandle:oper1, oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        BigInt_MulInt(g_BigIntPool[_:result], oper2);
    }
    return result;
}

stock BigIntHandle:operator*(oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper2]);
        BigInt_MulInt(g_BigIntPool[_:result], oper1);
    }
    return result;
}

stock BigIntHandle:operator/(BigIntHandle:oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        if (BigInt_CmpInt(g_BigIntPool[_:oper2], 0) == 0)
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        if (!BigInt_Div(g_BigIntPool[_:result], g_BigIntPool[_:oper2]))
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
    }
    return result;
}

stock BigIntHandle:operator/(BigIntHandle:oper1, oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        if (oper2 == 0)
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        if (!BigInt_DivInt(g_BigIntPool[_:result], oper2))
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
    }
    return result;
}

stock BigIntHandle:operator/(oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        if (BigInt_CmpInt(g_BigIntPool[_:oper2], 0) == 0)
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
        BigInt_FromInt(g_BigIntPool[_:result], oper1);
        if (!BigInt_Div(g_BigIntPool[_:result], g_BigIntPool[_:oper2]))
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
    }
    return result;
}

stock BigIntHandle:operator%(BigIntHandle:oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        if (BigInt_CmpInt(g_BigIntPool[_:oper2], 0) == 0)
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        if (!BigInt_Mod(g_BigIntPool[_:result], g_BigIntPool[_:oper2]))
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
    }
    return result;
}

stock BigIntHandle:operator%(BigIntHandle:oper1, oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        if (oper2 == 0)
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
        BigInt_Copy(g_BigIntPool[_:result], g_BigIntPool[_:oper1]);
        if (!BigInt_ModInt(g_BigIntPool[_:result], oper2))
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
    }
    return result;
}

stock BigIntHandle:operator%(oper1, BigIntHandle:oper2)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        if (BigInt_CmpInt(g_BigIntPool[_:oper2], 0) == 0)
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
        BigInt_FromInt(g_BigIntPool[_:result], oper1);
        if (!BigInt_Mod(g_BigIntPool[_:result], g_BigIntPool[_:oper2]))
        {
            BigIntHandle_Free(result);
            return BigIntHandle:-1;
        }
    }
    return result;
}

stock BigIntHandle:operator++(BigIntHandle:oper)
{
    if (_:oper >= 0 && _:oper < MAX_BIGINT_POOL)
    {
        BigInt_AddInt(g_BigIntPool[_:oper], 1);
    }
    return oper;
}

stock BigIntHandle:operator--(BigIntHandle:oper)
{
    if (_:oper >= 0 && _:oper < MAX_BIGINT_POOL)
    {
        BigInt_SubInt(g_BigIntPool[_:oper], 1);
    }
    return oper;
}

stock BigIntHandle:operator-(BigIntHandle:oper)
{
    new BigIntHandle:result = BigIntHandle_Alloc();
    if (_:result >= 0 && _:oper >= 0 && _:oper < MAX_BIGINT_POOL)
    {
        new BigInt:zero[eBigIntParts];
        BigInt_FromInt(zero, 0);
        BigInt_Copy(g_BigIntPool[_:result], zero);
        BigInt_Sub(g_BigIntPool[_:result], g_BigIntPool[_:oper]);
    }
    return result;
}

stock bool:operator==(BigIntHandle:oper1, BigIntHandle:oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_Cmp(g_BigIntPool[_:oper1], g_BigIntPool[_:oper2]) == 0;
    }
    return false;
}

stock bool:operator==(BigIntHandle:oper1, oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper1], oper2) == 0;
    }
    return false;
}

stock bool:operator==(oper1, BigIntHandle:oper2)
{
    if (_:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper2], oper1) == 0;
    }
    return false;
}

stock bool:operator!=(BigIntHandle:oper1, BigIntHandle:oper2)
{
    return !(oper1 == oper2);
}

stock bool:operator!=(BigIntHandle:oper1, oper2)
{
    return !(oper1 == oper2);
}

stock bool:operator!=(oper1, BigIntHandle:oper2)
{
    return !(oper1 == oper2);
}

stock bool:operator>(BigIntHandle:oper1, BigIntHandle:oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_Cmp(g_BigIntPool[_:oper1], g_BigIntPool[_:oper2]) > 0;
    }
    return false;
}

stock bool:operator>(BigIntHandle:oper1, oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper1], oper2) > 0;
    }
    return false;
}

stock bool:operator>(oper1, BigIntHandle:oper2)
{
    if (_:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper2], oper1) < 0;
    }
    return false;
}

stock bool:operator>=(BigIntHandle:oper1, BigIntHandle:oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_Cmp(g_BigIntPool[_:oper1], g_BigIntPool[_:oper2]) >= 0;
    }
    return false;
}

stock bool:operator>=(BigIntHandle:oper1, oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper1], oper2) >= 0;
    }
    return false;
}

stock bool:operator>=(oper1, BigIntHandle:oper2)
{
    if (_:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper2], oper1) <= 0;
    }
    return false;
}

stock bool:operator<(BigIntHandle:oper1, BigIntHandle:oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_Cmp(g_BigIntPool[_:oper1], g_BigIntPool[_:oper2]) < 0;
    }
    return false;
}

stock bool:operator<(BigIntHandle:oper1, oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper1], oper2) < 0;
    }
    return false;
}

stock bool:operator<(oper1, BigIntHandle:oper2)
{
    if (_:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper2], oper1) > 0;
    }
    return false;
}

stock bool:operator<=(BigIntHandle:oper1, BigIntHandle:oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL && _:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_Cmp(g_BigIntPool[_:oper1], g_BigIntPool[_:oper2]) <= 0;
    }
    return false;
}

stock bool:operator<=(BigIntHandle:oper1, oper2)
{
    if (_:oper1 >= 0 && _:oper1 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper1], oper2) <= 0;
    }
    return false;
}

stock bool:operator<=(oper1, BigIntHandle:oper2)
{
    if (_:oper2 >= 0 && _:oper2 < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper2], oper1) >= 0;
    }
    return false;
}

stock bool:operator!(BigIntHandle:oper)
{
    if (_:oper >= 0 && _:oper < MAX_BIGINT_POOL)
    {
        return BigInt_CmpInt(g_BigIntPool[_:oper], 0) == 0;
    }
    return true;
}
