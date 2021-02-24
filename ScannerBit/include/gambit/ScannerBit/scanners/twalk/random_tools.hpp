#ifndef RANDOM_TOOLS_HPP
#define RANDOM_TOOLS_HPP
#include <iostream>
#include <cstdio>

#include "gambit/Utils/threadsafe_rng.hpp"

template <typename T>
T *matrix(const int xN)
{
     T *temp = new T[xN];

     return temp;
}

template <typename T>
T **matrix(const int xN, const int yN)
{
     T **temp = new T*[xN];

     for (int i = 0; i < xN; i++)
          temp[i] = new T[yN];

     return temp;
}

template <typename T>
T ***matrix(const int xN, const int yN, const int zN)
{
     T ***temp = new T**[xN];

     for (int i = 0; i < xN; i++)
     {
          temp[i] = new T*[yN];
          for (int j = 0; j < yN; j++)
               temp[i][j] = new T[zN];
     }
     return temp;
}

template <typename T>
T *matrix(const int xN, T in)
{
        T *temp = new T[xN];

        for (int i = 0; i < xN; i++)
                temp[i] = in;

        return temp;
}

template <typename T>
T **matrix(const int xN, const int yN, T in)
{
        T **temp = new T*[xN];

        for (int i = 0; i < xN; i++)
        {
                temp[i] = new T[yN];
                for (int j = 0; j < yN; j++)
                        temp[i][j] = in;
        }

        return temp;
}

template <typename T>
T ***matrix(const int xN, const int yN, const int zN, T in)
{
        T ***temp = new T**[xN];

        for (int i = 0; i < xN; i++)
        {
                temp[i] = new T*[yN];
                for (int j = 0; j < yN; j++)
                {
                        temp[i][j] = new T[zN];
                        for (int k = 0; k < zN; k++)
                                temp[i][j][k] = in;
                }
        }
        return temp;
}

template <typename T>
                T *matrix(const int xN, T *in)
{
        T *temp = new T[xN];
        for (int i = 0; i < xN; i++)
                temp[i] = in[i];

        return temp;
}

template <typename T>
                T **matrix(const int xN, const int yN, T **in)
{
        T **temp = new T*[xN];

        for (int i = 0; i < xN; i++)
        {
                temp[i] = new T[yN];
                for (int j = 0; j < yN; j++)
                        temp[i][j] = in[i][j];
        }

        return temp;
}

template <typename T>
                T ***matrix(const int xN, const int yN, const int zN, T ***in)
{
        T ***temp = new T**[xN];

        for (int i = 0; i < xN; i++)
        {
                temp[i] = new T*[yN];
                for (int j = 0; j < yN; j++)
                {
                        temp[i][j] = new T[zN];
                        for (int k = 0; k < zN; k++)
                                temp[i][j][k] = in[i][j][k];
                }
        }
        return temp;
}


template <typename T>
void del(T *temp)
{
     delete[] temp;
     temp = NULL;
}

template <typename T>
void del(T **temp, int xN)
{
     for (int i = 0; i < xN; i++)
          delete[] temp[i];

     delete[] temp;
     temp = NULL;
}

template <typename T>
void del(T ***temp, int xN, int yN)
{
     for (int i = 0; i < xN; i++)
     {
          for (int j = 0; j < yN; j++)
               delete[] temp[i][j];
          delete[] temp[i];
     }

     delete[] temp;
     temp = NULL;
}

template<class T>
inline const T SQ(const T a) {return a*a;}

template<class T>
inline const T SQR(const T a) {return a*a;}

class Cholesky
{
    private:
        double **el;

        protected:
                int num;


    public:
        Cholesky(const int nin) : num(nin)
        {
            el = matrix <double> (num, num);
        }

