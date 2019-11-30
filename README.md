# Joystick-motor
Codigo para control del joystick

Este código permite controlar un joystick con arduino.

Esta preparado para dar a la salida el  codigo correspondiente.

Funcionamiento:

  1º Captamos la señal analógica con dos pines ADC
  
  2º Cambiamos los ejes de referencia. Pasamos de los codigos de entrada [0, 1024] a [-512, 511]. Pero por seguridad lo pasamos a [-500, 500].
  
  3º Definimos una zona de no funcionamiento a modo de sensibilidad, de [0, 50] (si el joystick sufre un golpe el sistema no lo captaría y con esto también evitamos que el sistema funcione cuando el par de los motores no es suficiente para mover los motores)
  
  4º El funcionamiento del joystick es de coordenadas cuadradas, por lo que a cada punto le corresponde un cuadrado que le otorgará la distancia para el cálculo de la velocidad(la coordenada más grande en valor absoluto le otorga la distancia). Ahora sabiendo que el el motor va de [0, 255], el código 0 se correspondría con |50| del ADC y el 255 con el |500|. Entoces interpolamos para obtener el código de velocidad del motor:
         Código_velocidad=[((255-0)/(500-50))·(|Valor_ADC|)]+50
  
  5º 
