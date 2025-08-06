// Run with commands:
// cd ScannerBit/emu_egg
// mpic++ -std=c++20 /src/egg.cpp -o egg
// mpic++ -std=c++20 mpi_test/gambit_dummy.cpp -o dummy
// mpirun -np 2 ./dummy : -np 2 ./egg "plugin1"


#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>   // Required for std::istringstream
#include <map>
#include <vector>
#include <cstring> // For memcpy

// #ifdef WITH_MPI
#include <mpi.h>
// #endif

std::tuple<int, std::string> splitChar(char* input)
{
    std::string received_message(input);

    std::string nonNumericPart;
    int numericPart;
    std::istringstream iss(received_message);
    iss >> nonNumericPart >> numericPart; 
    std::cout << nonNumericPart << " # " << numericPart << std::endl;

    return {numericPart, nonNumericPart};
}

// Function to serialize the map into a buffer
std::vector<char> serializeMap(const std::map<std::string, int>& my_map) {
    std::vector<char> buffer;

    // First, store the size of the map
    size_t map_size = my_map.size();
    buffer.resize(sizeof(size_t)); // Reserve space for the size
    std::memcpy(buffer.data(), &map_size, sizeof(size_t));

    // Now, serialize each string and int pair
    for (const auto& pair : my_map) {
        size_t key_length = pair.first.size();
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&key_length), reinterpret_cast<const char*>(&key_length) + sizeof(size_t));
        buffer.insert(buffer.end(), pair.first.begin(), pair.first.end());
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&pair.second), reinterpret_cast<const char*>(&pair.second) + sizeof(int));
    }

    return buffer;
}

// Function to deserialize the buffer back into a map
std::map<std::string, int> deserializeMap(const std::vector<char>& buffer) {
    std::map<std::string, int> my_map;
    size_t offset = 0;

    // Read the size of the map
    size_t map_size = *reinterpret_cast<const size_t*>(buffer.data() + offset);
    offset += sizeof(size_t);

    // Deserialize each string and int pair
    for (size_t i = 0; i < map_size; ++i) {
        size_t key_length = *reinterpret_cast<const size_t*>(buffer.data() + offset);
        offset += sizeof(size_t);
        
        std::string key(buffer.data() + offset, key_length);
        offset += key_length;

        int value = *reinterpret_cast<const int*>(buffer.data() + offset);
        offset += sizeof(int);

        my_map[key] = value;
    }

    return my_map;
}


void train() {}
int main(int argc, char *argv[]) 
{
    MPI_Init(&argc, &argv);

    // get rank and size
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //////// split to create local communicators
    int color = 0;
    // TODO: send color to the other executables

    // split local communicator
    MPI_Comm comm_local;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &comm_local);

    // get local information
    int local_rank, local_size;
    MPI_Comm_rank(comm_local, &local_rank);
    MPI_Comm_size(comm_local, &local_size);

    // print 
    std::cout  << "In dummy: world rank " << world_rank << ", color " << color << ", local rank " << local_rank << ", local size " << local_size << std::endl;

    //////// create map of plugins and their world ranks
    std::map<std::string, int> rank_map;
    std::vector<char> buffer;
    if (world_rank == 0)
    {
        // TODO: recieve from all executables, need to know how many

        // get plugin name and rank from all processes
        char my_string[10]; // TODO: probe for size of the string?
        MPI_Recv(&my_string, 10, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // TODO: send color to other executables as an answer to this?

        auto [plugin_rank, plugin_name] = splitChar(my_string);
        rank_map.insert({plugin_name, plugin_rank});

        std::cout << "Dummy recieved: plugin name " << plugin_name << ", and plugin master world rank " << plugin_rank << std::endl;

        // prepare to broadcast map
        buffer = serializeMap(rank_map);
    }

    //////// broadcast map to all gambit processes
    // send buffer size
    size_t buffer_size = buffer.size();
    MPI_Bcast(&buffer_size, 1, MPI_UNSIGNED_LONG, 0, comm_local);

    // Resize buffer on all ranks
    buffer.resize(buffer_size);
    
    // Send the map
    MPI_Bcast(buffer.data(), buffer_size, MPI_CHAR, 0, comm_local);


    //////// extract rank map on all gambit processes
    rank_map = deserializeMap(buffer);
    std::cout << "Dummy rank " << world_rank << ", has rank " << rank_map["plugin1"] << " in map for plugin1" << std::endl;


    // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

