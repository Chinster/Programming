import datetime
total_clicks = 0
combos = 0
prev_time = datetime.timedelta(-999, -999)
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

start_time = datetime.datetime.now()
inGame = True
while inGame:
    end_key = getch()
    if end_key == 'q':
        inGame = False
    elif end_key == start_key:
        total_clicks += 1
        end_time = datetime.datetime.now()
        time_delta = end_time - start_time
        combo_delta = time_delta - prev_time
        if combo_delta.seconds == 0 and combo_delta.microseconds < 250000 and combo_delta.microseconds > -250000:
            combos += 1
        else:
            combos = 0
        prev_time = time_delta
        time_delta_str = str(time_delta).replace('.', ':')
        if combos == 0:
            print("%i\t%s" % (total_clicks, time_delta_str))
        else:
            print("%i\t%s\t%i" % (total_clicks, time_delta_str, combos))
        start_time = end_time
    else:
        start_key = end_key
        total_clicks = 0
        combos = 0

