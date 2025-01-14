<!-- Please do not change this logo with link -->

<a target="_blank" href="https://www.microchip.com/" id="top-of-page">
   <picture>
      <source media="(prefers-color-scheme: light)" srcset="images/mchp_logo_light.png" width="350">
      <source media="(prefers-color-scheme: dark)" srcset="images/mchp_logo_dark.png" width="350">
      <img alt="Microchip Technologies Inc." src="https://www.microchip.com/content/experience-fragments/mchp/en_us/site/header/master/_jcr_content/root/responsivegrid/header/logo.coreimg.100.300.png/1605828081463/microchip.png">
   </picture>
</a>

# Stepper Motor Board Firmware

<img src="images/Stepper_Angled_Back" width="350"><img src="images/Board_Itself" width="350">

This repository contains an example to generate steps via function generator with the stepper driver reference design. This design is based on the Multiphase Power Board, the original code example is linked in related documentation.

## Full-Step Mode

In Full-Step mode, the motor rotates complete mechanical steps at once - for a standard 200 full-steps/revolution stepper motor, this would be 1.8 degrees for a sub-step. The motor's two coils are powered sequentially in four full-steps. The sequence determines the stepper motor's direction of rotation. Full-Step mode is simple to control, but can cause vibration and noise due to the larger step angle. Another drawback of using this mode is that the stepper motor's current consumption is at the highest level, having the lowest efficiency. This mode is often used in applications where the drive algorithm simplicity is more important than the smoothness of operation or precision.

## Half-Step Mode

In Half-Step mode, four extra steps are inserted between the four initial full-steps, which makes the stepper motor rotate by half of its full-step angle. This effectively doubles the number of mechanical steps per revolution - for a standard 200 full-steps/revolution stepper motor, this would be 0.9 degrees for a complete step, resulting in a smoother operation and less vibration compared to the Full-Step mode.
The benefits of having a balance between simplicity, efficiency, smoothness of operation and a lower current consumption outweigh the increased complexity of the control algorithm needed for this mode. It also provides double resolution of the Full-Step mode.

## MicroStep Mode

The Microstep mode divides the full-step angle into even smaller steps, providing even smoother operation and higher precision. The number of microsteps per full-step can vary, but common values are 8, 16, 32, or even 256 microsteps per full-step. Even though this mode requires the most complex control algorithms, the current consumption is lower than in Full-Step and Half-Step modes, providing the highest precision, the least vibration and less noise. Microstep mode is often used in applications where precision and smoothness of operation are paramount, such as in CNC machines.

## Related Documentation

