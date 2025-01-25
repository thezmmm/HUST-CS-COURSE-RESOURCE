#include <stdio.h>
#include <string.h>
char BNAME[] = { "myh" };
char BPASS[] = { "156308" };
char jieshu[] = { "q" };
char xiugai[] = { "m" };
extern char match;
extern unsigned int newbuf;
extern unsigned int a;
void Log() {
    match = 0;
    int count = 3;
    while (count--) {
        printf("Username:");
        char array_Log[20];
        scanf_s("%s", array_Log, 20);
        if (strcmp(array_Log, BNAME) == 0) {
            printf("Password:");
            memset(array_Log, 0, 20);
            scanf_s("%s", array_Log, 20);
            if (strcmp(array_Log, BPASS) == 0) {
                match = 1;
                printf("Successfully log in!Enter any key to continue!");
                getchar();
                getchar();
            }
            if (match == 1) break;
            printf("Error\n");
        }
        printf("Error\n");
    }

    return;
}
void printer(unsigned int newbuff) {
    printf("%08x\n", newbuff);

}
void selecter(void) {
    printf("Waiting\n");
    char array_Sel[20];
    scanf_s("%s", array_Sel, 20);
    if (strcmp(array_Sel, jieshu) == 0) {
        match = 1;
    }
    else if (strcmp(array_Sel, xiugai) == 0) {
        match = 2;
    }
    else { match = 0; }
    return;

}

unsigned int charu() {
    printf("\nInsert data:\n");
    a = 0;
    scanf_s("%u", &a, sizeof(a));
    return a;
}