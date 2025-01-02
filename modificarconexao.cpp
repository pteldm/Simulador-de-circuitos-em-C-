#include "modificarconexao.h"
#include "ui_modificarconexao.h"
#include <QPushButton>

ModificarConexao::ModificarConexao(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ModificarConexao),
  idPort(0)
{
  ui->setupUi(this);

  // Desabilita todos os widgets das entradas 1, 2, 3 e 4
  ui->labelInput1->setEnabled(false);
  ui->spinInput1->setEnabled(false);
  ui->labelInput2->setEnabled(false);
  ui->spinInput2->setEnabled(false);
  ui->labelInput3->setEnabled(false);
  ui->spinInput3->setEnabled(false);
  ui->labelInput4->setEnabled(false);
  ui->spinInput4->setEnabled(false);

  testa_entradas_validas();
}

ModificarConexao::~ModificarConexao()
{
  delete ui;
}

// Fixa o limite inferior (-numInputs) e superior (numPortas)
// dos spinBoxs que sao usados para indicar a origem das entradas das portas.
// Deve ser chamado cada vez que definir um novo circuito.
void ModificarConexao::fixarLimites(int minimo, int maximo)
{
  ui->spinInput1->setRange(minimo,maximo);
  ui->spinInput2->setRange(minimo,maximo);
  ui->spinInput3->setRange(minimo,maximo);
  ui->spinInput4->setRange(minimo,maximo);
}

// Adapta a janela ao numero de entradas da porta cujas conexoes estao sendo modificadas.
// Fixa os valores iniciais, de acordo com os valores atuais.
// Depois exibe (show) a janela de modificar conexoes.
void ModificarConexao::exibir(int IdPort, int NumInputs,
                              int IdInput1, int IdInput2, int IdInput3, int IdInput4)
{
  // Armazena a id da porta que estah sendo modificada
  idPort = IdPort;
  // Altera o label de exibicao da janela
  ui->labelIdPorta->setNum(idPort);

  // Conexao da entrada 1
  // Sempre habilitada
  ui->labelInput1->setEnabled(true);
  ui->spinInput1->setEnabled(true);
  ui->spinInput1->setValue(IdInput1);
  // Como a origem (id) da entrada foi alterada, chama on_spinInput1_valueChanged

  // Conexao da entrada 2
  // Habilitada se porta tiver 2 ou mais entradas
  if (NumInputs<2)
  {
    ui->labelInput2->setEnabled(false);
    ui->spinInput2->setEnabled(false);
    ui->spinInput2->setValue(0);
  }
  else
  {
    ui->labelInput2->setEnabled(true);
    ui->spinInput2->setEnabled(true);
    ui->spinInput2->setValue(IdInput2);
    // Como a origem (id) da entrada foi alterada, chama on_spinInput2_valueChanged
  }

  // Conexao da entrada 3
  // Habilitada se porta tiver 3 ou mais entradas
  if (NumInputs<3)
  {
    ui->labelInput3->setEnabled(false);
    ui->spinInput3->setEnabled(false);
    ui->spinInput3->setValue(0);
  }
  else
  {
    ui->labelInput3->setEnabled(true);
    ui->spinInput3->setEnabled(true);
    ui->spinInput3->setValue(IdInput3);
    // Como a origem (id) da entrada foi alterada, chama on_spinInput3_valueChanged
  }

  // Conexao da entrada 4
  // Habilitada se porta tiver 3 ou mais entradas
  if (NumInputs<4)
  {
    ui->labelInput4->setEnabled(false);
    ui->spinInput4->setEnabled(false);
    ui->spinInput4->setValue(0);
  }
  else
  {
    ui->labelInput4->setEnabled(true);
    ui->spinInput4->setEnabled(true);
    ui->spinInput4->setValue(IdInput4);
    // Como a origem (id) da entrada foi alterada, chama on_spinInput3_valueChanged
  }

  // Exibe a janela
  show();
}

// Testa se a origem (id) do sinal de alguma das entradas da porta tem valor invalido (zero)
// e se a entrada estah habilitada; se for o caso, desabilita o botao OK
void ModificarConexao::testa_entradas_validas(void)
{
  bool entradas_validas = (ui->spinInput1->value() != 0);
  if (entradas_validas)
  {
    entradas_validas = (ui->spinInput2->value()!=0 || !ui->spinInput2->isEnabled());
  }
  if (entradas_validas)
  {
    entradas_validas = (ui->spinInput3->value()!=0 || !ui->spinInput3->isEnabled());
  }
  if (entradas_validas)
  {
    entradas_validas = (ui->spinInput4->value()!=0 || !ui->spinInput4->isEnabled());
  }
  // Recupera um ponteiro para o botao OK
  QPushButton *botao_ok = ui->buttonBox->button(QDialogButtonBox::Ok);
  // Habilita/desabilita o botao OK
  botao_ok->setEnabled(entradas_validas);
}

// Quando modifica a conexao de alguma entrada da porta, verifica se a configuracao
// eh valida ou nao para habilitar ou nao o botao OK
void ModificarConexao::on_spinInput1_valueChanged(int)
{
  testa_entradas_validas();
}

void ModificarConexao::on_spinInput2_valueChanged(int)
{
  testa_entradas_validas();
}

void ModificarConexao::on_spinInput3_valueChanged(int)
{
  testa_entradas_validas();
}

void ModificarConexao::on_spinInput4_valueChanged(int)
{
  testa_entradas_validas();
}

// Apos OK, altera as conexoes de entrada da porta "idPorta".
// Deve emitir um sinal para a interface principal com os parametros escolhidos.
void ModificarConexao::on_buttonBox_accepted()
{
  // Recupera os valores escolhidos pelo usuario
  int idInputPort[] = {ui->spinInput1->value(),
                       ui->spinInput2->value(),
                       ui->spinInput3->value(),
                       ui->spinInput4->value()};
  // Emite sinal com os parametros
  emit signModificarConexao(idPort, idInputPort[0], idInputPort[1], idInputPort[2], idInputPort[3]);
}
