# Spells 'n' Curses

***Spells 'n' curses*** (pun intended) is a simple roguelike game written in C, using ncurses, and initially following [this tutorial](https://github.com/wadsworj/rogue).

## Build and run

You should have `gcc`, `make`, `libncurses5-dev` and `libncursesw5-dev` installed with:

```console
$ sudo apt install gcc make libncurses5-dev libncursesw5-dev
```

on Debian-based systems, or: 

```console
$ sudo pacman -S gcc make libncurses5-dev libncursesw5-dev
```

on Arch-based systems, or the equivalent on others. Then you just need to type:

```console
$ make
```

to build, and run with:

```console
$ ./spells_curses
```

### Notes

`gcc` is needed because `__attribute--((fallthrough))` is gcc-specific.

EOF
