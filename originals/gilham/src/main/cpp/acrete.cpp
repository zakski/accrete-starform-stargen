/* ACRETE.CPP - Coded Steve Gilham 11-MAR-1995 */
//              version 1.1 SG 18-MAR-1995 : re-layout, test&tweak
//                                           most important s.mass^0.333, not'/'
#include <iostream>
#include <math.h>


typedef short I2;   // hide base types
typedef long I4;
typedef unsigned long U4;
typedef float R4;
typedef double R8;

double safesqrt(double d)
{
//        cout << "sqrt of " << d << "\n";
    if(d <= 0)
    {
        return 0;
    }else{
        return sqrt(d);
    }
}

double safepow(double d, double i)
{
//        cout << i << "th power of " << d << "\n";
    if(d <= 0)
    {
        return 0;
    }else{
        return pow(d,i);
    }
}
                       
// linear congruential random numbers - algorithm as per
// VMS MTH$RANDOM function                      
#define I216 65536                      
class Random
{
    U4 seed;
public:
    Random();
    R8 next(); // linear congruential pseudo random numbers
};

Random:: Random()
{  
    U4 temp;
	std::cout << "Enter seed value (0 default)";
	std::cin >> temp;
    seed = (temp ? temp : (I4) 50957);
}

R8 Random::next() // linear congruential pseudo random numbers
{      // seed -> (1+seed*69069) % (2^32)
    U4 high = seed/I216;
    U4 low = seed - (high*I216);
    U4 temp = low;
    U4 work;
    // split into two quantities of 16 bytes + overflow room
    low = (low*3533)+1; // 69069 = 3533+65536
    work = low/I216;
    low = low - work*I216; // carry high word
    // lower word + carry + 65536*low  all shifted down 1 word
    high = (high*3533) + work + temp;
    work = high/I216;
    high -= (work*I216);
    seed = high*I216 + low;
    // extract return value            
    temp = high/256;
    R8 x1 = temp;  // truncate first
    R8 x2 = (high - temp*256);
    R8 x3 = low/256; // truncate first
    return ((((x3/256.0)+x2)/256.0)+x1)/256.0;
}

// the star that will gain the planets
class Sun
{
    R8 m;
    R8 luminosity;
public:
    Sun();
    // inner edge of accretion disk
    R8 melt() {return (0.3*safesqrt(luminosity));}
    R8 mass() {return m;}
    R8 flux() {return luminosity;}
};

Sun::Sun()
{  
	std::cout << "Enter mass of star (Sun=1), range 0.1 to 10\n";
	std::cin >> m;
    if(m < 0.1 || m > 10) m = 1.0;
    luminosity = m >= 0.4 ?
                 m*m*m*m :
                 0.23 * safepow(m,2.3);
}

// the disk from which the planets will grow
class DustCloud
{
    R8 dust[501];
    R8 gasRatio;
    R8 e;
    R8 least;
    I2 inner;
    I2 outer;
public:
    DustCloud();
    DustCloud(Sun& s);
    R8 eccentricity() {return e;}
    // mass-weighted random location of the next nucleus;
    R8 nucleus(Random *r);
    R8 sweep (R8 from, R8 to);
    R8 gas() { return gasRatio;}
    R8 mass();
};

DustCloud::DustCloud()
{
    int i;
    for(i=0; i<=500; i++) dust[i]=0.0;
    least = 0.0;
    gasRatio = 25.0;
    e = 0.35;
    inner = 3;
    outer = 500;
}

DustCloud::DustCloud(Sun& s)
{
    R8 temp, gas, density;
    int i;
    for(i=0; i<=500; i++) dust[i]=0.0;
    least = 0.0;

	std::cout << "Maximum nucleus eccentricity (Dole=.35)\n";
	std::cin >> temp;
    if((temp <=0) || (temp >=1)) temp = 0.35;
    e = temp;

	std::cout << "Outer edge of dust disk (AU) (Dole=50 (max))\n";
	std::cin >> temp;
    if((temp >= 50) || (temp <= 0)) temp = 50;
    outer = (10*temp)+0.5; if(outer < 1) outer = 500;
    if(outer > 500) outer = 500;
       
	std::cout << "Inner edge of dust disk (AU) (Dole=0.3)\n";
	std::cin >> temp;
    if((temp >= 50) || (temp <= s.melt())) temp = s.melt();
    inner = (10*temp)+0.5; if(inner < 1) inner = 1;
         
	std::cout << "Enter dust density (Dole=1)\n";
	std::cin >> density;
//    cout << "RAW dust density factor " << density << "\n";
    if(density <= 0.001) density = 1.0;
//    cout << "dust density factor " << density << "\n";

    // populate the disk surface density as e^-5(r^1/3)
    for (i = inner; i <= outer; i++)
    {      // ad-hoc scaling by star mass
        R8 r = (i/10.0)/safepow(s.mass(),0.333);
        R8 u = safepow(r, 0.333);
        dust[i] = 1.5*r*r*exp(-5.0*u);
    }
    for(i=0; i<=500; i++)
    {
        dust[i] *= density;
//        if(i%10) continue;
//        cout << i/10 << " AU, dust mass is " << dust[i] << "\n";
    }

    // mass function is unimodal - smallest value must
    // be at one edge or the other
    least = dust[inner] < dust[outer] ? dust[inner]:
                                        dust[outer];
    least /=2.0; // leeway

	std::cout << "Enter relative gas density (Dole=1)\n";
	std::cin >> gas;
    gasRatio = gas < 0.01 ? 25 : 25*gas;
   
}

