IOT Based Respiratory monitoring system

Main objective of this project is to observe a patient's condition using a
respiratory rate monitor.

Implemented Attributes :
1. NodeMCU
2. LM35 sensor
3. Thingspeak Cloud to view the data
4. Custom built website to control the whole IOT system
P5. hp script for sending mail

The LM35 temperature sensor is used. For calculating respiratory rate,
we need one LM35 temperature sensor. The data collected here will be
uploaded to ThingSpeak cloud and is observed. Every time we refresh
we can get the new respiratory rate at that moment. Here the LED acts
as an actuator. All the data is uploaded in NodeMCU for using
actuators and sensors. When nodeMCU sends breath count to the
Thingspeak server, the Php script takes data from Thingspeak and
then compares the breathing rate if it is low or high then it sends an
email.#   R e s p i r a t o r y - r a t e - m o n i t o r  
 