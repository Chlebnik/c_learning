#include <stdio.h>

long long factorial(int n) {
        if (n < 0) {
                return -1;
        }
        if (n == 0) {
                return 1;
        }
        if (n == 2) {
                return n;
        }
        return n * factorial(n - 1);
}

int main(void) {
        int n;
        scanf("%d", &n);
        long long result = factorial(n);
        if (result == -1) {
                printf("Negative nubmer error.\n");
                return 1;
        }
        printf("%lld\n", result);
        return 0;
}
