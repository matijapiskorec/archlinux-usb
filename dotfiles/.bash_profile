#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

# Color terminal on tty
source ~/Themes/wal-blue/colors-tty.sh

# Basic Arch system information on first login
if ! { [ "$TERM" = "screen" ] && [ -n "$TMUX" ]; } then
  archey3
fi
