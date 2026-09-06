#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h" 
#include "stm32f10x_gpio.h" 

// 1. 必须把 Delay 完整的写在 main 的上面！
void Delay(volatile uint32_t count) 
{
    while(count--)
    {
    }
}

void UseRegisterDelay()
{
 // 1. 使能 GPIOC 的时钟
    RCC->APB2ENR |= (1 << 4);
    
    // 2. 配置 PC13 为通用推挽输出，最大速度 50MHz
    GPIOC->CRH &= ~(0xF << 20); 
    GPIOC->CRH |=  (0x3 << 20); 

    while(1)
    {
        // 3. PC13 输出低电平 (0) -> 点亮 LED
        GPIOC->ODR &= ~(1 << 13); 
        Delay(2000000); // 延时等待
        
        // 4. PC13 输出高电平 (1) -> 熄灭 LED
        GPIOC->ODR |= (1 << 13);  
        Delay(2000000); // 延时等待
    }
}

void UseRegister()
{

		// RCC register , AHB 外设时钟
	//使能IOPC的时钟  IOPCEN : I/O port D clock enable. 1 enable, o unable.
	RCC->APB2ENR = 0x00000010;
	// 设置 PC13 口的模式。 PC13 口就是那个一直闪烁的灯  Configure PC13 as push-pull output
// 2. 配置 PC13 为推挽输出模式，最大速度 50MHz
GPIOC->CRH = 0x00300000;

// 3. 点亮 LED (PC13 输出低电平 0)  Set PC13 low to light the LED
GPIOC->ODR = 0x00000000; 
	//GPIOC->ODR = 0x00000000;
	//GPIOC->ODR = 0x00002000;
	// 4. Keep the processor running forever
	while(1)
	{
		
	}
}
void TurnPC13Light()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef initStruct;
	initStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	initStruct.GPIO_Pin = GPIO_Pin_13;
	initStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC,&initStruct);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);
   GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void TurnPA0Light()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef initStruct;
	initStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	initStruct.GPIO_Pin = GPIO_Pin_0;
	initStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&initStruct);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	

		//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	    while(1)
    {
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	        Delay(2000000); // 延时等待
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
           Delay(1000000); // 延时等待 		
    }
}

void TurnPB13Ring()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef initStruct;
	initStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	initStruct.GPIO_Pin = GPIO_Pin_All;
	initStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB,&initStruct);
	    while(1)
    {
			GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);
	        Delay(2000000); // 延时等待
			GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_SET);
           Delay(9000000); // 延时等待 		
    }

}


int main (void)
{
	//TurnPA0Light();
	//TurnPC13Light();
	//TurnPB13Ring();
}
