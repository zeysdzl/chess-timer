#include <TM1637Display.h>

#define CLK_PIN_DISP1 2     // CLK pin to be assigned to pin 2 (for the first display)
#define DIO_PIN_DISP1 3     // DIO pin to be assigned to pin 3 (for the first display)
#define CLK_PIN_DISP2 6     // CLK pin to be assigned to pin 6 (for the second display)
#define DIO_PIN_DISP2 7     // DIO pin to be assigned to pin 7 (for the second display)
#define BUTTON_PIN_DISP1 4  // Button pin to be assigned to pin 4 (for the first display)
#define BUTTON_PIN_DISP2 8  // Button pin to be assigned to pin 8 (for the second display)
#define BUZZER_PIN 5        // Buzzer pin to be assigned to pin 5

TM1637Display display1(CLK_PIN_DISP1, DIO_PIN_DISP1);
TM1637Display display2(CLK_PIN_DISP2, DIO_PIN_DISP2);

const unsigned long debounceDelay = 50; // Wait time for debouncing (milliseconds)
_Bool countdownActive1 = 0;
_Bool countdownActive2 = 0;
unsigned long lastButtonPressTime1 = 0;
unsigned long lastButtonPressTime2 = 0;
unsigned long startTime1 = 0;
unsigned long startTime2 = 0;
unsigned long elapsedTime1 = 0;
unsigned long elapsedTime2 = 0;
unsigned long duration1 = 30000; // 10 minutes (600000 milliseconds) (for the first display)
unsigned long duration2 = 30000; // 10 minutes (600000 milliseconds) (for the second display)

void setup() {
    pinMode(BUTTON_PIN_DISP1, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor enabled (for the first display)
    pinMode(BUTTON_PIN_DISP2, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor enabled (for the second display)
    pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as output
    display1.setBrightness(7); // Set the brightness level (0 - 7) (for the first display)
    display2.setBrightness(7); // Set the brightness level (0 - 7) (for the second display)
    countdownActive1 = 0; // Initial state of the first countdown
    countdownActive2 = 0; // Initial state of the second countdown
}

void loop() {
    // Button control for the first display
    if (digitalRead(BUTTON_PIN_DISP1) == LOW) {
        if (millis() - lastButtonPressTime1 > debounceDelay) {
            countdownActive1 = !countdownActive1;
            lastButtonPressTime1 = millis();
        }
    }

    // Button control for the second display
    if (digitalRead(BUTTON_PIN_DISP2) == LOW) {
        if (millis() - lastButtonPressTime2 > debounceDelay) {
            countdownActive2 = !countdownActive2;
            lastButtonPressTime2 = millis();
        }
    }

    // Countdown control for the first display
    if (countdownActive1) {
        elapsedTime1 = millis() - startTime1;
        unsigned long remainingTime1 = duration1 - elapsedTime1;

        int remainingMinutes1 = remainingTime1 / 60000;
        int remainingSeconds1 = (remainingTime1 % 60000) / 1000;
        int displayValue1 = (remainingMinutes1 * 100) + remainingSeconds1;

        display1.showNumberDecEx(displayValue1, 0b01000000, 1);

        if (remainingTime1 <= 8000) {
            countdownActive1 = 0;
            display1.showNumberDecEx(8888, 0b01110001, 1);
            for (int i = 0; i < 16; i++) {
                tone(BUZZER_PIN, 1000);
                delay(250);
                noTone(BUZZER_PIN);
                delay(250);
            }
            duration1 = 600000; // Reset the duration to 10 minutes (600000 milliseconds)
            startTime1 = millis();
        }
    } else {
        startTime1 = millis() - elapsedTime1;
    }

    // Countdown control for the second display
    if (countdownActive2) {
        elapsedTime2 = millis() - startTime2;
        unsigned long remainingTime2 = duration2 - elapsedTime2;

        int remainingMinutes2 = remainingTime2 / 60000;
        int remainingSeconds2 = (remainingTime2 % 60000) / 1000;
        int displayValue2 = (remainingMinutes2 * 100) + remainingSeconds2;

        display2.showNumberDecEx(displayValue2, 0b01000000, 1);

        if (remainingTime2 <= 8000) {
            countdownActive2 = 0;
            display2.showNumberDecEx(8888, 0b01110001, 1);
            for (int i = 0; i < 16; i++) {
                tone(BUZZER_PIN, 1000);
                delay(250);
                noTone(BUZZER_PIN);
                delay(250);
            }
            duration2 = 600000; // Reset the duration to 10 minutes (600000 milliseconds)
            startTime2 = millis();
        }
    } else {
        startTime2 = millis() - elapsedTime2;
    }

    delay(100);
}
