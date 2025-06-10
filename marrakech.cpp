#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

// Códigos de color ANSI para terminal
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string BOLD = "\033[1m";
const string BG_RED = "\033[41m";
const string BG_GREEN = "\033[42m";
const string BG_BLUE = "\033[44m";

struct Jugador {

	string nombre;
	string color;
	int n_alfombras;
	int total_monedas;
	int puntaje_total;
	bool activo;
    string color_display; // Para mostrar en pantalla

};

struct HassamEstado {
	int fila;
	int columna;
	string orientacion;
};

struct EstadoPago {
	int monedasPagadas;
	bool jugadorEliminado;
};

// Funcion que inicializa el tablero
void inicializarTablero(char tablero[7][7]);

// Funcion que lanza un dado (1-6)
int lanzarDado();

// Funcion para que el jugador elija la nueva orientaciC3n de Hassam
string orientarHassam(string orientacion_actual);

// Mueve a Hassam segC:n orientacion y pasos, respetando el mosaico
HassamEstado moverHassam(int fila, int columna, string orientacion, int pasos);

// Verifica si dos casillas son va!lidas para colocar una alfombra segun las reglas
bool validarColocacion(char tablero[7][7], int f1, int c1, int f2, int c2, char colorJugador);

// Muestra opciones y permite al jugador colocar su alfombra, devuelve si tuvo C)xito
bool colocarAlfombra(char tablero[7][7], HassamEstado hassam, char colorJugador, Jugador jugadores[2]);

// Muestra el tablero completo con simbolos de cada jugador y puntos vacC-os como '.'
void mostrarTablero(char tablero[7][7], HassamEstado hassam, Jugador jugadores[2]);

// Calcula el puntaje total del jugador (alfombras + monedas)
int calcularPuntaje(Jugador jugador, char tablero[7][7]);

// Devuelve el C-ndice del jugador ganador (0 o 1) segC:n puntaje final
int elegirGanador(Jugador jugadores[2], char tablero[7][7]);

// Guarda los datos de los jugadores y del ganador en un archivo .txt
void guardarPartida(Jugador jugadores[2], int ganadorIndex, char tablero[7][7]);

// EvalC:a cuC!ntas monedas debe pagar un jugador y si ha sido eliminado (alfombras conectadas)
EstadoPago pagarAOponente(char tablero[7][7], int fila, int columna, char colorAlfombra, int monedasJugador);

void mostrarTitulo() {
    cout << BOLD << CYAN << "\n";
    cout << "------------------------------------------------------------\n";
    cout << "|                                                          |\n";
    cout << "|              🕌 EL JUEGO DE MARRAKECH 🕌                   |\n";
    cout << "|                                                          |\n";
    cout << "|          🧶 El mercado de alfombras espera!               |\n";
    cout << "|                                                          |\n";
    cout << "------------------------------------------------------------\n";
    cout << RESET << "\n";
}


void inicializarJugadores(Jugador jugadores[2]) {
    string colores_disponibles[6] = {"Rojo", "Azul", "Verde", "Amarillo", "Magenta", "Cian"};
    char chars_colores[6] = {'R', 'A', 'V', 'M', 'G', 'C'};
    string display_colores[6] = {RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN};
    
    cout << BOLD << "🎮 REGISTRO DE JUGADORES\n" << RESET;
    cout << "═══════════════════════════\n\n";
    
    for (int i = 0; i < 2; i++) {
        cout << BOLD << "👤 Jugador " << (i + 1) << ":\n" << RESET;
        
        // Nombre del jugador
            cout << "  Ingrese su nombre: ";
            cin>> jugadores[i].nombre;
        
        
        // Selección de color
        cout << "\n  🎨 Colores disponibles:\n";
        for (int j = 0; j < 6; j++) {
            cout << "    " << (j + 1) << ". " << display_colores[j] << colores_disponibles[j] << RESET << "\n";
        }
        
        int opcion_color;
        while (true) {
            cout << "  Seleccione su color (1-6): ";
            cin >> opcion_color;
            
            if (opcion_color >= 1 && opcion_color <= 6) { 
                jugadores[i].color = chars_colores[opcion_color - 1];
                jugadores[i].color_display = display_colores[opcion_color - 1];
                    break;
            } else {
                cout << RED << "  ❌ Opción inválida. Seleccione 1-6.\n" << RESET;
            }
            cin.clear();
            cin.ignore(1000, '\n');
        }
        
        // Inicializar stats
        jugadores[i].n_alfombras = 10;
        jugadores[i].total_monedas = 20;
        jugadores[i].puntaje_total = 0;
        jugadores[i].activo = true;
        
        cout << GREEN << "  ✅ " << jugadores[i].nombre << " registrado con color " 
             << jugadores[i].color_display << colores_disponibles[opcion_color - 1] << RESET << "\n\n";
        
        cin.ignore(); // Limpiar buffer
    }
}

