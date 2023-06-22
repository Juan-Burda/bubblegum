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

# Playground

<p align="center">
  <img width="900" src="https://github.com/Juan-Burda/bubblegum/assets/70670549/44e18972-78cc-4349-8163-eba014479dc3">
</p>

[Bubblegum Playground](https://bubblegum-playground.vercel.app/) es un editor web que permite programar en Bubblegum y ver las animaciones generadas en tiempo real. Utiliza las herramientas de [Flex](https://github.com/westes/flex) y [Bison](https://www.gnu.org/software/bison/), pero compiladas en un módulo Javascript mediante [Emscripten](https://emscripten.org/)

El editor consiste en una aplicación web creada en [React](https://es.react.dev/) con [Next.js](https://nextjs.org/). Para consultar el código fuente, acceder a:

-   [Bubblegum Playground repository](https://github.com/elianparedes/bubblegum-playground)

## Desde C a Web Assembly

Para convertir el proyecto C en código que pueda ejecutarse en un navegador web, es recomendable utilizar la imagen provista por Emscripten, que contiene un entorno de desarrollo preparado para realizar dicho procedimiento.

```bash
user@machine:path/ $ docker pull emscripten/emsdk:latest
user@machine:path/ $ docker run -it -v ${PWD}:/root emscripten/emsdk:latest
```

Una vez dentro del contenedor, se deberá ejecutar la variante `web_env` de `build.sh`

```bash
user@machine:path/ $ ./script/build.sh web_env
```

Esto generará el modulo `Compiler.js` en el directorio `bin`.

## Configuración

Si se desease configurar un entorno como este desde cero, para poder generar el módulo Javascript, es necesario parametrizar correctamente la salida del compilador. Esto es realizado en el archivo `CMakeLists.txt`, dentro de la variante `WEB_ENV`.

```cmake
target_link_options(Compiler PUBLIC
		-O3 # Minifica el código, óptimo para producción. Ayuda a que este sea más rápido.
		-sMODULARIZE=1  # Lo compilará como un módulo, lo cual facilita la importación en proyectos
		-sEXPORT_NAME='createCompilerModule' # Nombre del constructor del módulo
		-sENVIRONMENT='web'
		-sSINGLE_FILE=1
		-sEXPORT_ES6=1 # Compatibilidad con ES6
		--no-entry # Indica que no posee un archivo de entrada, solo se expondrán funciones
		-sEXPORTED_FUNCTIONS=['_getCode','_malloc','_free','_freeCode'] # Las funciones que se podrán llamar desde Javascript
		-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','getValue','stringToNewUTF8','UTF8ToString'] # Funciones de la libreria de Emscripten
	)
```

Será necesario añadir la directiva `EMSCRIPTEN_KEEPALIVE` a las funciones que se desean exponer pero no se llaman desde un main.

```c
EMSCRIPTEN_KEEPALIVE
char *getCode(char *input) {
  ...
}
```

## Utilización

Dentro de un proyecto web, se deberá copiar el módulo `Compiler.js` y se lo debera importar dentro del archivo que se quiera utilizar. Notar que el módulo expone una función `createCompilerModule`, la cual construye el módulo y expone las funciones necesarias para, en este caso, realizar el parsing del lenguaje Bubblegum.

```javascript
import createCompilerModule from "../compiler/Compiler";

createCompilerModule().then((Module) => {
    setParse(() => wrapParse(Module));
});

function wrapParse(Module: any) {
    return function (code, callback): void {
        let codePtr = Module.stringToNewUTF8(code);

        let result = Module.ccall("getCode", "number", ["number"], [codePtr]);
        let parsedCode = Module.UTF8ToString(result);

        Module._free(result);
        Module._free(codePtr);

        callback(parsedCode);
    };
}
```

> Notar que es necesario liberar la memoria de los recursos utlizados.