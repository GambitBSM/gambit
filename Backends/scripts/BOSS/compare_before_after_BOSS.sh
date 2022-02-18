#/bin/bash
dir=$(pwd)
dir="${dir}/ExampleBackend"
# Compare hpp files first
for i in $(find $dir -name '*.cpp');
do
    last_item=$(echo $i | sed 's/\/home\/zelun\/UNSW\/2022_Summer_Project\/gambit\/Backends\/scripts\/BOSS\/ExampleBackend\///g')
    echo $last_item
    echo "\n"
    diff $i "ExampleBackend_ClassThree_afterBOSS/${last_item}"
done;