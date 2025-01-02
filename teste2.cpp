#include <iostream>
#include <string>

#include "circuito.h"

using namespace std;

// Funcao para imprimir as informacoes sobre um Circuito
void imprimir(const string& Nome, const Circuito& C)
{
  cout << Nome << '\t'
       << "NIn=" << C.getNumInputs() << '\t'
       << "NOut=" << C.getNumOutputs() << '\t'
       << "NPort=" << C.getNumPorts() << ": ";
  for (int i=0; i<C.getNumPorts(); ++i)
  {
    cout << C.getNamePort(i+1) << ' ';;
  }
  cout << endl;
}

// Funcao que inicializa e retorna um Circuito
// Ao retornar, pode usar o construtor por movimento
Circuito inicializa()
{
  Circuito prov;

  // Dimensiona o circuito
  prov.resize(2,1,1);
  // Inicializa a porta Id==1 como AND de 2 entradas
  prov.setPort(1,"AN",2);
  // As duas entradas da porta Id==1 veem das entradas -1 e -2 do circuito
  prov.setIdInPort(1, 0, -1);
  prov.setIdInPort(1, 1, -2);
  // A saida Id==1 do circuito vem da porta Id==1
  prov.setIdOutput(1, 1);

  return prov;
}

int main(void)
{
  // Testando o construtor default;
  cout << "1)==========\n";
  Circuito C0;
  imprimir("C0",C0);     // Deve imprimir "C0 NIn=0 NOut=0 NPort=0:"
  if (C0.setIdOutput(1,1)) cerr << "Deveria dar erro\n";
  if (C0.setPort(1,"AN",2)) cerr << "Deveria dar erro\n";

  // Testando o resize
  cout << "2)==========\n";
  C0.resize(2,2,2);
  imprimir("C0",C0);     // Deve imprimir "C0 NIn=2 NOut=2 NPort=2: ?? ??"

  // Testando a modificacao de circuito
  cout << "3)==========\n";
  // Inicializa porta inexistente (id invalido)
  if (C0.setPort(-1,"NO",3)) cerr << "Deveria dar erro 1\n";
  if (C0.setPort(0,"NO",3)) cerr << "Deveria dar erro 2\n";
  if (C0.setPort(3,"NO",3)) cerr << "Deveria dar erro 3\n";
  // Inicializa a porta Id==1 (valores invalidos e validos)
  if (C0.setPort(1,"MX",3)) cerr << "Deveria dar erro 4\n";
  if (C0.setPort(1,"NO",1)) cerr << "Deveria dar erro 5\n";
  if (!C0.setPort(1,"NO",3)) cerr << "Nao deveria dar erro 6\n";
  // Inicializa a porta Id==2 (valores invalidos e validos)
  if (C0.setPort(2,"NT",2)) cerr << "Deveria dar erro 7\n";
  if (!C0.setPort(2,"NT",1)) cerr << "Nao deveria dar erro 8\n";
  // Modifica as origens das entradas das portas
  if (C0.setIdInPort(-1,0,-1)) cerr << "Deveria dar erro 9\n";
  if (C0.setIdInPort(0,0,-1)) cerr << "Deveria dar erro 10\n";
  if (!C0.setIdInPort(1,0,-1)) cerr << "Nao deveria dar erro 11\n";
  if (!C0.setIdInPort(1,1,1)) cerr << "Nao deveria dar erro 12\n";
  if (!C0.setIdInPort(1,2,2)) cerr << "Nao deveria dar erro 13\n";
  if (C0.setIdInPort(1,3,2)) cerr << "Deveria dar erro 14\n";
  if (!C0.setIdInPort(2,0,-2)) cerr << "Nao deveria dar erro 15\n";
  if (C0.setIdInPort(2,-1,-2)) cerr << "Deveria dar erro 16\n";
  if (C0.setIdInPort(3,0,-1)) cerr << "Deveria dar erro 17\n";
  // Modifica as origens das saidas
  if (C0.setIdOutput(-1,1)) cerr << "Deveria dar erro 18\n";
  if (C0.setIdOutput(0,1)) cerr << "Deveria dar erro 19\n";
  if (!C0.setIdOutput(1,1)) cerr << "Nao deveria dar erro 20\n";
  if (C0.setIdOutput(1,0)) cerr << "Deveria dar erro 21\n";
  if (!C0.setIdOutput(2,-2)) cerr << "Nao deveria dar erro 22\n";
  if (C0.setIdOutput(3,1)) cerr << "Deveria dar erro 23\n";
  imprimir("C0",C0);     // OK - deve imprimir "C0 NIn=2 NOut=2 NPort=2: NO NT"

  // Testando o construtor por copia e clear
  cout << "4)==========\n";
  Circuito C1(C0);
  if (C1 != C0) cerr << "Nao deveria dar erro 24\n";
  C0.clear();
  imprimir("C0",C0);     // OK - deve imprimir "C0 NIn=0 NOut=0 NPort=0:"
  imprimir("C1",C1);     // OK - deve imprimir "C1 NIn=2 NOut=2 NPort=2: NO NT"

  // Testando o construtor por movimento
  // Pode chamar esse construtor 2 vezes:
  // - Para retornar o valor de inicializa() para uma variavel sem nome
  // - Para criar C2 a partir da variavel sem nome
  cout << "5)==========\n";
  Circuito C2(inicializa());
  imprimir("C2",C2);     // OK - deve imprimir "C2 NIn=2 NOut=1 NPort=1: AN"
  // Alterando C2
  // Inicializa a porta Id==1 como NXOR de 2 entradas
  if (!C2.setPort(1,"NX",2)) cerr << "Nao deveria dar erro 25\n";
  // As duas entradas da porta Id==1 veem das entradas -1 e -2 do circuito
  if (!C2.setIdInPort(1, 0, -1)) cerr << "Nao deveria dar erro 26\n";
  if (!C2.setIdInPort(1, 1, -2)) cerr << "Nao deveria dar erro 27\n";
  imprimir("C2",C2);     // OK - deve imprimir "C2 NIn=2 NOut=1 NPort=1: NX"

  // Testando o operador de atribuicao por copia
  cout << "6)==========\n";
  C0 = C1 = C2;
  if (C1 != C0) cerr << "Nao deveria dar erro 28\n";
  if (C2 != C0) cerr << "Nao deveria dar erro 29\n";
  C1.clear();
  imprimir("C0",C0);     // OK - deve imprimir "C0 NIn=2 NOut=1 NPort=1: NX"
  imprimir("C1",C1);     // OK - deve imprimir "C1 NIn=0 NOut=0 NPort=0:"
  imprimir("C2",C2);     // OK - deve imprimir "C2 NIn=2 NOut=1 NPort=1: NX"

  // Testando o operador de atribuicao por movimento
  cout << "7)==========\n";
  C0 = Circuito();
  imprimir("C0",C0);     // OK - deve imprimir "C0 NIn=0 NOut=0 NPort=0:"
  C1 = inicializa();
  imprimir("C1",C1);     // OK - deve imprimir "C1 NIn=2 NOut=1 NPort=1: AN"

  return 0;
}