        Cholesky(double **a, const int nin) : num(nin)
        {
            el = matrix <double> (num, num);
            double sum = 0;
            int i, j, k;

            for (i = 0; i < num; i++)
                for (j = 0; j < num; j++)
                    el[i][j] = a[i][j];

            for (i = 0; i < num; i++)
            {
                for (j = i; j < num; j++)
                {
                    for(sum = el[i][j], k = i - 1; k >= 0; k--)
                        sum -= el[i][k]*el[j][k];
                    if(i ==j)
                    {
                        if(sum <= 0.0)
                        {
                                                        std::cout << "Cholesky failed " << sum << std::endl;
                            getchar();
                        }
                        el[i][i] = sqrt(sum);
                    }
                    else
                        el[j][i] = sum/el[i][i];
                }
            }
            for (i = 0; i < num; i++)
                for (j = 0; j < i; j++)
                    el[j][i] = 0.0;
        }

        bool EnterMatM(double **a, const int min)
        {
            double sum = 0;
            int i, j, k;

            for (i = 0; i < num; i++)
            {
                for (j = 0; j < num; j++)
                {
                    el[i][j] = a[i][j];
                    //out1 << el[i][j] << "   " << endl;
                }
                //out1 << endl;
            }

            if (num >= min)
            {
                k = min -1;
                int l = num - min + 1;
                for (i = 0; i < l; i++)
                {
                    for (j = k+i; j < num; j++)
                        el[i][j] = el[j][i] = 0.0;
                }
            }

            for (i = 0; i < num; i++)
            {
                for (j = i; j < num; j++)
                {
                    for(sum = el[i][j], k = i - 1; k >= 0; k--)
                        sum -= el[i][k]*el[j][k];
                    if(i ==j)
                    {
                        if(sum <= 0.0)
                            return true;
                        el[i][i] = sqrt(sum);
                    }
                    else
                        el[j][i] = sum/el[i][i];
                }
            }
            for (i = 0; i < num; i++)
                for (j = 0; j < i; j++)
                    el[j][i] = 0.0;

//                         ofstream out2("cov2.dat");
//             double **ct = matrix <double> (n, n, 0.0);
//             for (i = 0; i < num; i++)
//                 for (j = 0; j < n; j++)
//                     for (k = 0; k < num; k++)
//                         ct[i][j] += el[i][k]*el[j][k];
//             for (i = 0; i < num; i++)
//             {
//                 for (j = 0; j < num; j++)
//                     out2 << ct[i][j] << "   ";
//                 out2 << endl;
//             }
//             cout << "finished" << endl;
//            getchar();

            return false;
        }

        bool EnterMat(double **a)
        {
            double sum = 0;
            int i, j, k;

            for (i = 0; i < num; i++)
            {
                for (j = 0; j < num; j++)
                {
                    el[i][j] = a[i][j];
                }
            }

            for (i = 0; i < num; i++)
            {
                for (j = i; j < num; j++)
                {
                    for(sum = el[i][j], k = i - 1; k >= 0; k--)
                        sum -= el[i][k]*el[j][k];
                    if(i ==j)
                    {
                        if(sum <= 0.0)
                            return false;
                        el[i][i] = sqrt(sum);
                    }
                    else
                        el[j][i] = sum/el[i][i];
                }
            }
            for (i = 0; i < num; i++)
                for (j = 0; j < i; j++)
                    el[j][i] = 0.0;

                        return true;
        }

                bool EnterMat(const std::vector<std::vector<double>> &a)
                {
                        double sum = 0;
                        int i, j, k;

                        for (i = 0; i < num; i++)
                        {
                                for (j = 0; j < num; j++)
                                {
                                        el[i][j] = a[i][j];
                                }
                        }

                        for (i = 0; i < num; i++)
                        {
                                for (j = i; j < num; j++)
                                {
                                        for(sum = el[i][j], k = i - 1; k >= 0; k--)
                                                sum -= el[i][k]*el[j][k];
                                        if(i ==j)
                                        {
                                                if(sum <= 0.0)
                                                        return false;
                                                el[i][i] = sqrt(sum);
                                        }
                                        else
                                                el[j][i] = sum/el[i][i];
                                }
                        }
                        for (i = 0; i < num; i++)
                                for (j = 0; j < i; j++)
                                        el[j][i] = 0.0;

                        return true;
                }

        void EnterMat(double **a, int nin)
        {
            del <double> (el, num);
            num = nin;
            el = matrix <double> (num, num);
            EnterMat(a);
        }

