cd ../../../downloaded
tar -xvf *rivet*
echo "diff -rupN Rivet-3.1.8/Makefile.in ../installed/rivet/3.1.8/Makefile.in" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/Makefile.in ../installed/rivet/3.1.8/Makefile.in >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/include/Rivet/Makefile.in ../installed/rivet/3.1.8/include/Rivet/Makefile.in" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/include/Rivet/Makefile.in ../installed/rivet/3.1.8/include/Rivet/Makefile.in >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/src/Core/Makefile.in ../installed/rivet/3.1.8/src/Core/Makefile.in" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/src/Core/Makefile.in ../installed/rivet/3.1.8/src/Core/Makefile.in >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/include/Rivet/AnalysisHandler.hh ../installed/rivet/3.1.8/include/Rivet/AnalysisHandler.hh" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/include/Rivet/AnalysisHandler.hh ../installed/rivet/3.1.8/include/Rivet/AnalysisHandler.hh >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/3.1.8/include/Rivet/Tools/RivetHepMC.hh" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/3.1.8/include/Rivet/Tools/RivetHepMC.hh >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/analyses/Makefile.in ../installed/rivet/3.1.8/analyses/Makefile.in" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/analyses/Makefile.in ../installed/rivet/3.1.8/analyses/Makefile.in >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/src/Core/AnalysisHandler.cc ../installed/rivet/3.1.8/src/Core/AnalysisHandler.cc" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/src/Core/AnalysisHandler.cc ../installed/rivet/3.1.8/src/Core/AnalysisHandler.cc >> patch_rivet_3.1.8.dif
echo "diff -rupN Rivet-3.1.8/configure ../installed/rivet/3.1.8/configure" >> patch_rivet_3.1.8.dif
diff -rupN Rivet-3.1.8/configure ../installed/rivet/3.1.8/configure >> patch_rivet_3.1.8.dif

mv patch_rivet_3.1.8.dif ../patches/rivet/3.1.8/
cd ../patches/rivet/3.1.8
