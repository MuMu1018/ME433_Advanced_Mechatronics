/*******************************************************************************
  MPLAB Harmony Application Header File
  Company:
    Microchip Technology Inc.
  File Name:
    app.h
  Summary:
    This header file provides prototypes and definitions for the application.
  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).
You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "mouse.h"
#include "LSM6DS333.h"
#include "I2C.h"
#include "ILI9163C.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define STRINGLENGTH 100
// *****************************************************************************
/* Application States
  Summary:
    Application states enumeration
  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,

	/* Application waits for configuration in this state */
    APP_STATE_WAIT_FOR_CONFIGURATION,

    /* Application runs mouse emulation in this state */
    APP_STATE_MOUSE_EMULATE,

    /* Application error state */
    APP_STATE_ERROR

} APP_STATES;


// *****************************************************************************
/* Application Data
  Summary:
    Holds application data
  Description:
    This structure holds the application's data.
  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;

    /* device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE  deviceHandle;

    /* Is device configured */
    bool isConfigured;

    /* Mouse x coordinate*/
    MOUSE_COORDINATE xCoordinate;

    /* Mouse y coordinate*/
    MOUSE_COORDINATE yCoordinate;

    /* Mouse buttons*/
    MOUSE_BUTTON_STATE mouseButton[MOUSE_BUTTON_NUMBERS];

    /* HID instance associated with this app object*/
    SYS_MODULE_INDEX hidInstance;

    /* Transfer handle */
    USB_DEVICE_HID_TRANSFER_HANDLE reportTransferHandle;

    /* Device Layer System Module Object */
    SYS_MODULE_OBJ deviceLayerObject;

    /* USB HID active Protocol */
    uint8_t activeProtocol;

    /* USB HID current Idle */
    uint8_t idleRate;

    /* Tracks the progress of the report send */
    bool isMouseReportSendBusy;

    /* Flag determines SOF event has occured */
    bool sofEventHasOccurred;

    /* SET IDLE timer */
    uint16_t setIdleTimer;

} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )
  Summary:
     MPLAB Harmony application initialization routine.
  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.
  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").
  Parameters:
    None.
  Returns:
    None.
  Example:
    <code>
    APP_Initialize();
    </code>
  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )
  Summary:
    MPLAB Harmony Demo application tasks function
  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.
  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.
  Parameters:
    None.
  Returns:
    None.
  Example:
    <code>
    APP_Tasks();
    </code>
  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks ( void );


#endif /* _APP_H */
/*******************************************************************************
 End of File
 */