void inicializarTablero(char tablero[7][7]) {
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            tablero[i][j] = ' ';
}

int lanzarDado() {
	return std::rand() % 6 + 1;
}



string orientarHassam(string orientacion_actual) {
    
  
    
    int opcion;
    while (true) {
        cout << "¿A dónde desea orientar a Hassam?" << endl;
        cout << "1. Girar a la izquierda." << endl;
        cout << "2. Girar a la derecha." << endl;
        cout << "3. Mantener posición actual: " << orientacion_actual << endl;
        cout << "Seleccione una opción (1-3): ";
        cin >> opcion;

        if (opcion < 1 || opcion > 3) {
            cin.clear(); // limpia error
            cin.ignore(1000, '\n'); // descarta entrada incorrecta
            cout << "❌ Opción inválida. Intente de nuevo.\n";
            continue;
        }

        break;
    }

    if (opcion == 1) {
        if (orientacion_actual == "N") orientacion_actual = "O";
        else if (orientacion_actual == "O") orientacion_actual = "S";
        else if (orientacion_actual == "S") orientacion_actual = "E";
        else if (orientacion_actual == "E") orientacion_actual = "N";
    } else if (opcion == 2) {
        if (orientacion_actual == "N") orientacion_actual = "E";
        else if (orientacion_actual == "E") orientacion_actual = "S";
        else if (orientacion_actual == "S") orientacion_actual = "O";
        else if (orientacion_actual == "O") orientacion_actual = "N";
    }

    return orientacion_actual;
}


HassamEstado moverHassam(int fila, int columna, string orientacion, int pasos) {
	if (orientacion == "N") {
		fila -= pasos;
		if (fila < 0) {
			int exceso = -fila;
			if (columna == 0) {
				orientacion = "E";
				columna += exceso;
				fila = 0;
			} else {
				if (columna % 2 == 0) {
					orientacion = "S";
					columna -= 1;
					fila = exceso - 1;
				} else {
					orientacion = "S";
					columna += 1;
					fila = exceso - 1;
				}
			}
		}
	}

	else if (orientacion == "S") {
		fila += pasos;
		if (fila > 6) {
			int exceso = fila - 6;
			if (columna == 6) {
				orientacion = "O";
				columna -= exceso;
				fila = 6;
			} else {
				if (columna % 2 == 0) {
					orientacion = "N";
					columna += 1;
					fila = 6 - (exceso - 1);
				} else {
					orientacion = "N";
					columna -= 1;
					fila = 6 - (exceso - 1);
				}
			}
		}
	}

	else if (orientacion == "E") {
		columna += pasos;
		if (columna > 6) {
			int exceso = columna - 6;
			if (fila == 6) {
				orientacion = "S";
				fila -= exceso;
				columna = 6;
			} else {
				if (fila % 2 == 0) {
					orientacion = "O";
					fila += 1;
					columna = 6 - (exceso - 1);
				} else {
					orientacion = "O";
					fila -= 1;
					columna = 6 - (exceso - 1);
				}
			}
		}
	}

	else if (orientacion == "O") {
		columna -= pasos;
		if (columna < 0) {
			int exceso = -columna;
			if (fila == 0) {
				orientacion = "S";
				columna = 0;
				fila += pasos;
			} else if (fila % 2 == 1) {
				orientacion = "E";
				fila += 1;
				columna = exceso - 1;
			} else {
				orientacion = "E";
				fila -= 1;
				columna = exceso;
			}
		}
	}
	HassamEstado nuevoEstado;
	nuevoEstado.fila = fila;
	nuevoEstado.columna = columna;
	nuevoEstado.orientacion = orientacion;
	return nuevoEstado;
}

