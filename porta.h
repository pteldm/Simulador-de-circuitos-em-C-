#ifndef _PORTA_H_
#define _PORTA_H_

#include <string>
#include <vector>
#include "bool3S.h"

///
/// A CLASSE ABSTRATA PORTA
///

class Porta;
using ptr_Porta = Porta*;

class Porta
{
protected:
  // O numero de entradas da porta
  int Nin_port;
  // O valor logico da saida da porta (?, F ou T)
  bool3S out_port;

public:
  /// ***********************
  /// Inicializacao e finalizacao
  /// ***********************

  // A classe abstrata Porta nao tem construtor default.
  Porta() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  Porta(int NI): Nin_port(NI),out_port(bool3S::UNDEF) {}
  // Destrutor virtual
  virtual ~Porta() {}

  // Essa funcao virtual pura deve criar e retornar um ponteiro que aponta para
  // uma copia de si mesma, do tipo correto.
  virtual ptr_Porta clone() const = 0;

  /// ***********************
  /// Funcoes de testagem
  /// ***********************

  // Retorna true se um indice (qual entrada da porta) eh valido
  bool validIndex(int I) const
  {
    return (I>=0 && I<getNumInputs());
  }

  /// ***********************
  /// Funcoes de consulta
  /// ***********************

  // Funcao virtual pura que retorna a sigla correta da Port (AN, NT, OR, NX, etc.)
  virtual std::string getName() const = 0;

  // Retorna o numero de entradas da porta
  int getNumInputs() const
  {
    return Nin_port;
  }

  // Retorna a saida logica (?, F ou T) da porta
  bool3S getOutput() const
  {
    return out_port;
  }

  /// ***********************
  /// Funcoes de modificacao
  /// ***********************

  // Fixa o valor logico da saida da porta (?, F, T)
  void setOutput(bool3S S)
  {
    out_port=S;
  }

  /// ***********************
  /// SIMULACAO (funcao principal da porta)
  /// ***********************

  // Simula uma porta logica.
  // Recebe um vector de bool3S com os valores logicos das entradas da porta
  // com os quais deve ser simulada a funcao logica da porta.
  // Se a dimensao do vetor in_port for adequada (>0 e igual ao numero de entradas
  // da porta), armazena o resultado da simulacao em out_port e retorna true.
  // Se nao for, faz out_port = UNDEF e retorna false.
  virtual bool simular(const std::vector<bool3S>& in_port) = 0;
};

///
/// As outras PORTAS
///

class PortaNOT: public Porta
{
public:
  // Construtor default (fixa o numero de entradas da porta como sendo 1)
  PortaNOT(): Porta(1) {}
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR

  // deletando o construtor específico pois a porta NOT deve ser criada apenas com 1 entrada
  PortaNOT(int N_entradas) = delete;

  //destrutor da classe PortaNOT
  ~PortaNOT()
  {
      this->Nin_port=0;
      this->out_port=bool3S::UNDEF;
  }

  //construtor por cópia
  PortaNOT(const PortaNOT &other) : Porta(other.Nin_port)
  {
      out_port = other.out_port;
  }

  //sobrecarga do operador de atribuição (por cópia)
  PortaNOT operator=(const PortaNOT& other)
  {
      if(this==&other)
      {
        return *this;
      }
      return PortaNOT(other);
  };

  ptr_Porta clone() const
  {
    return new PortaNOT(*this);
  }

  std::string getName() const
  {
      return "NT";
  }

  bool simular(const std::vector<bool3S>& in_port);
};

