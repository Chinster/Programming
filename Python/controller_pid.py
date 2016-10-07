import matplotlib.pyplot as plt
import matplotlib.lines as lines
import matplotlib.transforms as mtransforms
import matplotlib.text as mtext

import random
#import antigravity

ERROR = 1.0

# True states of the system
acceleration = 0
speed = 0

# PID constants
KP = 1.0
KD = 0
KI = 0

# Drawing Class.
class MyLine(lines.Line2D):
    def __init__(self, *args, **kwargs):
        # we'll update the position when the line data is set
        self.text = mtext.Text(0, 0, '')
        lines.Line2D.__init__(self, *args, **kwargs)

        # we can't access the label attr until *after* the line is
        # inited
        self.text.set_text(self.get_label())

    def set_figure(self, figure):
        self.text.set_figure(figure)
        lines.Line2D.set_figure(self, figure)

    def set_axes(self, axes):
        self.text.set_axes(axes)
        lines.Line2D.set_axes(self, axes)

    def set_transform(self, transform):
        # 2 pixel offset
        texttrans = transform + mtransforms.Affine2D().translate(2, 2)
        self.text.set_transform(texttrans)
        lines.Line2D.set_transform(self, transform)

    def set_data(self, x, y):
        if len(x):
            self.text.set_position((x[-1], y[-1]))

        lines.Line2D.set_data(self, x, y)

    def draw(self, renderer):
        # draw my label at the end of the line with 2 pixel offset
        lines.Line2D.draw(self, renderer)
        self.text.draw(renderer)

def fake_thrusters(speed):
    acceleration += error * THRUST_ERR + speed

def fake_sensor_speed():
    error = random.random() - .5;
    return speed + error * ERROR;

def fake_sensor_accel():
    error = random.random() - .5;
    return acceleration + error * ERROR;

def pid_control(targetSpeed):
    error = targetSpeed - fake_sensor_speed()
    return 0


def main():
    fig, ax = plt.subplots()
    fig.set_size_inches(6, 6)
    target_speed = 500
    speed = 0
    x = [] # Represents time
    y = [] # Graph starts at zero

    for z in range(0, 3):
        x.append(z)
        y.append(speed)
        speed += acceleration

        sense_speed = fake_sensor_speed()
        output = pid_control(target_speed)

    line = MyLine(x, y, mfc='red', ms=12)
    ax.add_line(line)
    plt.show()

main()

