cd ../../../downloaded
tar -xvf *rivet*
echo "diff -rupN Rivet-4.1.0/Makefile.in ../installed/rivet/4.1.0/Makefile.in" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/Makefile.in ../installed/rivet/4.1.0/Makefile.in >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/include/Rivet/Makefile.in ../installed/rivet/4.1.0/include/Rivet/Makefile.in" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/include/Rivet/Makefile.in ../installed/rivet/4.1.0/include/Rivet/Makefile.in >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/src/Core/Makefile.in ../installed/rivet/4.1.0/src/Core/Makefile.in" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/src/Core/Makefile.in ../installed/rivet/4.1.0/src/Core/Makefile.in >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/include/Rivet/AnalysisHandler.hh ../installed/rivet/4.1.0/include/Rivet/AnalysisHandler.hh" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/include/Rivet/AnalysisHandler.hh ../installed/rivet/4.1.0/include/Rivet/AnalysisHandler.hh >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/4.1.0/include/Rivet/Tools/RivetHepMC.hh" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/4.1.0/include/Rivet/Tools/RivetHepMC.hh >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/analyses/Makefile.in ../installed/rivet/4.1.0/analyses/Makefile.in" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/analyses/Makefile.in ../installed/rivet/4.1.0/analyses/Makefile.in >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/src/Core/AnalysisHandler.cc ../installed/rivet/4.1.0/src/Core/AnalysisHandler.cc" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/src/Core/AnalysisHandler.cc ../installed/rivet/4.1.0/src/Core/AnalysisHandler.cc >> patch_rivet_4.1.0.dif
echo "diff -rupN Rivet-4.1.0/configure ../installed/rivet/4.1.0/configure" >> patch_rivet_4.1.0.dif
diff -rupN Rivet-4.1.0/configure ../installed/rivet/4.1.0/configure >> patch_rivet_4.1.0.dif

mv patch_rivet_4.1.0.dif ../patches/rivet/4.1.0/
cd ../patches/rivet/4.1.0
