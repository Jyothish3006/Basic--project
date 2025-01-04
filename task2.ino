#include <LedControl.h>

// Create a LedControl instance
// Parameters: DIN pin, CLK pin, CS pin, number of matrices
LedControl lc = LedControl(11, 13, 10, 1);

// Character set for scrolling text (A-Z, 0-9, space, symbols)
byte alphabet[][8] = {
  {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00}, // A
  {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00}, // B
  {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00}, // C
  {0x00, 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00}, // D
  {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00}, // E
  {0x00, 0x7F, 0x48, 0x48, 0x48, 0x40, 0x00, 0x00}, // F
  // Add more characters here if needed
};

// Function to display a character on the matrix
void displayChar(byte character[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, character[row]);
  }
}

// Function to scroll a message
void scrollMessage(String message) {
  int len = message.length();
  for (int i = 0; i < len; i++) {
    char c = message[i];
    if (c >= 'A' && c <= 'F') {
      displayChar(alphabet[c - 'A']);
    } else {
      // Display blank for unsupported characters
      byte blank[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      displayChar(blank);
    }
    delay(500); // Pause between characters
  }
}

void setup() {
  lc.shutdown(0, false);    // Wake up the LED matrix
  lc.setIntensity(0, 8);    // Set brightness (0 to 15)
  lc.clearDisplay(0);       // Clear the display
}

void loop() {
  String message = "HELLO";
  scrollMessage(message);
  delay(1000);
}
