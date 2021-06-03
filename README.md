# Bodega IoT

Este proyecto de IoT trata sobre una bodega que contiene leche y se debe mantener una temperatura ambiente para que no se dañe, tambien tiene otras funciones como detectar movimiento para abrir la puerta y enciender un led azul, al no detectar movimiento la puerta se cierra y se enciende el led rojo.

## Comenzando 🚀 

_instrucciones para obtener una copia del proyecto en funcionamiento en tu máquina local para propósitos de desarrollo y pruebas._

### Pre-requisitos 📋

_Esto es lo que necesitas para ejecutar el proyecto:_

_librerias_

```
- PubSubClient.h
- Arduino.h
- ESP8266WiFi.h
- Servo.h
- DHT.h
- ThingSpeak.h
- FirebaseESP8266.h
```

_Disponer del microcontrolador_

```
ESP8266
```

_Creas un proyecto en firebase_

```
Para crear una base de datos y almacenar la información.
```

_Creas un proyecto en ThingSpeak_

```
Para visualizar el flujo de los datos mediante gráficas.
```

_Creas una cuenta de Gmail para el proyecto, por temas de seguridad no es recomiendable usar una cuenta personal_

## Instalación 🔧 

_Este es el paso a paso de lo que debes configurar_

Red wifi

```
agregas el nombre de la red en la linea 27 y la contraseña en la linea 28
```

_Datos de firebase_

```
- Copias el secreto de la base de datos y lo pegas en la linea 41 #define FIREBASE_AUTH
- Copias el link disponible en realtime database y lo pegas en la linea 40 #define FIREBASE_HOST
```

## Ejecutando el programa ⚙️

_Luego de la conexion con el broker MQTT se visualiza el envio de datos hacia la base de datos._
_En la terminal se vera la entrada de los datos para confirmar el envio por el broker._
_En el topic general se envian todos los estados, que son, la temperatura y la puerta._
_despues verificaremos que los datos vistos en la consola se envien en la base de datos. Para esto entramos a Firebase en la seccion realtime database, sonde se cargara la informacion de humedad y temperatura._
_En seguida, verificaremos las graficas en ThingSpeak._
_Después comprobamos que se esten enviando los datos por los topics, para esto entramos al correo en el cual queremos que se envien los datos y en la consola alteramos el estado de la puerta haciendo una peticion._
_Finalmente revizamos el correo para comprobar la alteración en alguno de los topics_

## Mapeado de cables ⌨️ 

_Mapeado de cables_

<p align="center"><img src="https://pm1.narvii.com/6139/7e51d04dfe2d12c33ad3426656d7e8171277c1d3_hq.jpg"/></p>

```
ejemplo
```

## Construido con 🛠️

_herramientas utilizadas_

- [PubSubClient](https://www.arduinolibraries.info/libraries/pub-sub-client) - Una biblioteca de cliente para mensajería MQTT.
- [Servo](https://www.arduinolibraries.info/libraries/servo) - Permite que las placas Arduino controlen una variedad de servomotores.
- [DHT](https://www.arduinolibraries.info/libraries/dht-sensor-library) - Biblioteca arduino para DHT11, DHT22, etc Temp &Sensores de humedad.
- [ThingSpeak](https://www.arduinolibraries.info/libraries/thing-speak) - Es un servicio de plataforma de IoT analítico que permite agregar, visualizar y analizar flujos de datos en vivo en la nube.
- [FirebaseESP8266](https://www.arduinolibraries.info/libraries/firebase-esp8266-client) - Esta biblioteca de cliente proporciona las operaciones más confiables para leer, almacenar, actualizar, eliminar, hacer copias de seguridad y restaurar los datos de la base de datos Firebase realtime.

## Autores ✒️

_Este es el equipo que ayudaron a levantar el proyecto_

- **Diego Varela** - _Lider del proyecto_ - [Diego Varela](https://github.com/varelagrajales)
- **Alexander Blanco** - _Colaborador_ - [Alexander Blanco](https://github.com/BlancoAlex)
- **David Aponte** - _Colaborador_ - [David Aponte](https://github.com/Davidaponte98)
- **Vivian Padilla** - _Colaborador_ - [Vivian Padilla](https://github.com/VivianEstrada)

## Gracias por ver 🎁

- Comenta a otros sobre este proyecto 📢

---

Por [Bodega IoT](https://github.com/BlancoAlex/Proyecto-IOT) 😊
