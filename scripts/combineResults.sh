HEADING='======================'
BLUE="\n${HEADING}\n\033[1;34m  "
NO_COL=" \033[0m\n${HEADING}\n\n"

# echo -e "${BLUE}MAKE SURE YOU HAVE py2 ACTIVATED${NO_COL}"
echo -e "${BLUE}combining results into runs/combined.hdf5${NO_COL}"

cd ../runs/samples && \
echo "python2 ../../Printers/scripts/combine_hdf5.py ../scan.hdf5 /data `ls | sed ':a;N;$!ba;s/\n/ /g'`" > ../combine.sh && \
bash ../combine.sh
