#include <HID.h>

#include "nunchuk_hid.hpp"

constexpr uint8_t JOYSTICK_REPORT_ID = 0x04;

static const uint8_t hid_report_descriptor[] PROGMEM = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x04, // USAGE (Joystick)
    0xa1, 0x01, // COLLECTION (Application)
    0x85, JOYSTICK_REPORT_ID, // REPORT_ID
    0x05, 0x09, // USAGE_PAGE (Button)
    0x19, 0x01, // USAGE_MINIMUM (Button 1)
    0x29, 0x02, // USAGE_MAXIMUM (Button 2)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0x01, // LOGICAL_MAXIMUM (1)
    0x75, 0x01, // REPORT_SIZE (1)
    0x95, 0x02, // REPORT_COUNT (2)
    0x81, 0x02, // INPUT (Data,Var,Abs)
    0x75, 0x06, // REPORT_SIZE (6)
    0x95, 0x01, // REPORT_COUNT (1)
    0x81, 0x03, // INPUT (Cnst,Var,Abs)
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x01, // USAGE (Pointer)
    0xA1, 0x00, // COLLECTION (Physical)
    0x09, 0x30, // USAGE (x)
    0x09, 0x31, // USAGE (y)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x02, // REPORT_COUNT (2)
    0x81, 0x02, // INPUT (Data,Var,Abs)
    0xc0, // END_COLLECTION
    0xc0 // END_COLLECTION
};

nunchuk_hid::nunchuk_hid()
{
    // Setup HID report structure
    static HIDSubDescriptor node(hid_report_descriptor, sizeof(hid_report_descriptor));
    HID().AppendDescriptor(&node);
    set_state(0, 127, 127);
    send_state();
}

void nunchuk_hid::update_if_changed(const uint8_t* const nunchuk_data)
{
    if (memcmp(previous_nunchuk_data, nunchuk_data, NUNCHUK_DATA_SIZE) == 0)
    {
        return;
    }

    memcpy(previous_nunchuk_data, nunchuk_data, NUNCHUK_DATA_SIZE);
    // http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
    const uint8_t SX = nunchuk_data[0];
    const uint8_t SY = nunchuk_data[1];
    const uint8_t BC = (~nunchuk_data[5] >> 1 & 1);
    const uint8_t BZ = (~nunchuk_data[5] & 1);
    set_state((BZ << 1) | BC, SX, ~SY);
    send_state();
}

void nunchuk_hid::set_state(const uint8_t btn_state, const uint8_t x_state, const uint8_t y_state)
{
    state[0] = btn_state;
    state[1] = x_state;
    state[2] = y_state;
}

void nunchuk_hid::send_state() const
{
    HID().SendReport(JOYSTICK_REPORT_ID, state, STATE_SIZE);
}
