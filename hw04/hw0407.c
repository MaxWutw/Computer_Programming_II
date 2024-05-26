#include <stdio.h>
#include <math.h>
#include <tgmath.h>

int main() {
    // Using math.h
    double result_math_double = pow(2.0, 3.0);       // Requires pow
    float result_math_float = powf(2.0f, 3.0f);      // Requires powf
    long double result_math_long_double = powl(2.0L, 3.0L); // Requires powl

    printf("math.h results: %f, %f, %Lf\n", result_math_double, result_math_float, result_math_long_double);

    // Using tgmath.h
    double result_tgmath_double = pow(2.0, 3.0);       // Uses type-generic pow
    float result_tgmath_float = pow(2.0f, 3.0f);      // Uses type-generic pow
    long double result_tgmath_long_double = pow(2.0L, 3.0L); // Uses type-generic pow

    printf("tgmath.h results: %f, %f, %Lf\n", result_tgmath_double, result_tgmath_float, result_tgmath_long_double);

    return 0;
}
