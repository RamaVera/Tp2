# Tp2
Sistemas Embebidos Tp N° 2


**1.b** Documentar mediante tablas c/texto e imágenes la secuencia de funciones invocadas durante la ejecución del ejemplo de aplicación, en qué archivo se encuentran, su descripción detallada, qué efecto tiene la aplicación sobre el hardware (identificar circuitos, puertos, pines, niveles, etc.) así como la interacción entre las mismas c. 


En la figura 1 se puede ver el contenido del archivo prefix.sct. Este contiene el diagrama de
estados del ejemplo “Blinky” que se utilizó en el Tp1. Este archivo prefix corresponde al que se
encuentra en la carpeta firmware_v2/projects/TP2/statecharts_bare_metal/gen, clonado de
/firmware_v2/sapi_examples/statecharts/statecharts_bare_metal/gen.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-1.PNG)

Para generar los archivos de código correspondientes al diagrama de estados, se hace click derecho
sobre el archivo prefix.sgen y se selecciona la opción “Generate Code Artifacts”. Este se puede ver
en la figura 2.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-2.PNG)

En la figura 3 se muestran los archivos que se generan con esta opción. Estos son Prefix.c, Prefix.h,
PrefixRequired.h y sc_types.h.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-3.PNG)

Estos archivos son usados por el archivo main.c que se encuentra en
firmware_v2/projects/TP2/statecharts_bare_metal/src. En la figura 4 se ve la inclusión del archivo
Prefix.h dentro del archivo main.c.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-4.PNG)

Dentro de este archivo se define una MACRO TEST y dependiendo de su valor se selecciona qué
ejemplo se va a ejecutar. Para este caso TEST = SCT_ 1, es decir que se va a ejecutar el ejemplo del
blinky, como se llega a ver en la figura 4. A continuación se analiza el main y su desarrollo,
haciendo uso del diagrama de estados creado con Yakindu.
En la figura 5 se puede ver el comienzo del main. Lo primero que se ve es la presencia de un
condicional para el compilador. “__USE_TIME_EVENTS” es una macro que se encuentra definida
más arriba en el main.c. Se puede ver en la figura 6.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-5.PNG)

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-6.PNG)

**La MACRO mencionada sirve para el uso de eventos del statechart, triggereados por el
cumplimiento de un timer. Es decir, que el diagrama de estados cambiaría de estado
automáticamente una vez que se cumpla un determinado tiempo. En este ejemplo uno
tendería a decir que debería estar en “true”, ya que una vez cumplido el tiempo seteado, el
LED se prende o se apagara, es decir, cambia de estado. Para ver porqué sucede esto, se
analizan las funciones utilizadas en el main.**

Lo siguiente que se hace en la figura 5 es configurar el tickrate y el tickcallbackset, es decir,
el tiempo de interrupción y la función que se invoca en esa interrupción. Esta función se encuentra
definida en el main y hace lo que se muestra en la figura 7.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-7.PNG)

La función solamente setea una variable, definida en el main.c, en true.
Continuando con la figura 5, se invoca a prefix_init y prefix enter. Ambas funciones reciben
la dirección de memoria de una variable “statechart”, definida en el main.c. Empezando por la
función “prefix_init”, esta puede verse en la figura 8.
Figura

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-8.PNG)

La variable “i” del tipo sc_integer es quivalente a una variable del tipo “int32_t”, simplemente las
llama de otra forma para saber que son internas del statechart. Luego hay un ciclo for, donde se
compara la variable “i” con una macro PREFIX_MAX_ORTHOGONAL_STATES, que se
encuentra definida en Prefix.h y para este caso vale 1. Estos Orthogonal States, según la
documentación de Yakindu, son:

                An orthogonal state is basically a composite state with more than one region.
                These regions are executed virtually concurrently. Please note the word virtually!
                YAKINDU Statechart Tools does not guarantee in any way that orthogonal regions
                are really executed concurrently. At the moment, no code generator utilizes threads
                to achieve this. Orthogonal states should rather be understood as a manner to have
                two or more sub-statecharts working together, however, they are executed one after
                the other in every cycle, and in a defined order: top to bottom, left to right. The
                same applies to multiple regions in the statechart itself. Please consult section
                "Raising and processing an event" for further information on region priorities and
                their meanings for the statechart execution.
                
                
![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-9.PNG)

