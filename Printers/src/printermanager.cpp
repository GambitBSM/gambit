//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Manager class for printers.
///  Creates printer object according to inifile
///  instructions, and cleans them up on exit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2014 May
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 May
///
///  *********************************************

#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/basebaseprinter.hpp"
#include "gambit/Printers/printermanager.hpp"
#include "gambit/Printers/printer_rollcall.hpp"
#include "gambit/Utils/yaml_options.hpp"

// Switch for debugging output (manual at the moment)
//#define DEBUG_MODE

#ifdef DEBUG_MODE
  #define DBUG(x) x
#else
  #define DBUG(x)
#endif

namespace Gambit
{
  
  // Set/Get global reader object retrieval
  Printers::PrinterManager* global_printer_manager = NULL;
  
  // Function to return the value of global_printer_manager
  Printers::PrinterManager* get_global_printer_manager()
  {
    return(global_printer_manager);
  }

  Printers::BaseReader& get_pp_reader()
  {
    if(global_printer_manager==NULL)
    {
       std::ostringstream os;
       os<<"Tried to retrieve postprocessor reader object, but no PrinterManager has been set! This should be set during scan setup.";
       Printers::printer_error().raise(LOCAL_INFO,os.str()); 
    }
    
    if(not global_printer_manager->reader_exists("old_points"))
    {
       std::ostringstream errmsg;
       errmsg<<"No postprocessor reader object found! This probably means that you are not scanning using the postprocessor. To retrieve data from previous output you must scan with the 'postproccesor' scanner.";
       Printers::printer_error().raise(LOCAL_INFO,errmsg.str());
    }

    return *(global_printer_manager->get_full_reader("old_points"));
  }

  void set_global_printer_manager(Printers::PrinterManager* pm)
  {
     global_printer_manager = pm;
  }

 
  namespace Printers
  {

    /// Manager class for creating printer objects
    PrinterManager::PrinterManager(const Options& printerNode, bool resume_mode)
      : BasePrinterManager(resume_mode)
      , tag(printerNode.getValue<std::string>("printer"))
      , options(printerNode.getNode("options"))
      , printerptr(NULL)
    {
      // Change printer pointer to actually point to the printer object
      if( printer_creators.find(tag)!=printer_creators.end() )
      {
         // If "tag" names a valid printer, create it.
         DBUG( std::cout << "PrinterManager: Creating Primary printer \"" << tag << "\"" << std::endl; )

         // pass on the "resume" flag to the printer
         Options mod_options = options;
         mod_options.setValue("resume",resume_mode);

         BasePrinter* null(NULL);
         printerptr = printer_creators.at(tag)(mod_options,null);
  
         // Update resume flag (primary printer may have switched it off due to lack of existing output)
         set_resume_mode(printerptr->get_resume());
      }
      else
      {
         // Otherwise throw an error
         std::ostringstream os;
         os << "Inifile entry 'printer:\""<<tag<<"\"' does not specify a valid printer! Please choose from one of the following:"<<std::endl;

         for (auto it = printer_creators.begin(); it != printer_creators.end(); ++it)
         {
            os << "  " << it->first << std::endl;
         }

         printer_error().raise(LOCAL_INFO,os.str());
      }
    }

    /// Destruct printer/reader objects
    void PrinterManager::delete_stream(const std::string& name)
    {
      if(name=="")
      {
         std::ostringstream os;
         os << "Tried to delete primary printer stream! Currently you are not permitted to do this. Why do you want to?";
         printer_error().raise(LOCAL_INFO,os.str());
      }
      else
      {
         auto it = auxprinters.find(name);
         if(it!=auxprinters.end())
         {
            delete it->second;
            auxprinters.erase(it);
         }
         else
         {
            std::ostringstream os;
            os << "Tried to delete printer stream '"<<name<<"', but could not find a print stream with that name! Perhaps it was never created, or was deleted already?";
            printer_error().raise(LOCAL_INFO,os.str());
         }
      }
    }

    void PrinterManager::delete_reader(const std::string& name)
    { 
      auto it = readers.find(name);
      if(it!=readers.end())
      {
         delete it->second;
         readers.erase(it);
      }
      else
      {
         std::ostringstream os;
         os << "Tried to delete reader object '"<<name<<"', but could not find a reader object with that name! Perhaps it was never created, or was deleted already?";
         printer_error().raise(LOCAL_INFO,os.str());
      }
    }
 
    PrinterManager::~PrinterManager()
    {
      // Delete all the printer objects
      DBUG( std::cout << "PrinterManager: Destructing printers and readers..." << std::endl; )
      typedef std::map<std::string, BasePrinter*>::iterator it_type;
      typedef std::map<std::string, BaseReader*>::iterator it2_type;
      for(it_type it = auxprinters.begin(); it != auxprinters.end(); it++) {
         delete it->second; // Delete the printer to which this pointer points.
      }
      for(it2_type it = readers.begin(); it != readers.end(); it++) {
         delete it->second; // Delete the reader to which this pointer points.
      }
      delete printerptr; // Delete primary printer
    }

