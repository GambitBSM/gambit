"""
MCMC-diffusion scanner
======================
"""

# This bit of the file contains th functions for a simple implementation of the MCMC diffusion scanner, taken from this github on September 17th 2024
# https://github.com/NickHunt-Smith/MCMC-diffusion
# Code by Martin White, borrowing from original implementaton by Nick Hunt-Smith

import sys,os
import numpy as np
from scipy import stats
import time
import math
from random import randrange
import pygtc
import scanner_plugin as splug
from scipy.optimize  import minimize


def lprint(msg):
    sys.stdout.write('\r')
    sys.stdout.write(msg)
    sys.stdout.flush()

class MHDiffusion(splug.scanner):

    __version__="1.0.0"
    __plugin_name__ = "mh_diffusion"

    def __init__(self,retrains=10,samples_per_retrain=1000,nsteps = 20,sigma = 0.3,
                 diffusion_prob = 0.5,bins = 20,noise_width = 0.05,beta_1 = 0.1,beta_2 = 0.3, **kwargs):

        super().__init__(use_mpi=False, use_resume=False)

        self.log_likelihood = self.loglike_hypercube
        self.printer.new_stream("txt", synchronised=False)

        # Get 20,000 random samples for initialising the diffusion model
        # Could make this tunable?
        initial_sample_size = 20000
        initial_samples = []
        self.low_bound = np.zeros(self.dim)
        self.high_bound = np.ones(self.dim)
        for dim_iter in range(0,self.dim):
            initial_samples.append(np.random.uniform(low = self.low_bound[dim_iter],
                                                     high = self.high_bound[dim_iter],size = initial_sample_size))
        self.initial_samples = np.array(initial_samples).T
        self.retrains = retrains
        self.samples_per_retrain = samples_per_retrain
        self.nsteps = nsteps
        self.sigma = sigma
        self.diffusion_prob = diffusion_prob
        self.bins = bins
        self.noise_width = noise_width
        self.beta_1 = beta_1
        self.beta_2 = beta_2

    def run(self):
        print('Diffusion MCMC Chain Started')
        
        training_samples = self.initial_samples
        initial_sample_size = len(training_samples)
        desired_sample_size = initial_sample_size
        var_guess = []
        for _ in range(0,self.nsteps):
            var_guess.append(1)
        var_guess = np.array(var_guess)

        # Train diffusion model on initial seeded samples
        model = DiffusionModel(self.dim,self.nsteps,self.noise_width,
        initial_sample_size,desired_sample_size,training_samples,var_guess,self.beta_1,self.beta_2)
        diffusion_samples,vars = model.fit()

        samples_final = self.initial_samples
        theta = samples_final[np.random.randint(0,len(samples_final))]
        accepted_diffusion = []
        accepted_MH = []
        total_time = 0
        diffusion_rate = []

        for retrain_iter in range(self.retrains):

            start = time.time()

            H = []
            edges = []
            for dim_iter in range(0,self.dim):
                H_temp,edges_temp = np.histogram(diffusion_samples[:,dim_iter],
                bins = self.bins)
                H.append(H_temp/np.sum(H_temp))
                edges.append(edges_temp)

            naccepted_diffusion = 0
            nattempted_diffusion = 0
            naccepted = 0
            nattempted = 0
            for i in range(self.samples_per_retrain):
                rand = np.random.uniform()
                # Diffusion as proposal some of the time
                if rand < self.diffusion_prob:
                    nattempted_diffusion +=1
                    rand_pick = randrange(len(diffusion_samples))
                    theta_prime = diffusion_samples[rand_pick]

                    edge_loc = []
                    for dim_iter in range(0,self.dim):
                        for edge_iter in range(0,len(edges[dim_iter])):
                            if theta_prime[dim_iter] >= edges[dim_iter][len(edges[dim_iter])-1]:
                                edge_loc.append(len(edges[dim_iter])-2)
                                break
                            elif theta_prime[dim_iter] < edges[dim_iter][edge_iter]:
                                edge_loc.append(edge_iter-1)
                                break

                    Q_prime = 1
                    for dim_iter in range(0,self.dim):
                        Q_prime = Q_prime*H[dim_iter][edge_loc[dim_iter]]
                    if Q_prime == float(0):
                        Q_prime = 0.000001

                    edge_loc = []
                    for dim_iter in range(0,self.dim):
                        for edge_iter in range(0,len(edges[dim_iter])):
                            if theta[dim_iter] >= edges[dim_iter][len(edges[dim_iter])-1]:
                                edge_loc.append(len(edges[dim_iter])-2)
                                break
                            elif theta[dim_iter] < edges[dim_iter][edge_iter]:
                                edge_loc.append(edge_iter-1)
                                break

                    Q = 1
                    for dim_iter in range(0,self.dim):
                        Q = Q*H[dim_iter][edge_loc[dim_iter]]
                    if Q == float(0):
                        Q = 0.000001

                    Q_ratio = Q/Q_prime


                    for j in range(self.dim):
                        while theta_prime[j] < self.low_bound[j] or theta_prime[j] > self.high_bound[j]:
                            theta_prime[j] = theta[j] + stats.norm(0, self.sigma).rvs()
              
                    L_ratio = self.log_likelihood(theta_prime)/self.log_likelihood(theta)
              
                    prob_accept = L_ratio*Q_ratio
                    a = min(1, prob_accept)
                    u = np.random.uniform()
                    if u < a:
                        naccepted_diffusion +=1
                        theta = theta_prime
                        accepted_diffusion.append(theta_prime)
                # M-H the rest of the time
                else:
                    nattempted +=1
                    theta_prime = np.zeros(self.dim)
                    for j in range(self.dim):
                        theta_prime[j] = theta[j] + stats.norm(0, self.sigma).rvs()
                        while theta_prime[j] < self.low_bound[j] or theta_prime[j] > self.high_bound[j]:
                            theta_prime[j] = theta[j] + stats.norm(0, self.sigma).rvs()
                    theta_prime = np.array(theta_prime)
                    a = min(1, self.log_likelihood(theta_prime)/self.log_likelihood(theta))
                    u = np.random.uniform()
                    if u < a:
                        naccepted +=1
                        theta = theta_prime
                        accepted_MH.append(theta_prime)
                samples_final = np.vstack((samples_final,theta))

                
            # Retrain Diffusion
            initial_sample_size = len(samples_final)
            desired_sample_size = 10*initial_sample_size
            training_samples = samples_final
            var_guess = vars
            model = DiffusionModel(self.dim,self.nsteps,
            self.noise_width,initial_sample_size,desired_sample_size,
            training_samples,var_guess,self.beta_1,self.beta_2)
            diffusion_samples,vars = model.fit()
            end = time.time()

            total_time += end-start

            print('Number of retrains = ' + str(retrain_iter+1) + '/' +
            str(self.retrains) + '\n' + 'Diffusion acceptance efficiency = ' +
            str(naccepted_diffusion/nattempted_diffusion) + '\n' +
            'Metropolis acceptance efficiency = ' + str(naccepted/nattempted) +
            '\n' + 'Previous Retrain Time = ' + str(np.round(end-start)) +
            ' seconds ' + '\n' + 'Total Retrain Time = ' +
            str(np.round(total_time)) + ' seconds ')

            if not retrain_iter == self.retrains-1:
                for _ in range(0,5):
                    UP = '\033[1A'
                    CLEAR = '\x1b[2K'
                    print(UP, end=CLEAR)

            diffusion_rate.append(naccepted_diffusion/nattempted_diffusion)
        return samples_final,accepted_diffusion,accepted_MH,diffusion_rate


