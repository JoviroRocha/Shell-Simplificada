#include "meushell.h"

int main(){

    printf("Configuring the shell...\n");
    config_read();
    printf("Done configuring!\n");
    return 0;
}