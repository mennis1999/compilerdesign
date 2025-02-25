#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char prod[MAX][MAX], first[MAX][MAX], follow[MAX][MAX];
int n;

void findFirst(char c, int idx) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (!isupper(prod[i][2])) // If terminal, add directly
                first[idx][strlen(first[idx])] = prod[i][2];
            else // If non-terminal, recurse
                findFirst(prod[i][2], idx);
        }
    }
}

void findFollow(char c, int idx) {
    if (idx == 0) follow[idx][strlen(follow[idx])] = '$'; // Start symbol gets $

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0')
                    findFirst(prod[i][j + 1], idx);
                else if (prod[i][0] != c)
                    findFollow(prod[i][0], idx);
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (Format: A=α):\n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);

    for (int i = 0; i < n; i++) findFirst(prod[i][0], i);
    for (int i = 0; i < n; i++) findFollow(prod[i][0], i);

    printf("\nFIRST sets:\n");
    for (int i = 0; i < n; i++) printf("FIRST(%c) = { %s }\n", prod[i][0], first[i]);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < n; i++) printf("FOLLOW(%c) = { %s }\n", prod[i][0], follow[i]);

    return 0;
}
