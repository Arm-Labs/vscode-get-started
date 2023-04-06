/*---------------------------------------------------------------------------
 * Copyright (c) 2021 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------
 * Function Branching Factor
 *---------------------------------------------------------------------------*/


void branchingFactor()
{
   int factor = atoi(getenv("BRANCHING_FACTOR"));
   /* GOOD: Prevent overflow by checking the input */
   /*if (factor < 0 || factor > 1000) {
       log("Factor out of range (%d)\n", factor);
       return -1;
   }
   */
   // This line can allocate too little memory if factor
   // is very large.
   char **root_node = (char **) malloc(factor * sizeof(char *));
}

/*---------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/

static void app_main (void *argument) {
  (void)argument;

  for(int count = 0; count<100; count++) {
    printf ("Hello World %d\r\n", count);
    osDelay (1000);
  }
  
  branchingFactor();

  exit(0);
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
static void app_initialize (void) {
  osThreadNew(app_main, NULL, NULL);
}

/*---------------------------------------------------------------------------
 * C main
 *---------------------------------------------------------------------------*/
int main (void) {

#if defined(RTE_Compiler_EventRecorder) && \
    (defined(__MICROLIB) || \
    !(defined(RTE_CMSIS_RTOS2_RTX5) || defined(RTE_CMSIS_RTOS2_FreeRTOS)))
  EventRecorderInitialize(EventRecordAll, 1U);
#endif

  osKernelInitialize();                 // Initialize CMSIS-RTOS2
  app_initialize();                     // Initialize application
  osKernelStart();                      // Start thread execution

  for (;;) {}
}

