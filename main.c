#include <stdio.h>
#include "libusb.h"

#define PID 0x2722
#define VID 0xc251

int main()
{
    int r; // return value

    printf("Hello World!\n");

    r = libusb_init(NULL);
    if (r < 0)
        printf("ERROR: fail to init libusb code=%d\n", r);

    libusb_set_debug(NULL, 3);

    libusb_device **list;
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    if (cnt < 0)
        printf("ERROR: failed to get device list code=%zd\n", cnt);

    for(ssize_t i = 0; i < cnt; i++){
        libusb_device *dev = list[i];
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0)
            printf("ERROR: failed to get device descriptor code=%d\n", r);

        if (desc.idVendor == VID){

            if (desc.idProduct == PID){
                libusb_device_handle *handle;
                r = libusb_open(dev, &handle);
                if (r < 0)
                    printf("ERROR: failed to open device code=%d\n", r);

                char buf[100];
                r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, buf, sizeof (buf));
                if (r < 0)
                    printf("ERROR: failed to get serial number code=%d\n", r);

                printf("\n\n%s\n\n", buf);
            }
        }
    }

    return 0;
}
