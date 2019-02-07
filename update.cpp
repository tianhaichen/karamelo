#include <iostream>
#include "update.h"
#include "scheme.h"
#include "method.h"
#include "style_scheme.h"
#include "style_method.h"
#include <vector>

using namespace std;

Update::Update(MPM *mpm) : Pointers(mpm)
{
  cout << "In Update::Update()" << endl;

  ntimestep = 0; // set the current timestep to 0
  dt = 1e-16;

  // Default scheme is MUSL:
  vector<string> scheme_args;
  scheme_args.push_back("musl");
  create_scheme(scheme_args);
  
  vector<string> method_args;
  method_args.push_back("tlmpm");
  create_method(method_args);
}

Update::~Update()
{
}

void Update::create_scheme(vector<string> args){
  if (args.size() < 1) {
    cout << "Illegal run_scheme command: not enough arguments" << endl;
    exit(1);
  }

  new_scheme(args);

  scheme_style = args[0];
}

void Update::new_scheme(vector<string> args){

  string style = args[0];

  if (0) return;

#define SCHEME_CLASS
#define SchemeStyle(key,Class) \
  else if (style.compare(#key) == 0) scheme = new Class(mpm,args);
#include "style_scheme.h"
#undef SchemeStyle
#undef SCHEME_CLASS

  else {
    cout << "Illegal scheme style" << endl;
    exit(1);
  }
}

void Update::create_method(vector<string> args){
  if (args.size() < 1) {
    cout << "Illegal run_method command: not enough arguments" << endl;
    exit(1);
  }

  new_method(args);

  method_style = args[0];
}

void Update::new_method(vector<string> args){

  string style = args[0];

  if (0) return;

#define METHOD_CLASS
#define MethodStyle(key,Class) \
  else if (style.compare(#key) == 0) method = new Class(mpm,args);
#include "style_method.h"
#undef MethodStyle
#undef METHOD_CLASS

  else {
    cout << "Illegal method style" << endl;
    exit(1);
  }
}