#ifndef __BSP_IIC_H
#define	__BSP_IIC_H

#include "stm32f10x.h"

/** 
  * 移植时需要修改这几个宏
  * 1-修改GPIO的宏
  */
	
#define I2C_OWN_ADDRESS         0X0A
#define EEPROM_ADDRESS          0XA0
// I2CX
#define  BSP_I2CX                    I2C1
#define  BSP_I2CX_CLK                RCC_APB1Periph_I2C1
#define  BSP_I2CX_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  BSP_I2CX_SPEED           400000

// I2CX GPIO 引脚宏定义
#define  BSP_I2CX_SCL_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  BSP_I2CX_SDA_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  BSP_I2CX_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  BSP_I2CX_SCL_GPIO_PORT       GPIOB
#define  BSP_I2CX_SCL_GPIO_PIN        GPIO_Pin_6
#define  BSP_I2CX_SDA_GPIO_PORT       GPIOB
#define  BSP_I2CX_SDA_GPIO_PIN        GPIO_Pin_7

void iic_config_init(void);
void eeprom_write_byte(uint8_t addr,uint8_t data);
void eeprom_read(uint8_t addr,uint8_t *data,uint8_t num);
void eeprom_write_wait(void);
void eeprom_write_page(uint8_t addr,uint8_t *data,uint8_t num);
#endif /* __BSP_IIC_H */
