#include <iostream>
#include "eos_shock.h"
#include "input.h"
#include "domain.h"
#include "mpm_math.h"
#include "math_special.h"
#include <Eigen/Eigen>
#include "var.h"

using namespace std;
using namespace Eigen;
using namespace MPM_Math;
using namespace MathSpecial;


EOSShock::EOSShock(MPM *mpm, vector<string> args) : EOS(mpm, args)
{
  cout << "Initiate EOSShock" << endl;

  if (args.size()<8) {
    cout << "Error: region command not enough arguments" << endl;
    exit(1);
  }
  //options(&args, args.begin()+3);
  rho0_ = input->parsev(args[2]);
  cout << "Set rho0 to " << rho0_ << endl;

  K_ = input->parsev(args[3]);
  cout << "Set K to " << K_ << endl;

  c0 = input->parsev(args[4]);
  cout << "Set c0 to " << c0 << endl;

  e0 = input->parsev(args[5]);
  cout << "Set e0 to " << e0 << endl;

  S = input->parsev(args[6]);
  cout << "Set S to " << S << endl;

  Gamma = input->parsev(args[7]);
  cout << "Set gamma to " << Gamma << endl;
}


EOSShock::~EOSShock()
{

}

double EOSShock::rho0(){
  return rho0_;
}

double EOSShock::K(){
  return K_;
}

double EOSShock::compute_pressure(const double J, const double rho, const double e){
  double mu = rho / rho0_ - 1.0;
  double pH = rho0_ * square(c0) * mu * (1.0 + mu) / square(1.0 - (S - 1.0) * mu);
  return (pH + rho * Gamma * (e - e0));
}