- [AVR<sup>®</sup> EB Product Page](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus/avr-eb?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bipolar-stepper-motor-drive-github&utm_bu=MCU08)
- [AVR<sup>®</sup> EB Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=AVR16EB32)
- [AVR<sup>®</sup> EB Stepper Example Code on GitHub](https://github.com/microchip-pic-avr-examples/avr16eb32-bipolar-stepper-motor-drive/tree/main)

## Software Used

- [MPLAB® X IDE v6.20 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bipolar-stepper-motor-drive-github&utm_bu=MCU08)
- [AVR-Ex DFP-2.10.205 or newer Device Pack](https://packs.download.microchip.com/)
- [MPLAB® XC8 compiler v3.00](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bipolar-stepper-motor-drive-github&utm_bu=MCU08)
- [MPLAB® Code Configurator (MCC) v 5.5.0](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bipolar-stepper-motor-drive-github&utm_bu=MCU08)

## Hardware Used

- [AVR<sup>®</sup> EB Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV73J36A?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-EB&utm_content=avr16eb32-bipolar-stepper-motor-drive-github&utm_bu=MCU08)
- Stepper Driver Board
- Motor used in the application: XY42STH34-035A Stepper Motor, but not mandatory
- A Voltage Power Supply (6-50V and 1-3A current capability, depending on the chosen motor)

## Functionaility

**The first application** is replicating common stepper driver ICs. By utilizing the `STEP` and `DIR` pins a user can control the speed and direction of a stepper motor by using a function generator. There is also an onboard potentiometer for current control. 

In the main loop, the EB monitors the Step pin for any impulses, which will trigger an if statement to determine the motor's direction, controlled by the DIR pin. The current control is managed by a CCL-controlled comparator poll.

**The second application** is an updated version of this [demo](https://github.com/microchip-pic-avr-examples/avr16eb32-bipolar-stepper-motor-drive/tree/main/3_Full-Ramp) to better fit the board.

## Configuration

**Note:** For a standard 200 full-steps/revolution stepper motor, 1.8 mechanical degrees represent 360 electrical degrees (360 electrical degrees/200-steps is 1.8 mechanical degrees).

Configuration is set up in the `stepper.h` files  

There are a few motor specific options that need to be addressed when swapping motors

`R`: motor winding resistance expressed in [ohm]

`I_OUT`: Motor Peak Current expressed in [mA]

to change the stepping mode, uncomment the corresponding macro in `stepper.h`

<img src="images/STEPPING MODE.png">

## Setup
This project can be replicated in MCC, with the exception of the `stepper.h` and `stepper.c` files, these will have to be imported from this project.

### INTERRUPT

<img src="images/interrupt00.png">

- Global Interrupts Enable: Enabled

### CLKCTRL

<img src="images/clkctrl00.png">

- Prescaler enabled: Disabled

### ADC

<img src="images/adc01.png">
<img src="images/adc02.png">

- Sample Duration : 255
- ADC Enable: Enabled
- Left Adjust: Enabled 
- Start command: Start a conversion immediately.
- Free Running: Enabled
- ADC Positive Channel Selection: ADC Input 20
- ADC Negative Channel Selection: Ground

### AC0

<img src="images/ac00.png">

- Positive input MUX Selection: Positive Pin 4
- Negative input MUX Selection: Negative Pin 3

### AC1

<img src="images/ac01.png">

- Positive input MUX Selection: Positive Pin 6
- Negative input MUX Selection: Negative Pin 3

### BOD

<img src="images/bod01.png">

- BOD Operation in Active Mode: Enabled in continuous mode
- BOD Level: 2.7 V
- BOD Operation in Sleep Mode: Disabled

### CCL


<img src="images/ccl00.png">
<img src="images/ccl_overview.png">

- Enable CCL: Enabled

*For LUT0* -Connect the LUT as above, and edit the LUT configurations.

<img src="images/lut01.png">

<img src="images/lut00.png">

- Enable LUT: Enabled
- Clock Selection: OSCHF
- Gate Type: OR

### TCE

<img src="images/TCE0.png">
<img src="images/TCE1.png">
<img src="images/TCE2.png">

- Timer Enable: Enabled
- Waveform Generation Mode: SINGLESLOPE
- Scaling Mode: BOTTOM
- Amplitude Control Enable: Enabled
- Generate ISR: Enabled
- Overflow Interrupt Enable: Enabled

### WEX

<img src="images/WEX0.png">
<img src="images/WEX1.png">
<img src="images/WEX2.png">

- Global Override Settings for Waveform Outputs : All outputs enabled
- Deadtime inserion Channel 0-3: Enabled
- Requested Dead-time Low Side: 0.2us
- Requested Dead-time High Side: 0.2us
- Fault Input A Enable: Enabled
- Fault Event Input A Blanking Enable: Enabled

### EVSYS

<img src="images/evsys.png" width ="750">

- (Generators):Channel 1 CCL_LUT0 -> 

- (Channels):Channel 1 -> 

- (Users):WEX A


### PIN MANAGER

<img src="images/pin_manager00.png" width ="750">

## Operation

There are a few notes to be made about the operation of the board. The original code was intended for multiple steps being taken, so doing 1 step causes some functions to be less than suitible for the application, such as `SPEED_LIMIT` and `STEPS_TO_SUBSTEP` These variables are given a default value, but can still be changed but comes with a significant performance decrease, this only goes for the function generator example.
  
## Results

<img src="images/ex1.gif" width="350">

This GIF shows the stepper motor hooked up to a function generator. The GIF also shows the LED and direction change made by the DIR pin being set.

<img src="images/ex2.gif" width="350">

This GIF shows the second example, which has the motor change its speed and direction via software. The speed and steps can be changed in software.
