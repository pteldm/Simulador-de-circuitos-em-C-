#ifndef MAINCIRCUITO_H
#define MAINCIRCUITO_H

#include <QMainWindow>
#include <QLabel>
#include "circuito.h"
#include "newcircuito.h"
#include "modificarporta.h"
#include "modificarconexao.h"
#include "modificarsaida.h"

/* ======================================================================== *
 * ESSA EH A CLASSE QUE REPRESENTA A TELA PRINCIPAL DO APLICATIVO           *
 * ======================================================================== */

namespace Ui {
class MainCircuito;
}

class MainCircuito : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainCircuito(QWidget *parent = 0);
  ~MainCircuito();

private slots:
  // Redimensiona o circuito
  void slotNewCircuito(int NInputs, int NOutputs, int NPortas);

  // Modifica uma porta
  void slotModificarPorta(int IdPort, QString TipoPort, int NumInputsPort);

  // Modifica uma conexao
  void slotModificarConexao(int IdPort, int IdInput1, int IdInput2, int IdInput3, int IdInput4);

  // Modifica uma saida
  void slotModificarSaida(int idSaida, int idOrigemSaida);

  // Exibe a caixa de dialogo para fixar caracteristicas de um novo circuito
  void on_actionNovo_triggered();

  // Abre uma caixa de dialogo para ler um arquivo
  void on_actionLer_triggered();

  // Abre uma caixa de dialogo para salvar um arquivo
  void on_actionSalvar_triggered();

  // Sai do aplicativo
  void on_actionSair_triggered();

  // Gera e exibe a tabela verdade para o circuito
  // Chama a funcao simular da classe Circuito
  void on_actionGerar_tabela_triggered();

  // Exibe a caixa de dialogo para fixar caracteristicas de uma porta
  void on_tablePortas_activated(const QModelIndex &index);

  // Exibe a caixa de dialogo para fixar conexoes de uma porta
  void on_tableConexoes_activated(const QModelIndex &index);

  // Exibe a caixa de dialogo para fixar caracteristicas de uma saida
  void on_tableSaidas_activated(const QModelIndex &index);

private:
  Ui::MainCircuito *ui;

  // O objeto da classe Circuito que efetivamente armazena os dados
  Circuito C;

  // As caixas pop up para digitacao de valores do circuito
  NewCircuito *newCircuito;           // Caixa de dialogo para criar um novo circuito
  ModificarPorta *modificarPorta;     // Caixa de dialogo para modificar uma porta
  ModificarConexao *modificarConexao; // Caixa de dialogo para modificar uma porta
  ModificarSaida *modificarSaida;     // Caixa de dialogo para modificar uma saida

  // Os exibidores dos valores na barra de status
  QLabel *numIn;     // Exibe o numero de entradas do circuito na barra de status
  QLabel *numOut;    // Exibe o numero de saidas do circuito na barra de status
  QLabel *numPortas; // Exibe o numero de portas do circuito na barra de status

  // Redimensiona todas as tabelas e reexibe todos os valores da barra de status
  // Essa funcao deve ser chamada sempre que mudar o circuito (digitar ou ler de arquivo)
  void redimensionaTabelas();

  // Apaga conteudo e redefine o texto dos pseudocabecalhos da tabela verdade.
  // Deve ser chamada sempre que alguma caracteristica do circuito (porta, conexao, saida) for alterada.
  void limparTabelaVerdade();

  // Exibe os dados da porta cuja id eh IdPort.
  // Essa funcao deve ser chamada sempre que mudar caracteristicas da porta.
  // A funcao redimensiona_tabela jah chama essa funcao para todas as portas.
  void showPort(int IdPort);

  // Exibe os dados das conexoes da porta cuja id eh IdPort.
  // Essa funcao deve ser chamada sempre que mudar caracteristicas da porta.
  // A funcao redimensiona_tabela jah chama essa funcao para todas as portas.
  void showConexao(int IdPort);

  // Exibe os dados da saida cuja id eh IdSaida.
  // Essa funcao deve ser chamada sempre que mudar valores da saida.
  // A funcao redimensiona_tabela jah chama essa funcao para todas as saidas.
  void showOutput(int IdSaida);
};

#endif // MAINCIRCUITO_H
