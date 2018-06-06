#include<EthernetClient.h>
#include <ThingSpeak.h>
#include<ESP8266WiFi.h>

char jsonBuffer[5000] = "[";

char ssid[] = "abcd"; // Network SSID (name)
char pass[] = "raghav123"; // Network password
WiFiClient client; // Initialize the WiFi client library
unsigned long myChannelNumber = <Channel Number>;
const char * myWriteAPIKey = <Write API KEY>;

char server[] = "api.thingspeak.com"; // ThingSpeak Server

/* Collect data once every 3 seconds and post data to ThingSpeak channel once every 30 seconds */
unsigned long lastConnectionTime = 0; // Track the last connection time
unsigned long lastUpdateTime = 0; // Track the last update time
const unsigned long postingInterval = 60L * 1000L; // Post data every 50 seconds
const unsigned long updateInterval = 3L * 1000L; // Update once every 3 seconds

// defines pins numbers D0=>16, D1=>5, D2=>4, D3=>0, D4=>2, D5=>14, D6=>12, D7=>13, D8=>15
const int echoPin1 = 16;
const int trigPin1 = 5;
const int echoPin2 = 4;
const int trigPin2 = 0;


// defines variables
long duration1;
long duration2;
int distance1;
int distance2;
// select the input pin for the potentiometer
int laserSensorPin = A0; 

int laserValue;
int accuracyCheck=0;    
int submitResult = 0;

int counter = 0;
long dataToAppend=0;
int stop_8 = 0;

void setup() 
{
  Serial.begin(9600);
  
  // Attempt to connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    delay(5000);  // Wait 5 seconds to connect
  }
  
  Serial.println("Connected to wifi");
  // Print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print your device IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin1 as an Input
  ThingSpeak.begin(client);
  
  accuracyCheckFunction();
  start_or_stop_8_test();
}

void start_or_stop_8_test()
{
  int status_ = analogRead(laserSensorPin);
  Serial.print("Switch on the laser to start the test");
  while(status_ > 100)
  {
    status_ = analogRead(laserSensorPin);
    Serial.print(".");
    delay(2000);
  }

  Serial.println(" ");
  Serial.print("Waiting to start 8 test");
  status_ = ThingSpeak.readFloatField(myChannelNumber, 7);
  while(status_ != 1)
  {
    status_ = ThingSpeak.readFloatField(myChannelNumber, 7);
    Serial.print(".");
  }
  return;
}

void accuracyCheckFunction()
{
  while(!accuracyCheck)
  {
    // Clears the trigPin
    digitalWrite(trigPin1, LOW);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration1 = pulseIn(echoPin1, HIGH);
  
    delay(200);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration2 = pulseIn(echoPin2, HIGH);
  
    // Calculating the distance
    distance1= duration1*0.034/2;
    distance2= duration2*0.034/2;
  
    //Perform accuracy check 
    if(distance1<25 && distance1>15 && distance2<25 && distance2>15)
      accuracyCheck++;
  
    Serial.print("The distances are ");
    Serial.print(distance1);
    Serial.print(" ");
    Serial.print(distance2);
    Serial.print(" ");
    Serial.println("Adjust the ultrasonic sensors");  
  }
  
  if(accuracyCheck==1)
  {
    Serial.print("The distances are ");
    Serial.print(distance1);
    Serial.print(" ");
    Serial.print(distance2);
    Serial.print(" ");
    Serial.println("Ultrasonic sensors are caliberated and is ready for the test");
    return;
  }
}

