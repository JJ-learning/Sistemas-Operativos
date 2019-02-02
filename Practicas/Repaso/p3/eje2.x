const MAXIMO=20;
struct persona
{
	string nombre<MAXIMO>;
	string apellido<MAXIMO>;
	int edad;
	string provincia<MAXIMO>;
};

struct vector_personas
{
	persona vector<MAXIMO>;
};

program PROGRAMA
{
	version BUSCAR
	{
		persona buscarApellido(vector_personas)=1;
		persona menorEdad(vector_personas)=2;
	}=1;
}=0x30000020;