        void ElMult (double *y, double *b)
        {
            int i, j;
            for(i = 0; i < num; i++)
            {
                b[i] = 0.0;
                for (j = 0; j <= i; j++)
                    b[i] += el[i][j]*y[j];
            }
        }

        void ElMult (double *y)
        {
            int i, j;
            double *b = new double[num];
            for(i = 0; i < num; i++)
            {
                b[i] = 0.0;
                for (j = 0; j <= i; j++)
                {
                    b[i] += el[i][j]*y[j];
                }
            }
            for (i = 0; i < num; i++)
            {
                y[i] = b[i];
            }
            delete[] b;
        }

        void Solve (double *b, double *x)
        {
            int i, k;
            double sum;

            for (i = 0; i < num; i++)
            {
                for (sum = b[i], k=i-1; k >=0; k--)
                    sum -= el[i][k]*x[k];
                x[i]=sum/el[i][i];
            }

            for (i = num-1; i >=0; i--)
            {
                for (sum = x[i], k=i+1; k<num; k++)
                    sum -= el[k][i]*x[k];
                x[i]=sum/el[i][i];
            }
        }

        double Square(double *y, double *y0)
        {
            int i, j;
            double sum;
            double *x = new double[num];

            for (i = 0; i < num; i++)
            {
                for (sum = (y[i]-y0[i]), j=0; j < i; j++)
                    sum -= el[i][j]*x[j];
                x[i]=sum/el[i][i];
            }

            sum = 0.0;
            for (i = 0; i < num; i++)
                sum += x[i]*x[i];

            delete[] x;

            return sum;
        }

        double Square(double *y, double *y0, int *map)
        {
            int i, j;
            double sum;
            double *x = new double[num];

            for (i = 0; i < num; i++)
            {
                for (sum = (y[map[i]]-y0[i]), j=0; j < i; j++)
                    sum -= el[i][j]*x[j];
                x[i]=sum/el[i][i];
            }

            sum = 0.0;
            for (i = 0; i < num; i++)
                sum += x[i]*x[i];

            delete[] x;

            return sum;
        }

        void Inverse(double **ainv)
        {
            double sum;

            for (int i = 0; i < num; i++)
                for (int j = 0; j <= i; j++)
                {
                    sum = (i == j ? 1.0 : 0.0);
                    for (int k = i-1; k >= j; k--)
                        sum -= el[i][k]*ainv[j][k];
                    ainv[j][i] = sum/el[i][i];
                }

            for (int i = num - 1; i >= 0; i--)
                for (int j = 0; j <= i; j++)
                {
                    sum = (i < j ? 0.0 : ainv[j][i]);
                    for (int k = i + 1; k < num; k++)
                        sum -= el[k][i]*ainv[j][k];
                    ainv[i][j] = ainv[j][i] = sum/el[i][i];
                }
        }

        double DetSqrt()
        {
            double temp = 1.0;
            for (int i = 0; i < num; i++)
                temp *= el[i][i];
            return temp;
        }
        ~Cholesky()
        {
            del <double> (el, num);
        }
};

class Ran_old
{
    private:
        unsigned long long int u, v, w;

    public:
        Ran_old(unsigned long long int j) : v(4101842887655102017LL), w(1)
        {
            u = j ^ v; int64();
            v = u; int64(); int64();
            w = v; int64(); int64();
        }
        inline unsigned long long int int64()
        {
            u = u * 2862933555777941757LL + 7046029254386353087LL;
            v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
            w = 4294957665U*(w & 0xffffffff) + (w >> 32);
            unsigned long long int x = u ^ (u << 21); x ^= x >> 35; x ^= x << 4;
            return (x + v) ^ w;
        }
        inline double Doub(){return 5.42101086242752217E-20 * int64();}
        inline unsigned int int32(){return (unsigned int)int64();}
};

class Ran
{
public:
        Ran(unsigned long long int){}
        inline double Doub(){return Gambit::Random::draw();}
};

