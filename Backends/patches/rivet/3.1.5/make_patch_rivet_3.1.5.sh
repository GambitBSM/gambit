cd ../../../downloaded
tar -xvf *rivet*
echo "diff -rupN Rivet-3.1.5/Makefile.in ../installed/rivet/3.1.5/Makefile.in" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/Makefile.in ../installed/rivet/3.1.5/Makefile.in >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/include/Rivet/Makefile.in ../installed/rivet/3.1.5/include/Rivet/Makefile.in" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/include/Rivet/Makefile.in ../installed/rivet/3.1.5/include/Rivet/Makefile.in >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/src/Core/Makefile.in ../installed/rivet/3.1.5/src/Core/Makefile.in" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/src/Core/Makefile.in ../installed/rivet/3.1.5/src/Core/Makefile.in >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/include/Rivet/AnalysisHandler.hh ../installed/rivet/3.1.5/include/Rivet/AnalysisHandler.hh" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/include/Rivet/AnalysisHandler.hh ../installed/rivet/3.1.5/include/Rivet/AnalysisHandler.hh >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/3.1.5/include/Rivet/Tools/RivetHepMC.hh" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/include/Rivet/Tools/RivetHepMC.hh ../installed/rivet/3.1.5/include/Rivet/Tools/RivetHepMC.hh >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/src/Core/AnalysisHandler.cc ../installed/rivet/3.1.5/src/Core/AnalysisHandler.c" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/src/Core/AnalysisHandler.cc ../installed/rivet/3.1.5/src/Core/AnalysisHandler.cc >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/analyses/Makefile.in ../installed/rivet/3.1.5/analyses/Makefile.in" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/analyses/Makefile.in ../installed/rivet/3.1.5/analyses/Makefile.in >> patch_rivet_3.1.5.dif
echo "diff -rupN Rivet-3.1.5/analyses/pluginCMS/CMS_2018_I1663958.cc ../installed/rivet/3.1.5/analyses/pluginCMS/CMS_2018_I1663958.cc" >> patch_rivet_3.1.5.dif
diff -rupN Rivet-3.1.5/analyses/pluginCMS/CMS_2018_I1663958.cc ../installed/rivet/3.1.5/analyses/pluginCMS/CMS_2018_I1663958.cc >> patch_rivet_3.1.5.dif
mv patch_rivet_3.1.5.dif ../patches/rivet/3.1.5/
cd ../patches/rivet/3.1.5
