#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

#define C4 261    // essa parte aqui vai ser usada para as melodias depois
#define D4 293
#define E4 329
#define F4 349
#define G4 392
#define A4 440
#define A5 880
#define B4 466
#define G5 784
#define B5 987
#define D6 1175
#define G6 1568
#define P 0

/*
    OBJETIVOS DA PROPOSTA

    1- inicializar o jogo, vendo qual � a palavra
    2- imprimir o jogo
    3- fazer as jogadas
    4- atualizar a palavra
    5- verificar a derrota ou vit�ria
    6 - perguntar ao jogador se ele deseja continuar e recome�ar o ciclo

    JOGO FEITO POR ---> Gabriel do Esp�rito Santo -- 2023 
    Code::Blocks 16.01
*/

// vari�veis globais

int i, cterros;
char aux[30],erros[7][20];

int fimjogo, contadordepalavras;

int menucriararquivo(); //declarando previamente para n�o acontecer erros na compila��o
void contapalavras();
void imprimir(int tam);
// m�sicas
void musicavitoria(){

    Beep(G5, 225);
    Beep(A5, 225);
    Beep(B5, 225);
    Beep(G5, 225);
    Beep(A5, 225);
    Beep(B5, 225);
    Beep(G5, 225);
    Beep(A5, 225);
    Beep(B5, 225);
    Beep(D6, 225);
    Beep(D6, 225);
    Beep(G6, 600);

    Beep(G5, 225);
    Beep(A5, 225);
    Beep(G5, 225);
    Beep(A5, 225);
    Beep(G5, 225);
    Beep(B5, 225);
    Beep(A5, 600);

    Beep(G5, 225);
    Beep(A5, 225);
    Beep(B5, 225);
    Beep(G5, 225);
    Beep(A5, 225);
}

void musicaderrota(){

    Beep(A4, 500);
    Beep(F4, 500);
    Beep(D4, 500);
    Beep(A4, 500);
    Beep(F4, 500);
    Beep(D4, 500);
    Beep(A4, 500);
    Beep(F4, 500);

    Beep(E4, 500);
    Beep(C4, 500);
    Beep(G4, 500);
    Beep(E4, 500);
    Beep(C4, 500);
    Beep(G4, 500);
    Beep(E4, 500);
    Beep(C4, 500);
}

//fun��o para conseguir mover o cursor
void gotoxy(int lin,int col){
    COORD coord;
    coord.X = col-1;
    coord.Y = lin-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}

//fun��o para desenhar uma caixa
void box(int lin1,int col1, int lin2,int col2){
    setlocale(LC_ALL,"C");
    int j;

    for(i=col1; i<=col2; i++) //fazendo as linhas
    {
        gotoxy(lin1,i);
        printf("%c",196);
        gotoxy(lin2,i);
        printf("%c",196);
    }

    for(i=lin1; i<=lin2; i++) //fazendo as linhas
    {
        gotoxy(i,col1);
        printf("%c",179);
        gotoxy(i,col2);
        printf("%c",179);
    }

    for(i=lin1+1; i<lin2; i++) //preenchendo
    {
        for(j=col1+1; j<col2; j++)
        {
            gotoxy(i,j);
            printf(" ");
        }
    }
    //colocando os cantos;
    gotoxy(lin1,col1);
    printf("%c",218);
    gotoxy(lin1,col2);
    printf("%c",191);
    gotoxy(lin2,col1);
    printf("%c",192);
    gotoxy(lin2,col2);
    printf("%c",217);
    setlocale(LC_ALL,"");
}

//fun��o para desenhar uma caixa
void box2(int lin1,int col1, int lin2,int col2)
{
    setlocale(LC_ALL,"C");
    int i,j;

    for(i=col1; i<=col2; i++) //fazendo as linhas
    {
        gotoxy(lin1,i);
        printf("%c",205);
        gotoxy(lin2,i);
        printf("%c",205);
    }

    for(i=lin1; i<=lin2; i++) //fazendo as colunas
    {
        gotoxy(i,col1);
        printf("%c",186);
        gotoxy(i,col2);
        printf("%c",186);
    }

    for(i=lin1+1; i<lin2; i++) //preenchendo
    {
        for(j=col1+1; j<col2; j++)
        {
            gotoxy(i,j);
            printf(" ");
        }
    }
    //colocando os cantos;
    gotoxy(lin1,col1);
    printf("%c",201);
    gotoxy(lin1,col2);
    printf("%c",187);
    gotoxy(lin2,col1);
    printf("%c",200);
    gotoxy(lin2,col2);
    printf("%c",188);
    setlocale(LC_ALL,"Portuguese");
}

