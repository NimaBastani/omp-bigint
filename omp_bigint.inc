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
