#ifndef QCD_BETA_H
#define QCD_BETA_H


class QCD_beta
{
    public:
        QCD_beta(unsigned int nf, unsigned int loop);
        virtual ~QCD_beta();
        double nf;
        double loop;
        double chet();
        double trad();
    protected:
    private:
        unsigned int m_nf;
        unsigned int m_loop;

};

#endif // QCD_BETA_H
