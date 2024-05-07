#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>

struct Carta {
    std::string valor;
    std::string palo;
};
void animacion();
void creditos();
int menu_principal(int opcion);
int numeroRandom(int dado);
void repartir(std::vector<Carta>& mazo, std::vector<Carta>& corral1, std::vector<Carta>& corral2);
void barajar(std::vector<Carta>& mazo);
void jugar(std::string& nombre1, std::string& nombre2);
void juego(std::vector<Carta>& corral1, std::vector<Carta>& corral2, std::vector<Carta>& mazo, std::string& nombre1, std::string& nombre2, std::vector<bool>& auxiliar);
void funcionalidad(int& dado, std::vector<Carta>& corral1, std::vector<Carta>& corral2, std::vector<Carta>& mazo, bool& turno, std::vector<bool>& auxiliar);
void pre_estadisticas(std::vector<Carta> corral1, std::vector<Carta> corral2, std::string nombre1, std::string nombre2, bool& verificacion);
void estadisticas(std::vector<Carta>& corral1, std::vector<Carta>& corral2, std::string& nombre1, std::string& nombre2, std::vector<bool>& auxiliar);

int main()
{
    setlocale(LC_ALL, "");

    std::vector<Carta> mazo;
    std::vector<Carta> corral1;
    std::vector<Carta> corral2;


    std::string nombre1, nombre2;

    std::vector<bool> auxiliar(5, false);

    animacion();

    int opcion = 0;
    char opcion_salir;
    opcion = menu_principal(opcion);

    repartir(mazo, corral1, corral2);

    do{
        switch(opcion)
        {
            case 1:
                jugar(nombre1, nombre2);
                juego(corral1, corral2, mazo, nombre1, nombre2, auxiliar);
                repartir(mazo, corral1, corral2);
                break;
            case 2:
                estadisticas(corral1, corral2, nombre1, nombre2, auxiliar);
                break;
            case 3:
                creditos();
                break;
            case 4:
                system("cls");
                std::cout << "\u00BFdesea salir? (S/N)\n";
                std::cout << "\n";
                std::cin >> opcion_salir;

                if (opcion_salir == 'S')
                {
                    return 0;
                }
        }
        opcion = menu_principal(opcion);
    } while (opcion != 0);

}

