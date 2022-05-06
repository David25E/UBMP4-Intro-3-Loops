/*==============================================================================
 Project: Intro-3-Loops
 Date:    May 16, 2021
 
 This example program demonstrates the use of while and for loop structures to
 change the brightness of LEDs using PWM (Pulse-Width Modulated) signals.
 
 Additional program analysis and programming activities expand the use of loops
 to create tones of different pitches and frequency sweeps.
==============================================================================*/
 
#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions
 
#include    "UBMP4.h"           // Include UBMP4 constants and functions
 
// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.
 
// Program variable definitions
unsigned char TonLED4 = 127;    // LED brightness PWM value
unsigned char TonLED5 = 127;
unsigned char PWMperiod;        // PWM period counter for PWM loops
unsigned int period = 460;      // Sound period value for later activities
 
int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
   
   
    while(1)
    {
        //testing LED's for brightness comparison
        LED3 = 1;
        LED6 = 1;
       // Decrease brightness
       if(SW2 == 0)
       {
           TonLED4 -= 1;
       }
 
       // Increase brightness
       if(SW3 == 0)
       {
           TonLED4 += 1;
       }
       // Decrease brightness
       if(SW5 == 0)
       {
           TonLED5 -= 1;
       }
 
       // Increase brightness
       if(SW4 == 0)
       {
           TonLED5 += 1;
       }
     
       // PWM LED4 brightness
       PWMperiod = 128;
     
       for(unsigned char PWMperiod = 255; PWMperiod != 0; PWMperiod --)
       {
           if(TonLED4 == PWMperiod)
           {
               LED4 = 1;
           }
           __delay_us(20);
           
           if(TonLED5 == PWMperiod)
           {
               LED5 = 1;
           }
           __delay_us(20);
       }
       LED4 = 0;
       LED5 = 0;

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }  
}
 
