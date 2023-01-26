#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    //Paso 1 Enceder el periferico Run Clock Gate Control GPIO
    SYSCTL->RCGCGPIO |= (1<<1) | (1<<5) | (1<<8) | (1<<12);//enable GPIOF,GPION,GPIOJ
    while((SYSCTL->PRGPIO&0x20)==0){};
    //Paso 2
 //   GPIO_PORTB_AHB_LOCK_R = 0x4C4F434B;
 //   GPIO_PORTB_AHB_CR_R = (1<<3);

    //Salidas
    GPIOF_AHB->DIR |= (1<<0) | (1<<4);
    GPION->DIR |= (1<<0) | (1<<1);
    GPIOB_AHB->DIR |= (1<<3);
    //Entradas
    GPIOJ_AHB->DIR |= (0<<1) | (0<<0);
    GPIOJ_AHB->PUR =  (1<<1) | (1<<0);
    //Paso 3
    GPIOJ_AHB->AFSEL |= 0x00;
    GPION->AFSEL |= 0x00;
    GPIOF_AHB->AFSEL |= 0x00;
    GPIOB_AHB->AFSEL |= 0x00;

    GPIOJ_AHB->PCTL|= 0x00;
    GPION->PCTL |= 0x00;
    GPIOF_AHB->PCTL |= 0x00;
    GPIOB_AHB->PCTL |= 0x00;

    GPIOF_AHB->DEN |= (1<<0) | (1<<4);
    GPION->DEN |= (1<<0) | (1<<1);
    GPIOJ_AHB->DEN |= (1<<1) | (1<<0);
    GPIOB_AHB->DEN |=  (1<<3);

    //configurar evento de interrupcion PORTJ
    GPIOJ_AHB->IM |= (0<<1) | (0<<0); //Limpiar los bits
    GPIOJ_AHB->IS |= (0<<1) | (0<<0);
    GPIOJ_AHB->IBE |= (0<<1) | (0<<0);
    GPIOJ_AHB->IEV |= (1<<1) | (1<<0);
    GPIOJ_AHB->RIS |= (0<<1) | (0<<0);
    GPIOJ_AHB->IM |= (1<<1) | (1<<0);
    // numero de interrupcion PORTJ = 51
    // n=12 ----> [4n+3] [4n+2] [4n+1] [4n] ---> [4n+3]

}

extern void Prender_LED(void)
{
    static int i=0;
    GPIOF_AHB->DATA = i;
    i = i + 1;
}

extern void GPIOJ_INT_ISR(void)
{
    if (GPIOJ_AHB->RIS == (1<<0))
    
    {
        GPIOF_AHB->DATA = (0<<4);
    }

    if (GPIOJ_AHB->RIS == (1<<1))
    {

        GPIOF_AHB->DATA = (0<<0);

        GPIOF_AHB->DATA = (1<<0);
   
    }
    GPIOJ_AHB->ICR |=(1<<0)|(1<<1);
}

