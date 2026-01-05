# ENVIRO\_CLOCK

## PROJECT OVERVIEW:

The Enviro Clock is a real-time embedded system application designed using an ARM7-based LPC2148 microcontroller.
It continuously displays real-time clock information along with ambient temperature on a 16×2 LCD.
The system supports interrupt-driven, menu-based configuration for editing RTC parameters and setting an alarm.
Visual feedback such as scrolling menus and an alarm indication symbol enhances user interaction.

## PURPOSE:

To display real-time time, date, day, and temperature continuously.
To provide a menu-driven interface for editing RTC information using an external interrupt.
To allow users to configure and enable an alarm with visual indication on the LCD.
To demonstrate ADC, RTC, interrupt handling, and keypad interfacing in embedded systems.

## MAIN FEATURES:

Real-time display of time (HH\:MM\:SS).
Real-time display of date and day.
Ambient temperature display using LM35 sensor.
ADC-based temperature measurement.
External interrupt-based menu activation.
Scroll-enabled LCD menu navigation.
RTC editing with ordered parameter selection.
Alarm configuration with visual alarm symbol on LCD.

## HARDWARE COMPONENTS:

LPC2148 ARM7 Microcontroller,
RTC Module (internal / external as configured),
LM35 Temperature Sensor,
16×2 Character LCD,
4×4 Matrix Keypad,
External Interrupt Push Button,
LED / Buzzer (for alarm indication)

## TEMPERATURE MEASUREMENT (LM35):

```
  The LM35 temperature sensor provides an analog output proportional
  to ambient temperature at a scale of 10 mV per °C.

  This analog voltage is connected to the ADC input of the LPC2148.
  The ADC continuously samples the sensor output, converts it into
  a digital value, and computes the temperature in degrees Celsius.

  The calculated temperature is displayed in real time on the LCD
  along with the clock information.
```

## MENU STRUCTURE & FUNCTIONALITY:

NORMAL MODE:
\- LCD continuously displays RTC time, date, day, and temperature.

```
Example:
    07:24:10   T:30°C
    28/10/25   THU
```

INTERRUPT MODE:
\- Triggered by pressing the external interrupt key.
\- Scroll-enabled menu appears on LCD.

```
    1. Edit RTC Info
    2. Set Alarm
    3. Exit
```

OPTION 1: EDIT RTC INFO
\- Opens RTC configuration menu.
\- Parameters are edited in the following fixed order:

```
    H  → Hour
    M  → Minute
    S  → Second
    D  → Date
    D  → Day
    M  → Month
    Y  → Year
    E  → Exit

- Values are modified using the keypad.
- Updated values are written back to the RTC.
```

OPTION 2: SET ALARM
\- Opens alarm configuration menu:

```
    1. Set Hour
    2. Set Minute
    3. Exit

- Alarm hour and minute can be configured.
- System continuously compares RTC time with alarm time.
```

OPTION 3: EXIT
\- Returns system to normal display mode.

## ALARM INDICATION:

```
  When the alarm is enabled, an alarm indication symbol is displayed
  on the LCD alongside the real-time clock information.

  When the alarm time matches the RTC time, the alarm is triggered.
  During alarm triggering:
    - The alarm symbol is animated such that the two outer wings
      of the symbol blink periodically.
    - A buzzer is activated simultaneously to provide an audible alert.

  The blinking wings provide a clear visual indication of an active
  alarm, synchronized with the buzzer sound.
```

## APPLICATIONS & SOCIAL USEFULNESS:

The Enviro Clock is useful in various real-world and societal applications where
accurate timekeeping, temperature monitoring, and alert mechanisms are required.

- Can be used in **homes and offices** to monitor time and room temperature.
- Helpful in **elderly care and patient monitoring systems** for timely alerts.
- Useful in **educational institutions and laboratories** for environment-aware timing.
- Can act as a **reminder and alert system** in industrial or workplace environments.
- Suitable for **embedded learning platforms** to demonstrate real-time systems.

## FUTURE SCOPE:

The Enviro Clock project can be further enhanced with additional features to make it
more intelligent, connected, and industry-ready.

- Integration of **wireless communication** (Wi-Fi / Bluetooth) for remote monitoring.
- Addition of **multiple alarms and scheduling features**.
- Data logging of temperature and time using **external memory or SD card**.
- Mobile or web application integration using **IoT platforms**.
- Upgrade to **graphical LCD or TFT display** for richer user interface.
- Power optimization and battery backup for **portable applications**.

  When the alarm is enabled, an alarm indication symbol is displayed
  on the LCD alongside the real-time clock information.

  When the alarm time matches the RTC time, the alarm is triggered.
  During alarm triggering:
    - The alarm symbol is animated such that the two outer wings
      of the symbol blink periodically.
    - A buzzer is activated simultaneously to provide an audible alert.

  The blinking wings provide a clear visual indication of an active
  alarm, synchronized with the buzzer sound.
```

When the alarm is enabled, an alarm indication symbol is displayed
on the LCD alongside the real-time clock information.

This symbol provides a clear visual confirmation that the alarm
has been set and is active.

```

 SAMPLE DISPLAY:
----------------

  LCD NORMAL DISPLAY
      07:24:10   T:30°C
      28/10/25   THU

  LCD DISPLAY (ALARM ENABLED)
      07:24:20   T:30°C 
      28/10/25   THU  ⟪⏰⟫

  LCD DISPLAY (ALARM TRIGGERED)
      07:30:00   T:30°C  
      28/10/25   THU  ⟪⏰⟫  (wings blinking)

 INSTALLATION STEPS:
--------------------

  SET UP TOOLCHAIN:
    -> Keil µVision or any compatible Embedded C IDE.

  HARDWARE CONNECTIONS:
    -> Connect LCD to LPC2148 GPIO pins.
    -> Connect LM35 output to ADC input pin.
    -> Connect keypad rows and columns to GPIO pins.
    -> Connect external interrupt switch to interrupt pin.

  BUILD & FLASH:
    -> Compile the source code.
    -> Flash the generated binary to the target board.

  START & TEST:
    -> Power ON the system.
    -> Verify RTC, temperature display, menu navigation, and alarm.

 USAGE INSTRUCTIONS:
---------------------
```

Step 1: Power ON the board.
LCD shows real-time clock and temperature.

Step 2: Press external interrupt key.
Menu window appears with scrolling enabled.

Step 3: Select "Edit RTC Info" to modify time/date parameters
in the order (H, M, S, D, D, M, Y, E).

Step 4: Select "Set Alarm" to configure alarm hour and minute.

Step 5: Alarm symbol appears on LCD when alarm is enabled.

Step 6: Select "Exit" to return to normal display mode.

```

 DEPENDENCIES:
---------------
```

Embedded C standard libraries
LPC2148 peripheral libraries
ADC, GPIO, RTC, and Interrupt drivers

```

 REFERENCES:
-------------
```

NXP LPC212x User Manual
LM35 Temperature Sensor Datasheet
ARM7TDMI Technical Reference Manual

```

 AUTHOR:
---------
  SILIVERU HARI KRISHNA
  Embedded Systems Engineer

```
