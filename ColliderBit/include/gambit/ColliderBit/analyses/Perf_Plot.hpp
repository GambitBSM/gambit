///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  *********************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <hdf5.h>

using namespace std;

namespace Gambit {
  namespace ColliderBit {


    class Perf_Plot {
    private:

      string _outfilename;
      size_t _numvariables;   
      vector<const char*> _variables;
      vector<vector<double>> _values;
      hid_t file;

    public:

      ~Perf_Plot() {

      }


      Perf_Plot(string outFileName, vector<const char*>* varNames) {

	string path = "ColliderBit/results/";
	path.append(outFileName);
	path.append(".hdf5");
	_outfilename = path;

	_variables = *varNames;
	_numvariables = _variables.size(); 
      }

      void fill(vector<double>* varValues) {
	_values.push_back(*varValues);
      }

      void createFile(double luminosity=0., double xsec_per_event=0.) {
	
	H5Eset_auto2(H5E_DEFAULT, NULL, NULL);
	
	size_t nvalues = _values.size();	
		
	if (nvalues > 0) {
        file = H5Fcreate(_outfilename.c_str(), H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT);

        for (size_t iVal=0;iVal<_numvariables;iVal++) { 

          hid_t dataset, dataspace;
          hsize_t dims[2];
          // herr_t status;

          dims[0] = 1;
	  dims[1] = nvalues;
          dataspace = H5Screate_simple(2, dims, NULL);

          dataset = H5Dcreate2(file, _variables.at(iVal), H5T_NATIVE_DOUBLE, dataspace, H5S_ALL, H5S_ALL, H5P_DEFAULT); 
          
	  double data[nvalues];
          for (size_t iVal2=0;iVal2<nvalues;iVal2++) {
	    data[iVal2]=_values.at(iVal2).at(iVal);
	  }

          // status = H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
          H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

          H5Sclose(dataspace);
          H5Dclose(dataset);

	}

	hid_t dataset_lum, dataspace_lum, dataset_xsec, dataspace_xsec;
        hsize_t dims_lum[2], dims_xsec[2];
        // herr_t status_lum, status_xsec;

        dims_lum[0] = 1;
        dims_lum[1] = 1;
        dataspace_lum = H5Screate_simple(2, dims_lum, NULL);

        dataset_lum = H5Dcreate2(file, "luminosity", H5T_NATIVE_DOUBLE, dataspace_lum, H5S_ALL, H5S_ALL, H5P_DEFAULT);

        double data_lum[1];
	data_lum[0]=luminosity;

        // status_lum = H5Dwrite(dataset_lum, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data_lum);
        H5Dwrite(dataset_lum, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data_lum);

        H5Sclose(dataspace_lum);
        H5Dclose(dataset_lum);
        
	dims_xsec[0] = 1;
        dims_xsec[1] = 1;
        dataspace_xsec = H5Screate_simple(2, dims_xsec, NULL);

        dataset_xsec = H5Dcreate2(file, "xsec_per_event", H5T_NATIVE_DOUBLE, dataspace_xsec, H5S_ALL, H5S_ALL, H5P_DEFAULT);

        double data_xsec[1];
	data_xsec[0]=xsec_per_event;

        // status_xsec = H5Dwrite(dataset_xsec, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data_xsec);
        H5Dwrite(dataset_xsec, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data_xsec);

        H5Sclose(dataspace_xsec);
        H5Dclose(dataset_xsec);


        H5Fclose(file);	
	
	}

      }

    };
  }
}
