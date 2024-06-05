#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TO-DO

- quando digitar um departamento que não existe , deve infromar 
- Adicionar system clears e system pause
- Editar prints de confirmação (Exemplo: Funcionario adicionado com sucesso)
- talvez adicionar tabela asc para acentos da lingua portuguesa

*/

// Definição das estruturas
typedef struct {
    int id;
    char nome[50];
} Departamento;

typedef struct {
    int id;
    char nome[50];
    float salario;
    int id_departamento;
} Funcionario;

/* Protótipos das funções
void cadastrarDepartamento();
void cadastrarFuncionario();
void listarDepartamentos();
void listarFuncionariosPorDepartamento();
void buscarFuncionarioPorID();
void removerFuncionario();
void salvarDepartamentos();
void carregarDepartamentos();
void salvarFuncionarios();
void carregarFuncionarios();
*/

// Vetores para armazenar dados em memória
Departamento departamentos[100];
Funcionario funcionarios[100];
int numDepartamentos = 0;
int numFuncionarios = 0;

int main() {
    carregarDepartamentos();
    carregarFuncionarios();
    int opcao;

    do {
        printf("\nMenu do Programa:\n");
        printf("1. Cadastrar departamento\n");
        printf("2. Cadastrar funcionário\n");
        printf("3. Listar departamentos\n");
        printf("4. Listar funcionários de um departamento\n");
        printf("5. Buscar funcionário por ID\n");
        printf("6. Remover funcionário\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarDepartamento();
                break;
            case 2:
                cadastrarFuncionario();
                break;
            case 3:
                listarDepartamentos();
                break;
            case 4:
                listarFuncionariosPorDepartamento();
                break;
            case 5:
                buscarFuncionarioPorID();
                break;
            case 6:
                removerFuncionario();
                break;
            case 7:
                salvarDepartamentos();
                salvarFuncionarios();
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}

void cadastrarDepartamento() {
    if (numDepartamentos >= 100) {
        printf("Número máximo de departamentos atingido!\n");
        return;
    }
    Departamento dept;
    printf("Digite o ID do departamento: ");
    scanf("%d", &dept.id);
    printf("Digite o nome do departamento: ");
    scanf("%s", dept.nome);
    departamentos[numDepartamentos++] = dept;
    printf("Departamento cadastrado com sucesso!\n");
}

void listarDepartamentos() {
    printf("\nLista de Departamentos:\n");
    for (int i = 0; i < numDepartamentos; i++) {
        printf("ID: %d, Nome: %s\n", departamentos[i].id, departamentos[i].nome);
    }
}
void cadastrarFuncionario() {
    if (numFuncionarios >= 100) {
        printf("Número máximo de funcionários atingido!\n");
        return;
    }
    Funcionario func;
    printf("Digite o ID do funcionário: ");
    scanf("%d", &func.id);
    printf("Digite o nome do funcionário: ");
    scanf("%s", func.nome);
    printf("Digite o salário do funcionário: ");
    scanf("%f", &func.salario);
    printf("Digite o ID do departamento: ");
    scanf("%d", &func.id_departamento);

    // Verificar se o departamento existe
    int departamentoExiste = 0;
    for (int i = 0; i < numDepartamentos; i++) {
        if (departamentos[i].id == func.id_departamento) {
            departamentoExiste = 1;
            break;
        }
    }

    if (!departamentoExiste) {
        printf("Departamento não encontrado!\n");
        return;
    }

    funcionarios[numFuncionarios++] = func;
    printf("Funcionário cadastrado com sucesso!\n");
}

void listarFuncionariosPorDepartamento() {
    int idDepartamento;
    printf("Digite o ID do departamento: ");
    scanf("%d", &idDepartamento);

    printf("\nFuncionários do Departamento %d:\n", idDepartamento);
    for (int i = 0; i < numFuncionarios; i++) {
        if (funcionarios[i].id_departamento == idDepartamento) {
            printf("ID: %d, Nome: %s, Salário: %.2f\n", funcionarios[i].id, funcionarios[i].nome, funcionarios[i].salario);
        }
    }
}

void buscarFuncionarioPorID() {
    int idFuncionario;
    printf("Digite o ID do funcionário: ");
    scanf("%d", &idFuncionario);

    for (int i = 0; i < numFuncionarios; i++) {
        if (funcionarios[i].id == idFuncionario) {
            printf("ID: %d, Nome: %s, Salário: %.2f, Departamento: %d\n",
                   funcionarios[i].id, funcionarios[i].nome, funcionarios[i].salario, funcionarios[i].id_departamento);
            return;
        }
    }
    printf("Funcionário não encontrado!\n");
}

void removerFuncionario() {
    int idFuncionario;
    printf("Digite o ID do funcionário que deseja remover: ");
    scanf("%d", &idFuncionario);

    for (int i = 0; i < numFuncionarios; i++) {
        if (funcionarios[i].id == idFuncionario) {
            for (int j = i; j < numFuncionarios - 1; j++) {
                funcionarios[j] = funcionarios[j + 1];
            }
            numFuncionarios--;
            printf("Funcionário removido com sucesso!\n");
            return;
        }
    }
    printf("Funcionário não encontrado!\n");
}
void salvarDepartamentos() {
    FILE *file = fopen("departamentos.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de departamentos para escrita!\n");
        return;
    }
    fwrite(departamentos, sizeof(Departamento), numDepartamentos, file);
    fclose(file);
}

void carregarDepartamentos() {
    FILE *file = fopen("departamentos.dat", "rb");
    if (file == NULL) {
        return; // Arquivo não existe ainda
    }
    numDepartamentos = fread(departamentos, sizeof(Departamento), 100, file);
    fclose(file);
}

void salvarFuncionarios() {
    FILE *file = fopen("funcionarios.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de funcionários para escrita!\n");
        return;
    }
    fwrite(funcionarios, sizeof(Funcionario), numFuncionarios, file);
    fclose(file);
}

void carregarFuncionarios() {
    FILE *file = fopen("funcionarios.dat", "rb");
    if (file == NULL) {
        return; // Arquivo não existe ainda
    }
    numFuncionarios = fread(funcionarios, sizeof(Funcionario), 100, file);
    fclose(file);
}
