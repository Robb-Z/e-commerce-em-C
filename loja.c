#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Funcoes
void BuscaProdutos(void);
void PlanoFidelidade(void);
void LoginCadastro(void);
void EntreContato(void);
void ExibirEstoque(void);
void PausarElimpar(void);
void Pausar(void);
void Limpar(void);

//Variaveis globais
int selcMenu, repetir = 1, logado = 0, fidelidade = 0, quantAdicional = 0, quantCompra, cadastro = 0;

struct Conta {
  char usuario[50];
  char nome[100];
  char email[100];
  int telefone;
  int senha;
  int idade;
};


struct Conta cliente;

//Estoque add
struct Adicional {
  char nomeItem[50];
  float valor;
  int estoque;
  int posicao;
};

struct Adicional estoqueAdicional[10];

//Estoque

  int estoque[6] = {10, 20, 50, 33, 55, 150};
  float valor[6] = {25.60, 26.30, 120.00, 50.99, 25.30, 60.50};

//programa inicio
int main(void) {
	setlocale(LC_ALL, "Portuguese");

  do {
    printf("\n\t\tREUSA CLOTHING - Consciente e Sustentável!\n\n");
    printf("\t\tEscolha uma das opções abaixo:\n");
    printf("\t1 -> Produtos REUSE\n");
    printf("\t2 -> Plano fidelidade\n");
    printf("\t3 -> Fazer login ou cadastro\n");
    printf("\t4 -> Entre em contato\n");
    printf("\t5 -> Sair\n");
    scanf("%d", &selcMenu);

    switch(selcMenu) {
      case 1:
        printf("\nEscolha\n\n"); 
        printf("\nAdministrar estoque(1) ou Comprar(2)\n\n"); 
        scanf("%d", &selcMenu);

        if(selcMenu == 1) {
          //estoque add
          Limpar();
          printf("\nQuantos itens deseja adicionar ao estoque?\n\n"); 
          scanf("%d", &quantAdicional);

          for(int i = 0; i < quantAdicional; i++) {
            printf("\n----------------------------------------\n"); 
            printf("\t\tITEM ADICIONAL %d", i + 1); 
            printf("\n----------------------------------------\n"); 

            estoqueAdicional[i].posicao = (i + 1) + 6;

            printf("\nQual nome do produto? (50 Caracteres max.)\n"); 
            scanf(" %[^\n]s", estoqueAdicional[i].nomeItem);
            printf("\nQual valor do produto %s?\n", estoqueAdicional[i].nomeItem); 
            scanf("%f", &estoqueAdicional[i].valor);
            printf("\nQual o estoque do produto %s?\n", estoqueAdicional[i].nomeItem); 
            scanf("%d", &estoqueAdicional[i].estoque);
          }
          printf("\nProdutos adicionados com sucesso ao estoque!!\n"); 
          printf("Retornando ao menu principal!!\n");
          PausarElimpar();
          //Aqui tinha um return 
          //ta funcionando sem
        } else {
          Limpar();
          printf("\nESCOLHA PRODUTOS PARA COMPRAR\n\n"); 

          ExibirEstoque();

          if (quantAdicional != 0) {
            for(int i = 0; i < quantAdicional; i++) {
                printf("\n\t#%d %s\n", estoqueAdicional[i].posicao, estoqueAdicional[i].nomeItem); 
                printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", estoqueAdicional[i].valor, estoqueAdicional[i].estoque); 
            }
          }

          printf("\nGostaria de comprar?"); 
          printf("(Digite quantos itens quer comprar ou 0 para retornar ao menu)\n"); 
          scanf("%d", &quantCompra);

          if(quantCompra == 0) {
            printf("\nRetornando ao menu!!\n"); 
            PausarElimpar();
            break;
            //Aqui tinha um return
            //substitui por break 
          }

          int produtoSelec[quantCompra + 1];
          int quantProduto[quantCompra + 1];

          for(int i = 0; i < quantCompra; i++) {
            int repetirAtual;
            do {
              repetirAtual = 0;
              printf("\nPedido #%d\n", i+1); 
              printf("Qual produto você quer comprar? (Digite o numero do item)\n");
              scanf("%d", &produtoSelec[i]);

              if(produtoSelec[i] <= 6 && produtoSelec[i] >= 1 ) {
                //Prod padrao
                printf("Qual a quantidade desse produto? (Digite a quantidade do item)\n"); 
                scanf("%d", &quantProduto[i]);

                if(quantProduto[i] > estoque[produtoSelec[i] - 1]) {
                  printf("\n--------------------------------------------------------------------\n"); 
                  printf("Você pediu mais do que temos no estoque, repetindo pedido atual...\n"); 
                  printf("--------------------------------------------------------------------\n"); 
                  repetirAtual = 1;
                }
              } else if (produtoSelec[i] > 6 && produtoSelec[i] <= quantAdicional + 6) {
                //Prod adicionais
                  printf("Qual a quantidade desse produto? (Digite a quantidade do item)\n"); 
                  scanf("%d", &quantProduto[i]);

                  if(quantProduto[i] > estoqueAdicional[produtoSelec[i] - 7].estoque) {
                    printf("\n--------------------------------------------------------------------\n"); 
                    printf("Você pediu mais do que temos no estoque, repetindo pedido atual...\n"); 
                    printf("--------------------------------------------------------------------\n"); 
                    repetirAtual = 1;
                  }
              } else {
                  printf("\n--------------------------------------------------------------------\n"); 
                  printf("Você pediu um item que não existe, repetindo pedido atual...\n"); 
                  printf("--------------------------------------------------------------------\n"); 
                  repetirAtual = 1;
              }
            } while (repetirAtual == 1);
          }
          
          Limpar();
          ExibirEstoque();

          if (quantAdicional != 0) {
            for(int i = 0; i < quantAdicional; i++) {
                printf("\n\t#%d %s\n", estoqueAdicional[i].posicao, estoqueAdicional[i].nomeItem); 
                printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", estoqueAdicional[i].valor, estoqueAdicional[i].estoque); 
            }
          }

          printf("\nVocê escolheu os seguintes itens:\n");  
          for(int i = 0; i < quantCompra; i++) {
            printf("%d ", produtoSelec[i]);     
          }
          printf("\n\nVocê escolheu esses itens com as seguintes quantidades:\n");  
          for(int i = 0; i < quantCompra; i++) {
            printf("%d ", quantProduto[i]);     
          }

          printf("\n\nSeu carrinho de compras está com valor atual de:\n"); 
          float carrinhoCompras = 0.0;
          for(int i = 0; i < quantCompra; i++) {

            if(produtoSelec[i] <= 6) {
              carrinhoCompras += (valor[produtoSelec[i]-1] * quantProduto[i]); //O -1 ta nessa posicao pq o item na array é -1 em relacao ao menu visual do estoque.
            } else {
              carrinhoCompras += (estoqueAdicional[produtoSelec[i] - 7].valor * estoqueAdicional[produtoSelec[i] - 7].estoque);
            }
          }
          printf("\nR$%.2f\n", carrinhoCompras);  
          Pausar();
          
          if(fidelidade == 1) {
            float desconto = carrinhoCompras * 0.15;
            carrinhoCompras -= desconto;
            printf("\nComo você é assinante do nosso plano de fidelidade\n");  
            printf("\nVocê tem 15%% de desconto nessa compra!!\n");  
            printf("\nEntão seu carrinho de compras tem um desconto de: %.2f\n", desconto);  
          }
          printf("\n\nSeu carrinho com desconto fica:\n"); 
          printf("\nR$%.2f\n", carrinhoCompras);  

          printf("\nConfirmar compra? (1 -> Sim - 2 -> Não)\n");  
          scanf("%d", &selcMenu);

          if(selcMenu == 2) {
            printf("\nCompra cancelada!! Retornando ao menu!\n");
            PausarElimpar();
            break;
            //Aqui tinha um return
            //substitui por break      
          }

          printf("\n\n\tATENCAO\n");  
          printf("\nPara concluir precisamos verificar seu login! -- REDIRECIONANDO PARA O LOGIN\n");  
          LoginCadastro();

          Limpar();
          printf("\nCompra realizada com sucesso!!\n");  
          printf("\nItens removidos do estoque!\n\n");

          for(int i = 0; i < quantCompra; i++) {
            if(produtoSelec[i] <= 6){
              estoque[produtoSelec[i] - 1] -= quantProduto[i];
            } else {
              estoqueAdicional[produtoSelec[i] - 7].estoque -= quantProduto[i];
            }
          }

          printf("\n\tEstoque atualizado:\n\n");  
          ExibirEstoque();
          if (quantAdicional != 0) {
            for(int i = 0; i < quantAdicional; i++) {
                printf("\n\t#%d %s\n", estoqueAdicional[i].posicao, estoqueAdicional[i].nomeItem); 
                printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", estoqueAdicional[i].valor, estoqueAdicional[i].estoque); 
            }
          }
          printf("\nPressione qualquer tecla para retornar ao menu!\n\n");  
          PausarElimpar();
          //Aqui tinha um return 
          //funciona sem!
          }
      break;
      case 2:
        PlanoFidelidade();
      break;
      case 3:
        LoginCadastro();
      break;
      case 4:
        EntreContato();
      break;
      case 5:
        printf("\n\nFECHANDO O PROGRAMA...\n\n"); 
        Pausar();
        return 0;
      break;
      default:
        printf("\nVocê digitou %d e isso é uma opção invalida\n", selcMenu); 
        PausarElimpar();
        repetir = 1;
      break;
    }
  } while (repetir == 1);
  return 0;
}
//Programa fim 

