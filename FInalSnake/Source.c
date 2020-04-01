#include<stdlib.h>
#include <glut.h>
#include <stdio.h>
int win = 0;
int DIR1 = 12, DIR2 = 12;
int TIME =200;
int SIZE = 20;
int box[20][20] = { 0 };
int player1Cl=6,player2Cl=8;
struct Snake* Head1 = NULL, * Head2 = NULL, * apple = NULL;
struct Snake {
	int X;
	int Y;
	int Value;
	struct Snake* next;
	struct Snake* Prev;
	struct Snake* ate;
};
void Start();


struct Snake* buildSnake(int x, int y, int val) {
	struct  Snake* Item = (struct  Snake*)malloc(sizeof(struct Snake));
	Item->X = x;
	Item->Y = y;
	Item->Value = val;
	Item->next = Item->Prev = Item->ate = NULL;
	return Item;
}
struct Snake* insetBody(struct Snake* head, int x, int y, int val) {
	struct Snake* item = buildSnake(x, y, val), * head1 = head;
	if (head == NULL)
		return item;
	while (head1->next) {
		head1 = head1->next;
	}
	item->Prev = head1;
	item->Value = head->Value - 1;
	head1->next = item;
	return head;
}
int interactSnake(struct Snake* head, struct Snake* item) {
	if (item == NULL)
		return 0;
	return (head->X == item->X && head->Y == item->Y) ? 1 : 0;
}
void updateApple() {
	int flag;
	struct Snake* temp;
	do {
		flag = 0;
		apple->X = rand() % SIZE;
		apple->Y = rand() % SIZE;
		temp = Head1;
		while (temp) {
			if (interactSnake(temp, apple)) {
				flag = 1;
				break;
			}
			temp = temp->next;
		}
		temp = Head2;
		while (temp) {
			if (interactSnake(temp, apple)) {
				flag = 1;
				break;
			}
			temp = temp->next;
		}
	} while (flag == 1);
}
void updateSnake(int x, int y, struct Snake* head) {
	int tempx, tempy, t1, t2;
	struct Snake* last = head;
	while (last->next)
		last = last->next;
	if (interactSnake(head, apple)) {
		printf("apple eaten");
		head->ate = insetBody(head->ate, apple->X, apple->Y, apple->Value);
		updateApple();
	}
	if (interactSnake(last, head->ate)) {
		printf("in the last");
		head = insetBody(head, last->X, last->Y, apple->Value);
		head->ate = head->ate->next;
	}
	if (x < 0)
		x = SIZE - 1;
	if (x >= SIZE)
		x = 0;
	if (y < 0)
		y = SIZE - 1;
	if (y >= SIZE)
		y = 0;
	
	while (head) {
		if (head->Prev == NULL) {
			t1 = head->X;
			t2 = head->Y;
			head->X = x;
			head->Y = y;
			tempx = t1;
			tempy = t2;
		}
		else
		{
			t1 = head->X;
			t2 = head->Y;
			head->X = tempx;
			head->Y = tempy;
			tempx = t1;
			tempy = t2;
		}
		head = head->next;
	}
}
void Move() {
	switch (DIR1)
	{
	case 12: {
		updateSnake(Head1->X, Head1->Y - 1, Head1);
		break;
	}
	case 6: {
		updateSnake(Head1->X, Head1->Y + 1, Head1);
		break;

	}case 3: {
		updateSnake(Head1->X + 1, Head1->Y, Head1);
		break;
	}
	case 9: {
		updateSnake(Head1->X - 1, Head1->Y, Head1);
		break;
	}
	default:
		break;
	}
	switch (DIR2)
	{
	case 12: {
		updateSnake(Head2->X, Head2->Y - 1, Head2);
		break;
	}
	case 6: {
		updateSnake(Head2->X, Head2->Y + 1, Head2);
		break;

	}case 3: {
		updateSnake(Head2->X + 1, Head2->Y, Head2);
		break;
	}
	case 9: {
		updateSnake(Head2->X - 1, Head2->Y, Head2);
		break;
	}
	default:
		break;
	}
	printf("player 1 (%d,%d)\nPlayer 2 (%d,%d)\n\n", Head1->X, Head1->Y, Head2->X, Head2->Y);
}
void fillSnakeBox(struct Snake* head) {
	int i, j;
	while (head) {
		i = head->Y;
		j = head->X;
		box[i][j] = head->Value;
		head = head->next;
	}
}
void fillBox(struct Snake* head1, struct Snake* head2) {
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			box[i][j] = 0;
	fillSnakeBox(head1);
	fillSnakeBox(head2);
	box[apple->Y][apple->X] = apple->Value;
}
int Check(struct Snake* head1, struct Snake* head2) {
	struct Snake* temp1 = head1->next, * temp2 = head2->next;
	while (temp1) {
		if (interactSnake(head1, temp1) || interactSnake(temp1, head2))
			return 1;
		temp1 = temp1->next;
	}
	while (temp2) {
		if (interactSnake(head2, temp2) || interactSnake(temp2, head1))
			return 2;
		temp2 = temp2->next;
	}
	return 0;
}



