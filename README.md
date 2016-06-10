Using MSP430 for door alarm timer

                  MSP430G2230
               -----------------  3.7 Li-ion battery
              |                 |  |
              |   ADC10 -> Vcc  |--- ..
              |                 |     \\
              |            P1.6 |-----|<1---| LED
              |                 |
              |            P1.5 |-----|o|---| Buzzer
              |                 |
              |                 |
              |            P1.2 |----_ \_----
              |                 |     SW   _|_
              |                 |           _  GND
               -----------------
                     SO-8

Description: If door (SW) not closed the LED is blinking every 2 sec, the alarm buzzer will XOR every 10 minutes.

