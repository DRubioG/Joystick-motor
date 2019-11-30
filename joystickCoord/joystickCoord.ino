#include <Math.h>

const int pinJoyX = A1;
const int pinJoyY = A0;
const int valor0x = 501;
const int valor0y = 521;
const int sen = 50;
//const int senN = -50;
const int x1 = 500;
const int x0 = 50;
const int y1 = 255;
const int y0 = 0;


float calcPend() { //valor constante de pendiente por si cambia el area de sensibilidad
  float m = 0;

  m = ((y1 - y0) / ((x1 - x0) * 1.0));
  return m;
}

int maxabs(int q, int w) {  //obtengo la coordenada de mayor valor, que es la que me da la mitad del lado con la que obtengo el codigo que va al motor
  int e = abs(q);
  int r = abs(w);
  return max(e, r);
}

int calCOD(float m, float radio) {  //me calcula el código que va al motor
  int codigo = 0;

  if (radio != 0) {
    codigo = m * (radio - x0) + y0;
  }
  return codigo;
}

float calcAng(int a, int b) {   //me calcula el angulo
  float angulo = 0;

  angulo = atan2(a , (b * 1.0)) * (180 / PI);
  return angulo;
}

int codigoMot(int cod, float ang) { //me da el codigo que va a cada motor
  int codI = 0, codD = 0;

  if ((ang < 90) && (ang > 0)) {        //primer cuadrante
    codI = cod;
    codD = (cod / 90.0) * ang;
  } else if ((ang > -90) && (ang < 0)) {  //cuarto cuadrante
    codI = -cod;
    codD = (cod / 90.0) * ang;
  } else if ((ang > 90) && (ang < 180)) { //segundo cuadrante
    codI = cod * ((ang / 90) - 2);
    codD = cod;
  } else if ((ang > -180) && (ang < -90)) { //cuarto cuadrante
    codI = -cod * ((ang / 90) + 2);
    codD = -cod;
  }
  Serial.print("Codigo motor Izdo -> ");
  Serial.println(codI);
  Serial.print("codigo motor Dcho -> ");
  Serial.println(codD);
}

void cuadrante(int a, int b) {    //me da el cuadrante
  if ((a > 0) && (b > 0)) {
    Serial.println("Primer cuadrante");
  }
  if ((a > 0) && (b < 0)) {
    Serial.println("Segundo cuadrante");
  }
  if ((a < 0) && (b < 0)) {
    Serial.println("tercer cuadrante");
  }
  if ((a < 0) && (b > 0)) {
    Serial.println("cuarto cuadrante");
  }
  if ((a == 0) && (b == 0)) {
    Serial.println("Centro");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Xvalue = 0;
  int Yvalue = 0;
  float radio = 0;
  float m = 0;
  int cod = 0;
  float angulo = 0;

  Xvalue = analogRead(pinJoyX); //obtengo el codigo del joystick
  delay(2);
  Yvalue = analogRead(pinJoyY);
  delay(2);
  int X = Xvalue - valor0x; //coloco el cero del joystick en X
  int Y = Yvalue - valor0y; //  ''    ''  ''  ''  ''  ''   Y
  Serial.print("X -> ");
  Serial.println(X);
  Serial.print("Y -> ");
  Serial.println(Y);

  if (X > 500) {    //coloco los limites de las medidas al cuadrado
    X = 500;
  }
  if (X < -500) {
    X = -500;
  }
  if (Y > 500) {
    Y = 500;
  }
  if (Y < -500) {
    Y = -500;
  }

  if ((maxabs(X, Y)) < sen) {   //coloco el area de sensibilidad
    X = 0;
    Y = 0;
  }


  radio = maxabs(X, Y);   //obtengo el radio
  //Serial.print("radio -> ");
  //Serial.println(radio);

  cuadrante(X, Y);    //obtengo el cuadrante

  angulo = calcAng(X, Y);   //calculo el angulo
  //Serial.print("angulo ->");
  //Serial.println(angulo);

  m = calcPend();     //calculo la pendiente, es un valor constante, no es necesario pero si cambias el valor no hace falta calcular la pendiente.

  cod = calCOD(m, radio);   //me da el codigo que va al motor(0-255)
  Serial.print("\t\t\t\tcodigo -> ");
  Serial.println(cod);

  codigoMot(cod , angulo);    //me asigna el codigo dependiendo del motor y el lugar al que va.

  delay(1000);


}
