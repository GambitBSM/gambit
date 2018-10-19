//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
/// Chunk data objects for postprocessor
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2016 Mar, 2017 Jan, Feb, Mar
///
///  *********************************************

#ifndef __postprocessor_chunks_hpp__
#define __postprocessor_chunks_hpp__

/// Struct to describe start and end indices for a chunk of data
struct Chunk
{
  std::size_t start; // Index of first point in this chunk
  std::size_t end;   // Index of last point in this chunk
  std::size_t eff_length; // Number of points in the chunk that are not marked to be skipped
  Chunk(std::size_t s, std::size_t e, std::size_t el)
   : start(s)
   , end(e)
   , eff_length(el)
  {}
  Chunk(std::size_t s, std::size_t e)
   : start(s)
   , end(e)
   , eff_length(e-s) // Assume eff_length is actual length if not provided (can manually set it later)
  {}
  Chunk()
   : start(0)
   , end(0)
   , eff_length(0)
  {}
  // Function to check if a given dataset index was processed in this chunk
  bool iContain(std::size_t index) const
  {
    return (start<=index) and (index<=end);
  }
  // Function to compute length of this chunk
  std::size_t length() const
  {
    return end - start + 1;
  }

  bool operator == (const Chunk& other) const 
  {
    return (this->start == other.start and this->end == other.end and this->eff_length == other.eff_length);
  }

};

// To use Chunk in std::unordered_map/set, need to provide hashing and equality functions
struct ChunkHash{ 
  std::size_t operator()(const Chunk &key) const { 
    return std::hash<std::size_t>()(key.start) ^ std::hash<std::size_t>()(key.end);
  }
};

struct ChunkEqual{
  bool operator()(const Chunk &lhs, const Chunk &rhs) const {
    return (lhs.start == rhs.start) and (lhs.end == rhs.end);
  }
};

struct ChunkLess{
  bool operator() (const Chunk& lhs, const Chunk& rhs) const
  {
    return (lhs.start < rhs.start); // Just sort based on start index alone
  }
};

//typedef std::unordered_set<Chunk,ChunkHash,ChunkEqual> ChunkSet; // Actually I want ordered sets now
typedef std::set<Chunk,ChunkLess> ChunkSet; // Actually I want ordered sets now

#endif
