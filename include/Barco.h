#ifndef BARCO_H
#define BARCO_H

#include <string>
#include <vector>

using namespace std;

class Barco{
	public:
		Barco(std::string nombre, int vida, vector<int> posiciones);
		void setNombre(std::string nombre);
		void setVida(int vida);
		void setPosiciones(vector<int> posciones);

		std::string getNombre();
		int getVida();
		vector<int> getPosiciones();
		
		

	private:
		std::string _nombre;
		int _vida;
		vector<int> posiciones;
};//Fin Barco

#endif