# Funciones disponibles para el proyecto

## <readline.h>

Cada vez que se utiliza la función readline() para leer una línea de entrada del usuario, esa línea se agrega automáticamente al historial. El usuario puede navegar por el historial de líneas utilizando las flechas arriba y abajo. 

- ### readline
Lee una línea de la entrada estándar.  
Parametros de entrada: prompt para indicar al usuario que debe ingresar información. OPCIONAL  
Parámetros de salida: Retorna la línea leída como una cadena.

- ### rl_clear_history
Permite limpiar todas las líneas almacenadas en el historial.

- ### rl_on_new_line
Se utiliza para indicar al sistema que se ha movido a una nueva línea vacía.  
Esto es útil para actualizar el estado interno del sistema de lectura de línea de comandos, ya que permite realizar tareas como la actualización del historial de comandos, etc.

- ### rl_replace_line 
Se utiliza para reemplazar el contenido actual de la línea de comandos con una nueva cadena de texto.  
Esta función se utiliza para actualizar la línea de comandos con nueva información, por ejemplo, cuando se desea mostrar información adicional al usuario mientras se ingresa un comando.

- ### rl_redisplay 
Para actualizar la línea de entrada mostrada en la pantalla.

- ### add_history
Permite agregar una línea al historial.  
Parametros de entrada: la linea a agregar al historial.

- ### printf 

- ### malloc 

- ### free 

- ### fork 
Crea un nuevo proceso duplicando el proceso que realiza la llamada.  
El nuevo proceso se denomina proceso hijo.  
El proceso que realiza la llamada se denomina proceso padre.  
Parametros de salida: En caso de éxito, se devuelve el PID del proceso hijo en el padre, y se devuelve 0 en el hijo. En caso de fallo, se devuelve -1 en el padre y no se crea ningún proceso hijo.

- ### wait 

- ### waitpid

- ### wait3 

- ### wait4 

- ### signal

- ### sigaction 

- ### kill 

- ### exit 

- ### getcwd 

- ### chdir 

- ### stat

- ### lstat 

- ### fstat 

- ### unlink 

- ### execve 

- ### dup 

- ### dup2 

- ### pipe

- ### opendir 

- ### readdir 

- ### closedir 

- ### strerror 

- ### perror

- ### isatty 

- ### ttyname 

- ### ttyslot 

- ### ioctl 

- ### getenv 

- ### tcsetattr

- ### tcgetattr

- ### tgetent

- ### tgetflag

- ### tgetnum

- ### tgetstr

- ### tgoto

- ### tputs