//mudar a cor do texto
void cortexto(int letras, int fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),letras+fundo);
}

bool acharpalavra(char palavra[]){

    FILE *file = fopen("Lista de palavras.bin","rb");
    char copia[20];
    bool achou = false;

    if(file){

        while(fread(copia,sizeof(char),20,file)){

            if(strcmp(copia,palavra) == 0){
                achou = true;
            }
        }

        fclose(file);
    }
    else{
        printf("Erro ao abrir achar palavra!\n");
    }

    return achou;
}

void apagarpalavra(){


    char palavraap[20],copia[20];

    gotoxy(13,4);printf("Digite a palavra para apagar:");
    scanf("%s",palavraap);

    for(i=0;i<strlen(palavraap);i++){
                        palavraap[i] = toupper(palavraap[i]);
                    }

    if(acharpalavra(palavraap)){
        gotoxy(15,4);printf("palavra encontrada!\n");
        Sleep(500);
        FILE *file = fopen("Lista de palavras.bin","rb");

        if(file){

                FILE *arqaux = fopen("Arq auxiliar.bin","wb");

                if(arqaux){

                        while(fread(copia,sizeof(char),20,file)){

                            if(strcmp(copia,palavraap) != 0){
                                fwrite(copia,sizeof(char),20,arqaux);
                            }
                        }
                        fclose(file);
                        fclose(arqaux);

                        remove("Lista de palavras.bin");

                        if(rename("Arq auxiliar.bin","Lista de palavras.bin") != 0){
                            printf("erro ao renomear!\n");
                        }

                        gotoxy(16,4);printf("Palavra removida com sucesso!");
                        Sleep(500);
                }
                else{
                    printf("Erro ao abrir arquivo auxiliar\n");
                }
        }
        else{
            printf("N�o foi possivel abrir arquivo\n");
        }
    }
    else{
        gotoxy(15,4);printf("palavra n�o encontrada\n!");
        Sleep(500);
    }
}

bool jogadavalida(char letra){

    if((letra>= 'a' && letra <= 'z') || (letra>= 'A' && letra <= 'Z') || letra == '1' || letra == '2' || letra == '3'){
        return true;
    }
    else{

        gotoxy(22,5);printf("caracteres especiais n�o s�o aceitos!");
        gotoxy(21,55);

        return false;
    }
}

//fun��o para imprimir o andamento do jogo
void imppalavra(int tam)
{
    gotoxy(8,20-tam/2); //fazendo a conta para centralizar o cursor

    //vendo se o vetor auxiliar tem - ou uma letra
    for(i=0; i<tam; i++)
    {
        if(aux[i] == '-')
        {
            cortexto(0,0);
            printf(" ");
            cortexto(7,16);
            printf(" ");
        }
        if(aux[i]!= '-')
        {
            cortexto(10,0);
            printf("%c",aux[i]);
            cortexto(7,16);
            printf(" ");
        }
    }
}

void fazerchute(char letra,char palavra[]){

        bool adivinhar = false,existe = false;
        char chute[20];

       do{
        gotoxy(22,5); printf("Digite o chute:  ");
        scanf("%s",chute);

        if(strlen(chute) > strlen(palavra)){
            gotoxy(24,5); printf("Chute muito grande!");
            system("cls");
            imprimir(strlen(palavra));
        }

       } while(strlen(chute)>strlen(palavra));
        for(i=0; i<strlen(chute); i++)
        {
            chute[i] = toupper(chute[i]);
        }
        adivinhar = true;

    if(adivinhar && letra != '2')
    {
        for(i=0; i<7; i++)
        {
            if(strcmp(erros[i],chute) == 0)
            {
                existe = true;;
            }
        }
        if(strcmp(palavra,chute) == 0 && !existe)
        {
            strcpy(aux,palavra);
            fimjogo = 1;
        }
        else if (strcmp(palavra,chute) != 0 && !existe)
        {
            strcpy(erros[cterros],chute);
            cterros += 1;
        }
        if(existe)
        {
            printf("\a\a");
        }
    }
}