/* Program Analysis
 *
 * 1. The main part of the program contains the 'while(1)' loop. What condition
 *    is being evaluated within its brackets? (Hint: Think about the Boolean
 *    variables from Activity 2-Variables.) How many times will this loop run?
 
 The condition that is being evaluated within its brackets is the number of times/how long the while loop will run for.
 In this case, the 1 will cause it to run forever until reset or a given commaned causes it to stop.
 *
 * 2. There is a second 'while(PWMperiod != 0)' loop inside the first while
 *    loop. What condition is being evaluated inside this while statement's
 *    brackets? How many times will the contents of this inner loop run?
 
 The condition that is evaluated within these brackets is that while PWMperiod is not 0, it will run the assigned code within its brackets.
 It will run forever unless PWMperiod is changed to 0.
 *
 * 3. What condition is being evaluated by the if statement inside the loop?
 *    What happens when the if condition is true?
 
 The condition that is being evaluated by the if statement inside the loop is that if TonLED4(the variable that allows the LED brightness to either decrease or increase) equals the PWMperiod,
 (the variable that creates the cycle of the continous decreasing or increasing pattern of the LED's), LED4 will light up. 
 These are the contents of the code that are required to light up and adjust the brightness of the LED.
 Later, if the statement is false, the line "PWMperiod --" restarts the loop.
 *
 * 4. Pressing the up or down buttons (SW3 and SW2) will increase or decrease
 *    the brightness of LED D4 using PWM (Pulse-Width Modulation). How many
 *    different brightnesses can the LED have? What would the step size of one
 *    brightness level change be if it was expressed as a percentage?
 
The board can have 256 different brightnesses, which is the step size. As a percentage, it would be approximately 0.39% (1/256 * 100).
 *
 * 5. The while loop needs three statements to perform its function. First, the
 *    assignment statement 'PWMperiod = 255;' sets the PWMperiod variable. Next,
 *    the condition 'while(PWMperiod != 0)' runs the contents of the loop code
 *    while the condition is true. Unlike if statements, in which program flow
 *    continues below the contents of the if structure, the while loop causes
 *    the condition to be re-evaluated after executing the contents of its code.
 *    To ensure that the while loop does end at some point, the assignment
 *    statement 'PWMperiod --;' modifies the variable from within the loop.
 *    When the condition is false, the loop terminates and the program continues
 *    running the code below the loop structure.
 *
 *    A 'for' loop is an alternative to a while loop, and incorporates the
 *    assignment of the loop variable, the loop conditional check, and variable
 *    modification into a single statement as shown in the example code. Replace
 *    the entire while structure in the code with the following for structure:
       
        // PWM LED4 brightness
        for(unsigned char PWMperiod = 255; PWMperiod != 0; PWMperiod --)
        {
            if(TonLED4 == PWMperiod)
            {
                LED4 = 1;
            }
            __delay_us(20);
        }
        LED4 = 0;
       
 *    What is an advantage of using a for loop instead of a while loop?
 
 An advantage for using a for loop is if you know how many cycles/loops you wish to do, because it can be more convinent than a while loop being dynamic.
 This is because the user determines the looping and stoppage of the while loop by what occurs. For example, in a program, a while loop can run until a different feature is used.
 
 * 6. The 'for' loop, above, redefines the PWMperiod variable in the
 *    initialization statement: 'for(unsigned char PWMperiod = 255; ...'
 *
 *    This instance of the PWMperiod variable will be local to the for loop,
 *    and won't maintain its value outside of the loop, or alter the value of
 *    the existing PWMperiod variable. It's a bad idea to re-use variable names
 *    inside loops since having two different versions of the same variable
 *    creates confusion. Is this really the case? Let's prove that the global
 *    PWMperiod variable is not affected by the local PWMperiod variable
 *    inside the for loop. Add this line above the for loop:
 
        PWMperiod = 128;
 *    Next, add the following lines after the for loop:
       
        if(PWMperiod == 128)
        {
            LED5 = 1;
        }
        else
        {
            LED5 = 0;
        }
       
 *    Compile and run the code. When the program runs, the PWMperiod variable
 *    inside the for loop will count down from 255 to 0, and should be 0 when
 *    the loop finishes. Is LED D5 lit? What must the value of PWMperiod be?
 
 LED D5 is lit, which means the value of PWmperiod must still be 128 since if it is not the LED would turn off.
 *
 *    Can you remove the global PWMperiod variable definition from the top of
 *    the program now that PWMperiod is being defined in the for loop?
 
 No, I can not remove the global PWMperiod from the variable definition because the PWMperiod is also being used outside of the for loop.
 Thus, it is still needed.
 *
 * 7. Add this code below the PWM loop to generate a tone:
               
        // Change pitch
        if(SW4 == 0)
        {
            period -= 1;
        }
       
        if(SW5 == 0)
        {
            period += 1;
        }
       
        // Make a tone
        for(unsigned char cycles = 50; cycles != 0; cycles--)
        {
            BEEPER = !BEEPER;
            for(unsigned int p = period; p != 0; p--);
        }
 *    The section to make a tone contains nested for loops. The outer loop
 *    repeatedly causes the BEEPER pin to toggle before the inner loop runs.
 *    The inner loop is an empty loop, shown by its trailing semicolon ';'. It
 *    contains no code, so nothing will be repeated, but exists only to add a
 *    time delay to our program. The higher the number of loops, the more
 *    instruction cycles it will take to decrement the loop counter variable
 *    to zero, increasing the time delay until the next cycle.
 *
 *    What variable type is period? How large a number can this variable hold?
 
 Period is an unsigned integer variable, so it can only deal/work with positive integers from 0 to 2^16(65 536).
 *
 * 8. Why is period copied to the local variable p inside the inner for loop?
 *    What would happen if the actual period variable was decremented instead?
 
 Period is copied to the local variable p inside the inner loop to be able to increase and decrease the delay of the first loop.
 If the actual period variable was decremented instead, the delay would not work because you would not be able to change the pitch of the beeper. 
 If it is period = 460, the beeper is simply producing a single pitched tone. Plus, if it is simply "period" in the for loop, there is no sound produced unless SW4 is pressed.
 *
 * Programming Activities
 *
 * 1. Pressing and holding SW2 or SW3 causes the brightness of LED D4 to cycle
 *    through its entire brightness range. Modify the code so that pressing and
 *    holding SW2 will dim the LED until it is off and then keep if off, and
 *    pressing and holding SW3 will brighten the LED and keep it at maximum
 *    brightness.
        // Decrease brightness
        if(SW2 == 0 && TonLED4 > 0)          // added TonLED4 > 0
        {
            TonLED4 -= 1;
        }
        // Increase brightness
        if(SW3 == 0 && TonLED4 < 255)        // added TonLED4 < 255
        {
            TonLED4 += 1;
   
        }
       
        // PWM LED4 brightness
        for(unsigned char PWMperiod = 255; PWMperiod != 0; PWMperiod --)
        {
            if(TonLED4 == PWMperiod)
            {
                LED4 = 1;
            }
            if(PWMperiod == 1){
                LED4 = 0;
            }
            __delay_us(20);
        }
        LED4 = 0;
 *
 * 2. Modify your program to control the brightness of LED D5 using SW4 and SW5
 *    while using SW3 and SW2 to control LED D4. Hint: To ensure each LED can
 *    reach maximum brightness (100% PWM on-time), you'll have to perform both
 *    PWM functions in the same loop. You can see the resulting PWM wave if you
 *    have access to an oscilloscope. If not, just light the other two LEDs and
 *    compare the brightness of LEDs D4 and D5 to them.
 *
         //testing LED's for brightness comparison
        LED3 = 1;
        LED6 = 1;
       // Decrease brightness
       if(SW2 == 0)
       {
           TonLED4 -= 1;
       }
 
       // Increase brightness
       if(SW3 == 0)
       {
           TonLED4 += 1;
       }
       // Decrease brightness
       if(SW5 == 0)
       {
           TonLED5 -= 1;
       }
 
       // Increase brightness
       if(SW4 == 0)
       {
           TonLED5 += 1;
       }
     
       // PWM LED4 brightness
       PWMperiod = 128;
     
       for(unsigned char PWMperiod = 255; PWMperiod != 0; PWMperiod --)
       {
           if(TonLED4 == PWMperiod)
           {
               LED4 = 1;
           }
           __delay_us(20);
           
           if(TonLED5 == PWMperiod)
           {
               LED5 = 1;
           }
           __delay_us(20);
       }
       LED4 = 0;
       LED5 = 0;
 * 3. Rather than having lights suddenly turn on at full brightness, or motors
 *    turn on at full power, create a program that uses a for loop and your PWM
 *    code to make a 'soft-start' program that slowly increases the PWM on-time
 *    when you press a button. Can you make it turn off in a similar way?
        
        if(SW2 == 0){                 //increases the brightening speed after a certain number is reached
            TonLED4 += 1;
            if(TonLED4 > 300){
            TonLED4 += 2;
        }
    
        }
            for(unsigned char PWMperiod = 510; PWMperiod != 0; PWMperiod --){     //inital loop to help brighten the LED
                if(TonLED4 == PWMperiod){
                    LED4 = 1;
                }
                __delay_us(20);
            }
            LED4 = 0;
            
            PWMperiod = 255;                 // this loop helps slow down the brightening of the LED
            while(PWMperiod != 0)
            {
            if(TonLED4 == PWMperiod)
            {
                LED4 = 1;
            }
            PWMperiod --;
            __delay_us(20);
        }
        LED4 = 0;

    I can turn it off in a similar way by doing the opposite, which is by slowly dimming the LED after the brightening phase reaches a certain point. 
    Potentially a for loop that accomplishes the opposite.
 *
 * 4. Make a program that creates an automated, electronic 'pulse', repeatedly
 *    brightening and dimming one or more LEDs.
    if(SW4 == 0){
       for(unsigned char PWMperiod = 255; PWMperiod != 0; PWMperiod --)    //Loop that turns on the LED's
       {
           if(TonLED4 && TonLED5 > PWMperiod)
           {
               LED4 = 1;
               TonLED4 -= 1;
               LED5 = 1;
               TonLED5 -= 1;
           }
           __delay_us(200);
       }
       __delay_ms(50);
       for(unsigned char PWMperiod = 0; PWMperiod != 254; PWMperiod ++)    //Loop that turns off the LED's
       {
           if(TonLED4 < PWMperiod && TonLED5 < PWMperiod)
           {
               LED4 = 0;
               TonLED4 += 1;
               LED5 = 0;
               TonLED5 += 1;

           }
           __delay_us(200);
        }
       }
 *
 * 5. Make a 'chirp' or 'pew-pew' sound effect by sweeping through a range of
 *    frequencies when a button is pressed.
 void makeSound(int cycles, long delay){
    for (unsigned int c = 0; c < cycles; c++)       //inital function to create sounds
    {
            BEEPER = !BEEPER;
        unsigned long n = delay;
        for (unsigned long p = 0; p < n; p++)
            ;
    }
}

int cycles = 100;
long delay = 200;

        if(SW2 == 0){                 //Makes sound
        makeSound(cycles, delay);    
       }
       if(SW3 == 0){
           delay --;
       }
       if(SW4 == 0){
           delay ++;
       }
       if(SW5 == 0){                 //reset pitch
           delay = 200;
       }
 */

