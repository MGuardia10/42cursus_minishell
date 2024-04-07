# todo list

## main

1. inicializar a 0 exit status - ✅
2. las caritas del main 🤬 😇  - ✅
3. mirar salto de linea cuando solo se pulsa enter - ✅
4. segfault con CTRL + D - ✅
5. codigo de error 1 cuando se pulsa CTRL + C - ✅
6. Añadir historial - ✅
7. Revisar leaks que da valgrind si son del readline (creo que si) - ✅
8. Acabar el README.md - ✅
9. Variables de entorno caso en el que se llame con env -i - ✅
10. Revisar print export variable duplicada la ultima - ✅

## señales
1. Eliminar que salga el capuchon ese + C, D , Q etc - ✅
2. Revisar las señales en MACs 42 (funcion rl_on_new_line) - ✅

## parse
--> $$ y $noalpha - ✅
--> proteger malloc con exit - ✅
--> historial de comandos gestionar espacios, nulos, etc - ✅
--> echo "|" - ✅

## Executer

1. en exit builtin llamar a clean_exit - ✅ (falta borrar el historial caundo se implemente).
2. si es string vacia salir status 0 - ✅
3. verificar que en pipes todos los fds quedan cerrados - ✅
4. borrar archivos temporales en cada exit o en cada iteracion del bucle - ✅
5. revisar builtins - ✅ (ok en principio pero probar mas casos cuando expander este ok)
6. Arreglar que el padre espere a todos los hijos no solo al ultimo - ✅
7. Revisar el heredoc - ✅
9. Revisar expander heredoc. - ✅
10. Revisar en caso de señal en heredoc que se elimine el archivo temporal - ✅
11. Revisar argumentos multiples en el exit - ✅

## Makefile

1. Ordenar makefile - ✅
2. En MACs de 42 que compile: NO hay que exportar las variables - ✅

## libft

1. Arreglar makefile - ✅
2. Revisar ft_itoa no compila en linux - ✅
3. Actualizar libft personal en su repo - ✅

## CASOS A SOLUCIONAR
# PARSEO
Quitar funcion comentada en init.c - ✅

# EXPANDER RAUL

										lo que hace					lo que deberia

/bin/echo $"42$"						-> 42						-> 42$ ✅		
/bin/echo "$ "							->							-> $ ✅
/bin/echo "$?"							->							-> 0 ✅
/bin/echo "'$?'"						-> ''						-> '0' ✅
/bin/echo $USER$TESTNOTFOUND$HOME$		-> te saca de la shell xd	-> mguardia/Users/mguardia$ ✅
/bin/echo '"'$USER'"' 					-> "mguardia 				-> "mguardia" ✅
/bin/echo "'"'$USER'"'"					-> '$USER					-> '$USER' ✅
/bin/echo '"'"$USER"'"'					-> "mguardia				-> "mguardia" ✅
/bin/echo text"'$USER'" ' $USER '		-> textmguardia  $USER		-> text'mguardia'  $USER ✅
/bin/echo ""'""""""$USER""""""'""		-> $USER					-> """"""$USER"""""" ✅
/bin/echo """""""'"$USER"'"""""""		-> mguardia					-> 'mguardia' ✅
/bin/echo """"""'""$USER""'""""""		-> $USER					-> ""$USER"" ✅
/bin/echo ""'""'""""$USER""""'""'""		-> mguardia					-> ""mguardia"" ✅
/bin/echo '""'""'""""$USER""""'""'""'	-> ""$USER					-> """"""$USER"""""" ✅
