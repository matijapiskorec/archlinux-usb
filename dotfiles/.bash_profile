#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

if ! { [ "$TERM" = "screen" ] && [ -n "$TMUX" ]; } then
  archey3
fi
