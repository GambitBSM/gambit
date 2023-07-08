//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of reader class for FlavBit YAML
///  database.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Marcin Chrzaszcz
///  \date 2015 May
///  \date 2016 July
///  \date 2016 August
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Mar
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 Oct
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"


namespace Gambit
{

  namespace FlavBit
  {


    /// Extraction operator for correlation
    void operator >> (const YAML::Node& node, Correlation& c)
    {
      // safety
      std::string name = node["name"].as<std::string>();
      if (name == "NONE") return;
      // reading correlation
      c.corr_name= name;
      c.corr_val = node["value"].as<double>();
    }

    /// Extraction operator for measurement
    void operator >> (const YAML::Node& node, Measurement& v)
    {
      v.name=node["name"].as<std::string>();
      v.is_limit = node["islimit"].as<bool>();
      v.exp_value= node["exp_value"].as<double>();
      if(node["exp_90_CL"]) v.exp_90_CL = node["exp_90_CL"].as<double>();
      if(node["exp_95_CL"]) v.exp_95_CL = node["exp_95_CL"].as<double>();
      if(node["one_sided"]) v.exp_one_sided = node["one_sided"].as<bool>();
      v.exp_source = node["exp_source"].as<std::string>();
      v.exp_stat_error = node["exp_stat_error"].as<double>();
      v.exp_sys_error = node["exp_sys_error"].as<double>();
      if(v.is_limit and !v.exp_stat_error and (v.exp_90_CL or v.exp_95_CL))
      {
        v.exp_stat_error =
          Flav_reader::get_error_from_confidence_levels(v.exp_value, v.exp_90_CL, v.exp_95_CL, v.exp_one_sided);
      }
      v.exp_error=sqrt( v.exp_stat_error*v.exp_stat_error + v.exp_sys_error*v.exp_sys_error );
      v.th_error=node["th_error"].as<double>();
      v.th_error_type=node["th_error_type"].as<std::string>();
      v.th_error_source = node["th_error_source"].as<std::string>();
      const YAML::Node& correlations = node["correlation"];
      v.corr.clear();
      for (unsigned i=0; i<correlations.size(); ++i)
      {
        Correlation corr_tmp;
        correlations[i] >> corr_tmp;
        if (corr_tmp.corr_name != "") v.corr.push_back(corr_tmp);
      }
    }

    /// Constructor that takes the location of the database as an argument
    Flav_reader::Flav_reader(std::string loc)
    {
      measurements=std::vector< Measurement >(0);
      measurement_location=loc;
      debug=false;
      use_S=true;
      use_P=false;
      number_measurements=0;
    }

    /// Read the entire database into memory
    void Flav_reader::read_yaml(std::string name)
    {
      std::string path=measurement_location+"/"+name;
      std::ifstream fin(path.c_str());
      YAML::Node doc = YAML::Load(fin);
      number_measurements=0;
      for(unsigned i=0;i<doc.size();++i)
      {
        Measurement mes_tmp;
        doc[i] >> mes_tmp;
        if(debug) print(mes_tmp);
        measurements.push_back(mes_tmp);
        number_measurements++;
      }
      if (debug) std::cout<<"Number of measurements: "<<number_measurements<<endl;
    }

    /// Read a single measurement from the database into memory
    void Flav_reader::read_yaml_measurement(std::string name, std::string measurement_name)
    {
      std::string path=measurement_location+"/"+name;
      std::ifstream fin(path.c_str());
      YAML::Node doc = YAML::Load(fin);
      Measurement mes_tmp;

      if (debug) std::cout << measurement_name.c_str() << std::endl;

      for (unsigned i=0; i<doc.size(); ++i)
      {
        Measurement mes_tmp;
        doc[i] >> mes_tmp;
        if(mes_tmp.name!=measurement_name.c_str()) continue;
        measurements.push_back(mes_tmp);
        number_measurements++;
        if (debug) std::cout << "Read in " << measurement_name << " " << mes_tmp.name << " " << mes_tmp.exp_value << std::endl;
      }
      if(debug) std::cout << "Number of measurements: " << number_measurements << std::endl;
    }

    /// Print a measurement previously read in from the database
    void Flav_reader::print(Measurement mes)
    {
      std::cout<<"################### Mesurement"<<endl;
      std::cout<<"Name: "<<mes.name<<endl;
      std::cout<<(mes.is_limit ? "Limit" : "Value")<<": "<<mes.exp_value<<endl;
      std::cout<<"Stat/sys errror: "<< mes.exp_stat_error<<"/"<<mes.exp_sys_error<<endl;
      std::cout<<"Error plus/minus: "<<mes.exp_error<<endl;
      std::cout<<"Experimental source: "<<mes.exp_source<<endl;
      std::cout<<"Correlations:"<<endl;
      for(unsigned i=0;i<mes.corr.size();++i)
      {
        std::cout<<mes.corr[i].corr_name<<"  "<<mes.corr[i].corr_val<<endl;
      }
      std::cout<<"########## END"<<endl;
    }

