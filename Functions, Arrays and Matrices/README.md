									PROBLEMA "JOCURI_SOCIETATE"
									

	In functia "main" am declarat variabilele cu 'long' intruncat se pot folosi numere din afara intervalului 'int', riscand sa se afiseze eroarea "Segmentation fault". Tot din acest motiv, pentru siguranta, am declarat variabila HP cu 'unsigned long long', pentru a dubla valoarea pe pozitive.
	Urmatorul pas a fost sa citim de la tastatura variabilele HP si N, iar apoi, N caractere si N valori. 
	Daca se citeste de la tastatura o valoare de tip 'Heal'(H), aceasta se adauga la valoarea HP-ului. In schimb, daca valoarea citita este de tip 'Shield'(S), aceasta se adauga intr-un vector de scuturi pe care il sortam descrescator cu ajutorul functiei "sort_shield". 
	Totusi, se pot citi si caractere diferite de 'S' sau 'H', pentru care trebuie afisat mesaajul de eroare "Invalid item type". Pentru acest caz am declarat o variabila 'nr_error' pe care am initializat-o cu 0, de care ne ajutam in afisarea mesajului de eroare de atatea ori cate caractere necorespunzatoare sunt citite de la tastatura. Dupa asta afisam valoarea HP-ului actualizata.
	Apoi, citim de la tastatura variabila 'M' si M damage-uri. Ne folosim de o variabila 'used_shield' initializata cu 0 in care retinem valoarea scutului folosit impotriva damage-ului respectiv pasului curent. Pentru a alege scutul corect care sa respecte toate cerintele (cel mai mare scut mai mic sau egal decat damage-ul), pe care il stergem din vector ca sa nu riscam refolosirea sa.
	In schimb, daca nu se gaseste un scut corespunzator, se alege cel mai mic scut din vectorul sortat, respectiv ultima valoare din el, pe care o stergem ca sa evitem reutilizarea lui.
	Ne folosim de variabila 'damage_received' pentru a retine damage-ul pe care l-am primit, urmand sa il scadem din valoarea HP-ului daca aceasta este mai mare decat 0 si mai mica decat valoarea HP-ului. In schimb, daca acesta este mai mare decat HP-ul, ii dam valoarea 0 HP-ului.
	La finalul functiei 'main' ne ocupam de afisare. Primul element afisat este valoarea HP-ului modificata, si valoarea scutului folosit impotriva damage-ului de la pasul curent, daca aceasta exista. Dar, daca HP-ul este 0, se afiseaza pe ecran valoarea acestuia si textul "You died.", programul oprindu-se.
	Daca mesajul "You died" nu a fost afisat, numarul de scuturi s-a terminat si valoarea HP-ului inca este diferit de 0, se afiseaza la final mesajul "Foe Vanquished!".
	
	
	
										PROBLEMA "FORME"


	Primul lucru facut in functia 'main' este citirea numarului N ce reprezinta numarul de forme care vor trebui afisate, iar apoi, cele N forme. Retinem intr-un vector de caractere, 'forma[]', pe cate o pozitie, unul din caracterele "p (patrat), d (dreptunghi), t (triunghi), c (cruce), f (fereastra)", iar pentru fiecare forma se citesc dimensiunile si masura unghiului, daca e cazul.
	Pentru fiecare caz am implementat cate o functie.
	
				*Functia 'forma_p' - pentru patrat

	In enunt ni se specifica ca dimensiunile apartin intervalului [-50, 50].Cu toate acestea, trebuie tinut cont ca dimensiunile nu pot fi numere negative sau nule. Daca aceste conditii nu sunt verificate, va fi afisat mesajul de eroare "Unsupported size to display shape."
	In cazul formei patrat, se citeste de la tastatura si masura unui unghi de rotatie a formei. In enunt avem restrictia ca masura acestui unghi trebuie sa fie divizibil cu 45 de grade. Deci, daca aceasta conditie nu este indeplinita, se afiseaza mesajul de eroare "Unsupported angle to display shape.", asta numai in cazul in care dimensiunile indeplinesc conditiile necesare.
	Daca niciun mesaj de eroare nu a fost afisat, se verifica masura unghiului pentru a ne da seama modul in care afisam forma. Daca unghiul este multiplu de 90 de grade, atunci forma va fi afisata drept un patrat. Daca este multiplu de 45 de grade dar nu si de 90, forma va fi afisata drept un romb.
	
				*Functia 'forma_d' - pentru dreptunghi

	In enunt ni se specifica ca dimensiunile apartin intervalului [-50, 50].Cu toate acestea, trebuie tinut cont ca dimensiunile nu pot fi numere negative sau nule. Daca aceste conditii nu sunt verificate, va fi afisat mesajul de eroare "Unsupported size to display shape.
	Avand in vedere ca pentru dreptunghi nu ni se da masura unui unghi, nu este nevoie sa verificam cazurile de eroare pentru acesta.
	Daca mesajul de eroare nu este afisat, putem construi dreptunghiul pe baza dimensiunilor date.
	
				*Functia 'forma_t' - pentru triunghi dreptunghic

	In enunt ni se specifica ca dimensiunile apartin intervalului [-50, 50].Cu toate acestea, trebuie tinut cont ca dimensiunile nu pot fi numere negative sau nule. Daca aceste conditii nu sunt verificate, va fi afisat mesajul de eroare "Unsupported size to display shape."
	In cazul formei triunghi, se citeste de la tastatura si masura unui unghi de rotatie a formei. In enunt avem restrictia ca masura acestui unghi trebuie sa fie divizibil cu 90 de grade. Deci, daca aceasta conditie nu este indeplinita, se afiseaza mesajul de eroare "Unsupported angle to display shape.", asta numai in cazul in care dimensiunile indeplinesc conditiile necesare.
	Daca niciun mesaj de eroare nu a fost afisat, se verifica masura unghiului pentru a ne da seama modul in care afisam forma.
	Dacă este pozitiv, există 4 cazuri ( 4 cadrane ). Am folosit următoarea formulă pentru aflarea cadranului: (int)(u / 360.0 * 100) % 100 ( rezultatul întors trebuie să fie întreg, de aceea am folosit tipul int, apoi în urma calculului , rezultatul întors poate fi 25 (unghiul este de 90,450,810 etc grade), 50 (unghiul este de 180,540,900 etc grade), 75 (unghiul este de 270,630,990 etc grade), 0 (unghiul este de 0,360,720 etc grade). 
	Dacă unghiul este negativ, această formula nu funcționează în cazul unghiurilor de 90,450,810... și 270,630,990... , inversandu-se valoarea returnată de calculul (int)(u / 360.0 * 100) % 100. După stabilirea cazului în care se încadrează unghiul, triunghiul se afișează la stdout.

				*Functia 'forma_c' - pentru cruce

	In enunt ni se specifica ca dimensiunile apartin intervalului [-50, 50].Cu toate acestea, trebuie tinut cont ca dimensiunile nu pot fi numere negative sau nule. Daca aceste conditii nu sunt verificate, va fi afisat mesajul de eroare "Unsupported size to display shape."
	In cazul formei cruce, se citeste de la tastatura si masura unui unghi de rotatie a formei. In enunt avem restrictia ca masura acestui unghi trebuie sa fie divizibil cu 45 de grade. Deci, daca aceasta conditie nu este indeplinita, se afiseaza mesajul de eroare "Unsupported angle to display shape.", asta numai in cazul in care dimensiunile indeplinesc conditiile necesare.
	Daca niciun mesaj de eroare nu a fost afisat, se verifica masura unghiului pentru a ne da seama modul in care afisam forma. Daca unghiul este multiplu de 90 de grade, atunci forma va fi afisata drept un cruce. Daca este multiplu de 45 de grade dar nu si de 90, forma va fi afisata drept un x.
	
				*Functia 'forma_f' - pentru fereastra

	In enunt ni se specifica ca dimensiunile apartin intervalului [-50, 50].Cu toate acestea, trebuie tinut cont ca dimensiunile nu pot fi numere negative sau nule. Daca aceste conditii nu sunt verificate, va fi afisat mesajul de eroare "Unsupported size to display shape.
	Avand in vedere ca pentru fereastra nu ni se da masura unui unghi, nu este nevoie sa verificam cazurile de eroare pentru acesta.
	Daca mesajul de eroare nu este afisat, putem construi ferestra pe baza dimensiunilor date.
	
	

									PROBLEMA "CIRCUITS"
									

	In functia 'main' citim de la tastatura un sir de caractere pentru a afla legea pe care trebuie sa o verificam (L), numarul de noduri (N) si numarul de fire (W).
	Daca sirul de caractere este "I", atunci trebuie sa verificam Legea I a lui Kirchhoff si ne folosim de functia 'verificare_legea_I".

				*Functia 'verificare_legea_I'

	In aceasta functie citim mai intai de la tastatura W fire, un fir continand un nod de inceput, un nod de final si intensitatea curentului electric care trece prin acel fir. Dupa ce am citit primul fir, calculam suma intensitatilor nodului de intrare si cea a nodului de iesire. 
	Pentru a verifica in acelasi timp si cazul in care intensitatea curentului este negativa si sensul in care circula curentul, nodul de inceput devenind nodul de final si invers, am folosit instructiunile "curent_out[nod_in - 1] += curent; curent_in[nod_out - 1] += curent;".
	In acelasi timp am verificat si daca circuitul este deschis sau nu, astfel: m-am folosit de un vector de frecventa de dimensiune N in care retin numarul de aparitii a fiecarui nod in firele date. Astfel, daca un nod nu apare de minim doua ori inseamna ca circuitul este deschis in nodul respectiv, programul oprindu-se dupa ce se afiseaza mesajul de eroare "Circuitul este deschis in nodul i", i fiind primul nod pentru care numarul de aparitii este mai mic de 2.
	Urmatorul caz este de a verifica daca suma intensitatilor care intra in nodul respectiv este egala cu suma celor care ies. Pentru aceasta actiune am folosit functia 'fabs' pentru numere reale pentru a calcula valoarea absoluta a diferentei dintre cele doua. Avand in vedere ca lucram cu numere cu 9 zecimale, am considerat o marja de eroare de 1e-6 (1*10^-6 = 0.000001) intrucat doua numere egale pot ajunge sa difere printr-o singura zecimala din cauza erorilor de precizie a calculatoarelor.
	Astfel, daca aceasta diferenta este mai mare decat eroarea 1e-6 inseamna ca numerele nu pot fi considerate egale, deci se afiseaza mesajul "Legea 1 a lui Kirchhoff nu se respecta pentru egalitatea ... in nodul ...", si programul de opreste.
	In caz contrar, se afiseaza mesajul "Legea 1 a lui Kirchhoff se respecta pentru circuitul dat".
	
				*Functia 'verificate_legea_II'
				
	In aceasta functie citim mai intai datele despre fiecare segment al circuitului (noduri, curent și componente), iar pentru fiecare componentă (rezistenta R sau sursă de tensiune E) calculam tensiunea pe consumatori și surse.
	Daca se citeste o literă diferită de E și R, funcția semnalează această eroare afișând mesajul "Componenta dorită nu exista".  
	Tensiunea consumatorilor se calculează prin produsul curentului cu rezistența ( U = I * R ), iar tensiunea surselor se adaugă direct. 
	La final, programul compară suma tensiunii consumatorilor cu suma tensiunii surselor cu ajutorul funcției fabs , folosită pentru a verifica dacă două numere de tip double sunt egale, scăzându le,  având o marjă de eroare (1e-6). Dacă diferența dintre ele este suficient de mică, legea este respectată și se afișează un mesaj pozitiv, iar  în caz contrar, programul afișează faptul ca legea nu se îndeplinește, programul oprindu-se ulterior.
	
	
	
									PROBLEMA "SEGMENT_DISPLAY"
									

	In functia "main" am inceput prin a citi de la tastatura dimensiunile matricei in cadrul careia se va lucra, N linii si M coloane, si L care reprezinta lungimea unui segment de leduri. Latimea am calculat-o conform enuntului, prin calcularea partii intregi a impartirii lui L la 3, valoare pe care am retinut-o in variabila W.
	Pentru a usura procesul, am initializat matricea cu caracterul spatiu (' ') pe fiecare pozitie.
	In instructiunea 'while(1)' citim comenzile de la tastatura cat timp ele sunt diferite de 'Q', intrucat aceasta reprezinta ultimul caracter citit. Aceste comenzi pot fi "F, P, W, A, S, D".
	
*Comanda F
				
	Daca se citeste de la tastatura caracterul 'F', urmata de o cifra, inseamna ca ni se cere sa construim una dintre cifrele 0, 1, 2, 3, 4, 5, 6, 7, 8, 9. De aceea, daca de la tastatura este citit un numar negativ sau de mai mult de o cifra, se afiseaza mesajul "The input given is not a digit". In cazul in care comanda 'F' este citita de mai multe ori de la tastatura reinitializam matricea cu spatii, deoarece urmatoarele comenzi trebuiesc aplicate pe noua cifra fata de cea initiala.
	Ca sa construim functia ne folosim de functiile 'seg_lines' care construieste liniile cifrelor, si 'seg_columns', care construieste coloanele cifrelor.
	
	*Functia 'seg_lines'
		In aceasta functie construim liniile cifrelor citite de la tastatura.
		Am inceput cu linia din mijloc. Avand in vedere ca toate cifrele, exceptand 0, 1 si , au linia din mijloc existenta, am adaugat caracterul '^' pe segmentul respectiv.
		Am continuat cu linia de sus. De asemenea, toate cifrele, mai putin 1 si 4, contin aceasta linie in constructia lor, am adaugat caracterul '^' pe acel segment.
		Am finalizat cu ultima linie. Toate cifrele contin acea linie, mai putin 1, 4 si 7, motiv pentru care am adaugat '^' pe segmentul respectiv.
		
	*Functia 'seg_column'
		In cazul acestei functii, ideea de baza este aceeasi ca si in cazul functiei 'seg_lines', doar ca am considerat coloane segmentele verticale din stanga sus, dreapta sus, stanga jos si dreapta jos, adaugand caracterul '^' in constructia cifrelor care contin coloana respectiva in constructia lor.
		
*Comanda P

	Daca se citeste de la tastatura caracterul 'P' inseamna ca ni se cere sa afisam matricea cu modificarile realizate pana in momentul primirii comenzii.
	In acest caz ne folosim de functia 'P_command' in cadrul careia facem afisarea matricei.
	
*Comanda W

	Daca se citeste de la tastatura caracterul 'W', urmat de un numar 'digit', inseamna ca ni se cere sa mutam primele digit linii pe ultimele digit linii ale matricii.
	Pentru a face acest lucru folosim functia 'W_command' in care se fac aceste mutari cu ajutorul unei matrici auxiliare in care retinem primele digit linii, pentru a face mutarea in sus a celorlalte linii fara a pierde cele digit linii.
	
*Comanda S

	Daca se citeste de la tastatura caracterul 'S', urmat de un numar 'digit', inseamna ca ni se cere sa mutam ultimele digit linii pe primele digit linii ale matricii.
	Pentru a face acest lucru folosim functia 'S_command' in care se fac aceste mutari cu ajutorul unei matrici auxiliare in care retinem ultimele digit linii, pentru a face mutarea in jos a celorlalte linii fara a pierde cele digit linii.
	
*Comanda D

	Daca se citeste de la tastatura caracterul 'D', urmat de un numar 'digit', inseamna ca ni se cere sa mutam ultimele digit coloane pe primele digit coloane ale matricii.
	Pentru a face acest lucru folosim functia 'D_command' in care se fac aceste mutari cu ajutorul unei matrici auxiliare in care retinem ultimele digit coloane, pentru a face mutarea in dreapta a celorlalte coloane fara a pierde cele digit coloane.
	
*Comanda A

	Daca se citeste de la tastatura caracterul 'A', urmat de un numar 'digit', inseamna ca ni se cere sa mutam primele digit coloane pe ultimele digit coloane ale matricii.
	Pentru a face acest lucru folosim functia 'A_command' in care se fac aceste mutari cu ajutorul unei matrici auxiliare in care retinem primele digit coloane, pentru a face mutarea in stanga a celorlalte coloane fara a pierde cele digit coloane.
	
	De asemenea, exista cazul in care se poate citi de la tastatura un caracter diferit de "F, P, W, A, S, D, Q", caz in care se afiseaza mesajul "Invalid command type".
	


