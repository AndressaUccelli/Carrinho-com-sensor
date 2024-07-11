// Definindo pinos para o LED e a ponte H
const int ledPin = 2; // Pino do LED
const int motor1Pin1 = 7; 
const int motor1Pin2 = 8; 
const int enableA = 5; 
const int motor2Pin1 = 9; 
const int motor2Pin2 = 10; 
const int enableB = 6;

// Definindo pinos para o sensor ultrassônico
const int trigPin = 11;
const int echoPin = 12;

// Definindo limites de distância
const int distanceStop = 5; // em centímetros
const int distanceTurn = 10; // em centímetros

void setup() {
  // Configurando os pinos dos motores como saídas
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  // Configurando o pino do LED como saída
  pinMode(ledPin, OUTPUT);
  
  // Configurando os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializando a comunicação serial
  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();
  
  if (distance <= distanceStop) {
    stopMotors();
    digitalWrite(ledPin, HIGH); // Acende o LED
    delay(500);
    
    // Verificando a esquerda
    turnLeft();
    delay(500);
    int leftDistance = getDistance();
    stopMotors();
    delay(500);

    // Se a distância à esquerda for maior que 10cm, segue
    if (leftDistance > distanceTurn) {
      moveForward();
    } else {
      // Verificando a direita
      turnRight();
      delay(1000); // Tempo maior para virar completamente à direita
      int rightDistance = getDistance();
      stopMotors();
      delay(500);
      
      // Se a distância à direita for maior que 10cm, segue
      if (rightDistance > distanceTurn) {
        moveForward();
      } else {
        // Caso contrário, vira à direita
        turnRight();
        delay(500);
      }
    }
  } else {
    moveForward();
    digitalWrite(ledPin, LOW); // Desliga o LED
  }
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enableA, 255); 
  analogWrite(enableB, 255);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enableA, 0); 
  analogWrite(enableB, 0);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enableA, 255);
  analogWrite(enableB, 255);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enableA, 255);
  analogWrite(enableB, 255);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  return distance;
}
