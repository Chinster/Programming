"""Gets a single char."""
class Getch:
    def __init__(self):
        try:
            self.impl = GetchWindows()
        except ImportError:
            self.impl = GetchUnix()
    def __call__(self):
        return self.impl()

class GetchUnix:
    def __init__(self):
        import tty, sys
    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

class GetchWindows:
    def __init__(self):
        import msvcrt
    def __call__(self):
        import msvcrt
        return msvcrt.getch()

getch = Getch()
print( "Press a key repeatedly... q to quit" )
start_key = getch()

import time
start_time = time.time()

inGame = True
while inGame:
    end_key = getch()
    if end_key == 'q':
        inGame = False
    elif end_key == start_key:
        end_time = time.time()
        diff_time = end_time - start_time
        diff_tots = int(diff_time)
        diff_ms = (diff_time - diff_tots) * 3
        diff_s = diff_tots % 60
        diff_m = (diff_tots / 60) % 60
        diff_h = diff_tots / 3600
        print( "%i:%i:%i:%f" % (diff_h, diff_m, diff_s, diff_ms ) )
        start_time = end_time
    else:
        start_key = end_key

