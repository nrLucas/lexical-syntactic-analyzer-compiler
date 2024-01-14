#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

#define pb push_back

typedef struct
{
    string CLASSE;
    string LEXEMA;
    string TIPO;
} TOKEN;

map<string, TOKEN> TABELA_DE_SIMBOLOS;

vector<string> PALAVRAS_RESERVADAS = {"inicio",
                                      "varinicio",
                                      "varfim",
                                      "escreva",
                                      "leia",
                                      "se",
                                      "entao",
                                      "fimse",
                                      "repita",
                                      "fimrepita",
                                      "fim",
                                      "inteiro",
                                      "literal",
                                      "real"};

vector<char> DIGITOS = {'0',
                        '1',
                        '2',
                        '3',
                        '4',
                        '5',
                        '6',
                        '7',
                        '8',
                        '9'};

vector<char> LETRAS = {'A',
                       'B',
                       'C',
                       'D',
                       'E',
                       'F',
                       'G',
                       'H',
                       'I',
                       'J',
                       'K',
                       'L',
                       'M',
                       'N',
                       'O',
                       'P',
                       'Q',
                       'R',
                       'S',
                       'T',
                       'U',
                       'V',
                       'W',
                       'X',
                       'Y',
                       'Z',
                       'a',
                       'b',
                       'c',
                       'd',
                       'e',
                       'f',
                       'g',
                       'h',
                       'i',
                       'j',
                       'k',
                       'l',
                       'm',
                       'n',
                       'o',
                       'p',
                       'q',
                       'r',
                       's',
                       't',
                       'u',
                       'v',
                       'w',
                       'x',
                       'y',
                       'z'};

vector<char> ALFABETO = {'\n',
                         ' ',
                         '0',
                         '1',
                         '2',
                         '3',
                         '4',
                         '5',
                         '6',
                         '7',
                         '8',
                         '9',
                         'A',
                         'B',
                         'C',
                         'D',
                         'E',
                         'F',
                         'G',
                         'H',
                         'I',
                         'J',
                         'K',
                         'L',
                         'M',
                         'N',
                         'O',
                         'P',
                         'Q',
                         'R',
                         'S',
                         'T',
                         'U',
                         'V',
                         'W',
                         'X',
                         'Y',
                         'Z',
                         'a',
                         'b',
                         'c',
                         'd',
                         'e',
                         'f',
                         'g',
                         'h',
                         'i',
                         'j',
                         'k',
                         'l',
                         'm',
                         'n',
                         'o',
                         'p',
                         'q',
                         'r',
                         's',
                         't',
                         'u',
                         'v',
                         'w',
                         'x',
                         'y',
                         'z',
                         '_',
                         33,
                         34,
                         39,
                         40,
                         41,
                         42,
                         43,
                         44,
                         45,
                         46,
                         47,
                         58,
                         59,
                         60,
                         61,
                         62,
                         63,
                         91,
                         92,
                         93,
                         123,
                         125};

map<char, bool> VERIFICA_ALFABETO;
string scanner_token;
string global_lexema;
string global_tipo;
bool scanner_token_ativo;
bool verificaNovoToken;
int global_linha = 1;
int global_coluna = 0;
string CLASSE_SINTATICO;

typedef struct
{
    bool ponto = false;
    bool exp = false;
    bool sinal = false;
    char sinal_simbolo;
} Token_Num;

Token_Num token_num;

TOKEN retorno;

list<string> CLASSES;

