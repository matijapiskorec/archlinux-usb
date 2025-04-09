# Github Copilot

Install Github Copilot CLI for Arch Linux:
<https://github.com/cli/cli/blob/trunk/docs/install_linux.md>

```
sudo pacman -Sy github-cli
```

Setup and authentificate Github Copilot in CLI:
<https://github.com/github/gh-copilot>

```
gh auth login --web -h github.com
gh extension install github/gh-copilot --force
```

Suggest a command in the terminal:
```
gh copilot suggest "Rotate an image in terminal"
```
