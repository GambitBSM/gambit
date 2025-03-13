cd ../../../downloaded
tar -xvf *rivet*
echo "diff -rupN Rivet-4.0.1/Makefile.in ../installed/rivet/4.0.1/Makefile.in" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/Makefile.in ../installed/rivet/4.0.1/Makefile.in >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/include/Rivet/Makefile.in ../installed/rivet/4.0.1/include/Rivet/Makefile.in" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/include/Rivet/Makefile.in ../installed/rivet/4.0.1/include/Rivet/Makefile.in >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/src/Core/Makefile.in ../installed/rivet/4.0.1/src/Core/Makefile.in" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/src/Core/Makefile.in ../installed/rivet/4.0.1/src/Core/Makefile.in >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/include/Rivet/AnalysisHandler.hh ../installed/rivet/4.0.1/include/Rivet/AnalysisHandler.hh" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/include/Rivet/AnalysisHandler.hh ../installed/rivet/4.0.1/include/Rivet/AnalysisHandler.hh >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/4.0.1/include/Rivet/Tools/RivetHepMC.hh" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/4.0.1/include/Rivet/Tools/RivetHepMC.hh >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/analyses/Makefile.in ../installed/rivet/4.0.1/analyses/Makefile.in" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/analyses/Makefile.in ../installed/rivet/4.0.1/analyses/Makefile.in >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/src/Core/AnalysisHandler.cc ../installed/rivet/4.0.1/src/Core/AnalysisHandler.cc" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/src/Core/AnalysisHandler.cc ../installed/rivet/4.0.1/src/Core/AnalysisHandler.cc >> patch_rivet_4.0.1.dif
echo "diff -rupN Rivet-4.0.1/configure ../installed/rivet/4.0.1/configure" >> patch_rivet_4.0.1.dif
diff -rupN Rivet-4.0.1/configure ../installed/rivet/4.0.1/configure >> patch_rivet_4.0.1.dif

mv patch_rivet_4.0.1.dif ../patches/rivet/4.0.1/
cd ../patches/rivet/4.0.1