class ExponDev : public Ran
{
    private:
        double beta;
    public:
        ExponDev(double din, unsigned long long ii) : Ran(ii), beta(din){}
        double Dev()
        {
            double u;
            do
            {
                u = Doub();
            }
            while(u == 0);

            return -log(u)/beta;
        }
};

class NormalDev : public Ran
{
    private:
        double mu, sig;

    public:
        NormalDev(double mmu, double ssig, unsigned long long i) : Ran(i), mu(mmu), sig(ssig){}
        double  Dev()
        {
            double u, v, x, y, q;
            do
            {
                u = Doub();
                v = 1.7156*(Doub() - 0.5);
                x = u - 0.449871;
                y = fabs(v) + 0.386595;
                q = x*x + y*(0.19600*y-0.25472*x);
            }
            while(q > 0.27597 && (q > 0.27846 || v*v > -4.0*log(u)*u*u));

            return mu + sig*v/u;
        }
};

class BasicDevs : public Ran
{
    private:

    public:
        BasicDevs(unsigned long long i) : Ran(i) {}

        double  Dev()
        {
            double u, v, x, y, q;
            do
            {
                u = Doub();
                v = 1.7156*(Doub() - 0.5);
                x = u - 0.449871;
                y = fabs(v) + 0.386595;
                q = x*x + y*(0.19600*y-0.25472*x);
            }
            while(q > 0.27597 && (q > 0.27846 || v*v > -4.0*log(u)*u*u));

            return v/u;
        }

        double ExpDev()
        {
            double u;
            do
            {
                u = Doub();
            }
            while(u == 0);

            return -log(u);
        }
};

class MultiNormalDev : public Ran, public Cholesky
{
    private:
        int mm;
        double f;
        double *spt;

    public:
        MultiNormalDev (double **vvar, double fin, unsigned long long int j, int nin) : Ran(j), Cholesky(vvar, nin), mm(nin), f(fin)
        {
            spt = matrix <double> (mm);
        }
        void Dev(double *pt, double *mean)
        {
            double u, v, x, y, q;
            for (int i = 0; i < mm; i++)
            {
                do
                {
                    u = Doub();
                    v = 1.7156*(Doub() - 0.5);
                    x = u - 0.449871;
                    y = fabs(v) + 0.386595;
                    q = x*x + y*(0.19600*y-0.25472*x);
                }
                while(q > 0.27597 && (q > 0.27846 || v*v > -4.0*log(u)*u*u));
                spt[i] = v/u;
            }
            ElMult(spt, pt);
            for (int i = 0; i < mm; i++)
                pt[i] = f*pt[i] + mean[i];
        }
        void Dev(double **cvar, double *pt, double *mean)
        {
            double u, v, x, y, q;
            for (int i = 0; i < mm; i++)
            {
                do
                {
                    u = Doub();
                    v = 1.7156*(Doub() - 0.5);
                    x = u - 0.449871;
                    y = fabs(v) + 0.386595;
                    q = x*x + y*(0.19600*y-0.25472*x);
                }
                while(q > 0.27597 && (q > 0.27846 || v*v > -4.0*log(u)*u*u));
                spt[i] = v/u;
            }
            EnterMat(cvar);
            ElMult(spt, pt);
            for (int i = 0; i < mm; i++)
                pt[i] = f*pt[i] + mean[i];
        }
        ~MultiNormalDev()
        {
            del <double> (spt);
        }
};

class AdvanceDevs : public BasicDevs, public Cholesky
{
    private:
        double fac;

    public:
        AdvanceDevs(int nin, double din, unsigned long long iin) :  BasicDevs(iin), Cholesky(nin), fac(din)
        {
        }

        AdvanceDevs(double **vvar, const int nin, double din, unsigned long long iin) :  BasicDevs(iin), Cholesky(vvar, nin), fac(din)
        {
        }

        double MultiDevDist()
        {
            double dist = 0.0;

            if(Doub() < 0.33)
                dist = ExpDev();
            else
            {
                double temp;
                for (int i = 0; i < 2; i++)
                {
                    temp = Dev();
                    dist += temp*temp;
                }
                dist = sqrt(dist/2.0);
            }

            return fac*dist;
        }

