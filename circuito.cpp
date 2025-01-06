#include <fstream>
#include "circuito.h"

///
/// CLASSE CIRCUITO
///

/// ***********************
/// Inicializacao e finalizacao
/// ***********************

// Construtor por copia
//
// FALTA IMPLEMENTAR
//
Circuito::Circuito(const Circuito& C):
    Nin_circ(C.Nin_circ),
    ports(C.ports.size()),
    out_circ(C.out_circ),
    id_in(C.id_in),
    id_out(C.id_out)
{
    for(int i=0; i<ports.size(); i++){
        ports[i] = C.ports[i]->clone();
    }
}

// Construtor por movimento
//
// FALTA IMPLEMENTAR
//

Circuito::Circuito(Circuito&& C) noexcept:
    Nin_circ(C.Nin_circ),
    ports(),
    out_circ(),
    id_in(),
    id_out()
{
    ports.swap(C.ports);
    out_circ.swap(C.out_circ);
    id_in.swap(C.id_in);
    id_out.swap(C.id_out);
}


// Limpa todo o conteudo do circuito.
void Circuito::clear() noexcept
{
    //
    // FALTA IMPLEMENTAR
    //
    for(int i=0; i<ports.size(); i++) delete ports[i];
    ports.clear();
    Nin_circ=0;
    out_circ.clear();
    id_in.clear();
    id_out.clear();
}

// Operador de atribuicao por copia
Circuito& Circuito::operator=(const Circuito& C)
{
    //
    // FALTA IMPLEMENTAR
    //
    if(this == &C) return *this;
    clear();

    ports.resize(C.ports.size());

    for(int i=0; i<ports.size(); i++){
        ports[i] = C.ports[i]->clone();
    }
    Nin_circ= C.Nin_circ;
    out_circ = C.out_circ;
    id_in = C.id_in;
    id_out= C.id_out;

    return *this;
}

// Operador de atribuicao por movimento
Circuito& Circuito::operator=(Circuito&& C) noexcept
{
    //
    // FALTA IMPLEMENTAR
    //
    clear();
    Nin_circ= C.Nin_circ;
    ports.swap(C.ports);
    out_circ.swap(C.out_circ);
    id_in.swap(C.id_in);
    id_out.swap(C.id_out);
    return *this;
}

// Redimensiona o circuito
void Circuito::resize(int NI, int NO, int NP)
{
    if (NI<=0 || NO<=0 || NP<=0) return;

    //
    // FALTA IMPLEMENTAR
    //
    Nin_circ = NI;                      // Atualiza o número de entradas
    out_circ.resize(NO, bool3S::UNDEF);  // Redimensiona as saídas, inicializando com UNDEF
    id_out.resize(NO, 0);                // Redimensiona o vetor de id_out, inicializando com 0

    // Redimensiona o vetor de portas
    ports.resize(NP, nullptr);          // Redimensiona as portas, inicializando com ponteiros nulos

    // Redimensiona o vetor de conectividade de entradas
    id_in.resize(NP);                   // Redimensiona o vetor de id_in para o número de portas
    for (int i = 0; i < NP; ++i) {
        id_in[i].resize(NI, 0);         // Para cada porta, redimensiona as entradas com valores 0
    }

}

/// ***********************
/// Funcoes de testagem
/// ***********************

// Testa igualdade entre circuitos
bool Circuito::operator==(const Circuito& C) const
{
    // Testa a igualdade do numero de entradas, saidas e portas
    if (getNumInputs() != C.getNumInputs() ||
        getNumOutputs() != C.getNumOutputs() ||
        getNumPorts() != C.getNumPorts()) return false;

    int id;
    // Testa a igualdade das portas
    for (id=1; id<=getNumPorts(); ++id)
    {
        if (definedPort(id))
        {
            if (!C.definedPort(id)) return false;
            if (getNamePort(id) != C.getNamePort(id)) return false;
            if (getNumInputsPort(id) != C.getNumInputsPort(id)) return false;
            for (int j=0; j<getNumInputsPort(id); ++j)
            {
                if (getIdInPort(id,j) != C.getIdInPort(id,j)) return false;
            }
        }
        else if (C.definedPort(id)) return false;
    }
    // Testa a igualdade das saidas
    for (id=1; id<=getNumOutputs(); ++id)
    {
        if (getIdOutputCirc(id) != C.getIdOutputCirc(id)) return false;
    }
    // Tudo igual!
    return true;
}

