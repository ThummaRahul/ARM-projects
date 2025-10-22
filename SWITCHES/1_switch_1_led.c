#include <LPC21xx.h>       // Header file for LPC21xx microcontroller

#define SW_AL 4            // Switch connected to P0.4
#define LED_AL 8           // LED connected to P0.8

int main()                // main function
{
    // Configure LED pin as output
    // IODIR0 register: 1 = output, 0 = input
    IODIR0 |= 1 << LED_AL;

    while (1) // Infinite loop to continuously check switch state
    {
        // Read switch state:
        // IOPIN0 reads all Port0 pins
        // Right shift by SW_AL to bring the switch bit to bit0
        // &1 to mask only the LSB (the switch state)
        if (((IOPIN0 >> SW_AL) & 1) == 0)  // If switch is pressed (active low)
        {
            IOCLR0 = 1 << LED_AL;         // Turn OFF the LED by clearing its pin
        }
        else                               // If switch is released
        {
            IOSET0 = 1 << LED_AL;         // Turn ON the LED by setting its pin
        }
    }
}
Explanation
Pin Definitions
SW_AL → 4 → Switch connected to P0.4.
LED_AL → 8 → LED connected to P0.8.

Configure LED as Output

IODIR0 |= 1 << LED_AL; sets only P0.8 as output.

Other pins remain unaffected because of |=.

Reading the Switch

IOPIN0 gives the current state of all Port0 pins.

(IOPIN0 >> SW_AL) & 1 isolates the switch pin value.

Many boards have active-low switches:

Pressed → 0

Released → 1

Controlling the LED

IOSET0 = 1 << LED_AL; → Makes P0.8 high → LED ON

IOCLR0 = 1 << LED_AL; → Makes P0.8 low → LED OFF

Looping

while(1) continuously monitors the switch and updates the LED in real time.
