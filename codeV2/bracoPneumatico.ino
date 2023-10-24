//CÓDIGO BRAÇO PNEUMÁTICO - AP ELETROMECÂNICA
//AUTOR: Lucas Eduardo Dias de Oliveira - SENAI CNV
//DATA: 04/10/2023

  /*Caro programador, quando eu escrevi este código, apenas eu e Deus sabíamos como ele
  deveria funcionar, hoje em dia apenas Deus sabe. Se for necessário fazer alguma alteração
  (que sem dúvidas é necessário), busque ler ele atentamente, toda a documentação e lógica
  está descrita abaixo, além disso, adicione suas horas de trabalho, somente como medida
  de controle para caso algum dia precise. Boa sorte!

  Total de horas gastas: 1h
   JUAREZ: 3H
  */

//ATENÇÃO: LEIA COM ATENÇÃO AS INSTRUÇÕES ABAIXO:


/*ATENÇÃO: MUDE SOMENTE A INSTRUÇÃO LOW/HIGH DE CADA CILINDRO/VENTOSA PARA DEFINIR QUAL DISPOSITIVO SERÁ ACIONADO:
 C1, C2, C3, VT DEVERÃO SER ANALISADO NO PROJETO FISICO PARA DEFINIR EM QUE PASSO ESTARÁ ACIONADO,
 O "TIME" CORRESPONDE AO TEMPO PARA A EXECUÇÃO DO PASSO (TEMPO EM mili segundos).

 Para definir os pinos físicos, basta alimentar o array "byte pinosSaida" (que se encontra abaixo), com as portas físicas
 do arduino, sendo respectivamente (C1, C2, C3, VT).

 O atual programa possui 15 possíveis passos para o braço, porém isso pode ser alterado,
 caso verifique que um desses passos não seja necessário, basta alterar o time correspondente
 ao passo para 0000.

 Para monitorar o que está acontecendo, basta abrir o monitor serial.
 

*/

//Quantidade de passos e componentes
#define passos 15
#define componentes 5 
 //                                         C1    C2    C3    VT   time
int operacao [passos] [componentes] = { {  LOW,  LOW,  HIGH, HIGH, 4000}, //PASSO 0 - ZERO MÁQUINA
                                        {  LOW,  LOW,  HIGH, LOW,  4000}, //PASSO 1
                                        {  LOW,  LOW,  LOW,  LOW,  4000}, //PASSO 2
                                        {  LOW,  HIGH, LOW,  LOW,  4000}, //PASSO 3
                                        {  HIGH, HIGH, LOW,  LOW,  4000}, //PASSO 4
                                        {  HIGH, HIGH, HIGH, LOW,  4000}, //PASSO 5
                                        {  HIGH, HIGH, HIGH, HIGH, 4000}, //PASSO 6
                                        {  HIGH, HIGH, LOW,  HIGH, 4000}, //PASSO 7
                                        {  HIGH, LOW,  LOW,  HIGH, 4000}, //PASSO 8
                                        {  LOW,  LOW,  LOW,  HIGH, 4000}, //PASSO 9
                                        {  LOW,  LOW,  HIGH, HIGH, 4000}, //PASSO 10
                                        {  LOW,  LOW,  LOW,  LOW,  0000}, //PASSO 11
                                        {  LOW,  LOW,  LOW,  LOW,  0000}, //PASSO 12
                                        {  LOW,  LOW,  LOW,  LOW,  0000}, //PASSO 13
                                        {  LOW,  LOW,  LOW,  LOW,  0000}}; //PASSO 14

//                      C1 C2 C3 VT
byte pinosSaidas [4] = { 3, 4, 5, 6};

void setup() {

  //Definir portas como saídas
  for(byte x=0; x<sizeof(pinosSaidas)/sizeof(pinosSaidas[0]);x++){
    pinMode(pinosSaidas[x], OUTPUT);
    digitalWrite(pinosSaidas[x], operacao[0][x]);
    delay(10);
  }

  //Inicializar comunicação serial
  Serial.begin(9600);
}

void loop() {
  //A passagem entre movimentação do braço, é definida através do "time" de cada passo
  for(byte y=0;(y<passos);y++){
    for(byte x=0;x<(componentes-1);x++){
      digitalWrite(pinosSaidas[x],operacao[y][x]);
      Serial.print(" Cmp:" + String(x) + " sta:" + String(operacao[y][x]));      
    }
    Serial.print(" pass:" + String(y));
    Serial.print("\n");
    delay(operacao[y][4]);
}
}
