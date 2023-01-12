#include <stdio.h>
#include <stdlib.h>

char HOST[30];
char PRONTO[30];
char SHELL[30];

void config_read(){
    FILE *config_file = fopen(".meushell.rec","r");
    if(!config_file){
        printf("ERROR: The file \".meushell.rec\" could not be found! \n");
        exit(0);
    }
    fscanf(config_file, "HOST=%s PRONTO=%s SHELL=%s", HOST, PRONTO, SHELL);
    return;
}