#include "io_iic.h"
#include "pcf8574.h"
#include "key.h"

#include "py32f0xx.h"

/* IIC IO操作的移植 */
static void io_iic_scl_write_port(uint8_t val)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,(val==0)?GPIO_PIN_RESET:GPIO_PIN_SET);
}

static void io_iic_sda_write_port(uint8_t val)
{
	/* out */
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;            /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,(val==0)?GPIO_PIN_RESET:GPIO_PIN_SET);
}

static void io_iic_sda_2read_port(void)
{
	/* in */
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;               /*  input */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  
}

static uint8_t io_iic_sda_read_port(void)
{
	return (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) == GPIO_PIN_SET)? 1: 0;
}

static void io_iic_delay_us_port(uint32_t delay)
{
	uint32_t volatile t=delay;
	while(t--);
}

static void io_iic_init_port(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOB_CLK_ENABLE();                          /* Enable GPIOB clock */

  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;            /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  
	
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 
}

static void io_iic_deinit_port(void)
{

}

static io_iic_dev_st iic_dev=
{
	.scl_write = io_iic_scl_write_port,
	.sda_write = io_iic_sda_write_port,
	.sda_2read = io_iic_sda_2read_port,
	.sda_read = io_iic_sda_read_port,
	.delay_pf = io_iic_delay_us_port,
	.init = io_iic_init_port,
	.deinit = io_iic_deinit_port,
	.delayus = 1,
};

/* pcf8574接口移植 */
static void pcf8574_iic_start_port(void)
{
	io_iic_start(&iic_dev);
}

static void pcf8574_iic_stop_port(void)
{
	io_iic_stop(&iic_dev);
}

static int pcf8574_iic_read_port(uint8_t* val, uint8_t ack)
{
	return io_iic_read(&iic_dev,val,ack);
}

static int pcf8574_iic_write_port(uint8_t val)
{
	return io_iic_write(&iic_dev,val);
}

static void pcf8574_iic_init_port(void)
{
	io_iic_init(&iic_dev);
}

static void pcf8574_iic_deinit_port(void)
{
	io_iic_deinit(&iic_dev);
}

pcf8574_dev_st pcf8574_dev=
{
	.start = pcf8574_iic_start_port,
	.stop = pcf8574_iic_stop_port,
	.read = pcf8574_iic_read_port,
	.write = pcf8574_iic_write_port,
	.init = pcf8574_iic_init_port,
	.deinit = pcf8574_iic_deinit_port,
	.addr = 0,
};

/* 对外接口 */
void key_init(void)
{
	pcf8574_init(&pcf8574_dev);
}

void key_deinit(void)
{
	pcf8574_deinit(&pcf8574_dev);
}

int key_write(uint8_t val)
{
	return pcf8574_write(&pcf8574_dev,val);
}

int key_read(uint8_t* val)
{
	return pcf8574_read(&pcf8574_dev,val);
}