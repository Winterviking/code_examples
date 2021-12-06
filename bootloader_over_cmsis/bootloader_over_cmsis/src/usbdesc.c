//=============================================================
//=============================================================
//
// ������� �������, ����������� ��� �����
//
//=============================================================
//=============================================================

#include "usbdesc.h"

//**********************************************************************************
// USB Standard Device Descriptor
const U8 USB_DeviceDescriptor_msc[] =
{
    USB_DEVICE_DESC_SIZE,              	// bLength
    USB_DEVICE_DESCRIPTOR_TYPE,        	// bDescriptorType
    0x00,0x02,													// bcdUSB
    0x00,                              	// bDeviceClass
    0x00,                              	// bDeviceSubClass
    0x00,                              	// bDeviceProtocol
    USB_MAX_PACKET0,                   	// bMaxPacketSize0 //64bytes
    0xE9, 0x27,//  0xc0,0x16,           // idVendor
    0x03, 0xB4,//  0xdf,0x05,           // idProduct
    0x00,0x01,													// bcdDevice
    0x01,                              	// iManufacturer
    0x02,                              	// iProduct
    0x03,                              	// iSerialNumber
    0x01                               	// bNumConfigurations: one possible configuration
};

//**********************************************************************************
// USB Configuration Descriptor
//   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor)
const unsigned short dd_msc=
    USB_CONFIGUARTION_DESC_SIZE +
    USB_INTERFACE_DESC_SIZE     +
    USB_ENDPOINT_DESC_SIZE			+
    USB_ENDPOINT_DESC_SIZE;

/*
const U8 USB_ConfigDescriptor_msc[] = {
																			//Configuration 1
  USB_CONFIGUARTION_DESC_SIZE,       	// bLength
  USB_CONFIGURATION_DESCRIPTOR_TYPE,	// bDescriptorType
	dd_msc&0xFF,(dd_msc>>8)&0xFF,								// wTotalLength
  0x01,                              	// bNumInterfaces
  0x01,                              	// bConfigurationValue: 0x01 is used to select this configuration
  0x00,                              	// iConfiguration: no string to describe this configuration
  0xC0,        		 										// bmAttributes //����������������
  0x32,          											// bMaxPower, device power consumption is 100 mA

//���������
	USB_INTERFACE_DESC_SIZE,//������ ����������� ����������
	USB_INTERFACE_DESCRIPTOR_TYPE,//��� ����������� - ���������
	0,//����� ����������� ����������
	0,//�������������� ����������
	2,//���������� �������� ����� ����������
	0x08,//��� ������ // mass storage bulk only
	0x06,//��� ���������
	0x50,//��� ���������
	0,//������ ���������� �����������

//���������� �������� �����
	USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
	USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
	0x81,//����� �������� ����� = 1, ����������� in
	0x02,//��� bulk
	0x40,0x00,//������������ ������ ������ ��� �����
	0x00,//�������� ������ (������������ ��� bulk)

//���������� �������� �����
	USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
	USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
	0x02,//����� �������� ����� = 2, ����������� out
	0x02,//��� bulk
	0x40,0x00,//������������ ������ ������ ��� �����
	0x00//�������� ������ (������������ ��� bulk)
};
*/
//**********************************************************************************
/*
// USB String Descriptor (optional)
const U8 USB_StringDescriptor[] = {
// Index 0x00: LANGID Codes
  0x04,                             // bLength
  USB_STRING_DESCRIPTOR_TYPE,       // bDescriptorType
  0x09,0x04,												// US English wLANGID
// Index 0x01: Manufacturer
  (8*2 + 2),                        // bLength (13 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,       // bDescriptorType
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
// Index 0x02: Product
  (10*2 + 2),                        // bLength (17 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
// Index 0x03: Serial Number
  (4*2 + 2),                        // bLength (12 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
  '1',0,                             // allowed characters are
  '1',0,                             //   0x0030 - 0x0039 ('0'..'9')
  '1',0,                             //   0x0041 - 0x0046 ('A'..'F')
  '1',0,                             //   length >= 26
// Index 0x04: Interface 0, Alternate Setting 0
  ( 3*2 + 2),                        // bLength (3 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
  'A',0,
  'A',0,
  'A',0,
};
*/

//**********************************************************************************
// USB Standard Device Descriptor
const U8 USB_DeviceDescriptor_cdc[] =
{
    USB_DEVICE_DESC_SIZE,              	// bLength
    USB_DEVICE_DESCRIPTOR_TYPE,        	// bDescriptorType
    0x00,0x02,													// bcdUSB
    0x02,                              	// bDeviceClass    //2-cdc
    0x00,                              	// bDeviceSubClass
    0x00,                              	// bDeviceProtocol
    USB_MAX_PACKET0,                   	// bMaxPacketSize0 //64bytes
    0xD8, 0x04,//  0xc0,0x16,  c251         // idVendor 04D8&PID_FD92
    0x92, 0xFD,//  0xdf,0x05,  1705         // idProduct
    //0xE9, 0x27,//  0xc0,0x16,           // idVendor
    //0x03, 0xB4,//  0xdf,0x05,           // idProduct
    0x00,0x01,													// bcdDevice
    0x01,                              	// iManufacturer
    0x02,                              	// iProduct
    0x03,                              	// iSerialNumber
    0x01                               	// bNumConfigurations: one possible configuration
};


