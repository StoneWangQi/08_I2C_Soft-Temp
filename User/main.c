/**
  ******************************************************************************
  * @file    GPIO/JTAG_Remap/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "PROJ_book.h" 

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

void fn_LED_Flash_Init(void);
void fn_usart_show_Init(void);
void fn_DMA_show_Init(void);
void fn_I2C_EE_Init(void);
void fn_I2C_EE_Soft_Init(void);

uint8_t writeData[_I2C_PageSize]={4,5,6,7,8,9,10,11};
uint8_t writeData2[_I2C_PageSize]={24,25,26,27,28,29,30,31};
uint8_t ReadData[_I2C_PageSize]={0};
int main(void)
{ 
      uint8_t i=0;
      fn_RCC_Init();          //CPU 倍频
      fn_Led_Init();          //LED 输出初始化
      fn_Key_Init();          //按键 输入初始化
      fn_USART_Init();        //串口输出初始化
      fn_LED_Flash_Init();    //RGB 输出测试
      fn_usart_show_Init();   //串口输出测试
      fn_EXTI_GPIO_Config();  //外部中断入口
      fn_DMA_show_Init();     //初始化DMA数据链路
      
      
      fn_I2C_EE_Init();       //初始化硬件I2C数据链路
  
      fn_I2C_EE_Soft_Init();  //初始化软件I2C数据链路
 
       
      while(1);
}


void fn_LED_Flash_Init(void){
  uint16_t  count_Init = 2;
  printf("\n ---> LED开始运行 \n");
  while(count_Init-->0){
    fn_LED_ALL_OFF();
    __R_OUT__;
    fn_Systick_Delay(500,_Systick_ms);
    fn_LED_ALL_OFF();
    __G_OUT__;
    fn_Systick_Delay(500,_Systick_ms);
    fn_LED_ALL_OFF();
    __B_OUT__;
    fn_Systick_Delay(500,_Systick_ms);
    fn_LED_ALL_OFF();
    __R_OUT__;
  } 
}

void fn_usart_show_Init(void){ 
  fn_Usart_Send_Byte(_DEBUG_USARTx,'\r');
  printf("-->串口通信指测试完毕 \n");
  fn_Usart_SendString(_DEBUG_USARTx," : wangqi \n");
}

void fn_DMA_show_Init(void){
  printf("\n ---> DMA开始运行 \n");
  _DMA_ROM_TO_RAM(Map_BUFFER_SIZE ,aSRC_Cont_Buffer , aDST_Buffer);
  _DMA_RAM_TO_USART(Map_BUFFER_SIZE ,USART_Source_ADDR , aDST_Buffer); 
  printf("---> DMA运行完毕 \n");
}
void fn_I2C_EE_Init(void){
  printf("\n-->I2C_函数写入开始 \n");
  _I2C_EE_Init();
  I2C_Write_fun(writeData ,EEP_Firstpage ,_I2C_PageSize);
  I2C_Read_fun(ReadData ,EEP_Firstpage ,_I2C_PageSize);
  printf("--->I2C_函数写入完毕\n\r");
}

void fn_I2C_EE_Soft_Init(void){
  printf("\n-->I2C_软件函数写入开始 \n");
  I2C_Soft_Init();
  I2C_Soft_Write_fun(writeData2 ,EEP_Firstpage ,_I2C_PageSize);
  I2C_Soft_Read_fun(ReadData ,EEP_Firstpage ,_I2C_PageSize);
  printf("\n--->I2C_软件函数写入完毕\n\r");
}
void delay(int x){
	int y = 0xFFFFF;
	while((x--)>0){
		while((y--)>0){
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
		}
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
