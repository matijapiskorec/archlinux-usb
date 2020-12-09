# Brave browser

To install Brave - a privacy oriented browser based on Chromium:
```
sudo pacman -Syu brave
```

## Vimium extension 

You can also install Vimium extension for it! Here are the shortcuts:
<https://github.com/philc/vimium/blob/master/README.md>

Keybindings for Vimium (copy/paste from the official documentation):

Once you have Vimium installed, you can see this list of key bindings at any time by typing `?`.

Navigating the current page:

    ?       show the help dialog for a list of all available keys
    h       scroll left
    j       scroll down
    k       scroll up
    l       scroll right
    gg      scroll to top of the page
    G       scroll to bottom of the page
    d       scroll down half a page
    u       scroll up half a page
    f       open a link in the current tab
    F       open a link in a new tab
    r       reload
    gs      view source
    i       enter insert mode -- all commands will be ignored until you hit Esc to exit
    yy      copy the current url to the clipboard
    yf      copy a link url to the clipboard
    gf      cycle forward to the next frame
    gF      focus the main/top frame

Navigating to new pages:

    o       Open URL, bookmark, or history entry
    O       Open URL, bookmark, history entry in a new tab
    b       Open bookmark
    B       Open bookmark in a new tab

Using find:

    /       enter find mode
              -- type your search query and hit enter to search, or Esc to cancel
    n       cycle forward to the next find match
    N       cycle backward to the previous find match

For advanced usage, see [regular expressions](https://github.com/philc/vimium/wiki/Find-Mode) on the wiki.

Navigating your history:

    H       go back in history
    L       go forward in history

Manipulating tabs:

    J, gT   go one tab left
    K, gt   go one tab right
    g0      go to the first tab
    g$      go to the last tab
    ^       visit the previously-visited tab
    t       create tab
    yt      duplicate current tab
    x       close current tab
    X       restore closed tab (i.e. unwind the 'x' command)
    T       search through your open tabs
    W       move current tab to new window
    <a-p>   pin/unpin current tab

Using marks:

    ma, mA  set local mark "a" (global mark "A")
    `a, `A  jump to local mark "a" (global mark "A")
    ``      jump back to the position before the previous jump
              -- that is, before the previous gg, G, n, N, / or `a

Additional advanced browsing commands:

    ]], [[  Follow the link labeled 'next' or '>' ('previous' or '<')
              - helpful for browsing paginated sites
    <a-f>   open multiple links in a new tab
    gi      focus the first (or n-th) text input box on the page
    gu      go up one level in the URL hierarchy
    gU      go up to root of the URL hierarchy
    ge      edit the current URL
    gE      edit the current URL and open in a new tab
    zH      scroll all the way left
    zL      scroll all the way right
    v       enter visual mode; use p/P to paste-and-go, use y to yank
    V       enter visual line mode

Vimium supports command repetition so, for example, hitting `5t` will open 5 tabs in rapid succession. `<Esc>` (or
`<c-[>`) will clear any partial commands in the queue and will also exit insert and find modes.

## Setting as the default browser

You can set Brave as the default browser from within the Settings. It works for Syncthing and Jupyter at least.

## Running Brave from the command line

To run Brave from the command line while using a prespecified link:
```
brave "https://aldaily.com" &>/dev/null
```

If you want to open localhost you need to prepend `http://` at the beginning (Firefox works without this for example):
```
brave "http://localhost:8000" &>/dev/null
```

## Profiling memory usage

To open Brave's task manager (you can also go to Menu - More Tools - Task Manager): `Shift+Esc`

There you can see CPU and memory usage for each tab in your browser separately. You can also do a right click and select Javascript memory to show column with Javascript memory of each tab.

For a more detailed memory report you can go to Dev Tools (Menu - More Tools - Developer Tools): `Ctrl-Shift-i`

From there you can select a Memory tab to see memory usage for all Javascript VM instances on a current page - it even shows workers!

