#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char HOST[30];
char PRONTO[30];
char SHELL[30];

void config(){
    // bin/<nome>
    // PEGAR O HOSTNAME [$ hostanme] e colocar em host
    // COLOCAR UM ID EM SHELL -> A DEFINIR
    // COLOCAR UM VALOR EM PRONTO REFERENTE AO DIRETÓRIO ATUAL -> pwd
}

void config_read(){
    FILE *config_file = fopen(".meushell.rec","r");
    if(!config_file){
        printf("ERROR: The file \".meushell.rec\" could not be found! \n");
        exit(0);
    }
    fscanf(config_file, "HOST=\"%s PRONTO=\"%s SHELL=\"%s", HOST, PRONTO, SHELL);
    return;
}