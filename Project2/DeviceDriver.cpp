#include "DeviceDriver.h"
#include <cstdio>
#include <windows.h>
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int firstReaeValue = (int)(m_hardware->read(address));
    for (int tryCount = 1; tryCount < 5; tryCount++)
    {
        Sleep(SLEEP_TIME);
        int nextReadValue = (int)(m_hardware->read(address));
        if (nextReadValue == firstReaeValue) continue;
        throw std::exception("Exception!!");
    }
    return firstReaeValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}