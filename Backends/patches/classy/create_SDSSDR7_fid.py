import numpy as np
import math
import scipy.integrate
import scipy.interpolate
import sys

# global variable to detect python version
# needed to avoid compatibility issues below
PYTHON3 = True
if sys.version_info[0] < 3:
  PYTHON3 = False


'''
  Script to compute the spectra of the fiducial cosmology needed for the 
  MontePython SDSS DR7 LRG likelihood. The file containing the fiducial spectra
  is saved as Backends/installed/class/<version>/sdss_lrgDR7_fiducialmodel.dat
  All routines taken and adopted from MontePython. 
  
  Why do we need this? 
    In MontePython, this file is created if it does not exist in the MP data folder. 
    However, the results depend on the treatment of the non linearities. Hence, it is 
    not guaranteed to be (CLASS) version independent. To ensure this for the use with
    GAMBIT, we execute this script after the build step of each CLASS version and save
    the resulting spectra in the installation folder of the respective CLASS version. 
    When running MontePython, we pass the path to the CLASS version that is used for
    the current GAMBIT run. Therefore, we avoid all potential inconsistencies related to the use
    of different CLASS versions for the computation of the likelihood and the calculation
    of the fiducial spectra.

  This script also fixes some compatibility issues with python3. 

  author: Janina Renk, janina.renk@fysik.su.se
    July 2020
'''

def remove_bao(k_in,pk_in):
  '''From MontePython 3.3.0, minor changes to work as stand-alone function
  '''
  # De-wiggling routine by Mario Ballardini
  # This k range has to contain the BAO features:
  k_ref=[2.8e-2, 4.5e-1]
  # Get interpolating function for input P(k) in log-log space:
  _interp_pk = scipy.interpolate.interp1d( np.log(k_in), np.log(pk_in),
                                           kind='quadratic', bounds_error=False )
  interp_pk = lambda x: np.exp(_interp_pk(np.log(x)))
  # Spline all (log-log) points outside k_ref range:
  idxs = np.where(np.logical_or(k_in <= k_ref[0], k_in >= k_ref[1]))
  _pk_smooth = scipy.interpolate.UnivariateSpline( np.log(k_in[idxs]),
                                                   np.log(pk_in[idxs]), k=3, s=0 )
  pk_smooth = lambda x: np.exp(_pk_smooth(np.log(x)))
  # Find second derivative of each spline:
  fwiggle = scipy.interpolate.UnivariateSpline(k_in, pk_in / pk_smooth(k_in), k=3, s=0)
  derivs = np.array([fwiggle.derivatives(_k) for _k in k_in]).T
  d2 = scipy.interpolate.UnivariateSpline(k_in, derivs[2], k=3, s=1.0)
  # Find maxima and minima of the gradient (zeros of 2nd deriv.), then put a
  # low-order spline through zeros to subtract smooth trend from wiggles fn.
  wzeros = d2.roots()
  wzeros = wzeros[np.where(np.logical_and(wzeros >= k_ref[0], wzeros <= k_ref[1]))]
  wzeros = np.concatenate((wzeros, [k_ref[1],]))
  wtrend = scipy.interpolate.UnivariateSpline(wzeros, fwiggle(wzeros), k=3, s=0)
  # Construct smooth no-BAO:
  idxs = np.where(np.logical_and(k_in > k_ref[0], k_in < k_ref[1]))
  pk_nobao = pk_smooth(k_in)
  pk_nobao[idxs] *= wtrend(k_in[idxs])
  # Construct interpolating functions:
  ipk = scipy.interpolate.interp1d( k_in, pk_nobao, kind='linear',
                                    bounds_error=False, fill_value=0. )
  pk_nobao = ipk(k_in)
  return pk_nobao