void fazerjogadas(char letra,char palavra[],int tam){

    bool existe = false,tem = false;

    for(i=0; i<tam; i++)
        {
            if(letra == aux[i])
            {
                existe = true;
            }
            if(erros[i][0] == letra)
            {
                existe = true;
            }
        }
        for(i=0; i<tam; i++)
        {
            if(letra == palavra[i])
            {
                aux[i] = letra;
                tem = true;;
            }
        }
        if((tem && existe) || (!tem && existe))
        {
            printf("\a\a");
        }
        if(!tem && !existe && letra != '2' && letra!= '3' && letra != '\n')
        {

            erros[cterros][0] = letra;
            cterros +=1;
        }
}

int jogadas(char palavra[],int tam)
{
    bool adivinhar = false;
    char letra;
    bool tem = false, existe = false;

    fflush(stdin);
    gotoxy(21,5);
    printf("Digite a letra ou (1- chutar, 2- sair, 3- MENU) :  ");
    do{
        letra = getch();
    }while(!jogadavalida(letra));

    letra = toupper(letra);
    printf("%c",letra);

    if(letra == '3'){
        fimjogo = menucriararquivo();
    }

    if(letra == '2')
    {
        fimjogo = 2;
    }

    if(letra == '1')
    {
        fazerchute(letra,palavra);
    }
    else
    {
        fazerjogadas(letra,palavra,tam);
    }
    setlocale(LC_ALL," ");
}
void imprimeperna(int coluna)
{
    box2(21,coluna-1,22,coluna+1);
    setlocale(LC_ALL,"C");
    gotoxy(20,coluna);
    printf("%c",186);
    gotoxy(19,coluna);
    printf("%c",203);
    gotoxy(21,coluna);
    printf("%c",202);
    setlocale(LC_ALL,"Portuguese");

}
void imprimebracoe()
{
    setlocale(LC_ALL,"C");
    gotoxy(16,71);
    printf("%c",201);
    gotoxy(17,71);
    printf("%c",185);
    gotoxy(18,71);
    printf("%c",200);
    gotoxy(16,72);
    printf("%c",203);
    gotoxy(18,72);
    printf("%c",185);
    gotoxy(17,70);
    printf("%c",205);
    gotoxy(17,69);
    printf("%c",201);
    gotoxy(21,69);
    printf("%c",206);
    gotoxy(21,68);
    printf("%c",201);
    gotoxy(21,70);
    printf("%c",187);
    for(i=18; i<21; i++)
    {
        gotoxy(i,69);
        printf("%c",186);

    }
    setlocale(LC_ALL,"Portuguese");
}
void imprimebracod()
{
    setlocale(LC_ALL,"C");
    for(i=18; i<21; i++)
    {
        gotoxy(i,83);
        printf("%c",186);
    }
    gotoxy(21,83);
    printf("%c",206);
    gotoxy(21,82);
    printf("%c",201);
    gotoxy(21,84);
    printf("%c",187);
    gotoxy(17,83);
    printf("%c",187);
    gotoxy(16,81);
    printf("%c",187);
    gotoxy(17,81);
    printf("%c",204);
    gotoxy(18,81);
    printf("%c",188);
    gotoxy(16,80);
    printf("%c",203);
    gotoxy(18,80);
    printf("%c",204);
    gotoxy(17,82);
    printf("%c",205);

    setlocale(LC_ALL,"Portuguese");
}

void imprimirparabens()
{
    cortexto(7,16);
    system("cls");

    printf("                                        __                            \n");
    printf("    ____     ____ _   _____   ____ _   / /_     ___     ____     _____\n");
    printf("   / __ \\   / __ `/  / ___/  / __ `/  / __ \\   / _ \\   / __ \\   / ___/\n");
    printf("  / /_/ /  / /_/ /  / /     / /_/ /  / /_/ /  /  __/  / / / /  (__  ) \n");
    printf(" / .___/   \\__,_/  /_/      \\__,_/  /_.___/   \\___/  /_/ /_/  /____/  \n");
    printf("/_/                                                                   \n");

    printf("          _____      \n");
    printf("        '.=====.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.   /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         .'   '.        \n");
    printf("        '-------'       \n\n");
    cortexto(7,0);

}

