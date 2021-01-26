#ifndef RGE_H
#define RGE_H

#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include "QCD_beta.h"
#include "LoopFunctions.h"


class RGE
{
    public:
        RGE();
        virtual ~RGE();
        Eigen::MatrixXd U0(unsigned int nf, double asmu_high, double asmu_low);
        Eigen::MatrixXd ADM_q_q_0(unsigned int nf);
        Eigen::MatrixXd ADM_w_q_0(unsigned int nf);
        Eigen::MatrixXd ADM_w_w_0(unsigned int nf);
        Eigen::MatrixXd ADM_qqp_qqp_0(unsigned int nf);
        Eigen::MatrixXd ADM_qqp_q_0(unsigned int nf, double mqmqp, double Qq, double Qqp);
        Eigen::MatrixXd ADM_qqp_qp_0(unsigned int nf, double mqmqp, double Qq, double Qqp);
        Eigen::MatrixXd ADM_0(unsigned int nf);
        void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove);
        void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove);
        Eigen::MatrixXd ADM_full(unsigned int nf);
        Eigen::VectorXd Cinit_mh_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        Eigen::VectorXd C_mb_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        Eigen::VectorXd Cmatched_mb_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        Eigen::VectorXd C_mc_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        Eigen::VectorXd Cmatched_mc_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        Eigen::VectorXd C_2GeV_0(int nf, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
    protected:
    private:
        //calculated in 2-loop as rge:
        double mumd = 0.46252608039;
double mums = 0.0232254188548;

double mumc =0.00184983387625;
double mumb =0.000461829760055;
double mdms= 0.0502142902628;
double mdmc =0.00399941528636;
double mdmb =0.000998494527412;
double msmc =0.0796469543915;
double msmb =0.0198846687305;
double mcmb =0.249660126773;

        double Qu = 2/3.;
        double Qd = -1/3.;
        double Qs = -1/3.;
        double Qc = 2/3.;
        double Qb = -1/3.;
        double as51lMh = 0.112943337832;
        double as51lMb = 0.212494236131;
        double as41lMc = 0.319897299822;
        double as41l2 = 0.26821777971;
        double as31l2 = 0.26479567324;


};

#endif // RGE_H