        double MultiDevPDF(double r, int dim)
        {
            return -(2.0 - dim)*std::log(r/fac) - r*r/fac/fac/2.0;
        }

        void MultiDev(double *pin, double *p0)
        {
            int i;
            double dist = 0.0;

            std::vector<double> vec(num);
            double norm = 0.0;
            for (i = 0; i < num; i++)
            {
                vec[i] = Dev();
                norm += vec[i]*vec[i];
            }
            norm = sqrt(norm);

            if(Doub() < 0.33)
                dist = ExpDev();
            else
            {
                double temp;
                for (i = 0; i < 2; i++)
                {
                    temp = Dev();
                    dist += temp*temp;
                }
                dist = sqrt(dist/2.0);
            }

            ElMult(&vec[0], pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fac*dist*pin[i]/norm + p0[i];
            }

            return;
        }

        void MultiDev(double **cvar, double *pin, double *p0)
        {
            int i;
            double dist = 0.0;

            double vec[num];
            double norm = 0.0;
            for (i = 0; i < num; i++)
            {
                vec[i] = Dev();
                norm += vec[i]*vec[i];
            }
            norm = sqrt(norm);

            if(Doub() < 0.33)
                dist = ExpDev();
            else
            {
                double temp;
                for (i = 0; i < 2; i++)
                {
                    temp = Dev();
                    dist += temp*temp;
                }
                dist = sqrt(dist/2.0);
            }

            EnterMat(cvar);
            ElMult(vec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fac*dist*pin[i]/norm + p0[i];
            }

            return;
        }

        void EllipseDev(double *pin, double *p0, double fin)
        {
            int i;
            double dist = 0.0;

            double vec[num];
            double norm = 0.0;
            for (i = 0; i < num; i++)
            {
                vec[i] = Dev();
                norm += vec[i]*vec[i];
            }
            norm = sqrt(norm);

            dist = pow(Doub(), 1.0/num);

            ElMult(vec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fin*dist*pin[i] + p0[i];
            }

            return;
        }

        void EllipseDev(double **cvar, double *pin, double *p0, double fin)
        {
            int i;
            double dist = 0.0;

            double vec[num];
            double norm = 0.0;
            for (i = 0; i < num; i++)
            {
                vec[i] = Dev();
                norm += vec[i]*vec[i];
            }
            norm = sqrt(norm);

            dist = pow(Doub(), 1.0/num);

            EnterMat(cvar);
            ElMult(vec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fin*dist*pin[i] + p0[i];
            }

            return;
        }
};

class RandomPlane : public AdvanceDevs
{
private:
    double **rotVec;
    double **currentVec;
    double **endVec;
    double **endEndVec;
    double **sEndVec;
    int proj, extra;
    double alimt;
    double sqrtAlim, powAlim, ratioAlim, ratioAlimt;

public:
    RandomPlane(const int projin, const int nin, const double din, const double alim, const double alimt, unsigned long long iin) : AdvanceDevs(nin, din, iin), proj(projin), alimt(alimt)
    {
        rotVec = matrix <double> (nin, nin);
        RandRot();
        if (proj > num) proj = num;
        extra = num % proj;
        endVec = currentVec + num - extra;
        endEndVec = currentVec + num;
        sEndVec = currentVec + num - proj;
        sqrtAlim = sqrt(alim);
        powAlim = pow(alim, 0.5 - proj);
        double vol1 = 2.0*(sqrt(alim) - 1.0);
        double vol2 = (1.0 - pow(alim, 0.5 - proj))/(proj - 0.5);
        ratioAlim = vol1/(vol1 + vol2);
        ratioAlimt = (alimt - 1.0)/(2.0*alimt + proj - 2.0);
    }

    double WalkDev()
    {
        if (Doub() <= ratioAlim)
            return SQ(1.0 + Doub()*(sqrtAlim - 1.0));
        else
            return pow(powAlim + Doub()*(1.0 - powAlim), 1.0/(proj - 0.5));
    }

