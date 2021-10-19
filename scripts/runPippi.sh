HEADING='=============================='
BLUE="\n${HEADING}\n\033[1;34m[GAMBIT-BUILD]  "
NO_COL="\033[0m\n${HEADING}\n\n"

echo -e "${BLUE}running pippi${NO_COL}"

# conda activate py2
../pippi/pippi plotRules.pip
# conda activate base