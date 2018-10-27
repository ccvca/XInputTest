# XInputTest
This is a simple command line tool for testing XInput devices. It fetches the state of all availiable devices and prints the state of all axes and buttons.

## Sample output
    Max supported controllers: 4
    Controller  connected on Port 0
    Controller 0 PN 1334126046 lT   0 rT   0 LX     0 LY     0 RX     0 RY     0 btns 0000000000000000 y x b a rshoulder lshoulder rthumb lthumb back start right left down up
    Controller NOT connected on Port 1
    Controller NOT connected on Port 2
    Controller NOT connected on Port 3
    Controller 0 PN 1334126625 lT   0 rT   0 LX -2048 LY  1535 RX 29439 RY 21503 btns 0000001000000000 y x b a RSHOULDER lshoulder rthumb lthumb back start right left down up
    Controller 0 PN 1334126921 lT 196 rT   0 LX-32768 LY -5632 RX 31999 RY 13055 btns 1010001110000000 Y x B a RSHOULDER LSHOULDER RTHUMB lthumb back start right left down up

## Build
 * The library `Xinput.lib` must be added to the linker.
 * Tested with Microsoft Visual Studio 2017
