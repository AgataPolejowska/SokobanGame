#include <iostream>
#include <cstdlib>

using namespace std;

struct Position {
    int x;
    int y;
};

const char workerChar = 'R';
const char packageChar = 'x';
const char placeChar = 'O';
const char wallChar = '#';

const char FirstMap[100][200]
{
    "####################",
    "#     R            #",
    "#     ######## x   #",
    "#     #      #     #",
    "#     #      #     #",
    "#   O #      #     #",
    "#   O ########     #",
    "#            x     #",
    "#                  #",
    "####################",
};

const char SecondMap[100][200]
{
    "###############",
    "####   ########",
    "#### x ########",
    "#### x ###O####",
    "###### ###O####",
    "######    O####",
    "##### x #  ####",
    "#####R  #######",
    "###############"
};

const char ThirdMap[100][200]
{
    "################",
    "######     #####",
    "#####OR    #####",
    "####### x  #####",
    "#####O# x  #####",
    "##### # O  #####",
    "#####x  xxO#####",
    "#####   O  #####",
    "################"
};


enum direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};





void findPosition (char Map[100][200], Position *worker, Position *package, Position *place,
                    int *packageCounter, int *placeCounter)
{
    for (int i=0; i<100; i++)
    {
        for (int j=0; j<200; j++)
        {
            if (Map[i][j] == workerChar)
            {
                worker->x = j;
                worker->y = i;

                Map[i][j] = ' ';
            }
            else if (Map[i][j] == packageChar)
            {
                package[*packageCounter].x = j;
                package[*packageCounter].y = i;

                Map[i][j] = ' ';
                (*packageCounter)++;
            }
            else if (Map[i][j] == placeChar)
            {
                place[*placeCounter].x = j;
                place[*placeCounter].y = i;

                (*placeCounter)++;
            }
        }
    }
}



void printMap (char Map[100][200], Position *worker, Position *package, Position *place, int *packageCounter)
{
    system ("cls");

	for (int i=0; i<100; i++)
	{
		bool nextLine = false;

		for (int j=0; j<200; j++)
		{
			char field = ' ';

			if ((worker->y == i) && (worker->x == j))
			{
				cout << workerChar;
				continue;
			}

			for (int k=0; k < *packageCounter; k++)
			{
				if ((package[k].x == j) && (package[k].y == i))
				{
					field = packageChar;
					break;
				}
				else if ((place[k].x == j) && (place[k].y == i))
                {
					field = placeChar;
				}
			}

			if (field != ' ')
            {
				cout << field;
				continue;
			}

			if (Map[i][j] != '\0')
            {
				cout << Map[i][j];
				nextLine = true;
			}
		}
       if (nextLine) cout << endl;
    }
}



bool checkWall (char Map[100][200], Position *package, Position *new_worker, Position *new_package,
                        int packageCounter, int packageNumber)
{
    if (Map[new_worker->y][new_worker->x] == wallChar) return true;

    if (packageNumber>=0)
    {
        if (Map[new_package->y][new_package->x] == wallChar) return true;

        for (int i=0; i<packageCounter; i++)
        {
            if ((package[i].x == (new_package->x)) && (package[i].y == (new_package->y))) return true;
        }
    }
    return false;
}



void movement (char Map[100][200], Position *worker, Position *package, Position *place,
                 int *packageCounter, int *movesCounter, bool *gameEnd)
{
    char key = cin.get();
    direction dir = NONE;

     switch (key) {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            exit(0);
        default:
            if ((int)key != 10)
            {
                cout << " Invalid input: " << key << endl;
                system ("pause");
            }
            break;
     }

    Position new_worker;
    Position new_package;

    new_worker.x = worker->x;
    new_worker.y = worker->y;
    new_package.x = package->x;
    new_package.y = package->y;

    if (dir == UP) new_worker.y--;
    else if (dir == DOWN) new_worker.y++;
    else if (dir == LEFT) new_worker.x--;
    else if (dir == RIGHT) new_worker.x++;

    int current_package = -1;

    for (int i=0; i<*packageCounter; i++)
    {
        if ((package[i].x == new_worker.x) && (package[i].y == new_worker.y))
        {
            new_package.x = package[i].x;
            new_package.y = package[i].y;
            current_package = i;
            break;
        }
    }

    if (current_package >= 0)
    {
        if (dir == UP) new_package.y--;
        else if (dir == DOWN) new_package.y++;
        else if (dir == LEFT) new_package.x--;
        else if (dir == RIGHT) new_package.x++;
    }

    if (!checkWall(Map, package, &new_worker, &new_package, *packageCounter, current_package))
    {
        worker->x = new_worker.x;
        worker->y = new_worker.y;

        if (current_package >= 0)
        {
            package[current_package].x = new_package.x;
            package[current_package].y = new_package.y;
        }
        (*movesCounter)++;
    }

    int onPlace[10] = {0};
    for (int k=0; k<*packageCounter; k++)
    {
        for (int m=0; m<*packageCounter; m++)
        {
            if ((package[k].x == place[m].x) && (package[k].y == place[m].y))
            {
                 onPlace[k] = 1;
            }
        }
    }

    *gameEnd = true;
    for (int k = 0; k < *packageCounter; k++)
    {
        if (!onPlace[k])
        {
            *gameEnd = false;
            break;
        }
    }
}



void copyMap(const char fromMap[100][200], char toMap[100][200])
{
    for (int i=0; i<100; i++)
    {
        for (int j=0; j<200; j++)
        {
            toMap[i][j] = fromMap[i][j];
        }
    }
}



int main()
{
    char name[40];
    char choice;
    bool gameStart = false;
    bool gameEnd = false;
    int movesCounter = 0;

    Position worker;
    worker.x = 0;
    worker.y = 0;

    Position package[10];
    int packageCounter = 0;

    Position place[10];
    int placeCounter = 0;

    char current_Map[100][200];

    cout << " \n \t\t\t WELCOME TO SOKOBAN GAME! " << endl;
    cout << endl;
    cout << " \n\t Enter your name: "; cin >> name;
    cout << "\n\t Hello " << name << "!" << endl;

    while (!gameStart)
    {
        cout << endl;
        cout << " \t Choose your map: \n" << endl;
        cout << " \t\t1. First Map " << endl;
        cout << " \t\t2. Second Map " << endl;
        cout << " \t\t3. Third Map " << endl;


        cin >> choice;

        switch(choice)
        {
            case '1':
                copyMap(FirstMap, current_Map);
                gameStart = true;
                break;
            case '2':
                copyMap(SecondMap, current_Map);
                gameStart = true;
                break;
            case '3':
                copyMap(ThirdMap, current_Map);
                gameStart = true;
                break;
            case 'q':
                exit(0);
            default:
                system ("cls");
                cout << " Invalid option. Choose once again.  " << endl;
        }
    }


    findPosition(current_Map, &worker, package, place, &packageCounter, &placeCounter);

    while (!gameEnd)
    {
        movement(current_Map, &worker, package, place, &packageCounter, &movesCounter, &gameEnd);
        printMap(current_Map, &worker, package, place, &packageCounter);
    }

    cout << endl;

    if (gameEnd == true)
    {
        system ("cls");
        cout << "\n\n \t\t\t You have won, " << name << "! Congratulations! \n" << endl;
        cout << " \t\t\t Number of moves:  "  << movesCounter << endl;
        cout << endl;
    }

    system ("pause");
    return 0;
}
