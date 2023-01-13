#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// PRECISAMOS IMPLEMENTAR O "&&" para executar comandos diferentes -> and
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname 

int main(){
    // Configure Shell
    printf(ANSI_COLOR_GREEN "Configuring the shell...\n" ANSI_COLOR_RESET);
    config();
    printf(ANSI_COLOR_GREEN "Done configuring!\n" ANSI_COLOR_RESET);
    while(1){
        // reseta as variáveis
        reseta_variaveis();
        // printa o PRONTO
        printf(ANSI_COLOR_BLUE "%s $ " ANSI_COLOR_RESET, PRONTO);
        // recebe o input
        scanf(" %[^\n]", data);
        // parseia o input
        parser();
        // executa o input
        if( fork() == 0 ) execvp(path, variaveis);
        wait(NULL);
        
    };
    return 0;
}