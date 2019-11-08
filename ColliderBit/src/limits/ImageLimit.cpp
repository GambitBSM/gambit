//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.j.fowlie@qq.com)
///  \date 2019 February
///
///  ********************************************


#include "gambit/ColliderBit/limits/ImageLimit.hpp"



namespace Gambit {
  namespace ColliderBit {

    data_type ImageLimit::get_image(std::string name) {
      std::fstream in(name);
      std::string line;
      data_type data;
      int line_number = 0;

      while (std::getline(in, line)) {
        double value;
        std::stringstream ss(line);

        data.push_back(std::vector<double>());

        while (ss >> value) {
          data[line_number].push_back(value);
        }
        ++line_number;
      }
      return data;
    }

    double ImageLimit::get_limit(double x, double y) {
      // Look-up nearest neighbour by index. The conversion factors
      // originate from the size of the grid divided by the
      // masses that the grid spans

      const double unit_x = (x - extent[0]) / (extent[1] -  extent[0]);
      const int index_x = std::round((image_data[0].size() - 1) * unit_x);

      const double unit_y = (y - extent[2]) / (extent[3] -  extent[2]);
      const int index_y = std::round((image_data.size() - 1) * unit_y);

      // Retrive limit from data

      try {
        return image_data.at(index_y).at(index_x);
      } catch (const std::out_of_range& e) {
        return limit_outside_grid;
      }
    }

    ImageLimit::ImageLimit(std::string name,
                         double x_min, double x_max,
                         double y_min, double y_max) {
      image_data = get_image(name);
      extent = {x_min, x_max, y_min, y_max};
    }

  }  // namespace ColliderBit
}  // namespace Gambit