    double TransDev()
    {
        if (Doub() < ratioAlimt)
        {
            return -pow(Doub(), 1.0/(alimt + proj - 1.0));
        }
        else
        {
            return -pow(Doub(), 1.0/(1.0 - alimt));
        }
    }

    double KWalkDev()
    {
        if (Doub() < 0.5)
        {
            if (Doub() <= ratioAlim)
            {
                return SQ(1.0 + Doub()*(sqrtAlim - 1.0));
            }
            else
            {
                return pow(powAlim + Doub()*(1.0 - powAlim), 1.0/(proj - 0.5));
            }
        }
        else
        {
            if (Doub() < ratioAlimt)
            {
                return -pow(Doub(), 1.0/(alimt + proj - 1.0));
            }
            else
            {
                return -pow(Doub(), 1.0/(1.0 - alimt));
            }
        }
    }

    bool KWalkDev(double &Z)
    {
        if (Doub() < 0.5)
        {
            Z = SQ(1.0/sqrtAlim + Doub()*(sqrtAlim - 1.0/sqrtAlim));

            return pow(Z, proj - 1) > Doub();
        }
        else
        {
            if (Doub() < (alimt - 1.0)/(2.0*alimt))
            {
                Z = -pow(Doub(), 1.0/(alimt + 1.0));
            }
            else
            {
                Z = -pow(Doub(), 1.0/(1.0 - alimt));
            }

            return pow(Z, proj - 2) > Doub();
        }
    }

    double WalkDev(double *ptrOut, double *ptr, double *ptr0)
    {
        double Z;

        Z = SQ(1.0/sqrtAlim + Doub()*(sqrtAlim - 1.0/sqrtAlim));

        Mult(ptrOut, ptr, ptr0, Z);

        return (proj - 1.0)*log(Z);
    }

    double TransDev(double *ptrOut, double *ptr, double *ptr0)
    {
        double Z;

        if (Doub() < (alimt - 1.0)/(2.0*alimt))
        {
            Z = -pow(Doub(), 1.0/(alimt + 1.0));
        }
        else
        {
            Z = -pow(Doub(), 1.0/(1.0 - alimt));
        }

        Mult(ptrOut, ptr, ptr0, Z);

        return (proj - 2.0)*log(-Z);
    }

    void Mult2(double *ptrOut, double *ptr, double *ptr0, const double Z)
    {
        std::vector<double> z(proj);
        for (int i = 0; i < proj; i++)
        {
            z[i] = 0.0;
            for (int j = 0; j < num; j++)
            {
                z[i] += (Z-1.0)*(ptr[j] - ptr0[j])*currentVec[i][j];
            }
        }

        for (int j = 0; j < num; j++)
        {
            ptrOut[j] = ptr[j];
            for (int i = 0; i < proj; i++)
            {
                ptrOut[j] += z[i]*currentVec[i][j];
            }
        }

        currentVec++;// += proj;
        if (currentVec == sEndVec)
        {
            for (double **vec = currentVec, **vec2 = rotVec; vec != endEndVec; vec++, vec2++)
            {
                double *temp = *vec2;
                *vec2 = *vec;
                *vec = temp;
            }
            RandRot(extra);
        }
    }

    void Mult(double *ptrOut, double *ptr, double *ptr0, const double Z)
    {
        RandRot(0, proj);

        std::vector<double> z(proj);
        for (int i = 0; i < proj; i++)
        {
            z[i] = 0.0;
            for (int j = 0; j < num; j++)
            {
                z[i] += (Z-1.0)*(ptr[j] - ptr0[j])*currentVec[i][j];
            }
        }

        for (int j = 0; j < num; j++)
        {
            ptrOut[j] = ptr[j];
            for (int i = 0; i < proj; i++)
            {
                ptrOut[j] += z[i]*currentVec[i][j];
            }
        }
    }

