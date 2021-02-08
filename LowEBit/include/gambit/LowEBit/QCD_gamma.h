#ifndef QCD_GAMMA_H
#define QCD_GAMMA_H


class QCD_gamma
{
    public:
        QCD_gamma(unsigned int nf, unsigned int loop);
        virtual ~QCD_gamma();
        double chet();
    protected:
    private:
        unsigned int loop;
        unsigned int nf;
};

#endif // QCD_GAMMA_H
