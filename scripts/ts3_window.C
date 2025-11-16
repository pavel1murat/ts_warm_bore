///////////////////////////////////////////////////////////////////////////////
// calculation for 250 um Al window: mu2e-20278 (Dave Pushka)
// underlying documents:
// - Fermilab guidelines document: https://lss.fnal.gov/archive/tm/TM-1380.pdf
//   local: file:./https://lss.fnal.gov/archive/tm/TM-1380.pdf
//   - there is a typo in the formula for circular rigid windows:
//     eq. 5.1b there should read qa^4/Et^4, not qa^4/Et^2 (it is dimensionless)
// from George:
// > Hi Pasha:
// >     The following are values that Dave is using for grade 5 titanium in this context:
// > Young's modulus   1.64x10^7 psi   (instead of 1.65x10^7 psi)
// > Ultimate stress   1.3x10^5  psi   (instead of 1.7x10^5 psi)
// > Yield stress      1.2x10^5 psi    (instead of 1.6x10^5 psi)
//
// - 2002 Roarks formulas for stress and strain 7th edition, formulas 11.11-1 and 11.11-2
//
// .L ts_warm_bore/scripts/ts3_window.C++
//  ts3_window()
// # ---------------------------checking 250 um Al window for 1.2 psi :
// x =    2.930605e+01  s =    1.181925e+04 Fu*0.5 =    1.200000e+04 Fy*0.9 =    1.980000e+04
// # ---------------------------checking 250 um Ti window at 1.2 psi:
// x =    2.479281e+01  s =    1.419771e+04 Fu*0.5 =    8.500000e+04 Fy*0.9 =    1.440000e+05
// # ---------------------------checking 300 um Ti window at 1 atm:
// x =    5.134870e+01  s =    8.271711e+04 Fu*0.5 =    8.500000e+04 Fy*0.9 =    1.440000e+05
//////////////////////////////////////////////////////////////////////////////

// | D, inches                |   17.716535 |            |
// | pressure(psi)            |        1.20 |            |
// | pressure (torr)          |   62.218547 |            |
// | R, mm                    |         225 |            |
// | R, inches                |   8.8582675 |            |
// | Young modulus, E(psi)    |         1e7 |            |
// | window thickness, in     |        0.01 |            |
// | window thickness, mm     |       0.254 |            |
// | poisson ratio,nu         |        0.33 |       0.33 |
// | K1 = 5.33/(1-nu^2)       |   5.9813713 |            |
// | K2 = 2.6/(1-nu^2)        |   2.9177421 |            |
// | K3 = 2/(1-nu)            |   2.9850746 |            |
// | Yield stress    Fy (psi) |       22000 |     160000 |
// | Ultimate stress Fu (psi) |       24000 |     170000 |

#include "TF1.h"
//-----------------------------------------------------------------------------
// constant
//-----------------------------------------------------------------------------
double fun1(double* X, double *P) {
  return P[0];
}

//-----------------------------------------------------------------------------
// P[0]: K1, P[1]: K2
//-----------------------------------------------------------------------------
double fun2(double* X, double *P) {
  double x = X[0];
  return P[0]*x+P[1]*x*x*x;
}

//-----------------------------------------------------------------------------
struct Material_t {
  TString Name;
  double  Fu;    // ultimate tensile strength, psi
  double  Fy;    // yield stress , psi
  double  E;     // Young modulus , psi
  double  nu;    
};

struct TS3Window_t {
  double      D;           // diameter, in
  double      t;           // thickness, in
  Material_t* Material;
};

//-----------------------------------------------------------------------------
// solves equation: k1*x + k2+x^3 = a
// epsilon - tolerance
//-----------------------------------------------------------------------------
double solve_x(double a, double k1, double k2, double epsilon) {

  //  printf(">>> solve_x: START : a, k1, k2 = %15.7f %15.7f %15.7f\n",a,k1,k2);

  double dfdx, dx, x1, f1, x, f, x2, f2;

  x = 0;
  f = k1*x+k2*x*x*x;

  int niter = 1;

  x2  = 0;
  f2 = 0;
  
  while (f2 < a) {
    x2 += 1;
    f2 = k1*x2+k2*x2*x2*x2;
  }

  //  printf ("x2 = %15.5e\n",x2);

  x1 = x2-1;
  f1 = k1*x1 + k2*x1*x1*x1;
  
  while (niter < 10) {

    x    = x1+(x2-x1)*(a-f1)/(f2-f1);
    f    = k1*x+k2*x*x*x;               // printf ("f1   = %15.5e\n",x1  );

    if (fabs(f1-a) < epsilon) break;

    if (f > a) {
      x2  = x;
      f2  = f;
    }
    else {
      x1 = x;
      f1 = f;
    }
    
    niter += 1;
  }

  //  printf(">>> solve_x: END : x = %15.7f  niter = %5i\n",x,niter);

  return x;
}