// Testa circuito valido
bool Circuito::valid() const
{
    int id;
    // Testa o numero de entradas, saidas e portas
    if (getNumInputs()<=0 || getNumOutputs()<=0 || getNumPorts()<=0) return false;
    // Testa cada porta
    for (id=1; id<=getNumPorts(); ++id)
    {
        if (!definedPort(id)) return false;
        for (int j=0; j<getNumInputsPort(id); ++j)
        {
            if (!validIdOrig(getIdInPort(id,j))) return false;
        }
    }
    // Testa cada saida
    for (id=1; id<=getNumOutputs(); ++id)
    {
        if (!validIdOrig(getIdOutputCirc(id))) return false;
    }
    // Tudo valido!
    return true;
}

/// ***********************
/// Funcoes de modificacao
/// ***********************

// A porta cuja id eh IdPort passa a ser do tipo Tipo (NT, AN, etc.), com Nin entradas.
// Tambem altera o numero de conexoes dessa porta no vetor id_in, para ser igual ao novo
// numero de entradas da porta.
// Caso necessario, converte os caracteres da string Tipo para maiusculas.
// Se der tudo certo, retorna true. Se algum parametro for invalido, retorna false.
bool Circuito::setPort(int IdPort,  std::string& Tipo, int Nin)
{
    // Chegagem dos parametros
    if (!validIdPort(IdPort)) return false;
    if (Tipo.size()!=2) return false;
    Tipo.at(0) = toupper(Tipo.at(0));
    Tipo.at(1) = toupper(Tipo.at(1));
    if (Tipo!="NT" &&
        Tipo!="AN" && Tipo!="NA" &&
        Tipo!="OR" && Tipo!="NO" &&
        Tipo!="XO" && Tipo!="NX") return false;
    if (Tipo=="NT" && Nin!=1) return false;
    if (Tipo!="NT" && Nin<2) return false;

    // Altera a porta:
    // - cria a nova porta
    // - redimensiona o vetor de conexoes da porta



    // Criação da nova porta com base no tipo
    if (Tipo == "NT") {
        ports[IdPort - 1] = new PortaNOT();
    }
    if (Tipo == "AN") {
        ports[IdPort-1] = new PortaAND(Nin);
    }
    if (Tipo == "NA") {
        ports[IdPort-1] = new PortaNAND(Nin);
    }
    if (Tipo == "OR") {
        ports[IdPort-1] = new PortaOR(Nin);
    }
    if (Tipo == "NO") {
        ports[IdPort-1] = new PortaNOR(Nin);
    }
    if (Tipo == "XO") {
        ports[IdPort-1] = new PortaXOR(Nin);
    }
    if (Tipo == "NX") {
        ports[IdPort-1] = new PortaNXOR(Nin);
    }

    // Redimensiona o vetor de entradas para o número de entradas especificado
    id_in.at(IdPort - 1).resize(Nin);

    return true;
}

// Altera a origem de uma entrada de uma porta
bool Circuito::setIdInPort(int IdPort, int I, int IdOrig)
{
    // Chegagem dos parametros
    if (!definedPort(IdPort)) return false;
    if (!ports.at(IdPort-1)->validIndex(I)) return false;
    if (!validIdOrig(IdOrig)) return false;
    // Fixa a origem da entrada
    id_in.at(IdPort-1).at(I) = IdOrig;
    return true;
}

// Altera a origem de uma saida
bool Circuito::setIdOutputCirc(int IdOut, int IdOrig)
{
    if (!validIdOutputCirc(IdOut) || !validIdOrig(IdOrig)) return false;
    id_out.at(IdOut-1) = IdOrig;
    return true;
}

/// ***********************
/// E/S de dados
/// ***********************