class DiffusionModel:
    def __init__(self,dim,nsteps,noise_width,initial_sample_size,
    desired_sample_size,training_samples,var_guess,beta_1,beta_2):
        self.dim = dim
        self.nsteps = nsteps
        self.initial_sample_size = initial_sample_size
        self.desired_sample_size = desired_sample_size
        self.training_samples = training_samples
        self.var_guess = var_guess
        self.noise_width = noise_width
        self.beta_1 = beta_1
        self.beta_2 = beta_2

    def forward_diffusion(self,x0,t,dim_iter,alpha_bar):
        eps = np.random.normal(loc = self.noise_means[dim_iter],
        scale = self.noise_stds[dim_iter], size = len(x0))
        mean = ((alpha_bar[t]) ** 0.5) * x0
        var = 1-alpha_bar[t]
        noise_added = mean + (var ** 0.5) * eps
        return noise_added

    def fit(self):

        # Set width of noised distribution after forward diffusion process to be (noise_width)*(std of training samples)
        initial_samples = []
        self.noise_stds = []
        self.noise_means = []
        for i in range(0,self.dim):
            initial_samples.append(self.training_samples[:,i])
            self.noise_stds.append(self.noise_width*np.std(self.training_samples[:,i]))
            self.noise_means.append(np.mean(self.training_samples[:,i]))

        # Perform forward diffusion process
        beta = np.linspace(self.beta_1, self.beta_2, self.nsteps)
        alpha = 1-beta
        alpha_bar = np.cumprod(alpha)
        X_diffusion = []
        noised = initial_samples
        X_diffusion.append(noised)
        for t in range(0,self.nsteps):
            noised_temp = []
            for i in range(len(noised)):
                noised_temp.append(self.forward_diffusion(noised[i],t,i,alpha_bar))
            X_diffusion.append(noised_temp)
            noised = noised_temp

        # Learn reverse diffusion process
        vars = []
        initial_noise = []
        for dim_iter in range(self.dim):
            initial_noise.append(np.random.normal(loc =
            self.noise_means[dim_iter], scale = self.noise_stds[dim_iter],
            size = self.initial_sample_size))

        def loss(phis):
            denoised = np.array(initial_noise)
            for p in range(0,self.nsteps):
                t = self.nsteps-p-1
                for dim_iter in range(self.dim):
                    diff_temp = X_diffusion[t][dim_iter]-X_diffusion[t+1][dim_iter]
                    denoised[dim_iter] = denoised[dim_iter] + diff_temp*phis[p]

            loss_temp = np.sum((np.array(X_diffusion[0]) - denoised)**2)
            return loss_temp

        guess = self.var_guess
        sol = minimize(loss, guess, method='Nelder-Mead', tol=1e-10)
        vars = sol.x

        # Set correct number of samples to generate
        remainder = self.desired_sample_size % self.initial_sample_size
        generations = int((self.desired_sample_size - remainder)/ self.initial_sample_size)
        if generations == 0:
            generations = 1

        final_samples_temp = []
        for dim_iter in range(self.dim):
            final_samples_temp.append([])

        # Perform reverse diffusion process
        for gen in range(0,generations):
            for dim_iter in range(self.dim):
                denoised = np.random.normal(loc = self.noise_means[dim_iter],
                scale = self.noise_stds[dim_iter], size = self.initial_sample_size)

                for p in range(0,self.nsteps):
                    t = self.nsteps-p-1
                    diff_temp = X_diffusion[t][dim_iter]-X_diffusion[t+1][dim_iter]
                    denoised = denoised + diff_temp*vars[p]


                final_samples_temp[dim_iter] = np.append(final_samples_temp[dim_iter],denoised)

        final_samples = []
        for j in range(len(final_samples_temp[0])):
            final_samples_ind = []
            for i in range(len(final_samples_temp)):
                final_samples_ind.append(final_samples_temp[i][j])
            final_samples.append(final_samples_ind)

        diffusion_samples = np.array(final_samples)

        return diffusion_samples,vars


__plugins__ = {MHDiffusion.__plugin_name__: MHDiffusion}


