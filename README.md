# GamepadToUSB
Uses an Arduino Pro Micro, but could probably use anything with an ATmega32U4.

Acts as a USB gamepad and accepts original NES, N64 and Genesis (Mega Drive) controllers as input. Why those? Because its what I have. See [schematic](Schematic.pdf) for wiring details.

#### Uses libraries:
* https://github.com/MHeironimus/ArduinoJoystickLibrary
* https://github.com/jonthysell/SegaController
* https://github.com/NicoHood/Nintendo (available via Library Manager)