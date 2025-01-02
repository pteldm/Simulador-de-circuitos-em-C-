#include "maincircuito.h"
#include "ui_maincircuito.h"
#include <QStringList>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

MainCircuito::MainCircuito(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainCircuito),
  C(),
  newCircuito(new NewCircuito(this)),
  modificarPorta(new ModificarPorta(this)),
  modificarConexao(new ModificarConexao(this)),
  modificarSaida(new ModificarSaida(this)),
  numIn(new QLabel(this)),
  numOut(new QLabel(this)),
  numPortas(new QLabel(this))
{
  ui->setupUi(this);

  // Cabecalhos da tabela de portas
  ui->tablePortas->horizontalHeader()->setVisible(true);
  ui->tablePortas->verticalHeader()->setVisible(true);
  ui->tablePortas->setHorizontalHeaderLabels(QStringList() << "TIPO" << "NUM\nENTR");
  ui->tablePortas->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->tablePortas->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);

  // Cabecalhos da tabela de conexoes
  ui->tableConexoes->horizontalHeader()->setVisible(true);
  ui->tableConexoes->verticalHeader()->setVisible(true);
  ui->tableConexoes->setHorizontalHeaderLabels(QStringList() << "ENTR\n1" << "ENTR\n2" << "ENTR\n3" << "ENTR\n4");
  ui->tableConexoes->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->tableConexoes->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
  ui->tableConexoes->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
  ui->tableConexoes->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);

  // Cabecalhos da tabela de saidas
  ui->tableSaidas->horizontalHeader()->setVisible(true);
  ui->tableSaidas->verticalHeader()->setVisible(true);
  ui->tableSaidas->setHorizontalHeaderLabels(QStringList() << "ORIG\nSAIDA");
  ui->tableSaidas->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

  // Insere os widgets da barra de status
  statusBar()->insertWidget(0,new QLabel("Num entradas: "));
  statusBar()->insertWidget(1,numIn);
  statusBar()->insertWidget(2,new QLabel("   Num saidas: "));
  statusBar()->insertWidget(3,numOut);
  statusBar()->insertWidget(4,new QLabel("   Num portas: "));
  statusBar()->insertWidget(5,numPortas);

  // Conecta sinais

  // Sinais da janela novo circuito para janela principal
  connect(newCircuito, &NewCircuito::signNewCircuito,
          this, &MainCircuito::slotNewCircuito);
  // Sinais da janela modificar porta para janela principal
  connect(modificarPorta, &ModificarPorta::signModificarPorta,
          this, &MainCircuito::slotModificarPorta);
  // Sinais da janela modificar conexao para janela principal
  connect(modificarConexao, &ModificarConexao::signModificarConexao,
          this, &MainCircuito::slotModificarConexao);
  // Sinais da janela modificar saida para janela principal
  connect(modificarSaida, &ModificarSaida::signModificarSaida,
          this, &MainCircuito::slotModificarSaida);

  // Redimensiona todas as tabelas e reexibe os valores da barra de status
  // Essa funcao deve ser chamada sempre que mudar o circuito
  redimensionaTabelas();
}

MainCircuito::~MainCircuito()
{
  delete ui;
}

