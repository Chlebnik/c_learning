#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
        size_t len = strlen(str);
        for (size_t i = 0; i < len / 2; i++) {
                char temp = *(str+i);
                *(str+i) = *(str + len - 1 - i);
                *(str + len - 1 - i) = temp;
        }
}

int main() {
        char* input = malloc(256);
        fscanf(stdin, "%s", input);
        reverse_string(input);
        printf("%s\n", input);
        return 0;
}
