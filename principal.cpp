// Davi Alves Carvalho
// Tema: Compositores Clássicos
// Método de Busca a ser utilizado: Busca Binária
// Método de ordenação a ser utilizado: Selection Sort
// Modo de gravação Texto

#include <iostream>
#include <fstream>
using namespace std;

struct comp_classicos
// Registro a ser utilizado
{
    int identificador, anoNascimento;
    string nome, estilo, principalObra;


};


void selectionSort(comp_classicos vetor[], int tam)
// Método de Ordenação
//Do lado esquerdo do vetor, a partir de uma posição de referência, vai-se montando um conjunto ordenado
// A cada passo, o menor elemento do lado direito é trazido para o final do conjunto ordenado do lado esquerdo.
{


    for(int i =0; i<tam-1; i++)
    {
        int anterior = i;
        for(int j=i+1; j<tam; j++)
        {
            if(vetor[j].identificador<vetor[anterior].identificador)
                anterior=j;
        }
        comp_classicos aux = vetor[anterior];
        vetor[anterior]=vetor[i];
        vetor[i] = aux;
    }
}

int BuscaBinaria(comp_classicos vetor[], int pos_inicial, int pos_final, int K)
// Método de Busca
// A estrutura apresentada vai“quebrando” o vetor ao meio, a cada iteração, e verifica-se em qual metade pode estar o valor procurado.
// Repete-se o processo até que o vetor de busca tenha tamanho 1, sendo encontrado ou não o elemento de interesse.
// Esse subprogama requer que o vetor tenha pelo menos 1 item.
{
    int meio = (pos_inicial + pos_final)/2;

    if (K == vetor[meio].identificador)   //caso base: elemento encontrado
    {
        return meio;
    }
    else if (pos_inicial < pos_final)   //caso geral: processo de busca
    {
        if (vetor[meio].identificador < K) return BuscaBinaria(vetor, meio+1, pos_final, K);
        else return BuscaBinaria(vetor, pos_inicial, meio-1, K);
    }
    else     //caso base: elemento não encontrado
    {
        return -1;

    }
}


bool existe(int id, comp_classicos vetor[], int tam)
//Ordena o vetor e verifica se um item existe no vetor, fazendo busca no campo "identificador" nos registros. ´

{
    if (tam != 0)
    {
        selectionSort(vetor,tam);
        int posicao = BuscaBinaria(vetor,0,tam-1,id);
        if (posicao != -1)
            return true;
        else
            return false;
    }
    return false;

}

void incluir (comp_classicos vetor[], int &tam, int qtd)
// Procedimento responsável pela inserção de dados
{

    cout << "Insira a quantidade de registros que voce deseja inserir: ";
    cin >> qtd;
    cout << "Os identificadores devem ser diferentes para cada registro" <<endl;

    int aux = tam + qtd;
    for (int i=tam; i<aux; i++)
    {
        cout << endl;
        cout << "Insira o seu identificador (apenas numeros): ";
        cin >> vetor[i].identificador;
        while (existe(vetor[i].identificador, vetor, tam))
        {
            cout << "Esse identificador ja existe, insira outro: ";
            cin >> vetor[i].identificador;
        }
        cout << "Insira o nome do compositor: ";
        cin.ignore();
        getline(cin,vetor[i].nome);
        cout << "Insira o ano de nascimento do compositor: ";
        cin >> vetor[i].anoNascimento;
        cout << "Insira o estilo da obra do compositor: ";
        cin.ignore();
        getline(cin,vetor[i].estilo);
        cout << "Insira a principal obra do compositor: ";
        getline(cin,vetor[i].principalObra);
        cout << endl;
        cout << "Registro Incluido com Sucesso" << endl;
        tam++;
    }
    if (tam == 100)
    {
        cout << "Não é possível inserir novo registro" << endl;
    }
}

void excluir(comp_classicos vetor[], int &tam, int pos)
// Procedimento para exclusão de um registro
// A estrutura busca o valor do campo identificador igual ao informado pelo usuário
// Em seguida desloca os elementos do vetor à sua direita para ocupar sua posição.
{
    for(int j=pos; j<tam; j++)
    {
        vetor[j] = vetor[j+1];
    }
    tam--;
    cout << "Registro Excluido com Sucesso" <<endl;
}
void listar (comp_classicos vetor[], int tam)
// Procedimento para listar os registros
// É feito a ordenação através do selection sort
// Em seguida é feita a impressão do número de registros e de cada campo
{
    cout << endl << "Numero de Registros:" << tam << endl;
    selectionSort(vetor,tam);
    for(int i=0; i < tam; i++)
    {
        cout << endl << "Identificador:" << vetor[i].identificador << endl;
        cout << "Nome do Compositor:" << vetor[i].nome << endl;
        cout << "Ano de nascimento:" << vetor[i].anoNascimento << endl;
        cout << "Estilo de obra:" << vetor[i].estilo << endl;
        cout << "Principal obra:" << vetor[i].principalObra << endl;
    }
}


