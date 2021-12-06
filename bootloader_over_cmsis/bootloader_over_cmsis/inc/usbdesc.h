#ifndef __USBDESC_H_INCLUDED__
#define __USBDESC_H_INCLUDED__

#include "usb_functions.h" // refactoring required .. alot

#define WBVAL(q) ((q & 0xFF),((q >> 8) & 0xFF))

/* USB Standard Device Descriptor */
typedef struct __attribute__ ((packed)) _USB_DEVICE_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
    U16 bcdUSB;
    U8  bDeviceClass;
    U8  bDeviceSubClass;
    U8  bDeviceProtocol;
    U8  bMaxPacketSize0;
    U16 idVendor;
    U16 idProduct;
    U16 bcdDevice;
    U8  iManufacturer;
    U8  iProduct;
    U8  iSerialNumber;
    U8  bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;
/* USB Standard Configuration Descriptor */

typedef struct __attribute__ ((packed)) _USB_CONFIGURATION_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
    U16 wTotalLength;
    U8  bNumInterfaces;
    U8  bConfigurationValue;
    U8  iConfiguration;
    U8  bmAttributes;
    U8  bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;

/* USB Standard Interface Descriptor */
typedef struct __attribute__ ((packed)) _USB_INTERFACE_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
    U8  bInterfaceNumber;
    U8  bAlternateSetting;
    U8  bNumEndpoints;
    U8  bInterfaceClass;
    U8  bInterfaceSubClass;
    U8  bInterfaceProtocol;
    U8  iInterface;
} USB_INTERFACE_DESCRIPTOR;

/* USB HID Descriptor */
typedef struct __attribute__ ((packed)) _USB_HID_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
    U16  bcdHID;
    U8  bCountryCode;
    U8  bNumDescriptors;
    U8	hid_report_desc_type;
    U16	wItemLength;
} USB_HID_DESCRIPTOR;

/* USB Standard Endpoint Descriptor */
typedef struct __attribute__ ((packed)) _USB_ENDPOINT_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
    U8  bEndpointAddress;
    U8  bmAttributes;
    U16 wMaxPacketSize;
    U8  bInterval;
} USB_ENDPOINT_DESCRIPTOR;

/* USB String Descriptor */

typedef struct __attribute__ ((packed)) _USB_STRING_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
    U16 bString;
} USB_STRING_DESCRIPTOR;

#define USB_DEVICE_DESC_SIZE        (sizeof(USB_DEVICE_DESCRIPTOR))
#define USB_CONFIGUARTION_DESC_SIZE (sizeof(USB_CONFIGURATION_DESCRIPTOR))
#define USB_INTERFACE_DESC_SIZE     (sizeof(USB_INTERFACE_DESCRIPTOR))
#define USB_ENDPOINT_DESC_SIZE      (sizeof(USB_ENDPOINT_DESCRIPTOR))
#define USB_HID_DESC_SIZE     			(sizeof(USB_HID_DESCRIPTOR))
//#define USB_STRING_DESCRIPTOR_SIZE 	(sizeof(USB_STRING_DESCRIPTOR))

extern const U8  USB_DeviceDescriptor_msc[];
extern const U8  USB_DeviceDescriptor_cdc[];
extern const U8  USB_DeviceDescriptor_hid[];
extern const U8  USB_ConfigDescriptor_msc[];
extern const U8  USB_ConfigDescriptor_cdc[];
extern const U8  USB_ConfigDescriptor_hid[];
extern const U8  USB_StringDescriptor[];
extern const U8 ReportDescriptor[];
extern const U8 HidDescriptor[];

typedef  struct __attribute__ ((packed)) _USB_COMMON_DESCRIPTOR
{
    U8  bLength;
    U8  bDescriptorType;
} USB_COMMON_DESCRIPTOR;

extern unsigned char line_coding[7];

#endif /* __USBDESC_H_INCLUDED__ */