void verificaTokenNaTabela()
{
    string classe;
    string lexema;
    string tipo = "Nulo";

    if (scanner_token == "NUM")
    {
        classe = scanner_token;
        lexema = global_lexema;
        if (token_num.ponto == true || (token_num.sinal == true && token_num.sinal_simbolo == '-'))
        {
            tipo.clear();
            tipo = "real";
        }
        else
        {
            tipo.clear();
            tipo = "inteiro";
        }
        token_num.exp = false;
        token_num.ponto = false;
        token_num.sinal = false;
        token_num.sinal_simbolo = ' ';
    }
    else
    {
        if (scanner_token == "id")
        {
            if (TABELA_DE_SIMBOLOS[global_lexema].CLASSE.size() == 0 && TABELA_DE_SIMBOLOS[global_lexema].LEXEMA.size() == 0)
            {
                TABELA_DE_SIMBOLOS[global_lexema].CLASSE = "id";
                TABELA_DE_SIMBOLOS[global_lexema].LEXEMA = global_lexema;
                TABELA_DE_SIMBOLOS[global_lexema].TIPO = "Nulo";
            }
            classe = TABELA_DE_SIMBOLOS[global_lexema].CLASSE;
            lexema = TABELA_DE_SIMBOLOS[global_lexema].LEXEMA;
            tipo.clear();
            tipo = TABELA_DE_SIMBOLOS[global_lexema].TIPO;
        }
        else
        {
            if (scanner_token == "Lit")
            {
                tipo.clear();
                tipo = "literal";
            }

            classe = scanner_token;
            lexema = global_lexema;
        }
    }

    retorno.CLASSE = classe;
    retorno.LEXEMA = lexema;
    retorno.TIPO = tipo;
    // CLASSE_SINTATICO = classe;
    if (retorno.CLASSE != "Comentario")
        CLASSES.pb(retorno.CLASSE);
}

void resetaControlesToken()
{
    scanner_token.clear();
    global_lexema.clear();
    scanner_token_ativo = false;
}

void Erro()
{
    cout << "Classe: ERRO, Lexema: " << global_lexema << ", Tipo: "
         << "Nulo" << endl
         << "ERRO lexico. Caractere invalido na linguagem. Linha " << global_linha << ", coluna " << global_coluna << endl;
}

