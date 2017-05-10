# Manual de Usuario

## Resumen del Programa

El siguiente programa es un simulador del camino de datos de un procesador MIPS con forwarding, escrito en C, lee un programa con instrucciones MIPS y ejecuta las instrucciones del programa. El simulador imprime luego los valores de los registros y de los buffers del procesador en cada ciclo de este para que el usuario tenga un mayor entendimento de como este va funcionando.

## Ejecucion

El programa requiere ejecutarse a traves del terminal. Primero compilando el programa y luego ejecutandolo.

```sh
$  gcc main.c lib/registros.c lib/instrucciones.c lib/memoria.c lib/buffer.c -o lab2
$ ./lab2
```

A continuación se pedira ingresar el nombre del archivo donde se encuentra el progrma MIPS, en este caso utilizamos el archivo EjemploCode.asm y el programa nos mostrara luego nos confirmara el nombre del archi ingresado.

```sh
$ Inicio Programa
$ Escriba el nombre del archivo que contenga el Programa
$ NOTA: EL PROGRAMA DEBE ESTAR EN LENGUAJE MIPS
$ ejemploCode.asm
$ El archivo elegido es: ejemploCode.asm
```

Luego necesitaremos el archivo con los valores iniciales de los registros.

```sh
$ Escriba el nombre del archivo que contenga los valores de los registros
$ ejemploRegistros.txt
$ El archivo elegido es: ejemploRegistros.txt
```

a continuacion deberemos ingresar los nombres de los archivos de salida para los valores de los registros y los buffers a lo largo de los ciclos de reloj.

```sh
$ Archivo de salida
$ NOTA: Los ARCHIVOS DE SALIDA DEBEN TERMINAR EN .html
$ Escriba el nombre del archivo donde quiere que se muestre los registros
$ outRegistros.html
$ El archivo es: outRegistros.html
$ Escriba el nombre del archivo donde quiere que se muestre los buffers a traves de los ciclos
$ outBuffer.html
$ El archivo es: outBuffer.html
```

## Observaciones

* El programa no tiene contramedidas a errores del usuario, si alguno de los archivos no existe el programa fallara.



