#include "gambit/LowEBit/RGE.h"

RGE::RGE(){
    //ctor
}

RGE::~RGE(){
    //dtor
}

Eigen::MatrixXd RGE::U0(unsigned int nf, double asmu_high, double asmu_low){
    double b0 = QCD_beta(nf,1).trad();
    return (std::log(asmu_high/asmu_low)/(2*b0) * ADM_full(nf).transpose()).exp();
}

Eigen::MatrixXd RGE::ADM_q_q_0(unsigned int nf){
    Eigen::MatrixXd res(4,4);
    res << -10,     -1./6., 4,                4,
            40,     34./3 , -112,             -16,
            0,      0,      -34./3+4*nf/3.,   0,
            0,      0,      32./3,  -38./3+4*nf/3.;
    return res;
}

Eigen::MatrixXd RGE::ADM_w_q_0(unsigned int nf){
    Eigen::MatrixXd res(1,4);
    res << 0, 0, 0, 6;
    return res;
}

Eigen::MatrixXd RGE::ADM_w_w_0(unsigned int nf){
    Eigen::MatrixXd res(1,1);
    res <<  8*nf/3. - 8;
    return res;
}

Eigen::MatrixXd RGE::ADM_qqp_qqp_0(unsigned int nf){
    Eigen::MatrixXd res(6,6);
    res <<  -16, 0, 0, 0, 0, -2,
            0, 2, 0, 0, -4./9, -5/6.,
            0, 0, -16, 0, 0, -2,
            0, 0, 0, 2, -4./9, -5/6.,
            0, -48, 0, -48, 16./3, 0,
            -32./3, -20, -32./3, -20, 0, -38./3;
    return res;
}

Eigen::MatrixXd RGE::ADM_qqp_q_0(unsigned int nf, double mqmqp, double Qq, double Qqp){
    Eigen::MatrixXd res(6,4);
    res <<  0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, -48./mqmqp*Qqp/Qq, 0,
            0, 0, 0, -8/mqmqp;
    return res;
}

Eigen::MatrixXd RGE::ADM_qqp_qp_0(unsigned int nf, double mqmqp, double Qq, double Qqp){
    Eigen::MatrixXd res(6,4);
    res <<  0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, -48.*mqmqp*Qq/Qqp, 0,
            0, 0, 0, -8*mqmqp;
    return res;
}

Eigen::MatrixXd RGE::ADM_0(unsigned int nf){
    Eigen::MatrixXd res(81,81);
    res <<  ADM_q_q_0(nf), Eigen::MatrixXd::Zero(4,77),
            Eigen::MatrixXd::Zero(4,4), ADM_q_q_0(nf), Eigen::MatrixXd::Zero(4,73),
            Eigen::MatrixXd::Zero(4,8), ADM_q_q_0(nf), Eigen::MatrixXd::Zero(4,69),
            Eigen::MatrixXd::Zero(4,12), ADM_q_q_0(nf), Eigen::MatrixXd::Zero(4,65),
            Eigen::MatrixXd::Zero(4,16), ADM_q_q_0(nf), Eigen::MatrixXd::Zero(4,61),
            ADM_qqp_q_0(nf,mumd,Qu,Qd), ADM_qqp_qp_0(nf,mumd,Qu,Qd), Eigen::MatrixXd::Zero(6,12), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,55),
            ADM_qqp_q_0(nf,mums,Qu,Qs), Eigen::MatrixXd::Zero(6,4), ADM_qqp_qp_0(nf,mums,Qu,Qs), Eigen::MatrixXd::Zero(6,14), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,49),
            ADM_qqp_q_0(nf,mumc,Qu,Qc), Eigen::MatrixXd::Zero(6,8), ADM_qqp_qp_0(nf,mumc,Qu,Qc), Eigen::MatrixXd::Zero(6,16), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,43),
            ADM_qqp_q_0(nf,mumb,Qu,Qb), Eigen::MatrixXd::Zero(6,12), ADM_qqp_qp_0(nf,mumb,Qu,Qb), Eigen::MatrixXd::Zero(6,18), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,37),
            Eigen::MatrixXd::Zero(6,4), ADM_qqp_q_0(nf,mdms,Qd,Qs), ADM_qqp_qp_0(nf,mdms,Qd,Qs), Eigen::MatrixXd::Zero(6,32), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,31),
            Eigen::MatrixXd::Zero(6,4), ADM_qqp_q_0(nf,mdmc,Qd,Qc), Eigen::MatrixXd::Zero(6,4), ADM_qqp_qp_0(nf,mdmc,Qd,Qc), Eigen::MatrixXd::Zero(6,34), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,25),
            Eigen::MatrixXd::Zero(6,4), ADM_qqp_q_0(nf,mdmb,Qd,Qb), Eigen::MatrixXd::Zero(6,8), ADM_qqp_qp_0(nf,mdmb,Qd,Qb), Eigen::MatrixXd::Zero(6,36), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,19),
            Eigen::MatrixXd::Zero(6,8), ADM_qqp_q_0(nf,msmc,Qs,Qc), ADM_qqp_qp_0(nf,msmc,Qs,Qc), Eigen::MatrixXd::Zero(6,46), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,13),
            Eigen::MatrixXd::Zero(6,8), ADM_qqp_q_0(nf,msmb,Qs,Qb), Eigen::MatrixXd::Zero(6,4), ADM_qqp_qp_0(nf,msmb,Qs,Qb), Eigen::MatrixXd::Zero(6,48), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,7),
            Eigen::MatrixXd::Zero(6,12), ADM_qqp_q_0(nf,mcmb,Qc,Qb), ADM_qqp_qp_0(nf,mcmb,Qc,Qb), Eigen::MatrixXd::Zero(6,54), ADM_qqp_qqp_0(nf), Eigen::MatrixXd::Zero(6,1),
            ADM_w_q_0(nf), ADM_w_q_0(nf), ADM_w_q_0(nf), ADM_w_q_0(nf), ADM_w_q_0(nf), Eigen::MatrixXd::Zero(1,60), ADM_w_w_0(nf);
    return res;
}

