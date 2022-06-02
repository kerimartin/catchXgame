#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAPSIZE 38 
#define TIMER 7

void writeto(int sor, int oszlop) 
{
	COORD c;
	c.Y = sor;
	c.X = oszlop;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void MapGenerator(char *dimchar, int size, int sor, int oszlop)
{
	for(int j = 0; j < size; j++)
	{
		dimchar[j] = ' ';
	}

	for(int generator = 0; generator < size / 14; generator++)
	{
		int number = (rand() % size) - 4;
		int counter = 0;
		counter += (rand() % 2) + 3;

		if(number % 2 == 0)
		{
			for(int i = 0; i < counter; i++)
			{
				dimchar[number + counter + i + 1] = '#';
			}
		}
		else
		{
			for(int i = 0; i < counter ; i++)
			{
				int osszeg = number + counter + (i * oszlop);
				
				if(osszeg > size)
				{
					osszeg = (size - osszeg) * (-1);
				}

				dimchar[osszeg] = '#';
			}
		}
	}

	for(int i = 0; i < oszlop; i++)
	{
		dimchar[i] = '*';
	}

	for(int k = 0; k < size; k += oszlop)
	{
		dimchar[k] = '*';
	}

	for(int l = size - oszlop; l < size; l++)
	{
		dimchar[l] = '*';
	}

	for(int e = oszlop - 1; e < size; e += oszlop)
	{
		dimchar[e] = '*';
	}
}

void MapDisplay(char *displaymap, int sor, int oszlop, int size)
{
	for(int i = 0; i < sor; i++)
	{
		for(int j = 0; j < oszlop; j++)
		{
			if(displaymap[j + (i * oszlop)] == 'O')
			{
				printf("\033[1;32m");
			}
			else if( (displaymap[j + (i * oszlop)] == '*') || (displaymap[j + (i * oszlop)] == 'X') )
			{
				printf("\033[0;31m");
			}

			printf("%c", displaymap[j + (i * oszlop)]);
			printf("\033[0m");
		}
		puts("");
	}
}

void CatchCheck(int playercordx, int playercordy, int enemycordx, int enemycordy)
{
	if( (playercordx == enemycordx) && (playercordy == enemycordy) )
	{
		int check;

		system("cls");
		puts("Congratulations, you won!");
		Beep(200, 100);
		Sleep(50);
		Beep(200, 100);
		puts("Press ESC to exit.");

		while(1)
		{
			check = getch();

			if(check == 27)
			{
				exit(0);
			}
		}
	}
}

void Move_up(int control, int sor, int oszlop, int *coordx, int *coordy, char GeneratedMap[sor][oszlop], char symbol, int *diditmove)
{
	*diditmove = 0;
	if( (control == 119) || (control == 87) || (control == 16) )
	{
		//megnezi hogy mozoghat-e, nincs-e a kozelben fal.
		if( (GeneratedMap[*coordx - 1][*coordy] != '#') && (GeneratedMap[*coordx - 1][*coordy] != '*') )
		{
			//szinallitas a printfnek
			if(symbol == 'O')
			{
				printf("\033[1;32m");
			}
			else
			{
				printf("\033[0;31m");
			}
			
			//pozicio atallitasa
			*coordx -= 1;
			//ezzel a fuggvennyel irja meghatarozott helyre az O betut, hogy ne kelljen system cls mindig.
			writeto(*coordx, *coordy);
			//ezzel beirja a megfelelo helyre ha stimmelnek a feltetelek.
			GeneratedMap[*coordx][*coordy] = symbol;
			//ezzel modositja a karakter kiirasi helyet is
			printf("%c", GeneratedMap[*coordx][*coordy]);
			//printf szin alaphelyzetbe allitasa.
			printf("\033[0m");

			//itt torli az elozo poziciot, amiben volt a player, hogy ne sokszorozodjon.
			writeto(*coordx + 1, *coordy);
			GeneratedMap[*coordx + 1][*coordy] = ' ';
			printf("%c", GeneratedMap[*coordx + 1][*coordy]);
			*diditmove = 1;
		}
	}
}

void Move_down(int control, int sor, int oszlop, int *coordx, int *coordy, char GeneratedMap[sor][oszlop], char symbol, int *diditmove)
{
	*diditmove = 0;
	if( (control == 115) || (control == 83) || (control == 16) )
	{
		//megnezi hogy mozoghat-e, nincs-e a kozelben fal.
		if( (GeneratedMap[*coordx + 1][*coordy] != '#') && (GeneratedMap[*coordx + 1][*coordy] != '*') )
		{
			//szinallitas a printfnek
			if(symbol == 'O')
			{
				printf("\033[1;32m");
			}
			else
			{
				printf("\033[0;31m");
			}

			//pozicio atallitasa
			*coordx += 1;
			//ezzel a fuggvennyel irja meghatarozott helyre az O betut, hogy ne kelljen system cls mindig.
			writeto(*coordx, *coordy);
			//ezzel beirja a megfelelo helyre ha stimmelnek a feltetelek.
			GeneratedMap[*coordx][*coordy] = symbol;
			//ezzel modositja a karakter kiirasi helyet is
			printf("%c", GeneratedMap[*coordx][*coordy]);
			//printf szin alaphelyzetbe allitasa.
			printf("\033[0m");

			//itt torli az elozo poziciot, amiben volt a player, hogy ne sokszorozodjon.
			writeto(*coordx - 1, *coordy);
			GeneratedMap[*coordx - 1][*coordy] = ' ';
			printf("%c", GeneratedMap[*coordx - 1][*coordy]);
			*diditmove = 1;
		}
	}
}

void Move_left(int control, int sor, int oszlop, int *coordx, int *coordy, char GeneratedMap[sor][oszlop], char symbol, int *diditmove)
{
	*diditmove = 0;
	if( (control == 97) || (control == 65) || (control == 16) )
	{
		//megnezi hogy mozoghat-e, nincs-e a kozelben fal.
		if( (GeneratedMap[*coordx][*coordy - 1] != '#') && (GeneratedMap[*coordx][*coordy - 1] != '*') )
		{
			//szinallitas a printfnek
			if(symbol == 'O')
			{
				printf("\033[1;32m");
			}
			else
			{
				printf("\033[0;31m");
			}

			//pozicio atallitasa
			*coordy -= 1;
			//ezzel a fuggvennyel irja meghatarozott helyre az O betut, hogy ne kelljen system cls mindig.
			writeto(*coordx, *coordy);
			//ezzel beirja a megfelelo helyre ha stimmelnek a feltetelek.
			GeneratedMap[*coordx][*coordy] = symbol;
			//ezzel modositja a karakter kiirasi helyet is
			printf("%c", GeneratedMap[*coordx][*coordy]);
			//printf szin alaphelyzetbe allitasa.
			printf("\033[0m");

			//itt torli az elozo poziciot, amiben volt a player, hogy ne sokszorozodjon.
			writeto(*coordx, *coordy + 1);
			GeneratedMap[*coordx][*coordy + 1] = ' ';
			printf("%c", GeneratedMap[*coordx][*coordy + 1]);
			*diditmove = 1;
		}
	}
}

void Move_right(int control, int sor, int oszlop, int *coordx, int *coordy, char GeneratedMap[sor][oszlop], char symbol, int *diditmove)
{
	*diditmove = 0;
	if( (control == 100) || (control == 68) || (control == 16) )
	{
		//megnezi hogy mozoghat-e, nincs-e a kozelben fal.
		if( (GeneratedMap[*coordx][*coordy + 1] != '#') && (GeneratedMap[*coordx][*coordy + 1] != '*') )
		{
			//szinallitas a printfnek
			if(symbol == 'O')
			{
				printf("\033[1;32m");
			}
			else
			{
				printf("\033[0;31m");
			}

			//pozicio atallitasa
			*coordy += 1;
			//ezzel a fuggvennyel irja meghatarozott helyre az O betut, hogy ne kelljen system cls mindig.
			writeto(*coordx, *coordy);
			//ezzel beirja a megfelelo helyre ha stimmelnek a feltetelek.
			GeneratedMap[*coordx][*coordy] = symbol;
			//ezzel modositja a karakter kiirasi helyet is
			printf("%c", GeneratedMap[*coordx][*coordy]);
			//printf szin alaphelyzetbe allitasa.
			printf("\033[0m");

			//itt torli az elozo poziciot, amiben volt a player, hogy ne sokszorozodjon.
			writeto(*coordx, *coordy - 1);
			GeneratedMap[*coordx][*coordy - 1] = ' ';
			printf("%c", GeneratedMap[*coordx][*coordy - 1]);
			*diditmove = 1;
		}
	}
}

int Check_map(const char *map, const int sor, const int oszlop)
{
	int counter = 0;
	for(int i = 0; i < sor * oszlop; i++)
	{
		if(map[i] == 'O' || map[i] == 'X')
		{
			counter++;
		}
	}

	return counter;
}

void SpawnElements(int sor, int oszlop, int *coordx, int *coordy, char map[sor][oszlop])
{
	while(1)
	{
		*coordx = (rand() % (sor - 1) - 5) + 5;
		*coordy = (rand() % (oszlop - 1) -5) + 5;

		if( (map[*coordx][*coordy] != '#') && (map[*coordx][*coordy] != '*') )
		{
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	//ezzel a cmd ablakmeretet allitom a palya !(~) meretehez.
	system("mode 95, 40");

	srand(time(NULL));

	//itt is van kurzor eltunteto hivas, de a while ciklusban is, hogyha atmeretezed az ablakot
	//akkor ujra eltunti.
	hidecursor();

	int sor = MAPSIZE;
	int oszlop = 2.5 * MAPSIZE;
	int startgame;
	int playercordx, playercordy;
	int enemycordx, enemycordy;
	int control;
	int enemycontrol = 16;
	int didenemymove = 0;
	int didplayermove = 0;
	int enemytimer;

	char GeneratedMap[sor][oszlop];
	char player = 'O';
	char enemyup = '^';
	char enemydown = 'v';
	char enemyleft = '<';
	char enemyright = '>';

	//palyageneralo fv.hivas
	MapGenerator(&GeneratedMap[0][0], sor * oszlop, sor, oszlop);

	//ez a "fomenu".
	puts("Press ENTER to start the game!");
	puts("Rules are easy, don't get caught.");
	while(1)
	{
		startgame = getch();

		//ha elindul a jatek, keres random spawn pointokat a playernek es az ellensegnek.
		//rand fuggveny segitsegevel
		if(startgame == 13)
		{
			while(1)
			{
				SpawnElements(sor, oszlop, &playercordx, &playercordy, GeneratedMap);
				GeneratedMap[playercordx][playercordy] = 'O';

				SpawnElements(sor, oszlop, &enemycordx, &enemycordy, GeneratedMap);
				GeneratedMap[enemycordx][enemycordy] = 'X';				

				if( (Check_map(&GeneratedMap[0][0], sor, oszlop)) != 2 ) 
				{
					MapGenerator(&GeneratedMap[0][0], sor * oszlop, sor, oszlop);
				}
				else
				{
					break;
				}
			}

		break;
		}
	}

	//beep hangot ad ki
	Beep(300, 100);
	//kitisztitja az ablakot
	system("cls");
	PlaySound("data/sound.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

	//kirajzolja a palyat
	MapDisplay(&GeneratedMap[0][0], sor, oszlop, sor * oszlop);
	puts("Press ESC to exit the game!");

	while(1)
	{
		//27 az ESC ascii kodja, escnel kilep.
		if(control == 27)
		{
			system("cls");
			exit(0);
		}

		//player movement
		Sleep(50);
		control = getch();

		Move_up(control, sor, oszlop, &playercordx, &playercordy, GeneratedMap, player, &didplayermove);
		Move_down(control, sor, oszlop, &playercordx, &playercordy, GeneratedMap, player, &didplayermove);
		Move_left(control, sor, oszlop, &playercordx, &playercordy, GeneratedMap, player, &didplayermove);
		Move_right(control, sor, oszlop, &playercordx, &playercordy, GeneratedMap, player, &didplayermove);

		CatchCheck(playercordx, playercordy, enemycordx, enemycordy);

		//Enemy Movement innentol. Enemytimer kell, hogy neha megbenuljon, maskepp mindent kidzsukol.
		enemytimer = rand() % TIMER;
		while(enemytimer)
		{
			if(playercordx - enemycordx == 0)
			{

				Move_up(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyup, &didenemymove);

				if(didenemymove == 1)
				{
					break;
				}
				
				if( (didenemymove == 0) && (playercordy - enemycordy > 0) )
				{
					Move_left(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyleft, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if( (didenemymove == 0) && (playercordy - enemycordy < 0) )
				{
					Move_right(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyright, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(didenemymove == 0)
				{
					Move_down(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemydown, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}			
			}
			else if(playercordy - enemycordy == 0)
			{

				Move_right(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyright, &didenemymove);

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_left(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyleft, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(didenemymove == 0)
				{
					Move_up(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyup, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(didenemymove == 0)
				{
					Move_down(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemydown, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}
			}

			if( (playercordx - enemycordx < 0) && (playercordx - enemycordx) > (playercordy - enemycordy) && ((playercordx - enemycordx) > -8) )
			{
				Move_down(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemydown, &didenemymove);

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_right(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyright, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_left(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyleft, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}											
			}
			else if( (playercordx - enemycordx > 0) && (playercordx - enemycordx) < (playercordy - enemycordy) && ((playercordx - enemycordx) < 8) )
			{
				Move_up(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyup, &didenemymove);

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_right(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyright, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_left(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyleft, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}
			}

			if( (playercordy - enemycordy < 0) && (playercordy - enemycordy) > (playercordx - enemycordx) && ((playercordy - enemycordy) > -8))
			{
				Move_right(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyright, &didenemymove);

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_up(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyup, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_down(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemydown, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}				

			}
			else if( (playercordy - enemycordy > 0) && (playercordy - enemycordy) < (playercordx - enemycordx) && ((playercordy - enemycordy) > 8) )
			{
				Move_left(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyleft, &didenemymove);

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_down(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemydown, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}

				if(!didenemymove)
				{
					Move_up(enemycontrol, sor, oszlop, &enemycordx, &enemycordy, GeneratedMap, enemyup, &didenemymove);
				}

				if(didenemymove == 1)
				{
					break;
				}
			}

			break;
		}

		//a catchcheck azert kell, hogy kidobjon ha elkaptad a botot, s ne menjen tovabb.
		CatchCheck(playercordx, playercordy, enemycordx, enemycordy);

		//elrejti a kiss villogo jelet a cmd-bol
		hidecursor();
	}

	return 0;
}