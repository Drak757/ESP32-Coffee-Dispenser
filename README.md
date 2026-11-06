# ESP32 Automatic Coffee Dispenser

An ESP32-based automatic coffee dispenser prototype that allows the user to select between Light, Medium, and Strong coffee settings.

The system uses three push buttons and an SG90 servo motor to control a dispensing gate. Each strength setting keeps the gate open for a different amount of time.

## Current Features

- Three coffee strength selections
  - Light
  - Medium
  - Strong
- Push-button user input
- SG90 servo-controlled dispensing gate
- Non-blocking timing using `millis()`
- Simple state-machine logic
- Separate 5V servo power supply with shared ground

## Strength Settings

| Setting | Dispense Time |
|---|---:|
| Light | 125 ms |
| Medium | 175 ms |
| Strong | 225 ms |

These times are currently used for testing and will be calibrated after the physical coffee hopper and gate are completed.

## Hardware

- ESP32 development board
- SG90 servo motor
- 3 push buttons
- Breadboards
- Breadboard 5V power supply module
- Jumper wires
- Cardboard prototype enclosure
- Hot glue

## Pin Connections

| Component | ESP32 Pin |
|---|---:|
| Servo Signal | GPIO 18 |
| Light Button | GPIO 19 |
| Medium Button | GPIO 21 |
| Strong Button | GPIO 22 |

### Servo Power

- Servo Red → 5V
- Servo Brown → GND
- Servo Orange → GPIO 18
- ESP32 GND and servo power supply GND share a common ground

### Buttons

Each button uses the ESP32's internal `INPUT_PULLUP` resistor.

- One side of each button → GND
- Light → GPIO 19
- Medium → GPIO 21
- Strong → GPIO 22

## How It Works

The dispenser begins in an IDLE state.

When the user presses one of the three strength buttons:

1. The ESP32 detects the selected strength.
2. The servo moves to approximately 90 degrees.
3. The dispensing gate opens.
4. The ESP32 records the starting time using `millis()`.
5. The gate remains open for the selected duration.
6. The servo returns to 0 degrees.
7. The system returns to the IDLE state.

Using `millis()` instead of `delay()` allows the ESP32 to continue running while timing the dispensing operation.

## Current State Machine

```text
        Button Press
             |
             v
        +---------+
        |  IDLE   |
        +---------+
             |
             v
     +---------------+
     |  DISPENSING   |
     +---------------+
             |
      Selected time
         expires
             |
             v
        +---------+
        |  IDLE   |
        +---------+