Como se hace una iteración sola, se accede al parámetro stateConfVector[1] (este es un elemento de
la variable handle del tipo Prefix), que es un vector de tamaño
PREFIX_MAX_ORTHOGONAL_STATES (en este caso 1) y se le asigna el valor Prefix_last_state.
Esto lo que quiere decir es que en este paso se setean todos los Orthogonal States en el estado
inicial que corresponde al punto negro de la figura 1. En este caso hay uno solo, así que solo se
setea este. Luego se setea el parámetro stateConfVectorPosition en 0. Por útlimo se invoca a
“prefix_clearInevents” pasándole como parámetro el mismo “handle”. Esta, como se muestra en la
figura 10, accede al elemento “iface”, que a su vez es otra estructura del tipo “PrefixIface”, que
solamente contiene un elemento del tipo “sc_boolean” que puede valer true o false. En esta función
se la está seteando en”false”. La función “prefix_clearOutEvents” en este caso no cumple ninguna
función.
Continuando con el main, se analiza la función “prefix_enter”, que también recibe la
dirección de memoria del statechart. El objetivo de esta función es entrar a un estado que no sea el
estado inicial, dentro del statechart. La función se puede ver en la figura 11,

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-10.PNG)

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-11.PNG)

la cual a su vez invoca a otra función “prefix_enseq_main_region_default”que recibe el parámetro
“handle”. Esta función corresponde a la secuencia de entrada por defecto, al statechart. Dentro de
esta a su vez llama a otra función “prefix_react_main_region__entry_Default” que también recibe
la función “handle”. El trabajo de esta es realizar el evento de entrar al primer estado, el cual, según
la figura 1, correspondería con tener el LED apagado. Es entonces que esta función invoca a una
última función más “prefix_enseq_main_region_APAGADO_default” que también recibe el
parámetro handle, cuyo objetivo es entrar al estado apagado. Esta se puede ver en la figura 12. A
continuación se analiza las funciones invocadas.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-12.PNG)

Primero se llama a una función “prefix_enact_main_region_APAGADO” que recibe el handler.
Esta se puede ver en la figura 13 y lo que hace es realizar la acción correspondiente al estado
“APAGADO”, es decir, invoca a la función que apaga el LED.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-13.PNG)

Continuando con la función “prefix_enseq_main_region_APAGADO_default”, esta setea el estado
del “stateConfVector” en “Prefix_main_region_APAGADO”, lo cual indica que ahora el statechart
se encuentra en el estado “APAGADO” (recordar que el vector stateConfVector contiene un
elemento por cada Orthogonal State, en este caso el vector stateConfVector tiene un solo elemento
ya que solo se tiene un Orthogonal State). Por último se setea el valor del elemento
“stateConfVectorPosition” en 0. Cabe aclarar que la función “prefixIface_opLED” se encuentra
declarada en el archivo “PrefixRequired.h”, archivo que se generó automáticamente por el Yakindu.
Las declaraciones en esta función me piden que las defina en otro archivo, manualmente.
Con el análisis realizado, puede analizarse el funcionamiento general del main. Como se ve
en la figura 14, luego de las funciones descriptas se entra en un while(1).

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-14.PNG)

Respecto a la función “__WFI()”, según la documentación de esta, corresponde a una función que
suspende la ejecución del main hasta que encuentre una interrupción. En este programa la
interrupción correspondería al caso del “Tick”. Cuando se cumple el tiempo seteado para la
interrupción del Tick, se invoca a “myTickHook”, que como ya se dijo, setea una variable en true.
Luego el main detecta que esto sucedió y entra en el if. Vuelve a setear la variable en false y llama a
dos funciones: “prefixIface_raise_evTick” y a “prefix_runCycle”. La primera se ve en la figura 14 bis y
su objetivo es indicarle al statechart que se ejecutó el evento evTick.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-14bis.PNG)

Se modifica el elemento “iface” del handle, accediendo al evento “evTick_raised” indicándole que
se activó. Por último se invoca a la función “prefix_runCycle”. Esta se puede ver en la figura 15.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-15.PNG)

Primero se invoca a “prefix_clearOutEvents” que como ya se dijo en este caso no hace nada. Luego
el ciclo for se repite una cantidad de veces igual a la cantidad de Orthogonal States que se tienen,
que en este caso es 1. Lo que se hace dentro del ciclo es setear el elemento
“stateConfVectorPosition” e incrementarlo en 1 en cada iteración. Dentro del ciclo hay un switch.
La variable a evaluar es la posición “stateConfVectorPosition” (que ahora vale 0) del vector
“stateConfVector”. Se refiere a que se va a trabajar en el único Orthogonal State que se tiene en este
ejemplo. Como se había hecho antes, la variable que corresponde a la posición 0 del vector
“stateConfVector” tiene el valor “Prefix_main_region_APAGADO”, entonces se entra al case
correspondiente y se invoca a la función “prefix_react_main_region_APAGADO”. La función esta
se puede ver en la figura 16.

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1b-16.PNG)

