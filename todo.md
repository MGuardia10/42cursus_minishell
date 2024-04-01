# todo list

## main

1. inicializar a 0 exit status - ✅
2. las caritas del main 🤬 😇  - ✅
3. mirar salto de linea cuando solo se pulsa enter - ✅
4. segfault con CTRL + D - ✅
5. codigo de error 1 cuando se pulsa CTRL + C - ✅
6. Añadir historial - PENDING
7. Revisar leaks que da valgrind si son del readline (creo que si) - PENDING

## señales
1. Eliminar que salga el capuchon ese + C, D , Q etc - ✅
2. Revisar las señales en MACs 42 (funcion rl_on_new_line) - PENDING

## parse

--> $$ y $noalpha
--> proteger malloc con exit

## Executer

1. en exit builtin llamar a clean_exit - ✅ (falta borrar el historial caundo se implemente).
2. si es string vacia salir status 0 - ✅
3. verificar que en pipes todos los fds quedan cerrados - ✅
4. borrar archivos temporales en cada exit o en cada iteracion del bucle - ✅
5. revisar builtins - ✅ (ok en principio pero probar mas casos cuando expander este ok)
6. Arreglar que el padre espere a todos los hijos no solo al ultimo - ✅
7. Revisar el heredoc (cunado expander ok) - PENDING
8. Revisar delimitador cuando es una variable expandida. - ✅
9. Revisar expander heredoc. - ✅
10. Revisar en caso de señal en heredoc que se elimine el archivo temporal - ✅

## Makefile

1. Ordenar makefile - ✅
2. En MACs de 42 asegurarnos que readline esta instalado y las variables correctamentes expandidas - PENDING

## libft

1. Arreglar makefile y hacerlo como el de minishell - ✅
2. Revisar ft_itoa no compila en linux - ✅
3. Actualizar libft personal en su repo - PENDING



## CASOS A SOLUCIONAR
### cd

cd "$PWD/file_tests" --> expande todo a NULL y solo deberia expandir PWD y lo demás quedarse igual
cd $PWD/file_tests   --> mismo problema pero sin comillas xd

## echo

echo  "$USER"tetext mguardia --> deberia poner "mguardiatetext mguardia" pero sale "mguardia tetext mguardia" esto es porque me pasas como argumentos distintos $USER expandido y tetext cuando deberian ser el mismo argumento pq no los separa el espacio.
echo $USER/home --> intenta expandir todo y solo deberia hasta la /
$EMPTY echo hi --> no expande a nada y echo es el comando, el primer comando se pasa como vacio
$EMPTY --> igual que antes, deberia de pasar al executer sin comandos y se pasa un comando vacio por lo que el exit status cambia

## export

export HELLO="123 A-" --> el problema es que llega HELLO como arg1 y "123 A-" como arg2. Parseo

## expander
expenv --> memoria completamente perdida en el caso del ft_itoa en expansion de $?
$PWD --> malloc: pointer being free was not allocated IMPORTANTE