void animacion()
{
    int num_repeticiones = 2;

    for (int rep = 0; rep < num_repeticiones; rep++) {
        for (int i = 0; i < 15; i++) {
            std::cout << "*******************************************************\n";
            std::cout << "*******************************************************\n";
            std::cout << "*********--*********************************--*********\n";
            std::cout << "********|  |*******************************|  |********\n";

            if (i < 5 || (i >= 10 && i < 15)) {
                std::cout << "*******| _  |*****************************| _  |*******\n";
                std::cout << "*******| O  |___*******+------+********___| O  |*******\n";
                std::cout << "*******|    ----|******|CLUTCH|*******|----    |*******\n";
                std::cout << "*******|    |**********+------+**********|     |*******\n";
            }
            else {
                std::cout << "*******| \\  |*****************************| /  |*******\n";
                std::cout << "*******| O  |___*******        ********___| O  |*******\n";
                std::cout << "*******|    ----|******        *******|----    |*******\n";
                std::cout << "*******|    |**********        **********|     |*******\n";
            }


            std::cout << "**|----|    |****************************|     |----|**\n";
            std::cout << "**|      |  |****************************|  |       |**\n";
            std::cout << "**| ------  |****************************|  ------- |**\n";
            std::cout << "**|         |****************************|          |**\n";
            std::cout << "***-       -******************************-        -***\n";
            std::cout << "****|-----|********************************|------|****\n";
            std::cout << "*******************************************************\n";
            std::cout << "*******************************************************\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "\x1B[2J\x1B[H";
        }
    }
}

void creditos()
{
    system("cls");

    std::cout << "+------------------------+\n";
    std::cout << "|                        |\n";
    std::cout << "|   GRACIAS POR JUGAR    |\n";
    std::cout << "|                        |\n";
    std::cout << "+------------------------+\n";
    std::cout << "|       INTEGRANTES      |\n";
    std::cout << "|                        |\n";
    std::cout << "|COMISION 112            |\n";
    std::cout << "|                        |\n";
    std::cout << "|SEBASTIAN CASTRO 22291  |\n";
    std::cout << "|                        |\n";
    std::cout << "+------------------------+\n";

    system("pause");
}

void repartir(std::vector<Carta>& mazo, std::vector<Carta>& corral1, std::vector<Carta>& corral2)
{
    const std::string valores[] = { "10 ", "J  ", "Q  ", "K  ", "A  " };
    const std::string palos[] = { "CORAZONES", "DIAMANTES", "   TREBOL", "    PICAS" };
    mazo.clear();
    corral1.clear();
    corral2.clear();

    for (std::string valor : valores) {
        for (std::string palo : palos) {
            Carta carta = { valor, palo };
            mazo.push_back(carta);
        }
    }
    barajar(mazo);
    for (int i = 0; i < 5; i++) {
        corral1.push_back(mazo.back());
        mazo.pop_back();
        corral2.push_back(mazo.back());
        mazo.pop_back();
    }
}

void barajar(std::vector<Carta>& mazo) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(mazo.begin(), mazo.end());
}

int menu_principal(int opcion)
{
    opcion = 1;
    char tecla;

    while (true) {
        system("cls");

        std::cout << "GLUTCH\n";
        std::cout << "-----------------\n";
        std::cout << (opcion == 1 ? ">" : "  ") << " JUGAR\n";
        std::cout << (opcion == 2 ? ">" : "  ") << " ESTADISTICAS\n";
        std::cout << (opcion == 3 ? ">" : "  ") << " CREDITOS\n";
        std::cout << "-----------------\n";
        std::cout << (opcion == 4 ? ">" : "  ") << " SALIR\n";

        tecla = _getch();


        if (tecla == 72 && opcion > 1) {
            opcion--;
        }
        else if (tecla == 80 && opcion < 4) {
            opcion++;
        }
        else if (tecla == 13) {
            return opcion;
        }

    }
}

int numeroRandom(int dado)
{
    dado = rand() % 7;
    return dado;
}

void jugar(std::string &nombre1, std::string &nombre2)
{
    nombre1.clear();
    nombre2.clear();
    system("cls");
    char opcion;
    std::cout << "GLUTCH\n";
    std::cout << "---------------------------------------------------------------------------------\n";
    std::cout << "Antes de comenzar debe registrar sus nombres:\n";
    std::cout << "\n";

    std::cout << "NOMBRE JUGADOR #1 ";
    getline(std::cin, nombre1);

    std::cout << "\n";

    std::cout << "NOMBRE JUGADOR #2 ";
    std::getline(std::cin, nombre2);

    std::cout << "\n";
    std::cout << "\u00BFConfirmar nombres? (S/N)\n";
    std::cout << "---------------------------------------------------------------------------------\n";


    do {
        std::cin >> opcion;
        std::cout << "\n";

        switch (opcion)
        {
        case 'S':
            std::cin.ignore();
            break;

        case 'N':
            std::cin.ignore();
            nombre1.clear();
            nombre2.clear();
            system("cls");
            std::cout << "GLUTCH\n";
            std::cout << "---------------------------------------------------------------------------------\n";
            std::cout << "Antes de comenzar debe registrar sus nombres:\n";
            std::cout << "\n";

            std::cout << "\u00BFNombre? ";
            getline(std::cin, nombre1);

            std::cout << "\n";

            std::cout << "\u00BFNombre? ";
            std::getline(std::cin, nombre2);

            std::cout << "\n";
            std::cout << "\u00BFConfirmar nombres? (S/N)\n";
            std::cout << "---------------------------------------------------------------------------------\n";
            break;

        default: system("cls");
            std::cout << "OPCION INCORRECTA \n";
            std::cout << "\u00BFConfirmar nombres? (S/N)\n";
            std::cin >> opcion;
            std::cout << "\n";

        }

    } while (opcion != 'S');
}

void juego(std::vector<Carta>& corral1, std::vector<Carta>& corral2, std::vector<Carta>& mazo, std::string& nombre1, std::string& nombre2, std::vector<bool>& auxiliar)
{
    int ronda = 0;
    int dado = 0;
    bool turno = true;
    bool verificacion = false;


    do{
        ronda++;
        if (verificacion == false)
        {
            barajar(mazo);
            system("cls");
            std::cout << " GLUTCH\n";
            std::cout << "+-------------------------------------------------------------------------+\n";
            std::cout << "| DADO 1 INTERCAMBIA UNA CARTA DE TU CORRAL POR UNA DEL MAZO              |\n";
            std::cout << "| DADO 2 INTERCAMBIA UNA CARTA DEL CORRAL CONTRARIO POR UNA DEL MAZO      |\n";
            std::cout << "| DADO 3 INTERCAMBIA UNA CARTA DE TU CORRAL POR UNA DEL CORRAL CONTRARIO  |\n";
            std::cout << "| DADO 4 INTERCAMBIA DOS CARTAS DE TU CORRAL                              |\n";
            std::cout << "| DADO 5 BLOQUEA UNA CARTA PARA NO PODER SER ROBADA              +--------+\n";
            std::cout << "| DADO 6 ELIJE CUALQUIERA DE LAS OPCIONES O SALTA EL TURNO       |RONDA #" << ronda << "|\n";
            std::cout << "+----------------------------------------------------------------+--------+\n";
            std::cout << "+--" << nombre1 << "--+" << "  << ES TU TURNO\n";
            std::cout << " \n";

            for (int a = 0; a < 5; a++)
            {
                std::cout << " +----------+ ";

            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |" << corral1[b].valor << "       | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " | " << corral1[b].palo << "| ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " +----------+ ";
            }

            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";

            for (int a = 0; a < 5; a++)
            {
                std::cout << " +----------+ ";

            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |" << corral2[b].valor << "       | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " | " << corral2[b].palo << "| ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " +----------+ ";
            }

            std::cout << "\n";
            std::cout << "\n";
            std::cout << "+--" << nombre2 << "--+\n";
            std::cout << "+-------------------------------------------------------------------------+\n";

            dado = numeroRandom(dado);
            switch (dado)
            {
            case 1:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|       |\n";
                std::cout << "|   *   |\n";
                std::cout << "|       |\n";
                std::cout << "+-------+\n";
                break;
            case 2:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*      |\n";
                std::cout << "|       |\n";
                std::cout << "|      *|\n";
                std::cout << "+-------+\n";
                break;
            case 3:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*      |\n";
                std::cout << "|   *   |\n";
                std::cout << "|      *|\n";
                std::cout << "+-------+\n";
                break;
            case 4:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*     *|\n";
                std::cout << "|       |\n";
                std::cout << "|*     *|\n";
                std::cout << "+-------+\n";
                break;
            case 5:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*     *|\n";
                std::cout << "|   *   |\n";
                std::cout << "|*     *|\n";
                std::cout << "+-------+\n";
                break;
            case 6:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*  *  *|\n";
                std::cout << "|       |\n";
                std::cout << "|*  *  *|\n";
                std::cout << "+-------+\n";
                break;

            }
            turno = true;
            funcionalidad(dado, corral1, corral2, mazo, turno, auxiliar);
            system("cls");
            pre_estadisticas(corral1, corral2, nombre1, nombre2, verificacion);
        }

        if (verificacion == false)
        {
            barajar(mazo);
            std::cout << " GLUTCH\n";
            std::cout << "+-------------------------------------------------------------------------+\n";
            std::cout << "| DADO 1 INTERCAMBIA UNA CARTA DE TU CORRAL POR UNA DEL MAZO              |\n";
            std::cout << "| DADO 2 INTERCAMBIA UNA CARTA DEL CORRAL CONTRARIO POR UNA DEL MAZO      |\n";
            std::cout << "| DADO 3 INTERCAMBIA UNA CARTA DE TU CORRAL POR UNA DEL CORRAL CONTRARIO  |\n";
            std::cout << "| DADO 4 INTERCAMBIA DOS CARTAS DE TU CORRAL                              |\n";
            std::cout << "| DADO 5 BLOQUEA UNA CARTA PARA NO PODER SER ROBADA              +--------+\n";
            std::cout << "| DADO 6 ELIJE CUALQUIERA DE LAS OPCIONES O SALTA EL TURNO       |RONDA #" << ronda << "|\n";
            std::cout << "+----------------------------------------------------------------+--------+\n";
            std::cout << "+--" << nombre1 << "--+\n";
            std::cout << " \n";

            for (int a = 0; a < 5; a++)
            {
                std::cout << " +----------+ ";

            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |" << corral1[b].valor << "       | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " | " << corral1[b].palo << "| ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " +----------+ ";
            }

            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";

            for (int a = 0; a < 5; a++)
            {
                std::cout << " +----------+ ";

            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |" << corral2[b].valor << "       | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " |          | ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " | " << corral2[b].palo << "| ";
            }
            std::cout << "\n";
            for (int b = 0; b < 5; b++) {

                std::cout << " +----------+ ";
            }

            std::cout << "\n";
            std::cout << "\n";
            std::cout << "+--" << nombre2 << "--+" << "  << ES TU TURNO\n";
            std::cout << "+-------------------------------------------------------------------------+\n";

            dado = numeroRandom(dado);
            switch (dado)
            {
            case 1:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|       |\n";
                std::cout << "|   *   |\n";
                std::cout << "|       |\n";
                std::cout << "+-------+\n";
                break;
            case 2:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*      |\n";
                std::cout << "|       |\n";
                std::cout << "|      *|\n";
                std::cout << "+-------+\n";
                break;
            case 3:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*      |\n";
                std::cout << "|   *   |\n";
                std::cout << "|      *|\n";
                std::cout << "+-------+\n";
                break;
            case 4:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*     *|\n";
                std::cout << "|       |\n";
                std::cout << "|*     *|\n";
                std::cout << "+-------+\n";
                break;
            case 5:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*     *|\n";
                std::cout << "|   *   |\n";
                std::cout << "|*     *|\n";
                std::cout << "+-------+\n";
                break;
            case 6:
                std::cout << "\n";
                std::cout << "+-------+\n";
                std::cout << "|*  *  *|\n";
                std::cout << "|       |\n";
                std::cout << "|*  *  *|\n";
                std::cout << "+-------+\n";
                break;

            }

            turno = false;
            funcionalidad(dado, corral1, corral2, mazo, turno, auxiliar);
            system("cls");
            pre_estadisticas(corral1, corral2, nombre1, nombre2, verificacion);
        }
        else
        {

        }
    }while (verificacion == false);
    estadisticas(corral1, corral2, nombre1, nombre2, auxiliar);
}

void funcionalidad(int& dado, std::vector<Carta>& corral1, std::vector<Carta>& corral2, std::vector<Carta>& mazo, bool& turno, std::vector<bool>&auxiliar)
{
    auxiliar[0] = false;
    int robar = 0, robar1 = 0;
    static char bloqueo_corral1[5] = { 'A','A','A','A','A' }, bloqueo_corral2[5] = { 'A','A','A','A','A' };

    if(turno == true)
    {
        switch (dado)
        {
            case 1:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar > 0 && robar < 6)
                {
                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 10);

                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;
                    } while (robar < 0 || robar > 5);

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 10);

                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }

            break;
            case 2:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                std::cin >> robar;
                if (bloqueo_corral2[robar-1] != 'B' && robar > 0 && robar < 6)
                {

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;

                        } while (robar1 > 0 || robar1 < 11);

                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
                else
                {

                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;

                    } while (bloqueo_corral2[robar-1] == 'B' || robar < 0 || robar > 6);

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;

                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;

                        } while (robar1 < 0 || robar1 > 11);

                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
            break;
            case 3:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar >= 1 && robar <= 5)
                {
                    std::cout << "\n";
                    std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                    std::cin >> robar1;

                    if (robar1 > 0 && robar1 < 6 && bloqueo_corral2[robar1-1] != 'B')
                    {
                        std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 5 || bloqueo_corral2[robar1-1] == 'B');
                        std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                    }

                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;
                    } while (robar < 0 || robar > 5);
                    std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                    std::cin >> robar1;

                    if (robar1 >= 1 && robar1 <= 5 && bloqueo_corral2[robar1-1] == 'B')
                    {
                        std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 5 || bloqueo_corral2[robar1-1] == 'B');
                        std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                    }

                }
                auxiliar[0] = true;
                auxiliar[2] = true;
            break;
            case 4:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar > 0 && robar < 6)
                {
                    std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                    std::cin >> robar1;
                    if (robar != robar1 && robar1 < 6 && robar1 > 0)
                    {
                        std::swap(corral1[robar-1].valor, corral1[robar1-1].valor);
                        std::swap(corral1[robar-1].palo, corral1[robar1-1].palo);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O LA CARTA ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                            std::cin >> robar1;
                        } while (robar == robar1);
                        std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                        std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                    }

                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                        std::cin >> robar;

                    } while (robar < 0 || robar > 5);

                    std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                    std::cin >> robar1;

                    if (robar != robar1 && robar1 < 6 && robar1 > 0) {
                        std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                        std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                            std::cin >> robar1;
                        } while (robar == robar1 || robar1 >6 || robar1 <1);
                        std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                        std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                    }
                }
            break;
            case 5:
                std::cout << "\n";
                std::cout << "BLOQUEA UNA CARTA DE TU MAZO PARA NO PODER SER ROBADA\n";
                std::cin >> robar;
                if (bloqueo_corral1[robar-1] != 'B')
                {
                    bloqueo_corral1[robar-1] = 'B';
                }
                else
                {
                    do
                    {
                        std::cout << "[LA CARTA QUE SELECCIONO YA ESTA BLOQUEADA, INGRESE OTRA]\n";
                        std::cin >> robar;
                    } while (bloqueo_corral1[robar-1] == 'B');
                    bloqueo_corral1[robar-1] = 'B';
                }
            break;
            case 6:

                std::cout << "\n";
                std::cout << "ELIJA CUALQUIERA DE LAS CARAS DEL DADO O LA CARA 6 PARA SALTAR EL TURNO\n";

                std::cin >> dado;

                switch (dado)
                {
                case 1:
                    std::cout << "\n";
                    std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                    std::cin >> robar;
                    if (robar > 0 && robar < 6)
                    {
                        std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                        std::cin >> robar1;
                        if (robar1 > 0 && robar1 < 11)
                        {
                            std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                                std::cin >> robar1;
                            } while (robar1 < 0 || robar1 > 10);

                            std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar;
                        } while (robar < 0 || robar > 5);

                        std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                        std::cin >> robar1;
                        if (robar1 > 0 && robar1 < 11)
                        {
                            std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                                std::cin >> robar1;
                            } while (robar1 < 0 || robar1 > 10);

                            std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                    }

                    break;
                case 2:
                    std::cout << "\n";
                    std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                    std::cin >> robar;
                    if (bloqueo_corral2[robar-1] != 'B' && robar > 0 && robar < 6)
                    {

                        std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                        std::cin >> robar1;
                        if (robar1 > 0 && robar1 < 11)
                        {
                            std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                                std::cin >> robar1;

                            } while (robar1 > 0 || robar1 < 11);

                            std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                    }
                    else
                    {

                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar;

                        } while (bloqueo_corral2[robar-1] == 'B' || robar < 0 || robar > 6);

                        std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                        std::cin >> robar1;

                        if (robar1 > 0 && robar1 < 11)
                        {
                            std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                                std::cin >> robar1;

                            } while (robar1 < 0 || robar1 > 11);

                            std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                            std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                        }
                    }
                    break;
                case 3:
                    std::cout << "\n";
                    std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                    std::cin >> robar;
                    if (robar >= 1 && robar <= 5)
                    {
                        std::cout << "\n";
                        std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                        std::cin >> robar1;

                        if (robar1 > 0 && robar1 < 6 && bloqueo_corral2[robar1-1] != 'B')
                        {
                            std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                                std::cin >> robar1;
                            } while (robar1 < 0 || robar1 > 5 || bloqueo_corral2[robar1-1] == 'B');
                            std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                        }

                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar;
                        } while (robar < 0 || robar > 5);
                        std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                        std::cin >> robar1;

                        if (robar1 >= 1 && robar1 <= 5 && bloqueo_corral2[robar1-1] == 'B')
                        {
                            std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                                std::cin >> robar1;
                            } while (robar1 < 0 || robar1 > 5 || bloqueo_corral2[robar1-1] == 'B');
                            std::swap(corral1[robar - 1].palo, corral2[robar1 - 1].palo);
                            std::swap(corral1[robar - 1].valor, corral2[robar1 - 1].valor);
                        }

                    }
                    auxiliar[0] = true;
                    auxiliar[2] = true;
                    break;
                case 4:
                    std::cout << "\n";
                    std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                    std::cin >> robar;
                    if (robar > 0 && robar < 6)
                    {
                        std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                        std::cin >> robar1;
                        if (robar != robar1 && robar1 < 6 && robar1 > 0)
                        {
                            std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                            std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O LA CARTA ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                                std::cin >> robar1;
                            } while (robar == robar1);
                            std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                            std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                        }

                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                            std::cin >> robar;

                        } while (robar < 0 || robar > 5);

                        std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                        std::cin >> robar1;

                        if (robar != robar1 && robar1 < 6 && robar1 > 0) {
                            std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                            std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                        }
                        else
                        {
                            do
                            {
                                std::cout << "\n";
                                std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                                std::cin >> robar1;
                            } while (robar == robar1 || robar1 > 6 || robar1 < 1);
                            std::swap(corral1[robar - 1].valor, corral1[robar1 - 1].valor);
                            std::swap(corral1[robar - 1].palo, corral1[robar1 - 1].palo);
                        }
                    }
                    break;
                case 5:
                    std::cout << "\n";
                    std::cout << "BLOQUEA UNA CARTA DE TU MAZO PARA NO PODER SER ROBADA\n";
                    std::cin >> robar;
                    if (bloqueo_corral1[robar - 1] != 'B')
                    {
                        bloqueo_corral1[robar - 1] = 'B';
                    }
                    else
                    {
                        do
                        {
                            std::cout << "[LA CARTA QUE SELECCIONO YA ESTA BLOQUEADA, INGRESE OTRA]\n";
                            std::cin >> robar;
                        } while (bloqueo_corral1[robar - 1] == 'B');
                        bloqueo_corral1[robar-1] = 'B';
                    }
                    break;
                case 6:
                    auxiliar[3] = true;
                    break;
                }
            break;
        }
    }
    else if (turno == false)
    {
        switch (dado)
        {
            case 1:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar > 0 && robar < 6)
                {
                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 10);

                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;
                    } while (robar < 0 || robar > 5);

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 10);

                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }

        break;
        case 2:
            std::cout << "\n";
            std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
            std::cin >> robar;
            if (bloqueo_corral1[robar-1] != 'B' && robar > 0 && robar < 6)
            {

                std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                std::cin >> robar1;
                if (robar1 > 0 && robar1 < 11)
                {
                    std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                    std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                        std::cin >> robar1;

                    } while (robar1 < 0 || robar1 > 11);

                    std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                    std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                }
            }
            else
            {

                do
                {
                    std::cout << "\n";
                    std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                    std::cin >> robar;

                } while (bloqueo_corral1[robar-1] == 'B' || robar < 0 || robar > 6);

                std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                std::cin >> robar1;

                if (robar1 > 0 && robar1 < 11)
                {
                    std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                    std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                        std::cin >> robar1;

                    } while (robar1 < 0 || robar1 > 11);

                    std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                    std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                }
            }
        break;

        case 3:
            std::cout << "\n";
            std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
            std::cin >> robar;
            if (robar >= 1 && robar <= 5)
            {
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                std::cin >> robar1;

                if (robar1 > 0 && robar1 < 6 && bloqueo_corral1[robar1-1] != 'B')
                {
                    std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                    std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar1;
                    } while (robar1 < 0 || robar1 > 5 || bloqueo_corral1[robar1-1] == 'B');
                    std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                    std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                }

            }
            else
            {
                do
                {
                    std::cout << "\n";
                    std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                    std::cin >> robar;
                } while (robar < 0 || robar > 5);
                std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                std::cin >> robar1;

                if (robar1 >= 1 && robar1 <= 5 && bloqueo_corral1[robar1-1] == 'B')
                {
                    std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                    std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar1;
                    } while (robar1 < 0 || robar1 > 5 || bloqueo_corral1[robar1 - 1] == 'B');
                    std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                    std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                }

            }
            auxiliar[0] = true;
            auxiliar[1] = true;
        break;

        case 4:
            std::cout << "\n";
            std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
            std::cin >> robar;
            if (robar > 0 && robar < 6)
            {
                std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                std::cin >> robar1;
                if (robar != robar1 && robar1 > 0 && robar1 < 6)
                {
                    std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                    std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                        std::cin >> robar1;
                    } while (robar != robar1 || robar1 < 1 || robar1 > 5);
                    std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                    std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                }

            }
            else
            {
                do
                {
                    std::cout << "\n";
                    std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                    std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                    std::cin >> robar;

                } while (robar < 1 || robar > 5);

                std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                std::cin >> robar1;

                if (robar1 > 0 && robar1 < 6 && robar1 != robar) {
                    std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                    std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                        std::cin >> robar1;
                    } while (robar == robar1 || robar1 < 1 || robar1 > 5);
                    std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                    std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                }
            }
        break;

        case 5:
            std::cout << "\n";
            std::cout << "BLOQUEA UNA CARTA DE TU MAZO PARA NO PODER SER ROBADA\n";
            std::cin >> robar;
            if (bloqueo_corral2[robar-1] != 'B')
            {
                bloqueo_corral2[robar-1] = 'B';
            }
            else
            {
                do
                {
                    std::cout << "[LA CARTA QUE SELECCIONO YA ESTA BLOQUEADA, INGRESE OTRA]\n";
                    std::cin >> robar;
                } while (bloqueo_corral2[robar-1] == 'B');
                bloqueo_corral2[robar] = 'B';
            }
        break;

        case 6:
            std::cout << "\n";
            std::cout << "ELIJA CUALQUIERA DE LAS CARAS DEL DADO O LA CARA 6 PARA SALTAR EL TURNO\n";

            std::cin >> dado;

            switch (dado)
            {
            case 1:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar > 0 && robar < 6)
                {
                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 10);

                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;
                    } while (robar < 0 || robar > 5);

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 10);

                        std::swap(corral2[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }

                break;
            case 2:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                std::cin >> robar;
                if (bloqueo_corral1[robar-1] != 'B' && robar > 0 && robar < 6)
                {

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;
                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;

                        } while (robar1 < 0 || robar1 > 11);

                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
                else
                {

                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;

                    } while (bloqueo_corral1[robar-1] == 'B' || robar < 0 || robar > 6);

                    std::cout << "ELIJA UNA CARTA DEL MAZO\n";
                    std::cin >> robar1;

                    if (robar1 > 0 && robar1 < 11)
                    {
                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA POR FAVOR, ELIJA UNA CARTA DEL 1 al 10]\n";
                            std::cin >> robar1;

                        } while (robar1 < 0 || robar1 > 11);

                        std::swap(corral1[robar - 1].palo, mazo[robar1 - 1].palo);
                        std::swap(corral1[robar - 1].valor, mazo[robar1 - 1].valor);
                    }
                }
                break;

            case 3:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar >= 1 && robar <= 5)
                {
                    std::cout << "\n";
                    std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                    std::cin >> robar1;

                    if (robar1 > 0 && robar1 < 6 && bloqueo_corral1[robar1-1] != 'B')
                    {
                        std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 5 || bloqueo_corral1[robar1-1] == 'B');
                        std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                    }

                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cin >> robar;
                    } while (robar < 0 || robar > 5);
                    std::cout << "ELIJA UNA CARTA DEL CORRAL RIVAL\n";
                    std::cin >> robar1;

                    if (robar1 >= 1 && robar1 <= 5 && bloqueo_corral1[robar1-1] == 'B')
                    {
                        std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[LA CARTA ES INVALIDA O ESTA BLOQUEADA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                            std::cin >> robar1;
                        } while (robar1 < 0 || robar1 > 5 || bloqueo_corral1[robar1-1] == 'B');
                        std::swap(corral2[robar - 1].palo, corral1[robar1 - 1].palo);
                        std::swap(corral2[robar - 1].valor, corral1[robar1 - 1].valor);
                    }

                }
                auxiliar[0] = true;
                auxiliar[1] = true;
                break;

            case 4:
                std::cout << "\n";
                std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                std::cin >> robar;
                if (robar > 0 && robar < 6)
                {
                    std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                    std::cin >> robar1;
                    if (robar != robar1 && robar1 > 0 && robar1 < 6)
                    {
                        std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                        std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                            std::cin >> robar1;
                        } while (robar != robar1 || robar1 < 1 || robar1 > 5);
                        std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                        std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                    }

                }
                else
                {
                    do
                    {
                        std::cout << "\n";
                        std::cout << "[LA CARTA ES INVALIDA, POR FAVOR, ELIJA UNA CARTA DEL 1 al 5]\n";
                        std::cout << "ELIJA UNA CARTA DE SU CORRAL\n";
                        std::cin >> robar;

                    } while (robar < 1 || robar > 5);

                    std::cout << "ELIJA OTRA CARTA DE SU CORRAL\n";
                    std::cin >> robar1;

                    if (robar1 > 0 && robar1 < 6 && robar1 != robar) {
                        std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                        std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                    }
                    else
                    {
                        do
                        {
                            std::cout << "\n";
                            std::cout << "[ESTAS INTENTANDO INTERCAMBIAR LA MISMA CARTA O ESTA FUERA DE RANGO, ELIJE OTRA]\n";
                            std::cin >> robar1;
                        } while (robar == robar1 || robar1 < 1 || robar1 > 5);
                        std::swap(corral2[robar - 1].valor, corral2[robar1 - 1].valor);
                        std::swap(corral2[robar - 1].palo, corral2[robar1 - 1].palo);
                    }
                }
                break;

            case 5:
                std::cout << "\n";
                std::cout << "BLOQUEA UNA CARTA DE TU MAZO PARA NO PODER SER ROBADA\n";
                std::cin >> robar;
                if (bloqueo_corral2[robar - 1] != 'B')
                {
                    bloqueo_corral2[robar - 1] = 'B';
                }
                else
                {
                    do
                    {
                        std::cout << "[LA CARTA QUE SELECCIONO YA ESTA BLOQUEADA, INGRESE OTRA]\n";
                        std::cin >> robar;
                    } while (bloqueo_corral2[robar - 1] != 'B');
                    bloqueo_corral2[robar-1] = 'B';
                }
                break;

            case 6:
                auxiliar[4] = true;;
                break;
            }
        break;
        }
    }

}

