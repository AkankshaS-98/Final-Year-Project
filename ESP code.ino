#include "ESP8266WiFi.h" 
#include <WiFiClient.h>

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"

char INSERT_DATA [] = "INSERT INTO body_parameter.info (PulseRate, SystolicBP, DiastolicBP, O2Saturation, TotalHemoglobin, Temperature) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')";
char query [256];

IPAddress server_addr (192,168,225,241);                    // IP of the MySQL *server* here
char user[]        = "hw";                                  // MySQL user login username
char password[]    = "";                                    // MySQL user login password

// const char* ssid      = "akrut";                            // your SSID
// const char* passkey   = "akrut@2019";                       // your SSID Password
const char* ssid      = "GERL";								// your SSID
const char* passkey   = "takkappus";						// your SSID Password

WiFiClient client;
MySQL_Connection conn((Client *)&client);

MAX30105 particleSensor;
boolean startflag = 0;

//  Heart Rate Parameters
const byte RATE_SIZE = 10;                                                          //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];                                                              //Array of heart rates
byte avg_rates[RATE_SIZE];                                                          //Array of heart rates
long del[25], timeDelay = 0;
byte rateSpot = 0, avgCnt = 0, loopCnt = 0;
long lastBeat = 0; 
float beatsPerMinute;
int beatAvg, Avg_beat, HRbpm;

// BP Rate Parameters
float SBP,DBP;

//  SPO2 Rate Parameters
//#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
//uint16_t irBuffer[100];                                                             //infrared LED sensor data
//uint16_t redBuffer[100];                                                            //red LED sensor data
//#else
uint32_t irBuffer[100];                                                             //infrared LED sensor data
uint32_t redBuffer[100];                                                            //red LED sensor data
//#endif

int32_t bufferLength;                                                               //data length
int32_t spo2;                                                                       //SPO2 value
int8_t validSPO2;                                                                   //indicator to show if the SPO2 calculation is valid
int32_t heartRate;                                                                  //heart rate value
int8_t validHeartRate;                                                              //indicator to show if the heart rate calculation is valid

void setup (void) {
  Serial.begin(9600);
  delay (2500);
  
  WiFi.begin (ssid, passkey);
  while (WiFi.status () != WL_CONNECTED) {
    delay (50);
//    Serial.print (".");
  }
  Serial.print ("W");
  delay (1500);
  
  Serial.print ("D");
  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay (50);
//    Serial.print (".");
  }
  delay (1500);
  
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {                                 //Use default I2C port, 400kHz speed
    Serial.print ("s");
    while (1);
  }
  Serial.print ("S");
  delay (2500);
}

