
// Necessary Libraries to run the Matrix Diasplay
#include <Adafruit_Protomatter.h>
#include <string.h>

// Setup of Matrix Pins for usage, self-documenting code
uint8_t rgbPins[]  = {7, 8, 9, 10, 11, 12};
uint8_t addrPins[] = {17, 18, 19, 20};
uint8_t clockPin   = 14;
uint8_t latchPin   = 15;
uint8_t oePin      = 16;

// Testing Parameters and values ("status0")
uint16_t tek_color = 0x07FF; //Cyan
uint16_t CursorposX = 0x0006;
uint16_t CursorposY = 0x000B;
String tek_message = "TEKTRONIX";

// GREEN "AVAILABLE" STATUS ("status1")
uint16_t available_color = 0x07E0;
String available_message = "AVAILABLE";

// RED "BUSY" STATUS ("status2")
uint16_t busy_color = 0xF800;
uint16_t busy_textsize = 2;
uint16_t busy_xpos = 0x0009;
uint16_t busy_ypos = 0x0009;
String busy_message = "BUSY";

// ORANGE "AWAY" STATUS ("status3")
uint16_t away_color = 0xFC00;
uint16_t away_textsize = 2;
uint16_t away_xpos = 0x0009;
uint16_t away_ypos = 0x0009;
String away_message = "AWAY";

// RED "IN MEETING" STATUS ("status4")
uint16_t inmeeting_color = 0xF800;
uint16_t inmeeting_textsize = 1;
uint16_t inmeeting_xpos = 0x000B;
uint16_t inmeeting_ypos = 0x0009;
String inmeeting_message = "IN\n  MEETING";

// CYAN "MUSIC/POD" STATUS ("status5")
uint16_t musicpod_color = 0x07E0;
uint16_t musicpod_textsize = 1;
uint16_t musicpod_xpos = 0x000B;
uint16_t musicpod_ypos = 0x0009;
String musicpod_message = "MUSIC OR\n  PODCAST";

// MISC variables

// creating 1 Protomatter object for the LED Matrix Display (64x32 LED pixels)
Adafruit_Protomatter displaymatrix(64, 4, 1, rgbPins, 4, addrPins, clockPin, latchPin, oePin, false);

// functions //

void Display_to_matrix(uint16_t tcolor, uint16_t xpos, uint16_t ypos, String m, uint16_t textsize=1){
  displaymatrix.setTextWrap(true);
  displaymatrix.setTextColor(tcolor);
  displaymatrix.setCursor(xpos, ypos);
  displaymatrix.setTextSize(textsize);
  displaymatrix.println(m);
  displaymatrix.show();
}


void setup() {
  // Start the Protomatter Driver and check for PROTOMATTER_OK
  ProtomatterStatus status = displaymatrix.begin();
  if(status != PROTOMATTER_OK){for(;;);}

  Serial.begin(115200); // setup the baud rate for testing with Serial Monitor

  // Quick test and Intialization of Matrix Display
  Display_to_matrix(tek_color, CursorposX, CursorposY, tek_message);
  delay(3000);

  // Clear the matrix
  displaymatrix.fillScreen(0x0000);
  displaymatrix.show();

}

void loop() {
  if (Serial.available() > 0) {

    // Erase the matrix display
    displaymatrix.fillScreen(0x0000);

    // Read the input string from the serial monitor
    String str_input = Serial.readStringUntil('\n');

    // Convert the string input to an integer.
    long status_int = strtol(str_input.c_str(), NULL, 10);

    // Switch Statement based on serial monitor input
    switch (status_int) {
      
      case 0: // TEKTRONIX
        Display_to_matrix(tek_color, CursorposX, CursorposY, tek_message);
        break;
      
      case 1: // AVAILABLE
        Display_to_matrix(available_color, CursorposX, CursorposY, available_message);
        Serial.println("AVAILABLE");
        break;

      case 2: // BUSY
        Display_to_matrix(busy_color, busy_xpos, busy_ypos, busy_message, busy_textsize);
        break;

      case 3: // AWAY
        Display_to_matrix(away_color, away_xpos, away_ypos, away_message, away_textsize);
        break;
      
      case 4: // IN MEETING
        Display_to_matrix(inmeeting_color, inmeeting_xpos, inmeeting_ypos, inmeeting_message);
        break;

      case 5: // MUSIC or PODCAST
        Display_to_matrix(musicpod_color, musicpod_xpos, musicpod_ypos, musicpod_message);
        break;

      default:
        displaymatrix.fillScreen(0x0000);
        displaymatrix.show();
    }

  }
}
