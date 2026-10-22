/*
  Transistor as a Switch - Arduino + BC547 + 12V Buzzer
  CodeTheHardware - Beginner Project 02
  Video: https://youtu.be/7pzKr06IQjM

  Press button  -> D9 HIGH -> BC547 ON  -> 12V buzzer ON
  Release button -> D9 LOW -> BC547 OFF -> 12V buzzer OFF

  Wiring:
    Push button     : A0 <-> GND (internal pull-up, no resistor needed)
    D9 -> 1k resistor -> BC547 Base
    10k resistor    : Base -> GND (keeps transistor OFF during reset)
    Emitter         -> GND
    Collector       -> Buzzer (-)
    Buzzer (+)      -> +12V
    Arduino GND     <-> 12V supply (-)   (common ground)
*/

#define GPIO_SW   A0
#define BUZZ_PIN  9      // not 13: D13 toggles during bootloader -> buzzer beeps on reset

int lastState = HIGH;    // HIGH = released (INPUT_PULLUP)

void setup()
{
  Serial.begin(9600);

  digitalWrite(BUZZ_PIN, LOW);      // set LOW first -> no glitch at power-up
  pinMode(BUZZ_PIN, OUTPUT);

  pinMode(GPIO_SW, INPUT_PULLUP);   // IMPORTANT: 0 = pressed, 1 = released

  Serial.println("System Started...");
}

void loop()
{
  int SW_State = digitalRead(GPIO_SW);

  if (SW_State != lastState)        // print only when state changes
  {
    if (SW_State == LOW)
    {
      digitalWrite(BUZZ_PIN, HIGH);
      Serial.println("Switch PRESSED  -> Buzzer ON");
    }
    else
    {
      digitalWrite(BUZZ_PIN, LOW);
      Serial.println("Switch RELEASED -> Buzzer OFF");
    }
    lastState = SW_State;
  }

  delay(20);                        // simple debounce, fast response
}
