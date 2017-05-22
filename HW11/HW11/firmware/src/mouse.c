/*******************************************************************************
  Mouse Function Driver
  Company:
    Microchip Technology Inc.
  FileName:
    mouse.c
  Summary:
    Mouse APIs 
  Description:
    Mouse APIs
*******************************************************************************/

/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).
You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.
SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

#include "mouse.h"

// *****************************************************************************
/* Function:
    void MOUSE_ReportCreate
    (
        MOUSE_COORDINATE x, 
        MOUSE_COORDINATE y,
        MOUSE_BUTTON_STATE * buttonArray,
        MOUSE_REPORT * mouseReport
    )
  Summary:
    This function creates a mouse report.
  Description:
    This function creates a mouse report. The application can use this function 
    to create the mouse report. The report can then be sent to the host by using
    the USB_DEVICE_HID_ReportSend() function.
  Precondition:
    None.
  Parameters:
    x - Mouse X Coordinate
    y - Mouse Y Coordinate
    buttonArray - Pointer to an array of button states. Size of the array is
    defined by USB_HID_MOUSE_BUTTON_NUBMERS.
    
    mouseReport - Output only variable that will contain the mouse report.
  Returns:
    None.
  Example:
    <code>
    // This example shows how to create and send the mouse report. Assume
    // that device is configured. Number of mouse buttons is 3. Assume that
    // this mouse is associated with HID Device Instance 0.
	MOUSE_REPORT mouseReport;
    MOUSE_BUTTON_STATE mouseButtons[USB_HID_MOUSE_BUTTON_NUMBERS];
    MOUSE_COORDINATE xCoordinate;
    MOUSE_COORDINATE yCoordinate;
    USB_DEVICE_HID_TRANSFER_HANDLE transferHandle;
    USB_DEVICE_HID_RESULT result;
    // Update the mouse state
    xCoordinate = someXCoordinate;
    yCoordinate = someYCoordinate;
    mouseButtons[0] = USB_HID_MOUSE_BUTTON_STATE_PRESSED;
    mouseButtons[1] = USB_HID_MOUSE_BUTTON_STATE_RELEASED;
    mouseButtons[2] = USB_HID_MOUSE_BUTTON_STATE_RELEASED;
    // Create the report.
    MOUSE_ReportCreate( xCoordinate, yCoordinate, 
        mouseButtons, &mouseReport);
    // Now send the report
  
    result = USB_DEVICE_HID_ReportSend( 0, &transferHandle,  
               (uint8_t *)mouseReport, sizeof(USB_HID_MOUSE_REPORT));
    if(USB_DEVICE_HID_RESULT_OK != result)
    {
        // Do error handling here.
    } 
    // The completion of the report send is indicated by the 
    // USB_DEVICE_HID_EVENT_REPORT_SEND_COMPLETE event.
    </code>
  Remarks:
    None.
*/

void MOUSE_ReportCreate
(
    MOUSE_COORDINATE x,
    MOUSE_COORDINATE y,
    MOUSE_BUTTON_STATE * buttonArray,
    MOUSE_REPORT * mouseReport
)
{
    int index;

    /* Initialize the mouse buttons byte */
    mouseReport->data[0] = 0;

    for (index = 0; index < MOUSE_BUTTON_NUMBERS; index ++)
    {
        /* Create the mouse button bit map */
        mouseReport->data[0] |= buttonArray[index];
    }

    /* Update the x and y co-ordinate */
	mouseReport->data[1] = x;
	mouseReport->data[2] = y;

	return;	
}

