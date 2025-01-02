#ifndef MODIFICARPORTA_H
#define MODIFICARPORTA_H

#include <QDialog>

/* ======================================================================== *
 * ESSA EH A CLASSE QUE REPRESENTA A CAIXA DE DIALOGO PARA ALTERAR PORTAS   *
 * ======================================================================== */

namespace Ui {
class ModificarPorta;
}

class ModificarPorta : public QDialog
{
  Q_OBJECT

public:
  explicit ModificarPorta(QWidget *parent = 0);
  ~ModificarPorta();

  // Fixa as caracteristicas iniciais da porta que estah sendo modificada.
  // Depois exibe (show) a janela de modificar porta
  void exibir(int IdPort, QString TipoPort, int NumInputsPort);

private slots:
  // Sempre que modificar o tipo de porta, modifica os limites do spinBox que eh utilizado
  // para escolher o numero de entradas daquela porta:
  // NT: de 1 a 1
  // Demais: de 2 a 4
  void on_comboTipoPorta_currentTextChanged(const QString &arg1);

  // Apos OK, altera as caracteristas da porta "idPorta".
  // Deve emitir um sinal para a interface principal com os parametros escolhidos.
  void on_buttonBox_accepted();

private:
  Ui::ModificarPorta *ui;

  // Qual porta estah sendo modificada
  int idPort;

signals:
  void signModificarPorta(int IdPort, QString tipoPort, int numInputs);
};

#endif // MODIFICARPORTA_H