def get_flat_fid(cosmo,kh,z,sigma2bao,h):
  '''From MontePython 3.3.0, minor changes to work as stand-alone function
  '''

  # SDSS DR7 LRG specific function
  # Compute fiducial properties for a flat fiducial
  # with Omega_m = 0.25, Omega_L = 0.75, h = 0.701
  
  k = kh*h
  # P(k) *with* wiggles, both linear and nonlinear
  Plin = np.zeros(len(k), 'float64')
  Pnl = np.zeros(len(k), 'float64')
  # P(k) *without* wiggles, both linear and nonlinear
  Psmooth = np.zeros(len(k), 'float64')
  Psmooth_nl = np.zeros(len(k), 'float64')
  # Damping function and smeared P(k)
  fdamp = np.zeros([len(k), len(z)], 'float64')
  Psmear = np.zeros([len(k), len(z)], 'float64')
  # Ratio of smoothened non-linear to linear P(k)
  fidnlratio = np.zeros([len(k), len(z)], 'float64')
  # Loop over each redshift bin
  for j in range(len(z)):
    # Compute Pk *with* wiggles, both linear and nonlinear
    # Get P(k) at right values of k in Mpc**3, convert it to (Mpc/h)^3 and rescale it
    # Get values of P(k) in Mpc**3
    for i in range(len(k)):
        Plin[i] = cosmo.pk_lin(k[i], z[j])
        Pnl[i] = cosmo.pk(k[i], z[j])
    # Get rescaled values of P(k) in (Mpc/h)**3
    Plin *= h**3 #(h/scaling)**3
    Pnl *= h**3 #(h/scaling)**3
    # Compute Pk *without* wiggles, both linear and nonlinear
    Psmooth = remove_bao(kh,Plin)
    Psmooth_nl = remove_bao(kh,Pnl)
    # Apply Gaussian damping due to non-linearities
    fdamp[:,j] = np.exp(-0.5*sigma2bao[j]*kh**2)
    Psmear[:,j] = Plin*fdamp[:,j]+Psmooth*(1.0-fdamp[:,j])
    # Take ratio of smoothened non-linear to linear P(k)
    fidnlratio[:,j] = Psmooth_nl/Psmooth

  # Polynomials to shape small scale behaviour from N-body sims
  kdata=kh
  fidpolyNEAR=np.zeros(np.size(kdata))
  fidpolyNEAR[kdata<=0.194055] = (1.0 - 0.680886*kdata[kdata<=0.194055] + 6.48151*kdata[kdata<=0.194055]**2)
  fidpolyNEAR[kdata>0.194055] = (1.0 - 2.13627*kdata[kdata>0.194055] + 21.0537*kdata[kdata>0.194055]**2 - 50.1167*kdata[kdata>0.194055]**3 + 36.8155*kdata[kdata>0.194055]**4)*1.04482
  fidpolyMID=np.zeros(np.size(kdata))
  fidpolyMID[kdata<=0.19431] = (1.0 - 0.530799*kdata[kdata<=0.19431] + 6.31822*kdata[kdata<=0.19431]**2)
  fidpolyMID[kdata>0.19431] = (1.0 - 1.97873*kdata[kdata>0.19431] + 20.8551*kdata[kdata>0.19431]**2 - 50.0376*kdata[kdata>0.19431]**3 + 36.4056*kdata[kdata>0.19431]**4)*1.04384
  fidpolyFAR=np.zeros(np.size(kdata))
  fidpolyFAR[kdata<=0.19148] = (1.0 - 0.475028*kdata[kdata<=0.19148] + 6.69004*kdata[kdata<=0.19148]**2)
  fidpolyFAR[kdata>0.19148] = (1.0 - 1.84891*kdata[kdata>0.19148] + 21.3479*kdata[kdata>0.19148]**2 - 52.4846*kdata[kdata>0.19148]**3 + 38.9541*kdata[kdata>0.19148]**4)*1.03753

  fidNEAR=np.interp(kh,kdata,fidpolyNEAR)
  fidMID=np.interp(kh,kdata,fidpolyMID)
  fidFAR=np.interp(kh,kdata,fidpolyFAR)

  return fidnlratio, fidNEAR, fidMID, fidFAR