void imprimecorda()
{
    setlocale(LC_ALL,"C");
    cortexto(15,64);
    system("cls");
    printf("     |/|\n     | |\n     |/|\n    (___)\n    (___)\n    (___)\n    (___)\n    (___)\n   //   \\\\\n  //     \\\\\n  ||      ||\n  ||      ||\n  ||      ||\n   \\\\____//\n    -----\n");
    setlocale(LC_ALL,"Portuguese");
    cortexto(7,0);
}

void imprimepescoco(){

    setlocale(LC_ALL,"C");
    gotoxy(15,76);printf("%c",186);
    gotoxy(14,76);printf("%c",203);
    gotoxy(16,76);printf("%c",202);
    setlocale(LC_ALL,"Portuguese");
}

void imprimecabeca(){

    setlocale(LC_ALL,"C");
    box2(11,73,14,79);
    gotoxy(12,75);
    printf("%c %c",167,167);
    gotoxy(13,75);
    printf("---");
    Sleep(2000);
    cortexto(4,0);
    gotoxy(12,75);
    printf("%c %c",88,88);
    gotoxy(13,75);
    printf("+++");

    setlocale(LC_ALL,"Portuguese");
}

void impheart()
{
    setlocale(LC_ALL,"C");
    cortexto(14,0);
    for(i=9; i<26; i++)
    {
        gotoxy(i,60);
        printf("%c",186);
    }
    for(i=60; i<90; i++)
    {
        gotoxy(25,i);
        printf("%c",220);
    }
    for(i=62; i<75; i++)
    {
        gotoxy(9,i);
        printf("%c",196);
    }
    gotoxy(9,75);
    printf("%c",191);
    gotoxy(10,75);
    printf("%c",193);

    cortexto(11,0);

    if(cterros>0)
    {
        //tronco
        box2(16,72,19,80);
    }
    if(cterros>1)
    {
        //perna direita
        imprimeperna(78);
    }
    if(cterros>2)
    {
        //perna
        imprimeperna(74);
    }
    if(cterros>3)
    {
        //bra�o direito
        imprimebracod();
    }
    if(cterros>4){
        //bra�o esquerdo
        imprimebracoe();
    }
    if(cterros>5){
        //pesco�o
        imprimepescoco();
    }
    if(cterros>6){
        //cabe�a
        imprimecabeca();

    }
    cortexto(7,0);
    setlocale(LC_ALL," ");
}

void imprimir(int tam)
{
    int j;
    impheart();

    gotoxy(4,50);
    printf("J O G O  D A  F O R C A");
    cortexto(15,16);
    box(5,2,9,46);
    cortexto(7,0);
    cortexto(1,240);
    gotoxy(6,18);
    printf(" P A L A V R A ");
    cortexto(7,0);

    cortexto(14,64);
    box(11,10,19,30); //cor vermelha
    gotoxy(11,13);
    printf("P A L P I T E S");

    for(i=12,j=1; i<19||j<=7; i++,j++)
    {
        gotoxy(i,12);
        printf("%d-",j);
    }
    cortexto(7,0);

    imppalavra(tam);

    cortexto(0,64);
    for(i=12,j=0; i<19||j<7; i++,j++)
    {
        gotoxy(i,15);
        printf("%s\n",erros[j]);
    }
    cortexto(7,0);
}

void inicializar(int tam,char palavra[])
{
    strcpy(aux,palavra);
    for(i=0; i<tam; i++)
    {
        aux[i] = '-' ;

    }
    for(i=0; i<7; i++)
    {
        strcpy(erros[i]," ");
    }

}
int sortearpalavra()
{
    contapalavras();
    int sorteio;
    srand(time(NULL));
    sorteio = rand() % contadordepalavras;
    return sorteio;
}

