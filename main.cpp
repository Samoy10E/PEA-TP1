#include "eval-perf.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <random>

#define C1 0.2f
#define C2 0.3f

// Exercice 5
void somme_prefixe1(std::vector<int> &tab){
    for(size_t i=1;i<tab.size();i++)
        tab[i] += tab[i-1];
}

void somme_prefixe2(std::vector<int> &tab){
    int res = 0;
    size_t size = tab.size();
    for(size_t i=1;i<size;i++){
        res += tab[i];
        tab[i-1] = res;
    }
}

int flops_somme_prefixe(int n){return n;}

// Exercice 6

void poly1(std::vector<int32_t> tab, int32_t alpha, int32_t &res){
    res = tab[0];
    size_t size = tab.size();
    for(size_t i=1;i<size;i++){
        alpha *= alpha;
        res += alpha*tab[i]; 
    }
}

void poly1(std::vector<float> tab, float alpha, float &res){
    res = tab[0];
    size_t size = tab.size();
    for(size_t i;i<size;i++){
        alpha *= alpha;
        res += alpha*tab[i]; 
    }
}

void poly2(std::vector<int32_t> tab, int32_t alpha, int32_t &res){
    res = tab[-1]*alpha + tab[-2];
    size_t size = tab.size();
    for(size_t i=3;i<size;i++)
        res = res*alpha + tab[size-i]; 
}

void poly2(std::vector<float> tab, float alpha, float &res){
    res = tab[-1]*alpha + tab[-2];
    size_t size = tab.size();
    for(size_t i=3;i<size;i++)
        res = res*alpha + tab[size-i];
    
}

int flops_poly(int n){return n;}

// Exercice 7

void reduce_plus(const std::vector<int32_t> &V, int32_t &res){
    res = 0;
    size_t size = V.size();
    for(size_t i=0;i<size;i++)
        res = res + V[i];
}

void reduce_plus2(const std::vector<int32_t> &V, int32_t &res){
    res = 0;
    size_t size = V.size()/2;
    for(size_t i=0;i<size;i+=2){
        res = res + V[i];
        res = res + V[i+1];
    }

    if (V.size()%2)
        res = res + V[-1];
}

void reduce_mult(const std::vector<int32_t> &V, int32_t &res){
    res = 1;
    size_t size = V.size();
    for(size_t i=0;i<size;i++)
        res = res * V[i];
}

void reduce_mult2(const std::vector<int32_t> &V, int32_t &res){
    res = 1;
    size_t size = V.size()/2;
    for(size_t i=0;i<size;i+=2){
        res = res * V[i];
        res = res * V[i+1];
    }

    if (V.size()%2)
        res = res * V[-1];
}

// Exercice 8

void slowperformance1(float *x, const float *y, const float *z, int n){
    for(int i=0;i<n-2;i++){
        x[i] = x[i]/ M_SQRT2 + y[i] * C1;
        x[i+1] += z[(i%4)*10] * C2;
        x[i+2] += sin((2*M_PI*i)/3) * y[i+2];
    }
}

void slowperformance2(float *x, const float *y, const float *z, int n){
    // i=0
    x[0] = x[0]/ M_SQRT2 + y[0] * C1;
    x[1] += z[10] * C2;
    // i=1
    x[1] += x[1]/ M_SQRT2 + y[1] * C1;

    for(int i=2;i<n-2;i++){
        x[i] =  x[i]/M_SQRT2 
                + y[i]*C1 
                + z[((i-1)%4)*10]*C2 
                + sin((2*M_PI*i)/3)*y[i];
    }
    // i = n-4
    x[n-3] += z[((n-4)%4)*10] * C2;
    x[n-2] += sin((2*M_PI*(n-4))/3) * y[n-2];
    // i = n-3
    x[n-1] += sin((2*M_PI*(n-3))/3) * y[n-1];
}