// Redimensiona e reexibe todas as tabelas e reexibe todos os valores da barra de status.
// Essa funcao deve ser chamada sempre que mudar o circuito (digitar ou ler de arquivo)
void MainCircuito::redimensionaTabelas()
{
  // Caracteristicas do Circuito
  int numInputs=C.getNumInputs();
  int numOutputs=C.getNumOutputs();
  int numPorts=C.getNumPorts();

  // Variaveis auxiliares
  int i;

  // ==========================================================
  // Ajusta os valores da barra de status
  // ==========================================================

  numIn->setNum(numInputs);
  numOut->setNum(numOutputs);
  numPortas->setNum(numPorts);

  // ==========================================================
  // Redimensiona e exibe a tabela das portas
  // ==========================================================

  // Limpa o conteudo, mas nao os cabecalhos
  ui->tablePortas->clearContents();

  ui->tablePortas->setRowCount(numPorts);
  for (i=0; i<numPorts; i++)
  {
    showPort(i+1);
  }

  // ==========================================================
  // Redimensiona e exibe a tabela das conexoes
  // ==========================================================

  // Limpa o conteudo, mas nao os cabecalhos
  ui->tableConexoes->clearContents();

  ui->tableConexoes->setRowCount(numPorts);
  for (i=0; i<numPorts; i++)
  {
    showConexao(i+1);
  }

  // ==========================================================
  // Redimensiona e exibe a tabela de saidas
  // ==========================================================

  // Limpa o conteudo, mas nao os cabecalhos
  ui->tableSaidas->clearContents();

  ui->tableSaidas->setRowCount(numOutputs);
  for (i=0; i<numOutputs; i++)
  {
    showOutput(i+1);
  }

  // ==========================================================
  // Redimensiona a tabela verdade
  // ==========================================================

  // Antes de redimensionar a tabela, anula todos os setSpan da primeira linha
  // Se nao fizer isso, dah erro ao redimensionar
  ui->tableTabelaVerdade->clearSpans();

  // Modifica as dimensoes
  ui->tableTabelaVerdade->setColumnCount(numInputs+numOutputs);
  int numCombinacoesEntrada = (numInputs>0 ? round(pow(3,numInputs)) : 0);
  // A tabela verdade tem uma linha a mais do que o numero de combinacoes de entrada
  // para conter o pseudocabecalho da primeira linha
  ui->tableTabelaVerdade->setRowCount(1 + numCombinacoesEntrada);
  // Cria as celulas de pseudocabecalho na primeira linha,
  // formadas pela aglutinacao de varias celulas
  if (numInputs > 1) ui->tableTabelaVerdade->setSpan(0,0,1,numInputs);
  if (numOutputs > 1) ui->tableTabelaVerdade->setSpan(0,numInputs,1,numOutputs);

  // Apaga conteudo e redefine o texto dos pseudocabecalhos
  limparTabelaVerdade();

  // ==========================================================
  // Fixa os limites para os spin boxs das janelas
  // de conexoes de portas (classe ModificarConexao) e
  // de origem das saidas (classe ModificarSaida).
  // ==========================================================

  modificarConexao->fixarLimites(-numInputs, numPorts);
  modificarSaida->fixarLimites(-numInputs, numPorts);
}

// Apaga conteudo e redefine o texto dos pseudocabecalhos da tabela verdade.
// Deve ser chamada sempre que alguma caracteristica do circuito (porta, conexao, saida) for alterada.
void MainCircuito::limparTabelaVerdade()
{
  // Caracteristicas do Circuito
  int numInputs(C.getNumInputs());
  int numOutputs(C.getNumOutputs());

  // Variavel auxiliar
  QLabel *prov;

  // Limpa todo o conteudo, inclusive pseudocabecalhos
  ui->tableTabelaVerdade->clear();

  // Recoloca os textos dos pseudocabecalhos na primeira linha.
  // Entradas
  if (numInputs > 0)
  {
    prov = new QLabel("ENTRADAS");
    prov->setAlignment(Qt::AlignCenter);
    prov->setStyleSheet("font-weight: bold");
    ui->tableTabelaVerdade->setCellWidget(0,0,prov);
  }
  // Saidas
  if (numOutputs > 0)
  {
    prov = new QLabel("SAIDAS");
    prov->setAlignment(Qt::AlignCenter);
    prov->setStyleSheet("font-weight: bold");
    ui->tableTabelaVerdade->setCellWidget(0,numInputs,prov);
  }
}

void MainCircuito::slotNewCircuito(int NInputs, int NOutputs, int NPortas)
{
  // Redimensiona o Circuito
  C.resize(NInputs,NOutputs,NPortas);

  // Depois do novo circuito redimensionado, as tabelas devem ser redimensionadas
  redimensionaTabelas();
}

void MainCircuito::slotModificarPorta(int IdPort, QString TipoPort, int NumInputsPort)
{
  // Altera a porta.
  std::string Tipo = TipoPort.toStdString();
  if (C.setPort(IdPort, Tipo, NumInputsPort))
  {
    // Depois de alterada, devem ser reexibidas a porta e as conexoes correspondentes
    showPort(IdPort);
    showConexao(IdPort);
  }
  else
  {
    QMessageBox::critical(this, "Porta incorreta", "Erro na modificacao da porta id="+QString::number(IdPort)+
                          " tipo="+TipoPort+" com "+QString::number(NumInputsPort)+ " entradas");
  }
  // Limpa a tabela verdade
  limparTabelaVerdade();
}

