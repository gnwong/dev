## this is only run for interactive shells. used for qol improvements.

# if not running interactively, don't do anything
[ -z "$PS1" ] && return

## wrap formatters

NEWLINE=$'\n'

# test return value and print error message if non-zero
RV="%(?.0.%? %F{red}error%f)"
# test for user and assign color
SU="%(!.%F{red}root%f.%F{cyan}%n%f)"

# now set prompt/term
# export PS1="\[${Purple}\] ~~~ \[${White}\][ ${RV}\[${White}\]] ${SU}@\[${Green}\]\h\[${NC}\]  \[${Yellow}\]\w\[${White}\] \n$ "
export PS1="%F{magenta} ~~~ %F{white}[ ${RV} %F{white}] ${SU}@%F{green}%m  %F{yellow}%~%f ${NEWLINE}%(!.#.$) "

## handle Darwin/Linux environments
if [[ $(uname) == "Darwin" ]]; then
  export LSCOLORS="Exgxcxdxbxegedabagacad"
  alias ls='echo -ne "${NC}"; ls -Gp'
elif [[ $(uname) == "Linux" ]]; then
  alias ls='ls --color=auto'
else
  echo "It appears you're running $(uname), which is not supported by this version of .zshrc"
fi

## set aliases
alias q="exit"
alias l="ls -l"
alias listsize="du -s * | sort -nr | awk '{print \$2}' | xargs du -sh"

## set configuration
setopt APPEND_HISTORY