    // Create new printer object (of the same type as the primary printer)
    // and attach it to the provided name.
    void PrinterManager::new_stream(const std::string& streamname, const Options& new_options)
    {
       //TODO need some way for the scanners to change the options
       //for the auxiliary printers, e.g. so we can print to a different file
       DBUG( std::cout << "PrinterManager: Creating Auxilliary printer \"" << tag << "\" with name \"" << streamname << "\"" << std::endl; )
       Options mod_options = new_options;
       mod_options.setValue("resume",this->resume_mode());
       mod_options.setValue("auxilliary",true);
       mod_options.setValue("name",streamname);
       mod_options.setValue("default_output_path",options.getValue<str>("default_output_path"));
       // To construct printer as an auxilliary printer, a pointer to the primary printer is supplied as well as the options.
       auxprinters[streamname] = printer_creators.at(tag)(mod_options,printerptr);
       // Some printers may requires two-step initiations so this virtual function is provided to allow that.
       auxprinters.at(streamname)->auxilliary_init();
    }

    // Create new printer reader object (of the same type as the primary printer)
    // and attach it to the provided name.
    void PrinterManager::new_reader(const std::string& readstreamname, const Options& options)
    {
       DBUG( std::cout << "PrinterManager: Creating printer read stream of type \"" << tag << "\" with name \"" << readstreamname << "\"" << std::endl; )
       std::string whichreader = options.getValueOrDef<std::string>(tag,"type");
       if(reader_creators.find(whichreader)==reader_creators.end())
       {
         std::ostringstream os;
         os << "PrinterManager: Tried to construct reader with name '"<<readstreamname<<"' as reader-type '"<<whichreader<<"', but this is not a valid reader type! Please choose one of the following:"<<std::endl;
         for (auto it = reader_creators.begin(); it != reader_creators.end(); ++it)
         {
            os << "  " << it->first << std::endl;
         }
         printer_error().raise(LOCAL_INFO,os.str());
       }
       readers[readstreamname] = reader_creators.at(whichreader)(options);
    }

    /// Create for reader object for previous print output ("resume reader")
    void PrinterManager::create_resume_reader()
    {
       // The only difficulty here is to get the options needed to build
       // the reader (filenames etc). This varies between different types
       // of printers, so we have to ask the primary printer object to
       // give us these options.  
       new_reader("resume", get_stream()->resume_reader_options()); 
    }
 
    // Retrieve pointer to named printer object
    BaseBasePrinter* PrinterManager::get_stream(const std::string& streamname)
    {
      DBUG( std::cout << "PrinterManager: Retrieving printer stream \"" << streamname << "\"" << std::endl; )
      if(streamname=="")
      {
        if(printerptr==NULL)
        {
           printer_error().raise(LOCAL_INFO,"Error retrieving primary printer from PrinterManager! printerptr==NULL! Must be a bug in the PrinterManager initialisation.");
        }
        return printerptr;
      }
      else
      {
        // Note that this routine automatically converts the BasePrinter pointer into a BaseBasePrinter pointer
        // (for a more minimal interface for use in ScannerBit)
        typedef std::map<std::string, BasePrinter*>::iterator it_type;
        it_type it = auxprinters.find(streamname);
        if( it == auxprinters.end() )
        {
          std::ostringstream errmsg;
          errmsg << "Error! PrinterManager failed to retrieve the requested auxilliary print stream with name '"<<streamname<<"'! The stream may not have been created in the first place. Please check that the scanner plugin you are using correctly creates a printer stream with this name.";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        return it->second;
      }
    }

    /// Retrieve pointer to named reader object
    BaseBaseReader* PrinterManager::get_reader(const std::string& readername)
    {
      // Note that this routine automatically converts the BaseReader pointer into a BaseBaseReader pointer
      // (for a more minimal interface for use in ScannerBit)
      return get_full_reader(readername);
    }

    /// Retrieve non-base version of reader object (for use in module functions rather than ScannerBit)
    BaseReader* PrinterManager::get_full_reader(const std::string& readername)
    {
      DBUG( std::cout << "PrinterManager: Retrieving reader stream \"" << readername << "\"" << std::endl; )
      // Note that this routine automatically converts the BaseReader pointer into a BaseBaseReader pointer
      // (for a more minimal interface for use in ScannerBit)
      typedef std::map<std::string, BaseReader*>::iterator it_type;
      it_type it = readers.find(readername);
      if( it == readers.end() )
      {
        std::ostringstream errmsg;
        errmsg << "Error! PrinterManager failed to retrieve the requested reader stream with name '"<<readername<<"'! The reader may not have been created in the first place. Please check that the scanner plugin you are using correctly creates a reader stream with this name.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      return it->second;
    }

    /// Checker for existence of reader object
    bool PrinterManager::reader_exists(const std::string& readername)
    {
      typedef std::map<std::string, BaseReader*>::iterator it_type;
      it_type it = readers.find(readername);
      return (it != readers.end());
    }

    /// Instruct all printers that scan has finished and to perform cleanup
    void PrinterManager::finalise(bool abnormal)
    {
      typedef std::map<std::string, BasePrinter*>::iterator it_type;
      for(it_type it = auxprinters.begin(); it != auxprinters.end(); it++) {
         it->second->finalise(abnormal);
      }
      printerptr->finalise(abnormal);
    }

  }
}

#undef DBUG
#undef DEBUG_MODE
