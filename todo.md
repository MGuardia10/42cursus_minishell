# todo list

## main
--> inicializar a 0 exit status OK
--> Revisar las señales
--> las caritas del main 🤬 😇 🖕 OK
--> mirar salto de linea cuando solo se pulsa enter OK
--> segfault con CTRL + D OK
--> codigo de error 1 cuando se pulsa CTRL + C OK

## parse
--> $$ y $noalpha OK
--> proteger malloc con exit OK
--> historial de comandos gestionar espacios, nulos, etc OK

## Executer
--> en exit builint lalmar a clean_exit OK
--> si es string vacia salir status 0 OK
--> verificar que en pipes todos los fds quedan cerrados
--> borrar archivos temporales en cada exit o en cada iteracion del bucle OK

## CASOS A SOLUCIONAR
### cd

cd "$PWD/file_tests" --> expande todo a NULL y solo deberia expandir PWD y lo demás quedarse igual OK
cd $PWD/file_tests   --> mismo problema pero sin comillas xd OK

## echo

echo  "$USER"tetext mguardia --> deberia poner "mguardiatetext mguardia" pero sale "mguardia tetext mguardia" esto es porque me pasas como argumentos distintos $USER expandido y tetext cuando deberian ser el mismo argumento pq no los separa el espacio. OK
echo $USER/home --> intenta expandir todo y solo deberia hasta la /
$EMPTY echo hi --> no expande a nada y echo es el comando, el primer comando se pasa como vacio OK
$EMPTY --> igual que antes, deberia de pasar al executer sin comandos y se pasa un comando vacio por lo que el exit status cambia OK

## export

export HELLO="123 A-" --> el problema es que llega HELLO como arg1 y "123 A-" como arg2. Parseo OK