La función “prefix_check_main_region_APAGADO_tr0_tr0” simplemente chequea el elemento
“evTickraised” del elemento “iface” de la estructura “handle” para ver si es true, lo cual quiere decir
que sucedió el evento que triggerea el cambio de estado. En este caso esto es cierto, ya que se hizo
previamente con la función de la figura 14. Luego se ejecuta
“prefix_effect_main_region_APAGADO_tr0” la cual ejecuta la reacción, es decir, el cambio de
estado. Dentro de esta se ejecuta la función “prefix_exseq_main_region_APAGADO”, función que
solamente deja el stateConfVector[0] en el estado inicial del puntito negro y deja el contador
stateConfVectorPosition = 0. Por último se ejecuta la secuencia de entrada al estado
“ENCENDIDO” con la función “prefix_enseq_main_region_ENCENDIDO” que solamente ejecuta
la acción de encender el LED y setear el “stateConfVector[0] en el estado “ENCENDIDO”. Esta
última función “prefix_enseq_main_region_ENCENDIDO” es de la misma forma que la función de
la figura 12, pero para el estado ENCENDIDO.
Volviendo a la figura 15, al final de dicha función se ejecuta “prefix_clearInEvents”, función
que se analizó en la figura 10 y solo le dice al statechart que el evento que triggerea el cambio de
estados no está sucediendo.

**Al principio se dijo que se estaba utilizando un evento por cumplimiento de un timer y
que por esto, la MACRO “__USE_TIME_EVENTS” debería estar en “true” pero se
encuentra en “false”. Entonces, a partir de lo visto hasta acá, sucede que, cuando se cumple el
timer y se invoca a la interrupción de Ticks, se está levantando un flag, el cual luego es
analizado en el main. Es decir, no se hace el cambio de estado por un timer si no por el valor
del flag, si es “true” o “false”.**


**1.c** Idem b pero con datos (definiciones, constantes, variables, estructuras, etc

En primer lugar, se analizarán los tipos de datos de las funciones y constantes declaradas en el archivo
firmware_v2\sapi_examples\edu-ciaa-nxp\statecharts\statecharts_bare_metal\gen\Prefix.c

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1c-1.PNG)

En el archivo
firmware_v2\sapi_examples\edu-ciaa-nxp\statecharts\statecharts_bare_metal\gen\Prefix.h
se encuentra definido “Prefix” como la siguiente estructura:

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1c-2.PNG)

Donde “PrefixStates” es un enum con los distintos posibles estados de la región:
```
typedefenum
{
	Prefix_main_region_APAGADO,
	Prefix_main_region_ENCENDIDO,
	Prefix_last_state
} PrefixStates;
```

Y “PrefixIface” es una estructura con un booleano:

```
typedefstruct
{
	sc_booleanevTick_raised;
} PrefixIface;
```

La variable stateConfVectorPosition es un int para guardar la posición del vector.
Estos tres datos son los que reciben las funciones declaradas y los que se manipulan dentro de las mismas, por ejemplo, para ir cambiando de estado.
A continuación, se analizarán los tipos de datos de las funciones y constantes declaradas en el archivo
/firmware_v2/sapi_examples/edu-ciaa-nxp/statecharts/statecharts_bare_metal/src/main.c
Al principio del archivo se definen las opciones de compilación y se selecciona qué ejemplo se quiere ejecutar

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1c-3.PNG)

Luego se define un flag de tipo volátil, una variable de tipo Prefix (ya explicada), el uso de los TIME_EVENTS y una variable de tipo TimerTicks, que es una estructura que se encuentra declarada en /firmware_v2/examples/statechart/inc/TimerTicks.h

![alt text](https://github.com/RamaVera/Tp2/blob/master/img/1c-4.PNG)

```
typedefstruct
{
	sc_eventidevid;
	sc_uintegertime_ms;
	sc_uintegercount;
	sc_booleanperiodic;
	sc_booleanactive;
	sc_booleanevPending;
} TimerTicks;
```

El resto del programa (cuya secuencia de funciones está explicada en otro documento) usa principalmente los datos nombrados anteriormente.









<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE4MzE4NzkzMDQsMTE0ODk4NDg2OF19
-->
