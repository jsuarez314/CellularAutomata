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

#include "CellularAutomata.h"
#include "TApplication.h"
#include "TBenchmark.h"
#include <iostream>
using namespace std;

CellularAutomata::CellularAutomata(const TGWindow *p,UInt_t w,UInt_t h){

  l1 = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY ,2,2,2,2);
  l2 = new TGLayoutHints(kLHintsCenterX | kLHintsCenterY ,4,4,4,4);
    
  TMF1 = new TGMainFrame(p,h,w);
  TMF1->SetWindowName("Cellular Automata");
  TMF1->SetWMSizeHints(w,h,w,h,1,1);

  HF1 = new TGHorizontalFrame(TMF1,2,2);

  // Group Frames Left______________________________________________________
  VFO1 = new TGVerticalFrame(HF1,2,2);

  GF1 = new TGGroupFrame(VFO1,"Parameters",kVerticalFrame);

  GFNode= new TGGroupFrame(GF1,"Cells(Width)",kHorizontalFrame);
  NEPoints = new TGNumberEntry(GFNode,10);
  NEPoints->SetNumStyle(TGNumberFormat::kNESReal);
  NEPoints->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEPoints->SetLimits(TGNumberFormat::kNELLimitMinMax,2,100);
  GFNode->AddFrame(NEPoints);


  //Options__________________________________________________
  GF2 = new TGGroupFrame(VFO1,"Options",kVerticalFrame);
  TGBRun = new TGTextButton(GF2,"&Start",1);
  TGBRun->Connect("Clicked()","CellularAutomata",this,"Control()");

  TGBReset = new TGTextButton(GF2,"&Reset",1);
  TGBReset->Connect("Clicked()","CellularAutomata",this,"Reset()");
  TGBReset->SetEnabled(false);

  TGBExit = new TGTextButton(GF2,"&Exit","gApplication->Terminate(0)");

  GF1->AddFrame(GFNode,new TGLayoutHints(kLHintsNormal,3,3,3,3));

  GF2->AddFrame(TGBRun,l1);
  GF2->AddFrame(TGBReset,l1);
  GF2->AddFrame(TGBExit,l1);

  VFO1->AddFrame(GF1,l2);
  VFO1->AddFrame(GF2,l2);

  // Canvas Right___________________________________________________________
  VFO2 = new TGVerticalFrame(HF1,2,2,2,2);

  TRootEmbeddedCanvas *EC1 = new TRootEmbeddedCanvas("EC1",VFO2,450,450);   
  c1 = EC1->GetCanvas();
  VFO2->AddFrame(EC1,new TGLayoutHints(kLHintsNormal,1,1,1,1));

  HF1->AddFrame(VFO1,new TGLayoutHints(kLHintsNormal,10,10,10,10));
  HF1->AddFrame(VFO2,new TGLayoutHints(kLHintsNormal,10,10,10,10));

  TMF1->AddFrame(HF1);
  
  TMF1->MapSubwindows();
  TMF1->Resize(TMF1->GetDefaultSize());
  TMF1->MapWindow();

  CountState=2;
  time=0;
  i=0;
  j=0;
  Count = new TTimer(0.1);
  Count->Connect("Timeout()","CellularAutomata",this,"Run()");
}

void CellularAutomata::Init(){
  
  Rand = new TRandom3();
  Rand->SetSeed();
  NBox= NEPoints->GetNumber();
  c1->Range(0,0,NBox+1,NBox+1);
  for(Int_t w=0;w<=NBox;w++){
    for(Int_t h=0;h<=NBox;h++){
      tb[w][h]= new TBox(w,h,w+1,h+1);
      aleator1=Rand->Uniform(0,9);
      if(aleator1<=8.5){s[w][h]=1; tb[w][h]->SetFillColor(0);}//Cell Live
      else{s[w][h]=0; tb[w][h]->SetFillColor(1);}//Cell Dead
      tb[w][h]->Draw();
    }
   }

  c1->Update();
}

void CellularAutomata::Control(){
  if(CountState==0){
    Count->TurnOff();
    CountState=1;                                     //Pausa
    TGBRun->SetText("&Cont.");
    TGBReset->SetEnabled(true);
  }
  else if(CountState==2){
    CountState=0;                                     //Inicia 
    TGBRun->SetText("&Pause");
    NEPoints->SetState(false);
    CellularAutomata::Run();
  }
  else if(CountState==1){
    Count->TurnOn();
    CountState=0;                                     //Continua
    NEPoints->SetState(false);
    TGBRun->SetText("&Pause");
    TGBReset->SetEnabled(false);
  }
}

void CellularAutomata::Reset(){
  time=0;
  c1->Clear();
  c1->Update();
  NEPoints->SetState(true);
  TGBRun->SetText("&Start");
  Count->Reset();
}

