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
int speed1 = 2;
int speed2 = 2;

// focuser number increment steps
int nbTurns1 = -10000;
int nbTurns2 = -10000;

// new value
int newValue = 0;

// moving or not
int moving1 = 0;

void setup() 
{  // initialisation des entrées
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
    if (cmd=="GETSPEED1")
    {
      Serial.print(speed1);
      Serial.println("#");
    }
    else if (cmd=="GETSPEED2")
    {
      Serial.print(speed2);
      Serial.println("#");
    }
    else if (cmd=="GETTURNS1")
    {
      Serial.print(nbTurns1);
      Serial.println("#");
    }
    else if (cmd=="GETTURNS2")
    {
      Serial.print(nbTurns2);
      Serial.println("#");
    }
    else if (cmd=="SETSPEED1")
    {
      newValue = 1;
    }
    else if (cmd=="SETSPEED2")
    {
      newValue = 2;
    }
    else if (cmd=="SETTURNS1")
    {
      newValue = 3;
    }
    else if (cmd=="SETTURNS2")
    {
      newValue = 4;
    }    
    else if (cmd=="MOVE1")
    {
      M1_Move();
    }
    else if (cmd=="MOVE2")
    {
      M2_Move();
    }
    else if (newValue == 1)
    {
      // speed
      speed1 = cmd.toInt();
      newValue = 0;
    }
    else if (newValue == 2)
    {
      // speed
      speed2 = cmd.toInt();
      newValue = 0;
    }
    else if (newValue == 3)
    {
      // #steps to do
      nbTurns1 = cmd.toInt();
      newValue = 0;
    }
    else if (newValue == 4)
    {
      // #steps to do
      nbTurns2 = cmd.toInt();
      newValue = 0;
    }
  }
}


void M1_Move()
{
    // direction
    boolean dir = true;
    
    if (nbTurns1 < 0)
      dir = false;

    // nombre de pas
    int step_number = 0;

    while(step_number < (abs(nbTurns1) * 4))
    {
      if(dir)
      {
        Move_Motor1_Coil_Left(step_number%4);
      }
      else
      {
        Move_Motor1_Coil_Right(step_number%4);
      }

      step_number++;
      delay(speed1);
    }

    digitalWrite(STEPPER1_PIN_1, LOW);
    digitalWrite(STEPPER1_PIN_2, LOW);
    digitalWrite(STEPPER1_PIN_3, LOW);
    digitalWrite(STEPPER1_PIN_4, LOW);
}



void Move_Motor1_Coil_Left(int coil_number)
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

void Move_Motor1_Coil_Right(int coil_number)
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









void M2_Move()
{
    // direction
    boolean dir = true;
    
    if (nbTurns2 < 0)
      dir = false;

    // nombre de pas
    int step_number = 0;

    while(step_number < (abs(nbTurns2) * 4))
    {
      if(dir)
      {
        Move_Motor2_Coil_Left(step_number%4);
      }
      else
      {
        Move_Motor2_Coil_Right(step_number%4);
      }

      step_number++;
      delay(speed2);
    }

    digitalWrite(STEPPER2_PIN_1, LOW);
    digitalWrite(STEPPER2_PIN_2, LOW);
    digitalWrite(STEPPER2_PIN_3, LOW);
    digitalWrite(STEPPER2_PIN_4, LOW);
}





void Move_Motor2_Coil_Left(int coil_number)
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

void Move_Motor2_Coil_Right(int coil_number)
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