//-----------------------------------------------------------------------------
// pressure : in PSI
//-----------------------------------------------------------------------------
void check_win(TS3Window_t& Win, double Pressure) {

  double D    = Win.D;         // TS3 window diameter, inches
  double R    = D/2.;
  double t    = Win.t;
  double y    = R/t;

  double E    = Win.Material->E;
  double nu   = Win.Material->nu ; 

  double k1    = 5.33/(1-nu*nu);
  double k2    = 2.6 /(1-nu*nu);
  double k3    = 2.  /(1-nu);
  double k4    = 0.976;

  double  y4   = y*y*y*y;

  double a     = (Pressure/E)*y4;

// printf ("Pressure = %15.6e   y  = %15.6e a  = %15.6e\n",Win.P, y, a);
// printf ("k1       = %15.6e   k2 = %15.6e k3 = %15.6e k4 = %15.6e \n",k1,k2,k3,k4);
//-----------------------------------------------------------------------------
// x = deflection/w.thickness
//-----------------------------------------------------------------------------
  double epsilon = 1.e-8;
  double x       = solve_x(a,k1,k2,epsilon);
//-----------------------------------------------------------------------------
// also determine deflection graphically
//-----------------------------------------------------------------------------
  double xmax = 100;
  
  TF1* f1 = new TF1("f1",fun1,0,100,1);
  f1->SetNpx(10000);
  f1->SetParameter(0,a);

  f1->Draw();

  TF1* f2 = new TF1("f2",fun2,0,100,2);
  f2->SetNpx(10000);

  f2->SetParameter(0,k1);
  f2->SetParameter(1,k2);

  f1->Draw();

  f2->SetLineColor(kBlue+2);
  f2->Draw("same");
//-----------------------------------------------------------------------------
// calculate stress:
//-----------------------------------------------------------------------------
  double s = E/(y*y)*(k3*x+k4*x*x);

  printf("x = %15.6e  stress = %15.6e Fu*0.5 = %15.6e Fy*0.9 = %15.6e\n",
	 x,s,Win.Material->Fu*0.5,Win.Material->Fy*0.9);
}

  // double g     = 981.;         // cm/sec^2 free fall acceleration
  // double torr  = 13.59*0.1*g;
  // double psi   = 453.59237/(2.54*2.54)*g;

//-----------------------------------------------------------------------------
//              name     Fu       Fy       E    nu
//-----------------------------------------------------------------------------
Material_t mAl   { "Al",  24000.,  22000., 1.0e7 , 0.33};  // Al
Material_t mTi   { "Ti", 170000., 160000., 1.65e7, 0.33};  // Ti grade 5
Material_t mTi_DP{ "Ti", 130000., 120000., 1.64e7, 0.33};  // Ti grade 5, parameters used by Dave Pushka's (according to George)

//-----------------------------------------------------------------------------
void ts3_window() {

  double  p;
  
  printf("# -- 250 um Al window at 1.2 psi: ");
  //              45cm  254um 
  TS3Window_t w1{ 17.7, 0.01, &mAl}; p = 1.2;  
  check_win(w1,p);
  
  printf("# --  50 um Ti window at 1.2 psi: ");
  //              45cm     ~50um 
  TS3Window_t w11{ 17.7, 0.002 , &mTi}; p = 1.2;
  check_win(w11,p);

  printf("# -- 100 um Ti window at 1.2 psi: ");
  //              45cm     4mil ~100um 
  TS3Window_t w12{ 17.7, 0.004 , &mTi}; p = 1.2;
  check_win(w12,p);

  printf("# -- 150 um Ti window at 1.2 psi: ");
  //              45cm  ~150um 
  TS3Window_t w3{ 17.7, 0.006 , &mTi}; p = 1.2;
  check_win(w3,p);

  printf("# -- 150 um Ti window at 12  psi: ");
  //              45cm  ~150um 
  TS3Window_t w31{ 17.7, 0.006 , &mTi}; p = 12.;
  check_win(w31,p);

  printf("# -- 200 um Ti window at 1.0 atm: ");
  //              45cm  ~150um 
  TS3Window_t w32{ 17.7, 0.008 , &mTi}; p = 14.7;
  check_win(w32,p);

  printf("# -- 250 um Ti window at 1.2 psi: ");
  //              45cm  254um 
  TS3Window_t w2{ 17.7, 0.01 , &mTi}; p = 1.2;
  check_win(w2,p);

  printf("# -- 250 um Ti window at 1.0 atm: ");
  //              45cm  254um 
  TS3Window_t w21{ 17.7, 0.01 , &mTi}; p = 14.7;
  check_win(w21,p);

  printf("# -- 300 um Ti window at 1.5 atm: ");
    //              45cm  ~300 um
  TS3Window_t w4{ 17.7, 0.012, &mTi};  p = 14.7*1.5 ; 
  check_win(w4,p);
}