void PlanoFidelidade(void) {
  printf("\nPLANO FIDELIDADE\n");
  printf("\tVerificando login...\n");
  LoginCadastro();
  if(fidelidade == 0) {
    printf("\tVocê não assinou nosso plano fidelidade ainda!!\n");
    printf("\tCom nosso plano fidelidade por R$ 89.88\n\n");
    printf("\tvocê ganha 15%% de desconto em todo site\n");
    printf("\t4 peças de roupa por mês\n");
    printf("\tPlante uma árvore na amazônia\n");
    printf("\tFrete gratuito\n");
    printf("\tGostaria de assinar nosso plano? (1 -> Sim / 2 -> Não)\n");
    scanf("%d", &selcMenu);
    if (selcMenu == 1) {
      fidelidade = 1;
      printf("\tPlano de fidelidade assinado com sucesso!!\n");
      printf("\tAproveite todos nossos produtos com desconto!! -- RETORNANDO\n");
    } else {
      printf("\tPoxa você escolheu não assinar nosso plano! Fica para próxima.. -- RETORNANDO\n");
    }
  } else {
    printf("\tVocê já assinou nosso plano fidelidade!!\n");
    printf("\tGostaria de voltar ao menu e comprar com descontos ou cancelar o plano?\n");
    printf("\t(1 -> Voltar / 2 -> Cancelar plano)\n");
    scanf("%d", &selcMenu);
    if(selcMenu == 2) {
      fidelidade = 0;
      printf("\tSeu plano fidelidade foi cancelado!!\n");
    } else {
      printf("\tRETORNANDO\n");
    }
  }
  PausarElimpar();
  repetir = 1;
  return;

}

