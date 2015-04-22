#include "correpocoyo.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <exception>



template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }



int main(){

	  std::string s = "hola";

    CorrePocoyo<std::string> carrera1;
    carrera1.nuevoCorredor(s);
    carrera1.nuevoCorredor("hola2");
    carrera1.nuevoCorredor("hola3");

    std::cout << carrera1 <<std::endl;
    
		carrera1.seCansa("hola");
    
		CorrePocoyo<std::string> carrera2;
    carrera2.nuevoCorredor("chau");
    carrera2.nuevoCorredor("chau2");
    carrera2.nuevoCorredor("chau3");

		std::cout << carrera1 <<std::endl;
		std::cout << s << std::endl;
}
