# tmux terminal multiplexer (instead of screen)

Tmux has Session-Window-Pane hierarchy.

Start your session: `tmux`
Split pane vertically: `Ctrl-b %`
Split pane horizontally: `Ctrl-b "`
Move between panes: `Ctrl-b [arrows]`
Closing panes: `Ctrl-d`
Create a new window: `Ctrl-b c`
Switching between windows: `Ctrl-b p`, `Ctrl-b n`, `Ctrl-b [number]`
Detach current session: `Ctrl-b d`
List sessions: `tmux ls`
Attach a session: `tmux attach -t [number]`
Create a named session: `tmux new -s [name of new session] `
Rename a session: `tmux rename-session -t [number] [name of new session]`
Attach a named session: `tmux attach -t [name of session]`
Available commands: `Ctrl-b ?`
Toggle fullscreen of a pane: `Ctrl-b z`
Resize pane in direction of [arrow]: `Ctrl-b Ctrl-[arrow]`
Rename the current window: `Ctrl-b ,`

## Powerline status bar

Install powerline status bar:
```
sudo pacman -Syu powerline powerline-fonts
```

Add following to your `~/.tmux.conf`:
```
source /usr/lib/python3.7/site-packages/powerline/bindings/tmux/powerline.conf
```
