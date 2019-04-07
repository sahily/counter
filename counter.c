/*
 * counter.c
 *
 * Created: 4/6/2019 8:46:08 PM
 * Author : Sahil S. Mahajan
 * Description: Simple counter 0000 to 9999
 *
 */

#include <REG51F.h>

void delay(unsigned int k);
void display(void);
void incrementOnes(void);
void incrementTens(void);
void incrementHundreds(void);
void incrementThousands(void);
void resetToZero(void);

sbit sl1 = P2^3;
sbit sl2 = P2^2;
sbit sl3 = P2^1;
sbit sl4 = P2^0;

unsigned int numberList[10] = {
                                  0xFC,   //0         
                                  0x60,   //1
                                  0xDA,   //2 
                                  0xF2,   //3
                                  0x66,   //4
                                  0xB6,   //5
                                  0xBE,   //6
                                  0xE0,   //7
                                  0xFE,   //8
                                  0xF6    //9
                              };

unsigned int numbersToDisplay[4] = {'0','0','0','0'};   //the thousands, hundreds, tens, and ones place of the count number

unsigned int digitSelector[4][4] = {
                                      0,1,1,1,   //select 1st digit on 7seg display
                                      1,0,1,1,   //select 2nd digit on 7seg display
                                      1,1,0,1,   //select 3rd digit on 7seg display
                                      1,1,1,0    //select 4th digit on 7seg display
                                   };

unsigned int n;   /* This is just to make multiple iterations of the display function in the main function.  */
                  /* The number of iterations will control the speed of the count.                           */



void main()
{
    while(1)
    {
        for(n=0;n<29;n++)
        {
            display();
        }
        incrementOnes();
    }
}


/* -----------------
 * Function: delay
 * -----------------
 *
 * creates delay for a specificed number of milliseconds
 *
 * k: number of milliseconds (approximate)
 *
 */

void delay(unsigned int k)
{
    unsigned int i;
    unsigned int j;
    for(i=0;i<k;i++)
    {
        for(j=0;j<120;j++);
    }
}


/* -----------------
 * Function: display
 * -----------------
 *
 * selects one digit on the 7-segment display at a time and displays a number on the selected digit
 *
 */
      
void display(void)
{       
    unsigned char x;

    for(x=0;x<4;x++)
    {
        sl1 = digitSelector[x][0];
        sl2 = digitSelector[x][1];
        sl3 = digitSelector[x][2];
        sl4 = digitSelector[x][3];      /* Digit is selected when its pin is reset.        */ 
                                        /* Only one of these is selected in each iteration */

        P0 = numberList[numbersToDisplay[x]-'0'];

        delay(4);                       /* 4 milliseconds seems about the right amount of time */
                                        /* for a smooth transition to the next digit/number.   */
    }               
}


/* -----------------
 * Function: incrementOnes
 * -----------------
 *
 * 1. Increments ones place of the count number
 * 2. Calls incrementTens function if ones place increments past 9
 *
 */

void incrementOnes(void)
{
    numbersToDisplay[3]++;   
    if(numbersToDisplay[3] == '9'+1)
    {
        incrementTens();
    }   
}


/* -----------------
 * Function: incrementTens
 * -----------------
 *
 * 1. Resets ones place to zero
 * 2. Increments tens place of the count number
 * 3. Calls incrementHundreds function if tens place increments past 9   
 * 
 */

void incrementTens(void)
{
    numbersToDisplay[3] = '0';
    numbersToDisplay[2]++;
    if(numbersToDisplay[2] == '9'+1)
    {
        incrementHundreds();
    }
}


/* -----------------
 * Function: incrementHundreds
 * -----------------
 *
 * 1. Resets tens place to zero
 * 2. Increments hundreds place of the count number
 * 3. Calls incrementThousands function if hundreds place increments past 9   
 * 
 */

void incrementHundreds(void)
{
    numbersToDisplay[2] = '0';
    numbersToDisplay[1]++;
    if(numbersToDisplay[1] == '9'+1)
    {
        incrementThousands();
    }
}


/* -----------------
 * Function: incrementThousands
 * -----------------
 *
 * 1. Resets hundreds place to zero
 * 2. Increments thousands place of the count number
 * 3. Calls resetToZero function if thousands place increments past 9   
 * 
 */

void incrementThousands(void)
{
    numbersToDisplay[1] = '0';
    numbersToDisplay[0]++;
    if(numbersToDisplay[0] == '9'+1)
    {
        resetToZero();
    }
}


/* -----------------
 * Function: resetToZero
 * -----------------
 *
 * resets count to 0000   
 * 
 */

void resetToZero(void)
{
    numbersToDisplay[0] = '0';
    numbersToDisplay[1] = '0';
    numbersToDisplay[2] = '0';
    numbersToDisplay[3] = '0';
}