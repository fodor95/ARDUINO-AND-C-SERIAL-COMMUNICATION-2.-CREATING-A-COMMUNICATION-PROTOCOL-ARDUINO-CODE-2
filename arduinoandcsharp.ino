//variables for receiving data
String inputString = "";         
bool stringComplete = false;  

//string what is going to be sent back to PC
String responseToPc = "";

void setup() {
  Serial.begin(345600);
  Serial.setTimeout(50);
  inputString.reserve(200);
}

void loop() {
  //if the string is completed, than generate a response
  if (stringComplete) {
    
    //read up some analog value, it doesn`t really matter now what
    int readAnalog0 = random(0, 50000);
    
    //Generate the response
    //the first part of the message is the checksum
    responseToPc = calculateChecksum(String(readAnalog0));
    
    //the checksum and the message is going to be separated by ":" character
    responseToPc += ":";
    
    //this is the data what the arduino is sending
    responseToPc += String(readAnalog0);
   // delay(1000);
    //send the package to PC
    Serial.println(responseToPc);
   
    //reset receiving variables
    inputString = "";
    stringComplete = false;
  }
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
      inputString += inChar;
    //ending char, by default newline, can be anything  
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


int calculateChecksum(String dataIn){
//this is the function which is used to generate the checksum

  int lengthOfData = dataIn.length();
  
  int sum = 0;
  int character = 0;

  //calculate the checksum as represented and explained before
  for(int i = 0; i < lengthOfData; i++){
    character = (int)dataIn.charAt(i);
    sum += (character * (i+1));
    }

  //returning the checksum 
  return sum%1001;
  
}
