#include<stdio.h>
#include<time.h>
#include<string.h>
#include <assert.h>
#include<math.h>
struct tranzactii
{
	float suma;
	char tip[20];
	char data[20];
	char descriere[100];
}tranz[200],nou;
int cnt=0;
char date_an_luna_zi[30];
void validare_date_calendar(int an,int luna,int zi,int *ok)
{
	/*valideaza date;anul introdus de utilizator trebuie sa fie cuprins intre 2000 si 2023;
	ziua intre 1 si 31; luna intre 1 si 12;daca datele introduse nu respecta conditiile 
	variabila ok se incrementeaza cu1
	*/
	if(an<2000|| an >2023)
	{
		*ok+=1;
		
	}
	if(zi<1 || zi>31)
	{
		*ok+=1;
		
	}
	if(luna<1||luna>12)
	{
		*ok+=1;
		
	}
}
void print_validare_date_calendar(int an,int luna,int zi)
{
	/*
	printeaza un mesaj in caz ca datele sunt invalide
	*/
	int p=0;//am folosit o alta variabila decat ok ca sa nu afecteze programul
        validare_date_calendar(an,luna,zi,&p);
	if(p!=0)
	   printf("Date calendaristice invalide\n");
	
}
void test_validare_date_calendar() {
    int ok = 0;

    // Test valid 
    validare_date_calendar(2022, 11, 6, &ok);
    assert(ok == 0);

    // Test invalid (an)
    validare_date_calendar(1999, 11, 6, &ok);
    assert(ok == 1);

    // Test invalid (luna)
    validare_date_calendar(2022, 13, 6, &ok);
    assert(ok == 2);

    // Test invalid (zi)
    validare_date_calendar(2022, 11, 35, &ok);
    assert(ok == 3);
    printf("test_valideaza_date_calendar passed\n");

}

