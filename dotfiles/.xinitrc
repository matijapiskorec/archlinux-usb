# Load .Xresources
[[ -f ~/.Xresources ]] && xrdb -merge -I$HOME ~/.Xresources

setxkbmap hr
feh --bg-fill ~/Themes/wal-red/*.jpg
compton -CGb
exec i3
