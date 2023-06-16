
class SmartHomeDevice {
  protected:
    byte _pin;
  	int _pin1;

  public:
    SmartHomeDevice(byte pin) {
      if(A0<pin<A5){
      _pin = pin;
      pinMode(_pin, INPUT);
      }
   
    else if(0<pin<9){
      _pin = pin;
      pinMode(_pin, OUTPUT);
    }
    }
  
};

class ClimateControl : public SmartHomeDevice {
  public:
    ClimateControl(int _pin) : SmartHomeDevice(_pin) {}

    float getTemperature() {
      int sensorValue = analogRead(_pin); // зчитуємо значення з аналогового входу
      float temperature = (sensorValue * 5.0 / 1024.0) * 10.0; // обчислюємо температуру за формулою LM35
      return temperature;
    }
};

class GasControl : public SmartHomeDevice {
  public:
    GasControl(int pin) : SmartHomeDevice(pin) {}

    float getGasLevel() {
      int sensorValue = analogRead(_pin); 
      float voltage = sensorValue * (5.0 / 1023.0); 
      float gasLevel = (voltage / 5.0) * 100.0; 
      return gasLevel;
    }
}; 
class VentelationControl : public  GasControl {
  public: 
  
  VentelationControl(int _pin) :  GasControl(_pin) {  pinMode(_pin, OUTPUT);}
  
    void turnOnVentelationMotor() {
      digitalWrite(_pin, HIGH);
    }

    void turnOffVentelationMotor() {
      digitalWrite(_pin, LOW);
    }
}; 
class HeatingControl : public ClimateControl {
  public:  

  HeatingControl(int _pin) : ClimateControl(_pin) {  pinMode(_pin, OUTPUT);}
    void turnOnHeatingMotor() {
      digitalWrite(_pin, HIGH);
    }

    void turnOffHeatingMotor() {
      digitalWrite(_pin, LOW);
    }
}; 
class FireSecurity : public SmartHomeDevice {
  public:
    FireSecurity(int _pin) : SmartHomeDevice(_pin) {}
  float getSmoke(){
   int sensorValue = analogRead(_pin); 
      float voltage = sensorValue * (5.0 / 1023.0); 
      float gasLevel = (voltage / 5.0) * 100.0; 
      return gasLevel;
    }
};

class VilianSecurity : public SmartHomeDevice {
  public:
    VilianSecurity(int pin) : SmartHomeDevice(pin) {}

    float getVilianLevel() {
      int sensorValue = analogRead(_pin); 
      float voltage = sensorValue * (5.0 / 1023.0); 
      float vilianLevel = (voltage / 5.0) * 100.0; 
      return vilianLevel;
    }
}; 
class SignalizationControl : public FireSecurity {
  public: 
  SignalizationControl(int _pin) : FireSecurity(_pin) {  pinMode(_pin, OUTPUT);}
    void turnOnSignalization() { 
       digitalWrite(_pin, HIGH);
   

      }
    

    void turnOffSignalization() {
      digitalWrite(_pin, LOW);
    }
}; 
class PoliceControl : public VilianSecurity {
  public: 
  PoliceControl(int _pin) : VilianSecurity(_pin) {  pinMode(_pin, OUTPUT);}
    void turnOnPolice () {
      digitalWrite(_pin, HIGH);
    }

    void turnOffPolice () {
      digitalWrite(_pin, LOW);
    }
}; 
class LightingSensor : public SmartHomeDevice {
  public:
    LightingSensor(int _pin) : SmartHomeDevice(_pin) {}

    float getLight() {
      int sensorValue = analogRead(_pin); 
      float voltage = sensorValue * (5.0 / 1023.0); 
      float level = (voltage / 5.0) * 100.0; 
      return level;
    }
};

class LightingControl : public LightingSensor {
  public: 
  LightingControl(int _pin) : LightingSensor(_pin) {}
    void turnOnLighting() {
      digitalWrite(_pin, HIGH);
    }

    void turnOffLighting() {
      digitalWrite(_pin, LOW);
    }
  
}; 



ClimateControl climateControl(A0);
LightingControl osvitlenya(4);
GasControl gasSensor(A2);
VentelationControl VentelationControl(5); 
HeatingControl batareya(7);
FireSecurity pozhar(A1); 
VilianSecurity dozor(A3);
LightingSensor okomir(A4); 
PoliceControl viuviu(8);


SignalizationControl signalizatsia(10);
void setup() {
  Serial.begin(9600);
}

void loop() {
  float temperature = climateControl.getTemperature();
  float gasLevel = gasSensor.getGasLevel();
  float smoke = pozhar.getSmoke();
  float vilian = dozor.getVilianLevel();
  float light = okomir.getLight();
  unsigned long currentMillis = millis();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C | ");
  Serial.print("Gas Level: ");
  Serial.print(gasLevel);
  Serial.println("% |");
  Serial.print("Smoke:");
  Serial.print(smoke);
  Serial.print("% |");
  if(vilian>0){
    Serial.println("Vilian: Alarm");
  }else{ 
    Serial.println("Safe and sound");
  } 
  Serial.print("Light:");
  Serial.print(light);
  Serial.println("% |");
	Serial.print("-------------------------------------------");
  Serial.println(""); 
    Serial.println(currentMillis);
  if(temperature>30){
    VentelationControl.turnOnVentelationMotor(); 
  }
   delay(1);
  VentelationControl.turnOffVentelationMotor(); 
  signalizatsia.turnOffSignalization();
  batareya.turnOffHeatingMotor(); 
   viuviu.turnOffPolice();
  
   if(gasLevel>10){
    VentelationControl.turnOnVentelationMotor(); 
  } 
   if(smoke>10){
    viuviu.turnOnPolice();
     signalizatsia.turnOnSignalization();
  }
   delay(1);
  VentelationControl.turnOffVentelationMotor(); 
  signalizatsia.turnOffSignalization();
  batareya.turnOffHeatingMotor(); 
   viuviu.turnOffPolice();
   if(temperature<20){
    batareya.turnOnHeatingMotor(); 
   
  } 
   
   if(gasLevel>10){
    VentelationControl.turnOnVentelationMotor(); 
  }  
   if(vilian>10){
   viuviu.turnOnPolice();
  }  
  delay(1);
  VentelationControl.turnOffVentelationMotor(); 
  signalizatsia.turnOffSignalization();
  batareya.turnOffHeatingMotor(); 
   viuviu.turnOffPolice(); 
  if(light>50){
    osvitlenya.turnOnLighting();
  }
  delay(1);
  VentelationControl.turnOffVentelationMotor(); 
  signalizatsia.turnOffSignalization();
  batareya.turnOffHeatingMotor(); 
   viuviu.turnOffPolice(); 
  osvitlenya.turnOffLighting();

}