// USB Configuration Descriptor
//   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor)
#define dd_cdc (USB_CONFIGUARTION_DESC_SIZE+USB_INTERFACE_DESC_SIZE+19+USB_ENDPOINT_DESC_SIZE+USB_INTERFACE_DESC_SIZE+USB_ENDPOINT_DESC_SIZE+USB_ENDPOINT_DESC_SIZE)

const U8 USB_ConfigDescriptor_cdc[] =
{
    //Configuration 1
    USB_CONFIGUARTION_DESC_SIZE,       	// bLength
    USB_CONFIGURATION_DESCRIPTOR_TYPE,	// bDescriptorType
    dd_cdc&0xFF,(dd_cdc>>8)&0xFF,								// wTotalLength
    0x02,                              	// bNumInterfaces
    0x01,                              	// bConfigurationValue: 0x01 is used to select this configuration
    0x00,                              	// iConfiguration: no string to describe this configuration
    0xC0,        		 										// bmAttributes //����������������
    0x32,          											// bMaxPower, device power consumption is 100 mA

//��������� ����������
    USB_INTERFACE_DESC_SIZE,//������ ����������� ����������
    USB_INTERFACE_DESCRIPTOR_TYPE,//��� ����������� - ���������
    0,//����� ����������� ����������
    0,//�������������� ����������
    1,//���������� �������� ����� ����������
    2,//��� ������ CDC comm
    2,//��� ���������
    1,//��� ���������
    0,//������ ���������� �����������

//����������� CDC
    0x05, 0x24, 0x00, 0x00, 0x02, //������������ ����������
    0x05, 0x24, 0x01, 0x00, 0x01, //���������� ������ ������
    0x04, 0x24, 0x02, 0x00,       //���������� ������������ ����������
    0x05, 0x24, 0x06, 0x00, 0x01, //���������� �������������

//���������� �������� �����
    USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
    USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
    0x83,//����� �������� ����� = 3, ����������� in
    0x03,//��� interrupt
    0x20,0x00,//������������ ������ ������ ��� �����
    0x02,//�������� ������ ��� ����� ���� interrupt

//��������� ������
    USB_INTERFACE_DESC_SIZE,//������ ����������� ����������
    USB_INTERFACE_DESCRIPTOR_TYPE,//��� ����������� - ���������
    1,//����� ����������� ����������
    0,//�������������� ����������
    2,//���������� �������� ����� ����������
    0x0A,//��� ������ // CDC ACM Data
    0,//��� ���������
    0,//��� ���������
    0,//������ ���������� �����������

//���������� �������� �����
    USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
    USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
    0x81,//����� �������� ����� = 1, ����������� in
    0x02,//��� bulk
    0x20,0x00,//������������ ������ ������ ��� �����
    0x00,//�������� ������ (������������ ��� bulk)

//���������� �������� �����
    USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
    USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
    0x02,//����� �������� ����� = 2, ����������� out
    0x02,//��� bulk
    0x40,0x00,//������������ ������ ������ ��� �����
    0x00//�������� ������ (������������ ��� bulk)
};

/*
// USB String Descriptor (optional)
const U8 USB_StringDescriptor[] = {
// Index 0x00: LANGID Codes
  0x04,                             // bLength
  USB_STRING_DESCRIPTOR_TYPE,       // bDescriptorType
  0x09,0x04,												// US English wLANGID
// Index 0x01: Manufacturer
  (8*2 + 2),                        // bLength (13 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,       // bDescriptorType
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
// Index 0x02: Product
  (10*2 + 2),                        // bLength (17 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
  'A',0,
// Index 0x03: Serial Number
  (4*2 + 2),                        // bLength (12 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
  '1',0,                             // allowed characters are
  '1',0,                             //   0x0030 - 0x0039 ('0'..'9')
  '1',0,                             //   0x0041 - 0x0046 ('A'..'F')
  '1',0,                             //   length >= 26
// Index 0x04: Interface 0, Alternate Setting 0
  ( 3*2 + 2),                        // bLength (3 Char + Type + lenght)
  USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
  'A',0,
  'A',0,
  'A',0,
};
*/

//**********************************************************************************
// USB Standard Device Descriptor
const U8 USB_DeviceDescriptor_hid[] =
{
    USB_DEVICE_DESC_SIZE,              	// bLength
    USB_DEVICE_DESCRIPTOR_TYPE,        	// bDescriptorType
    0x10,0x01,													// bcdUSB
    0x00,                              	// bDeviceClass
    0x00,                              	// bDeviceSubClass
    0x00,                              	// bDeviceProtocol
    USB_MAX_PACKET0,                   	// bMaxPacketSize0 //64bytes
    0x61,0x04,           // idVendor 0461&PID0010
    0x10,0x00,           // idProduct
    0x00,0x01,													// bcdDevice
    0x01,                              	// iManufacturer
    0x02,                              	// iProduct
    0x03,                              	// iSerialNumber
    0x01                               	// bNumConfigurations: one possible configuration
};

