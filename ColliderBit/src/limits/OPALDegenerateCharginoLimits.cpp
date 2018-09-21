#include "gambit/ColliderBit/limits/OPALDegenerateCharginoLimits.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    P2 OPALDegenerateCharginoLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(x,y);
    }
    
    std::vector<P2> OPALDegenerateCharginoLimitAt208GeV::dataFromLimit(double limit)
    {
      std::vector<P2> data;
      str filename;

      if(limit ==  0.66) filename = "0.66pb_dark_blue";
      else if(limit == 1.00) filename = "1.00pb_light_blue";
      else if(limit == 1.33) filename = "1.33pb_light_green";
      else if(limit == 1.66) filename = "1.66pb_dark_green";
      else if(limit == 2.00) filename = "2.00pb_yellow";
      else if(limit == 2.33) filename = "2.33pb_orange";
      else if(limit == 2.66) filename = "2.66pb_red";
      else if(limit == 3.00) filename = "3.00pb_purple";
      else if(limit == 3.33) filename = "3.33pb_pink"; 
      else if(limit == 3.66) filename = "3.66pb_black";
      else if(limit == 4.00) filename = "4.00pb_white";

      str path;
      path = GAMBIT_DIR  "/ColliderBit/data/OPALdata/" + filename;

      std::ifstream file(path);
      while(file.good())
      {
        std::string line;
        getline(file,line);
        if(!file.good()) break;
        std::stringstream iss(line);
        std::pair<double,double> point;
        iss >> point.first;
        iss.ignore();
        iss >> point.second;
        data.push_back(convertPt(point.first, point.second));
      }
  
      return data;

    }

    bool OPALDegenerateCharginoLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plots only go down to 45 GeV
      return (x <= 95. and x >= 45. and y <= 5. and y >= 0.320);
    }
    
    OPALDegenerateCharginoLimitAt208GeV::OPALDegenerateCharginoLimitAt208GeV()
    {
      ///// Limit values /////
      std::vector<double> limitValues = {0.66, 1.00, 1.33, 1.66, 2.00, 2.33, 2.66, 3.00, 3.33, 3.66, 4.00};
      _limitValuesSorted.push_back(0.66); // dark blue
      _limitValuesSorted.push_back(1.00); // light blue
      _limitValuesSorted.push_back(1.33); // light green
      _limitValuesSorted.push_back(1.66); // dark green
      _limitValuesSorted.push_back(2.00); // yellow
      _limitValuesSorted.push_back(2.33); // orange
      _limitValuesSorted.push_back(2.66); // red
      _limitValuesSorted.push_back(3.00); // purple
      _limitValuesSorted.push_back(3.33); // pink
      _limitValuesSorted.push_back(3.66); // black
      _limitValuesSorted.push_back(4.00); // white

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// Data structure ////
      std::vector<P2> data;

      //// Iterate over limits ////
      for(unsigned int i = 0; i < limitValues.size(); i++)
      {
        data = dataFromLimit(limitValues[i]);
        if(data.empty())
          break;

        corners.clear();
        for(auto p = data.begin(); p != data.end(); p++)
          corners.push_back(*p);
        contoursPointer = new Contours();
        contoursPointer->resize(corners.size() - 1);
        std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
        _limitContours.insert(LimitContourEntry(i, contoursPointer));
      }

    }
    

  }
}