EstadoPago pagarAOponente(char tablero[7][7], int fila, int columna, char colorAlfombra, int monedasJugador) {
	EstadoPago resultado = {0, false};
	if (tablero[fila][columna] != colorAlfombra) return resultado;

	bool visitado[7][7] = {};
	int pilaF[49], pilaC[49], tope = 0;
	pilaF[tope] = fila;
	pilaC[tope] = columna;
	visitado[fila][columna] = true;
	tope++;

	 int casillas_conectadas = 0;
	while (tope > 0) {
		tope--;
		int f = pilaF[tope], c = pilaC[tope];
		 casillas_conectadas++;

		int df[4] = {-1, 1, 0, 0};
		int dc[4] = {0, 0, -1, 1};

		for (int i = 0; i < 4; i++) {
			int nf = f + df[i], nc = c + dc[i];
			if (nf >= 0 && nf < 7 && nc >= 0 && nc < 7 && !visitado[nf][nc] && tablero[nf][nc] == colorAlfombra) {
				pilaF[tope] = nf;
				pilaC[tope] = nc;
				tope++;
				visitado[nf][nc] = true;
			}
		}
	}

 


	// Visualizacion
	cout << "\n> Alfombras conectadas del oponente:\n";
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			cout << (visitado[i][j] ? 'X' : tablero[i][j]) << ' ';
		}
		cout << endl;
	}

	  cout << "\n" << BOLD << "💰 PAGO AL OPONENTE\n" << RESET;
    cout << "Casillas de alfombra conectadas: " << YELLOW << casillas_conectadas << RESET << "\n";
    cout << "Monedas disponibles: " << GREEN << monedasJugador << RESET << "\n";

    if (monedasJugador >= casillas_conectadas) {
        resultado.monedasPagadas = casillas_conectadas;
        cout << "Monedas a pagar: " << RED << casillas_conectadas << RESET << "\n";
        cout << GREEN << "✅ Pago realizado correctamente.\n" << RESET;
    } else {
        resultado.monedasPagadas = monedasJugador;
        resultado.jugadorEliminado = true;
        cout << "Monedas a pagar: " << RED << monedasJugador << " (todas las disponibles)" << RESET << "\n";
        cout << RED << "❌ ¡No tiene suficientes monedas! JUGADOR ELIMINADO.\n" << RESET;
    }


	return resultado;
}

bool colocarAlfombra(char tablero[7][7], HassamEstado hassam, char colorJugador, Jugador jugadores[2]) {
    mostrarTablero(tablero,hassam,jugadores);
	int f = hassam.fila;
	int c = hassam.columna;

	int df[4] = {-1, 1, 0, 0};  // arriba, abajo, izq, der
	int dc[4] = {0, 0, -1, 1};

	int opcionesF1[4], opcionesC1[4], opcionesF2[4], opcionesC2[4];
	int totalOpciones = 0;

	cout << "Opciones validas para colocar alfombra adyacente a [" << f << "][" << c << "]:\n";

	for (int i = 0; i < 4; i++) {
		int f1 = f;
		int c1 = c;
		int f2 = f + df[i];
		int c2 = c + dc[i];

		if (f2 < 0 || f2 >= 7 || c2 < 0 || c2 >= 7) continue;

		char t1 = tablero[f1][c1];
		char t2 = tablero[f2][c2];

		if (validarColocacion(tablero, f1, c1, f2, c2, colorJugador)) {
			opcionesF1[totalOpciones] = f1;
			opcionesC1[totalOpciones] = c1;
			opcionesF2[totalOpciones] = f2;
			opcionesC2[totalOpciones] = c2;

			cout << (totalOpciones + 1) << ". [" << f1 << "][" << c1 << "] y [" << f2 << "][" << c2 << "]\n";
			totalOpciones++;
		}
	}

	if (totalOpciones == 0) {
		cout << "No hay opciones validas para colocar una alfombra.\n";
		return false;
	}

        int eleccion;
        while (true) {
            cout << "Seleccione una opción: ";
            cin >> eleccion;
        
            if (eleccion < 1 || eleccion > totalOpciones) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "❌ Opción inválida. Intente de nuevo.\n";
                continue;
            }
        
            break;
        }

	int f1 = opcionesF1[eleccion - 1];
	int c1 = opcionesC1[eleccion - 1];
	int f2 = opcionesF2[eleccion - 1];
	int c2 = opcionesC2[eleccion - 1];

	tablero[f1][c1] = colorJugador;
	tablero[f2][c2] = colorJugador;

	cout << "b   Alfombra colocada en [" << f1 << "][" << c1 << "] y [" << f2 << "][" << c2 << "]\n";
	return true;
}

bool validarColocacion(char tablero[7][7], int f1, int c1, int f2, int c2, char colorJugador) {
    char t1 = tablero[f1][c1];
    char t2 = tablero[f2][c2];
    
    // Regla a: Dos casillas vacías
    if (t1 == ' ' && t2 == ' ') return true;
    
    // Regla b: Una vacía y una alfombra (no propia)
    if ((t1 == ' ' && t2 != ' ' && t2 != colorJugador) || 
        (t2 == ' ' && t1 != ' ' && t1 != colorJugador)) return true;
    
    // Regla c: Dos alfombras distintas, ninguna propia
    if (t1 != ' ' && t2 != ' ' && t1 != t2 &&
        t1 != colorJugador && t2 != colorJugador) return true;

    return false;
}


