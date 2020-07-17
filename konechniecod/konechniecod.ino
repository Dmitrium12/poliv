  }
}



void reconnect() {         
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    // с пользователем и паролем раскомментировать этот код
     if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
    //if (client.connect(clientId.c_str())) {

      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("server/pump1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(5, INPUT_PULLUP);
//  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  waitForSync();
  pinMode(relayPin, OUTPUT);

   pinMode(SENS_PIN, INPUT);
     digitalWrite(relayPin, HIGH);
}

void loop() {

  String topic ="";
  String value;


  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2) {
    lastMsg = now;
    ++indexSend;
    //snprintf (msg, MSG_BUFFER_SIZE, "", value);
}


      delay(1000);
// Устанавливаем текущее время
  CurrentTime = millis();
  // считываем сенсор
  CurrentState = 0;
  CurrentState = digitalRead(SENS_PIN);
            
            if(millis()-vrema>60000) {
                vrema = millis();
            value = CurrentState;
            topic = "base1/sensor1/water_level";
            Serial.println(value);
            client.publish(topic.c_str(), value.c_str()); 
            if (sostoianie_pompi != 5){
           sostoianie_pompi = 5;
            value = "1";
            topic = "base1/device1/pump_state";
           Serial.println(CurrentState);
           client.publish(topic.c_str(), value.c_str()); 
           }
                    //  delay(280000);     
            // если текущее состояние сенсора 0, то выключаем светодиод
          }else{
           }
          
          
        
  // смена состояния не состоялась, сбрасываем таймер
  }


///////////////////////////////////////////////////////////////
String getCurrentTime(){
    return dateTime(ISO8601);
}