    void HopBlow(double *ptrOut, double *ptrIn, double *ptr, double *ptr0)
    {
        double max = 0;

        RandRot(0, proj);

        std::vector<double> z(proj);
        for (int i = 0; i < proj; i++)
        {
            z[i] = 0.0;
            for (int j = 0; j < num; j++)
            {
                z[i] += (ptr[j] - ptr0[j])*currentVec[i][j];
            }
        }

        for (auto &&elem : z)
        {
            double pt = std::abs(elem);
            if (pt > max)
                max = pt;
        }

        double r = MultiDevDist();

        for (int j = 0; j < num; j++)
        {
            ptrOut[j] = ptrIn[j];
            for (int i = 0; i < proj; i++)
            {
                ptrOut[j] += r*max*currentVec[i][j]/3.0;
            }
        }
    }

    void RandRot(const int start = 0)
    {
        double temp;
        std::vector<double> vec(num);
        int i, j, k;

        for (i = start; i < num; i++)
        {
            for (j = 0; j < num; j++)
                vec[j] = Dev();
            for (j = 0; j < i; j++)
            {
                temp = 0.0;
                for (k = 0; k < num; k++)
                    temp += vec[k]*rotVec[j][k];
                for (k = 0; k < num; k++)
                    vec[k] -= temp*rotVec[j][k];
            }
            temp = 0.0;
            for (j = 0; j < num; j++)
                temp += vec[j]*vec[j];
            temp = sqrt(temp);
            for (j = 0; j < num; j++)
                rotVec[i][j] = vec[j]/temp;
        }

        currentVec = rotVec;
    }

    void RandRot(const int start, const int end)
    {
        double temp;
        std::vector<double> vec(num);
        int i, j, k;

        for (i = start; i < end; i++)
        {
            for (j = 0; j < num; j++)
                vec[j] = Dev();
            for (j = 0; j < i; j++)
            {
                temp = 0.0;
                for (k = 0; k < num; k++)
                    temp += vec[k]*rotVec[j][k];
                for (k = 0; k < num; k++)
                    vec[k] -= temp*rotVec[j][k];
            }
            temp = 0.0;
            for (j = 0; j < num; j++)
                temp += vec[j]*vec[j];
            temp = sqrt(temp);
            for (j = 0; j < num; j++)
                rotVec[i][j] = vec[j]/temp;
        }

        currentVec = rotVec;
    }

    int Dim() const {return proj;}

    ~RandomPlane()
    {
        del <double> (rotVec, num);
    }
};

class RandomBasis : public BasicDevs
{
    private:
        double **rotVec;

    protected:
        int num;
        double **currentVec;
        double **endVec;

    public:
        RandomBasis(int nin, unsigned long long iin) : BasicDevs(iin), num(nin)
        {
            rotVec = matrix <double> (nin, nin);
            RandRot();
            endVec = currentVec + num;
        }

        void ChangeDim(const int nin)
        {
            del <double> (rotVec, num);
            num = nin;
            rotVec = matrix <double> (nin, nin);
            RandRot();
            endVec = currentVec + num;
        }

        void RandRot()
        {
            double temp;
            double vec[num];
            int i, j, k;

            for (i = 0; i < num; i++)
            {
                for (j = 0; j < num; j++)
                    vec[j] = Dev();
                for (j = 0; j < i; j++)
                {
                    temp = 0.0;
                    for (k = 0; k < num; k++)
                        temp += vec[k]*rotVec[j][k];
                    for (k = 0; k < num; k++)
                        vec[k] -= temp*rotVec[j][k];
                }
                temp = 0.0;
                for (j = 0; j < num; j++)
                    temp += vec[j]*vec[j];
                temp = sqrt(temp);
                for (j = 0; j < num; j++)
                    rotVec[i][j] = vec[j]/temp;
            }

            currentVec = rotVec;
        }

        double RanMult(double **cin)
        {
            int i, j;
            double temp = 0.0;

            for (i = 0; i < num; i++)
            {
                for (j = 0; j < num; j++)
                {
                    temp += (*currentVec)[i]*cin[i][j]*(*currentVec)[j];
                }
            }
            return temp;
        }

        void RanMult(const double in, double *out)
        {
            int i;
            double *ptr = *currentVec;

            for (i = 0; i < num; i++)
            {
                *out++ = in*(*ptr++);

            }
            return;
        }

