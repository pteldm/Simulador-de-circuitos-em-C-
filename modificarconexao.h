#ifndef MODIFICARCONEXAO_H
#define MODIFICARCONEXAO_H

#include <QDialog>

/* ======================================================================== *
 * ESSA EH A CLASSE QUE REPRESENTA A CAIXA DE DIALOGO PARA ALTERAR CONEXOES *
 * ======================================================================== */

namespace Ui {
class ModificarConexao;
}

class ModificarConexao : public QDialog
{
  Q_OBJECT

public:
  explicit ModificarConexao(QWidget *parent = 0);
  ~ModificarConexao();

  // Fixa o limite inferior (-numInputs) e superior (numPortas)
  // dos spinBoxs que sao usados para indicar a origem das entradas das portas.
  // Deve ser chamado cada vez que definir um novo circuito.
  void fixarLimites(int minimo, int maximo);

  // Fixa as caracteristas iniciais das conexoes que estao sendo modificadas.
  // Depois exibe (show) a janela de modificar conexoes
  void exibir(int IdPort, int NumInputs, int IdInput1, int IdInput2, int IdInput3, int IdInput4);

private slots:
  // Quando modifica a conexao de alguma entrada da porta, verifica se a configuracao
  // eh valida ou nao para habilitar ou nao o botao OK
  void on_spinInput1_valueChanged(int);
  void on_spinInput2_valueChanged(int);
  void on_spinInput3_valueChanged(int);
  void on_spinInput4_valueChanged(int);

  // Apos OK, altera as conexoes de entrada da porta "idPorta".
  // Deve emitir um sinal para a interface principal com os parametros escolhidos.
  void on_buttonBox_accepted();

private:
  Ui::ModificarConexao *ui;

  // Qual porta estah sendo modificada
  int idPort;

  // Testa se a origem (id) do sinal de alguma das entradas da porta tem valor invalido (zero)
  // e se a entrada estah habilitada; se for o caso, desabilita o botao OK
  void testa_entradas_validas();

signals:
  void signModificarConexao(int IdPort, int IdInput1, int IdInput2, int IdInput3, int IdInput4);
};

#endif // MODIFICARCONEXAO_H