R8 DustCloud::nucleus(Random *r)
{
    R8 mass = 0.0;
    int i;
    for (i=inner; i<= outer; i++) mass += dust[i];
//    cout << mass/0.03 << " left\n";
    if(mass < least) return -1.0; // exhausted;
    mass *= r->next();
    for (i=inner; i <= outer && mass > 0; i++)
    {
        mass -= dust[i];
    }
    return i/10.0;
}

// sweep mass in given orbital range
R8 DustCloud::sweep (R8 from, R8 to)
{
    int low = (10*from)+0.5;
    if (low < inner) low = inner;
    int high = (10*to)+0.5;
    if(high > outer) high = outer;
    int i;
    R8 mass = 0.0;
    for(i=low; i<= high; i++)
    {
        mass += dust[i];
        dust[i] = 0;
    }
    if(mass < least) mass = -1;
    return mass;
}

R8 DustCloud::mass()
{
    R8 m = 0.0;
    int i;
    for (i=inner; i<= outer; i++) m += dust[i];
    return m;
}



// a simple planet
class Planet
{          
    R8 totalMass;
    R8 rockyMass;
    R8 semiMajorAxis;
    R8 eccentricity;
    int status;
    DustCloud *cloud;
public:
    // simple constructor
    Planet (DustCloud *c, Random *r);
    Planet();
    // order operation defined on planets
    friend int operator < (Planet p1, Planet p2)
    {
        return p1.semiMajorAxis < p2.semiMajorAxis;
    }
    // overlap operator        
    friend int operator == (Planet p1, Planet p2)
    {   // is there overlap between the orbital bands?
        R8 p1in = p1.semiMajorAxis * (1.0-p1.eccentricity);
        R8 p1out= p1.semiMajorAxis * (1.0+p1.eccentricity);
        R8 p2in = p2.semiMajorAxis * (1.0-p2.eccentricity);
        R8 p2out= p2.semiMajorAxis * (1.0+p2.eccentricity);
        return (p1in >= p2in && p1in <= p2out) ||
               (p1out>= p2in && p1out<= p2out) ||
               (p2in >= p1in && p2in <= p1out) ||
               (p2out>= p1in && p2out<= p1out) ;
    }
    friend int operator != (Planet& p1, Planet& p2){return !(p1==p2);}
    int OK() {return status;} // if created OK
    // collision
    void collide (Planet& p2, Random *r);
    void grow(Sun& s);
    void print(Sun& s, int i, Random *r);
    R8 rock() {return rockyMass;}
    R8 gas() {return totalMass-rockyMass;}
    void clear();
};

Planet::Planet()
{
    totalMass = rockyMass = 0.0;
    semiMajorAxis = -1.0;
    eccentricity = 0.0;
    cloud = (DustCloud*) 0;
    status = 0;
}

    // real constructor
Planet::Planet (DustCloud *c, Random *r)
{   // define where it belongs
    cloud = c;
    // no mass as yet
    totalMass = rockyMass = 0.0;
    // randomly located and w/ random eccentricity
    eccentricity = r->next() * c->eccentricity();
    semiMajorAxis = c->nucleus(r);
    status = semiMajorAxis >= 0;
//        cout << semiMajorAxis << " sma - Planet w/args\n";
}
   

