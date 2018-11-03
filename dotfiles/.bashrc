#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
alias less='less -Q'
alias man='man -P "less -Q"'

# Cool colored prompt (git removed because we have it bellow)
# https://stackoverflow.com/questions/4133904/ps1-line-with-git-current-branch-and-colors
function color_my_prompt {
    local __user_and_host="\[\033[01;32m\]\u\[\033[01;34m\]@\h"
    local __cur_location="\[\033[01;34m\]\w"
    local __git_branch_color="\[\033[31m\]"
    local __git_branch='`git branch 2> /dev/null | grep -e ^* | sed -E  s/^\\\\\*\ \(.+\)$/\(\\\\\1\)\ /`'
    local __prompt_tail="\n\[\033[35m\]>"
    local __last_color="\[\033[00m\]"
    export PS1="$__user_and_host $__cur_location $__git_branch_color$__git_branch$__prompt_tail$__last_color "
    #export PS1="$__user_and_host $__cur_location $__prompt_tail$__last_color "
}
color_my_prompt

# Fancy git prompt, if you don't want to use the one above
# https://github.com/magicmonty/bash-git-prompt
GIT_PROMPT_ONLY_IN_REPO=1
source ~/.bash-git-prompt/gitprompt.sh

# Several fallback prompts
#PS1='> '
#PS1='[\u@\h \W]\$ '
#PS1='\[\033[1;33m\]\u\]\[\033[1;37m\]@\[\033[1;32m\]\h \[\e[1;36m\][\l] \[\033[1;31m\][\w] \n\[\033[1;31m\]>> \[\033[00m\]'