void slowperformance3(float *x, const float *y, const float *z, int n){
    // i=0
    x[0] = x[0]/ M_SQRT2 + y[0] * C1;
    x[1] += z[10] * C2;
    // i=1
    x[1] += x[1]/ M_SQRT2 + y[1] * C1;

    float res;
    const float SIN = std::sqrt(3)/2;
    int i = 2;
    while(i<n-7){
        res =  x[i]/M_SQRT2 
                + y[i]*C1 
                + z[((i-1)%4)*10]*C2;
        if(i%3==1)
            res += SIN*y[i];
        else if (i%3==2)
            res -= SIN*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]/M_SQRT2 
                + y[i]*C1 
                + z[((i-1)%4)*10]*C2;
        if(i%3==1)
            res += SIN*y[i];
        else if (i%3==2)
            res -= SIN*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]/M_SQRT2 
                + y[i]*C1 
                + z[((i-1)%4)*10]*C2;
        if(i%3==1)
            res += SIN*y[i];
        else if (i%3==2)
            res -= SIN*y[i];
        
        x[i] = res;
        i++;
    }

    while(i<n-4){
        res =  x[i]/M_SQRT2 
                + y[i]*C1 
                + z[((i-1)%4)*10]*C2;
        if(i%3==1)
            res += SIN*y[i];
        else if (i%3==2)
            res -= SIN*y[i];
        
        x[i] = res;
        i++;
    }
    // i = n-4
    x[n-3] += z[((n-4)%4)*10] * C2;
    x[n-2] += sin((2*M_PI*(n-4))/3) * y[n-2];
    // i = n-3
    x[n-1] += sin((2*M_PI*(n-3))/3) * y[n-1];
}

void slowperformance4(float *x, const float *y, const float *z, int n){
    // i=0
    x[0] = x[0]/ M_SQRT2 + y[0] * C1;
    x[1] += z[10] * C2;
    // i=1
    x[1] += x[1]/ M_SQRT2 + y[1] * C1;

    float res;
    const float SIN = std::sqrt(3)/2;
    const float z0 = z[0];
    const float z10 = z[10];
    const float z20 =z [20];
    const float z30 = z[30];

    int i = 2;
    while(i<n-16){
        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;
        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;
        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;
        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;

        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;
    }

    while(i<n-4){
        res =  x[i]*M_SQRT2*0.5f;
        if (i%4==1)
            res += z0*C2;
        else if (i%4==2)
            res += z10*C2;
        else if (i%4==3)
            res += z20*C2;
        else
            res += z30*C2;

        if(i%3==1)
            res += (SIN+C1)*y[i];
        else if (i%3==2)
            res += (C1-SIN)*y[i];
        
        x[i] = res;
        i++;
    }
    
    // i = n-4
    x[n-3] += z[((n-4)%4)*10] * C2;
    x[n-2] += sin((2*M_PI*(n-4))/3) * y[n-2];
    // i = n-3
    x[n-1] += sin((2*M_PI*(n-3))/3) * y[n-1];
}

int flops_slowperformance(int n){return n;}

// Exercice 6

void poly1_bis(std::vector<int32_t> tab, int32_t alpha, int32_t &res){
    res = tab[0];
    size_t size = tab.size();
    int32_t tab_alpha[size];
    tab_alpha[0] = 1;
    for(size_t i=1;i<size;i++)
        tab_alpha[i] = tab_alpha[i-1]*alpha;

    int32_t res1,res2,res3,res4,res5,res6,res7,res8,res9,res10,res11,res12=0;
    size_t i;
    for(i=1;i<size-12;i+=12){
        res1 += alpha*tab[i];
        res2 += alpha*tab[i+1];
        res3 += alpha*tab[i+2];
        res4 += alpha*tab[i+3];
        res5 += alpha*tab[i+4];
        res6 += alpha*tab[i+5];
        res7 += alpha*tab[i+6];
        res8 += alpha*tab[i+7];
        res9 += alpha*tab[i+8];
        res10 += alpha*tab[i+9];
        res11 += alpha*tab[i+10];
        res12 += alpha*tab[i+11];
    }
    res += res1+res2+res3+res4+res5+res6+res7+res8+res9+res10+res11+res12;
    for(;i<size;i++)
        res += alpha*tab[i];
}