void valideaza_date_char(char tip[],int *ok)
{
	//valideaza tipul ca sa poata sa-l introduca in vector;
	//daca nu este de tipul precizat, respectiv "Income" sau "Expense" variabila ok
	//se incrementeaza cu 1
	if (strcmp(tip,"Income")!=0 && strcmp(tip,"Expense")!=0)
	{
		*ok+=1;
		return;
	}
}
void printeaza_validare_date_char(char tip[])
{
	//printeaza un mesaj pentru utilizator ca sa stie ca a introdus gresit
	int p=0;
	valideaza_date_char(tip,&p);
	if(p!=0)
	   printf("Caractere pentru 'tip' neacceptate\n");
}
void test_valideaza_date_char() {
    int ok = 0;

    // Test valid 
    valideaza_date_char("Income", &ok);
    assert(ok == 0);

    //Test valid
    valideaza_date_char("Expense", &ok);
    assert(ok == 0);
    
    // Test invalid 
    valideaza_date_char("income", &ok);
    assert(ok == 1);

     // Test invalid 
    valideaza_date_char("expense", &ok);
    assert(ok == 2);
    
    // Test invalid 
    valideaza_date_char("ajk", &ok);
    assert(ok == 3);
    printf("test_valideaza_date_char passed\n");
   
}
void valideaza_suma(float suma,int *ok)
{
	//valideaza suma sa fie mai mare decat 0, in caz contrar incrementeaza variabila ok
	if(suma<=0)
	{
		*ok+=1;
		
	}
}
void printeaza_valideaza_suma(float suma)
{
	//printeaza un mesaj pentru utilizator in cazul in care variabila suma nu este corespunzatoare
	int p=0;
	valideaza_suma(suma,&p);
	if(p!=0)
		printf("Suma invalida\n");
}
void test_valideaza_suma() {
    int ok = 0;

    // Test valid 
    valideaza_suma(100.50, &ok);
    assert(ok == 0);

    // Test invalid
    valideaza_suma(-50.20, &ok);
    assert(ok == 1);
    printf("test_valideaza_suma passed\n");
  
}
int sir_vid(char s[])
{
	//verifica daca un sir este vid si returneaza 0 sau 1 in caz contrar
	if(s[0]=='\0')
		return 0;
	else 
		return 1;
}
void test_sir_vid()
{
	char copy[25];
	strcpy(copy,"dhk");
	assert(sir_vid(copy)==1);
	strcpy(copy,"");
	assert(sir_vid(copy)==0);
	strcpy(copy,"11/11/2023");
	assert(sir_vid(copy)==1);
	printf("test_sir_vid passed\n");
}
void tranzactie()
{
	//folosim biblioteca time.h
	//folosim structura definita in time.h stuct tm care retine componente ale timpului
	//precum an,luna,an,zi,minute,secunde,etc..
	//mktime converteste o structura tm intr-o reprezentare time_h
        date_an_luna_zi[0]='\0';
        int ok=0;
	int an,luna,zi;
	struct tm calendar={0};
	printf("Introduceti anul:");
	scanf("%d",&an);
	calendar.tm_year=an-1900;
	
	printf("Introduceti luna:");
	scanf("%d",&luna);
	calendar.tm_mon=luna-1;
	
	printf("Introduceti ziua:");
	scanf("%d",&zi);
	calendar.tm_mday=zi;
	validare_date_calendar(an,luna,zi,&ok);//validam datele prin incrementarea lui ok
	print_validare_date_calendar(an,luna,zi);//afisam mesaj daca datele nu sunt valide
	time_t timp=mktime(&calendar);
	//daca ok-ul este dif de 0 nu introducem datele in vector
	//struct tm calendar returneaza timp=-1 daca conversia nu a fost posibila
	if(timp==-1 ||ok!=0)
		{
		printf("Formatul nu este acceptat\n");
		}
	else{ 
		//convertim la string si adaugam data in variabila globala date_an_zi
		strftime(date_an_luna_zi,sizeof(date_an_luna_zi),"%x",&calendar);
		printf("%s\n", date_an_luna_zi);
		}
}
void adaugare(char data[],char descriere[],float suma,char tip[])
{     
    //functie care adauga in lista de tranzactii globala datele care au fost validate anterior
    strcpy(tranz[cnt].data,data);
    strcpy(tranz[cnt].descriere,descriere);
    tranz[cnt].suma=suma;
    strcpy(tranz[cnt].tip,tip);
    cnt++;
}
int comparare(float a, float b, float epsilon) {
   //compara 2 float-uri cu o marja de eroare 
    return fabs(a - b) < epsilon;
}
void test_adaugare()
{
    cnt=0;
    //test1
    adaugare("01/12/21","facturi",251.12,"Expense");
    assert(strcmp(tranz[0].data,"01/12/21")==0);
    assert(strcmp(tranz[0].descriere,"facturi")==0);
    assert(comparare(tranz[0].suma,251.12,0.1));
    assert(strcmp(tranz[0].tip,"Expense")==0);
    
    //test2
    adaugare("01/10/23","salariu",2000.5,"Income");
    assert(strcmp(tranz[1].data,"01/10/23")==0);
    assert(strcmp(tranz[1].descriere,"salariu")==0);
    assert(comparare(tranz[1].suma,2000.5,0.1));
    assert(strcmp(tranz[1].tip,"Income")==0);
    printf("test_adaugare passed\n");
 
}

