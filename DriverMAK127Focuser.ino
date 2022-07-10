// Motor pins
// focuser 1
int STEPPER1_PIN_1= 2;
int STEPPER1_PIN_2= 3;
int STEPPER1_PIN_3= 4;
int STEPPER1_PIN_4= 5;

// focuser 2
int STEPPER2_PIN_1= 6;
int STEPPER2_PIN_2= 7;
int STEPPER2_PIN_3= 8;
int STEPPER2_PIN_4= 9;

// focuser speeds in ms
int delay1 = 2;
int delay2 = 2;

// focuser number increment steps
int nbTurns1 = 50;
int nbTurns2 = 50;

// new value
int newValue = 0;

// moving or not
int moving1 = 0;

void setup() 
{  
  // initialisation des entrées
  pinMode(STEPPER1_PIN_1, OUTPUT);
  pinMode(STEPPER1_PIN_2, OUTPUT);
  pinMode(STEPPER1_PIN_3, OUTPUT);
  pinMode(STEPPER1_PIN_4, OUTPUT);
  pinMode(STEPPER2_PIN_1, OUTPUT);
  pinMode(STEPPER2_PIN_2, OUTPUT);
  pinMode(STEPPER2_PIN_3, OUTPUT);
  pinMode(STEPPER2_PIN_4, OUTPUT);
  
  Serial.begin(57600);
  Serial.flush();
}

void loop() 
{
  String cmd;

  if(Serial.available()>0)
  {
    cmd=Serial.readStringUntil('#');
    if (cmd=="GDELAY1")
    {
      Serial.print(delay1);
      Serial.println("#");
    }
    else if (cmd=="GDELAY2")
    {
      Serial.print(delay2);
      Serial.println("#");
    }
    else if (cmd=="GTURNS1")
    {
      Serial.print(nbTurns1);
      Serial.println("#");
    }
    else if (cmd=="GTURNS2")
    {
      Serial.print(nbTurns2);
      Serial.println("#");
    }
    else if (cmd=="SDELAY1")
    {
      newValue = 1;
    }
    else if (cmd=="SDELAY2")
    {
      newValue = 2;
    }
    else if (cmd=="STURNS1")
    {
      newValue = 3;
    }
    else if (cmd=="STURNS2")
    {
      newValue = 4;
    }    
    else if (cmd=="F1")
    {
      moveForward1(0);
      Serial.print("DONE");
      Serial.println("#");
    }
    else if (cmd=="F2")
    {
      moveForward2(0);
      Serial.print("DONE");
      Serial.println("#");
    }    
    else if (cmd=="R1")
    {
      moveBackward1(0);
      Serial.print("DONE");
      Serial.println("#");
    }
    else if (cmd=="R2")
    {
      moveBackward2(0);
      Serial.print("DONE");
      Serial.println("#");
    }
    else if (cmd=="FF1")
    {
      moveForward1(1);
      Serial.print("DONE");
      Serial.println("#");
    }
    else if (cmd=="FF2")
    {
      moveForward2(1);
      Serial.print("DONE");
      Serial.println("#");
    }    
    else if (cmd=="FR1")
    {
      moveBackward1(1);
      Serial.print("DONE");
      Serial.println("#");
    }
    else if (cmd=="FR2")
    {
      moveBackward2(1);
      Serial.print("DONE");
      Serial.println("#");
    }
    else if (newValue == 1)
    {
      // speed
      delay1 = abs(cmd.toInt());
      newValue = 0;
      delay(1000);
      Serial.print(delay1);
      Serial.println("#");
    }
    else if (newValue == 2)
    {
      // speed
      delay2 = abs(cmd.toInt());
      newValue = 0;
      delay(1000);
      Serial.print(delay2);
      Serial.println("#");
    }
    else if (newValue == 3)
    {
      // #steps to do
      nbTurns1 = abs(cmd.toInt());
      newValue = 0;
      delay(1000);
      Serial.print(nbTurns1);
      Serial.println("#");
    }
    else if (newValue == 4)
    {
      // #steps to do
      nbTurns2 = abs(cmd.toInt());
      newValue = 0;
      delay(1000);
      Serial.print(nbTurns2);
      Serial.println("#");
    }
  }
}


void moveForward1(int fast)
{
    int nbTurns = nbTurns1;
    
    if (fast) 
      nbTurns = nbTurns * 3;
    
    // nombre de pas
    int step_number = 0;

    while(step_number < (nbTurns * 4))
    {
      moveCoilForward1(step_number%4);
      step_number++;
      delay(delay1);
    }

    digitalWrite(STEPPER1_PIN_1, LOW);
    digitalWrite(STEPPER1_PIN_2, LOW);
    digitalWrite(STEPPER1_PIN_3, LOW);
    digitalWrite(STEPPER1_PIN_4, LOW);
}

void moveBackward1(int fast)
{
    int nbTurns = nbTurns1;
    
    if (fast) 
      nbTurns = nbTurns * 3;
      
    // nombre de pas
    int step_number = 0;

    while(step_number < (nbTurns * 4))
    {
      moveCoilBackward1(step_number%4);
      step_number++;
      delay(delay1);
    }

    digitalWrite(STEPPER1_PIN_1, LOW);
    digitalWrite(STEPPER1_PIN_2, LOW);
    digitalWrite(STEPPER1_PIN_3, LOW);
    digitalWrite(STEPPER1_PIN_4, LOW);
}