void criararquivoB()
{
    char palavras[100][20] =
    {
        "CACHORRO", "GATO", "CARRO", "BANANA", "COMPUTADOR",
        "MESA", "TELEFONE", "CADEIRA", "JANELA", "PORTA",
        "CHAVE", "LIVRO", "CANETA", "RELOGIO", "COPO",
        "BICICLETA", "AVIAO", "BARCO", "MONTANHA", "PRAIA",
        "SOL", "LUA", "ESTRELA", "PLANETA", "UNIVERSO",
        "PAVAO", "AMIZADE", "FAMILIA", "TRABALHO", "ESTUDO",
        "ESCOLA", "PROFESSOR", "ALUNO", "ENSAIO", "MUSICA",
        "ARTE", "PINTURA", "DANCA", "TEATRO", "FILME",
        "FOTOGRAFIA", "NATUREZA", "CIDADE", "VIAGEM", "FERIAS",
        "ESPORTE", "FUTEBOL", "BASQUETE", "NATACAO", "CORRIDA",
        "GINASTICA", "COMIDA", "BEBIDA", "RESTAURANTE", "COZINHA",
        "RECEITA", "COMPUTACAO", "PROGRAMACAO", "INTERNET", "TECNOLOGIA",
        "ENERGIA", "ELETRICIDADE", "SUSTENTABILIDADE", "POLITICA", "DEMOCRACIA",
        "JUSTICA", "LIBERDADE", "IGUALDADE", "PAZ", "GUERRA",
        "HISTORIA", "CULTURA", "RELIGIAO", "CIENCIA", "CONHECIMENTO",
        "DESCOBERTA", "EXPLORACAO", "INOVACAO", "REVOLUCAO", "EVOLUCAO",
        "FUTURO", "PASSADO", "PRESENTE", "TEMPO", "ESPACO",
        "VIDA", "MORTE", "SONHO", "REALIDADE", "ESPERANCA",
        "MEDO", "CORAGEM", "RISO", "CHORO", "SILENCIO",
        "PALAVRA", "POESIA", "FRASE", "VERSO", "PROSA"
    };

    FILE *file1 = fopen("Lista de palavras.bin","rb"); // se o file1 retornar NULL o arquivo n�o existe ainda. ent�o � criado um novo

    if(file1 == NULL){
            FILE *file = fopen("Lista de palavras.bin","wb");

            if(file)
        {
                for(i=0;i<100;i++){
                fwrite(palavras[i],sizeof(char),20,file);
                }
                fclose(file);
                printf("Arquivo criado com sucesso!\n");
                printf("\nPARA MELHOR VISUALIZA��O JOGUE EM TELA CHEIA!!\n");
                Sleep(3000);
        }
            else
            {
                printf("N foi possivel abrir o arquivo!!\n");
            }
    }
    else{
        printf("Arquivo j� existe!\n");
        printf("\nPARA MELHOR VISUALIZA��O JOGUE EM TELA CHEIA!!\n");
        Sleep(3000);
        fclose(file1);
    }
}

void contapalavras(){

    FILE *file = fopen("Lista de palavras.bin","rb");

    if(file){

        contadordepalavras = 0;

        char palavra[20];

        while(fread(palavra,sizeof(char),20,file)){
            contadordepalavras += 1;
        }
        fclose(file);
    }
    else{
        printf("Erro ao contar palavras");
    }
}

void verpalavras(){

    char copia[30];
    int c = 4 , l = 13,mlin;

    contapalavras();

    FILE *file = fopen("Lista de palavras.bin","rb");

    if(file){

        gotoxy(l,c+25);printf("************************ PALAVRAS ************************");
        l+=2;
        gotoxy(l,c);printf("N�mero de palavras lidas do arquivo: %d",contadordepalavras);
        l+=2;

        while(fread(&copia,sizeof(char),20,file)){
            gotoxy(l,c); printf("%s",copia);
            l++;
            if((l-13) % (contadordepalavras/4) == 0){
                mlin = l+3;
                l = 17;
                c += 23;
            }
        }
        fclose(file);
        gotoxy(mlin,4); system("pause");
    }
}