void mostrarTablero(char tablero[7][7], HassamEstado hassam, Jugador jugadores[2]) {


    cout << "\n"  << "🧱 Estado actual del tablero:\n\n";

    // Encabezado de columnas
    cout << "    ";
    for (int col = 0; col < 7; col++) {
        cout << " " << col << "  ";
    }
    cout << endl;

    // Separador superior
    cout << "   +";
    for (int j = 0; j < 7; j++) {
        cout << "---+";
    }
    cout << endl;

    for (int i = 0; i < 7; i++) {
        cout << " " << i << " |";

        for (int j = 0; j < 7; j++) {
            string contenido = "   ";

            if (i == hassam.fila && j == hassam.columna && tablero[i][j] == ' ') {
                // Mostrar flecha de Hassam si está en casilla vacía
                if (hassam.orientacion == "N") contenido = BOLD + WHITE + BG_BLUE + " ^ " + RESET;
                else if (hassam.orientacion == "S") contenido = BOLD + WHITE + BG_BLUE + " v " + RESET;
                else if (hassam.orientacion == "E") contenido = BOLD + WHITE + BG_BLUE + " > " + RESET;
                else if (hassam.orientacion == "O") contenido = BOLD + WHITE + BG_BLUE + " < " + RESET;
            } else if (tablero[i][j] != ' ') {
                // Mostrar letra de la alfombra con su color
                char letra = tablero[i][j];
                string color_display = WHITE;

                for (int k = 0; k < 2; k++) {
                    if (jugadores[k].color[0] == letra) {
                        color_display = jugadores[k].color_display;
                        break;
                    }
                }

                contenido = color_display + " " + letra + " " + RESET;
            }

            cout << contenido << "|";
        }

        cout << endl;

        // Separador entre filas
        cout << "   +";
        for (int j = 0; j < 7; j++) {
            cout << "---+";
        }
        cout << endl;
    }

    // Leyenda
    cout << "\n" << "📘 Leyenda:\n";
    cout<< " A, B, ... → mitades de alfombra del jugador (en su color)\n";
    cout<< BOLD << WHITE << BG_BLUE << " ^ v < > " << RESET << " → Hassam (solo en casilla vacía)\n";

    cout << "\n"  << "📍 Posición actual de Hassam: [" << hassam.fila << "][" << hassam.columna << "]\n";
    cout << "🧭 Orientación actual: " << YELLOW << hassam.orientacion << RESET << "\n\n";
}






int calcularPuntaje(Jugador jugador, char tablero[7][7]) {
	int puntaje = jugador.total_monedas;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (tablero[i][j] == jugador.color[0]) {
				puntaje++;
			}
		}
	}

	return puntaje;
}

int elegirGanador(Jugador jugadores[2], char tablero[7][7]) {
	int puntajes[2];

	for (int i = 0; i < 2; i++) {
		puntajes[i] = calcularPuntaje(jugadores[i], tablero);
		jugadores[i].puntaje_total = puntajes[i]; // guardar para mostrar
	}

	if (puntajes[0] > puntajes[1]) return 0;
	else return 1;
}

void guardarPartida(Jugador jugadores[2], int ganadorIndex, char tablero[7][7]) {
    ofstream archivo("partida.txt");

    if (!archivo) {
        cout << "Error al guardar la partida.\n";
        return;
    }

    for (int i = 0; i < 2; i++) {
        int mitadesAlfombra = 0;

        for (int f = 0; f < 7; f++) {
            for (int c = 0; c < 7; c++) {
                if (tablero[f][c] == jugadores[i].color[0]) {
                    mitadesAlfombra++;
                }
            }
        }

        archivo << "Nombre: " << jugadores[i].nombre << endl;
        archivo << "Color: " << jugadores[i].color << endl;
        archivo << "Cantidad de alfombras: " << mitadesAlfombra << endl;
        archivo << "Cantidad de monedas: " << jugadores[i].total_monedas << endl;
        archivo << endl;
    }

    archivo << "El ganador es " << jugadores[ganadorIndex].nombre << endl;
    archivo.close();

    cout << "✅ Partida guardada correctamente en 'partida.txt'.\n";
}


