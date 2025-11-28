
/*
 * BigInt Operator Test Filterscript
 * Complete test suite for all BigInt operators
 */

#include <a_samp>
#include <omp_bigint>
public OnFilterScriptInit()
{
    print("========================================");
    print("BigInt Operator Test Filterscript");
    print("Starting comprehensive operator tests...");
    print("========================================");
    
    // ========================================
    // Test 1: Creating handles and initializing values
    // ========================================
    print("\n--- Test 1: Creating handles ---");
    new BigIntHandle:a = BigIntHandle_FromInt(100);
    new BigIntHandle:b = BigIntHandle_FromInt(50);
    new BigIntHandle:c = BigIntHandle_FromInt(-25);
    
    printf("a = %d", BigIntHandle_ToInt(a));
    printf("b = %d", BigIntHandle_ToInt(b));
    printf("c = %d", BigIntHandle_ToInt(c));
    
    // ========================================
    // Test 2: Operator + (Addition)
    // ========================================
    print("\n--- Test 2: Operator + (Addition) ---");
    new BigIntHandle:sum1 = a + b;           // 100 + 50 = 150
    new BigIntHandle:sum2 = a + 25;          // 100 + 25 = 125
    new BigIntHandle:sum3 = 75 + b;          // 75 + 50 = 125
    new BigIntHandle:sum4 = a + c;           // 100 + (-25) = 75
    
    printf("a + b = %d (Expected: 150)", BigIntHandle_ToInt(sum1));
    printf("a + 25 = %d (Expected: 125)", BigIntHandle_ToInt(sum2));
    printf("75 + b = %d (Expected: 125)", BigIntHandle_ToInt(sum3));
    printf("a + c = %d (Expected: 75)", BigIntHandle_ToInt(sum4));
    
    // ========================================
    // Test 3: Operator - (Subtraction)
    // ========================================
    print("\n--- Test 3: Operator - (Subtraction) ---");
    new BigIntHandle:sub1 = a - b;           // 100 - 50 = 50
    new BigIntHandle:sub2 = a - 25;         // 100 - 25 = 75
    new BigIntHandle:sub3 = 200 - a;        // 200 - 100 = 100
    new BigIntHandle:sub4 = a - c;          // 100 - (-25) = 125
    new BigIntHandle:neg = -a;               // -100
    
    printf("a - b = %d (Expected: 50)", BigIntHandle_ToInt(sub1));
    printf("a - 25 = %d (Expected: 75)", BigIntHandle_ToInt(sub2));
    printf("200 - a = %d (Expected: 100)", BigIntHandle_ToInt(sub3));
    printf("a - c = %d (Expected: 125)", BigIntHandle_ToInt(sub4));
    printf("-a = %d (Expected: -100)", BigIntHandle_ToInt(neg));
    
    // ========================================
    // Test 4: Operator * (Multiplication)
    // ========================================
    print("\n--- Test 4: Operator * (Multiplication) ---");
    new BigIntHandle:mul1 = a * b;           // 100 * 50 = 5000
    new BigIntHandle:mul2 = a * 3;           // 100 * 3 = 300
    new BigIntHandle:mul3 = 4 * b;           // 4 * 50 = 200
    new BigIntHandle:mul4 = c * 2;           // -25 * 2 = -50
    
    printf("a * b = %d (Expected: 5000)", BigIntHandle_ToInt(mul1));
    printf("a * 3 = %d (Expected: 300)", BigIntHandle_ToInt(mul2));
    printf("4 * b = %d (Expected: 200)", BigIntHandle_ToInt(mul3));
    printf("c * 2 = %d (Expected: -50)", BigIntHandle_ToInt(mul4));
    
    // ========================================
    // Test 5: Operator / (Division)
    // ========================================
    print("\n--- Test 5: Operator / (Division) ---");
    new BigIntHandle:div1 = a / b;           // 100 / 50 = 2
    new BigIntHandle:div2 = a / 4;           // 100 / 4 = 25
    new BigIntHandle:div3 = 200 / a;        // 200 / 100 = 2
    new BigIntHandle:div4 = c / 5;           // -25 / 5 = -5
    
    printf("a / b = %d (Expected: 2)", BigIntHandle_ToInt(div1));
    printf("a / 4 = %d (Expected: 25)", BigIntHandle_ToInt(div2));
    printf("200 / a = %d (Expected: 2)", BigIntHandle_ToInt(div3));
    printf("c / 5 = %d (Expected: -5)", BigIntHandle_ToInt(div4));
    
    // ========================================
    // Test 6: Operator % (Modulo)
    // ========================================
    print("\n--- Test 6: Operator %% (Modulo) ---");
    new BigIntHandle:mod1 = a % b;           // 100 % 50 = 0
    new BigIntHandle:mod2 = a % 7;          // 100 % 7 = 2
    new BigIntHandle:mod3 = 23 % a;         // 23 % 100 = 23
    
    printf("a %% b = %d (Expected: 0)", BigIntHandle_ToInt(mod1));
    printf("a %% 7 = %d (Expected: 2)", BigIntHandle_ToInt(mod2));
    printf("23 %% a = %d (Expected: 23)", BigIntHandle_ToInt(mod3));
    
    // ========================================
    // Test 7: Operator ++ and --
    // ========================================
    print("\n--- Test 7: Operator ++ and -- ---");
    new BigIntHandle:inc = BigIntHandle_FromInt(10);
    new BigIntHandle:dec = BigIntHandle_FromInt(10);
    
    printf("Before ++: %d", BigIntHandle_ToInt(inc));
    inc++;
    printf("After ++: %d (Expected: 11)", BigIntHandle_ToInt(inc));
    
    printf("Before --: %d", BigIntHandle_ToInt(dec));
    dec--;
    printf("After --: %d (Expected: 9)", BigIntHandle_ToInt(dec));
    
    // ========================================
    // Test 8: Operator == (Equality)
    // ========================================
    print("\n--- Test 8: Operator == (Equality) ---");
    new BigIntHandle:x = BigIntHandle_FromInt(100);
    new BigIntHandle:y = BigIntHandle_FromInt(100);
    new BigIntHandle:z = BigIntHandle_FromInt(50);
    
    if (a == x)
        printf("a == x: true (Expected: true)");
    else
        printf("a == x: false (Expected: true) - ERROR!");
    
    if (a == z)
        printf("a == z: true (Expected: false) - ERROR!");
    else
        printf("a == z: false (Expected: false)");
    
    if (a == 100)
        printf("a == 100: true (Expected: true)");
    else
        printf("a == 100: false (Expected: true) - ERROR!");
    
    if (a == 50)
        printf("a == 50: true (Expected: false) - ERROR!");
    else
        printf("a == 50: false (Expected: false)");
    
    // ========================================
    // Test 9: Operator != (Inequality)
    // ========================================
    print("\n--- Test 9: Operator != (Inequality) ---");
    if (a != z)
        printf("a != z: true (Expected: true)");
    else
        printf("a != z: false (Expected: true) - ERROR!");
    
    if (a != x)
        printf("a != x: true (Expected: false) - ERROR!");
    else
        printf("a != x: false (Expected: false)");
    
    if (a != 50)
        printf("a != 50: true (Expected: true)");
    else
        printf("a != 50: false (Expected: true) - ERROR!");
    
    // ========================================
    // Test 10: Operator > (Greater than)
    // ========================================
    print("\n--- Test 10: Operator > (Greater than) ---");
    if (a > b)
        printf("a > b: true (Expected: true)");
    else
        printf("a > b: false (Expected: true) - ERROR!");
    
    if (b > a)
        printf("b > a: true (Expected: false) - ERROR!");
    else
        printf("b > a: false (Expected: false)");
    
    if (a > 50)
        printf("a > 50: true (Expected: true)");
    else
        printf("a > 50: false (Expected: true) - ERROR!");
    
    if (50 > a)
        printf("50 > a: true (Expected: false) - ERROR!");
    else
        printf("50 > a: false (Expected: false)");
    
    // ========================================
    // Test 11: Operator < (Less than)
    // ========================================
    print("\n--- Test 11: Operator < (Less than) ---");
    if (b < a)
        printf("b < a: true (Expected: true)");
    else
        printf("b < a: false (Expected: true) - ERROR!");
    
    if (a < b)
        printf("a < b: true (Expected: false) - ERROR!");
    else
        printf("a < b: false (Expected: false)");
    
    if (b < 100)
        printf("b < 100: true (Expected: true)");
    else
        printf("b < 100: false (Expected: true) - ERROR!");
    
    // ========================================
    // Test 12: Operator >= (Greater than or equal)
    // ========================================
    print("\n--- Test 12: Operator >= (Greater than or equal) ---");
    if (a >= b)
        printf("a >= b: true (Expected: true)");
    else
        printf("a >= b: false (Expected: true) - ERROR!");
    
    if (a >= x)
        printf("a >= x: true (Expected: true)");
    else
        printf("a >= x: false (Expected: true) - ERROR!");
    
    if (b >= a)
        printf("b >= a: true (Expected: false) - ERROR!");
    else
        printf("b >= a: false (Expected: false)");
    
    // ========================================
    // Test 13: Operator <= (Less than or equal)
    // ========================================
    print("\n--- Test 13: Operator <= (Less than or equal) ---");
    if (b <= a)
        printf("b <= a: true (Expected: true)");
    else
        printf("b <= a: false (Expected: true) - ERROR!");
    
    if (a <= x)
        printf("a <= x: true (Expected: true)");
    else
        printf("a <= x: false (Expected: true) - ERROR!");
    
    if (a <= b)
        printf("a <= b: true (Expected: false) - ERROR!");
    else
        printf("a <= b: false (Expected: false)");
    
    // ========================================
    // Test 14: Operator ! (Logical NOT)
    // ========================================
    print("\n--- Test 14: Operator ! (Logical NOT) ---");
    new BigIntHandle:zero = BigIntHandle_FromInt(0);
    new BigIntHandle:nonZero = BigIntHandle_FromInt(5);
    
    if (!zero)
        printf("!zero: true (Expected: true)");
    else
        printf("!zero: false (Expected: true) - ERROR!");
    
    if (!nonZero)
        printf("!nonZero: true (Expected: false) - ERROR!");
    else
        printf("!nonZero: false (Expected: false)");
    
    // ========================================
    // Test 15: Conversion between Handle and Array
    // ========================================
    print("\n--- Test 15: Conversion between Handle and Array ---");
    new_bigint(arr);
    BigInt_FromInt(arr, 12345);
    
    new BigIntHandle:h = BigInt_ToHandle(arr);
    printf("Array to Handle: %d (Expected: 12345)", BigIntHandle_ToInt(h));
    
    new_bigint(arr2);
    BigInt_FromHandle(h, arr2);
    printf("Handle to Array: %d (Expected: 12345)", BigInt_ToInt(arr2));
    
    // ========================================
    // Test 16: Complex combined operations
    // ========================================
    print("\n--- Test 16: Complex combined operations ---");
    new BigIntHandle:result1 = (a + b) * 2;      // (100 + 50) * 2 = 300
    new BigIntHandle:result2 = a * b - 1000;     // 100 * 50 - 1000 = 4000
    new BigIntHandle:result3 = (a - b) / 2;      // (100 - 50) / 2 = 25
    
    printf("(a + b) * 2 = %d (Expected: 300)", BigIntHandle_ToInt(result1));
    printf("a * b - 1000 = %d (Expected: 4000)", BigIntHandle_ToInt(result2));
    printf("(a - b) / 2 = %d (Expected: 25)", BigIntHandle_ToInt(result3));
    
    // ========================================
    // Test 17: Comparison with negative numbers
    // ========================================
    print("\n--- Test 17: Comparison with negative numbers ---");
    new BigIntHandle:neg1 = BigIntHandle_FromInt(-10);
    new BigIntHandle:neg2 = BigIntHandle_FromInt(-20);
    
    if (neg1 > neg2)
        printf("-10 > -20: true (Expected: true)");
    else
        printf("-10 > -20: false (Expected: true) - ERROR!");
    
    if (neg1 > 0)
        printf("-10 > 0: true (Expected: false) - ERROR!");
    else
        printf("-10 > 0: false (Expected: false)");
    
    if (0 > neg1)
        printf("0 > -10: true (Expected: true)");
    else
        printf("0 > -10: false (Expected: true) - ERROR!");
    
    // ========================================
    // Test 18: 64-bit integer tests (beyond 32-bit range)
    // ========================================
    print("\n--- Test 18: 64-bit integer tests (beyond 32-bit range) ---");
    
    // Test with numbers larger than 32-bit max (2,147,483,647)
    new BigIntHandle:large1 = BigIntHandle_FromInt(2147483647);  // Max 32-bit int
    new BigIntHandle:large2;
    new_bigint(temp64);
    
    // Create 64-bit max value using FromString
    BigInt_FromString(temp64, "9223372036854775807");  // Max 64-bit positive: 9,223,372,036,854,775,807
    large2 = BigInt_ToHandle(temp64);
    
    printf("32-bit max: %d", BigIntHandle_ToInt(large1));
    printf("64-bit max (9,223,372,036,854,775,807) - ToInt will clamp to 32-bit max: %d", BigIntHandle_ToInt(large2));
    
    // Test arithmetic with large numbers
    new BigIntHandle:large3 = large1 + 1;  // Should be 2,147,483,648 (beyond 32-bit)
    printf("Max 32-bit + 1: %d (Note: ToInt will clamp to 32-bit max)", BigIntHandle_ToInt(large3));
    
    // Test with negative large numbers
    new BigIntHandle:largeNeg1 = BigIntHandle_FromInt(-2147483648);  // Min 32-bit int
    new BigIntHandle:largeNeg2;
    BigInt_FromString(temp64, "-9223372036854775808");  // Min 64-bit negative: -9,223,372,036,854,775,808
    largeNeg2 = BigInt_ToHandle(temp64);
    
    printf("32-bit min: %d", BigIntHandle_ToInt(largeNeg1));
    printf("64-bit min (-9,223,372,036,854,775,808) - ToInt will clamp to 32-bit min: %d", BigIntHandle_ToInt(largeNeg2));
    
    // Test multiplication that exceeds 32-bit
    new BigIntHandle:mult1 = BigIntHandle_FromInt(100000);
    new BigIntHandle:mult2 = BigIntHandle_FromInt(100000);
    new BigIntHandle:multResult = mult1 * mult2;  // 10,000,000,000 (exceeds 32-bit)
    printf("100000 * 100000 = %d (Note: ToInt will clamp, but value is 10 billion)", BigIntHandle_ToInt(multResult));
    
    // Test with specific 64-bit values using FromString for accuracy
    // 5,000,000,000 (5 billion)
    BigInt_FromString(temp64, "5000000000");
    new BigIntHandle:fiveBillion = BigInt_ToHandle(temp64);
    
    // 10,000,000,000 (10 billion)
    BigInt_FromString(temp64, "10000000000");
    new BigIntHandle:tenBillion = BigInt_ToHandle(temp64);
    
    printf("5 billion handle created");
    printf("10 billion handle created");
    
    // Test comparison with large numbers
    if (tenBillion > fiveBillion)
        printf("10 billion > 5 billion: true (Expected: true)");
    else
        printf("10 billion > 5 billion: false (Expected: true) - ERROR!");
    
    if (fiveBillion > tenBillion)
        printf("5 billion > 10 billion: true (Expected: false) - ERROR!");
    else
        printf("5 billion > 10 billion: false (Expected: false)");
    
    // Test addition with large numbers
    new BigIntHandle:sumLarge = fiveBillion + fiveBillion;  // Should be 10 billion
    printf("5 billion + 5 billion = 10 billion (check via comparison)");
    if (sumLarge == tenBillion)
        printf("sumLarge == tenBillion: true (Expected: true)");
    else
        printf("sumLarge == tenBillion: false (Expected: true) - ERROR!");
    
    // Test subtraction with large numbers
    new BigIntHandle:subLarge = tenBillion - fiveBillion;  // Should be 5 billion
    if (subLarge == fiveBillion)
        printf("10 billion - 5 billion == 5 billion: true (Expected: true)");
    else
        printf("10 billion - 5 billion == 5 billion: false (Expected: true) - ERROR!");
    
    // Test division with large numbers
    new BigIntHandle:divLarge = tenBillion / 2;  // Should be 5 billion
    if (divLarge == fiveBillion)
        printf("10 billion / 2 == 5 billion: true (Expected: true)");
    else
        printf("10 billion / 2 == 5 billion: false (Expected: true) - ERROR!");
    
    // Test modulo with large numbers
    new BigIntHandle:modLarge = tenBillion % 3;
    printf("10 billion %% 3 calculated");
    
    // Test with more 64-bit values
    // 1,000,000,000,000 (1 trillion)
    BigInt_FromString(temp64, "1000000000000");
    new BigIntHandle:oneTrillion = BigInt_ToHandle(temp64);
    
    // 2,000,000,000,000 (2 trillion)
    BigInt_FromString(temp64, "2000000000000");
    new BigIntHandle:twoTrillion = BigInt_ToHandle(temp64);
    
    printf("1 trillion and 2 trillion handles created");
    
    // Test multiplication with trillion values
    new BigIntHandle:multTrillion = oneTrillion * 2;
    if (multTrillion == twoTrillion)
        printf("1 trillion * 2 == 2 trillion: true (Expected: true)");
    else
        printf("1 trillion * 2 == 2 trillion: false (Expected: true) - ERROR!");
    
    // Test division with trillion values
    new BigIntHandle:divTrillion = twoTrillion / 2;
    if (divTrillion == oneTrillion)
        printf("2 trillion / 2 == 1 trillion: true (Expected: true)");
    else
        printf("2 trillion / 2 == 1 trillion: false (Expected: true) - ERROR!");
    
    // Test comparison with trillion values
    if (twoTrillion > oneTrillion)
        printf("2 trillion > 1 trillion: true (Expected: true)");
    else
        printf("2 trillion > 1 trillion: false (Expected: true) - ERROR!");
    
    // Test with max 64-bit value operations
    new BigIntHandle:max64 = large2;  // Max 64-bit from above
    new BigIntHandle:max64Minus1 = max64 - 1;
    if (max64 > max64Minus1)
        printf("Max 64-bit > (Max 64-bit - 1): true (Expected: true)");
    else
        printf("Max 64-bit > (Max 64-bit - 1): false (Expected: true) - ERROR!");
    
    // Test with min 64-bit value operations
    new BigIntHandle:min64 = largeNeg2;  // Min 64-bit from above
    new BigIntHandle:min64Plus1 = min64 + 1;
    if (min64Plus1 > min64)
        printf("(Min 64-bit + 1) > Min 64-bit: true (Expected: true)");
    else
        printf("(Min 64-bit + 1) > Min 64-bit: false (Expected: true) - ERROR!");
    
    // Free trillion handles
    BigIntHandle_Free(oneTrillion);
    BigIntHandle_Free(twoTrillion);
    BigIntHandle_Free(multTrillion);
    BigIntHandle_Free(divTrillion);
    BigIntHandle_Free(max64Minus1);
    BigIntHandle_Free(min64Plus1);
    
    // Test with very large negative numbers using FromString
    // -5,000,000,000
    BigInt_FromString(temp64, "-5000000000");
    new BigIntHandle:negFiveBillion = BigInt_ToHandle(temp64);
    
    // -10,000,000,000
    BigInt_FromString(temp64, "-10000000000");
    new BigIntHandle:negTenBillion = BigInt_ToHandle(temp64);
    
    if (negFiveBillion > negTenBillion)
        printf("-5 billion > -10 billion: true (Expected: true)");
    else
        printf("-5 billion > -10 billion: false (Expected: true) - ERROR!");
    
    if (negTenBillion > 0)
        printf("-10 billion > 0: true (Expected: false) - ERROR!");
    else
        printf("-10 billion > 0: false (Expected: false)");
    
    if (0 > negTenBillion)
        printf("0 > -10 billion: true (Expected: true)");
    else
        printf("0 > -10 billion: false (Expected: true) - ERROR!");
    
    // Test arithmetic with negative large numbers
    new BigIntHandle:negSum = negFiveBillion + negFiveBillion;  // Should be -10 billion
    if (negSum == negTenBillion)
        printf("-5 billion + -5 billion == -10 billion: true (Expected: true)");
    else
        printf("-5 billion + -5 billion == -10 billion: false (Expected: true) - ERROR!");
    
    // Test conversion to string for large numbers
    new str[64];
    BigInt_FromHandle(tenBillion, temp64);
    BigInt_ToString(temp64, str, sizeof(str));
    printf("10 billion as string: %s", str);
    
    BigInt_FromHandle(negTenBillion, temp64);
    BigInt_ToString(temp64, str, sizeof(str));
    printf("-10 billion as string: %s", str);
    
    // Free large number handles
    BigIntHandle_Free(large1);
    BigIntHandle_Free(large2);
    BigIntHandle_Free(large3);
    BigIntHandle_Free(largeNeg1);
    BigIntHandle_Free(largeNeg2);
    BigIntHandle_Free(mult1);
    BigIntHandle_Free(mult2);
    BigIntHandle_Free(multResult);
    BigIntHandle_Free(fiveBillion);
    BigIntHandle_Free(tenBillion);
    BigIntHandle_Free(sumLarge);
    BigIntHandle_Free(subLarge);
    BigIntHandle_Free(divLarge);
    BigIntHandle_Free(modLarge);
    BigIntHandle_Free(negFiveBillion);
    BigIntHandle_Free(negTenBillion);
    BigIntHandle_Free(negSum);
    
    // ========================================
    // Test 19: Freeing handles
    // ========================================
    print("\n--- Test 19: Freeing handles ---");
    BigIntHandle_Free(a);
    BigIntHandle_Free(b);
    BigIntHandle_Free(c);
    BigIntHandle_Free(sum1);
    BigIntHandle_Free(sum2);
    BigIntHandle_Free(sum3);
    BigIntHandle_Free(sum4);
    BigIntHandle_Free(sub1);
    BigIntHandle_Free(sub2);
    BigIntHandle_Free(sub3);
    BigIntHandle_Free(sub4);
    BigIntHandle_Free(neg);
    BigIntHandle_Free(mul1);
    BigIntHandle_Free(mul2);
    BigIntHandle_Free(mul3);
    BigIntHandle_Free(mul4);
    BigIntHandle_Free(div1);
    BigIntHandle_Free(div2);
    BigIntHandle_Free(div3);
    BigIntHandle_Free(div4);
    BigIntHandle_Free(mod1);
    BigIntHandle_Free(mod2);
    BigIntHandle_Free(mod3);
    BigIntHandle_Free(inc);
    BigIntHandle_Free(dec);
    BigIntHandle_Free(x);
    BigIntHandle_Free(y);
    BigIntHandle_Free(z);
    BigIntHandle_Free(h);
    BigIntHandle_Free(result1);
    BigIntHandle_Free(result2);
    BigIntHandle_Free(result3);
    BigIntHandle_Free(zero);
    BigIntHandle_Free(nonZero);
    BigIntHandle_Free(neg1);
    BigIntHandle_Free(neg2);
    
    print("All handles freed");
    
    print("\n========================================");
    print("BigInt Operator Test - Test Complete!");
    print("========================================");
    
    return 1;
}

public OnFilterScriptExit()
{
    print("========================================");
    print("BigInt Operator Test Filterscript");
    print("Unloaded!");
    print("========================================");
    
    return 1;
}