void LoginCadastro(void) {
  int menu, repetirLogin = 0;
  do {

    if (selcMenu == 3) {
      printf("\n\t\tLOGIN OU CADASTRO\n");
    }

    if(logado == 0) {
      printf("\tVocê não está logado!\n");
      printf("\tVocê gostaria de se cadastrar ou fazer login?\n");
      printf("\n\tLogin -> 1\n");
      printf("\n\tCadastro -> 2\n");
      scanf("%d", &menu);

      switch(menu) {
        case 1:
          printf("\tVocê selecionou: LOGIN\n");
          printf("Digite seu usuário:\n");
          scanf(" %[^\n]s", cliente.usuario);
          printf("Digite sua senha (APENAS NÚMEROS):\n");
          scanf("%d", &cliente.senha);
          Limpar();
          if(cadastro == 0) {
            printf("Usuário não encontrado na base de dados!! -- RETORNANDO\n");
            repetirLogin = 1;
          } else {
            printf("Login realizado com sucesso!! -- RETORNANDO\n");
            logado = 1;
            return; 
          }         
        break;
        case 2:
          printf("\tVocê selecionou: CADASTRO\n");
          printf("Digite seu usuario:\n");
          scanf(" %[^\n]s", cliente.usuario);
          printf("Digite sua senha, use APENAS números:\n");
          scanf("%d", &cliente.senha);
          printf("Digite seu nome completo\n");
          scanf(" %[^\n]s", cliente.nome);
          printf("Digite sua idade\n");
          scanf("%d", &cliente.idade);        
          printf("Digite seu e-mail:\n");
          scanf(" %[^\n]s", cliente.email);
          printf("Digite seu telefone:\n");
          scanf("%d", &cliente.telefone);

          printf("\n\nCadastro realizado com sucesso!! -- RETORNANDO\n");

          printf("\tSeu nome: %s\n", cliente.nome);
          printf("\tSeu usuario: %s\n", cliente.usuario);
          printf("\tSua e-mail: %s\n", cliente.email);
          printf("\tSua telefone: %d\n", cliente.telefone);
          printf("\tSua idade: %d\n", cliente.idade);
          printf("\tSua senha: %d\n", cliente.senha);
          cadastro = 1;
          logado = 1;
          PausarElimpar();
          return;
        break;
        default:
          printf("\nVocê digitou %d e isso é uma opção invalida\n", selcMenu); 
          Pausar();
          repetirLogin = 1;
        break;
      }
    } else {
      printf("\nVocê já está logado no sistema!!\n\n");
      printf("\nDeseja fazer logout? (1 -> Sim - 2 -> Nao)\n"); 
      scanf("%d", &selcMenu);
      if (selcMenu == 1) {
        logado = 0;
        printf("\nVocê está deslogado!! -- RETORNANDO\n"); 
        PausarElimpar();
      } else {
        printf("\nVocê ainda está logado!! -- RETORNANDO\n");
        PausarElimpar();
      }
      repetirLogin = 0;
    }
  } while (repetirLogin == 1);
  return;
}

