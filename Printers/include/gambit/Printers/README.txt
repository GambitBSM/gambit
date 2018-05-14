Instructions for adding new Gambit printers.
----------------------------------------------------
- Printers must be derived from the BasePrinter class and overload the virtual 
  functions appropriately.
- Add the main header for the printer to the path:

   modules/Printers/include/gambit/Printers/printers/my_new_printer.hpp
 
  During building of Gambit by CMake, Printers/scripts/printer_harvester.py 
  will run and add these headers to

   modules/Printers/include/gambit/Printers/printer_rollcall.hpp

  which will make Gambit aware of the printers' existence. 

- If a printer depends on external libraries, currently these will need to be
  dealt with manually in the main CMakeLists.txt file. Will automate this
  hopefully, similar to ScannerBit.

- If the external libraries are missing, CMakeLists.txt should -Ditch the
  printer which needs them. Code associated with the printer will also need to
  be ditched in this event. In order to have this happen automatically, such
  code should be places in the following directories:

    headers:
      modules/Printers/include/gambit/Printers/printers/my_new_printer/extra_header.hpp
 
    source files:
      modules/Printers/src/printers/my_new_printer/extra_header.hpp
   
  If my_new_printer.hpp is -Ditched, then files in these folders will be 
  ignored by Gambit.


