#include "Perfil.h"
#include "PessoaNaoVerificada.h"
#include "PessoaVerificada.h"
#include "Pagina.h"
#include "Postagem.h"
#include "RedeSocial.h"

#include <iostream>

using namespace std;

void listarPerfis(RedeSocial* R) {
    for(int i = 0; i < R->getQuantidadeDePerfis(); i++) {
        cout << i+1 << ") " << R->getPerfis()[i]->getNome();
        if ( EhVerificado( R->getPerfis()[i] ) ) {
            cout << " (Verificada)";
        }
        cout << endl;
    }
}

void interface() {

    RedeSocial* PoliBook = new RedeSocial();

    string opcao_string = "";
    int opcao = -1;
    while (opcao_string != "0") {
        cout << "Escolha uma opcao"   << endl
             << "1) Cadastrar Pessoa" << endl
             << "2) Cadastrar Pagina" << endl
             << "3) Logar"            << endl
             << "0) Terminar"         << endl;

        while (true) {
            getline(cin, opcao_string);

            // Convert from string to number safely
            stringstream myStream(opcao_string);
            if (myStream >> opcao) break;
            cout << "Numero invalido. Tente novamente." << endl;
        }

        switch (opcao) {
            case 1:
            {
                string nome;
                string verificada = "";
                cout << "Informe os dados da pessoa" << endl;
                cout << "Nome: ";
                getline(cin, nome);

                while (verificada != "s" && verificada != "n") {
                    cout << "Verificada (s/n)? ";
                    getline(cin, verificada);

                    if(verificada == "s") {

                        string email;
                        cout << "Email: ";
                        getline(cin, email);

                        PoliBook->adicionar(new PessoaVerificada(nome, email));

                    }

                    else if(verificada == "n") {
                        PoliBook->adicionar(new PessoaNaoVerificada(nome));
                    }
                }
                cout << endl;
            }
            break;

            case 2:
            {
                string nome;
                cout << "Informe os dados da pagina" << endl;
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Proprietario:" << endl;
                listarPerfis(PoliBook);

                string numero_string = "";
                int numero = -1;

                while (true) {
                    cout << "Digite o numero ou 0 para cancelar: ";
                    getline(cin, numero_string);

                    // Convert from string to number safely
                    stringstream myStream(numero_string);
                    if (myStream >> numero) break;
                }

                if (numero != 0) {
                    if ( PessoaVerificada* pv = dynamic_cast<PessoaVerificada*>(PoliBook->getPerfis()[numero-1]) ) {
                        PoliBook->adicionar( new Pagina(nome, pv) );
                    }
                    else {
                        cout << "Somente pessoas verificadas podem ser proprietarias" << endl;
                    }
                }
                cout << endl;
            }
            break;

            case 3:
            {
                cout << "Escolha um perfil:" << endl;
                listarPerfis(PoliBook);

                string numero_string = "";
                int numero = -1;
                while (true) {
                    cout << "Digite o numero ou 0 para cancelar: ";
                    getline(cin, numero_string);

                    // Convert from string to number safely
                    stringstream myStream(numero_string);
                    if (myStream >> numero) break;
                }

                if (numero != 0) {
                    Perfil* p = PoliBook->getPerfis()[numero-1];
                    cout << p->getNome();
                    if ( PessoaVerificada* pv = dynamic_cast<PessoaVerificada*>(p) ) {
                        cout << " - " << pv->getEmail();
                    }
                    cout << endl;
                    if ( Pagina* pag = dynamic_cast<Pagina*>(p) ) {
                        cout << "Proprietario " << pag->getProprietario()->getNome() << endl;
                    }
                    cout << "Contatos: " << p->getQuantidadeDeContatos() << endl;
                    cout << "---" << endl;

                    int acao = -1;
                    string acao_string = "";
                    while (acao != 0) {
                        cout << "Escolha uma opcao:" << endl
                             << "1) Fazer Postagem" << endl
                             << "2) Ver postagens dos contatos" << endl
                             << "3) Adicionar contato" << endl
                             << "0) Deslogar" << endl;
                        while (true) {

                            getline(cin, acao_string);

                            // Convert from string to number safely
                            stringstream myStream(acao_string);
                            if (myStream >> acao) break;
                            cout << "Tente novamente" << endl;
                        }

                        switch (acao) {
                            case 1:
                            {
                                cout << "Story (s/n): ";
                                string resposta;
                                getline(cin, resposta);

                                int data = -1;
                                string data_string = "";
                                while (true) {
                                    cout << "Data: ";
                                    getline(cin, data_string);

                                    // Convert from string to number safely
                                    stringstream myStream(data_string);
                                    if (myStream >> data) break;
                                }

                                int dataDeFim = -1;
                                string dataDeFim_string = "";
                                if (resposta == "s") {
                                    while (true) {
                                        cout << "Data de fim: ";
                                        getline(cin, dataDeFim_string);

                                        // Convert from string to number safely
                                        stringstream myStream(dataDeFim_string);
                                        if (myStream >> dataDeFim) break;
                                    }
                                }

                                string texto;
                                cout << "Texto: ";
                                getline(cin, texto);
                                if (resposta == "s") {
                                    p->adicionarPostagem(new Story(texto, data, dataDeFim, p));
                                }
                                else {
                                    p->adicionarPostagem(new Postagem(texto, data, p));
                                }
                                cout << endl;
                            }
                            break;

                            case 2:
                            {
                                int data = -1;
                                int quantidade;
                                string data_string = "";
                                while (true) {
                                    cout << "Data: ";
                                    getline(cin, data_string);

                                    // Convert from string to number safely
                                    stringstream myStream(data_string);
                                    if (myStream >> data) break;
                                }

                                cout << "Postagens dos ultimos 3 dias:" << endl;
                                Postagem** postagensDosContatos = p->getPostagensDosContatos(data, quantidade);
                                for (int i = 0; i < quantidade; i++) {
                                    postagensDosContatos[i]->imprimir();
                                }
                                cout << endl;
                            }
                            break;

                            case 3:
                            {
                                cout << "Perfil:" << endl;
                                listarPerfis(PoliBook);

                                int escolha = -1;
                                string escolha_string = "";
                                while (true) {
                                    cout << "Digite o numero ou 0 para cancelar: ";
                                    getline(cin, escolha_string);

                                    // Convert from string to number safely
                                    stringstream myStream(escolha_string);
                                    if (myStream >> escolha) break;
                                }

                                if (escolha != 0) {
                                    if( p->adicionarContato(PoliBook->getPerfis()[escolha-1]) ) {
                                        cout << "Adicionado com sucesso" << endl;
                                    }
                                    else {
                                        cout << "Contato nao adicionado" << endl;
                                    }
                                }
                                else cout << "Contato nao adicionado" << endl;
                                cout << endl;
                            }
                            break;
                        }
                    }
                }
                cout << endl;
            }
            break;

            case 0:
            {
                delete PoliBook;
            }
            break;
        }
    }
}

int main() {
    interface();
    return 0;
}

