# Comando de git para trabajar con ramas

1. Procedimientos basicos para trabajar con ramas: https://git-scm.com/book/es/v2/Ramificaciones-en-Git-Procedimientos-B%C3%A1sicos-para-Ramificar-y-Fusionar
2. Ramificaciones en git y gestion de ramas: https://git-scm.com/book/es/v2/Ramificaciones-en-Git-Gesti%C3%B3n-de-Ramas
3. Lista de todos los comandos y guías: https://git-scm.com/docs
4. Libro completo de git: https://git-scm.com/book/en/v2

## Crear una rama y movernos directamente a ella:
```
git checkout -b <nombre_rama>

sería lo mismo que hacer:
	1. git branch <nombre_rama>		// Crea la nueva rama
	2. git checkout <nombre_rama>	// Te mueve a la nueva rama
```


## Borrar una rama una vez ya esta mergeada
```
git branch -d <nombre_rama>

La flag -d es de --delete, borra la rama que le especifiquemos una vez este mergeada. También existe la flag -D, tambien de --DELETE, que borra la rama aun sin haber sido mergeada, asique cuidado xd

```

## Ver listado de ramas
```
git branch -l

La flag -l es de --list, lista todas las ramas de nuestro repo.
```

## Ver la rama en la que estamos y el hash + mensaje del ultimo commit
```
git branch -v
```

## Ver listado de ramas que estan / no estan mergeadas
```
git branch --merged
git branch --no-merged
```
## Unir la rama con la rama master/main
```
git checkout master/main
git merge <nombre_rama>

Lo que hace cada comando:
	1. git checkout <nombre_rama>	// Nos movemos a la rama main/master
	2. git merge <nombre_rama>		// Añade la rama al main/master
```

Puede pasar que haya conflictos entre la rama main y la rama que queremos mergear. Si no hay problemas git hará un "fast-forward" lo cual significa que todo se integró bien. En el caso contrario, git entrará en una especie de modo pausa, esperando que resolvamos los conflictos. En visual creo que te sale visualmente donde hay conflictos y con corregirlos y guardar el archivo vale. Pero si estas desde la terminal puedes hacer `git status` para ver donde estan los conflictos.

También existe una herramienta grafica de git que te permite ir resolviendo conflictos de manera mas visual. el comando es `git mergetool`, no lo he usado nunca asique no se decirte como es.