void RGE::removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove){
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

    matrix.conservativeResize(numRows,numCols);
}

void RGE::removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove){
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
}



Eigen::MatrixXd RGE::ADM_full(unsigned int nf){
    if(nf == 5){
        return ADM_0(5);
    }
    if(nf == 4){
        Eigen::MatrixXd res = ADM_0(4);
        int i = 68;
        for(int j = 0; j<80-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        i = 56;
        for(int j = 0; j<62-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        i = 38;
        for(int j = 0; j<44-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        i = 16;
        for(int j = 0; j<20-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        return res;
    }
    if(nf == 3){
        Eigen::MatrixXd res = ADM_0(3);
        int i = 50;
        for(int j = 0; j<80-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        i = 32;
        for(int j = 0; j<44-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        i = 12;
        for(int j = 0; j<20-i; j++){
            removeColumn(res,i);
            removeRow(res,i);
        }
        return res;
    }
    std::cout << "ERROR. number of flavours should be 3 <= nf <= 5" << std::endl;
	Eigen::MatrixXd res(1,1);
	return res;
}

Eigen::VectorXd RGE::Cinit_mh_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    Eigen::VectorXd res(81);
    LoopFunctions c;
    res << 0, 0,
        c.C3q('u',muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t), c.C4q('u',muW,Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_t),
        0, 0,
        c.C3q('d',muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t), c.C4q('d',muW,Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_t),
        0, 0,
        c.C3q('s',muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t), c.C4q('s',muW,Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_t),
        c.C1q('c',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0,
        c.C1q('b',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        c.C1qqp('u','c',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0, 0, 0,
        c.C1qqp('u','b',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        c.C1qqp('d','c',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0, 0, 0,
        c.C1qqp('d','b',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0, 0, 0,
        c.C1qqp('s','c',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0, 0, 0,
        c.C1qqp('s','b',Lambda,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b), 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        c.Cw(Lambda,Ctil_t);
    return res;
}

Eigen::VectorXd RGE::C_mb_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    double as_high = as51lMh;
    double as_low = as51lMb;
    return U0(5,as_high,as_low) * Cinit_mh_0(muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t);
}

Eigen::VectorXd RGE::Cmatched_mb_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    Eigen::MatrixXd res = C_mb_0(muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t);
    int i = 68;
    for(int j = 0; j<80-i; j++){
        removeRow(res,i);
    }
    i = 56;
    for(int j = 0; j<62-i; j++){
        removeRow(res,i);
    }
    i = 38;
    for(int j = 0; j<44-i; j++){
        removeRow(res,i);
    }
    i = 16;
    for(int j = 0; j<20-i; j++){
        removeRow(res,i);
    }
    return res;
}

Eigen::VectorXd RGE::C_mc_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    double as_high = as51lMb;
    double as_low = as41lMc;
    return U0(4,as_high,as_low) * Cmatched_mb_0(muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t);
}

Eigen::VectorXd RGE::Cmatched_mc_0(double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    Eigen::MatrixXd res = C_mc_0(muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t);
    int i = 40;
    for(int j = 0; j<52-i; j++){
        removeRow(res,i);
    }
    i = 28;
    for(int j = 0; j<34-i; j++){
        removeRow(res,i);
    }
    i = 12;
    for(int j = 0; j<16-i; j++){
        removeRow(res,i);
    }
    return res;
}

Eigen::VectorXd RGE::C_2GeV_0(int nf, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    if(nf==4){
        double as_high = as51lMb;
        double as_low = as41l2;
        return U0(4,as_high,as_low) * Cmatched_mb_0(muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t);
    }
    if(nf==3){
        double as_high = as41lMc;
        double as_low = as31l2;
        return U0(3,as_high,as_low) * Cmatched_mc_0(muW,Lambda,Ctil_e,Ctil_mu,Ctil_tau,Ctil_u,Ctil_d,Ctil_s,Ctil_c,Ctil_b,Ctil_t);
    }
	std::cout << "only 3 or 4 flavour matching" << std::endl;
	Eigen::VectorXd res(1);
	return res;
}



