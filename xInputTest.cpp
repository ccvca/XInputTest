#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#include <bitset>

#include <signal.h>
#include <iomanip>

bool run = true;

static void signalHandler(int sign)
{
	run = false;
}

void coutState(XINPUT_STATE state)
{
	UINT btns = state.Gamepad.wButtons;
	
	std::bitset<sizeof(state.Gamepad.wButtons) * 8> buttons(btns);
	std::cout
		<< " PN " << state.dwPacketNumber
		<< " lT" << std::setfill(' ') << std::setw(4) << (int) state.Gamepad.bLeftTrigger
		<< " rT" << std::setfill(' ') << std::setw(4) << (int) state.Gamepad.bRightTrigger
		<< " LX" << std::setfill(' ') << std::setw(6) << (int) state.Gamepad.sThumbLX
		<< " LY" << std::setfill(' ') << std::setw(6) << (int) state.Gamepad.sThumbLY
		<< " RX" << std::setfill(' ') << std::setw(6) << (int) state.Gamepad.sThumbRX
		<< " RY" << std::setfill(' ') << std::setw(6) << (int) state.Gamepad.sThumbRY
		<< " btns " << buttons
		<< " "
			<< ((btns & XINPUT_GAMEPAD_Y             ) ? "Y " : "y ")
			<< ((btns & XINPUT_GAMEPAD_X             ) ? "X " : "x ")
			<< ((btns & XINPUT_GAMEPAD_B             ) ? "B " : "b ")
			<< ((btns & XINPUT_GAMEPAD_A             ) ? "A " : "a ")
			<< ((btns & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? "RSHOULDER " : "rshoulder ")
			<< ((btns & XINPUT_GAMEPAD_LEFT_SHOULDER ) ? "LSHOULDER " : "lshoulder ")
			<< ((btns & XINPUT_GAMEPAD_RIGHT_THUMB   ) ? "RTHUMB " : "rthumb ")
			<< ((btns & XINPUT_GAMEPAD_LEFT_THUMB    ) ? "LTHUMB " : "lthumb ")
			<< ((btns & XINPUT_GAMEPAD_BACK          ) ? "BACK " : "back ")
			<< ((btns & XINPUT_GAMEPAD_START         ) ? "START " : "start ")
			<< ((btns & XINPUT_GAMEPAD_DPAD_RIGHT    ) ? "RIGHT " : "right ")
			<< ((btns & XINPUT_GAMEPAD_DPAD_LEFT     ) ? "LEFT " : "left ")
			<< ((btns & XINPUT_GAMEPAD_DPAD_DOWN     ) ? "DOWN " : "down ")
			<< ((btns & XINPUT_GAMEPAD_DPAD_UP       ) ? "UP " : "up ")
		<< std::endl;

}


int main(int argc, char* argv[])
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	XINPUT_STATE inputState;

	std::cout << "Max supported controllers: " << XUSER_MAX_COUNT << std::endl;

	bool connected[XUSER_MAX_COUNT];
	bool firstRun = true;
	std::uint8_t vibCnt = 0;
	while (run)
	{
		for (DWORD iController = 0; iController < XUSER_MAX_COUNT; ++iController)
		{
			bool isConn = XInputGetState(iController, &inputState) == ERROR_SUCCESS;
			if (connected[iController] != isConn || firstRun)
			{
				std::cout << "Controller " << (isConn ? "" : "NOT") << " connected on Port " << iController << std::endl;
				connected[iController] = isConn;
			}
			if (!isConn)
			{
				continue;
			}
			std::cout << "Controller " << iController;
			coutState(inputState);

			XINPUT_VIBRATION vib;
			vib.wLeftMotorSpeed = vibCnt < 128 ? (2*vibCnt + 1) : 0;
			vib.wRightMotorSpeed = vibCnt < 128 ? (2*vibCnt + 1) : 0;
			XInputSetState(iController, &vib);
		}
		Sleep(250);
		firstRun = false;
		vibCnt += 16;
	}
	
	return 0;
}