void loop (void) {
  boolean processFlag = true;
  const byte RATE_SIZE = 10;                                                          //Increase this for more averaging. 4 is good.
  byte rates[RATE_SIZE];                                                              //Array of heart rates
  byte avg_rates[RATE_SIZE];                                                          //Array of heart rates
  long del[25], timeDelay;
  byte rateSpot = 0, avgCnt = 0, loopCnt = 0;
  long lastBeat = 0; 
  float beatsPerMinute;
  int beatAvg, Avg_beat, HRbpm;
  
  // BP Rate Parameters
  float SBP,DBP;

  particleSensor.setup();                                                            //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);                                         //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);                                         //Turn off Green LED    
  Serial.print ("F");
  while (processFlag == true) {
    long irValue = particleSensor.getIR();
    if (irValue > 50000) {
      startflag = true;
      Serial.print ("H");
//      Serial.println ("Calibrating HR and BP");
    }
    
    while (startflag == true) {
      long irValue = particleSensor.getIR();
      if (irValue > 50000) {
        if (checkForBeat(irValue) == true) {
          long delta = millis() - lastBeat;
          lastBeat = millis();
          
          beatsPerMinute = 60 / (delta / 1000.0);
          if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            rates[rateSpot++] = (byte)beatsPerMinute;
            rateSpot %= RATE_SIZE;
  //          Serial.print (".");
            beatAvg = 0;
            for (byte x = 0 ; x < RATE_SIZE ; x++)
              beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
              
            avgCnt++;
            del[avgCnt] = delta;
//            Serial.println (del[avgCnt]);
            Serial.print ("*" + String (map (avgCnt, 0, 25, 0, 100)) + "#");
            if (avgCnt >= 11 && avgCnt <= 20) {
              avg_rates[loopCnt++] = (byte)beatAvg;
              loopCnt %= RATE_SIZE;
            }
            else {
              for (byte y = 0 ; y < RATE_SIZE ; y++)
                Avg_beat += avg_rates[y];
              Avg_beat /= RATE_SIZE;
            }
            if (avgCnt >= 25) {
              timeDelay = 0;
//              https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6603632/#FD6-sensors-19-02557
              for (byte y = 11 ; y < (10 + RATE_SIZE) ; y++) {
                timeDelay += del[y];
//                Serial.println (String (timeDelay) + " , " + String (del[y]));
              }
              
              timeDelay /= RATE_SIZE;
              HRbpm = Avg_beat;
              long HRms = 60000 / HRbpm;
              long td = HRms - timeDelay;
              int Ksbp = 45, Kdbp = 28;
              
              SBP = (184.3 - ((1.329 * HRbpm) + 0.0848 * td)) + Ksbp;
              DBP = (55.96 - ((0.02912 * HRbpm) + 0.02302 * td)) + Kdbp;

//              Serial.println ("");
//              Serial.println ("HRbpm: " + String (HRbpm));
////              Serial.println ("HRms: " + String (HRms));
////              Serial.println ("delta: " + String (timeDelay));
//              Serial.println ("SBP: " + String (SBP));
//              Serial.println ("DBP: " + String (DBP));
//              Serial.println ("");

              startflag = false;
              processFlag = false;
              avgCnt = 0;
              delay (1500);
            }
          }
        }
      }
    }
  }

  processFlag = true;
  byte ledBrightness  = 60;     //Options: 0=Off to 255=50mA
  byte sampleAverage  = 4;      //Options: 1, 2, 4, 8, 16, 32
  byte ledMode        = 2;      //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate     = 100;    //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth      = 411;    //Options: 69, 118, 215, 411
  int adcRange        = 4096;   //Options: 2048, 4096, 8192, 16384

  //  h = 10 * D * (Chbo/SPO2) * Erf
  float D             = 1.05;   // density of blood
  float Chbo          = 26.35;
  float Erf           = 5;
  float hb;

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  Serial.print ("O");
  while (processFlag == true) {
    bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps
    
    for (byte i = 0 ; i < bufferLength ; i++) {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data
  
      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();
    }
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    startflag = true;

    avgCnt = 0;
    while (startflag == true) {
      for (byte i = 25; i < 100; i++) {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
      }

      for (byte i = 75; i < 100; i++) {
        while (particleSensor.available() == false)
          particleSensor.check();
  
        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();
        particleSensor.nextSample();

        avgCnt ++;
        if (validSPO2 == 1) {
          Serial.print ("*" + String (map (avgCnt, 0, 50, 0, 100)) + "#");
          if (avgCnt ==  50) {
            hb = 10 * D * (Chbo/spo2) * Erf;
//            https://iovs.arvojournals.org/article.aspx?articleid=2127689
            
//            Serial.println ("");
//            Serial.println ("Blood Oxygen Saturation : " + String (spo2));
//            Serial.println ("Hemoglobin : " + String (hb));
//            Serial.println ("");
            
            startflag = 0;
            processFlag = 0;
            delay (1500);
          }
        }
        else {
          avgCnt = 0;
        }
      }
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    }
  }

  processFlag = true;
  particleSensor.setup(0);
  particleSensor.enableDIETEMPRDY();
  Serial.print ("T");
  delay (1500);
  float temperatureF = 0;
  while (processFlag == true) {
    for (int dl = 0; dl <= 30; dl++) {
      Serial.print ("*" + String (map (dl, 0, 30, 0, 100)) + "#");
      temperatureF += particleSensor.readTemperatureF();
      delay (500);
    }
    temperatureF = temperatureF / 30;
//    Serial.println ("");
//    Serial.println ("Body Temperature : " +  String (temperatureF));
//    Serial.println ("");
    processFlag = 0;
    delay (1500);
  }

  if (WiFi.status () == WL_CONNECTED && conn.connect(server_addr, 3306, user, password) == true) {
    sprintf(query, INSERT_DATA, String (HRbpm).c_str(), String (SBP).c_str(), String (DBP).c_str(), String (spo2).c_str(), String (hb).c_str(), String (temperatureF).c_str());
//    Serial.println (query);
    MySQL_Cursor *inst_mem = new MySQL_Cursor(&conn);
    inst_mem->execute(query);
    delete inst_mem;

    Serial.print ("I");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay (1500);
  }
  else {
    if (WiFi.status () != WL_CONNECTED){
      Serial.print ("w");
    }
    else if (conn.connect(server_addr, 3306, user, password) != true){
      Serial.print ("d");
    }
    delay (1500);
  }
  Serial.print ("*" + String (HRbpm) + "," + String (SBP) + "," + String (DBP) + "," + String (spo2) + "," + String (hb)+ "," + String (temperatureF) + "#");

  processFlag = true;
  while (processFlag == true) {
    if (Serial.available () > 0) {
      char recVal = Serial.read ();
      if (recVal == '^') {
        processFlag = false;
      }
    }
  }
}
