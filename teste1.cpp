#include <iostream>
#include <string>
#include "porta.h"

using namespace std;

int main(void)
{
  // Criacao de portas como objeto estaticos (nao polimorficos)

  // Porta NOT
  PortaNOT P_NT;
  PortaNOT P_NT1(1);   // Deve gerar erro de compilacao: precisa comentar

  // Porta AND
  PortaAND P_AN;       // Deve gerar erro de compilacao: precisa comentar
  PortaAND P_AN1(1);
  PortaAND P_AN2(2), P_AN3(3);

  // Porta NAND
  PortaNAND P_NA;      // Deve gerar erro de compilacao: precisa comentar
  PortaNAND P_NA1(1);
  PortaNAND P_NA2(2), P_NA3(3);

  // Porta OR
  PortaOR P_OR;        // Deve gerar erro de compilacao: precisa comentar
  PortaOR P_OR1(1);
  PortaOR P_OR2(2), P_OR3(3);

  // Porta NOR
  PortaNOR P_NO;       // Deve gerar erro de compilacao: precisa comentar
  PortaNOR P_NO1(1);
  PortaNOR P_NO2(2), P_NO3(3);

  // Porta XOR
  PortaXOR P_XO;       // Deve gerar erro de compilacao: precisa comentar
  PortaXOR P_XO1(1);
  PortaXOR P_XO2(2), P_XO3(3);

  // Porta NXOR
  PortaNXOR P_XO;      // Deve gerar erro de compilacao: precisa comentar
  PortaNXOR P_NX1(1);
  PortaNXOR P_NX2(2), P_NX3(3);

  // Teste do numero de entradas das portas
  if (P_NT.getNumInputs() != 1) cerr << "Erro na criacao da porta NOT\n";
  if (P_AN1.getNumInputs() != 0) cerr << "Erro na criacao da porta AND de 1/0 entrada\n";
  if (P_AN2.getNumInputs() != 2) cerr << "Erro na criacao da porta AND de 2 entradas\n";
  if (P_AN3.getNumInputs() != 3) cerr << "Erro na criacao da porta AND de 3 entradas\n";
  if (P_NA1.getNumInputs() != 0) cerr << "Erro na criacao da porta NAND de 1/0 entrada\n";
  if (P_NA2.getNumInputs() != 2) cerr << "Erro na criacao da porta NAND de 2 entradas\n";
  if (P_NA3.getNumInputs() != 3) cerr << "Erro na criacao da porta NAND de 3 entradas\n";
  if (P_OR1.getNumInputs() != 0) cerr << "Erro na criacao da porta OR de 1/0 entrada\n";
  if (P_OR2.getNumInputs() != 2) cerr << "Erro na criacao da porta OR de 2 entradas\n";
  if (P_OR3.getNumInputs() != 3) cerr << "Erro na criacao da porta OR de 3 entradas\n";
  if (P_NO1.getNumInputs() != 0) cerr << "Erro na criacao da porta NOR de 1/0 entrada\n";
  if (P_NO2.getNumInputs() != 2) cerr << "Erro na criacao da porta NOR de 2 entradas\n";
  if (P_NO3.getNumInputs() != 3) cerr << "Erro na criacao da porta NOR de 3 entradas\n";
  if (P_XO1.getNumInputs() != 0) cerr << "Erro na criacao da porta XOR de 1/0 entrada\n";
  if (P_XO2.getNumInputs() != 2) cerr << "Erro na criacao da porta XOR de 2 entradas\n";
  if (P_XO3.getNumInputs() != 3) cerr << "Erro na criacao da porta XOR de 3 entradas\n";
  if (P_NX1.getNumInputs() != 0) cerr << "Erro na criacao da porta NXOR de 1/0 entrada\n";
  if (P_NX2.getNumInputs() != 2) cerr << "Erro na criacao da porta NXOR de 2 entradas\n";
  if (P_NX3.getNumInputs() != 3) cerr << "Erro na criacao da porta NXOR de 3 entradas\n";

  // Vetores de entradas das portas
  vector<bool3S> in0;    // 0 entradas
  vector<bool3S> in1(1); // 1 entrada
  vector<bool3S> in2(2); // 2 entradas
  vector<bool3S> in3(3); // 3 entradas

  ////////////////////////////////////////////////////
  // Teste da compatibilidade do vetor de entrada com
  // o numero de entradas da porta
  ////////////////////////////////////////////////////

  // Teste da porta NOT
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NOT\n";
  if (P_NT.simular(in0)) cerr << "Erro na simulacao de P_NT com 0 entradas\n";
  if (!P_NT.simular(in1)) cerr << "Erro na simulacao de P_NT com 1 entrada\n";
  if (P_NT.simular(in2)) cerr << "Erro na simulacao de P_NT com 2 entradas\n";
  if (P_NT.simular(in3)) cerr << "Erro na simulacao de P_NT com 3 entradas\n";

  // Teste da porta AND1
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS AND1\n";
  if (P_AN1.simular(in0)) cerr << "Erro na simulacao de P_AN1 com 0 entradas\n";
  if (P_AN1.simular(in1)) cerr << "Erro na simulacao de P_AN1 com 1 entrada\n";
  if (P_AN1.simular(in2)) cerr << "Erro na simulacao de P_AN1 com 2 entradas\n";
  if (P_AN1.simular(in3)) cerr << "Erro na simulacao de P_AN1 com 3 entradas\n";

  // Teste da porta AND2
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS AND2\n";
  if (P_AN2.simular(in0)) cerr << "Erro na simulacao de P_AN2 com 0 entradas\n";
  if (P_AN2.simular(in1)) cerr << "Erro na simulacao de P_AN2 com 1 entrada\n";
  if (!P_AN2.simular(in2)) cerr << "Erro na simulacao de P_AN2 com 2 entradas\n";
  if (P_AN2.simular(in3)) cerr << "Erro na simulacao de P_AN2 com 3 entradas\n";

  // Teste da porta AND3
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS AND3\n";
  if (P_AN3.simular(in0)) cerr << "Erro na simulacao de P_AN3 com 0 entradas\n";
  if (P_AN3.simular(in1)) cerr << "Erro na simulacao de P_AN3 com 1 entrada\n";
  if (P_AN3.simular(in2)) cerr << "Erro na simulacao de P_AN3 com 2 entradas\n";
  if (!P_AN3.simular(in3)) cerr << "Erro na simulacao de P_AN3 com 3 entradas\n";

  // Teste da porta NAND1
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NAND1\n";
  if (P_NA1.simular(in0)) cerr << "Erro na simulacao de P_NA1 com 0 entradas\n";
  if (P_NA1.simular(in1)) cerr << "Erro na simulacao de P_NA1 com 1 entrada\n";
  if (P_NA1.simular(in2)) cerr << "Erro na simulacao de P_NA1 com 2 entradas\n";
  if (P_NA1.simular(in3)) cerr << "Erro na simulacao de P_NA1 com 3 entradas\n";

  // Teste da porta NAND2
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NAND2\n";
  if (P_NA2.simular(in0)) cerr << "Erro na simulacao de P_NA2 com 0 entradas\n";
  if (P_NA2.simular(in1)) cerr << "Erro na simulacao de P_NA2 com 1 entrada\n";
  if (!P_NA2.simular(in2)) cerr << "Erro na simulacao de P_NA2 com 2 entradas\n";
  if (P_NA2.simular(in3)) cerr << "Erro na simulacao de P_NA2 com 3 entradas\n";

  // Teste da porta NAND3
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NAND3\n";
  if (P_NA3.simular(in0)) cerr << "Erro na simulacao de P_NA3 com 0 entradas\n";
  if (P_NA3.simular(in1)) cerr << "Erro na simulacao de P_NA3 com 1 entrada\n";
  if (P_NA3.simular(in2)) cerr << "Erro na simulacao de P_NA3 com 2 entradas\n";
  if (!P_NA3.simular(in3)) cerr << "Erro na simulacao de P_NA3 com 3 entradas\n";

  // Teste da porta OR1
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS OR1\n";
  if (P_OR1.simular(in0)) cerr << "Erro na simulacao de P_OR1 com 0 entradas\n";
  if (P_OR1.simular(in1)) cerr << "Erro na simulacao de P_OR1 com 1 entrada\n";
  if (P_OR1.simular(in2)) cerr << "Erro na simulacao de P_OR1 com 2 entradas\n";
  if (P_OR1.simular(in3)) cerr << "Erro na simulacao de P_OR1 com 3 entradas\n";

  // Teste da porta OR2
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS OR2\n";
  if (P_OR2.simular(in0)) cerr << "Erro na simulacao de P_OR2 com 0 entradas\n";
  if (P_OR2.simular(in1)) cerr << "Erro na simulacao de P_OR2 com 1 entrada\n";
  if (!P_OR2.simular(in2)) cerr << "Erro na simulacao de P_OR2 com 2 entradas\n";
  if (P_OR2.simular(in3)) cerr << "Erro na simulacao de P_OR2 com 3 entradas\n";

  // Teste da porta OR3
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS OR3\n";
  if (P_OR3.simular(in0)) cerr << "Erro na simulacao de P_OR3 com 0 entradas\n";
  if (P_OR3.simular(in1)) cerr << "Erro na simulacao de P_OR3 com 1 entrada\n";
  if (P_OR3.simular(in2)) cerr << "Erro na simulacao de P_OR3 com 2 entradas\n";
  if (!P_OR3.simular(in3)) cerr << "Erro na simulacao de P_OR3 com 3 entradas\n";

  // Teste da porta NOR1
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NOR1\n";
  if (P_NO1.simular(in0)) cerr << "Erro na simulacao de P_NO1 com 0 entradas\n";
  if (P_NO1.simular(in1)) cerr << "Erro na simulacao de P_NO1 com 1 entrada\n";
  if (P_NO1.simular(in2)) cerr << "Erro na simulacao de P_NO1 com 2 entradas\n";
  if (P_NO1.simular(in3)) cerr << "Erro na simulacao de P_NO1 com 3 entradas\n";

  // Teste da porta NOR2
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NOR2\n";
  if (P_NO2.simular(in0)) cerr << "Erro na simulacao de P_NO2 com 0 entradas\n";
  if (P_NO2.simular(in1)) cerr << "Erro na simulacao de P_NO2 com 1 entrada\n";
  if (!P_NO2.simular(in2)) cerr << "Erro na simulacao de P_NO2 com 2 entradas\n";
  if (P_NO2.simular(in3)) cerr << "Erro na simulacao de P_NO2 com 3 entradas\n";

  // Teste da porta NOR3
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NOR3\n";
  if (P_NO3.simular(in0)) cerr << "Erro na simulacao de P_NO3 com 0 entradas\n";
  if (P_NO3.simular(in1)) cerr << "Erro na simulacao de P_NO3 com 1 entrada\n";
  if (P_NO3.simular(in2)) cerr << "Erro na simulacao de P_NO3 com 2 entradas\n";
  if (!P_NO3.simular(in3)) cerr << "Erro na simulacao de P_NO3 com 3 entradas\n";

  // Teste da porta XOR1
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS XOR1\n";
  if (P_XO1.simular(in0)) cerr << "Erro na simulacao de P_XO1 com 0 entradas\n";
  if (P_XO1.simular(in1)) cerr << "Erro na simulacao de P_XO1 com 1 entrada\n";
  if (P_XO1.simular(in2)) cerr << "Erro na simulacao de P_XO1 com 2 entradas\n";
  if (P_XO1.simular(in3)) cerr << "Erro na simulacao de P_XO1 com 3 entradas\n";

  // Teste da porta XOR2
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS XOR2\n";
  if (P_XO2.simular(in0)) cerr << "Erro na simulacao de P_XO2 com 0 entradas\n";
  if (P_XO2.simular(in1)) cerr << "Erro na simulacao de P_XO2 com 1 entrada\n";
  if (!P_XO2.simular(in2)) cerr << "Erro na simulacao de P_XO2 com 2 entradas\n";
  if (P_XO2.simular(in3)) cerr << "Erro na simulacao de P_XO2 com 3 entradas\n";

  // Teste da porta XOR3
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS XOR3\n";
  if (P_XO3.simular(in0)) cerr << "Erro na simulacao de P_XO3 com 0 entradas\n";
  if (P_XO3.simular(in1)) cerr << "Erro na simulacao de P_XO3 com 1 entrada\n";
  if (P_XO3.simular(in2)) cerr << "Erro na simulacao de P_XO3 com 2 entradas\n";
  if (!P_XO3.simular(in3)) cerr << "Erro na simulacao de P_XO3 com 3 entradas\n";

  // Teste da porta NXOR1
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NXOR1\n";
  if (P_NX1.simular(in0)) cerr << "Erro na simulacao de P_NX1 com 0 entradas\n";
  if (P_NX1.simular(in1)) cerr << "Erro na simulacao de P_NX1 com 1 entrada\n";
  if (P_NX1.simular(in2)) cerr << "Erro na simulacao de P_NX1 com 2 entradas\n";
  if (P_NX1.simular(in3)) cerr << "Erro na simulacao de P_NX1 com 3 entradas\n";

  // Teste da porta NXOR2
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NXOR2\n";
  if (P_NX2.simular(in0)) cerr << "Erro na simulacao de P_NX2 com 0 entradas\n";
  if (P_NX2.simular(in1)) cerr << "Erro na simulacao de P_NX2 com 1 entrada\n";
  if (!P_NX2.simular(in2)) cerr << "Erro na simulacao de P_NX2 com 2 entradas\n";
  if (P_NX2.simular(in3)) cerr << "Erro na simulacao de P_NX2 com 3 entradas\n";

  // Teste da porta NXOR3
  cout << "\nCOMPATIBILIDADE DAS ENTRADAS NXOR3\n";
  if (P_NX3.simular(in0)) cerr << "Erro na simulacao de P_NX3 com 0 entradas\n";
  if (P_NX3.simular(in1)) cerr << "Erro na simulacao de P_NX3 com 1 entrada\n";
  if (P_NX3.simular(in2)) cerr << "Erro na simulacao de P_NX3 com 2 entradas\n";
  if (!P_NX3.simular(in3)) cerr << "Erro na simulacao de P_NX3 com 3 entradas\n";

  ////////////////////////////////////////////////////
  // Teste da simulacao
  ////////////////////////////////////////////////////

  int i,j,k;

  // Simulacao da porta de 1 entrada
  cout << "\nSIMULACAO DE PORTAS COM 1 ENTRADA\n";
  in1.at(0) = bool3S::UNDEF;
  for (i=0; i<3; ++i)
  {
    P_NT.simular(in1);
    if ( P_NT.getOutput() != ~in1.at(0) )
      cerr << "Erro na simulacao da NOT\n";
    ++in1.at(0);
  }

  // Simulacao das portas de 2 entradas
  cout << "\nSIMULACAO DE PORTAS COM 2 ENTRADAS\n";
  in2.at(0) = bool3S::UNDEF;
  in2.at(1) = bool3S::UNDEF;
  for (i=0; i<3; ++i)
  {
    for (j=0; j<3; ++j)
    {
      P_AN2.simular(in2);
      if ( P_AN2.getOutput() != (in2.at(0) & in2.at(1)) )
        cerr << "Erro na simulacao da AND2\n";
      P_NA2.simular(in2);
      if ( P_NA2.getOutput() != ~(in2.at(0) & in2.at(1)) )
        cerr << "Erro na simulacao da NAND2\n";
      P_OR2.simular(in2);
      if ( P_OR2.getOutput() != (in2.at(0) | in2.at(1)) )
        cerr << "Erro na simulacao da OR2\n";
      P_NO2.simular(in2);
      if ( P_NO2.getOutput() != ~(in2.at(0) | in2.at(1)) )
        cerr << "Erro na simulacao da NOR2\n";
      P_XO2.simular(in2);
      if ( P_XO2.getOutput() != (in2.at(0) ^ in2.at(1)) )
        cerr << "Erro na simulacao da XOR2\n";
      P_NX2.simular(in2);
      if ( P_NX2.getOutput() != ~(in2.at(0) ^ in2.at(1)) )
        cerr << "Erro na simulacao da NXOR2\n";
      ++in2.at(1);
    }
    ++in2.at(0);
  }

  // Simulacao das portas de 3 entradas
  cout << "\nSIMULACAO DE PORTAS COM 3 ENTRADAS\n";
  in3.at(0) = bool3S::UNDEF;
  in3.at(1) = bool3S::UNDEF;
  in3.at(2) = bool3S::UNDEF;
  for (i=0; i<3; ++i)
  {
    for (j=0; j<3; ++j)
    {
      for (k=0; k<3; ++k)
      {
        P_AN3.simular(in3);
        if ( P_AN3.getOutput() != (in3.at(0) & in3.at(1) & in3.at(2)) )
          cerr << "Erro na simulacao da AND3\n";
        P_NA3.simular(in3);
        if ( P_NA3.getOutput() != ~(in3.at(0) & in3.at(1) & in3.at(2)) )
          cerr << "Erro na simulacao da NAND3\n";
        P_OR3.simular(in3);
        if ( P_OR3.getOutput() != (in3.at(0) | in3.at(1) | in3.at(2)) )
          cerr << "Erro na simulacao da OR3\n";
        P_NO3.simular(in3);
        if ( P_NO3.getOutput() != ~(in3.at(0) | in3.at(1) | in3.at(2)) )
          cerr << "Erro na simulacao da NOR3\n";
        P_XO3.simular(in3);
        if ( P_XO3.getOutput() != (in3.at(0) ^ in3.at(1) ^ in3.at(2)) )
          cerr << "Erro na simulacao da XOR3\n";
        P_NX3.simular(in3);
        if ( P_NX3.getOutput() != ~(in3.at(0) ^ in3.at(1) ^ in3.at(2)) )
          cerr << "Erro na simulacao da NXOR3\n";
        ++in3.at(2);
      }
      ++in3.at(1);
    }
    ++in3.at(0);
  }

  ////////////////////////////////////////////////////
  // Teste do comportamento polimorfico
  ////////////////////////////////////////////////////

  vector<ptr_Porta> P(7); // Os 7 tipos de portas

  // Aloca a porta de 1 entrada
  P.at(0) = new PortaNOT;

  // Aloca as portas de 2 entradas
  P.at(1) = new PortaAND(2);
  P.at(2) = new PortaNAND(2);
  P.at(3) = new PortaOR(2);
  P.at(4) = new PortaNOR(2);
  P.at(5) = new PortaXOR(2);
  P.at(6) = new PortaNXOR(2);

  // Impressao dos nomes
  cout << "\nTIPOS DE PORTAS:\n";
  for (i=0; i<7; ++i)
  {
    cout << "Porta " << i << ": " << P.at(i)->getName() << endl;
  }

  // Simulacao da porta polimorfica de 1 entrada
  cout << "\nSIMULACAO DE PORTAS DINAMICAS COM 1 ENTRADA\n";
  in1.at(0) = bool3S::UNDEF;
  for (i=0; i<3; ++i)
  {
    P_NT.simular(in1);
    P.at(0)->simular(in1);
    if ( P_NT.getOutput() != P.at(0)->getOutput() )
      cerr << "Erro na simulacao da NOT polimorfica\n";
    ++in1.at(0);
  }

  // Simulacao das portas polimorficas de 2 entradas
  cout << "\nSIMULACAO DE PORTAS DINAMICAS COM 2 ENTRADAS\n";
  in2.at(0) = bool3S::UNDEF;
  in2.at(1) = bool3S::UNDEF;
  for (i=0; i<3; ++i)
  {
    for (j=0; j<3; ++j)
    {
      P_AN2.simular(in2);
      P.at(1)->simular(in2);
      if ( P_AN2.getOutput() != P.at(1)->getOutput() )
        cerr << "Erro na simulacao da AND2 polimorfica\n";
      P_NA2.simular(in2);
      P.at(2)->simular(in2);
      if ( P_NA2.getOutput() != P.at(2)->getOutput() )
        cerr << "Erro na simulacao da NAND2 polimorfica\n";
      P_OR2.simular(in2);
      P.at(3)->simular(in2);
      if ( P_OR2.getOutput() != P.at(3)->getOutput() )
        cerr << "Erro na simulacao da OR2 polimorfica\n";
      P_NO2.simular(in2);
      P.at(4)->simular(in2);
      if ( P_NO2.getOutput() != P.at(4)->getOutput() )
        cerr << "Erro na simulacao da NOR2 polimorfica\n";
      P_XO2.simular(in2);
      P.at(5)->simular(in2);
      if ( P_XO2.getOutput() != P.at(5)->getOutput() )
        cerr << "Erro na simulacao da XOR2 polimorfica\n";
      P_NX2.simular(in2);
      P.at(6)->simular(in2);
      if ( P_NX2.getOutput() != P.at(6)->getOutput() )
        cerr << "Erro na simulacao da NXOR2 polimorfica\n";
      ++in2.at(1);
    }
    ++in2.at(0);
  }

  // Libera as portas de 2 entradas
  for (i=1; i<7; ++i)
  {
    delete P.at(i);
    P.at(i) = nullptr;
  }

  // Aloca as portas de 3 entradas
  P.at(1) = new PortaAND(3);
  P.at(2) = new PortaNAND(3);
  P.at(3) = new PortaOR(3);
  P.at(4) = new PortaNOR(3);
  P.at(5) = new PortaXOR(3);
  P.at(6) = new PortaNXOR(3);

  // Simulacao das portas polimorficas de 3 entradas
  cout << "\nSIMULACAO DE PORTAS DINAMICAS COM 3 ENTRADAS\n";
  in3.at(0) = bool3S::UNDEF;
  in3.at(1) = bool3S::UNDEF;
  in3.at(2) = bool3S::UNDEF;
  for (i=0; i<3; ++i)
  {
    for (j=0; j<3; ++j)
    {
      for (k=0; k<3; ++k)
      {
        P_AN3.simular(in3);
        P.at(1)->simular(in3);
        if ( P_AN3.getOutput() != P.at(1)->getOutput() )
          cerr << "Erro na simulacao da AND3 polimorfica\n";
        P_NA3.simular(in3);
        P.at(2)->simular(in3);
        if ( P_NA3.getOutput() != P.at(2)->getOutput() )
          cerr << "Erro na simulacao da NAND3 polimorfica\n";
        P_OR3.simular(in3);
        P.at(3)->simular(in3);
        if ( P_OR3.getOutput() != P.at(3)->getOutput() )
          cerr << "Erro na simulacao da OR3 polimorfica\n";
        P_NO3.simular(in3);
        P.at(4)->simular(in3);
        if ( P_NO3.getOutput() != P.at(4)->getOutput() )
          cerr << "Erro na simulacao da NOR3 polimorfica\n";
        P_XO3.simular(in3);
        P.at(5)->simular(in3);
        if ( P_XO3.getOutput() != P.at(5)->getOutput() )
          cerr << "Erro na simulacao da XOR3 polimorfica\n";
        P_NX3.simular(in3);
        P.at(6)->simular(in3);
        if ( P_NX3.getOutput() != P.at(6)->getOutput() )
          cerr << "Erro na simulacao da NXOR3 polimorfica\n";
        ++in3.at(2);
      }
      ++in3.at(1);
    }
    ++in3.at(0);
  }

  // Libera todas as portas
  for (i=0; i<7; ++i)
  {
    delete P.at(i);
    P.at(i) = nullptr;
  }

  return 0;
}