class PortaAND: public Porta
{
public:
  // PortaAND nao tem construtor default: sempre deve ser informado o num de entradas
  PortaAND() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaAND(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR
  //

  //destrutor da classe Porta AND
  ~PortaAND()
  {
      this->Nin_port=0;
      this->out_port= bool3S::UNDEF;
  }

  //construtor por cópia
  PortaAND(const PortaAND &other) : Porta(other.Nin_port)
  {
    if(other.Nin_port<2)
    {
      Nin_port = 0;
    }
    this->out_port=other.out_port;
  }

  //sobrecarga do operador de atribuição (por cópia)
  PortaAND operator=(const PortaAND &other)
  {
      if(this == &other)
      {
        return *this;
      }
      return PortaAND(other);
  }

  //função virtual clone da classe PortaAND
  ptr_Porta clone() const
  {
    return new PortaAND(*this);
  }

  //função virtual getName da classe PortaAND
  std::string getName() const
  {
      return "AN";
  }

  //função virtual simular da classe PortaAND
  bool simular(const std::vector<bool3S>& in_port);

};

class PortaNAND: public Porta
{
public:
  // PortaNAND nao tem construtor default: sempre deve ser informado o num de entradas
  PortaNAND() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaNAND(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR
  //

  //destrutor da classe PortaNAND
  ~PortaNAND()
  {
      this->Nin_port=0;
      this->out_port=bool3S::UNDEF;
  }

  //construtor por cópia
  PortaNAND(const PortaNAND &other) : Porta(other.Nin_port)
  {
      this->out_port = other.out_port;
  }

  //sobrecarga do operador de atribuição(por cópia)
  PortaNAND operator=(const PortaNAND &other)
  {
      if(this==&other)
      {
          return *this;
      }
      return PortaNAND(other);
  }

  //função virtual clone da classe PortaNAND
  ptr_Porta clone() const
  {
      return new PortaNAND(*this);
  }

  std::string getName() const
  {
      return "NA";
  }

  bool simular(const std::vector<bool3S> &in_port);

};

class PortaOR: public Porta
{
public:
  // PortaOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR
  //

  //destrutor da classe PortaOR
  ~PortaOR()
  {
      this->Nin_port=0;
      this->out_port=bool3S::UNDEF;
  }

  //construtor por cópia da classe PortaOR
  PortaOR(const PortaOR &other) : Porta(other.Nin_port)
  {
      this->out_port = other.out_port;
  }

  //sobrecarga do operador de atribuição (por cópia)
  PortaOR operator=(const PortaOR &other)
  {
      if(this==&other)
      {
          return *this;
      }
      return PortaOR(other);
  }

  //função virtual clone
  ptr_Porta clone() const
  {
      return new PortaOR(*this);
  }

  //função virtual getName
  std::string getName() const
  {
      return "OR";
  }

  //função virtual simular
  bool simular(const std::vector<bool3S> &in_port);
};

class PortaNOR: public Porta
{
public:
  // PortaNOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaNOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaNOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR
  //

  //destrutor da classe PortaNOR
  ~PortaNOR()
  {
      this->Nin_port=0;
      this->out_port=bool3S::UNDEF;
  }

  //construtor por cópia da classe PortaNOR
  PortaNOR(const PortaNOR &other) : Porta(other.Nin_port)
  {
      this->out_port=other.out_port;
  }

  //sobrecarga do operador de atribuição(por cópia)
  PortaNOR operator=(const PortaNOR &other)
  {
      if(this==&other)
      {
          return *this;
      }
      return PortaNOR(other);
  }

  //função virtual clone
  ptr_Porta clone() const
  {
      return new PortaNOR(*this);
  }

  //função virtual getName
  std::string getName() const
  {
      return "NO";
  }

  //função virtual simular
  bool simular(const std::vector<bool3S> &in_port);
};

class PortaXOR: public Porta
{
public:
  // PortaXOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaXOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaXOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR
  //

  //destrutor da classe PortaXOR
  ~PortaXOR()
  {
      this->Nin_port=0;
      this->out_port=bool3S::UNDEF;
  }

  //construtor por cópia da classe PortaXOR
  PortaXOR(const PortaXOR &other) : Porta(other.Nin_port)
  {
      this->out_port = other.out_port;
  }

  //sobrecarga do operador de atribuição(por cópia)
  PortaXOR operator=(const PortaXOR &other)
  {
      if(this == &other)
          return *this;

      return PortaXOR(other);
  }

  //função virtual clone
  ptr_Porta clone() const
  {
      return new PortaXOR(*this);
  }

  //função virtual getName
  std::string getName() const
  {
      return "XO";
  }

  //função virtual simular
  bool simular(const std::vector<bool3S> &in_port);
};

class PortaNXOR: public Porta
{
public:
  // PortaNXOR nao tem construtor default: sempre deve ser informado o num de entradas
  PortaNXOR() = delete;
  // Construtor especifico (recebe como parametro o numero de entradas da porta)
  // Se o parametro for invalido, faz Nin_port=0
  PortaNXOR(int NI): Porta(NI)
  {
    if (NI<2) Nin_port=0;
  }
  // DEMAIS FUNCOES DA PORTA
  //
  // FALTA DECLARAR
  //
};

#endif // _PORTA_H_
