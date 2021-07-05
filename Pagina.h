#ifndef PAGINA_H
#define PAGINA_H

#include "Perfil.h"
#include "PessoaVerificada.h"

#include <string>

class Pagina: public Perfil {
    public:
        Pagina(string nome, PessoaVerificada* proprietario);
        Pagina(string nome, PessoaVerificada* proprietario, int id); // Persistencia
        virtual ~Pagina();
    
        PessoaVerificada* getProprietario();
        void imprimir();

    private:
        PessoaVerificada* proprietario;
};

#endif // PAGINA_H
