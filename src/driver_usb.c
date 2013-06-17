#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "driver_usb.h"
#include <stm32f2xx_gpio.h>
//#include <rccF2.h>
#include <usbd_cdc_vcp.h>

USB_OTG_CORE_HANDLE  USB_OTG_dev;


void delay_us(uint32_t volatile us) {
	us *= 12000;
	while(us--);
}

void setupUSB (void) {
    #define USB_DISC_DEV         GPIOD
    #define USB_DISC_PIN         11

	//gpio_set_mode(USB_DISC_DEV, USB_DISC_PIN, GPIO_OUTPUT_OD); // ala42
#ifdef USB_DISC_OD
  //gpio_set_mode(USB_DISC_DEV, USB_DISC_PIN, GPIO_OUTPUT_OD); // ala42
#else
  //gpio_set_mode(USB_DISC_DEV, USB_DISC_PIN, GPIO_OUTPUT_PP); // ala42 for active pull-up on disconnect pin
#endif

  //gpio_write_bit(USB_DISC_DEV, USB_DISC_PIN,0); // ala42
 // delay_us(200);

  /* setup the apb clock for USB */
  //RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE) ;


  /* initialize the usb application */
  //gpio_write_bit(USB_DISC_DEV, USB_DISC_PIN, 1); // ala42 // presents us to the host
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_cb,
            &USR_cb);
  //GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
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
  USBD_DeInitFull(&USB_OTG_dev);
  return USB_SUCCESS;
}
void usbDsbISR(void) {};

#include "usb_dcd_int.h"
void OTG_FS_IRQHandler(void) {
  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}