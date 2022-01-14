# xmas-lights
Project using ESP-32 devices to control a bunch of (Christmas) outdoor lights using H-bridges

I have a bunch of outdoor Christmas lights. They are all essentially two channel devices and driven by various power units which come with a number of patters they can display. Each manufacturer's power pack/controller is different from others and it's impossible to sync all the lights up.

That's where this project comes in.

Generally all the lights work from a 31v dc supply that swaps polarity around 200 times a second and uses two channels of pwm (one per polarity) to control each channels brightness.

I want to build a standard controller, based around the ESP-32 and one or more H bridges. Using their on-board Wifi, they can synchronise with each other and produce a better looking display overall. 

That's the theory, anyway - let's see how it goes.
