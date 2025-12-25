# Chess Timer (Arduino + 2× TM1637)

A simple two-player chess timer built with **Arduino Uno** and **two TM1637 4-digit 7-segment displays**.  
Each player has a dedicated button to start/stop their own countdown. When the remaining time reaches a critical threshold, a buzzer alert is triggered and `8888` is displayed.

> This project is implemented as a **course project / prototype**.  
> Classic chess clock behavior (one player’s button stopping their own timer and starting the opponent’s timer) is listed as a future improvement.

---

## Hardware Components

- Arduino Uno
- 2× TM1637 4-digit 7-segment display
- 2× Push button (using `INPUT_PULLUP`)
- 1× Buzzer
- Breadboard and jumper wires

---

## Pin Connections

| Component | Arduino Pin |
|---|---:|
| Display 1 CLK | D2 |
| Display 1 DIO | D3 |
| Display 2 CLK | D6 |
| Display 2 DIO | D7 |
| Button 1 | D4 |
| Button 2 | D8 |
| Buzzer | D5 |

### Button Wiring (Important)
Buttons are configured using `INPUT_PULLUP`, so they must be wired **active LOW**  
(button pressed → connected to GND).

---

## Circuit Diagram

![Circuit Diagram](media/images/circuit.jpg)

---

## Software Setup

1. Install **Arduino IDE**.
2. Install the **TM1637Display** library via Library Manager.
3. Open `chess_timer.ino`.
4. Select **Arduino Uno** as the board and upload the sketch.

---

## Usage

- Press **Player 1 button** to start/stop Display 1 timer.
- Press **Player 2 button** to start/stop Display 2 timer.
- When the remaining time drops below the defined threshold,  
  the buzzer sounds and `8888` is shown on the display.

---

## Changing the Timer Duration

Durations are defined in milliseconds:

- 10 minutes → `600000`
- 5 minutes → `300000`
- 30 seconds (testing) → `30000`

You can modify these values directly in the source code.

---

## Demo Video

The demo video is included directly in this repository:

📁 `media/demo.mp4`

> GitHub does not embed videos inside README files.  
> Download the file to watch the demo locally.

---

## Known Limitations

- Both timers can run simultaneously.
- Button debouncing is basic and can be improved.
- Classic chess clock logic (automatic opponent switch) is not yet implemented.

---