//**********************************************************************************
// USB Configuration Descriptor
//   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor)
unsigned short dd_hid=
    USB_CONFIGUARTION_DESC_SIZE +
    USB_INTERFACE_DESC_SIZE     +
    USB_ENDPOINT_DESC_SIZE			+
    USB_ENDPOINT_DESC_SIZE			+
    USB_HID_DESC_SIZE;
/*
const U8 USB_ConfigDescriptor_hid[] = {
																			//Configuration 1
  USB_CONFIGUARTION_DESC_SIZE,       	// bLength
  USB_CONFIGURATION_DESCRIPTOR_TYPE,	// bDescriptorType
	dd_hid&0xFF,(dd_hid>>8)&0xFF,								// wTotalLength
  0x01,                              	// bNumInterfaces
  0x01,                              	// bConfigurationValue: 0x01 is used to select this configuration
  0x00,                              	// iConfiguration: no string to describe this configuration
  0xC0,        		 										// bmAttributes //����������������
  0x00,          											// bMaxPower, device power consumption is 100 mA

//���������
	USB_INTERFACE_DESC_SIZE,//������ ����������� ����������
	USB_INTERFACE_DESCRIPTOR_TYPE,//��� ����������� - ���������
	0,//����� ����������� ����������
	0,//�������������� ����������
	2,//���������� �������� ����� ����������
	0x03,//��� ������ // hid
	0x01,//��� ��������� // not boot
	0x01,//��� ��������� // keyboard
	0,//������ ���������� �����������
//HID-descriptor
	USB_HID_DESC_SIZE,
	USB_HID_DESCRIPTOR_TYPE,
	0x01, 0x01,   // bcdHID: ����� ������ HID 1.1
	0x00,         // bCountryCode: ��� ������
	0x01,         // bNumDescriptors: ���������� report ������������
	USB_HID_REPORT_DESCRIPTOR_TYPE,
	63,	0x00, // wItemLength: ����� report-�����������

//���������� �������� �����
	USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
	USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
	0x81,//����� �������� ����� = 1, ����������� in
	0x03,// - Interrupt endpoint
	0x40,0x00,//������������ ������ ������ ��� �����
  0x0A,     // bInterval: �������� ������ (100 ms)

//���������� �������� �����
	USB_ENDPOINT_DESC_SIZE,//������ ����������� �������� �����
	USB_ENDPOINT_DESCRIPTOR_TYPE,//��� ����������� - �������� �����
	0x02,//����� �������� ����� = 2, ����������� out
	0x03,// - Interrupt endpoint
	0x40,0x00,//������������ ������ ������ ��� �����
  0x0A     // bInterval: �������� ������ (32 ms)
};
*/
const U8 HidDescriptor[] =
{
    USB_HID_DESC_SIZE,
    USB_HID_DESCRIPTOR_TYPE,
    0x01, 0x01,   // bcdHID: ����� ������ HID 1.1
    0x00,         // bCountryCode: ��� ������
    0x01,         // bNumDescriptors: ���������� report ������������
    USB_HID_REPORT_DESCRIPTOR_TYPE,
    63,	0x00			// wItemLength: ����� report-�����������
};

const U8 ReportDescriptor[] =
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,                    //   REPORT_COUNT (5)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x03,                    //   REPORT_SIZE (3)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};
//**********************************************************************************

// USB String Descriptor (optional)
const U8 USB_StringDescriptor[] =
{
// Index 0x00: LANGID Codes
    0x04,                             // bLength
    USB_STRING_DESCRIPTOR_TYPE,       // bDescriptorType
    0x09,0x04,												// US English wLANGID
// Index 0x01: Manufacturer
    (8*2 + 2),                        // bLength (13 Char + Type + lenght)
    USB_STRING_DESCRIPTOR_TYPE,       // bDescriptorType
    'U',0,
    'S',0,
    'B',0,
    ' ',0,
    'P',0,
    'L',0,
    'A',0,
    'Y',0,
// Index 0x02: Product
    (3*2 + 2),                        // bLength (17 Char + Type + lenght)
    USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
    '1',0,
    '1',0,
    '1',0,
// Index 0x03: Serial Number
    (3*2 + 2),                        // bLength (12 Char + Type + lenght)
    USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
    '1',0,                             //   0x0030 - 0x0039 ('0'..'9')
    '1',0,                             //   0x0041 - 0x0046 ('A'..'F')
    '1',0,                             //   length >= 26
// Index 0x04: Interface 0, Alternate Setting 0
    ( 3*2 + 2),                        // bLength (3 Char + Type + lenght)
    USB_STRING_DESCRIPTOR_TYPE,        // bDescriptorType
    '1',0,
    '1',0,
    '1',0,
};








