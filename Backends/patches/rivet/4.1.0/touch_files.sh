for dir in $Rivet_dirs; do for file in "$dir"/*lo; do [ -e "$file" ] && touch $file; done; done
for dir in $Rivet_dirs; do for file in "$dir"/*la; do [ -e "$file" ] && touch $file; done; done
echo "Reseting library modification times"
