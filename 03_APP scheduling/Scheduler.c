/*
 * Scheduler.c
 *
 *  Created on: 2024. 6. 27.
 *      Author: user
 */

#include "Scheduler.h"
#include "Driver_Stm.h"

#include <stdio.h>
#include <stdint.h>
#include "Blinky_LED.h"
#include "uart.h"
#include "DrvAdc.h"

#define MidAdc_GetAdcGroup0SenseRaw()   (&stSensorAdcRaw)

typedef struct {
        uint32_t u32nuCnt1ms;
        uint32_t u32nuCnt10ms;
        uint32_t u32nuCnt50ms;
        uint32_t u32nuCnt100ms;
        uint32_t u32nuCnt500ms;
} TestCnt;

static void AppTask1ms(void);
static void AppTask10ms(void);
static void AppTask50ms(void);
static void AppTask100ms(void);
static void AppTask500ms(void);

TestCnt stTestCnt;

static void AppTask1ms(void){
    stTestCnt.u32nuCnt1ms++;
    DrvAdc_GetAdcRawGroup4();
    SensorAdcRaw* pstSensorAdcRaw = MidAdc_GetAdcGroup0SenseRaw();
    int ULSraw = pstSensorAdcRaw->UlSSense1_Raw;
    blinkLED(ULSraw);
    printf("%d\n", ULSraw);
}
static void AppTask10ms(void){    stTestCnt.u32nuCnt10ms++;    }
static void AppTask50ms(void){
    stTestCnt.u32nuCnt50ms++;
}
static void AppTask100ms(void){    stTestCnt.u32nuCnt100ms++; }// _out_uart3('a');   }
static void AppTask500ms(void){    stTestCnt.u32nuCnt500ms++; }// toggleLED();    }


void AppScheduling(void){
    if (stSchedulingInfo.u8nuScheduling1msFlag == 1u){
        stSchedulingInfo.u8nuScheduling1msFlag = 0u;
        AppTask1ms();

        if (stSchedulingInfo.u8nuScheduling10msFlag == 1u){
            stSchedulingInfo.u8nuScheduling10msFlag = 0u;
            AppTask10ms();
        }
        if (stSchedulingInfo.u8nuScheduling50msFlag == 1u){
            stSchedulingInfo.u8nuScheduling50msFlag = 0u;
            AppTask50ms();
        }
        if (stSchedulingInfo.u8nuScheduling100msFlag == 1u){
            stSchedulingInfo.u8nuScheduling100msFlag = 0u;
            AppTask100ms();
        }
        if (stSchedulingInfo.u8nuScheduling500msFlag == 1u){
            stSchedulingInfo.u8nuScheduling500msFlag = 0u;
            AppTask500ms();
        }
    }

}
