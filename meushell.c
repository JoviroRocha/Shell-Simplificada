#include "meushell.h"

// USAREMOS O "which <comando>" para localizar?
// PRECISAMOS IMPLEMENTAR O "&&" para executar comandos diferentes -> and
// TBD: IMPLEMENTAR O CONFIG, A MUDANCA DE CONFIG, IMPLEMENTAR CD, LIMPA, SAIR, AJUDA E AMB, IMPLEMENTAR O HISTORICO, IMPLEMENTAR A LEITURA DE COMANDOS POR ARQUIVO
// USAREMOS /bin/ls /bin/pwd /bin/hostname

int main()
{
    char data[100];
    char *variables[1];
    char var_amb_arq[2][256];
    char variables_amb[2][256];

    // Configure Shell
    printf(COLOR_GREEN "Configuring the shell...\n" COLOR_RESET);
    config();
    printf(COLOR_GREEN "Done configuring!\n" COLOR_RESET);
    while (1)
    {
        // reseta as variáveis
        reset_variables(variables);
        // printa o PRONTO
        printf(COLOR_BLUE "%s $ " COLOR_RESET, PRONTO);
        // recebe o input
        scanf(" %[^\n]", data);
        // adiciona ao histórico
        add_history(data);
        //
        shell_functions(data, variables, var_amb_arq, variables_amb);
    };
    return 0;
}
