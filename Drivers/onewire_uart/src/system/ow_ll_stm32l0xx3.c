/*
 * STM32L073RZ
 *
 * UART configuration is:
 *
 * UART:                USART5
 * STM32 TX:            GPIOC, GPIO_PIN_12
 * STM32 RX:            GPIOD, GPIO_PIN_2
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Eric Fryters, 2019
 */


#include "system/ow_ll.h"

#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_lpuart.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_dma.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_pwr.h"


// USART
#define ONEWIRE_USART                           USART5
//#define ONEWIRE_USART_CLK_EN                    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define ONEWIRE_USART_CKL_EN					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART5);

// USART TX PIN
#define ONEWIRE_TX_PORT                         GPIOC
#define ONEWIRE_TX_PORT_CLK_EN					LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
#define ONEWIRE_TX_PIN                          LL_GPIO_PIN_12
#define ONEWIRE_TX_PIN_AF                       LL_GPIO_AF_2

// USART RX PIN
#define ONEWIRE_RX_PORT                         GPIOD
#define ONEWIRE_RX_PORT_CLK_EN                  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
#define ONEWIRE_RX_PIN                          LL_GPIO_PIN_2
#define ONEWIRE_RX_PIN_AF                       LL_GPIO_AF_6



/**
 * \brief           USART structure
 */
static LL_USART_InitTypeDef usart_init;

/**
 * \brief           Initialize low-level communication
 * \param[in]       arg: User argument
 * \return          `1` on success, `0` otherwise
 */
uint8_t ow_ll_init(void* arg) {
    LL_GPIO_InitTypeDef gpio_init;

    /* Peripheral clock enable */
    ONEWIRE_USART_CKL_EN;
    ONEWIRE_TX_PORT_CLK_EN;
    ONEWIRE_RX_PORT_CLK_EN;

    /* Configure GPIO pins */
    LL_GPIO_StructInit(&gpio_init);
    gpio_init.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_init.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio_init.Pull = LL_GPIO_PULL_UP;

    /* TX pin */
    gpio_init.Alternate = ONEWIRE_TX_PIN_AF;
    gpio_init.Pin = ONEWIRE_TX_PIN;
    LL_GPIO_Init(ONEWIRE_TX_PORT, &gpio_init);

    /* RX pin */
    gpio_init.Alternate = ONEWIRE_RX_PIN_AF;
    gpio_init.Pin = ONEWIRE_RX_PIN;
    LL_GPIO_Init(ONEWIRE_RX_PORT, &gpio_init);

    /* Configure UART peripherals */
    LL_USART_DeInit(ONEWIRE_USART);
    LL_USART_StructInit(&usart_init);
    usart_init.BaudRate = 9600;
    usart_init.DataWidth = LL_USART_DATAWIDTH_8B;
    usart_init.StopBits = LL_USART_STOPBITS_1;
    usart_init.Parity = LL_USART_PARITY_NONE;
    usart_init.TransferDirection = LL_USART_DIRECTION_TX_RX;
    usart_init.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    usart_init.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(ONEWIRE_USART, &usart_init);
    LL_USART_ConfigAsyncMode(ONEWIRE_USART);

    OW_UNUSED(arg);

    return 1;
}

/**
 * \brief           Deinit low-level
 * \param[in]       arg: User argument
 * \return          `1` on success, `0` otherwise
 */
uint8_t ow_ll_deinit(void* arg) {
    LL_USART_DeInit(ONEWIRE_USART);
    OW_UNUSED(arg);
    return 1;
}

/**
 * \brief           UART set baudrate function
 * \param[in]       arg: User argument
 * \param[in]       baud: Expected baudrate for UART
 * \return          `1` on success, `0` otherwise
 */
uint8_t ow_ll_set_baudrate(uint32_t baud, void* arg) {
    usart_init.BaudRate = baud;
    LL_USART_Init(ONEWIRE_USART, &usart_init);
    LL_USART_ConfigAsyncMode(ONEWIRE_USART);
    OW_UNUSED(arg);

    return 1;
}

/**
 * \brief           Transmit-Receive data over OneWire bus
 * \param[in]       tx: Array of data to send
 * \param[out]      rx: Array to save receive data
 * \param[in]       len: Number of bytes to send
 * \param[in]       arg: User argument
 * \return          `1` on success, `0` otherwise
 */
uint8_t ow_ll_transmit_receive(const uint8_t* tx, uint8_t* rx, size_t len, void* arg) {
    const uint8_t* t = tx;
    uint8_t* r = rx;

    /* Send byte with polling */
    LL_USART_Enable(ONEWIRE_USART);
    for (; len > 0; --len, ++t, ++r) {
        LL_USART_TransmitData8(ONEWIRE_USART, *t);
        while (!LL_USART_IsActiveFlag_TXE(ONEWIRE_USART));
        while (!LL_USART_IsActiveFlag_RXNE(ONEWIRE_USART));
        *r = LL_USART_ReceiveData8(ONEWIRE_USART);
    }
    while (!LL_USART_IsActiveFlag_TC(ONEWIRE_USART)) {}
    LL_USART_Disable(ONEWIRE_USART);
    OW_UNUSED(arg);
    return 1;
}

/* Include generic STM32 driver */
//#include "../system/ow_ll_stm32.c"

