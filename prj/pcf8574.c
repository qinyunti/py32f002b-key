#include "pcf8574.h"

#define PCF8574_WR_ADDR 0x40/**< 写地址 */
#define PCF8574_RD_ADDR 0x41/**< 读地址 */

/**
 * \fn pcf8574_read
 * 读数据
 * \param[in] dev \ref pcf8574_dev_st
 * \param[in] val 存读出的值
 * \retval 0  成功
 * \retval <0 失败
*/
int pcf8574_read(pcf8574_dev_st* dev, uint8_t* val)
{
    /* 启动 */
    dev->stop(); /* 如果直接start 上电后第一次总是无ACK,所以先stop进入确定状态 */
    dev->start();

    /* 发送读地址 */
    if(0 != dev->write(PCF8574_RD_ADDR | ((dev->addr & 0x07)<<1)))
    {
        dev->stop();
        return -1;
    }

    /* 读数据 */
    if(0 != dev->read(val,0))
    {
        dev->stop();
         return -2; 
    }

    /* 结束 */
    dev->stop();
    return 0;
}

/**
 * \fn pcf8574_write
 * 写数据
 * \param[in] dev \ref pcf8574_dev_st
 * \param[in] val 待写入的值
 * \retval 0  成功
 * \retval <0 失败
*/
int pcf8574_write(pcf8574_dev_st* dev, uint8_t val)
{
    /* 启动 */
    dev->stop(); /* 如果直接start 上电后第一次总是无ACK,所以先stop进入确定状态 */
    dev->start();

    /* 发送写地址 */
    if(0 != dev->write(PCF8574_WR_ADDR | ((dev->addr & 0x07)<<1)))
    {
        dev->stop();
        return -1;
    }

    /* 写数据 */
    if(0 != dev->write(val))
    {
        dev->stop();
        return -2;
    }
     
    /* 结束 */
    dev->stop();
    return 0;
}

/**
 * \fn pcf8574_init
 * 初始化
 * \param[in] dev \ref pcf8574_dev_st
*/
void pcf8574_init(pcf8574_dev_st* dev)
{
    dev->init();
}

/**
 * \fn pcf8574_deinit
 * 解除初始化
 * \param[in] dev \ref pcf8574_dev_st
*/
void pcf8574_deinit(pcf8574_dev_st* dev)
{
    dev->deinit();
}