        void RanMult(double *in, const double w, double *out)
        {
            int i;
            double *ptr = *currentVec;

            for (i = 0; i < num; i++)
            {
                *out++ = *in++ + w*(*ptr++);
            }
            return;
        }

        double Mag(double *a, double *a0)
        {
            double temp = 0.0;
            int i;
            double *ptr = *currentVec;

            for (i = 0; i < num; i++)
                temp += (*a++-*a0++)*(*ptr++);

            return temp;
        }

        void Adjust(double *a, const double lim, const int iin)
        {
            double temp = (lim - a[iin])/(*currentVec)[iin];
            double *ptr = *currentVec;

            for (int i = 0; i < num; i++)
                a[i] += temp*(*ptr++);
            return;
        }

        virtual void operator ++ (int)
        {
            if (++currentVec == endVec)
            {
                RandRot();
            }
        }

        virtual ~RandomBasis()
        {
            del <double> (rotVec, num);
        }
};

class TransformRandomBasis : public RandomBasis, public Cholesky
{
    private:
                int num;

    public:
        TransformRandomBasis(double **vvar, int nin, unsigned long long iin) : RandomBasis(nin, iin), Cholesky(vvar, nin), num(nin)
        {
            double **ptr = currentVec;
            for (int i = 0; i < num; i++)
            {
                ElMult(*ptr++);
            }
        }

        void operator ++ (int)
        {
            if (++currentVec == endVec)
            {
                RandRot();
                double **ptr = currentVec;
                for (int i = 0; i < num; i++)
                {
                    ElMult(*ptr++);
                }
            }
        }
};

class MultiNormDev : public RandomBasis, public Cholesky
{
    private:
        double fac;
                int num;

    public:
        MultiNormDev(int nin, double din, unsigned long long iin) : RandomBasis(nin, iin), Cholesky(nin), fac(din), num(nin)
        {
        }

        MultiNormDev(double **vvar, const int nin, double din, unsigned long long iin) : RandomBasis(nin, iin), Cholesky(vvar, nin), fac(din), num(nin)
        {
        }

        void MultiDev(double *pin, double *p0)
        {
            int i;
            double dist = 0.0;

            if(Doub() < 0.33)
                dist = ExpDev();
            else
            {
                double temp;
                for (i = 0; i < 2; i++)
                {
                    temp = Dev();
                    dist += temp*temp;
                }
                dist = sqrt(dist/2.0);
            }

            ElMult(*currentVec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fac*dist*pin[i] + p0[i];
            }
            (*this)++;

            return;
        }

        void MultiDev(double **cvar, double *pin, double *p0)
        {
            int i;
            double dist = 0.0;

            if(Doub() < 0.33)
                dist = ExpDev();
            else
            {
                double temp;
                for (i = 0; i < 2; i++)
                {
                    temp = Dev();
                    dist += temp*temp;
                }
                dist = sqrt(dist/2.0);
            }

            EnterMat(cvar);
            ElMult(*currentVec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fac*dist*pin[i] + p0[i];
            }
            (*this)++;

            return;
        }

        void MultiDevGauss(double **cvar, double *pin, double *p0)
        {
            int i;
            double dist = 0.0;

            double temp;
            for (i = 0; i < 2; i++)
            {
                temp = Dev();
                dist += temp*temp;
            }
            dist = sqrt(dist/2.0);


            EnterMat(cvar);
            ElMult(*currentVec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fac*dist*pin[i] + p0[i];
            }
            (*this)++;

            return;
        }

        void EllipseDev(double *pin, double *p0, double fin)
        {
            int i;
            double dist = 0.0;

            dist = pow(Doub(), 1.0/num);

            ElMult(*currentVec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fin*dist*pin[i] + p0[i];
            }
            (*this)++;

            return;
        }

        void EllipseDev(double **cvar, double *pin, double *p0, double fin)
        {
            int i;
            double dist = 0.0;

            dist = pow(Doub(), 1.0/num);

            EnterMat(cvar);
            ElMult(*currentVec, pin);
            for (i = 0; i < num; i++)
            {
                pin[i] = fin*dist*pin[i] + p0[i];
            }
            (*this)++;

            return;
        }
};

#endif
