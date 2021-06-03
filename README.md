# Bodega IoT

Este proyecto de IoT trata sobre una bodega que contiene leche y se debe mantener una temperatura ambiente para que no se dañe, tambien tiene otras funciones como detectar movimiento para abrir la puerta y enciender un led azul, al no detectar movimiento la puerta se cierra y se enciende el led rojo.

## Comenzando 🚀 

Si desea realizar una descarga del proyecto y obtener nuevos conocimientos ingresa en boton verde que dice code, luego saldra una lista 
desplegable con el link del proyecto asu vez las opciones de:

-open with Github desktop 
-Download ZIP.

### Pre-requisitos 📋

_Esto es lo que necesitas para ejecutar el proyecto:_

librerias

```
- PubSubClient.h
- Arduino.h
- ESP8266WiFi.h
- Servo.h
- DHT.h
- ThingSpeak.h
- FirebaseESP8266.h
```

- Disponer del microcontrolador

ESP8266

- Creas un proyecto en firebase

Para crear una base de datos y almacenar la información.

- Creas un proyecto en ThingSpeak

Para visualizar el flujo de los datos mediante gráficas.

- Creas una cuenta de Gmail para el proyecto, por temas de seguridad no es recomiendable usar una cuenta personal

## Instalación 🔧 

para poder tener el desarrollo del proyecto se debe de tene en cuenta la instalacion del software arduino ya que alli fue donde se configuro generalmente todo el proyecto.

Luego de tener los anteriores pasos pertinentes, se continua con descomprimido el archivo que decargo en el primer paso.

Red wifi
- agregas el nombre de la red en la linea 27 y la contraseña en la linea 28

Datos de firebase
- Copias el secreto de la base de datos y lo pegas en la linea 41 #define FIREBASE_AUTH
- Copias el link disponible en realtime database y lo pegas en la linea 40 #define FIREBASE_HOST

## Ejecutando el programa ⚙️

- Luego de la conexion con el broker MQTT se visualiza el envio de datos hacia la base de datos.
- En la terminal se vera la entrada de los datos para confirmar el envio por el broker.
- En el topic general se envian todos los estados, que son, la temperatura y la puerta.
- despues verificaremos que los datos vistos en la consola se envien en la base de datos. Para esto entramos a Firebase en la seccion realtime database, sonde se cargara la informacion de humedad y temperatura.
- En seguida, verificaremos las graficas en ThingSpeak.
- Después comprobamos que se esten enviando los datos por los topics, para esto entramos al correo en el cual queremos que se envien los datos y en la consola alteramos el estado de la puerta haciendo una peticion.
- Finalmente revizamos el correo para comprobar la alteración en alguno de los topics

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
