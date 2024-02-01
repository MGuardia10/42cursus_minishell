# Funciones disponibles para minishell

# Contenidos

1. [Leer de la terminal e historial](#leer-de-la-terminal-e-historial)
2. [C clasics](#c-clasics)
3. [Manejo de procesos](#manejo-de-procesos)
4. [Manejo de directorios y archivos](#manejo-de-directorios-y-archivos)
5. [Manejo de errores](#manejo-de-errores)
6. [Manejo de terminal](#manejo-de-terminal)
# 
## Leer de la terminal e historial
- ### readline
Lee una línea de la entrada estándar.  
Parametros de entrada: prompt para indicar al usuario que debe ingresar información. OPCIONAL  
Parámetros de salida: Retorna la línea leída como una cadena.  
Cada vez que se utiliza la función readline() para leer una línea de entrada del usuario, esa línea se agrega automáticamente al historial. El usuario puede navegar por el historial de líneas utilizando las flechas arriba y abajo. 

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
# 
## C clasics
- ### printf 
- ### malloc 
- ### free 

## Manejo de procesos.
- ### fork 
Crea un nuevo proceso duplicando el proceso que realiza la llamada.  
El nuevo proceso se denomina proceso hijo.  
El proceso que realiza la llamada se denomina proceso padre.  
Parametros de salida: En caso de éxito, se devuelve el PID del proceso hijo en el padre, y se devuelve 0 en el hijo. En caso de fallo, se devuelve -1 en el padre y no se crea ningún proceso hijo.

- ### wait 
Cuando se llama a wait, el proceso padre se bloquea hasta que uno de sus procesos hijos finalice.  
Una vez que un proceso hijo finaliza, el proceso padre puede obtener información sobre el estado de finalización del proceso hijo, como su PID y el estado de salida.
- ### waitpid
La función waitpid es similar a wait, pero permite al proceso padre esperar a un proceso hijo específico en lugar de esperar a cualquier proceso hijo. 
- ### wait3, wait4
Proporcionan más opciones y detalles sobre el estado de finalización de los procesos hijos.
- ### signal
- ### sigaction 
- ### kill 
- ### exit 
# 
## Manejo de directorios y archivos
- ### getcwd 
Se utiliza para obtener el directorio de trabajo actual del proceso.
- ### chdir 
Se utiliza para cambiar el directorio de trabajo actual del proceso a la ruta especificada.
- ### stat, lstat, fstat
Estas funciones se utilizan para obtener información sobre un archivo.  
stat y lstat toman una ruta de archivo como argumento, mientras que fstat toma un descriptor de archivo. stat sigue los enlaces simbólicos, mientras que lstat devuelve información sobre el enlace simbólico en sí.
- ### unlink 
Para eliminar un archivo. Toma como argumento la ruta del archivo a eliminar.
- ### execve 
Se utiliza para ejecutar un nuevo programa en el espacio de memoria del proceso actual, reemplazando el programa actual. Toma como argumentos la ruta del nuevo programa, un array de argumentos y un array de variables de entorno.
- ### dup, dup2
Se utilizan para duplicar descriptores de archivo. dup crea una copia del descriptor de archivo en el descriptor de archivo más bajo disponible, mientras que dup2 copia el descriptor de archivo a un descriptor de archivo específico.
- ### pipe
Se utiliza para crear un canal de comunicación unidireccional entre procesos. Esta función crea dos descriptores de archivo, uno para leer del canal y otro para escribir en él.
- ### opendir 
Se utiliza para abrir un directorio para leer. Devuelve un puntero a una estructura DIR que se puede usar con otras funciones para leer el contenido del directorio.
- ### readdir 
Se utiliza para leer una entrada del directorio abierto con opendir. Devuelve un puntero a una estructura dirent que contiene información sobre la entrada del directorio.
- ### closedir 
Se utiliza para cerrar un directorio abierto con opendir.
# 
## Manejo de errores
- ### strerror 
Obtener una cadena que describe un código de error.
- ### perror
Imprimir un mensaje de error a stderr.
# 
## Manejo de terminal
- ### isatty 
Se utiliza para determinar si un descriptor de archivo se refiere a un terminal. Devuelve 1 si es así, y 0 en caso contrario.
- ### ttyname 
Se utiliza para obtener el nombre del terminal asociado con un descriptor de archivo. Devuelve una cadena que representa el nombre del terminal, o NULL si el descriptor de archivo no se refiere a un terminal.
- ### ttyslot 
Se utiliza para determinar el índice del terminal actual en el archivo de terminales del sistema.
- ### ioctl 
La función ioctl se utiliza para realizar operaciones de control de dispositivos en descriptores de archivo.
- ### getenv 
La función getenv se utiliza para obtener el valor de una variable de entorno. Toma como argumento el nombre de la variable de entorno y devuelve su valor como una cadena.
- ### tcsetattr
Se utiliza para cambiar los atributos de un terminal. Toma como argumentos un descriptor de archivo que se refiere a un terminal y una estructura termios que contiene los nuevos atributos.
- ### tcgetattr
Se utiliza para obtener los atributos actuales de un terminal. Toma como argumento un descriptor de archivo que se refiere a un terminal y llena una estructura termios con los atributos actuales.
- ### tgetent
Se utiliza para cargar una entrada de la base de datos de terminales.
- ### tgetflag
Se utiliza para obtener el valor de una capacidad booleana para el terminal actual.
- ### tgetnum
Se utiliza para obtener el valor de una capacidad numérica para el terminal actual.
- ### tgetstr
Se utiliza para obtener el valor de una capacidad de cadena para el terminal actual.
- ### tgoto
Se utiliza para mover el cursor a una posición específica en el terminal.
- ### tputs
Se utiliza para escribir una cadena en el terminal, con retrasos apropiados para las capacidades de padding del terminal. 