# VisiData for exploring datasets in terminal

Install VisiData from Arch repository:
```
sudo pacman -Syu visidata
```

An Introduction to VisiData
<https://jsvine.github.io/intro-to-visidata/index.html>

You can run it on a file either with the `visidata` command or the `vd` command:
```
visidata file.csv
vd file.csv
```

Frequency table: `Shift-f`

`Control-h` 	Open the help menu
`Control-c` 	Abort the current command
`Control-q` 	Force-quit VisiData entirely
`q` 	Quit the current VisiData “sheet”
`gq` 	Quit all VisiData sheets and exit gracefully
`Shift-U` 	Undo
`Shift-R` 	Redo

`gj` 	move cursor to last row
`gk` 	move cursor to first row
`gh` 	move cursor to leftmost column
`gl` 	move cursor to rightmost column
`PageDown/Control-F` 	move cursor one page down (forward)
`PageUp/Control-B` 	move cursor one page up (backward)

`/ + regex` 	Search forward in current column
`? + regex` 	Search backward in current column
`g/ + regex` 	Search forward in all columns
`g? + regex` 	Search backward in all columns

n 	Move to next matching row
N 	Move to previous matching row
c + regex 	Jump to the next matching column
zr + n 	Jump to row number n
zc + n 	Jump to column number n

s 	Select the current row
u 	Unselect the current row
t 	Toggle the current row between selected/unselected

gs 	Select all rows
gu 	Unselect all rows
gt 	Toggle all rows between selected/unselected

| + term 	Select all rows where term matches the current column
\ + term 	Unselect all rows where term matches the current column
g| + term 	Select all rows where term matches any column
g\ + term 	Unselect all rows where term matches any column
, 	Select all rows where the current column matches this row’s value for that column
g, 	Select all rows matching the current row (for all non-hidden columns)

z| + expr 	Select all rows where expr evaluates to True
z\ + expr 	Unselect all rows where expr evaluates to True

