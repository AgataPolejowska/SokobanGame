                worker->y = i;

                MAP[i][j] = ' ';
            }
            else if (MAP[i][j] == PACKAGE_CHAR)
            {
                package[*packageCounter].x = j;
                package[*packageCounter].y = i;

                MAP[i][j] = ' ';
                (*packageCounter)++;
            }
            else if (MAP[i][j] == PLACE_CHAR)
            {
                place[*placeCounter].x = j;
                place[*placeCounter].y = i;

                (*placeCounter)++;
            }
        }
    }
}



void printMap (char MAP[100][200], Position *worker, Position *package, Position *place, int *packageCounter)
{
    system ("cls");
    cout << "\n\n\n";
	for (int i = 0; i < 100; i++)
	{
		bool nextLine = false;
        cout << "\t\t\t";
		for (int j = 0; j < 200; j++)
		{
			char field = ' ';

			if ((worker->y == i) && (worker->x == j))
			{
				cout << WORKER_CHAR;
				continue;
			}

			for (int k = 0; k < *packageCounter; k++)
			{
				if ((package[k].x == j) && (package[k].y == i))
				{
					field = PACKAGE_CHAR;
					break;
				}