    /// Compute the covariance matrix and populate the measurement and theory error vectors
    void Flav_reader::initialise_matrices()
    {
      // Create the correlation matrix
      M_cor_cov = boost::numeric::ublas::identity_matrix<double>(number_measurements);
      for(int i=0; i<number_measurements; ++i)
      {
        #ifdef FLAVBIT_DEBUG
          std::cout<<"Correlation size: "<< measurements[i].corr.size()<<endl;
        #endif
        for ( unsigned icorr=0; icorr< measurements[i].corr.size(); ++icorr)
        {
          #ifdef FLAVBIT_DEBUG
            std::cout<<"Searching for correlation: "<< measurements[i].corr[icorr].corr_name <<endl;
          #endif
          int i_corr_index=get_measurement_for_corr(measurements[i].corr[icorr].corr_name  );
          M_cor_cov(i_corr_index,i)=measurements[i].corr[icorr].corr_val;
        }
      }
      if (debug) print_matrix(M_cor_cov,"Correlation Matrix:");

      // Make sure the correlation matrix is symmetric and has 1s on the diagonal
      check_corr_matrix(M_cor_cov);

      // Convert the correlation matrix to a covariance matrix
      for(int i=0; i<number_measurements;++i)
      {
        for(int j=0;j<number_measurements;++j)
        {
          M_cor_cov(i,j)=M_cor_cov(i,j)*(measurements[i].exp_error)*(measurements[j].exp_error);
        }
      }
      if (debug) print_matrix(M_cor_cov,"Covariance Matrix:");

      // Construct the the measurement vector
      M_measurements= boost::numeric::ublas::matrix<double> (number_measurements,1);
      for(int i=0; i<number_measurements;++i)
      {
        M_measurements(i,0)=measurements[i].exp_value;
      }
      if (debug) print_matrix(M_measurements, "Measurements:", false);

      // Construct the theory error vector
      M_th_err = boost::numeric::ublas::matrix< std::pair<double,bool> > (number_measurements,1);
      for(int i=0; i<number_measurements;++i)
      {
        M_th_err(i,0).first = measurements[i].th_error;
        str err_type = measurements[i].th_error_type;
        if (err_type == "A") M_th_err(i,0).second = true;
        else if (err_type == "M") M_th_err(i,0).second = false;
        else FlavBit_error().raise(LOCAL_INFO, "Unrecognised theory error type in database: "+err_type);
      }
      if (debug) print_matrix(M_th_err, "Theory errors:", false);

    }

    /// Find the second measurement that corresponds to a given correlation
    int Flav_reader::get_measurement_for_corr(std::string ss)
    {
      for(int i=0;i<number_measurements;++i)
      {
        if(measurements[i].name == ss) return i;
      }
      std::cout<<"Error!, didn't find measuremnet: "<<ss<<endl;
      return -1;
    }

    /// Print a boost ublas matrix
    void Flav_reader::print_matrix(boost::numeric::ublas::matrix<double>& M, str name, bool is_true_matrix)
    {
      int jmax = is_true_matrix ? number_measurements : 1;
      std::cout<<name<<endl;
      for(int i=0; i < number_measurements; ++i)
      {
        for(int j=0 ; j< jmax; ++j) std::cout<<M(i,j)<<"\t";
        std::cout<<endl;
      }
    }

    /// Print a boost ublas matrix with a pair type
    void Flav_reader::print_matrix(boost::numeric::ublas::matrix< std::pair<double, bool> >& M, str name, bool is_true_matrix)
    {
      int jmax = is_true_matrix ? number_measurements : 1;
      std::cout<<name<<endl;
      for(int i=0; i < number_measurements; ++i)
      {
        for(int j=0 ; j< jmax; ++j) std::cout<<M(i,j).first<<":"<<M(i,j).second<<"\t";
        std::cout<<endl;
      }
    }

    /// Check that a correlation matrix has 1s on the diagonal and is symmetric
    void Flav_reader::check_corr_matrix(boost::numeric::ublas::matrix<double>& M)
    {
      for( int i=0; i < number_measurements; ++i)
      {
        for( int j=0 ; j< number_measurements; ++j)
        {
          if (i==j && M(i,i)!=1)
          {
            FlavBit_error().raise(LOCAL_INFO, "Correlation matrix diagonal element differs from 1!");
          }
          if (M(i,j) != M(j,i))
          {
            std::cout << "Correlation matrix " << i << "," << j << " = " << M(i,j) << std::endl;
            std::cout << "Correlation matrix " << i << "," << j << " = " << M(j,i) << std::endl;
            FlavBit_error().raise(LOCAL_INFO, "Correlation matrix not symmetric");
          }
        }
      }
    }

    double Flav_reader::get_error_from_confidence_levels(double exp_value, double CL_90, double CL_95, bool one_sided)
    {
      double error = 0;
      if(one_sided)
      {
        if(CL_90 != 0)
          error = fabs(exp_value - CL_90)/1.28;
        else if (CL_95 != 0)
          error =fabs(exp_value - CL_95)/1.64;
      }
      else
      {
        if(CL_90 != 0)
          error = fabs(exp_value - CL_90)/1.64;
        else if(CL_95 != 0)
          error = fabs(exp_value - CL_95)/1.96;
      }
      return error;

    }
  }
}
