#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int bss = 0;

int main(int argc, char** argv) {

        int localvar;
        int localvar2;
        int* heap = NULL;
        pid_t pid = getpid();

        printf("BSS is at %.16llx\n", &bss);

        heap = (int*) malloc(sizeof(int));
        printf("heap is at %.16llx\n", heap);

        printf("stack is at %.16llx\n", &localvar);
        printf("stack2 is at %.16llx\n", &localvar2);

        return 0;
}
