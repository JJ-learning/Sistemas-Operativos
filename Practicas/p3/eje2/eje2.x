const MAXIMO=20;
struct persona
{
	string nombre<MAXIMO>;
	string apellido<MAXIMO>;
	int edad;
	string provincia<MAXIMO>;
};
struct array_personas 
{
	persona Registros<MAXIMO>;
	int cant_devuelte;
};
struct parametros_b
{
	string provincia<MAXIMO>;
	int edad;
};

program PROGRAMA
{
	version BUSCAR
	{
		persona bucasApell(array_personas) = 1;
		persona menorEdad(array_personas) = 2;
	}=1;
}=0x30000019;
