#include <LPC21xx.h>

// Define switch pins
#define SW0 4   // Switch connected to P0.4
#define SW1 5   // Switch connected to P0.5
#define SW2 6   // Switch connected to P0.6
#define SW3 7   // Switch connected to P0.7

// Define LED pins
#define LED0 8  // LED connected to P0.8
#define LED1 9  // LED connected to P0.9
#define LED2 10 // LED connected to P0.10
#define LED3 11 // LED connected to P0.11

int main()
{
    // Configure LED pins as outputs
    // IODIR0 sets direction for Port0 pins: 1 = Output, 0 = Input
    IODIR0 |= (1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3);

    while (1) // Infinite loop
    {
        // -----------------------
        // Control LED0 with SW0
        // -----------------------
        if (((IOPIN0 >> SW0) & 1) == 0) // If switch is pressed (logic 0)
            IOCLR0 = 1 << LED0;          // Turn OFF LED0
        else                            // If switch is not pressed (logic 1)
            IOSET0 = 1 << LED0;          // Turn ON LED0

        // -----------------------
        // Control LED1 with SW1
        // -----------------------
        if (((IOPIN0 >> SW1) & 1) == 0)
            IOCLR0 = 1 << LED1;
        else
            IOSET0 = 1 << LED1;

        // -----------------------
        // Control LED2 with SW2
        // -----------------------
        if (((IOPIN0 >> SW2) & 1) == 0)
            IOCLR0 = 1 << LED2;
        else
            IOSET0 = 1 << LED2;

        // -----------------------
        // Control LED3 with SW3
        // -----------------------
        if (((IOPIN0 >> SW3) & 1) == 0)
            IOCLR0 = 1 << LED3;
        else
            IOSET0 = 1 << LED3;
    }
}
Explanation

Pin Definitions

SW0 to SW3 are the switch pins (input pins).

LED0 to LED3 are the LED pins (output pins).

Setting Direction

IODIR0 is the Port0 direction register.

1 → output, 0 → input.

Using |= ensures we don’t modify other pins accidentally.

Reading Switch State

IOPIN0 reads the status of all Port0 pins.

(IOPIN0 >> SWx) & 1 isolates the bit of the specific switch.

Pressed switch gives 0, released gives 1 (assuming active low switches).

Turning LEDs ON/OFF

IOSET0 sets a pin high (LED ON if active high).

IOCLR0 clears a pin (LED OFF if active high).

Infinite Loop

Keeps continuously checking the switches and updating LED states in real time.
