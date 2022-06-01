#include <stdio.h>
#include "libusb.h"

#define PID 0x2722
#define VID 0xc251

int main()
{
    int r; // return value

    printf("\n\nhid driver reader is starting\n\n");

    r = libusb_init(NULL);
    if (r < 0){
        printf("ERROR: fail to init libusb code=%d\n", r);
        exit(r);
    }

    libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_INFO);

    libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, VID, PID);
    if (handle == NULL){
        printf("ERROR: failed to open device VID=0x%x, PID=0x%x\n", VID, PID);
        exit(0);
    }

    libusb_device *dev = libusb_get_device(handle);
    if (dev == NULL){
        printf("ERROR: failed to get device\n");
        exit(0);
    }

    struct libusb_device_descriptor desc;
    r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0){
        printf("ERROR: failed to get device descriptor code=%d\n", r);
        exit(r);
    }



    printf("\nDevice VID: 0x%X; PID=0x%X\n\n", VID, PID);
    unsigned char buf[100];
    r = libusb_get_string_descriptor_ascii(handle, desc.iProduct, buf, sizeof (buf));
    if (r < 0){
        printf("ERROR: failed to get product code=%d\n", r);
        exit(r);
    }
    printf("Product: %s\n", buf);

    r = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, buf, sizeof (buf));
    if (r < 0){
        printf("ERROR: failed to get manufacturer code=%d\n", r);
        exit(r);
    }
    printf("Manufacturer: %s\n", buf);

    r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, buf, sizeof (buf));
    if (r < 0){
        printf("ERROR: failed to get serial number code=%d\n", r);
        exit(r);
    }
    printf("Serial number: %s\n", buf);


    libusb_close(handle);

    return 0;
}
