#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }

    char *start = str;
    char *end = str + strlen(str) - 1;

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    char str[1024];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        reverse_string(str);
        printf("%s\n", str);
    }

    return 0;
}