void MainCircuito::slotModificarConexao(int IdPort, int IdInput1, int IdInput2, int IdInput3, int IdInput4)
{
  // Modifica a conexao
  bool tudo_ok = C.setIdInPort(IdPort, 0, IdInput1);
  if (tudo_ok && C.getNumInputsPort(IdPort)>=2) tudo_ok = C.setIdInPort(IdPort, 1, IdInput2);
  if (tudo_ok && C.getNumInputsPort(IdPort)>=3) tudo_ok = C.setIdInPort(IdPort, 2, IdInput3);
  if (tudo_ok && C.getNumInputsPort(IdPort)>=4) tudo_ok = C.setIdInPort(IdPort, 3, IdInput4);
  if (tudo_ok)
  {
    // Depois de alterada, devem ser reexibidas as conexoes
    showConexao(IdPort);
  }
  else
  {
    QMessageBox::critical(this, "Conexoes incorretas", "Erro na modificacao das conexoes id="+QString::number(IdPort)+
                          " com valores "+QString::number(IdInput1)+','+QString::number(IdInput2)+','+
                          QString::number(IdInput3)+','+QString::number(IdInput4));
  }
  // Limpa a tabela verdade
  limparTabelaVerdade();
}

void MainCircuito::slotModificarSaida(int IdSaida, int IdOrigemSaida)
{
  // Modifica a saida
  if (C.setIdOutputCirc(IdSaida, IdOrigemSaida))
  {
    // Depois de alterada, deve ser reexibida a saida correspondente
    showOutput(IdSaida);
  }
  else
  {
    QMessageBox::critical(this, "Saida incorreta", "Erro na modificacao da saida id="+QString::number(IdSaida)+
                          " com valor "+QString::number(IdOrigemSaida));
  }
  // Limpa a tabela verdade
  limparTabelaVerdade();
}

// Exibe os dados da porta cuja id eh IdPort.
// Essa funcao deve ser chamada sempre que mudar caracteristicas da porta.
// A funcao redimensiona_tabela jah chama essa funcao para todas as portas.
void MainCircuito::showPort(int IdPort)
{
  // Testa se IdPort eh valido
  if (!C.validIdPort(IdPort))
  {
    QMessageBox::critical(this, "Porta incorreta", "Erro na exibicao da porta id="+QString::number(IdPort));
    return;  // Encerra a funcao
  }

  // Obtem o nome e o numero de entradas da porta
  QString namePort = QString::fromStdString(C.getNamePort(IdPort));
  int numInputsPort = C.getNumInputsPort(IdPort);

  // Cria e define valores dos widgets da linha da tabela que corresponde aa porta
  QLabel *prov;
  // Coluna 0
  prov = new QLabel(namePort);
  prov->setAlignment(Qt::AlignCenter);
  ui->tablePortas->setCellWidget(IdPort-1,0,prov);
  // Coluna 1
  prov = new QLabel(QString::number(numInputsPort));
  prov->setAlignment(Qt::AlignCenter);
  ui->tablePortas->setCellWidget(IdPort-1,1,prov);
}

// Exibe os dados das conexoes da porta cuja id eh IdPort.
// Essa funcao deve ser chamada sempre que mudar caracteristicas da porta.
// A funcao redimensiona_tabela jah chama essa funcao para todas as portas.
void MainCircuito::showConexao(int IdPort)
{
  // Testa se IdPort eh valido
  if (!C.validIdPort(IdPort))
  {
    QMessageBox::critical(this, "Conexoes incorretas", "Erro na exibicao das conexoes da porta id="+QString::number(IdPort));
    return;  // Encerra a funcao
  }

  // Obtem o numero de entradas da porta
  int numInputsPort=C.getNumInputsPort(IdPort);

  // Cria e define valores dos widgets da linha da tabela que corresponde aas conexoes
  QLabel *prov;
  for (int j=0; j<numInputsPort; j++)
  {
    // Obtem a id de origem da entrada j da porta cuja id eh IdPort
    int idInput=C.getIdInPort(IdPort,j);

    // Cria os widgets das celulas da tabela de portas
    prov = new QLabel(QString::number(idInput));
    prov->setAlignment(Qt::AlignCenter);
    ui->tableConexoes->setCellWidget(IdPort-1,j,prov);
  }
}

