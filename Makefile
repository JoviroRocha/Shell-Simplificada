all: compile_message programa.exe ; @echo "Executando o programa!" ; ./programa.exe
programa.exe: meushell.c ; gcc -o programa.exe meushell.c
compile_message: ; @echo "Compilando o programa!"