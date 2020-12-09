# i3 reference

Keyboard bindings for the most common i3 window manager commands. `$mod` is either `Win` or `Alt` key, depending on the i3 setup.

Create a new terminal: `$mod Enter`
Move between the windows: `$mod [arrows]`
Resize a window: `$mod r`
Split a window vertically when creating next new window: `$mod v`
Split a window horizontally when creating next new window: `$mod h`
Select parent window: `$mod a`
Toggle fullscreen: `$mod f`
Switch to another workspace: `$mod [number]`
Move window to another workspace: `$mod Shift [numbers]`
Open application launcher (dmenu): `$mod d`
Move window: `$mod Shift [arrows]`
Kill a window: `$mod Shift q`
Restart i3 (when modifying config): `$mod Shift r`

Send a window to scratchpad (floating hidden): `$mod Shift x`
Cycle scratchpad windows (show/hide if there is only one): `$mod x`
Make scratchpad window tilling again (toggle floating): `$mod Shift Space`

Default layout: `$mod e`
Stacking layout: `$mod s`
Tabbed layout: `$mod w`

Managing multiple tabbed windows side by side with default layout:
Create a window to the right: `$mod Enter`
Switch to the right window: `$mod [right arrow]`
Create a window bellow on the right corner: `$mod v`, `$mod Enter`
Switch back to the window above: `$mod [up arrow]`
Switch to the tabbed layout: `$mod w`

At startup all windows are created as children of the same root container. If you want to nest a newly created window to be a child of already existing window, first focus to the desired parent window, then execute either `$mod v` or `$mod h`. Then all newly created windows will be children of this window, including the ones you create with `dmenu`. If you execute `$mod w` all the children windows will be tabbed under the parent window. If you want to later return focus to the parent container, to create new windows higher on the hierarchy, execute `$mod a`.

