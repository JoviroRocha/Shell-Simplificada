#include "meushell.h"

int main(){

    char data[100];
    printf("Configuring the shell...\n");
    config_read();
    printf("Done configuring!\n");
    while(1){
        printf("%s $ ",PRONTO);
        gets(data);
        printf("%s \n", data);
        system(data);
    };
    return 0;
}