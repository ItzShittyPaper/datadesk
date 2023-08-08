# IM BACK LMAO
working on a game engine using datadesk as the map format
-----------------------------------------------------------

# DEAD PROJECT
it's a dead project now, i just moved on from programming
thank you all for your support. it means a lot.

-----------------------------------------------------------

## datadesk

the datadesk document format, includes the text-based DRAWER reference interpreter and the datadesk API.
it is an interpreted markup language that bridges the gap between images and text files.

## Compiling DRAWER

Install the required dependencies:
1. Void Linux (glibc): `sudo xbps-install ncurses ncurses-devel gcc make`
2. Arch / Manjaro:     `sudo pacman -S ncurses gcc make`
3. Debian / Ubuntu:    `sudo apt install ncurses ncurses-dev gcc make`
4. Gentoo:             `you guys should know what to install by now`

Run `make` and then `sudo make install`
When you want to update run `sudo make clean` first and then compile the new version.

## Usage

`drawer <file.ds>`
The datadesk demo file is `/etc/datadesk/demo.ds`, you can open it to see the new features.

## How to use datadesk?

datadesk has 7 main commands:

1. /s - writes a sentence to the screen, automatically placing multiple lines until the end of the command (/e).
2. /r - draws a rectangle on the screen.
3. /e - ends the /s command (and every command that has a dynamic argument number).
4. /v - draws a vertical line.
5. /h - draws a horizontal line.
6. /l - makes a list, useful for things like tables of contents or some shit. can make categories and subcategories with '<' and '>'.
7. /  - used only once, "/" means the scene root in a datadesk source file.

There are also arguments for certain commands like /s:

1. 'B' - makes text bold
2. 'L' - enables line numbering
3. 'U' - underlines text
(you can combine these args AFAIK)

The language uses a pass-based syntax in which the return key separates different passes.
This approach makes writing software with datadesk in mind really easy.
It works like this:

- 1st pass: the y coordinate
- 2nd pass: the x coordinate
- 3rd pass: the command / a character

If the 3rd pass is a command there are arguments after the pass; Technically these are called "Optional passes".
The y coordinate is specified first because ncurses works the same way.
Even if it feels weird at first, it is really simple in the long run.
This decision makes sense because when talking people first specify the row (y), and then the column (x).

more info on my blog https://makulaturka.tk/datadesk/
