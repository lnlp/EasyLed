# EasyLed

EasyLed is an Arduino library that makes controlling standard LEDs easy.

Use simple logical functions like led.on(), led.toggle(), led.flash(), led.isOff() and more.
Helps to write clean code that is easy to read and understand. No more fuss with pinMode(), digitalWrite(), HIGH and LOW.

For example, to switch on a LED simply use led.on(). Straightforward to use and it's clear what it does.
Easier and much more clear than digitalWrite(LED_PIN, LOW) which makes you wonder if it switches the LED On or Off.



### Constructor

```cpp
EasyLed(
    const uint8_t pin,                      // GPIO pin to which the LED is connected.
    const ActiveLevel activeLevel,          // The logic level when the LED is on.
    const State initialState = State::Off,  // Optional, default is off.
    const uint8_t pinmode = OUTPUT          // Optional, default is OUTPUT, some Arduino cores
)                                           // also support OUTPUT_OPEN_DRAIN which can be
                                            // optionally specified here.         
```   


### Enumeration types

```cpp
enum class State {Off, On};
enum class ActiveLevel {Low = LOW, High = HIGH};
```


### Functions

```cpp
void on()                                   // Switch LED on

void off()                                  // Switch LED off

void toggle()                               // Toggle LED state.

void flash(                                 // Flash LED (all parameters are optional)
    const uint8_t  count = 2,               // Number of flashes
    const uint16_t onTimeMs = 160,          // on-time duration in milliseconds
    const uint16_t offTimeMs = 160,         // off-time duration in milliseconds
    const uint16_t leadOffTimeMs = 200,     // off-time duration before first flash
    const uint16_t trailOffTimeMs = 300     // off-time duration after last flash
                                            // lead and trail time are only used when LED is on
)

bool isOn()                                 // Returns true if LED is on, false otherwise

bool isOff()                                // Returns true if LED is off, false otherwise

EasyLed::State getState()                   // Returns the current state (On or Off)

void setState(EasyLed::State state)         // Sets the current state

uint8_t pin()                               // Returns the GPIO pin number as specified in constructor

EasyLed::ActiveLevel activeLevel()          // Returns the active-level as specified in constructor
```

### Included examples

- `led-basics.ino` - Shows basic use
- `led-advanced.ino` - Shows more advanced use
- `led-state.ino` - Shows how to save and restore state
- `led-activelevel-tester.ino` - Helps determine if LED is active-low or active-high


### Simple code example

```cpp
#include "EasyLed.h"

EasyLed led(LED_BUILTIN, EasyLed::ActiveLevel::Low);

void setup() 
{
    ...
}  

void loop() 
{ 
    readSensors();

    led.on();
    transmitSensorData();
    led.off();
}
```
