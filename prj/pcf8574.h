#ifndef PCF8574_H
#define PCF8574_H

#ifdef __cplusplus
    extern "C"{
#endif

#include <stdint.h>

typedef void    (*pcf8574_iic_start_pf)(void);/**< IIC启动接口 */
typedef void    (*pcf8574_iic_stop_pf)(void); /**< IIC停止接口 */
typedef int     (*pcf8574_iic_read_pf)(uint8_t* val, uint8_t ack); /**< IIC读接口   */
typedef int     (*pcf8574_iic_write_pf)(uint8_t val); /**< IIC写接口   */
typedef void    (*pcf8574_iic_init_pf)(void); /**< 初始化接口 */
typedef void    (*pcf8574_iic_deinit_pf)(void); /**< 解除初始化接口 */
typedef void    (*pcf8574_iic_delay_us_pf)(uint32_t delay); /**< 延时接口      */

/**
 * \struct pcf8574_dev_st
 * 接口结构体
*/
typedef struct
{
    pcf8574_iic_start_pf start; /**< IIC启动接口 */
    pcf8574_iic_stop_pf  stop;  /**< IIC停止接口 */
    pcf8574_iic_read_pf read;   /**< IIC读接口   */
    pcf8574_iic_write_pf write; /**< IIC写接口   */
    pcf8574_iic_init_pf init;   /**< 初始化接口  */
    pcf8574_iic_deinit_pf deinit; /**< 解除初始化接口  */
    uint8_t   addr;      /**< 3位硬件地址    */
} pcf8574_dev_st;

/**
 * \fn pcf8574_read
 * 读数据
 * \param[in] dev \ref pcf8574_dev_st
 * \param[in] val 存读出的值
 * \retval 0 成功
 * \retval <0 失败
*/
int pcf8574_read(pcf8574_dev_st* dev, uint8_t* val);

/**
 * \fn pcf8574_write
 * 写数据
 * \param[in] dev \ref pcf8574_dev_st
 * \param[in] val 待写入的值
 * \retval 0 成功
 * \retval <0 失败
*/
int pcf8574_write(pcf8574_dev_st* dev, uint8_t val);
/**
 * \fn pcf8574_init
 * 初始化
 * \param[in] dev \ref pcf8574_dev_st
*/
void pcf8574_init(pcf8574_dev_st* dev);
/**
 * \fn pcf8574_deinit
 * 解除初始化
 * \param[in] dev \ref pcf8574_dev_st
*/
void pcf8574_deinit(pcf8574_dev_st* dev);

#ifdef __cplusplus
}
#endif

#endif