void adauga_tranzactii()
{
	///t nou;
	int ok=0;
	if(cnt>=199){
		printf("Ati atins limita maxima de tranzactii\n");
		return;}
	printf("Introduceti data:\n");
	tranzactie();
	//verificam daca datele furnizate de utilizator pentru data calendaristica au fost    corect introduse I(daca au fost corecte inseamna ca aceastea se afla in vectorul sir_vid
	if(sir_vid(date_an_luna_zi)==1){
	strcpy(nou.data,date_an_luna_zi);
	}
	else 
	  return;
	printf("Introduceti descrierea:\n");
    	scanf(" %[^\n]", nou.descriere);
    	printf("Introduceti suma:\n");
    	scanf("%f", &nou.suma);
    	valideaza_suma(nou.suma,&ok);//valideaza suma si incrementeaza variabila ok 
    	printeaza_valideaza_suma(nou.suma);//afiseaza mesaj daca datele sunt incorecte
    	printf("Introduceti tipul(Income/Expense):\n");
    	scanf("%s", nou.tip);
	valideaza_date_char(nou.tip,&ok);//valideaza datele si incrementeaza ok
	printeaza_validare_date_char(nou.tip);//afiseaza mesaj daca datele sunt incorecte
	if(ok==0){
    	adaugare(nou.data,nou.descriere,nou.suma,nou.tip);//daca toate datele sunt corecte adauga tranzactia in lista
    	printf("Tranzactie introdusa cu succes.\n");
    	}
    	else 
    	printf("Tranzactia nu a putut fi introdusa.Va rog sa reincercati\n");
    	//se afiseaza mesaj daca s-a putut introduce tranzactia 
}
void afiseaza_tranzactii() {
    //afiseaza lista de tranzactii anterioare
    printf("---Toate tranzactiile ----\n");
    for (int i = 0; i < cnt; i++) {
        printf("Data: %s, Descrierea: %s, Suma: %.2f, Tip: %s\n",
               tranz[i].data, tranz[i].descriere, tranz[i].suma, tranz[i].tip);
    }
}
float calculeaza_balanta()
{
	//calculeaza balanta si returneaza un float
	//balanta creste daca tranzactia este de tipul "Income"
	//balanta scade daca tranzactia este de tipul "Expense"
	float balanta=0;
	for(int i=0;i<cnt;i++)
		if(strcmp(tranz[i].tip,"Income")==0)
			balanta+=tranz[i].suma;
		else if(strcmp(tranz[i].tip,"Expense")==0)
			balanta-=tranz[i].suma;
	return balanta;
}
void test_calculeaza_balanta()
{
	cnt=0;
	adaugare("01/01/01","nr1",124.0,"Income");
	adaugare("01/01/01","nr2",125.0,"Expense");
	adaugare("01/01/01","nr3",1000.0,"Income");
	float balanta=calculeaza_balanta();
	assert(comparare(balanta,999.0,0.1));
	printf("test_calculeaza_balanta passed\n");
}
void clear()
{
	//functie care sterge continutul dintr-o fila
    char const *numefila="fila_tranzactii.txt";
	FILE*file=fopen(numefila,"w");
	if(file==NULL)
	{
		printf("Fila nu se poate deschide %s\n",numefila);
		return;
	}
	fclose(file);
}
void exporta_date_in_fila()
{
	//deschidem o fila 
	char const *numefila="fila_tranzactii.txt";
	FILE*file=fopen(numefila,"w");
	//verifica daca fila s-a deschis cu succes
	if(file==NULL)
	{
		printf("Fila nu se poate deschide %s\n",numefila);
		return;
	}
	//introduce toate datele din vectorul curent in fila
	for(int i=0;i<cnt;i++)
		fprintf(file,"%s\t%s\t%f\t%s\n",tranz[i].data,tranz[i].descriere,
		tranz[i].suma,tranz[i].tip);
	//se inchide fila
	fclose(file);
	printf("Tranzactii salvate cu succes!\n");//se afiseaza mesaj
}

void importa_date_in_fila()
{
	//deschidem fila
	char const *numefila="fila_tranzactii.txt";
	FILE*file=fopen(numefila,"r");
	//se verifica daca fila s-a deschis cu succes
	if(file==NULL)
	{
		printf("Fila e goala %s\n",numefila);
		return;
	}
	//citeste elemente din fila si le introduce in vectorul curent
		 while(fscanf(file,"%s\t%s\t%f\t%s\n",
		 tranz[cnt].data,tranz[cnt].descriere,&tranz[cnt].suma,tranz[cnt].tip)!=EOF)
		cnt++;
		
	fclose(file);//se inchide fila
	printf("Date importate cu succes!\n");//se afiseaza mesaj
}

