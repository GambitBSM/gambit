C     example program to run pp sequential recombination
C     algorithms from f77 with fjcore
C     
C     To compile, either use the Makefile and type
C
C        make fjcore_fortran_example
C
C     or simply execute
C
C        g++ -O -c fjcore.cc fjcorefortran.cc
C        gfortran -O fjcore_fortran_example.o fjcore.o fjcorefortran.o -lstdc++\
C                 -o fjcore_fortran_example
C     
C     Given the complications inherent in mixing C++ and fortran, your
C     mileage may vary...
C     
C     To use, type: ./fjcore_fortran_example < single-event.dat
C     
C     $Id: fjcore_fortran_example.f 4100 2016-03-15 20:50:22Z salam $
C     
      program fjcore_fortran_example
      implicit none
c ... maximum number of particles
      integer n
      parameter (n = 1000)
      integer i,j
c ... momenta: first index is Lorentz index (1=px,2=py,3=pz,4=E),
c ... second index indicates which particle it is 
c ... [note, indices are inverted relative to convention in Pythia]
      double precision p(4,n)
c ... parameters of the jet algorithm
      double precision  R, f, palg    
c ... array to store the returned jets
      double precision jets(4,n)
      double precision fjcoredmerge
      integer constituents(n)
      integer npart, njets, nconst ! <= n
      double precision rapmin,rapmax,phimin,phimax
      integer nrepeat
c ... fill in p (NB, energy is p(4,i))
      do i=1,n
         read(*,*,end=500) p(1,i),p(2,i),p(3,i),p(4,i)
      enddo
      
 500  npart = i-1

      R = 0.6d0
      f = 0.75d0
c.....cluster with a pp generalised-kt sequential recombination alg
      palg = -1d0 ! 1.0d0 = kt, 0.0d0 = Cam/Aachen, -1.0d0 = anti-kt
      call fjcoreppgenkt(p,npart,R,palg,jets,njets)   ! ... now you have the jets


c.....write out all inclusive jets, in order of decreasing pt
      write(*,*) '      px         py          pz         E         pT'  
      do i=1,njets
         write(*,*) i,(jets(j,i),j=1,4), sqrt(jets(1,i)**2+jets(2,i)**2)
      enddo
      
c.....write out indices of constituents of first jet
      write(*,*)
      write(*,*) 'Indices of constituents of first jet'
      i = 1;
      call fjcoreconstituents(i, constituents, nconst)
      write(*,*) (constituents(i),i=1,nconst)

c.....write out the last 5 dmerge values
      write(*,*)
      write(*,*) "dmerge values from last 5 steps"
      do i=0,4
         write(*,*) " dmerge from ",i+1," to ",i," = ", fjcoredmerge(i)
      end do


      end
      
