# casa0016
 Smart Arduino-Based Lighting System

## Project Background
This Arduino-based smart lighting project is focused on creating an adaptive and energy-efficient lighting solution for indoor environments. It leverages various sensors to intelligently respond to changes in ambient light, temperature, and sound, enhancing user comfort and promoting sustainable living.

## Development Environment
- **IDE**: Arduino IDE
- **Hardware**: Arduino Uno, NeoPixel LED Strip, DHT22 Sensor, PIR Motion Sensor, LDR, Sound Sensor
- **Language**: C/C++ for Arduino
- **Design Tools**: CAD for enclosure, Soldering tools for stripboard assembly

|components | pictures | 
| ------- | ------- | 
| arduino Uno R3   |  <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/ARDUINO.jpg" alt="图片2">  |
| BUTTON   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/BUTTON.jpg" alt="图片2">   |
| DHT22  | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/DHT22.jpg" alt="图片2">   |
| LDR SENSOR   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/LDR.jpg" alt="图片2">   |
| LED_STRIPS   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/LED_STRIP.jpg" alt="图片2">   |
| PIR SENSOR   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/PIR.jpg" alt="图片2">   |
| PKANKS   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/Planks%20for%20laser%20cutting.jpg" alt="图片2">   |
| CAPACITOR  | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/capacitor.jpg" alt="图片2">   |
| JUMP_WIRE  | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/jump_wire.jpg" alt="图片2">   |
| SOUND SENSOR   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/sound_sensor.jpg" alt="图片2">   |
| STRIPBOARD   | <img src="https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/stripboard.jpg" alt="图片2">   |

## Development Process
The development involved initial prototyping on a breadboard, with iterative coding and testing phases.
### Prototype on Breadboard

Here is an image of the initial prototype of our smart lighting system assembled on a breadboard:

![Prototype on Breadboard]( https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/prototype_on_board.png)

*Description*: This image shows the early stage of our project where the components like the Arduino Uno, NeoPixel LED strip, and various sensors were first assembled on a breadboard for testing and development purposes.

The system has two functions, which are switched by a switch. The first mode will first detect the surrounding light intensity, if the surrounding light intensity is too high will not light up, if the light intensity is low will light up, after the light will detect whether there is human activity around, after a period of time no human activity will be detected will gradually reduce the intensity of the light to 10%; the colour of the light will be mapped to the temperature, the low temperature warm tones, the high temperature cold tones. In addition, in one mode, the light will automatically switch off whenever the light intensity is too high. In the second mode, the light will stay on, but the light intensity will change according to the intensity of the surrounding sound.

Features developed include:
- Motion-activated lighting
- Sound-responsive light adjustment
- Temperature-based color change

The final design was assembled on a stripboard with a custom laser-cut enclosure.

![Prototype on stripboard]( https://github.com/liangleiliu-lab/casa0016/blob/main/pictures/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20240110143847.jpg)

## Product Features
- **Adaptive Brightness**: Auto-adjusts based on ambient light levels.
- **Motion-Activated Lighting**: Responds to occupancy for energy efficiency.
- **Color Temperature Adjustment**: Changes hues with room temperature.
- **Sound-Responsive Mode**: Alters light intensity with ambient sound.
- **Eco-Friendly**: Designed with energy conservation in mind.
## Video Demonstrations

### PIR and LDR Functionality
This video showcases the system's light and motion detection capabilities:
- Low ambient light triggers the light to turn on.
- Absence of motion leads to dimming the lights.
- Detection of motion brightens the lights again.
- High ambient light turns the lights off.
Please click on the image to get a video of the test.

[![PIR and LDR Functionality](https://github.com/liangleiliu-lab/casa0016/blob/main/test_presentation/383fad217de8e0ed550265989b889f2f.jpg)](https://github.com/liangleiliu-lab/casa0016/blob/main/test_presentation/383fad217de8e0ed550265989b889f2f.mp4)

### Temperature-Induced Color Change
Watch how the light color changes with temperature variations using a heat gun
Please click on the image to get a video of the test

[![Temperature-Induced Color Change](https://github.com/liangleiliu-lab/casa0016/blob/main/test_presentation/41a0a2142cf68fdd3831e19f4db4e728.jpg)](https://github.com/liangleiliu-lab/casa0016/blob/main/test_presentation/41a0a2142cf68fdd3831e19f4db4e728.mp4)

## Future Work
- **Outdoor Adaptation**: Incorporating weatherproof features and solar power.
- **Enhanced User Interface**: Developing an intuitive control application.
- **Analytics Feature**: Adding usage data analysis for further efficiency.