void keyborad(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w': {
		if (DIR1 != 6)
			DIR1 = 12;
		break;
	}
	case 's': {
		if (DIR1 != 12)
			DIR1 = 6;
		break;
	}
	case 'd': {
		if (DIR1 != 9)
			DIR1 = 3;
		break;
	}
	case 'a': {
		if (DIR1 != 3)
			DIR1 = 9;
		break;
	}
	case '8': {
		if (DIR2 != 6)
			DIR2 = 12;
		break;
	}
	case '5': {
		if (DIR2 != 12)
			DIR2 = 6;
		break;
	}
	case '6': {
		if (DIR2 != 9)
			DIR2 = 3;
		break;
	}
	case '4': {
		if (DIR2 != 3)
			DIR2 = 9;
		break;
	}
	case 'r': {
		if (win != 0) {
			win = 0;
			Start();
		}
		else
			win = 3;
	}
	default:
		break;
	}

}


void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SIZE * 100, SIZE * 100, 0);
	glMatrixMode(GL_MODELVIEW);
}
void kavim()
{
	int i, j;
	for (i = 0, j = 0; i <= SIZE; i++, j++)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(i * 100, 0);
		glVertex2i(i * 100, SIZE * 100);
		glVertex2i(0, j * 100);
		glVertex2i(SIZE * 100, j * 100);
		glEnd();

	}
}
void begin()
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (box[j][i] == 1)
			{
				glColor3f(0, 1, 0);

			}
			if (box[j][i] == 2)
			{
				glColor3f(1, 0, 0);

			}
			if (box[j][i] == 0)
			{
				glColor3f(1, 1, 1);

			}
			if (box[j][i] == 3)
			{
				glColor3f(0.4, 1, 0.6);

			}
			if (box[j][i] == 4)
			{
				glColor3f(0, 0, 1);

			}
			if (box[j][i] == 5)
			{
				glColor3f(0.5, 0.5, 1);

			}
			if (box[j][i] == 6)
			{
				glColor3f(1, 1, 0);

			}
			if (box[j][i] == 7)
			{
				glColor3f(0.6, 0.3, 4);

			}
			if (box[j][i] == 8)
			{
				glColor3f(0.1, 0.1, 1);

			}
			if (box[j][i] == 9)
			{
				glColor3f(0.2, 0.2, 0.2);

			}
			glRectf(i * 100, j * 100, i * 100 + 100, j * 100 + 100);
		}
	}
	kavim();
}



void Draw(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	begin();
	glFlush();
}
void Tick() {
	Move();
	fillBox(Head1, Head2);
	if (!win && !(win = Check(Head1, Head2))) {
		Draw();
		glutTimerFunc(TIME, Tick, 0);
	}
	else
	{
		Move();
		fillBox(Head1, Head2);
		if (win == 1)
			printf("player 1 win\n");
		else if (win == 2)
			printf("player 2 win\n");
		else
			printf("Tie");
	}
}
void Start() {
	int i, j;
	DIR1 = 12;
	DIR2 = 12;
	free(Head1);
	free(Head2);
	Head1 = NULL;
	Head2 = NULL;
	Head1 = insetBody(Head1, 5, 5, player1Cl);
	Head1 = insetBody(Head1, 5, 6, 2);
	Head1 = insetBody(Head1, 5, 7, 2);
	Head1 = insetBody(Head1, 5, 8, 2);

	Head2 = insetBody(Head2, 8, 5, player2Cl);
	Head2 = insetBody(Head2, 8, 6, 2);
	Head2 = insetBody(Head2, 8, 7, 2);
	Head2 = insetBody(Head2, 8, 8, 2);
	for (i=0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			box[i][j] = 0;
	apple = (struct Snake*)malloc(sizeof(struct Snake));
	apple->X = 4;
	apple->Y = 4;
	apple->Value = 9;
	updateApple();
	Draw();
	glutTimerFunc(TIME, Tick, 0);
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("simple");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyborad);
	srand(time(NULL));
	Start();
	glClearColor(1, 1, 1, 0);

	


	glutMainLoop();
	return 0;
}