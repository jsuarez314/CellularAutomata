///////////////////////////////////////////////////////////////////////////
//                                                                       //
// NOTICE OF COPYRIGHT                                                   //
//                                                                       //
//                Copyright (C) 2013   John Suárez                       //
//                https://github.com/fnoj/CellularAutomata               //
//                                                                       //
// This program is free software; you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation; either version 2 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details:                          //
//                                                                       //
//          http://www.gnu.org/copyleft/gpl.html                         //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#ifndef __CINT__

#ifndef ROOT_TApplication
#include "TApplication.h"
#endif
#include "CellularAutomata.h"
#endif

#ifdef __CINT__
#include "CellularAutomata.cxx"
#endif

int Application(){

  CellularAutomata *App = new CellularAutomata(gClient->GetRoot(),650,500);

  return 0;

}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication CellularAutomataApp("CellularAutomataApp", &argc, argv);
  int retVal = Application();
  CellularAutomataApp.Run();
  return retVal;
}
#endif
