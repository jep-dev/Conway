#ifndef MODULAR_HPP
#define MODULAR_HPP

#include "view.hpp"       // -> runnable.hpp, frame.hpp, panel.hpp
using namespace Runnable; // <- Runnable::*
using namespace View;     // <- View::*

#ifndef BUILD
#define BUILD "n/a" /* Default used */
#endif

#ifndef VERSION
#define VERSION 0 /* Default used */
#endif

#endif
