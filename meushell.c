#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname 

int main(){

    char data[100];
    printf("Configuring the shell...\n");
    config_read();
    printf("Done configuring!\n");
    while(1){
        printf("%s $ ",PRONTO);
        scanf(" %[^\n]", data);
        char variaveis[100].split(" ");
        scanf(" %[^\n]", variaveis);
        if(strcmp(data , "ls") == 0){
            if( fork() == 0 ) execl("/bin/ls", "ls", variaveis,  NULL);
            wait(NULL);
        }
    };
    return 0;
}