void test_exporta_si_importa_date_in_fila()
{
	cnt=0;
	//se creeaza o lista 
	adaugare("01/12/21","facturi",251.12,"Expense");
	adaugare("01/10/23","salariu",2000.5,"Income");
	exporta_date_in_fila();//se exporta datele in fila
	cnt=0;//se sterg elementele din lista curenta
	
	importa_date_in_fila();//se importa datele din fila
	//se verifica daca datele au fost introduse cu succes din fila in vectorul global
    	assert(strcmp(tranz[0].data,"01/12/21")==0);
    	assert(strcmp(tranz[0].descriere,"facturi")==0);
    	assert(comparare(tranz[0].suma,251.12,0.1));
    	assert(strcmp(tranz[0].tip,"Expense")==0);
    	assert(strcmp(tranz[1].data,"01/10/23")==0);
    	assert(strcmp(tranz[1].descriere,"salariu")==0);
    	assert(comparare(tranz[1].suma,2000.5,0.1));
    	assert(strcmp(tranz[1].tip,"Income")==0);
    	clear();//stergem continutul din fila text
	printf("test_exporta_si_importa_date_in_fila passed\n");
}
void raport_financiar()
{
	//functie care face un raport_financiar
	//veniturile se incrementeaza daca tipul tranzactiei="Income"
	//cheltuielile se decrementeaza daca tipul tranzactiei="Expense"
	//se face diferente dintre cheltuieli si venituri pentru a afla daca
	//utilizatorul are in final pierderi sau profit
	//se afiseaza un mesaj pentru fiecare variabila
	float venituri=0;
	float cheltuieli=0;
	float profit=0;
	float pierderi=0;
	for(int i=0;i<cnt;i++)
		if(strcmp(tranz[i].tip,"Income")==0)
			venituri+=tranz[i].suma;
		else if(strcmp(tranz[i].tip,"Expense")==0)
			cheltuieli+=tranz[i].suma;
	profit=venituri-cheltuieli;
	pierderi=cheltuieli-venituri;
	printf("Veniturile dumneavoastra sunt: 	%.2f\n",venituri);
	printf("Cheltuielile dumneavoastra sunt:  %.2f\n",cheltuieli);
	if(profit>0)
		printf("Aveti profit de: %.2f",profit);
	else 
		if(pierderi>0)
			printf("Aveti pierderi de:  %.2f\n",pierderi);
		else 
			printf("Nu aveti pierderi si nici profit\n");
}
void toate_testele()
{
	//functie care contine toate testele programului
	//daca acestea se executa corect se afiseaza un mesaj in final
        test_validare_date_calendar();
	test_valideaza_date_char();
	test_valideaza_suma();
	test_sir_vid();
	test_adaugare();
	test_exporta_si_importa_date_in_fila();
	test_calculeaza_balanta();
	printf("\n***toate testele au trecut cu succes!***\n\n\n");
}

int citire_tasta()
{
	//functia citeste pana cand utilizatorul returneaza un int!=0
	int tasta=0;
	char sir[5];
	while(tasta==0)//putem pune aceasta conditie deoarece nu avem tasta 0 in meniu
	{
		printf("Introduceti o tasta\n");
		if(fgets(sir,sizeof(sir),stdin)!=NULL)//verifica daca inputul depaseste limita declarata a variabilei sir
		{
			if(sscanf(sir,"%d",&tasta)==1)//se verifica daca se poate converti sirul in int
				break;
			else 
				printf("Tasta invalida\n");
		}
		else 
		   printf("Tasta invalida,va rugam introduceti o tasta valida\n");
	}
	return tasta;
}
int main()
{
	toate_testele();//se afiseaza mesaj la inceputul programukui daca testele s-au executat corect,daca nu sunt erori de testare
	cnt=0;
	int op;
	//se afiseaza meniul pana cand utilizatorul apasa tasta 7
	do{
	printf("\n----Date de Management Fianciar----- \n");
	printf("1.     Adauga o tranzactie             \n");
	printf("2.     Afiseaza toate tranzactiile     \n");
	printf("3.     Afiseaza raportul financiar     \n");
	printf("4.     Afiseaza balanta                \n");
	printf("5.     Salveaza tranzatiile intr-o fila\n");
	printf("6.     Importa date dintr-o fila       \n");
	printf("7.     Iesire program                  \n");
	printf("\n");
	op=citire_tasta();
	switch(op){
		case 1:
			adauga_tranzactii();
			break;
		case 2:
			afiseaza_tranzactii();
			break;
		case 3:
			raport_financiar();
			break;
		case 4:
			printf("Balanta este:  %.2f",calculeaza_balanta());
			break;
		case 5:
	                exporta_date_in_fila();
			break;
		case 6:
			importa_date_in_fila();
			break;
		case 7:
			break;
		default:
			printf("Tasta invalida. Va rog introduceti o tasta valida\n");
	}
	}while(op!=7);
	return 0;
}