void moveCoilForward1(int coil_number)
{
  switch(coil_number)
  {
      case 0:
        digitalWrite(STEPPER1_PIN_1, HIGH);
        digitalWrite(STEPPER1_PIN_2, LOW);
        digitalWrite(STEPPER1_PIN_3, LOW);
        digitalWrite(STEPPER1_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER1_PIN_1, LOW);
        digitalWrite(STEPPER1_PIN_2, HIGH);
        digitalWrite(STEPPER1_PIN_3, LOW);
        digitalWrite(STEPPER1_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER1_PIN_1, LOW);
        digitalWrite(STEPPER1_PIN_2, LOW);
        digitalWrite(STEPPER1_PIN_3, HIGH);
        digitalWrite(STEPPER1_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER1_PIN_1, LOW);
        digitalWrite(STEPPER1_PIN_2, LOW);
        digitalWrite(STEPPER1_PIN_3, LOW);
        digitalWrite(STEPPER1_PIN_4, HIGH);
        break;
  } 
}

void moveCoilBackward1(int coil_number)
{
  switch(coil_number)
  {
    case 0:
      digitalWrite(STEPPER1_PIN_1, LOW);
      digitalWrite(STEPPER1_PIN_2, LOW);
      digitalWrite(STEPPER1_PIN_3, LOW);
      digitalWrite(STEPPER1_PIN_4, HIGH);
      break;
    case 1:
      digitalWrite(STEPPER1_PIN_1, LOW);
      digitalWrite(STEPPER1_PIN_2, LOW);
      digitalWrite(STEPPER1_PIN_3, HIGH);
      digitalWrite(STEPPER1_PIN_4, LOW);
      break;
    case 2:
      digitalWrite(STEPPER1_PIN_1, LOW);
      digitalWrite(STEPPER1_PIN_2, HIGH);
      digitalWrite(STEPPER1_PIN_3, LOW);
      digitalWrite(STEPPER1_PIN_4, LOW);
      break;
    case 3:
      digitalWrite(STEPPER1_PIN_1, HIGH);
      digitalWrite(STEPPER1_PIN_2, LOW);
      digitalWrite(STEPPER1_PIN_3, LOW);
      digitalWrite(STEPPER1_PIN_4, LOW);
      break;
  }
}



void moveForward2(int fast)
{
    int nbTurns = nbTurns2;
    
    if (fast) 
      nbTurns = nbTurns * 3;
      
    // nombre de pas
    int step_number = 0;

    while(step_number < (nbTurns * 4))
    {
      moveCoilForward2(step_number%4);
      step_number++;
      delay(delay2);
    }

    digitalWrite(STEPPER2_PIN_1, LOW);
    digitalWrite(STEPPER2_PIN_2, LOW);
    digitalWrite(STEPPER2_PIN_3, LOW);
    digitalWrite(STEPPER2_PIN_4, LOW);
}


void moveBackward2(int fast)
{
    int nbTurns = nbTurns2;
    
    if (fast) 
      nbTurns = nbTurns * 3;
      
    // nombre de pas
    int step_number = 0;

    while(step_number < (nbTurns * 4))
    {
      moveCoilBackward2(step_number%4);
      step_number++;
      delay(delay2);
    }

    digitalWrite(STEPPER2_PIN_1, LOW);
    digitalWrite(STEPPER2_PIN_2, LOW);
    digitalWrite(STEPPER2_PIN_3, LOW);
    digitalWrite(STEPPER2_PIN_4, LOW);
}



void moveCoilForward2(int coil_number)
{
  switch(coil_number)
  {
      case 0:
        digitalWrite(STEPPER2_PIN_1, HIGH);
        digitalWrite(STEPPER2_PIN_2, LOW);
        digitalWrite(STEPPER2_PIN_3, LOW);
        digitalWrite(STEPPER2_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER2_PIN_1, LOW);
        digitalWrite(STEPPER2_PIN_2, HIGH);
        digitalWrite(STEPPER2_PIN_3, LOW);
        digitalWrite(STEPPER2_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER2_PIN_1, LOW);
        digitalWrite(STEPPER2_PIN_2, LOW);
        digitalWrite(STEPPER2_PIN_3, HIGH);
        digitalWrite(STEPPER2_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER2_PIN_1, LOW);
        digitalWrite(STEPPER2_PIN_2, LOW);
        digitalWrite(STEPPER2_PIN_3, LOW);
        digitalWrite(STEPPER2_PIN_4, HIGH);
        break;
  } 
}


void moveCoilBackward2(int coil_number)
{
  switch(coil_number)
  {
    case 0:
      digitalWrite(STEPPER2_PIN_1, LOW);
      digitalWrite(STEPPER2_PIN_2, LOW);
      digitalWrite(STEPPER2_PIN_3, LOW);
      digitalWrite(STEPPER2_PIN_4, HIGH);
      break;
    case 1:
      digitalWrite(STEPPER2_PIN_1, LOW);
      digitalWrite(STEPPER2_PIN_2, LOW);
      digitalWrite(STEPPER2_PIN_3, HIGH);
      digitalWrite(STEPPER2_PIN_4, LOW);
      break;
    case 2:
      digitalWrite(STEPPER2_PIN_1, LOW);
      digitalWrite(STEPPER2_PIN_2, HIGH);
      digitalWrite(STEPPER2_PIN_3, LOW);
      digitalWrite(STEPPER2_PIN_4, LOW);
      break;
    case 3:
      digitalWrite(STEPPER2_PIN_1, HIGH);
      digitalWrite(STEPPER2_PIN_2, LOW);
      digitalWrite(STEPPER2_PIN_3, LOW);
      digitalWrite(STEPPER2_PIN_4, LOW);
      break;
  }
}