void Planet::collide (Planet& p2, Random *r)
{
//dbg
//        cout << "rock/total/sma/e\n";
//        cout << rockyMass << totalMass << semiMajorAxis << eccentricity << "\n";
//        cout << p2.rockyMass << p2.totalMass << p2.semiMajorAxis << p2.eccentricity << "\n";
//        cout << "------\n";
//end dbg

    // sum angular momenta
    R8 angMom1 = totalMass*
            safesqrt(semiMajorAxis*
            (1.0-eccentricity*eccentricity));
    R8 angMom2 = p2.totalMass*
            safesqrt(p2.semiMajorAxis*
            (1.0-p2.eccentricity*p2.eccentricity));
    R8 h = angMom1 + angMom2;
    // sum masses
    totalMass += p2.totalMass; p2.totalMass = 0.0;
    rockyMass += p2.rockyMass; p2.rockyMass = 0.0;
    // randomly circularise orbit
    if(eccentricity > p2.eccentricity)
                eccentricity = p2.eccentricity;
    eccentricity*= r->next();
    // deduce new orbit from conserved mass, angular momentum
    h /= totalMass;
    semiMajorAxis = (h*h)/
            (1.0-eccentricity*eccentricity);
//dbug
//    cout << semiMajorAxis << " = POST COLLISION SMA\n";
//    cout << h << " = h\n";
//    cout << totalMass << " = mass\n";
//    cout << eccentricity << " = e\n";
//end dbg
        // indicate p2 absorbed
        p2.semiMajorAxis = -1.0;
        p2.status = 0; // destroyed
}

void Planet::grow(Sun& s)
{
    R8 apastron = semiMajorAxis*(1.0+eccentricity);
    R8 periastron = semiMajorAxis*(1.0-eccentricity);
//        cout << semiMajorAxis << " = semiMajorAxis\n";
//        cout << eccentricity << " = eccentricity\n";
    R8 criticalMass = 0.12*safepow(periastron,-0.75)*
                                   safepow(s.flux(), 0.375);
    R8 deltaM = 0;
    do
    {
        totalMass = rockyMass < criticalMass ?
                    rockyMass :
                    criticalMass +
                    (rockyMass-criticalMass)*cloud->gas();
        R8 crossSection = 0.1*safesqrt(safesqrt(
                    totalMass/s.mass()));
        deltaM = cloud->sweep(periastron-crossSection,
                                apastron+crossSection);
        if(deltaM > 0) rockyMass += deltaM;
    } while (deltaM > 0);
    if(rockyMass <= 0) clear();
}

void Planet::print(Sun& s, int i, Random *r)
{  
	std::cout << "#\tOrbit\tTotalMass\tRockyMass\tecc\n";
	std::cout << i << "\t";
	std::cout << semiMajorAxis << "\t";
	std::cout << totalMass/0.03 << "\t";
	std::cout << rockyMass/0.03 << "\t";
	std::cout << eccentricity << "\n";

	std::cout << "\tyear\ttemp(C)\tincl\n\t";
	std::cout << safesqrt(semiMajorAxis/s.mass())*semiMajorAxis << "\t";
	std::cout << 288*safesqrt(safesqrt(s.flux())/semiMajorAxis)-273 << "\t";
	std::cout << 180*(1-safepow(r->next(),(2.0/9.0))) << "\n";

	std::cout << "\tradius(km)\tg(m/s^2)\n\t";
    R8 radius;
    if(totalMass <= rockyMass*1.01)
    {
        R8 nextR = -2;
        radius = safepow(rockyMass/0.03,1.0/3.0);
        for(;;)
        {
                R8 guessMass = radius*safepow(2.0,1.0/3.0);
                nextR = guessMass*safepow(2.0,-radius/3.0);
                if(fabs(nextR-radius) < 0.01) break;
                radius=nextR;
        }
    }
    else if(totalMass < 200)
            radius = 4.3*safepow(totalMass,0.38);  // heuristic gas giant
    else radius = 0.7 * safepow(totalMass,0.6); //heuristic star
    R8 g = 327*totalMass/radius;
	std::cout << 6400.0*radius << "\t";
	std::cout << g << "\n\n";

}

void Planet::clear()
{
    totalMass = rockyMass = 0.0;
    semiMajorAxis = -1.0;
    eccentricity = 0.0;
    cloud = (DustCloud*) 0;
    status = 0;
}

// allocator done this way to work around far vs near pointer
// teething problems with plain "new".  Breaking the class up into
// header and body, and using "operator new" would be more aesthetic
#define MAX 25
class AllocPlanet
{
    int used[MAX];
    Planet x[MAX];
public:
    AllocPlanet();
    Planet *newPlanet(Planet p);
    void deletePlanet(Planet *p);
};

AllocPlanet::AllocPlanet()
{
    int i;
    for(i=0; i<MAX; i++)used[i]=0;
}

Planet *AllocPlanet::newPlanet(Planet p)
{
    int i;
// dbug
//    int sum = 0;
//    for(i=0; i<MAX; i++) sum+= used[i];
//    cout << sum << " planets allocated, and looking for another\n";
//end
    for(i=0; i<MAX; i++)
    {
        if(!used[i])
        {
                used[i] = 1;
                x[i] = p;
                return x+i;
        }
    }
    return 0;
}

void AllocPlanet::deletePlanet(Planet *p)
{
    int i = p-x;
    if(i >=0 && i< MAX) used[i]=0;
    p->clear();
}
 
