#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
	int codigo;
	char nome[30];
	float preco;
} Produto;

typedef struct {
	Produto produto;
	int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void comprarProduto();
void listarProdutos();
void vizualizarCarrinho();
Produto PegarProdutoPorCodigo(int codigo);
int* temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];

int main() {

	menu();

	return 0;
}

void infoProduto(Produto prod) {
	printf("Código: %d \nNome: %s \nPreço: %.2f\n", prod.codigo,
			strtok(prod.nome, "\n"), prod.preco);
}

void menu() {
	printf("================================================\n");
	printf("================= Bem-vindo(a) =================\n");
	printf("===================== Shop =====================\n");
	printf("================================================\n");

	printf("Selecione uma opção abaixo: \n");
	printf("[1] - Cadastrar produto\n");
	printf("[2] - Listar produto\n");
	printf("[3] - Comprar produto\n");
	printf("[4] - Vizualizar carrinho\n");
	printf("[5] - Fechar pedido\n");
	printf("[6] - Sair\n");

	int opcao;
	fflush(stdout);
	scanf("%d", &opcao);
	getchar();

	switch (opcao) {
	case 1:
		cadastrarProduto();
		break;
	case 2:
		listarProdutos();
		break;
	case 3:
		comprarProduto();
		break;
	case 4:
		vizualizarCarrinho();
		break;
	case 5:
		fecharPedido();
		break;
	case 6:
		printf("Volte Sempre!\n");
		Sleep(2);
		exit(0);
	default:
		printf("Opção inválida.\n");
		Sleep(2);
		menu();
	}
}

void cadastrarProduto() {
	printf("Cadastro de produto\n");
	printf("===================\n");

	printf("Informe o nome do produto: \n");
	fflush(stdout);
	fgets(produtos[contador_produto].nome, 30, stdin);

	printf("Informe o preço do produto: \n");
	fflush(stdout);
	scanf("%f", &produtos[contador_produto].preco);

	printf("O produto %s foi cadastrado com sucesso!\n", strtok(produtos[contador_produto].nome, "\n"));

	produtos[contador_produto].codigo = (contador_produto + 1);
	contador_produto++;

	Sleep(2);
	menu();
}

	void listarProdutos() {
		if (contador_produto > 0) {
			printf("Listagem de produtos.\n");
			printf("---------------------\n");
			for (int i = 0; i < contador_produto; i++) {
				infoProduto(produtos[i]);
				printf("---------------------\n");
				Sleep(1);
			}
			Sleep(2);
			menu();
		} else {
			printf("Ainda não temos produtos cadastrados.\n");
			Sleep(2);
			menu();
		}
	}

	void comprarProduto() {
		if (contador_produto > 0) {
			printf("Informe o código do produto para adicionar ao carrinho.\n");

			printf("=============== Produtos disponíveis ===============\n");
			for (int i = 0; i < contador_produto; i++) {
				infoProduto(produtos[i]);
				printf("---------------------\n");
				Sleep(1);
			}
			int code;
			fflush(stdout);
			scanf("%d", &code);
			getchar();

			int temMercado = 0;
			for (int i = 0; i < contador_produto; i++) {
				if (produtos[i].codigo == code) {
					temMercado = 1;

					if (contador_carrinho > 0) {
						int *retorno = temNoCarrinho(code);

						if (retorno[0] == 1) {
							carrinho[retorno[1]].quantidade++;
							printf(
									"Aumentei a quantidade do produto %s já existente no carrinho."
											"\n",
									strtok(carrinho[retorno[1]].produto.nome,
											"\n"));
							Sleep(2);
							menu();
						} else {
							Produto p = PegarProdutoPorCodigo(code);
							carrinho[contador_carrinho].produto = p;
							carrinho[contador_carrinho].quantidade = 1;
							contador_carrinho++;
							printf("O produto %s foi adicionado ao carrinho.\n",
									strtok(p.nome, "\n"));
							Sleep(2);
							menu();
						}
					} else {
						Produto p = PegarProdutoPorCodigo(code);
						carrinho[contador_carrinho].produto = p;
						carrinho[contador_carrinho].quantidade = 1;
						contador_carrinho++;
						printf("O produto %s foi adicionado ao carrinho.\n",
								strtok(p.nome, "\n"));
						Sleep(2);
						menu();
					}

				}
			}

			if (temMercado < 1) {
				printf("Não foi encontrado o produto com código %d.\n", code);
				Sleep(2);
				menu();
			}

		} else {
			printf("Ainda não existem produtos para vender.\n");
			Sleep(2);
			menu();
		}
	}

	void vizualizarCarrinho() {
		if (contador_carrinho > 0) {
			printf("Produtos do carrinho\n");
			printf("---------------------\n");
			for (int i = 0; i < contador_carrinho; i++) {
				infoProduto(carrinho[i].produto);
				printf("Quantidade: %d\n", carrinho[i].quantidade);
				printf("---------------------\n");
				Sleep(1);
			}
			Sleep(2);
			menu();
		} else {
			printf("Ainda não temos produtos no carrinho.\n");
			Sleep(2);
			menu();
		}
	}

	Produto PegarProdutoPorCodigo(int codigo) {
		Produto p;
		for (int i = 0; i < contador_produto; i++) {
			if (produtos[i].codigo == codigo) {
				p = produtos[i];
			}
		}
		return p;
	}

	int* temNoCarrinho(int codigo) {
		int static retorno[] = { 0, 0 };
		for (int i = 0; i < contador_carrinho; i++) {
			if (carrinho[i].produto.codigo == codigo) {
				retorno[0] = 1;
				retorno[1] = i;
			}
		}
		return retorno;
	}

	void fecharPedido() {
		if (contador_carrinho > 0) {
			float valorTotal = 0.0;
			printf("Produtos do carrinho\n");
			printf("---------------------\n");
			for (int i = 0; i < contador_carrinho; i++) {
				Produto p = carrinho[i].produto;
				int qtd = carrinho[i].quantidade;
				valorTotal += p.preco * qtd;
				infoProduto(p);
				printf("Quantidade = %d\n", qtd);
				printf("---------------------\n");
				Sleep(1);
			}
			printf("Sua fatura é R$%.2f.\n", valorTotal);

			contador_carrinho = 0;
			printf("Obrigado pela preferência!\n");
			Sleep(5);
			menu();
		} else {
			printf("Você ainda não possui nenhum produto no carrinho.\n");
			Sleep(3);
			menu();
		}
	}
