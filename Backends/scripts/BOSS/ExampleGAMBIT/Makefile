# Build examplegambit.exe
examplegambit:
	g++ -pthread examplegambit.cpp -ldl -o examplegambit.exe -I./include


# Delete all BOSS-related files
remove-BOSS-files:
	rm -r ./include/gambit


# Copy BOSS-related files 
copy-BOSS-files:
	mkdir -p ./include/gambit/Backends
	mkdir -p ./include/gambit/Utils
	cp -r ../BOSS_output/ExampleBackend_1_234/for_gambit/include/backend_types ./include/gambit/Backends/
	cp ../BOSS_output/ExampleBackend_1_234/abstractbase.hpp ./include/gambit/Backends/
	cp ../BOSS_output/ExampleBackend_1_234/backend_undefs.hpp ./include/gambit/Backends/
	cp ../BOSS_output/ExampleBackend_1_234/function_return_utils.hpp ./include/gambit/Backends/
	cp ../BOSS_output/ExampleBackend_1_234/wrapperbase.hpp ./include/gambit/Backends/
	cp ../common_headers/cats.hpp ./include/gambit/Utils/


.PHONY: clean

# Delete examplegambit.exe
clean:
	rm examplegambit.exe