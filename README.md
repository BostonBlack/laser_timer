The laser timer program and all asocciated files can be found at https://github.com/BostonBlack/laser_timer

**note:** This documentation assumes the ERROR418 - Wednesday Group C board is being used and the gates are similar to those used in the 2024 competition

## Setup

### Wiring
Both LDR sensors should be plugged into the microcontroller, the Vout lines should be plugged into analog input pins. If using an ATMega 4808 the code is configured to use PD6 and PD7. Try to minimise the distance wire has to travel between the two sensors.

the XC4490 lasers require 5V power. This can can be supplied either by a line to the microcontroller or, if space for the robots is a concern, batteries. 

**Warning!** If power is supplied using 4 AA rechargable batteries, they will need to be replaced after around 2.5 hours or the lasers become too dim to reliably stop the gates triggering.

### Placement
It is recommended that the laser module be placed internally on the board and the sensor modules towards the edge. This is becuse the laser module can be driven by batteries while the sensor modules must be wired presenting a potential hazard to the robots and gates.

The start gate can be placed anywhereas long as the laser crosses the line at the starting point, once the laser is crossed to start the timer it doesnt matter how often it is crossed.

The end gate should be placed such that the laser crosses the line only once at the finish. If it crosses the line at any other point the timer will finish early.

Ensure enough room is left for the robots and consider that some robots may not be following the line very well...

### Code
Ensure that the threshold set is correct for the light conditions and laser being used. DEBUG can be set to true to print the sensor values and help decide what the threshold should be. It is recommended for readability that VERBOSE be set to false when doing this.

DEBUG should be set to false when using the gates for timing

Ensure the correct pins are set for the sensors

When VERBOSE is set to true the time will be constantly printed out while the timer is running, this will slightly slow the response time of the gates as serial printing takes some time. If VERBOSE is set to false the timer will print `Timer active...` when the start gate is triggered then will not print anything else. When the end gate is triggered the final time will be printed as well as `Timer stopped.`

## Operation
To ensure the gates and timer are working as expected, pass your hand throught the start then end gate. A time should be printed out.

Before timing a run ensure that the timer is off. This can be done by observing the debug LED, if the LED is on then the timer is on, or by simply passing a hand through the end gate.

When placing the robot on the line at the start take care that hands or arms do not trigger the start or end gates. 

Once the robot has finished the course ensure it does not then trigger the start gate again as this will restart the timer. If VERBOSE is true this will make it difficult to recover the previous time as new times will flood the serial monitor. If this does occur, trigger the end gate by passing your hand through it, then scroll up till the next `-----Finish Time-----` is reached.