# Game_of_Life

Proof of concept Conway's Game of Life.

![](gol.GIF)

# Todo
+ load() doesnt work
+ save() can segfault somehow; dunno how to recreate the bug tho

# Notes
+ resizing the window will lead to either stripping balls or (more likely) a crash
+ if one loads a fauna that was saved under different screen size
	everything is gonna be offset; however i hardly care
+ an insanely sized screen will cause int overflows and abnormal behaviour