void loop() 
{
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);

  delay(300);
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculating the distance
  distance1= duration1*0.034/2;
  distance2= duration2*0.034/2;


  strcat(jsonBuffer,"{\"delta_t\":");
  unsigned long deltaT = (millis() - lastUpdateTime)/1000;
  size_t lengthT = String(deltaT).length();
  char temp[4];
  String(deltaT).toCharArray(temp,lengthT+1);
  strcat(jsonBuffer,temp);
  strcat(jsonBuffer,",");
      
  //Add Distance 1 to JSon Array
  dataToAppend = distance1; 
  strcat(jsonBuffer, "\"field1\":");
  lengthT = String(dataToAppend).length();
  String(dataToAppend).toCharArray(temp,lengthT+1);
  strcat(jsonBuffer,temp);
  strcat(jsonBuffer,",");
  
  //Print Distance1
  Serial.print(" ");
  Serial.print(temp);
  Serial.print(" ");
  
  //Add Distance 2 to JSon Array
  dataToAppend = distance2; 
  strcat(jsonBuffer, "\"field2\":");
  lengthT = String(dataToAppend).length();
  String(dataToAppend).toCharArray(temp,lengthT+1);
  strcat(jsonBuffer,temp);
  strcat(jsonBuffer,",");
  
  //Print Distance2
  Serial.print(temp);
  Serial.print(" ");
  
  laserValue = analogRead(laserSensorPin);
  
  //laser value is appended as 1 if laser is hit and 0 otherwise
  if(laserValue < 100)
    dataToAppend = 1; 
  else
    dataToAppend = 0; 

  strcat(jsonBuffer, "\"field6\":");
  lengthT = String(dataToAppend).length();
  String(dataToAppend).toCharArray(temp,lengthT+1);
  strcat(jsonBuffer,temp);    
  strcat(jsonBuffer,"},");

  Serial.print(temp);
  Serial.println(" ");
  
  // If posting interval time has reached 30 seconds, update the ThingSpeak channel with your data
  if (millis() - lastConnectionTime >=  postingInterval)
  {
    size_t len = strlen(jsonBuffer);
    jsonBuffer[len-1] = ']';
    httpRequest(jsonBuffer);
  }
  lastUpdateTime = millis(); // Update the last update time
  delay(3000);
  /*  JSON format for updates paramter in the API
   *  This examples uses the relative timestamp as it uses the "delta_t". You can also provide the absolute timestamp using the "created_at" parameter instead of "delta_t".
   *  "[{\"delta_t\":0,\"field1\":-70},{\"delta_t\":3,\"field1\":-66}]"
   */
}

  

// Updates the ThingSpeakchannel with data
void httpRequest(char* jsonBuffer) 
{
  stop_8 = ThingSpeak.readFloatField(myChannelNumber, 7);
  if(stop_8 == 0)
  {
    ThingSpeak.writeField(myChannelNumber, 7, 2, myWriteAPIKey);
    Serial.println("Test Completed and submitted for evaluation");
    while(1)
    {
      Serial.println(".");
      delay(1000);
    };
  }
  /* JSON format for data buffer in the API
   *  This examples uses the relative timestamp as it uses the "delta_t". You can also provide the absolute timestamp using the "created_at" parameter
   *  instead of "delta_t".
   *   "{\"write_api_key\":\"YOUR-CHANNEL-WRITEAPIKEY\",\"updates\":[{\"delta_t\":0,\"field1\":-60},{\"delta_t\":15,\"field1\":200},{\"delta_t\":15,\"field1\":-66}]
   */

  // Format the data buffer as noted above
  char data[2000] = "{\"write_api_key\":\""+myWriteAPIKey+"\",\"updates\":"; 
  strcat(data,jsonBuffer);
  strcat(data,"}");
  // Close any connection before sending a new request
  client.stop();
  String data_length = String(strlen(data)+1); //Compute the data buffer length
  Serial.println(data);
  // POST data to ThingSpeak
  if (client.connect(server, 80)) {
    client.println("POST /channels/"+StringmyChannelNumber)+"/bulk_update.json HTTP/1.1"); // Replace YOUR-CHANNEL-ID with your ThingSpeak channel ID
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: mw.doc.bulk-update (Arduino ESP8266)");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.println("Content-Length: "+data_length);
    client.println();
    client.println(data);
    Serial.println(data);
  }
  else {
    Serial.println("Failure: Failed to connect to ThingSpeak");
  }
  delay(250); //Wait to receive the response
  client.parseFloat();
  int response = client.parseInt();
  String resp = String(response);
  if(response == 202)
  {
    Serial.println("Submit Success");
    submitResult++;
  }
  Serial.println("Response code:"+resp); // Print the response code. 202 indicates that the server has accepted the response
  jsonBuffer[0] = '['; //Reinitialize the jsonBuffer for next batch of data
  jsonBuffer[1] = '\0';
  lastConnectionTime = millis(); //Update the last conenction time
}
