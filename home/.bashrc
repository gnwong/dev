#
#   .bashrc 
#
#     CREATED:  17 JULY 2013
#     UPDATED:  27 MARCH 2014
#     AUTHOR:   George Wong

### If not running interactively, don't do anything
[ -z "$PS1" ] && return

### Colors
# Normal Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White
# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White
# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White
# Color reset
NC='\033[m'

### Test return value and print error message on unsuccessful values
RV="\[${White}\]\$? \$(if [[ \$? -ne 0 ]]; then echo \"\[${Red}\]error \"; fi)"

### Test for user and assign color
SU="\$(if [[ \${USER} == \"root\" ]]; then echo \"\[${Red}\]\u\[${NC}\]\"; else echo \"\[${Cyan}\]\u\[${NC}\]\"; fi)\[${White}\]"

### Define the prompt and term
export PS1="\[${Purple}\] ~~~ \[${White}\][ ${RV}\[${White}\]] ${SU}@\[${Green}\]\h\[${NC}\]  \[${Yellow}\]\w\[${White}\] \n$ "

### Handle Darwin vs Linux environments
if [[ $(uname) == "Darwin" ]]; then
  export LSCOLORS="Exgxcxdxbxegedabagacad"
  alias ls='echo -ne "${NC}"; ls -Gp'
elif [[ $(uname) == "Linux" ]]; then
  alias ls='ls --color=auto'
else
  echo "It appears you're running $(uname), which is unsupported by this version of .bashrc"
fi

### Aliases
alias q="exit"
alias l="ls -l"
alias la="ls -la"
alias cls='echo -e "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"'

### Configuration
shopt -s histappend     #append to history
shopt -s checkwinsize   #properly adjust size of window if necessary
export TERM=xterm-color

### Please don't make changes below this line.
export FBROOT=/Users/gwong/Desktop/fastbit-ibis1.3.7/src
export PATH=/opt/tools/local/bin:$PATH
if [ -f /opt/tools/env.sh ]; then
  source /opt/tools/env.sh
fi