// Exibe os dados da saida cuja id eh IdSaida.
// Essa funcao deve ser chamada sempre que mudar valores da saida.
// A funcao redimensiona_tabela jah chama essa funcao para todas as saidas.
void MainCircuito::showOutput(int IdSaida)
{
  // Testa se IdSaida eh valido
  if (!C.validIdOutputCirc(IdSaida))
  {
    QMessageBox::critical(this, "Saida incorreta", "Erro na exibicao da saida id="+QString::number(IdSaida));
    return;  // Encerra a funcao
  }

  // Obtem a id de origem da saida cuja id eh IdSaida
  int idOutput=C.getIdOutputCirc(IdSaida);

  // Cria e define valor do widget da celula da tabela de saidas
  QLabel *prov;
  // Coluna 0 (unica)
  prov = new QLabel(QString::number(idOutput));
  prov->setAlignment(Qt::AlignCenter);
  ui->tableSaidas->setCellWidget(IdSaida-1,0,prov);
}

// Exibe a caixa de dialogo para fixar caracteristicas de um novo circuito
void MainCircuito::on_actionNovo_triggered()
{
  newCircuito->exibir();
}

// Abre uma caixa de dialogo para ler um arquivo
void MainCircuito::on_actionLer_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Arquivo de circuito", "",
                                                  "Circuitos (*.txt);;Todos (*.*)");

  if (!fileName.isEmpty()) {
    // Leh o circuito do arquivo com nome "fileName"
    if (!C.ler(fileName.toStdString()))
    {
      // Exibe uma msg de erro na leitura
      QMessageBox::critical(this, "Erro de leitura", "Erro ao ler um circuito a partir do arquivo:\n"+fileName);
      return;
    }

    // Testa se o circuito lido tem alguma porta com mais de 4 entradas.
    // Caso haja, nao pode ser exibido nessa interface.
    for (int id=1; id<=C.getNumPorts(); ++id)
    {
      // Testa o numero de entradas de uma porta
      if (C.getNumInputsPort(id) > 4)
      {
        // Exibe uma msg de erro
        QMessageBox::critical(this, "Erro de exibicao", "Circuito contem porta com mais de 4 entradas");
        // Torna o circuito vazio
        C.clear();
        // Continua para o redimensionamento das tabelas.
        continue;
      }
    }

    // Feita a leitura, reexibe todas as tabelas
    redimensionaTabelas();
  }
}

// Abre uma caixa de dialogo para salvar um arquivo
void MainCircuito::on_actionSalvar_triggered()
{
  // Soh pode salvar se o Circuito for valido
  if (!C.valid())
  {
    QMessageBox::critical(this, "Erro de escrita", "O Circuito nao esta completamente definido.\nNao pode ser salvo.");
    return;
  }

  QString fileName = QFileDialog::getSaveFileName(this, "Arquivo de circuito", "",
                                                  "Circuitos (*.txt);;Todos (*.*)");

  if (!fileName.isEmpty()) {
    // Salva o circuito no arquivo com nome "fileName"
    if (!C.salvar(fileName.toStdString()))
    {
      // Exibe uma msg de erro na leitura
      QMessageBox::critical(this, "Erro de escrita", "Erro ao salvar um circuito no arquivo:\n"+fileName);
    }
  }
}

void MainCircuito::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

