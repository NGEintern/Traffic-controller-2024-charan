// Define the pins for each LED
const int A_Red = 14;
const int A_Green = 12;
const int A_Amber = 13;

const int B_Red = 27;
const int B_Green = 26;
const int B_Amber = 25;

const int C_Red = 33;
const int C_Green = 32;
const int C_Amber = 35;

const int D_Red = 22;
const int D_Green = 21;
const int D_Amber = 19;

// Timing constants
int GreenTimeA = 60000;  // Green light time for Route A in milliseconds (60 seconds)
int GreenTimeB = 60000;  // Green light time for Route B in milliseconds (40 seconds)
int GreenTimeC = 60000;  // Green light time for Route C in milliseconds (55 seconds)
int GreenTimeD = 60000;  // Green light time for Route D in milliseconds (10 seconds)
const int AmberTime = 5000;  // Amber light blink time in milliseconds (5 seconds)

// Function to set green light times
void setGreenTimes(int timeA, int timeB, int timeC, int timeD) {
  GreenTimeA = timeA * 1000;  // Convert seconds to milliseconds
  GreenTimeB = timeB * 1000;  // Convert seconds to milliseconds
  GreenTimeC = timeC * 1000;  // Convert seconds to milliseconds
  GreenTimeD = timeD * 1000;  // Convert seconds to milliseconds
}

void setup() {
  // Initialize the LED pins as outputs
  pinMode(A_Red, OUTPUT);
  pinMode(A_Green, OUTPUT);
  pinMode(A_Amber, OUTPUT);

  pinMode(B_Red, OUTPUT);
  pinMode(B_Green, OUTPUT);
  pinMode(B_Amber, OUTPUT);

  pinMode(C_Red, OUTPUT);
  pinMode(C_Green, OUTPUT);
  pinMode(C_Amber, OUTPUT);

  pinMode(D_Red, OUTPUT);
  pinMode(D_Green, OUTPUT);
  pinMode(D_Amber, OUTPUT);

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Set initial green light times
  setGreenTimes(60, 60, 60, 60);
}

void printLightTimes(int remainingGreenTime, int remainingRedTimeB, int remainingRedTimeC, int remainingRedTimeD) {
  Serial.print("Route A: Green (");
  Serial.print(remainingGreenTime);
  Serial.print("s), Route B: Red (");
  Serial.print(remainingRedTimeB);
  Serial.print("s), Route C: Red (");
  Serial.print(remainingRedTimeC);
  Serial.print("s), Route D: Red (");
  Serial.print(remainingRedTimeD);
  Serial.println("s)");
}

void printAmberLightTimes(int route, int amberTime) {
  Serial.print("Route ");
  if (route == A_Amber) {
    Serial.print("A");
  } else if (route == B_Amber) {
    Serial.print("B");
  } else if (route == C_Amber) {
    Serial.print("C");
  } else if (route == D_Amber) {
    Serial.print("D");
  }
  Serial.print(": Amber (");
  Serial.print(amberTime);
  Serial.println("s)");
}

