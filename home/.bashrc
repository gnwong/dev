#
# .bashrc
# 
#   CREATED:  17 JULY 2013
#   UPDATED:  17 JULY 2013
#   AUTHOR:   George Wong


# If not running interactively, don't do anything
[ -z "$PS1" ] && return

#if [ -n "${SSH_CONNECTION}" ]; then
  

#
# Colors
#
# Normal Colors
Black='\e[0;30m'        # Black
Red='\e[0;31m'          # Red
Green='\e[0;32m'        # Green
Yellow='\e[0;33m'       # Yellow
Blue='\e[0;34m'         # Blue
Purple='\e[0;35m'       # Purple
Cyan='\e[0;36m'         # Cyan
White='\e[0;37m'        # White

# Bold
BBlack='\e[1;30m'       # Black
BRed='\e[1;31m'         # Red
BGreen='\e[1;32m'       # Green
BYellow='\e[1;33m'      # Yellow
BBlue='\e[1;34m'        # Blue
BPurple='\e[1;35m'      # Purple
BCyan='\e[1;36m'        # Cyan
BWhite='\e[1;37m'       # White

# Background
On_Black='\e[40m'       # Black
On_Red='\e[41m'         # Red
On_Green='\e[42m'       # Green
On_Yellow='\e[43m'      # Yellow
On_Blue='\e[44m'        # Blue
On_Purple='\e[45m'      # Purple
On_Cyan='\e[46m'        # Cyan
On_White='\e[47m'       # White

NC="\e[m"               # Color Reset


# Test for user type (for proper color assignment)
if [[ ${USER} == "root" ]]; then
  SU="${Red}\u${NC}"
elif [[ ${USER} != $(logname) ]]; then
  SU="\[${Red}\]\u\[${NC}\]"
else
  SU="\[${Cyan}\]\u\[${NC}\]"
fi


# Standard prompt
export PS1="${SU}\[${White}\]@\[${Green}\]\h\[${NC}\] \[${BBlue}\]\w\[${White}\] $ "

#
# Alias
#
alias q="exit"

# Insert above this line. Below code (should be) is deprecated


# export PS1="\w$ "
#
# Fastbit
#
export FBROOT=/Users/gwong/Desktop/fastbit-ibis1.3.7/src



if [ -f /opt/tools/env.sh ]; then
  source /opt/tools/env.sh
fi



