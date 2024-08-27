#includ <ESP8266WiF.>
#includ <Arduin.>
#includ <ESP8266WebServe.>
#includ <WiFiClien.>
#includ <ThingSpea.>
// ThingSpeak settings
unsigned long myChannel = 2284877;
const char *apiKey = "EU9725V9RFC6X8E7";
//details of network that has been connected
const char *ssid="realme C53";
const char *pass="hahahaha";
//create a client and server to listen on port number 80
WiFiClient client;
ESP8266WebServer server(80);
float val;
//lm35Pin for reading analog value from sensor
int lm35Pin = A0;
// LED pin
const int ledPin = D0;
float roomtemp = 30.00;
float baseline = 1.06;
bool flag = false;
float diff;
float breathingRate;
int breathcount=0;
void setup()
{
Serial.begin(9600);
//set D0 to output to operate actuator
pinMode(D0, OUTPUT);
//connect to wifi using ssid and password of present
network
WiFi.begin(ssid, pass);
//start thingspeak client to write the information on cloud
ThingSpeak.begin(client);
// Define a route for displaying the temperature and LED
control on the web page
server.on("/", HP_GET, handleRoot);
// Define a route for handling LED control
server.on("/control", HP_POST, handleControl);
// Start the web server
server.begin();
}
void loop() //main loop
{
int i = 0;
while(i<100)
{
//printing the localIP address of present process
Serial.println(WiFi.localIP());
// read analog value from lm 35 Pin
val=analogRead(lm35Pin)*3300/10240.0+30;
Serial.print("Temperature: ");
Serial.print(val);
Serial.println(" C");
//write the value sensed by sensor to the cloud
ThingSpeak.writeField(myChannel,3,val,apiKey);
//count breath algo
diff = val - roomtemp - baseline;
Serial.print("diff = ");
Serial.println(diff);
//whenever the dierence value is greater than 0.7
increase the counter value
if(diff >= 0.7 && flag == false)
{
flag = true;
breathcount++;
}
if(diff < 0.7 && flag == true)
{
flag = false;
}
i++;
delay(100);
}
Serial.print("breath count = ");
Serial.println(breathcount);
breathingRate = 6 * breathcount;
ThingSpeak.writeField(myChannel,2,breathingRate,apiKey);
server.handleClient(); // Handle web client requests
delay(60*1000 );
}
void handleRoot() {
//initialise string html that has to be sent to server to
display information on webpage
String html = "<html><body>";
html += "<h1>Breathing Rate Monitor</h1>";
html += "<p>Breathing Rate: " + String(breathingRate) + " breaths per
minute</p>";
// Add LED control buttons
html += "<form action='/control' method='post'>";
html += "<button type='submit' name='led' value='on'>Tur On
LE</button>";
html += "<button type='submit' name='led' value='off''>Tur Off
LE</button>";
html += "</form>";
html += "</body></html>";
server.send(200, "text/html", html);
}
void handleControl() {
String ledState = server.arg("led");
if (ledState == "on") {
digitalWrite(ledPin, HIGH);
} else if (ledState == "off") {
digitalWrite(ledPin, LOW);
}
// Redirect back to the control page
server.sendHeader("Location", "/");
server.send(302, "text/plain", "");
}