#!/usr/bin/env python3
import asyncio
from enum import Enum

# Enum for controller events. Values are completely arbitrary.
class Button(Enum):
    A, B, X, Y = range(0, 4)
    LStick, RStick, LTrigger, RTrigger = range(4, 8)
    L3, R3, LB, RB = range(8, 12)
    DpadU, DpadD, DpadL, DpadR = range(12, 16)
    Back = 16
    Start = 17
    Guide = 18   # This is the Xbox button on the Xbox controller

class Joystick:
    @asyncio.coroutine
    def init():
        self.proc = yield from asyncio.create_subprocess_exec('./fake.sh',
                                                 #"--no-uintput",
                                                 #"--detach-kernel-driver"],
                                                 stdout=asyncio.subprocess.PIPE)

        while True:
            line = yield from process.stdout.readline()
            if line:
                call_handlers(line)
            else:
                break

        return process

    def onButton(button, callback):
        self.handlers[button].append(callback)

    # Each handler will parse its portion of the input line
    def call_handlers(line):
        print(line)
        self.handleLStick(line)
        self.handleRStick(line)
        self.handleDpad(line)
        self.handleSpecial(line)
        self.handleActionButtons(line)
        self.handleBumpers(line)
        self.handleTriggers(line)

    def handleLStick(line):
        print("leftX: %s" % line[3:9])
        print("leftY: %s" % line[13:19])

        if self.handlers[Button.LStick]:
            leftX = self.axisScale(int(line[3:9]))
            leftY = self.axisScale(int(line[13:19]))
            for cb in self.handlers[Button.LStick]:
                cb(leftX, leftY)

        # "Clicking" the left analog stick
        if self.handlers[Button.L3] and int(line[90:91]):
            for cb in self.handlers[Button.L3]:
                cb()

    def handleRStick(line):
        if self.handlers[Button.RStick]:
            rightX = self.axisScale(int(line[24:30]))
            rightY = self.axisScale(int(line[34:40]))
            for cb in self.handlers[Button.LStick]:
                cb(leftX, leftY)

        # "Clicking" the left analog stick
        if self.handlers[Button.R3] and int(line[95:96]):
            for cb in self.handlers[Button.R3]:
                cb()

    def handleDpad(line):
        if self.handlers[Button.DpadU] and int(line[45:46]):
            for cb in self.handlers[Button.DpadU]:
                cb()

        if self.handlers[Button.DpadD] and int(line[50:51]):
            for cb in self.handlers[Button.DpadD]:
                cb()

        if self.handlers[Button.DpadL] and int(line[55:56]):
            for cb in self.handlers[Button.DpadL]:
                cb()

        if self.handlers[Button.DpadR] and int(line[60:61]):
            for cb in self.handlers[Button.DpadR]:
                cb()

    def handleSpecialButtons(line):
        if self.handlers([Button.Back]) and int(line[68:69]):
            for cb in self.handlers[Button.Back]:
                cb()

        if self.handlers([Button.Guide]) and int(line[76:77]):
            for cb in self.handlers[Button.Guide]:
                cb()

        if self.handlers([Button.Start]) and int(line[84:85]):
            for cb in self.handlers[Button.Start]:
                cb()

    def handleActionButtons(line):
        if self.handlers([Button.A]) and int(line[100:101]):
            for cb in self.handlers[Button.A]:
                cb()

        if self.handlers([Button.B]) and int(line[104:105]):
            for cb in self.handlers[Button.B]:
                cb()
        if self.handlers([Button.X]) and int(line[108:109]):
            for cb in self.handlers[Button.X]:
                cb()
        if self.handlers([Button.Y]) and int(line[112:113]):
            for cb in self.handlers[Button.Y]:
                cb()

    def handleBumpers(line):
        if self.handlers([Button.LB]) and int(line[118:119]):
            for cb in self.handlers[Button.LB]:
                cb()

        if self.handlers([Button.RB]) and int(line[123:124]):
            for cb in self.handlers[Button.RB]:
                cb()

    def handleTriggers(line):
        if self.handlers([Button.LTrigger]):
            for cb in self.handlers[Button.LTrigger]:
                cb(int(line[129:132]) / 255.0)    # scale trigger values from 0 to 1

        if self.handlers([Button.RTrigger]):
            for cb in self.handlers[Button.RTrigger]:
                cb(int(line[136:139]) / 255.0)    # scale trigger values from 0 to 1

    # Scale raw (-32768 to +32767) axis to -1.0 to 1.0 with deadzones
    # Deadzone is +/- range of values to consider to be center stick (i.e. 0.0)
    def axisScale(self, raw, deadzone=4000):
        if abs(raw) < deadzone:
            return 0.0
        else:
            if raw < 0:
                return (raw + deadzone) / (32768.0 - deadzone)
            else:
                return (raw - deadzone) / (32767.0 - deadzone)

    def close():
        self.proc.kill()


if __name__ == "__main__":
    if sys.platform == "win32":
        loop = asyncio.ProactorEventLoop()
        asyncio.set_event_loop(loop)
    else:
        loop = asyncio.get_event_loop()

    joy = Joystick.init()
    joy.onButton(Button.A, lambda: print('Hi'))
    loop.run_until_complete(joy)
    joy.close()
