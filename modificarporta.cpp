#include "modificarporta.h"
#include "ui_modificarporta.h"

ModificarPorta::ModificarPorta(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ModificarPorta),
  idPort(0)
{
  ui->setupUi(this);

  // Inclui os tipos de portas
  ui->comboTipoPorta->addItems(QStringList() << "NT" << "AN" << "OR" << "XO" << "NA" << "NO" << "NX");
  // Seleciona o primeiro tipo de porta (NT)
  ui->comboTipoPorta->setCurrentText("NT");
  // Como o index foi alterado via programa, chama on_comboTipoPorta_currentIndexChanged
  // Isso altera os limites do spinBox do numero de entradas (1-1 p/ NT)
}

ModificarPorta::~ModificarPorta()
{
  delete ui;
}

// Fixa as caracteristas iniciais da porta que estah sendo modificada.
// Depois exibe (show) a janela de modificar porta.
void ModificarPorta::exibir(int IdPort, QString TipoPort, int NumInputsPort)
{
  // Armazena a id da porta que estah sendo modificada
  idPort = IdPort;
  // Altera o label de exibicao da janela
  ui->labelIdPorta->setNum(idPort);

  // Ajusta os boxs de entrada de dados aos parametros da porta

  // Tipo de porta
  if (TipoPort!="AN" && TipoPort!="NA" && TipoPort!="OR" &&
      TipoPort!="NO" && TipoPort!="XO" && TipoPort!="NX") TipoPort="NT";
  ui->comboTipoPorta->setCurrentText(TipoPort);
  // Como a escolha do combo foi alterado via programa, chama on_comboTipoPorta_currentIndexChanged
  // Isso, por sua vez, altera os limites do spinBox do numero de entradas (1-1 p/ NT, 2-4 p/ demais)

  // Numero de entradas
  ui->spinNumInputs->setValue(NumInputsPort);

  // Exibe a janela
  show();
}

// Sempre que modificar o tipo de porta, modifica os limites do spinBox que eh utilizado
// para escolher o numero de entradas daquela porta:
// NT: de 1 a 1
// Demais: de 2 a 4
void ModificarPorta::on_comboTipoPorta_currentTextChanged(const QString &arg1)
{
  // Fixa os limites para o numero de entradas: de 1 a 1 se for NT, 2 a 4 para outros tipos
  if (arg1=="NT") ui->spinNumInputs->setRange(1,1);
  else ui->spinNumInputs->setRange(2,4);
}

// Apos OK, altera as caracteristas da porta "idPorta".
// Deve emitir um sinal para a interface principal com os parametros escolhidos.
void ModificarPorta::on_buttonBox_accepted()
{
  // Recupera os valores escolhidos pelo usuario
  QString tipoPort = ui->comboTipoPorta->currentText();
  int numInputsPort = ui->spinNumInputs->value();
  // Emite sinal com os parametros
  emit signModificarPorta(idPort, tipoPort, numInputsPort);
}