void pre_estadisticas(std::vector<Carta> corral1, std::vector<Carta> corral2, std::string nombre1, std::string nombre2, bool& verificacion)
{
    std::vector<Carta> pre_conteo(5);
    std::vector<Carta> pre_conteoRACISTA(5);
    int contador_de_cartas = 0;
    int contador_de_cartas1 = 0;
    int contador_de_cartasRACISTA = 0;
    int contador_de_cartas1RACISTA = 0;

    pre_conteo[0].valor = "10 ";
    pre_conteo[1].valor = "J  ";
    pre_conteo[2].valor = "Q  ";
    pre_conteo[3].valor = "K  ";
    pre_conteo[4].valor = "A  ";
    pre_conteoRACISTA[0].valor = "K  ";
    pre_conteoRACISTA[1].valor = "K  ";
    pre_conteoRACISTA[2].valor = "K  ";
    pre_conteoRACISTA[3].valor = "K  ";
    pre_conteoRACISTA[4].valor = "K  ";

    for (int i = 0; i < 5; i++)
    {
        if (pre_conteo[i].valor == corral1[i].valor)
        {
            contador_de_cartas++;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (pre_conteo[i].valor == corral2[i].valor)
        {
            contador_de_cartas1++;
        }
    }


    if (contador_de_cartas == 5 || contador_de_cartas1 == 5)
    {
        verificacion = true;
    }

}

void estadisticas(std::vector<Carta> &corral1, std::vector<Carta> &corral2, std::string &nombre1, std::string &nombre2, std::vector<bool>& auxiliar)
{
    system("cls");

    std::vector<Carta> conteo(5);
    std::string ultimo_ganador;

    std::vector<bool>auxiliar1(5, false);
    static std::vector<bool> auxiliar_ant(5,false);

    for (int i = 0; i < 5; i++)
    {
        auxiliar1[i] = auxiliar[i];
    }

    int contadorc1 = 0;
    int contadorc2 = 0;
    int malubicadac1 = 0;
    int malubicadac2 = 0;
    static int contadorc1_ant = 0;
    static int contadorc2_ant = 0;
    static int malubicadac1_ant = 0;
    static int malubicadac2_ant = 0;
    static int ultima_robada = 0;
    static int robadoc1 = 0;
    static int robadoc2 = 0;
    static int saltoc1 = 0;
    static int saltoc2 = 0;

    conteo[0].valor = "10 ";
    conteo[1].valor = "J  ";
    conteo[2].valor = "Q  ";
    conteo[3].valor = "K  ";
    conteo[4].valor = "A  ";

    for (int i = 0; i < 5; i++)
    {
        if (corral1[i].valor == conteo[i].valor)
        {
            contadorc1++;
        }
        else if(corral1[i].valor != conteo[i].valor)
        {
            malubicadac1++;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (corral2[i].valor == conteo[i].valor)
        {
            contadorc2++;
        }
        else if(corral2[i].valor != conteo[i].valor)
        {
            malubicadac2++;
        }
    }



    if (contadorc1 == 5)
    {
        contadorc1_ant = contadorc1;
        malubicadac2_ant = malubicadac2;
        contadorc1 = 0;
        contadorc2 = 0;
        malubicadac2 = 0;
        malubicadac1 = 0;
        ultimo_ganador = nombre1;
        for (int i = 0; i < 5; i++)
        {
            auxiliar_ant[i] = auxiliar1[i];
        }

        if (auxiliar_ant[0] == true)
        {
            ultima_robada = 5;
        }

        if (auxiliar_ant[1] == true)
        {
            robadoc1 = 0;
        }
        else
        {
            robadoc1 = 10;
        }

        if (auxiliar_ant[2] == true)
        {
            robadoc2 = 0;
        }
        else
        {
            robadoc2 = 10;
        }

        if (auxiliar_ant[3] == true)
        {
            saltoc1 = 0;
        }
        else
        {
            saltoc1 = 10;
        }

        if (auxiliar_ant[4] == true)
        {
            saltoc2 = 0;
        }
        else
        {
            saltoc2 = 10;
        }

    }

    if (contadorc2 == 5)
    {
        contadorc2_ant = contadorc2;
        malubicadac1_ant = malubicadac1;
        contadorc2 = 0;
        contadorc1 = 0;
        malubicadac1 = 0;
        malubicadac2 = 0;
        ultimo_ganador = nombre2;
        for (int i = 0; i < 5; i++)
        {
            auxiliar_ant[i] = auxiliar1[i];
        }

        if (auxiliar_ant[0] == true)
        {
            ultima_robada = 5;
        }

        if (auxiliar_ant[1] == true)
        {
            robadoc1 = 0;
        }
        else
        {
            robadoc1 = 10;
        }

        if (auxiliar_ant[2] == true)
        {
            robadoc2 = 0;
        }
        else
        {
            robadoc2 = 10;
        }

        if (auxiliar_ant[3] == true)
        {
            saltoc1 = 0;
        }
        else
        {
            saltoc1 = 10;
        }

        if (auxiliar_ant[4] == true)
        {
            saltoc2 = 0;
        }
        else
        {
            saltoc2 = 10;
        }
    }
    if(contadorc1_ant == 5)
    {
        std::cout << "CLUTCH\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "HITO                   " << ultimo_ganador << "\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "Ganar la partida                         " << "15 PUNTOS\n";
        std::cout << "Robo última carta al jugador rival       " << ultima_robada << " PUNTOS\n";
        std::cout << "Cartas mal ubicadas del rival            " << malubicadac2_ant*5 << " PUNTOS\n";
        std::cout << "Sin pasar de turno                       " << saltoc1 << " PUNTOS\n";
        std::cout << "Sin haber sufrido un robo del rival      " << robadoc2 << " PUNTOS\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "GANADOR                "  << ultimo_ganador << "\n";
        std::cout << "TOTAL:                 " << 15+(malubicadac2_ant*5)+ultima_robada+saltoc1+robadoc2 << " PUNTOS\n";
        std::cout << "\n";
        system("pause");
        std::cin.clear();

    }
    else if (contadorc2_ant == 5)
    {
        std::cout << "CLUTCH\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "HITO                   " << ultimo_ganador << "\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "Ganar la partida                         " << "15 PUNTOS\n";
        std::cout << "Robo última carta al jugador rival       " << ultima_robada << " PUNTOS\n";
        std::cout << "Cartas mal ubicadas del rival            " << malubicadac1_ant * 5 << " PUNTOS\n";
        std::cout << "Sin pasar de turno                       " << saltoc2 << " PUNTOS\n";
        std::cout << "Sin haber sufrido un robo del rival      " << robadoc1 << " PUNTOS\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "GANADOR                " << ultimo_ganador << "\n";
        std::cout << "TOTAL:                 " << 15 + (malubicadac1_ant * 5) + ultima_robada + saltoc2 + robadoc1 << " PUNTOS\n";
        std::cout << "\n";
        system("pause");
        std::cin.clear();
    }
    else
    {
        std::cout << "AUN NO SE GANO NINGUNA PARTIDA\n";
        std::cout << "\n";
        system("pause");
    }

    std::cin.ignore();
}