void poly2_bis(std::vector<int32_t> tab, int32_t alpha, int32_t &res){
    res = tab[-1]*alpha + tab[-2];
    size_t size = tab.size();

    size_t i;
    for(i=3;i<size-12;i+=12){
        res = res*alpha + tab[size-i];
        res = res*alpha + tab[size-i-1];
        res = res*alpha + tab[size-i-2];
        res = res*alpha + tab[size-i-3];
        res = res*alpha + tab[size-i-4];
        res = res*alpha + tab[size-i-5];
        res = res*alpha + tab[size-i-6];
        res = res*alpha + tab[size-i-7];
        res = res*alpha + tab[size-i-8];
        res = res*alpha + tab[size-i-9];
        res = res*alpha + tab[size-i-10];
        res = res*alpha + tab[size-i-11];
    }

    for(;i<size;i++)
        res = res*alpha + tab[size-i];
}

int main(){
    int n,N, nb_test;
    EvalPerf PE;

    n = 10000;
    nb_test = 10000;

    /**** Exercice 5 ****/
    
    // std::vector<int> tab;

    // srand(time(NULL));
    // for(int j=0;j<n;j++)
    //     tab.push_back(rand()); 

    // PE.start();
    // for(int i=0;i<nb_test;i++)
    //     somme_prefixe2(tab);
    // PE.stop();

    // std::cout<<"valeur retourné:"<<tab[0]<<std::endl;

    // N = flops_somme_prefixe(n);

    /**** Exercice 6 ****/

    // srand(time(NULL));
    // int32_t alpha = rand();
    // int32_t res=0;
    // std::vector<int32_t> tab;
    // for(int j=0;j<n;j++)
    //     tab.push_back((int32_t) rand());

    // PE.start();
    // for(int i=0;i<nb_test;i++){
    //     poly2(tab, alpha, res);
    //     alpha = 1/res + 1 ;
    // }
    // PE.stop();

    // std::cout<<"valeur retourné:"<<res<<std::endl;

    // N = flops_poly(n);


    /**** Exercice 7 ****/

    // srand(time(NULL));
    // int32_t res=0;
    // std::vector<int32_t> tab;
    // for(int j=0;j<n;j++)
    //     tab.push_back((int32_t) rand() + 1);

    // PE.start();
    // for(int i=0;i<nb_test;i++){
    //     reduce_mult2(tab, res);
    //     tab[0] = res%10 + 1;
    // }
    // PE.stop();

    // std::cout<<"valeur retourné:"<<tab[res]<<std::endl;

    // N = flops_poly(n);

    /**** Exercice 8 ****/
    // std::random_device rd;     // Only used once to initialise (seed) engine
    // std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
    // std::uniform_int_distribution<int> uni(0,100); // Guaranteed unbiased

    // float X[n],Y[n],Z[n];
    // for(int i=0;i<n;i++){
    //     X[i] = uni(rng);
    //     Y[i] = uni(rng);
    //     Z[i] = uni(rng);
    // }
    // PE.start();
    // for(int i=0;i<nb_test;i++)
    //     slowperformance4(X,Y,Z,n);
    
    // PE.stop();
    // N = flops_slowperformance(n);
    // std::cout<<"valeur retourné:"<<X[0]<<std::endl;


    /**** Exercice 8 ****/
    srand(time(NULL));
    int32_t alpha = rand();
    int32_t res=0;
    std::vector<int32_t> tab;
    for(int j=0;j<n;j++)
        tab.push_back((int32_t) rand());

    PE.start();
    for(int i=0;i<nb_test;i++){
        poly2_bis(tab, alpha, res);
        alpha = 1/res + 1 ;
    }
    PE.stop();
    
    N = flops_poly(n);
    std::cout<<"valeur retourné:"<<res<<std::endl;

    std::cout<<"* nbr cycles: "<<PE.nb_cycle()/nb_test<<std::endl;
    std::cout<<"* nbr secondes: "<<PE.second()/nb_test<<std::endl;
    std::cout<<"* nbr millisecondes: "<<PE.millisecond()/nb_test<<std::endl;
    std::cout<<"* CPI= "<<PE.CPI(N)/nb_test<<std::endl;
    std::cout<<"* IPC= "<<PE.IPC(N)/nb_test<<std::endl;

    return 0;
}