void CellularAutomata::Run(){
  Count->TurnOn();
  if(time==0){
    cout<<"Run...."<<endl;
    CellularAutomata::Init();
    time++;
  }
  if(i==0){//Límite Izquierdo
    if(j==0){//Esquina Inferior Izquierda
      if(s[0][1]==1 && s[1][1]==1 && s[1][0]==1){
	s[0][0]=1; 
	tb[0][0]->SetFillColor(0);
	tb[0][0]->Draw();
      }
      else{
	s[0][0]=0; 
	tb[0][0]->SetFillColor(1);
	tb[0][0]->Draw();
      }
    }
    if(j==NBox){//Esquina Superior Izquierda
      if(s[0][NBox-1]==1 && s[1][NBox-1]==1 && s[1][NBox]==1){
	s[0][NBox]=1; 
	tb[0][NBox]->SetFillColor(0);
	tb[0][NBox]->Draw();
      }
      else{
	s[0][NBox]=0; 
	tb[0][NBox]->SetFillColor(1);
	tb[0][NBox]->Draw();
      }
    }
    
    if(j>0 && j<NBox){//Borde Izquierdo
      Lives=0;
      if (s[i][j+1]==1) Lives++;
      if (s[i][j-1]==1) Lives++; 
      if (s[i+1][j-1]==1) Lives++;
      if (s[i+1][j]==1) Lives++;
      if (s[i+1][j+1]==1)Lives++;
      if(s[i][j]==0 && Lives==3){
	s[i][j]=1; 
	tb[i][j]->SetFillColor(0);
	tb[i][j]->Draw();
      }
      if(s[i][j]==1 && Lives!=2 && Lives!=3){
	s[i][j]=0; 
	tb[i][j]->SetFillColor(1);
	tb[i][j]->Draw();
      }
    }
  }

  if(i==NBox){//Límite Derecho
    if(j==0){//Esquina Inferior Derecha
      if(s[NBox-1][0]==1 && s[NBox-1][1]==1 && s[NBox][1]==1){
	s[NBox][0]=1; 
	tb[NBox][0]->SetFillColor(0);
	tb[NBox][0]->Draw();
      }
      else{
	s[NBox][0]=0; 
	tb[NBox][0]->SetFillColor(1);
	tb[NBox][0]->Draw();
      }
    }
    if(j==NBox){//Esquina Superior Derecha
      if(s[NBox][NBox-1]==1 && s[NBox-1][NBox-1]==1 && s[NBox-1][NBox]==1){
	s[NBox][NBox]=1; 
	tb[NBox][NBox]->SetFillColor(0);
	tb[NBox][NBox]->Draw();
      }
      else{
	s[NBox][NBox]=0; 
	tb[NBox][NBox]->SetFillColor(1);
	tb[NBox][NBox]->Draw();
      }
    }
    
    if(j<NBox && j>0){//Borde Derecho
      Lives=0;
      if (s[i][j+1]==1) Lives++;
      if (s[i][j-1]==1) Lives++; 
      if (s[i-1][j-1]==1) Lives++;
      if (s[i-1][j]==1) Lives++;
      if (s[i-1][j+1]==1)Lives++;
      if(s[i][j]==0 && Lives==3){
	s[i][j]=1; 
	tb[i][j]->SetFillColor(0);
	tb[i][j]->Draw();
      }
      if(s[i][j]==1 && Lives!=2 && Lives!=3){
	s[i][j]=0; 
	tb[i][j]->SetFillColor(1);
	tb[i][j]->Draw();
      }
    }
  }

  if(i!=0 && j!=0 && i!=NBox && j!=NBox){//Celulas Internas
    Lives=0;
    if(s[i-1][j]==1) Lives++;
    if(s[i+1][j]==1) Lives++;
    if(s[i][j-1]==1) Lives++;
    if(s[i][j+1]==1) Lives++;
    if(s[i-1][j-1]==1) Lives++;
    if(s[i-1][j+1]==1) Lives++;
    if(s[i+1][j-1]==1) Lives++;
    if(s[i+1][j+1]==1) Lives++;
    if(s[i][j]==0 && Lives==3){
      s[i][j]=1; 
      tb[i][j]->SetFillColor(0);
      tb[i][j]->Draw();
    }
    if(s[i][j]==1 && Lives!=2 && Lives!=3){
      s[i][j]=0; 
      tb[i][j]->SetFillColor(1);
      tb[i][j]->Draw();
    }
  }
  
  if(i>0 && i<NBox){//Límites Superior e Inferior
    if(j==0){//Límite Inferior
      Lives=0;
      if(s[i-1][j]==1) Lives++;
      if(s[i-1][j+1]==1) Lives++;
      if(s[i][j+1]==1) Lives++;
      if(s[i+1][j+1]==1) Lives++;
      if(s[i+1][j]==1) Lives++;
      if(s[i][j]==0 && Lives==3){
	s[i][j]=1; 
	tb[i][j]->SetFillColor(0);
	tb[i][j]->Draw();
      }
      if(s[i][j]==1 && Lives!=2 && Lives!=3){
	s[i][j]=0; 
	tb[i][j]->SetFillColor(1);
	tb[i][j]->Draw();
      }
    }
    if(j==NBox){//Límite Superior
      Lives=0;
      if(s[i-1][j]==1) Lives++;
      if(s[i-1][j-1]==1) Lives++;
      if(s[i][j-1]==1) Lives++;
      if(s[i+1][j-1]==1) Lives++;
      if(s[i+1][j]==1) Lives++;
      if(s[i][j]==0 && Lives==3){
	s[i][j]=1; 
	tb[i][j]->SetFillColor(0);
	tb[i][j]->Draw();
      }
      if(s[i][j]==1 && Lives!=2 && Lives!=3){
	s[i][j]=0; 
	tb[i][j]->SetFillColor(1);
	tb[i][j]->Draw();
      }
    }
  }
  i=i+1;
  if(i==NBox+1){
    if(j==NBox){time=time+1; c1->Update(); i=0; j=0;}
    else{i=0; j=j+1;}
  }
}

CellularAutomata::~CellularAutomata(){
  TMF1->Cleanup();
  delete TMF1;
}