int main() {
    srand(time(0));
    mostrarTitulo();

    char tablero[7][7];
    inicializarTablero(tablero);

    Jugador jugadores[2];

    // Registro de jugadores
    inicializarJugadores(jugadores);
    
    
   cout << "\n" << BOLD << GREEN << "🎮 ¡COMIENZA EL JUEGO!\n" << RESET;
    cout << BOLD << "📜 Reglas rapidas:\n" << RESET;
    cout << "• Cada jugador tiene 10 alfombras y 20 monedas\n";
    cout << "• En tu turno: orienta a Hassam, lanza el dado, muévelo\n";
    cout << "• Si caes en alfombra enemiga, pagas monedas\n";
    cout << "• Luego colocas una alfombra adyacente a Hassam\n";
    cout << "• Ganas por eliminación o por mayor puntaje al final\n\n";
    
    HassamEstado hassam = {3, 3, "N"};  // Posición inicial
    int turno = 0;
    
    
    mostrarTablero(tablero,hassam, jugadores);

    while (true) {


        if (!jugadores[turno].activo) {
            cout << jugadores[turno].nombre << " está eliminado. Se salta turno.\n";
            turno = 1 - turno;
            continue;
        }

        cout << "\nTurno de " << BOLD << jugadores[turno].nombre << RESET << " (Monedas: " << jugadores[turno].total_monedas
             << ", Alfombras restantes: " << jugadores[turno].n_alfombras << ")\n";

        hassam.orientacion = orientarHassam(hassam.orientacion);
        int pasos = lanzarDado();
        cout << "Dado: " << pasos << " pasos.\n";

        hassam = moverHassam(hassam.fila, hassam.columna, hassam.orientacion, pasos);

        cout << "Nueva posición de Hassam: [" << hassam.fila << "][" << hassam.columna << "]\n";

        // Pago si pisa alfombra enemiga
        char casilla = tablero[hassam.fila][hassam.columna];
        if (casilla != ' ' && casilla != jugadores[turno].color[0]) {
            EstadoPago pago = pagarAOponente(tablero, hassam.fila, hassam.columna, casilla, jugadores[turno].total_monedas);
            jugadores[turno].total_monedas -= pago.monedasPagadas;
            if (jugadores[turno].total_monedas < 0) jugadores[turno].total_monedas = 0;
            if (pago.jugadorEliminado) {
                jugadores[turno].activo = false;
                cout << jugadores[turno].nombre << " ha sido eliminado por falta de monedas.\n";
            }
        } else {
            cout << "No cayó sobre alfombra enemiga.\n";
        }

        // Colocar alfombra si puede
        if (jugadores[turno].activo && jugadores[turno].n_alfombras > 0) {
            bool colocada = colocarAlfombra(tablero, hassam, jugadores[turno].color[0], jugadores);
            if (colocada) {
                jugadores[turno].n_alfombras--;
            }
        mostrarTablero(tablero,hassam, jugadores);
        } else if (jugadores[turno].activo) {
            cout << jugadores[turno].nombre << " ya no tiene alfombras disponibles.\n";
        }

        // Verificar fin de partida
        int activos = 0, sinAlfombras = 0, idxUltimo = -1;
        for (int i = 0; i < 2; i++) {
            if (jugadores[i].activo) {
                activos++;
                idxUltimo = i;
                if (jugadores[i].n_alfombras == 0)
                    sinAlfombras++;
            }
        }

        if (activos == 1) {
            cout << "\nFin del juego: Solo queda un jugador activo.\n";
            cout << "El otro jugador ha sido eliminado por falta de monedas.\n";
            cout << "🏆 El ganador por supervivencia es: " << jugadores[idxUltimo].nombre << "\n";
             mostrarTablero(tablero,hassam, jugadores);
            guardarPartida(jugadores, idxUltimo, tablero);
            break;
        }

        if (sinAlfombras == 2) {
            cout << "\nFin del juego: Todos los jugadores han colocado todas sus alfombras.\n";
            cout << "Calculando puntajes...\n\n";

            for (int i = 0; i < 2; i++) {
                jugadores[i].puntaje_total = calcularPuntaje(jugadores[i], tablero);
                cout << jugadores[i].nombre << " (" << jugadores[i].color << "): "
                     << jugadores[i].puntaje_total << " puntos ("
                     << jugadores[i].total_monedas << " monedas + "
                     << jugadores[i].puntaje_total - jugadores[i].total_monedas << " mitades de alfombra)\n";
            }

            int ganadorIdx = elegirGanador(jugadores, tablero);
            cout << "\n🏆 El ganador por puntaje es: " << jugadores[ganadorIdx].nombre << "\n";

             mostrarTablero(tablero,hassam, jugadores);
            guardarPartida(jugadores, ganadorIdx, tablero);
            break;
        }

        // Cambiar de turno
        turno = 1 - turno;
    }

    return 0;
}