void verificaNum(char c)
{
    char aux = global_lexema[global_lexema.size() - 1];

    if (
        find(DIGITOS.begin(), DIGITOS.end(), aux) != DIGITOS.end() &&
        token_num.ponto == false &&
        token_num.exp == false &&
        token_num.sinal == false &&
        c == '.')
    {
        token_num.ponto = true;
        global_lexema.pb(c);
    }
    else
    {

        if (aux == '.')
        {
            if (find(DIGITOS.begin(), DIGITOS.end(), c) != DIGITOS.end())
            {
                global_lexema.pb(c);
            }
            else
            {
                global_lexema.pb(c);
                Erro();
                resetaControlesToken();
            }
        }
        else
        {
            if (c == 'e' || c == 'E')
            {
                if (find(DIGITOS.begin(), DIGITOS.end(), aux) != DIGITOS.end() &&
                    token_num.exp == false &&
                    token_num.sinal == false)
                {
                    token_num.exp = true;
                    global_lexema.pb(c);
                }
                else
                {
                    global_lexema.pb(c);
                    Erro();
                    resetaControlesToken();
                }
            }

            else
            {

                if (c == '+' || c == '-')
                {
                    if (
                        (aux == 'e' || aux == 'E') &&
                        token_num.sinal == false &&
                        token_num.exp == true)
                    {
                        token_num.sinal = true;
                        token_num.sinal_simbolo = c;
                        global_lexema.pb(c);
                    }

                    else
                    {
                        global_lexema.pb(c);
                        Erro();
                        resetaControlesToken();
                    }
                }
                else
                {
                    if (aux == '+' || aux == '-')
                    {
                        if (find(DIGITOS.begin(), DIGITOS.end(), c) != DIGITOS.end())
                        {
                            global_lexema.pb(c);
                        }
                        else
                        {
                            global_lexema.pb(c);
                            Erro();
                            resetaControlesToken();
                        }
                    }
                    else
                    {
                        if (find(DIGITOS.begin(), DIGITOS.end(), aux) != DIGITOS.end())
                        {
                            if (find(DIGITOS.begin(), DIGITOS.end(), c) != DIGITOS.end())
                            {
                                global_lexema.pb(c);
                            }
                            else
                            {
                                verificaTokenNaTabela();
                                resetaControlesToken();

                                if (c != ' ' || c != '\n' || c != '\t')
                                {
                                    verificaNovoToken = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void verificaId(char c)
{

    if (find(LETRAS.begin(), LETRAS.end(), c) != LETRAS.end() || find(DIGITOS.begin(), DIGITOS.end(), c) != DIGITOS.end() || c == '_')
    {
        global_lexema.pb(c);
    }
    else
    {
        verificaTokenNaTabela();
        resetaControlesToken();

        if (c != ' ' && c != '\n' && c != '\t')
        {
            verificaNovoToken = true;
        }
    }
}

void verificaOPR_RCB(char c)
{

    if (global_lexema[0] == '<')
    {
        if (c == '=' || c == '>')
        {
            global_lexema.pb(c);
            scanner_token = "OPR";
            verificaTokenNaTabela();
            resetaControlesToken();
        }
        else
        {
            if (c == '-')
            {
                global_lexema.pb(c);
                scanner_token = "RCB";
                verificaTokenNaTabela();
                resetaControlesToken();
            }
            else
            {
                scanner_token = "OPR";
                verificaTokenNaTabela();
                resetaControlesToken();
                verificaNovoToken = true;
            }
        }
    }
    else
    {
        if (global_lexema[0] == '>')
        {
            if (c == '=')
            {
                global_lexema.pb(c);
                scanner_token = "OPR";
                verificaTokenNaTabela();
                resetaControlesToken();
            }
            else
            {
                scanner_token = "OPR";
                verificaTokenNaTabela();
                resetaControlesToken();
                verificaNovoToken = true;
            }
        }
    }
}

void verificaLit(char c)
{

    if (c == '"')
    {
        global_lexema.pb(c);
        verificaTokenNaTabela();
        resetaControlesToken();
    }
    else
    {
        global_lexema.pb(c);
    }
}

void verificaComentario(char c)
{

    if (c == '}')
    {
        global_lexema.pb(c);
        verificaTokenNaTabela();
        resetaControlesToken();
    }
    else
    {
        if (find(ALFABETO.begin(), ALFABETO.end(), c) != ALFABETO.end())
        {
            global_lexema.pb(c);
        }
    }
}

void verificaPT_V(char c)
{
    verificaTokenNaTabela();
    resetaControlesToken();
}

void verificaVIR(char c)
{
    verificaTokenNaTabela();
    resetaControlesToken();
}

void verificaFC_P(char c)
{
    verificaTokenNaTabela();
    resetaControlesToken();
}

void verificaAB_P(char c)
{
    verificaTokenNaTabela();
    resetaControlesToken();
}

void verificaOPM(char c)
{
    verificaTokenNaTabela();
    resetaControlesToken();
}

void scannerToken(char c)
{
    if (scanner_token == "NUM")
    {
        verificaNum(c);
    }
    if (scanner_token == "Lit")
    {
        verificaLit(c);
    }
    if (scanner_token == "id")
    {
        verificaId(c);
    }
    if (scanner_token == "OPR_RCB")
    {
        verificaOPR_RCB(c);
    }
    if (scanner_token == "Comentario")
    {
        verificaComentario(c);
    }
    if (scanner_token == "PT_V")
    {
        verificaPT_V(c);
    }
    if (scanner_token == "VIR")
    {
        verificaVIR(c);
    }
    if (scanner_token == "FC_P")
    {
        verificaFC_P(c);
    }
    if (scanner_token == "AB_P")
    {
        verificaAB_P(c);
    }
    if (scanner_token == "OPM")
    {
        verificaOPM(c);
    }
}

void verificaAlfabeto()
{
    int i;
    for (i = 0; i < ALFABETO.size(); i++)
    {
        VERIFICA_ALFABETO[ALFABETO[i]] = true;
    }

    for (i = 0; i < PALAVRAS_RESERVADAS.size(); i++)
    {
        TABELA_DE_SIMBOLOS[PALAVRAS_RESERVADAS[i]].CLASSE = PALAVRAS_RESERVADAS[i];
        TABELA_DE_SIMBOLOS[PALAVRAS_RESERVADAS[i]].LEXEMA = PALAVRAS_RESERVADAS[i];
        TABELA_DE_SIMBOLOS[PALAVRAS_RESERVADAS[i]].TIPO = PALAVRAS_RESERVADAS[i];
    }
}

void scanner(char c)
{
    if (c == '\n')
    {
        global_linha++;
        global_coluna = 0;
    }
    else
    {
        global_coluna++;
    }

    if (VERIFICA_ALFABETO[c] == true)
    {
        if (scanner_token_ativo == true)
        {
            scannerToken(c);
            if (verificaNovoToken == true)
            {
                verificaNovoToken = false;
                if (find(DIGITOS.begin(), DIGITOS.end(), c) != DIGITOS.end())
                {
                    scanner_token_ativo = true;
                    scanner_token = "NUM";
                    global_lexema.pb(c);
                }
                if (find(LETRAS.begin(), LETRAS.end(), c) != LETRAS.end())
                {
                    scanner_token_ativo = true;
                    scanner_token = "id";
                    global_lexema.pb(c);
                }
                if (c == '<' || c == '>' || c == '=')
                {
                    scanner_token_ativo = true;
                    scanner_token = "OPR_RCB";
                    global_lexema.pb(c);
                }
                if (c == '"')
                {

                    scanner_token_ativo = true;
                    scanner_token = "Lit";
                    global_lexema.pb(c);
                }
                if (c == '{')
                {
                    scanner_token_ativo = true;
                    scanner_token = "Comentario";
                    global_lexema.pb(c);
                }
                if (c == '(')
                {
                    scanner_token = "AB_P";
                    global_lexema.pb(c);
                    scannerToken(c);
                }
                if (c == ')')
                {
                    scanner_token = "FC_P";
                    global_lexema.pb(c);
                    scannerToken(c);
                }
                if (c == ';')
                {
                    scanner_token = "PT_V";
                    global_lexema.pb(c);
                    scannerToken(c);
                }
                if (c == ',')
                {
                    scanner_token = "VIR";
                    global_lexema.pb(c);
                    scannerToken(c);
                }
                if (c == '+' || c == '-' || c == '*' || c == '/')
                {
                    scanner_token = "OPM";
                    global_lexema.pb(c);
                    scannerToken(c);
                }
            }
        }
        else
        {
            verificaNovoToken = false;
            if (find(DIGITOS.begin(), DIGITOS.end(), c) != DIGITOS.end())
            {
                scanner_token_ativo = true;
                scanner_token = "NUM";
                global_lexema.pb(c);
            }
            if (find(LETRAS.begin(), LETRAS.end(), c) != LETRAS.end())
            {
                scanner_token_ativo = true;
                scanner_token = "id";
                global_lexema.pb(c);
            }
            if (c == '<' || c == '>' || c == '=')
            {
                scanner_token_ativo = true;
                scanner_token = "OPR_RCB";
                global_lexema.pb(c);
            }
            if (c == '"')
            {

                scanner_token_ativo = true;
                scanner_token = "Lit";
                global_lexema.pb(c);
            }
            if (c == '{')
            {
                scanner_token_ativo = true;
                scanner_token = "Comentario";
                global_lexema.pb(c);
            }
            if (c == '(')
            {
                scanner_token = "AB_P";
                global_lexema.pb(c);
                scannerToken(c);
            }
            if (c == ')')
            {
                scanner_token = "FC_P";
                global_lexema.pb(c);
                scannerToken(c);
            }
            if (c == ';')
            {
                scanner_token = "PT_V";
                global_lexema.pb(c);
                scannerToken(c);
            }
            if (c == ',')
            {
                scanner_token = "VIR";
                global_lexema.pb(c);
                scannerToken(c);
            }
            if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                scanner_token = "OPM";
                global_lexema.pb(c);
                scannerToken(c);
            }
        }
    }
    else
    {
        if (scanner_token_ativo == true)
        {
            if (scanner_token == "NUM" || scanner_token == "id" || scanner_token == "OPR")
            {
                verificaTokenNaTabela();
                resetaControlesToken();
            }
        }
        global_lexema.pb(c);
        Erro();
        resetaControlesToken();
    }
}

void iniciaToken()
{
    retorno.CLASSE = "";
    retorno.LEXEMA = "";
    retorno.TIPO = "";
}

string LISTA_REGRAS_COMPLETAS[] = {"P -> P",
                                   "P -> inicio V A",
                                   "V -> varincio LV",
                                   "LV -> D LV",
                                   "LV -> varfim pt_v",
                                   "D -> TIPO L pt_v",
                                   "L -> id vir L",
                                   "L -> id",
                                   "TIPO -> inteiro",
                                   "TIPO -> real",
                                   "TIPO -> literal",
                                   "A -> ES A",
                                   "ES -> leia id pt_v",
                                   "ES -> escreva ARG pt_v",
                                   "ARG -> lit",
                                   "ARG -> num",
                                   "ARG -> id",
                                   "A -> CMD A",
                                   "CMD -> id rcb LD pt_v",
                                   "LD -> OPRD opm OPRD",
                                   "LD -> OPRD",
                                   "OPRD -> id",
                                   "OPRD -> num",
                                   "A -> COND A",
                                   "COND -> CAB CP",
                                   "CAB -> se ab_p EXP_R fc_p entao",
                                   "EXP_R -> OPRD opr OPRD",
                                   "CP -> ES CP",
                                   "CP -> CMD CP",
                                   "CP -> COND CP",
                                   "CP -> fimse",
                                   "A -> R A",
                                   "R -> CABR CPR",
                                   "CABR -> repita ab_p EXP_R fc_p",
                                   "CPR -> ES CPR",
                                   "CPR -> CMD CPR",
                                   "CPR -> COND CPR",
                                   "CPR -> fimrepita",
                                   "A -> fim"};

string LISTA_REGRAS_ESQUERDA[] = {"P'",
                                  "P",
                                  "V",
                                  "LV",
                                  "LV",
                                  "D",
                                  "L",
                                  "L",
                                  "TIPO",
                                  "TIPO",
                                  "TIPO",
                                  "A",
                                  "ES",
                                  "ES",
                                  "ARG",
                                  "ARG",
                                  "ARG",
                                  "A",
                                  "CMD",
                                  "LD",
                                  "LD",
                                  "OPRD",
                                  "OPRD",
                                  "A",
                                  "COND",
                                  "CAB",
                                  "EXP_R",
                                  "CP",
                                  "CP",
                                  "CP",
                                  "CP",
                                  "A",
                                  "R",
                                  "CABR",
                                  "CPR",
                                  "CPR",
                                  "CPR",
                                  "CPR",
                                  "A"};

int CARDINALIDADE_DIREITA[] = {1, 3, 2, 2, 2, 3, 3, 1, 1, 1, 1, 2, 3, 3, 1, 1, 1, 2, 4, 3, 1, 1, 1, 2, 2, 5, 3, 2, 2, 2, 1, 2, 2, 4, 2, 2, 2, 1, 1};

typedef struct
{
    string regra_esquerda;
    string regra_completa;
    int cardinalidade_da_direita;
} REGRAS_GRAMATICA_SHIFT_REDUCE;

map<int, REGRAS_GRAMATICA_SHIFT_REDUCE> REGRAS_GRAMATICA;

typedef struct
{
    char action;
    int numero_regra;
} ACTION;

map<int, map<string, ACTION>> SLR_ACTION;

map<int, map<string, int>> SLR_GOTO;

list<int> PILHA;
list<int> PILHA_RECUPERACAO_ERRO;

void preenche_Regras_Gramatica()
{
    int i;
    for (i = 1; i <= 39; i++)
    {
        REGRAS_GRAMATICA[i].regra_esquerda = LISTA_REGRAS_ESQUERDA[i - 1];
        REGRAS_GRAMATICA[i].regra_completa = LISTA_REGRAS_COMPLETAS[i - 1];
        REGRAS_GRAMATICA[i].cardinalidade_da_direita = CARDINALIDADE_DIREITA[i - 1];
    }
}

void preenche_SLR_ACTION()
{

    string fname = "slr_action.csv";

    vector<vector<string>> content;
    vector<string> row;
    string line, word, coluna, aux;
    int num;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);

            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    // cout << "i size: " << content.size() << endl;
    for (int i = 1; i < content.size(); i++)
    {

        for (int j = 0; j < content[i].size(); j++)
        {

            coluna = content[0][j];

            if (content[i][j].size() > 0)
            {

                if (content[i][j] == "Acc")
                {
                    SLR_ACTION[i - 1][coluna].action = 'A';
                }
                else
                {
                    char action = content[i][j][0];
                    SLR_ACTION[i - 1][coluna].action = content[i][j][0];

                    aux.clear();

                    for (int k = 1; k < content[i][j].size(); k++)
                    {
                        aux.push_back(content[i][j][k]);
                    };

                    num = stoi(aux);

                    SLR_ACTION[i - 1][coluna].numero_regra = num;
                }
            }
        }
    }

    // for (int i = 0; i < 77; i++)
    // {
    //     cout << SLR_ACTION[i]["id"].action << " " << SLR_ACTION[i]["id"].numero_regra << endl;
    // }
}

void preenche_SLR_GOTO()
{
    string fname = "slr_desvio.csv";

    vector<vector<string>> content;
    vector<string> row;
    string line, word, coluna, aux;
    int num;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);

            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    // cout << "i size: " << content.size() << endl;
    for (int i = 1; i < content.size(); i++)
    {

        for (int j = 0; j < content[i].size(); j++)
        {

            coluna = content[0][j];

            if (content[i][j].size() > 0)
            {

                aux.clear();
                aux = content[i][j];
                num = stoi(aux);

                SLR_GOTO[i - 1][coluna] = num;
            }
        }
    }

    // for (int i = 0; i < 77; i++)
    // {
    //     cout << "i: " << i << " - " << SLR_GOTO[i]["COND"] << endl;
    // }
    // cout << "=========================================" << endl;
}

int main()
{

    verificaAlfabeto();
    iniciaToken();

    preenche_Regras_Gramatica();
    preenche_SLR_ACTION();
    preenche_SLR_GOTO();

    char c;
    int s, numero_regra, quantidade_desempilha, i;
    string regra_esquerda;
    string FILE;
    int contFile = 0;

    PILHA.push_front(0);

    ifstream fin("test_file.alg");

    verificaNovoToken = false;

    while (fin.get(c))
    {
        FILE.pb(c);
    }

    while (1)
    {

        c = FILE[contFile];
        contFile++;

        scanner(c);

        if (CLASSES.size() != 0)
        {
            CLASSE_SINTATICO = CLASSES.front();
            CLASSES.pop_front();
            break;
        }
    }

    while (1)
    {
        s = PILHA.front();

        if (SLR_ACTION[s][CLASSE_SINTATICO].action == 'S')
        {

            numero_regra = SLR_ACTION[s][CLASSE_SINTATICO].numero_regra;
            PILHA.push_front(numero_regra);

            if (contFile >= FILE.size())
            {
                CLASSE_SINTATICO = "$";
            }
            else
            {
                if (CLASSE_SINTATICO == "PT_V")
                {
                    PILHA_RECUPERACAO_ERRO = PILHA;
                }

                if (CLASSES.size() != 0)
                {
                    CLASSE_SINTATICO = CLASSES.front();
                    CLASSES.pop_front();
                }
                else
                {

                    while (1)
                    {

                        c = FILE[contFile];
                        contFile++;

                        scanner(c);

                        if (contFile >= FILE.size())
                        {
                            scanner(' ');
                        }

                        if (CLASSES.size() != 0)
                        {
                            CLASSE_SINTATICO = CLASSES.front();
                            CLASSES.pop_front();
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if (SLR_ACTION[s][CLASSE_SINTATICO].action == 'R')
            {

                numero_regra = SLR_ACTION[s][CLASSE_SINTATICO].numero_regra;
                quantidade_desempilha = REGRAS_GRAMATICA[numero_regra].cardinalidade_da_direita;

                cout << REGRAS_GRAMATICA[numero_regra].regra_completa << endl;

                for (i = 0; i < quantidade_desempilha; i++)
                {
                    PILHA.pop_front();
                }

                regra_esquerda = REGRAS_GRAMATICA[numero_regra].regra_esquerda;
                numero_regra = PILHA.front();

                PILHA.push_front(SLR_GOTO[numero_regra][regra_esquerda]);
            }
            else
            {
                if (SLR_ACTION[s][CLASSE_SINTATICO].action == 'A')
                {
                    // LINGUAGEM ACEITA
                    break;
                }
                else
                {

                    cout << "ERRO SINTATICO. "
                         << "Linha " << global_linha << ", coluna " << global_coluna << endl;
                    PILHA = PILHA_RECUPERACAO_ERRO;
                    if (CLASSES.size() != 0)
                    {
                        CLASSE_SINTATICO = CLASSES.front();
                        CLASSES.pop_front();
                    }
                    else
                    {

                        while (1)
                        {

                            c = FILE[contFile];
                            contFile++;

                            scanner(c);

                            if (contFile >= FILE.size())
                            {
                                scanner(' ');
                            }

                            if (CLASSES.size() != 0)
                            {
                                CLASSE_SINTATICO = CLASSES.front();
                                CLASSES.pop_front();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}