void EntreContato(void) {
  char mensagem[201];
  printf("\t\t\nENTRE EM CONTATO\n\n"); 

  printf("\nMensagem: (200 Caracteres no máximo)\n"); 
  scanf(" %[^\n]s", mensagem);

  if (logado == 1) {
    printf("-----------------------------------------\n\n");
    printf("Nome: %s\n", cliente.nome);
    printf("Usuário: %s\n", cliente.usuario);
    printf("Idade: %d\n", cliente.idade);
    printf("E-mail: %s\n", cliente.email);
    printf("Telefone: %d\n", cliente.telefone);
    printf("Mensagem:\n\n");
    printf("%s", mensagem);
    printf("\n-----------------------------------------");
    printf("\n\nMensagem emviada!!:\n\n");
  } else {
    printf("Digite os seguintes dados antes de enviar a mensagem:\n");
    printf("Nome:\n");
    scanf(" %[^\n]s", cliente.nome);
    printf("Idade:\n");
    scanf("%d", &cliente.idade);
    printf("E-mail:\n");
    scanf(" %[^\n]s", cliente.email);
    printf("Telefone:\n");
    scanf("%d", &cliente.telefone);
    Limpar();
    printf("-----------------------------------------");
    printf("Nome: %s\n", cliente.nome);
    printf("Usuário: %s\n", cliente.usuario);
    printf("Idade: %d\n", cliente.idade);
    printf("E-mail: %s\n", cliente.email);
    printf("Telefone: %d\n", cliente.telefone);
    printf("Mensagem:\n\n");
    printf("%s", mensagem);
    printf("\n\n-----------------------------------------");
    printf("\n\nMensagem emviada!!:\n\n");
  }

  PausarElimpar();
}

void ExibirEstoque(void) {
  printf("\n\t#1 Camisa Fibra Têxtil\n"); 
  printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", valor[0], estoque[0]); 

  printf("\n\t#2 Blusa Social Fibra Têxtil\n"); 
  printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", valor[1], estoque[1]); 

  printf("\n\t#3 Mochila Big-Kong\n"); 
  printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", valor[2], estoque[2]); 

  printf("\n\t#4 Camiseta sem manga\n"); 
  printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", valor[3], estoque[3]); 

  printf("\n\t#5 Camisa Vermelha Fibra Têxtil\n"); 
  printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", valor[4], estoque[4]); 

  printf("\n\t#6 Camisa Azul Fibra Têxtil\n"); 
  printf("\tValor: R$%.2f -- Quantidade em estoque: %d\n", valor[5], estoque[5]); 
}

//Outras Funcoes

void PausarElimpar(void) {
  system("pause");
  system("cls");
  return;
}

void Pausar(void) {
  system("pause");
  return;
}

void Limpar(void) {
  system("cls");
  return;
}