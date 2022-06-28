/***********************************************************************************
 * Low Power Library
 * Copyright (c) 2019, Colin Duffy https://github.com/duff3013
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ***********************************************************************************
 *  SnoozeUSBSerial.h
 *  Teensy 3.6
 *
 * Purpose: Low Power USB Serial Driver
 *
 **********************************************************************************/
#if defined(__MK66FX1M0__)

#ifndef SnoozeUSBSerial3_h
#define SnoozeUSBSerial3_h

#include "SnoozeBlock.h"
#include "common.h"

#define USB_SERIAL3_BUFFER_SIZE 100

class SnoozeUSBSerial3 : public SnoozeBlock, public Stream
{
private:
    virtual void enableDriver(uint8_t mode);
    virtual void disableDriver(uint8_t mode);
    virtual void clearIsrFlags(uint32_t ipsr);
    static void isr(void);
    char print_buffer[USB_SERIAL3_BUFFER_SIZE];

public:
    SnoozeUSBSerial3(void)
    {
        isDriver = true;
        isUsed = true;
    }
    virtual size_t write(uint8_t b);
    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual int available();
    virtual int read();
    virtual int peek();
    operator bool()
    {
#if (defined(USB_TRIPLE_SERIAL))
        return usb_configuration && (usb_cdc3_line_rtsdtr & USB_SERIAL_DTR) && ((uint32_t)(systick_millis_count - usb_cdc3_line_rtsdtr_millis) >= 15);
#else
        return false;
#endif
    }
};
#endif /* SnoozeUSBSerial3_h */
#endif /* __MK66FX1M0__ */
