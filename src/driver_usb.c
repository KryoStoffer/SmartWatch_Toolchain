#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_defines.h"
#include "driver_usb.h"
#include <usbd_cdc_vcp.h>

USB_OTG_CORE_HANDLE  USB_OTG_dev;

void setupUSB (void) {
    #define USB_DISC_DEV         GPIOD
    #define USB_DISC_PIN         11

  //digitalWrite(CONNECT_USB,HIGH);

  /* setup the apb clock for USB */
  //RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE) ;


  /* initialize the usb application */
  //digitalWrite(CONNECT_USB,LOW);
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_cb,
            &USR_cb);
}

extern uint16_t VCP_DataTx (u8* Buf, uint32_t Len);
extern void     VCP_SetUSBTxBlocking(uint8_t mode);
extern uint32_t VCPBytesAvailable(void);
extern uint8_t  VCPGetByte(void);

uint32_t usbSendBytes(const char* sendBuf, uint32_t len) {
	VCP_DataTx((uint8_t*)sendBuf, len);
	return len;
}

void usbEnableBlockingTx(void) {
	VCP_SetUSBTxBlocking(1);
}

void usbDisableBlockingTx(void) {
	VCP_SetUSBTxBlocking(0);
}


uint32_t usbBytesAvailable(void) {
	return VCPBytesAvailable();

}
uint32_t usbReceiveBytes(u8* recvBuf, uint32_t len) {
	  int newBytes = usbBytesAvailable();
	  if (len > newBytes) {
	      len = newBytes;
	  }

	  int i;
	  for (i=0;i<len;i++) {
	      recvBuf[i] = VCPGetByte();
	  }

	  return len;
}

u8 usbIsConfigured() {
  return 1; //(bDeviceState == CONFIGURED);
}

u8 usbIsConnected() {
  return 1; //(bDeviceState != UNCONNECTED);
}

RESULT usbPowerOn(void) {
  return USB_SUCCESS;
}

RESULT usbPowerOff(void) {
  USBD_DeInit(&USB_OTG_dev);
  return USB_SUCCESS;
}
void usbDsbISR(void) {};

#include "usb_dcd_int.h"

	__attribute__ ((interrupt ("IRQ")))
void OTG_FS_WKUP_IRQHandler(void)
{
	if(USB_OTG_dev.cfg.low_power)
	{
		*(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
		SystemInit();
		USB_OTG_UngateClock(&USB_OTG_dev);
	}
	EXTI_ClearITPendingBit(EXTI_Line18);
}

	__attribute__ ((interrupt ("IRQ")))
void OTG_FS_IRQHandler(void)
{
	USBD_OTG_ISR_Handler (&USB_OTG_dev);
}


