#include <stdio.h>

long long factorial(int n) {
    if (n < 0) {
        return -1; // Error case for negative numbers
    }
    if (n == 0) {
        return 1;
    }
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    printf("%lld\n", factorial(n));
    return 0;
}