// Gera e exibe a tabela verdade para o circuito
// Chama a funcao simular da classe circuito
void MainCircuito::on_actionGerar_tabela_triggered()
{
  // Soh pode simular se o Circuito for valido
  if (!C.valid())
  {
    QMessageBox::critical(this, "Erro de simulacao", "O Circuito nao esta completamente definido.\nNao pode ser simulado.");
    return;
  }

  // Caracteristicas do Circuito
  int numInputs = C.getNumInputs();
  int numOutputs = C.getNumOutputs();

  // vector com as "numInputs" entradas do circuito,
  // a serem geradas consecutivamente com todas as combinacoes de entrada.
  // Comeca com todas as entradas bool3S::UNDEF
  std::vector<bool3S> in_circ(numInputs, bool3S::UNDEF);

  // Linha na tabela verdade (comeca de 1 e nao de 0,
  // pois a 1a linha eh o pseudocabecalho)
  int linha=1;

  // Variaveis auxiliares
  QLabel *prov;
  int i;

  //
  // Gera todas as combinacoes de entrada e as linhas correspondentes da tabela verdade
  //
  do
  {
    // Chama o metodo de simulacao da classe Circuito,
    // passando como parametro o vetor de entradas atual.
    C.simular(in_circ);

    //
    // Exibe as entradas
    //
    for (i=0; i<numInputs; ++i)
    {
      // Exibe o valor de cada uma das entradas do circuito
      // na linha "linha" da tabela verdade, nas colunas de 0 a numInputs-1
      prov = new QLabel( QString( toChar(in_circ.at(i)) ) );
      prov->setAlignment(Qt::AlignCenter);
      ui->tableTabelaVerdade->setCellWidget(linha, i, prov);
    }

    //
    // Exibe as saidas
    //
    for (i=0; i<numOutputs; ++i)
    {
      // Exibe o valor de cada uma das saidas do circuito
      // na linha "linha" da tabela verdade, nas colunas de numInputs a numInputs+numOutputs-1
      prov = new QLabel( QString( toChar(C.getOutputCirc(i+1)) ) );
      prov->setAlignment(Qt::AlignCenter);
      ui->tableTabelaVerdade->setCellWidget(linha, i+numInputs, prov);
    }

    // Incrementa a linha da tabela para proxima exibicao
    ++linha;

    // Gera a proxima combinacao de entrada
    // Incrementa a ultima entrada que nao for TRUE
    // Se a ultima for TRUE, tenta incrementar a anterior
    i = numInputs-1;
    while (i>=0 && in_circ.at(i)==bool3S::TRUE)
    {
      ++in_circ.at(i);
      --i;
    };
    // Incrementa a input selecionada
    if (i>=0) ++in_circ.at(i);

  } while (i>=0);
}

// Exibe a caixa de dialogo para fixar caracteristicas de uma porta
void MainCircuito::on_tablePortas_activated(const QModelIndex &index)
{
  // Converte de indice de linha para Id de porta
  int idPort = index.row()+1;

  // Caracteristicas da porta
  QString namePort = C.getNamePort(idPort).c_str();
  int numInputsPort = C.getNumInputsPort(idPort);

  // Exibe a janela de modificacao com as caracteristicas atuais da porta
  modificarPorta->exibir(idPort, namePort, numInputsPort);
}

// Exibe a caixa de dialogo para fixar conexoes de uma porta
void MainCircuito::on_tableConexoes_activated(const QModelIndex &index)
{
  // Converte de indice de linha para Id de porta
  int idPort = index.row()+1;

  // Numero de entradas da porta
  int numInputsPort = C.getNumInputsPort(idPort);

  // As id das entradas da porta
  int idInputPort[4]{0};
  for (int j=0; j<numInputsPort; j++)
  {
    idInputPort[j] = C.getIdInPort(idPort,j);
  }

  // Exibe a janela de modificacao com as caracteristicas atuais das conexoes
  modificarConexao->exibir(idPort, numInputsPort, idInputPort[0], idInputPort[1], idInputPort[2], idInputPort[3]);
}

// Exibe a caixa de dialogo para fixar caracteristicas de uma saida
void MainCircuito::on_tableSaidas_activated(const QModelIndex &index)
{
  // Converte de indice de linha para Id de porta
  int idSaida = index.row()+1;

  // Id de origem da saida
  int idOrigemSaida = C.getIdOutputCirc(idSaida);

  // Exibe a janela de modificacao com as caracteristicas atuais da saida
  modificarSaida->exibir(idSaida, idOrigemSaida);
}
