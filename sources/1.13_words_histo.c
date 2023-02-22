#include <stdio.h>
#define MAXWORDS 1000

int main() {
    char c;
    int i, j, lengths[MAXWORDS];
    for (i=0; i < MAXWORDS; i++) lengths[i]=0;
    i=0;
    
    while ((c=getchar()) != EOF) {
        if (c != ' ' || c != '\t' || c != '\n')
            ++lengths[i];
        else ++i;
    }

    printf("Building histo:\n");
    for (i=0; i < MAXWORDS; i++) {
        if (lengths[i] > 0) {
            for (j=0; j < lengths[i]; j++) putchar('+');
            putchar('\n');
        }
    }
}

