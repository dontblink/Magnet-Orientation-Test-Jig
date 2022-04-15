using these neopixels: 
https://www.amazon.com/Lighting-Modules-Breadboard-Friendly-NeoPixel/dp/B011O9UW9E/ref=sr_1_7?crid=9K0ZOLF0A696&keywords=neopixel+adafruit&qid=1649989761&sprefix=neopixel+adafruit%2Caps%2C107&sr=8-7

and these hall effect sensors:
https://www.amazon.com/Sensor-Linear-Effect-Sensitivity-Detection/dp/B09BJC64NM/ref=sr_1_4?crid=16GKQSF3ZD401&keywords=hall+effect+sensor&qid=1649989940&sprefix=hall+effect+sensor%2Caps%2C133&sr=8-4

LEDs will turn green if the corresponding hall effect sensor is sensing a magnet in the correct orientation, turn red if it's the wrong orientation,
and be completely off if it senses nothing.
South sensing hall effect sensors are on A0, A1, A4, A5
North sensing hall effect sensors are on A2, A3

maybe the worst schematic editor i've ever used, but here's the gist: hall effect sensors powered by 3V3, inputs on A0-A5
neopixels powered by 5V, connect pin 6->in, then daisy chaining out to in and 5V/GND on subsequent neopixels
![image](https://user-images.githubusercontent.com/1450612/163510074-578d6792-9956-41c2-96b7-4a4864449bd1.png)
