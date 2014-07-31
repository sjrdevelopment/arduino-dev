
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xF8, 0x8F };
//IPAddress ip( 10,192,55,29 );

EthernetServer server(80);

String stat = "";

int solenoidPin = 8;

void setup()
{
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(solenoidPin, OUTPUT);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac);

  server.begin();

  Serial.println("setup finished");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = false;
    boolean lineBeforePost = false;
    
    while (client.connected()) {
      while(client.available()) {
        char c = client.read();
        //Serial.print(c);
 
        
        
        
        if (lineBeforePost && c != '\n') {
          while(client.available()) {
           char ic = client.read();
           if(ic == '=') {
               char nextChar = client.read();
               if(nextChar == 'f') {
                 stat = "fail";
                 failNotification();
                
               } else if (nextChar == 'p') {
                 stat = "pass";
                passNotification(); 
               
               }
               
               //Serial.println("Build has " + stat + ".");
         
              // send a standard http response header
              client.println("HTTP/1.0 200 OK");
              client.println("Content-Type: text/html");
              client.println();
              client.println("<HTML><BODY>Received data ok - build has " + stat + "</BODY></HTML>");
              delay(1000);
              client.stop();   
           }
           
          }
        } else if (c == '\n' && lineBeforePost) {
        //  Serial.println("line before post");
          
        } else if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c == '\r'  && currentLineIsBlank) {
           lineBeforePost = true;
        } else {
          currentLineIsBlank = false;
        }
        
        /*
        if (c == '\n' && currentLineIsBlank) {

// Here is where the POST data is.  
  
         /* while(client.available())
          {
            Serial.println("client available 2");
             char ic = client.read();
             Serial.print(ic);
            /* if(ic == '=') {
               char nextChar = client.read();
               if(nextChar == 'f') {
                 stat = "fail";
                 failNotification();
               } else if (nextChar == 'p') {
                 stat = "pass";
                passNotification(); 
               }
             }
             
          }
          
          Serial.println();

          Serial.println("Build has " + stat + ".");
         
          // send a standard http response header
          client.println("HTTP/1.0 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML><BODY>Received data ok - build has " + stat + "</BODY></HTML>");
          client.stop();
        }
        else if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
        */
        
      }
      
    }
    Serial.println("Disconnected");
  }
  delay(100);
}

void passNotification() {
  Serial.println("Running pass");
   digitalWrite(solenoidPin, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(10);               // wait for a second
   digitalWrite(solenoidPin, LOW);    // turn the LED off by making the voltage LOW
   delay(100); 
}

void failNotification() {
   Serial.println("Running fail");
   digitalWrite(solenoidPin, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(10);               // wait for a second
   digitalWrite(solenoidPin, LOW);    // turn the LED off by making the voltage LOW
   delay(250); 
   digitalWrite(solenoidPin, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(10);               // wait for a second
   digitalWrite(solenoidPin, LOW);    // turn the LED off by making the voltage LOW
   delay(250);
   digitalWrite(solenoidPin, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(10);               // wait for a second
   digitalWrite(solenoidPin, LOW);    // turn the LED off by making the voltage LOW
   delay(100);
}
