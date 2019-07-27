#include <iostream>
#include <math.h>
#include <vector>

int count = 0;

struct input_pars {
    double v1;
    double v2;
    double mA;
    double lambda1;
    double lambda2;
    double lambda3;
    double lambda4;
    double lambda5;
    double lambda6;
    double lambda7;
    double tanb;
};

double get_Lambda1(input_pars input) {
    double lam1 = input.lambda1, lam2 = input.lambda2, lam345 = input.lambda3 + input.lambda4 + input.lambda5;
    double lam6 = input.lambda6, lam7 = input.lambda7, b = atan(input.tanb), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
    return lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
}

double get_Lambda5(input_pars input) {
    double lam1 = input.lambda1, lam2 = input.lambda2, lam345 = input.lambda3 + input.lambda4 + input.lambda5, lam5= input.lambda5;
    double lam6 = input.lambda6, lam7 = input.lambda7, b = atan(input.tanb), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
    return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
}

double get_Lambda6(input_pars input) {
    double lam1 = input.lambda1, lam2 = input.lambda2, lam345 = input.lambda3 + input.lambda4 + input.lambda5;
    double lam6 = input.lambda6, lam7 = input.lambda7, b = atan(input.tanb), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*b)*lam6 + sb*sin(3.*b)*lam7;
}

double get_alpha(input_pars input) {
         double v_1 = input.v1, v_2 = input.v2;
         double b = atan(v_2/v_1); 
         double v2 = pow(v_1,2) + pow(v_2,2);
         double mA = input.mA;
         double mA_2 = pow(mA,2);
         double Lam1 = get_Lambda1(input), Lam5 = get_Lambda5(input), Lam6 = get_Lambda6(input);
         double tan2ba = (2.0*Lam6*v2)/(mA_2 + (Lam5-Lam1)*v2);
         double s2ba = -(2.0*Lam6*v2)/sqrt(pow((mA_2 + (Lam5-Lam1)*v2),2) + 4.0*pow(Lam6,2)*v2*v2);
         double c2ba = s2ba/tan2ba;
         double c2ba_alternate = -(mA_2 + (Lam5-Lam1)*v2)/sqrt(pow((mA_2 + (Lam5-Lam1)*v2),2) + 4.0*pow(Lam6,2)*v2*v2);
         double ba = 0.5*acos(c2ba);
         double ba_alternative = 0.5*acos(c2ba_alternate);
         double alpha = b - ba;
         double alpha_alternative = b - ba_alternative;
        //  std::cout << "tan2ba: " << tan2ba << std::endl;
        //  std::cout << "s2ba: " << tan2ba << std::endl;
        //  std::cout << "c2ba: " << tan2ba << std::endl;
        //  std::cout << "ba: " << ba << std::endl;
        //  std::cout << "b: " << b << std::endl;
        //  std::cout << "sba: " << sin(ba) << std::endl;
         std::cout << "alpha: " << alpha << std::endl;
         std::cout << "alpha_alternative: " << alpha_alternative << std::endl;
         return alpha;
}

double generate_random(double min, double max) {
    double r = ((double) rand() / (RAND_MAX));
    return min + (r * (max-min));
}

int main()
{
    double alpha = 0.0;
    input_pars input;
    const double vev = 247.0;
    while (!std::isnan(alpha))
    {
        double tanb = generate_random(0.01,100.0);
        // std::cout << "tanb: "<< tanb <<std::endl;
        // std::cout << "b: "<< atan(tanb) <<std::endl;
        double v1 = sqrt(vev*vev/(1.0+tanb*tanb)); 
        input.v1 = v1;
        input.v2 = sqrt(vev*vev - v1*v1);
        input.tanb = tanb;
        input.mA = generate_random(10.0,10000.0);
        input.lambda1 = generate_random(-4*M_PI,4*M_PI);
        input.lambda2 = generate_random(-4*M_PI,4*M_PI);
        input.lambda3 = generate_random(-4*M_PI,4*M_PI);
        input.lambda4 = generate_random(-4*M_PI,4*M_PI);
        input.lambda5 = generate_random(-4*M_PI,4*M_PI);
        input.lambda6 = 0.0;
        input.lambda7 = 0.0;

        alpha = get_alpha(input);
        if (count%1000000==0) {
            std::cout << count << std::endl;
        }
        // std::cout << "alpha: "<< alpha << std::endl;
        // std::cout << std::endl << "-----" << std::endl;
        count++;
    }

    // print problem point
    std::cout << std::endl << std::endl << "**DETECTED NAN **" << std::endl;
    std::cout << input.v1 << std::endl;
    std::cout << input.v2 << std::endl;
    std::cout << input.tanb << std::endl;
    std::cout << input.mA << std::endl;
    std::cout << input.lambda1 << std::endl;
    std::cout << input.lambda2 << std::endl;
    std::cout << input.lambda3 << std::endl;
    std::cout << input.lambda4 << std::endl;
    std::cout << input.lambda5 << std::endl;
    return 0;
        


}