def sdss_lrgDR7_fiducial_setup(path,cosmo,h):
  ''' From MontePython 3.3.0, minor changes to work as stand-alone function
      and fix of use with python3
  '''

  # update in numpy's logspace function breaks python3 compatibility, fixed by using
  # goemspace function, giving same result as old logspace
  if PYTHON3:
    kh = np.geomspace(1e-3,1,num=int((math.log(1.0)-math.log(1e-3))/0.01)+1)
  else:
    kh = np.logspace(math.log(1e-3),math.log(1.0),num=(math.log(1.0)-math.log(1e-3))/0.01+1,base=math.exp(1.0))

  # Rescale the scaling factor by the fiducial value for h divided by the sampled value
  # h=0.701 was used for the N-body calibration simulations
  #scaling = scaling * (0.701/h)
  k = kh*h # k in 1/Mpc

  # Define redshift bins and associated bao 2 sigma value [NEAR, MID, FAR]
  z = np.array([0.235, 0.342, 0.421])
  sigma2bao = np.array([86.9988, 85.1374, 84.5958])
  # Initialize arrays
  # Analytical growth factor for each redshift bin
  D_growth = np.zeros(len(z))
  # P(k) *with* wiggles, both linear and nonlinear
  Plin = np.zeros(len(k), 'float64')
  Pnl = np.zeros(len(k), 'float64')
  # P(k) *without* wiggles, both linear and nonlinear
  Psmooth = np.zeros(len(k), 'float64')
  Psmooth_nl = np.zeros(len(k), 'float64')
  # Damping function and smeared P(k)
  fdamp = np.zeros([len(k), len(z)], 'float64')
  Psmear = np.zeros([len(k), len(z)], 'float64')
  # Ratio of smoothened non-linear to linear P(k)
  nlratio = np.zeros([len(k), len(z)], 'float64')
  # Loop over each redshift bin
  for j in range(len(z)):
      # Compute growth factor at each redshift
      # This growth factor is normalized by the growth factor today
      D_growth[j] = cosmo.scale_independent_growth_factor(z[j])
      # Compute Pk *with* wiggles, both linear and nonlinear
      # Get P(k) at right values of k in Mpc**3, convert it to (Mpc/h)^3 and rescale it
      # Get values of P(k) in Mpc**3
      for i in range(len(k)):
          Plin[i] = cosmo.pk_lin(k[i], z[j])
          Pnl[i] = cosmo.pk(k[i], z[j])
      # Get rescaled values of P(k) in (Mpc/h)**3
      Plin *= h**3 #(h/scaling)**3
      Pnl *= h**3 #(h/scaling)**3
      # Compute Pk *without* wiggles, both linear and nonlinear
      Psmooth = remove_bao(kh,Plin)
      Psmooth_nl = remove_bao(kh,Pnl)
      # Apply Gaussian damping due to non-linearities
      fdamp[:,j] = np.exp(-0.5*sigma2bao[j]*kh**2)
      Psmear[:,j] = Plin*fdamp[:,j]+Psmooth*(1.0-fdamp[:,j])
      # Take ratio of smoothened non-linear to linear P(k)
      nlratio[:,j] = Psmooth_nl/Psmooth


      fidnlratio, fidNEAR, fidMID, fidFAR = get_flat_fid(cosmo,kh,z,sigma2bao,h)

      #print('sdss_lrgDR7: Creating fiducial file with Omega_b = 0.25, Omega_L = 0.75, h = 0.701')
      #print('             Required for non-linear modeling')
      # Save non-linear corrections from N-body sims for each redshift bin
      arr=np.zeros((np.size(kh),7))
      arr[:,0]=kh
      arr[:,1]=fidNEAR
      arr[:,2]=fidMID
      arr[:,3]=fidFAR
      # Save non-linear corrections from halofit for each redshift bin
      arr[:,4:7]=fidnlratio
      np.savetxt(path+'/sdss_lrgDR7_fiducialmodel.dat',arr)
      #print('             Fiducial created')


if __name__ == "__main__":

  # set output path where file with fiducial spectra will be saved
  # depending on which CLASS version is being installed
  path_to_classy = sys.argv[1]
  classy_version = sys.argv[2]

  # initialise variable cosmo. Will be overwritten with 
  # instance of CLASS'es python wrapper. Need to do it 
  # like this with overwriting to keep this script in-
  # dependent of the CLASS version that is used. 
  cosmo = None
  sys.path.insert(0,path_to_classy+"/lib/")
  print("from classy_"+classy_version+" import Class")
  exec("from classy_"+classy_version+" import Class")
  exec("cosmo = Class()")

  # set run arguments for fiducial cosmology and call CLASS
  h = 0.701
  cosmo_arguments = {'P_k_max_h/Mpc': 1.5, 'ln10^{10}A_s': 3.0, 'N_ur': 3.04, 'h': h,
                                'omega_b': 0.035*0.701**2, 'non linear': ' halofit ', 'YHe': 0.24, 'k_pivot': 0.05,
                                'n_s': 0.96, 'tau_reio': 0.084, 'z_max_pk': 0.5, 'output': ' mPk ',
                                'omega_cdm': 0.215*0.701**2, 'T_cmb': 2.726}
  cosmo.set(cosmo_arguments)
  cosmo.compute(['lensing'])

  # call routines to write file with spectra of fiducial model
  sdss_lrgDR7_fiducial_setup(path_to_classy,cosmo,h)