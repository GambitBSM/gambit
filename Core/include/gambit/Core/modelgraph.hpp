//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Model graph declarations.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 July 17
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Aug
///  \date 2014 Mar
///
///  *********************************************


#ifndef __modelgraph_hpp__
#define __modelgraph_hpp__

#include "gambit/Core/depresolver.hpp"
#include "gambit/Models/models.hpp"

namespace Gambit
{

  /// Model hierarchy tree class
  class ModelHierarchy
  {
    /// Property tag for adding color property to edges
    struct edge_color_t { typedef boost::edge_property_tag kind; };

    /// Typedefs for central boost (model) graph
    /// @{
    typedef boost::property<edge_color_t, std::string> EdgeColor;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, functor*, EdgeColor> ModelGraphType;
    typedef boost::graph_traits<ModelGraphType>::vertex_descriptor ModelVertexID;
    typedef boost::graph_traits<ModelGraphType>::edge_descriptor ModelEdgeID;
    typedef boost::property_map<ModelGraphType,boost::vertex_index_t>::type ModelIndexMap;
    /// @}

    /// Shorthand for vector of pointers to primary model functors
    typedef std::vector<primary_model_functor*> primodel_vec;

    private:

      /// Helper class for drawing the model hierarchy graph (labels)
      class labelWriter
      {
        private:
          const ModelGraphType * myGraph;
        public:
          /// Constructor
          labelWriter(const ModelGraphType*);
          void operator()(std::ostream&, const ModelVertexID&) const;
      };


      /// Helper class for drawing the model hierarchy graph (edges)
      class colorWriter
      {
        private:

          const boost::property_map<ModelGraphType, edge_color_t>::const_type color;

        public:

          /// Constructor
          colorWriter(const ModelGraphType* g) : color( boost::get(edge_color_t(),*g) )
          {}

          template<class VertexOrEdge>
          void operator()(std::ostream& out, const VertexOrEdge& e) const
          {
            // check if this is the edge we want to color red
            if( boost::get(color,e) == "red" ) out << "[color=red]";
          }
      };

      /// The model claw that provides all the model info
      const Models::ModelFunctorClaw* boundClaw;

      /// Output filename
      str filename;

      /// Turn on verbose operation
      bool verbose;

      /// The central boost graph object for the model hierarchy
      ModelGraphType modelGraph;

      /// Add model functors (vertices) to model hierarchy graph
      void addFunctorsToGraph(const primodel_vec&);

      /// Add edges (relationships) to model hierarchy graph
      void makeGraph (const primodel_vec&);

    public:

      /// Constructor
      ModelHierarchy(const Models::ModelFunctorClaw&, const primodel_vec&, str, bool);

  };

}

#endif



