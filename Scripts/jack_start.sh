#!/bin/bash
jack_control start
jack_control eps realtime true
jack_control ds alsa
jack_control dps device hw:0,3 		#See aplay -l for options.
jack_control dps rate 48000
jack_control dps nperiods 2
jack_control dps period 64
