#define semaforo1_verde  10
#define semaforo1_rojo   11
#define semaforo2_verde  9
#define semaforo2_rojo   13
#define semaforo3_verde  8
#define semaforo3_rojo   12
#define interruptor      2

void setup() {
  // Configuramos los pines como salidas para los semáforos
  int semaforos[] = {semaforo1_verde, semaforo1_rojo, semaforo2_verde, semaforo2_rojo, semaforo3_verde, semaforo3_rojo};
  for (int i = 0; i < 6; i++) {
    pinMode(semaforos[i], OUTPUT);
  }
  // Configuramos el pin del interruptor
  pinMode(interruptor, INPUT);
  
  Serial.begin(9600);  // Iniciar comunicación serie para monitor
}

void setSemaforo(int verde, int rojo, bool estadoVerde, bool estadoRojo) {
  digitalWrite(verde, estadoVerde ? HIGH : LOW);
  digitalWrite(rojo, estadoRojo ? HIGH : LOW);
}

// Función para hacer parpadear los LEDs en amarillo intermitente
void parpadearAmarillo() {
  for (int i = 0; i < 3; i++) {
    setSemaforo(semaforo1_verde, semaforo1_rojo, true, true); // Amarillo (ambos encendidos)
    setSemaforo(semaforo2_verde, semaforo2_rojo, true, true);
    setSemaforo(semaforo3_verde, semaforo3_rojo, true, true);
    delay(500);  // Encendido por 500 ms
    setSemaforo(semaforo1_verde, semaforo1_rojo, false, false); // Apagar
    setSemaforo(semaforo2_verde, semaforo2_rojo, false, false);
    setSemaforo(semaforo3_verde, semaforo3_rojo, false, false);
    delay(500);  // Apagado por 500 ms
  }
}

void loop() {
  // Leer el estado del interruptor
  bool inter = digitalRead(interruptor);

  if (inter == LOW) {
    // Si el interruptor está apagado, parpadear en amarillo
    Serial.println("SEMAFOROS EN AMARILLO INTERMITENTE");
    parpadearAmarillo();
  } else {
    // Si el interruptor está encendido, ciclo normal de semáforos
    for (int i = 0; i < 3; i++) {
      switch(i) {
        case 0: 
          // Semáforo 1 verde, semáforo 2 y 3 rojo
          setSemaforo(semaforo1_verde, semaforo1_rojo, true, false);  // Verde encendido
          setSemaforo(semaforo2_verde, semaforo2_rojo, false, true);  // Rojo encendido
          setSemaforo(semaforo3_verde, semaforo3_rojo, false, true);  // Rojo encendido
          Serial.println("Semáforo 1: VERDE, Semáforo 2 y 3: ROJO");
          break;
        case 1:
          // Semáforo 2 verde, semáforo 1 y 3 rojo
          setSemaforo(semaforo1_verde, semaforo1_rojo, false, true);  // Rojo encendido
          setSemaforo(semaforo2_verde, semaforo2_rojo, true, false);  // Verde encendido
          setSemaforo(semaforo3_verde, semaforo3_rojo, false, true);  // Rojo encendido
          Serial.println("Semáforo 2: VERDE, Semáforo 1 y 3: ROJO");
          break;
        case 2:
          // Semáforo 3 verde, semáforo 1 y 2 rojo
          setSemaforo(semaforo1_verde, semaforo1_rojo, false, true);  // Rojo encendido
          setSemaforo(semaforo2_verde, semaforo2_rojo, false, true);  // Rojo encendido
          setSemaforo(semaforo3_verde, semaforo3_rojo, true, false);  // Verde encendido
          Serial.println("Semáforo 3: VERDE, Semáforo 1 y 2: ROJO");
          break;
      }
      delay(1000);  // Mantener el estado durante 1 segundo
    }
  }
}

