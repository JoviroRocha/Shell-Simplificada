all:
  echo Executando o programa!
  programa.exe

programa.exe:
  echo Compilando o programa
  gcc -o programa.exe meuCodigo.c
