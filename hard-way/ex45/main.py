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

boolean inGame = True
while inGame:
    end_key = getch()
    if end_key == 'q':
        inGame = false
    elif end_key == start_key
        end_time = time.time()
        diff_time = end_time - start_time
        

