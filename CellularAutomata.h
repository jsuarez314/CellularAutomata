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

#include <RQ_OBJECT.h>
#include <TGFrame.h>
#include <TFile.h>
#include <TTimer.h>
#include <TGTab.h>
#include <TGStatusBar.h>
#include <TBox.h>
#include <TAxis.h>
#include <TRandom3.h>
#include <TRootEmbeddedCanvas.h>
#include <TCanvas.h>
#include <TGNumberEntry.h>
#include <TGraph.h>
#include <TMath.h>
#include <TGClient.h>
#include <TDialogCanvas.h>
#include <TGFileDialog.h>

class CellularAutomata{

  RQ_OBJECT("CellularAutomata");

 public:
  
  CellularAutomata(const TGWindow *p,UInt_t w,UInt_t h);
  void Control();
  void Run();
  void Reset();
  ~CellularAutomata();
  
 private:

  TGLayoutHints *l1, *l2;
  TGMainFrame *TMF1;
  TRootEmbeddedCanvas *EC1;
  TCanvas *c1;  
  TGVerticalFrame  *VFO1, *VFO2;
  TGHorizontalFrame  *HF1;
  TGNumberEntry *NEPoints;
  TGTextButton *TGBRun,*TGBReset;
  TGTextButton *TGBExit;
  TGGroupFrame  *GF1, *GF2, *GF3;                          //Group Parameters, Options and Results.
  TGGroupFrame *GFNode;
  
  TTimer *Count; 
  TFile *f1;
  TRandom3 *Rand;

  Int_t CountState;    // 0=Run     1=Pause     2=Stop
  Int_t time;
  Double_t NRandom;
  Int_t NBox;                                              //Number Box
  Int_t Cells;
  Int_t Lives;
  Int_t i,j;
  Int_t s[100][100];

  Double_t aleator1, aleator2;
  TBox *tb[100][100]; 

  void Init();

  ClassDef(CellularAutomata,0);
};