void adicionarpalavras(){

    char copia[20];
    int n,i,j;
    int opc;

    gotoxy(13,4);printf("Digite o n�mero de palavras que deseja adicionar:");
    scanf("%d",&n);
    printf("\n");

    char **mat = malloc(n * sizeof(char*));

    if(mat){

    for(i=0;i<n;i++){
        mat[i] = malloc(20*sizeof(char));
        printf("   Digite a %d palavra:  ",i+1);
        scanf("%s",mat[i]);

        for(j=0;j<strlen(mat[i]);j++){
            mat[i][j] = toupper(mat[i][j]);
        }
    }
     printf("\n\n   PALAVRAS CADASTRADAS:\n\n");
    for(i=0;i<n;i++){
        printf("   %s\n",mat[i]);
    }

    printf("\n   Deseja adicionar essas palavras ao arquivo?(1-SIM,2-N�O):  ");
    scanf("%d",&opc);

    if(opc == 1){

        FILE *file = fopen("Lista de palavras.bin","ab+");

        if(file){

            for(i=0;i<n;i++){
                fwrite(mat[i],sizeof(char),20,file);
            }
            printf("   Palavras adicionadas com sucesso!\n");
            Sleep(2000);
            fclose(file);

        }
        else{
            printf("   Erro ao abrir arquivo para adicionar as novas palavras!\n");
        }
    }
    else{
        printf("   Voc� escolheu n�o modificar o arquivo!\n");
    }
}
    else{
        printf("Erro ao alocar mem�ria.\n");
    }

    for (i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

int menucriararquivo(){

    int opc = 0,l = 3,c = 4, terminajogo =0;

    while(opc != 4 && opc != 5){

        system("cls");

        cortexto(15,16);
        box2(2,2,12,32);

        gotoxy(l,c);printf("MENU\n");

        gotoxy(l+2,c);printf("1- ADICIONAR PALAVRAS\n");
        gotoxy(l+3,c);printf("2- VER PALAVRAS DISPON�VEIS\n");
        gotoxy(l+4,c);printf("3- EXCLUIR PALAVRA\n");
        gotoxy(l+5,c);printf("4- INICIAR JOGO\n");
        gotoxy(l+6,c);printf("5- FECHAR JOGO\n");
        gotoxy(l+8,c);printf("DIGITE SUA OP��O --->  ");
        scanf("%d",&opc);
        fflush(stdin);
        cortexto(7,0);

        switch(opc){

            case 1:{
                adicionarpalavras();
                break;
            }
            case 2:{
                verpalavras();
                break;
            }
            case 3:{
                apagarpalavra();
                break;
            }
            case 4:{
                contapalavras();
                break;
            }
            case 5:{
                gotoxy(l+11,c);printf("Voc� encerrou o jogo!\n");
                terminajogo = 2;
                Sleep(2000);
                system("cls");
                break;
            }

            default:{
            gotoxy(l+9,c);printf("Opc�o inv�lida!");
            Sleep(500);
            }
        }
    }
    return terminajogo;
}

void jogodaforca(){

    int t;
    setlocale(LC_ALL,"Portuguese");
    char palavra[20];
    int terminarjogo = 1;

    criararquivoB();

    terminarjogo = menucriararquivo();

    while(terminarjogo != 2)
    {
        system("cls");

        FILE *file = fopen("Lista de palavras.bin","rb");
        int res;
        res = sortearpalavra();

        fseek(file,20* res*sizeof(char),SEEK_SET);
        fread(palavra,sizeof(char),20,file);

        fclose(file);

        fimjogo = 0;

        t = strlen(palavra);

        inicializar(t,palavra);
        cterros = 0;

        while(1)
        {
            system("cls");
            imprimir(t);

            jogadas(palavra,t);

            if(fimjogo == 2 || fimjogo == 1)
            {
                break;
            }

            if(cterros == 7)
            {
                fimjogo = 3; //acabaram as vidas
                break;
            }
            if(strcmp(aux,palavra) == 0)
            {
                fimjogo = 1; //adivinhou a a palavra letra a letra
                break;
            }
            Sleep(600);
        }
        setlocale(LC_ALL," ");
        switch(fimjogo)
        {
        case 1:
        {
            imprimir(t);
            Sleep(3000);
            imprimirparabens();
            gotoxy(24,5);
            printf("PARAB�NS, VOC� ADIVINHOU A PALAVRA!\n\n");
            musicavitoria();

            break;
        }
        case 2:
        {   imprimir(t);
            gotoxy(23,5);
            printf("VOC� ESCOLHEU SAIR!\n\n");
            break;
        }
        case 3:
        {
            imprimir(t);
            Sleep(2000);
            imprimecorda();
            gotoxy(22,5);
            printf("VOC� FOI ENFORCADO! ACABARAM SUAS VIDAS!");
            gotoxy(23,5);
            printf("A PALAVRA ERA: %s\n\n",palavra);
            musicaderrota();
            break;
        }
    }

        if(fimjogo == 2)
        {
            terminarjogo = 2;
        }
        else
        {
            gotoxy(24,5);
            printf("Deseja continuar? (1- sim, 2- n�o): ");
            scanf("%d",&terminarjogo);
        }

    }

}

int main()
{
    jogodaforca();
    printf("\n    ");
    system("pause");
    return 0;
}