// Entrada dos dados de um circuito via arquivo
bool Circuito::ler(const std::string& arq)
{
    // Novo circuito provisorio a ser lido do arquivo
    Circuito prov;
    // A stream do arquivo a ser lido
    std::ifstream myfile(arq);

    try
    {
        if (!myfile.is_open()) throw 1;

        // Variaveis temporarias para leitura
        std::string pS;
        int NI,NO,NP;
        char c;
        std::string Tipo;
        int Nin_port;
        int id_orig;
        int i,id,I;

        // Lendo as dimensoes do circuito
        myfile >> pS >> NI >> NO >> NP;
        if (!myfile.good() || pS!="CIRCUITO" ||
            NI<=0 || NO<=0 || NP<=0) throw 2;
        // Redimensionando o novo circuito
        prov.resize(NI, NO, NP);

        // Lendo as portas do circuito
        myfile >> pS;
        if (!myfile.good() || pS!="PORTAS") throw 3;
        for (i=0; i<prov.getNumPorts(); ++i)
        {
            // Lendo o tipo e o numero de entradas de uma porta
            myfile >> id >> c >> Tipo >> Nin_port;
            if (!myfile.good() || id != i+1 || c!=')' ||
                !prov.setPort(id,Tipo,Nin_port)) throw 4;
        }

        // Lendo a conectividade das portas
        myfile >> pS;
        if (!myfile.good() || pS!="CONEXOES") throw 5;
        for (i=0; i<prov.getNumPorts(); ++i)
        {
            // Lendo a id da porta
            myfile >> id >> c;
            if (!myfile.good() || id != i+1 || c!=')') throw 6;
            // Lendo as ids das entradas da porta
            for (I=0; I<prov.getNumInputsPort(id); ++I)
            {
                myfile >> id_orig;
                if (!myfile.good() ||
                    !prov.setIdInPort(id, I, id_orig)) throw 7;
            }
        }

        // Lendo as saidas do circuito
        myfile >> pS;
        if (!myfile.good() || pS!="SAIDAS") throw 8;
        for (i=0; i<prov.getNumOutputs(); ++i)
        {
            // Lendo a id de uma saida do circuito
            myfile >> id >> c >> id_orig;
            if (!myfile.good() || id != i+1 || c!=')' ||
                !prov.setIdOutputCirc(id, id_orig)) throw 9;
        }
    }
    catch (int erro)
    {
        // Mensagem de erro para debug.

        std::cerr << "ERRO Circuito::ler - arquivo (" << arq
                  << ") invalido - erro tipo " << erro << std::endl;

        return false;
    }

    // Leitura OK
    // Faz o circuito assumir as caracteristicas lidas do arquivo
    *this = std::move(prov);
    return true;
}

// Saida dos dados de um circuito
std::ostream& Circuito::escrever(std::ostream& O) const
{
    // Soh imprime se o circuito for valido
    if (!valid()) return O;

    int id,I;

    O << "CIRCUITO "
      << getNumInputs() << ' '
      << getNumOutputs() << ' '
      << getNumPorts() << std::endl;
    O << "PORTAS\n";
    for (id=1; id<=getNumPorts(); ++id)
    {
        O << id << ") " << getNamePort(id) << ' '
          << getNumInputsPort(id) << std::endl;
    }
    O << "CONEXOES\n";
    for (id=1; id<=getNumPorts(); ++id)
    {
        O << id << ')';
        for (I=0; I<getNumInputsPort(id); ++I)
        {
            O << ' ' << getIdInPort(id,I);
        }
        O << std::endl;
    }
    O << "SAIDAS\n";
    for (id=1; id<=getNumOutputs(); ++id)
    {
        O << id << ") " << getIdOutputCirc(id) << std::endl;
    }
    return O;
}

// Salvar circuito em arquivo
bool Circuito::salvar(const std::string& arq) const
{
    if (!valid()) return false;

    std::ofstream myfile(arq);
    if (!myfile.is_open()) return false;
    escrever(myfile);
    return true;
}

/// ***********************
/// SIMULACAO (funcao principal do circuito)
/// ***********************

// Simula o circuito
bool Circuito::simular(const std::vector<bool3S>& in_circ)
{
    // Só simula se o circuito e o parâmetro forem válidos
    if (!valid() || int(in_circ.size()) != getNumInputs()) return false;

    // Inicializa a saída de todas as portas como UNDEF
    for (int i = 0; i < getNumPorts(); i++) {
        ports.at(i)->setOutput(bool3S::UNDEF);
    }

    bool tudo_def, alguma_def;


    do {
        tudo_def = true;
        alguma_def = false;

        for (int i = 1; i <= getNumPorts(); i++) {
            if (getOutputPort(i) == bool3S::UNDEF) {
                std::vector<bool3S> in_port(getNumInputsPort(i));
                for (int j = 0; j < getNumInputsPort(i); j++) {
                    int id_orig = getIdInPort(i,j);
                    in_port[j] = id_orig > 0 ? ports.at(id_orig-1)->getOutput() : in_circ[-id_orig -1];
                }
                ports.at(i-1)->simular(in_port);

                if (getOutputPort(i) == bool3S::UNDEF) {
                    tudo_def = false;
                } else {
                    alguma_def = true;
                }
            }
        }


    } while (!tudo_def && alguma_def);


    for(int i=1; i<=getNumOutputs(); i++){
        int id_orig = getIdOutputCirc(i);
        out_circ[i-1] = id_orig > 0 ? ports.at(id_orig-1)->getOutput() : in_circ[-id_orig -1];
    }


    std::cout << "chegou 2";

    // Tudo OK com a simulação
    return true;
}
