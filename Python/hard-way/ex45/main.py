import datetime
import random
total_clicks = 0
combos = 0
inGame = True
difficulty = 45000 #within 50000microseconds from 1bps. 
talent = 7000
compliments = [ 
    "Much good. Very accurate. Wow.",
    "Many talents. Such Timing. Wow.",
    "Many skill. Much talent.",
    "What great talent!",
    "So stronk!",
    "No one is better than you.",
    "No way! How you do that?",
    "Recognizing talent...",
    "Observing greatness...",
    "Calculating skill...",
    "You're pretty.",
    "You're the most beautiful person playing this game.",
    "You're special to me!",
    "If I ever needed a slave, it'd be you!",
    "If you were any more massive, you'd be a blackhole.",
    "If you were a cheese, you'd be American.",
    "You get a bronze metal!",
    "You get a fiesta.",
    "You get joy.",
    "I don't even know.",
    "If I were a boy, I think I would understand.",
    "Compliment get.",
    "Achievement get.",
    "Joy get."]
    

    


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


print( "Press any key at 1 beat per second... q to quit" )
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
        if time_delta.seconds == 1 and time_delta.microseconds < difficulty:
            combos += 1
            if time_delta.microseconds < talent:
                isTalented = True
            else:
                isTalented = False
        elif time_delta.seconds == 0 and time_delta.microseconds > (1000000 - difficulty):
            if time_delta.microseconds > (1000000 - talent):
                isTalented = True
            else:
                isTalented = False
            combos += 1
        else:
            combos = 0
        prev_time = time_delta
        time_delta_str = str(time_delta).replace('.', ':')
        if combos == 0:
            print("%i\t%s" % (total_clicks, time_delta_str))
        else:
            if isTalented:
                rand = random.randint(0, len(compliments))
                print("%i\t%s\tSuper Combo: %i\t%s" % (total_clicks, time_delta_str, combos, compliments[rand]))
            else:
                print("%i\t%s\tCombo:%i" % (total_clicks, time_delta_str, combos))
        start_time = end_time
    else:
        start_key = end_key
        total_clicks = 0
        combos = 0

