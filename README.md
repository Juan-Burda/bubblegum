<p align="center">
  <img width="600" src="https://user-images.githubusercontent.com/70670549/236367508-8641017f-60b0-41ec-95d0-c227ba246882.png">
</p>

Un compilador construido a partir de https://github.com/agustin-golmar/Flex-Bison-Compiler.

## Requerimientos

Para la compilación del proyecto correr:
```bash
user@machine:path/ $ docker pull elianparedes/flex-bison:v1
```

Luego, pararse dentro de la carpeta del proyecto y correr el comando:
```bash
user@machine:path/ $ docker run -it -v ${PWD}:/root elianparedes/flex-bison:v1
```

## Construcción

Para construir el proyecto por completo, ejecute dentro del contenedor de Docker:

```bash
user@docker:path/ $ chmod u+x --recursive script
user@docker:path/ $ script/build.sh
```

## Testing

En Linux:

```bash
user@machine:path/ $ script/test.sh
```

En Windows:

```bash
user@machine:path/ $ script\test.bat
```