void loop() {
  // Route A Green, Route B, C, D Red
  digitalWrite(A_Green, HIGH);
  digitalWrite(A_Amber, LOW);
  digitalWrite(A_Red, LOW);

  digitalWrite(B_Red, HIGH);
  digitalWrite(B_Green, LOW);
  digitalWrite(B_Amber, LOW);

  digitalWrite(C_Red, HIGH);
  digitalWrite(C_Green, LOW);
  digitalWrite(C_Amber, LOW);

  digitalWrite(D_Red, HIGH);
  digitalWrite(D_Green, LOW);
  digitalWrite(D_Amber, LOW);

  for (int i = GreenTimeA / 1000; i > 0; i--) {
    if (i <= 5) {
      digitalWrite(A_Green, LOW);
      digitalWrite(A_Amber, HIGH);
      printAmberLightTimes(A_Amber, i);
    } else {
      digitalWrite(A_Green, HIGH);
      digitalWrite(A_Amber, LOW);
    }
    printLightTimes(i, i , i + (GreenTimeB / 1000), i + (GreenTimeB / 1000) + (GreenTimeC / 1000));
    delay(1000);
  }

  // Route A Red, Route B Green
  digitalWrite(A_Green, LOW);
  digitalWrite(A_Amber, LOW);
  digitalWrite(A_Red, HIGH);

  digitalWrite(B_Red, LOW);
  digitalWrite(B_Green, HIGH);
  digitalWrite(B_Amber, LOW);

  for (int i = GreenTimeB / 1000; i > 0; i--) {
    if (i <= 5) {
      digitalWrite(B_Green, LOW);
      digitalWrite(B_Amber, HIGH);
      printAmberLightTimes(B_Amber, i);
    } else {
      digitalWrite(B_Green, HIGH);
      digitalWrite(B_Amber, LOW);
    }
    Serial.print("Route A: Red (");
    Serial.print(i + (GreenTimeB / 1000)+(GreenTimeC / 1000)+(GreenTimeD / 1000));
    Serial.print("s), Route B: Green (");
    Serial.print(i);
    Serial.print("s), Route C: Red (");
    Serial.print(i);
    Serial.print("s), Route D: Red (");
    Serial.print(i + (GreenTimeC / 1000));
    Serial.println("s)");
    delay(1000);
  }

  // Route B Red, Route C Green
  digitalWrite(B_Green, LOW);
  digitalWrite(B_Amber, LOW);
  digitalWrite(B_Red, HIGH);

  digitalWrite(C_Red, LOW);
  digitalWrite(C_Green, HIGH);
  digitalWrite(C_Amber, LOW);

  for (int i = GreenTimeC / 1000; i > 0; i--) {
    if (i <= 5) {
      digitalWrite(C_Green, LOW);
      digitalWrite(C_Amber, HIGH);
      printAmberLightTimes(C_Amber, i);
    } else {
      digitalWrite(C_Green, HIGH);
      digitalWrite(C_Amber, LOW);
    }
    Serial.print("Route A: Red (");
    Serial.print(i + (GreenTimeB / 1000) + (GreenTimeD / 1000) );
    Serial.print("s), Route B: Red (");
    Serial.print(i + (GreenTimeA / 1000) + (GreenTimeC / 1000) + (GreenTimeD / 1000));
    Serial.print("s), Route C: Green (");
    Serial.print(i);
    Serial.print("s), Route D: Red (");
    Serial.print(i);
    Serial.println("s)");
    delay(1000);
  }

  // Route C Red, Route D Green
  digitalWrite(C_Green, LOW);
  digitalWrite(C_Amber, LOW);
  digitalWrite(C_Red, HIGH);

  digitalWrite(D_Red, LOW);
  digitalWrite(D_Green, HIGH);
  digitalWrite(D_Amber, LOW);

  for (int i = GreenTimeD / 1000; i > 0; i--) {
    if (i <= 5) {
      digitalWrite(D_Green, LOW);
      digitalWrite(D_Amber, HIGH);
      printAmberLightTimes(D_Amber, i);
    } else {
      digitalWrite(D_Green, HIGH);
      digitalWrite(D_Amber, LOW);
    }
    Serial.print("Route A: Red (");
    Serial.print(i);
    Serial.print("s), Route B: Red (");
    Serial.print(i + (GreenTimeA / 1000) + (GreenTimeD / 1000) );
    Serial.print("s), Route C: Red (");
    Serial.print(i + (GreenTimeA / 1000) + (GreenTimeB / 1000));
    Serial.print("s), Route D: Green (");
    Serial.print(i);
    Serial.println("s)");
    delay(1000);
  }

  // Route D Red, back to Route A Green
  digitalWrite(D_Green, LOW);
  digitalWrite(D_Amber, LOW);
  digitalWrite(D_Red, HIGH);
}
