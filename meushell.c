#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// PRECISAMOS IMPLEMENTAR O "&&" para executar comandos diferentes -> and
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname 

int main(){

    printf("Configuring the shell...\n");
    config_read();
    printf("Done configuring!\n");
    while(1){
        // reseta as variáveis
        reseta_variaveis(variaveis);
        // printa o PRONTO
        printf("%s $ ",PRONTO);
        // recebe o input
        scanf(" %[^\n]", data);
        // parseia o input
        char * token = strtok(data, " ");
        loop = 0;
        while(token != NULL){
            variaveis[loop++] = token;
            token = strtok (NULL, " ");
        }
        strcpy(path, "/bin/");
        strcat(path, variaveis[0]);
        // executa o input
        if( fork() == 0 ) execl(path, variaveis[0], variaveis[1],variaveis[2], variaveis[3], variaveis[4],  NULL);
        wait(NULL);
        
    };
    return 0;
}