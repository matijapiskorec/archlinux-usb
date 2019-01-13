# Micro terminal text editor

Micro is terminal-based text editor that is lightweight and meant as a replacement for nano, with usual keybindings.

Webpage: https://github.com/zyedidia/micro#installation

Download a binary:
```
curl https://getmic.ro | bash
```

Then simply copy it to `/usr/local/bin` directory:
```
sudo mv micro /usr/local/bin/.
```

Unlike Sublime Text, you can pipe text into micro for easier copy/pasting. For example, pipe a polkit man page to micro by choosing cat as an alternative pager instead of less:
```
man -P cat polkit | micro
```