void  alterar (comp_classicos vetor[], int tam)
// Procedimento para alterar um campo do registro (com exceção do Identificador)
// É realizada a busca binária com o identificador do registro a ser alterado , que é armazenada na variável "Posição"
// Se o identificador existir(for diferente de -1) é feito a alteração, através de uma subscrição do campo escolhido.
{
    int id;
    cout << "Digite o identificador do registro que deseja alterar: ";
    cin >> id;
    cout <<endl;
    selectionSort(vetor,tam);
    int posicao = BuscaBinaria(vetor,0,tam-1,id);
    if (posicao == -1)
    {
        cout << "Registro nao encontrado" <<endl;
    }
    if (posicao != -1)
    {

        int buscaCampo;
        cout << "Qual campo voce deseja alterar? ((1) Nome, (2) Ano de nascimento, (3) Estilo ou (4) Principal Obra)"
             << endl << "Digite o numero equivalente ao campo escolhido: ";
        cin >> buscaCampo;

        if (buscaCampo == 1)
        {
            cout << "Escolha um novo nome: ";
            cin.ignore();
            getline(cin,vetor[posicao].nome);

        }
        if (buscaCampo == 2)
        {
            cout << "Escolha o novo ano de nascimento: ";
            cin >> vetor[posicao].anoNascimento;
        }
        if (buscaCampo == 3)
        {
            cout << "Escolha o novo estilo musical: ";
            cin.ignore();
            getline(cin,vetor[posicao].estilo);


        }
        if (buscaCampo == 4)
        {
            cout << "Escolha a nova principal obra: ";
            cin.ignore();
            getline(cin,vetor[posicao].principalObra);

        }

        cout << "Registro alterado com sucesso" << endl;
    }
}

void GravarDados (comp_classicos vetor[],int tam)
// Procedimento de gravação Texto
// Se o arquivo não existir, o mesmo será criado;
// É realizada a ordenação pelo selection sort, ordenando os registros por ordem do identificador
// Em seguida é feita a escrita/gravação no arquivo em formado txt
{
    ofstream arquivo("gravacao.txt");
    selectionSort(vetor,tam);
    for (int i = 0; i < tam; i++)
    {
		
        arquivo << "Identificador:" << vetor[i].identificador << endl << "Nome:" << vetor[i].nome
                << endl << "Ano de Nascimento:" << vetor[i].anoNascimento << endl << "Estilo:" << vetor[i].estilo
                << endl << "Principal Obra: " << vetor[i].principalObra <<endl <<endl;
    }
    arquivo.close();
    cout << "Gravacao Realizada com Sucesso" <<endl;
}

int main()
{
    cout << "Bem vindo ao Classical Music Workshop" << endl;
    cout <<"Um projeto desenvolvido para valorizacao dos compositores classicos, faca sua contribuicao a partir das opcoes a baixo!" << endl;
    cout << endl;
    cout << " ****MENU**** " << endl << endl;
    cout << "O que deseja fazer?" << endl;
    cout << "(1)Incluir - Para inserir dados referentes a um ou mais compositor" << endl;
    cout << "(2)Excluir - Para excluir algum registro" << endl;
    cout << "(3)Listar - Para visualizacao dos registros existentes e seus respectivos campos" << endl;
    cout << "(4)Alterar - Para alterar algum campo de um registro" << endl;
    cout << "(5)Gravar dados - Para gravar os dados no arquivo" << endl;
    cout << "(6)Sair - Para encerrar o programa" << endl;

    comp_classicos *compositores = new comp_classicos[100];
    int opcao;
    cout << endl;
    cout << "Digite a opcao desejada: ";
    cin >> opcao;

    int qtd = 0, tam =0;

    while (opcao != 6)
    {

        if (opcao == 1)
        {
            incluir(compositores,tam,qtd);

        }

        if (opcao == 2)
        {
            int excluiId;
            cout << "Digite o identificador equivalente ao registro que deseja excluir: ";
            cin >> excluiId;
            selectionSort(compositores,tam);
            int posicao = BuscaBinaria(compositores,0, tam-1,excluiId);
            if (posicao != -1)
                excluir(compositores,tam,posicao);
            else if (posicao == -1)
            {
                cout << "Registro nao encontrado" <<endl;
            }

        }

        if (opcao == 3)
        {
            listar(compositores,tam);
        }

        if (opcao == 4)
        {
            alterar(compositores,tam);
        }

        if (opcao == 5)
        {
            GravarDados(compositores,tam);
        }
        cout <<endl;

        cout << "O que deseja fazer agora?" << endl;
        cout << "(1)Incluir - Para inserir dados referentes a um ou mais compositor" << endl;
        cout << "(2)Excluir - Para excluir algum registro" << endl;
        cout << "(3)Listar - Para visualizacao dos registros existentes e seus respectivos campos" << endl;
        cout << "(4)Alterar - Para alterar algum campo de um registro" << endl;
        cout << "(5)Gravar dados - Para gravar os dados no arquivo" << endl;
        cout << "(6)Sair - Para encerrar o programa" << endl;
        cout << "Opcao: ";
        cin >> opcao;
    }

    if (opcao == 6)
    {
        string sim_ou_nao;
        cout << "Caso ainda nao tenha gravado, deseja gravar seus dados antes de encerrar o progama? Se sim, digite 'SIM', se nao, digite 'NAO': ";
        cin >> sim_ou_nao;
        if (sim_ou_nao == "SIM")
        {
            GravarDados(compositores,tam);
            cout << "Obrigado pela sua colaboracao, a Classical Music Workshop agradece!";
        }
        else
            cout << "Obrigado pela sua colaboracao, a Classical Music Workshop agradece!";
        delete [] compositores;
        return 0;

    }

    delete[] compositores;



    return 0;
}