// sorted list of planets as a solar system
class AllocSSystem;

class SSystem
{
    Planet *p;
    SSystem *next;
    SSystem *previous;
public:
    SSystem ();
    void print(Sun& s, int i, Random *r);
    SSystem* insert(Planet *p1, AllocSSystem& as, SSystem *t);
    // remove dead planets from the system
    void clear(AllocSSystem& as, AllocPlanet& ap);
    void collide(Sun& s, Random *r, AllocSSystem& as, AllocPlanet& ap);
    R8 rock();
    R8 gas();
};

SSystem::SSystem ()
{
    p = (Planet*)0;
    next = previous = (SSystem*)0;
}

void SSystem::print(Sun& s, int i, Random *r)
{
    p->print(s, i, r); i++;
    if(next) next->print(s, i, r);
}

R8 SSystem::rock()
{
    R8 m = p->rock();
    if(next) m+=next->rock();
    return m;
}

R8 SSystem::gas()
{
    R8 m = p->gas();
    if(next) m+=next->gas();
    return m;
}

class AllocSSystem
{
    int used[MAX];
    SSystem x[MAX];
public:
    AllocSSystem();
    SSystem *newSSystem();
    void deleteSSystem(SSystem *p);
};

AllocSSystem::AllocSSystem()
{
    int i;
    for(i=0; i<MAX; i++)
    used[i]=0;
}

SSystem *AllocSSystem::newSSystem()
{
    int i;
    for(i=0; i<MAX; i++)
    {
        if(!used[i])
        {
                used[i] = 1;
                x[i] = SSystem();
                return x+i;
        }
    }
    return 0;
}

void AllocSSystem::deleteSSystem(SSystem *p)
{
    int i = p-x;
    if(i >=0 && i< MAX) used[i]=0;
}

SSystem* SSystem::insert(Planet *p1, AllocSSystem &as, SSystem *t)
{
    SSystem *head = 0;
    if(p == 0) p = p1;
    else
    {   // recurse until we find the first planet outside
        if(*p < *p1)
        {
            if(next) next->insert(p1,as,next);
            else // this is the outermost
            {
                next = as.newSSystem();
                next->previous = t;
                next->p = p1;
            }
        }
        else // just inside this one
        {
            SSystem *n = as.newSSystem();
            n->next = t;
            n->previous = previous;
            if(previous) previous->next = n;
            else head = n;
            previous = n;
            n->p = p1;
        }
    }
    return head;
}

// remove dead planets from the system
void SSystem::clear(AllocSSystem& as, AllocPlanet& ap)
{  
    SSystem *n = next;
    if(!p->OK())
    {
        if(previous) previous->next = next;
        if(next)next->previous = previous;
        ap.deletePlanet(p);
        as.deleteSSystem(this);
    }
    if(n) n->clear(as, ap);
}

void SSystem::collide(Sun& s, Random *r, AllocSSystem& as, AllocPlanet&
ap)
{
    while(next)
    {
        if(!(*(next->p) == *p)) break;
        // orbits cross  
//        cout << "COLLISION!!\n";
        p->collide(*(next->p), r); //smash them
        p->grow(s); // re-accrete this one
        clear(as,ap); // clean up corpse and iterate
    }
    if(next) next->collide(s,r,as,ap); // and continue
}

int main ()
{                    
    Random r;
    char name[120];
	std::cout << "Enter title\n";
	std::cin  >> name;
	std::cout << name << "\n";

    // instantiate sun and dust/gas disk
    Sun s;
    DustCloud d = DustCloud(s);

    // Create a solar system
    AllocPlanet ap;
    AllocSSystem as;
    SSystem *list = as.newSSystem();

    R8 dust = d.mass();
//    cout << d.mass() << " initially\n";

    for (;;)
    {
        Planet *p = ap.newPlanet(Planet(&d, &r));
        if(!p) break;
        if(!p->OK()) break;         // all dust gone
        p->grow(s);                        // accrete
        if(!p->OK())                        // nothing accreted (fencepost?)
        {
            ap.deletePlanet(p);
            continue;
        }
        SSystem *head = list->insert(p,as,list);                   // add to list
        if(head) list = head;
//        cout << d.mass() + list->rock() << " with new planet\n";;
//        cout << list->gas()/list->rock() << " = gas to rock ratio\n";
        list->collide(s, &r, as, ap);    // manage collisions
//        cout << d.mass() + list->rock() << " after collisions\n";;
//        cout << list->gas()/list->rock() << " = gas to rock ratio\n";
    }

//    cout << d.mass() + list->rock() << " after all dust gone\n";;
//    cout << list->gas()/list->rock() << " = gas to rock ratio\n";
    list->print(s, 1, &r);                                // output
    return 0;
}

