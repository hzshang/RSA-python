#include <gmp.h>
#include <gmpxx.h>
#include "util.h"
gmp_randclass *r;
static void init_random();
void (*init_rand_ptr)() = init_random;

mpz_class m_gcd(mpz_class op1,mpz_class op2){
    mpz_class a;
    mpz_class b;
    if (op1<op2){
        a=op2;
        b=op1;
    }else{
        a=op1;
        b=op2;
    }
    while(a%b!=0){
        mpz_class c=a%b;
        a=b;
        b=c;
    }
    return b;
}

mpz_class m_pow(mpz_class x,mpz_class e,mpz_class N){
    mpz_class ret;
    mpz_powm(ret.get_mpz_t(),x.get_mpz_t(),e.get_mpz_t(),N.get_mpz_t());
    return ret;
}

static void init_random(){
    unsigned int seed;
    const char *ptr="/dev/urandom";
    FILE *rand=fopen(ptr,"r");
    if( rand == NULL){
        perror(ptr);
        exit(1);
    }
    fread(&seed,sizeof(int),1,rand);
    fclose(rand);
    r=new gmp_randclass(gmp_randinit_default);
    r->seed(seed);
}

mpz_class get_random_r(const mpz_class& begin,const mpz_class& end){
    // get a random number between begin ~ end (inclusive)
    mpz_class tmp=get_random(end-begin);
    return tmp+begin;
}
static inline void check_init(){
    if( init_rand_ptr ){
        init_rand_ptr();
        init_rand_ptr=NULL;
    }
}

mpz_class get_random(const mpz_class& end){
    check_init();
    return r->get_z_range(end);
}

mpz_class get_random_bits(int bits){
    check_init();
    return r->get_z_bits(bits);
}

void extend_gcd(mpz_class a,mpz_class b,mpz_class& s,mpz_class& t,mpz_class& r){
    mpz_class s1=1,s2=0;
    mpz_class t1=0,t2=1;
    mpz_class r1=a,r2=b;
    mpz_class q;
    while (r2>0){
        q=r1/r2;
        r=r1 - q*r2;
        r1=r2;
        r2=r;

        s = s1 - q*s2;
        s1=s2;
        s2=s;

        t = t1 - q*t2;
        t1 = t2;
        t2 = t;
    }
    r=r1;
    s=s1;
    t=t1;
}

mpz_class invert(mpz_class x, mpz_class N){
    mpz_class s,t,r;
    extend_gcd(x,N,s,t,r);
    return (s%N + N ) %N;
}


