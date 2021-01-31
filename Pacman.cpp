/*
	author: Mohaiminul Islam
	last modified: December 19, 2020
*/


# include "iGraphics.h"
# include "gl.h"


void movePaco();
int isForbidden(double x, double y);
void generateFoods();
void newGame();
void drawGrid();

int height = 720, width = 640;
int i, j, k;

//pages
int menu = 0, gameOn = 0, win = 0, lose = 0, start = 1, help = 0, highScore = 0;

int music = 1;
char pacoPic[50] = "pacoRt2.bmp";
int c = 0, f = 0;
//c is index of paco photo
//f is number of foods

int score = 0;
int eatenFood = 0;
int lives = 3;
int playerNameLength = 0;
int pacoPause = 0;
int pacoBonus = 0, bonus = 0;


typedef struct _pacman {
    int x;
    int y;
    int toRight;
    int toLeft;
    int toUp;
    int toDown;

} pacman;

typedef struct _ghost {
    int x;
    int y;
    int toRight;
    int toLeft;
    int toUp;
    int toDown;
    int fear;
    char photo[50];
} ghost;

typedef struct _foods {
    int x;
    int y;
    int on;
} foods;

typedef struct _fearFoods {
    int x;
    int y;
    int on;
} fearFoods;

typedef struct _players {
    char name[100];
    int score;
} players;

pacman paco;
ghost red, cyan, pink, orange;
foods food[300];
fearFoods fearFood[4];
players player;
players leaderBoard[10];
FILE* save = NULL;
FILE* scoreFile = NULL;



void saveGame()
{
    /**
        paco.x
        paco.y
        paco.toRight
        paco.toLeft
        paco.toUp
        paco.toDown

        red.x
        red.y
        red.toRight
        red.toLeft
        red.toUp
        red.toDown
        red.photo

        cyan.x
        cyan.y
        cyan.toRight
        cyan.toLeft
        cyan.toUp
        cyan.toDown
        cyan.photo

        pink.x
        pink.y
        pink.toRight
        pink.toLeft
        pink.toUp
        pink.toDown
        pink.photo

        orange.x
        orange.y
        orange.toRight
        orange.toLeft
        orange.toUp
        orange.toDown
        orange.photo

        score
        lives
        eatenFoods
        pacoBonus
        bonus

        foods[256]

        fearFoods[4]
    **/
    save = fopen("gameData.txt", "w");

    fprintf(save, "%d\n", paco.x);
    fprintf(save, "%d\n", paco.y);
    fprintf(save, "%d\n", paco.toRight);
    fprintf(save, "%d\n", paco.toLeft);
    fprintf(save, "%d\n", paco.toUp);
    fprintf(save, "%d\n", paco.toDown);

    fprintf(save, "%d\n", red.x);
    fprintf(save, "%d\n", red.y);
    fprintf(save, "%d\n", red.toRight);
    fprintf(save, "%d\n", red.toLeft);
    fprintf(save, "%d\n", red.toUp);
    fprintf(save, "%d\n", red.toDown);

    fprintf(save, "%d\n", cyan.x);
    fprintf(save, "%d\n", cyan.y);
    fprintf(save, "%d\n", cyan.toRight);
    fprintf(save, "%d\n", cyan.toLeft);
    fprintf(save, "%d\n", cyan.toUp);
    fprintf(save, "%d\n", cyan.toDown);

    fprintf(save, "%d\n", pink.x);
    fprintf(save, "%d\n", pink.y);
    fprintf(save, "%d\n", pink.toRight);
    fprintf(save, "%d\n", pink.toLeft);
    fprintf(save, "%d\n", pink.toUp);
    fprintf(save, "%d\n", pink.toDown);

    fprintf(save, "%d\n", orange.x);
    fprintf(save, "%d\n", orange.y);
    fprintf(save, "%d\n", orange.toRight);
    fprintf(save, "%d\n", orange.toLeft);
    fprintf(save, "%d\n", orange.toUp);
    fprintf(save, "%d\n", orange.toDown);

    fprintf(save, "%d\n", score);
    fprintf(save, "%d\n", lives);
    fprintf(save, "%d\n", eatenFood);
    fprintf(save, "%d\n", pacoBonus);
    fprintf(save, "%d\n", bonus);

    for (i = 0; i < 256; i++)
        fprintf(save, "%d\n", food[i].on);

    for (i = 0; i < 4; i++)
        fprintf(save, "%d\n", fearFood[i].on);

    fclose(save);
}

void reloadGame()
{

    newGame();
    save = fopen("gameData.txt", "r");

    if (save == NULL) {
        newGame();
        gameOn = 1;
    }

    fscanf(save, "%d\n", &paco.x);
    fscanf(save, "%d\n", &paco.y);
    fscanf(save, "%d\n", &paco.toRight);
    fscanf(save, "%d\n", &paco.toLeft);
    fscanf(save, "%d\n", &paco.toUp);
    fscanf(save, "%d\n", &paco.toDown);

    fscanf(save, "%d\n", &red.x);
    fscanf(save, "%d\n", &red.y);
    fscanf(save, "%d\n", &red.toRight);
    fscanf(save, "%d\n", &red.toLeft);
    fscanf(save, "%d\n", &red.toUp);
    fscanf(save, "%d\n", &red.toDown);

    fscanf(save, "%d\n", &cyan.x);
    fscanf(save, "%d\n", &cyan.y);
    fscanf(save, "%d\n", &cyan.toRight);
    fscanf(save, "%d\n", &cyan.toLeft);
    fscanf(save, "%d\n", &cyan.toUp);
    fscanf(save, "%d\n", &cyan.toDown);

    fscanf(save, "%d\n", &pink.x);
    fscanf(save, "%d\n", &pink.y);
    fscanf(save, "%d\n", &pink.toRight);
    fscanf(save, "%d\n", &pink.toLeft);
    fscanf(save, "%d\n", &pink.toUp);
    fscanf(save, "%d\n", &pink.toDown);

    fscanf(save, "%d\n", &orange.x);
    fscanf(save, "%d\n", &orange.y);
    fscanf(save, "%d\n", &orange.toRight);
    fscanf(save, "%d\n", &orange.toLeft);
    fscanf(save, "%d\n", &orange.toUp);
    fscanf(save, "%d\n", &orange.toDown);

    fscanf(save, "%d\n", &score);
    fscanf(save, "%d\n", &lives);
    fscanf(save, "%d\n", &eatenFood);
    fscanf(save, "%d\n", &pacoBonus);
    fscanf(save, "%d\n", &bonus);

    for (i = 0; i < 256; i++)
        fscanf(save, "%d\n", &food[i].on);

    for (i = 0; i < 4; i++)
        fscanf(save, "%d\n", &fearFood[i].on);

    strcpy(red.photo, "redRt.bmp");
    strcpy(cyan.photo, "cyanRt.bmp");
    strcpy(pink.photo, "pinkRt.bmp");
    strcpy(orange.photo, "orangeRt.bmp");

    fclose(save);

    if (lives == 0 || eatenFood == f)
        newGame();

    pacoPause = 1;
}

void newGame()
{
    paco = {320-15, 170-15, 1, 0, 0, 0};

    red.x = 320-15, red.y = 410-15;
    red.toRight = 1, red.toLeft = 0, red.toUp = 0, red.toDown = 0, red.fear = 0;
    strcpy(red.photo, "redRt.bmp");

    cyan.x = 280-15, cyan.y = 350-15;
    cyan.toRight = 0, cyan.toLeft = 1, cyan.toUp = 0, cyan.toDown = 0, cyan.fear = 0;
    strcpy(cyan.photo, "cyanLt.bmp");

    pink.x = 320-15, pink.y = 350-15;
    pink.toRight = 0, pink.toLeft = 0, pink.toUp = 1, pink.toDown = 0, pink.fear = 0;
    strcpy(pink.photo, "pinkUp.bmp");

    orange.x = 360-15, orange.y = 350-15;
    orange.toRight = 0, orange.toLeft = 0, orange.toUp = 0, orange.toDown = 1, orange.fear = 0;
    strcpy(orange.photo, "orangeDn.bmp");

    generateFoods();
    score = 0;
    lives = 3;
    eatenFood = 0;

    pacoPause = 1;
    pacoBonus = 0;
    bonus = 0;
}

void generateFoods()
{
    f = 0;
    for (i = 50; i <= 590; i+=20) {
        for (j = 50; j <= 610; j+=20) {
            if (i>=190&&i<=450&&j>=250&&j<=450) continue;
            if (j==350&&i!=170&&i!=470) continue;
            if (i==50&&j==170) continue;
            if (i==590&&j==170) continue;
            if (i==50&&j==550) continue;
            if (i==590&&j==550) continue;


            if (!isForbidden(i, j)) {
                food[f] = {i, j, 1};
                f++;
            }
        }
    }

    fearFood[0] = {50, 170, 1};
    fearFood[1] = {590, 170, 1};
    fearFood[2] = {50, 550, 1};
    fearFood[3] = {590, 550, 1};

    f+=4;

}

void foodCheck()
{
    for (i = 0; i < f; i++) {
        if (food[i].x==paco.x+15 && food[i].y==paco.y+15&&food[i].on) {
            food[i].on = 0;
            score+=20;
            eatenFood++;
            if (music)
                PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_chomp.wav", NULL, SND_FILENAME | SND_ASYNC);
        }
    }

    for (i = 0; i < 4; i++) {
        if (fearFood[i].x==paco.x+15 && fearFood[i].y==paco.y+15&&fearFood[i].on) {
            fearFood[i].on = 0;
            score+=200;
            pacoBonus = 1;
            eatenFood++;
        }
    }

}

int isCollision()
{
    if (pacoBonus) return 0;

    if (abs(paco.x-red.x)<=10 && abs(paco.y-red.y)<=10) {
        if (music)
            PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_death.wav", NULL, SND_FILENAME | SND_ASYNC);
        return 1;
    }

    if (abs(paco.x-cyan.x)<=10 && abs(paco.y-cyan.y)<=10) {
        if (music)
            PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_death.wav", NULL, SND_FILENAME | SND_ASYNC);
        return 1;
    }

    if (abs(paco.x-orange.x)<=10 && abs(paco.y-orange.y)<=10) {
        if (music)
            PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_death.wav", NULL, SND_FILENAME | SND_ASYNC);
        return 1;
    }

    if (abs(paco.x-pink.x)<=10 && abs(paco.y-pink.y)<=10) {
        if (music)
            PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_death.wav", NULL, SND_FILENAME | SND_ASYNC);
        return 1;
    }
    return 0;
}

void revive()
{
    paco = {320-15, 170-15, 1, 0, 0, 0};

    strcpy(pacoPic, "pacoRt2.bmp");

    red.x = 320-15, red.y = 410-15;
    red.toRight = 1, red.toLeft = 0, red.toUp = 0, red.toDown = 0, red.fear = 0;
    strcpy(red.photo, "redRt.bmp");

    cyan.x = 280-15, cyan.y = 350-15;
    cyan.toRight = 1, cyan.toLeft = 0, cyan.toUp = 0, cyan.toDown = 0, cyan.fear = 0;
    strcpy(cyan.photo, "cyanLt.bmp");

    pink.x = 320-15, pink.y = 350-15;
    pink.toRight = 1, pink.toLeft = 0, pink.toUp = 0, pink.toDown = 0, pink.fear = 0;
    strcpy(pink.photo, "pinkUp.bmp");

    orange.x = 360-15, orange.y = 350-15;
    orange.toRight = 1, orange.toLeft = 0, orange.toUp = 0, orange.toDown = 0, orange.fear = 0;
    strcpy(orange.photo, "orangeDn.bmp");

    pacoPause = 1;
    pacoBonus = 0;
    bonus = 0;
}

void initializeLeaderBoard()
{
    for (i = 0; i < 10; i++) {
        strcpy(leaderBoard[i].name, "-");
        leaderBoard[i].score = 0;
    }

    scoreFile = fopen("score.txt", "r");
    char tmpName[100];

    char aaa;
    for (i = 0; i < 10 && scoreFile!=NULL && fscanf(scoreFile, "%s", tmpName)!=EOF; i++) {
        strcpy(leaderBoard[i].name, tmpName);
        fscanf(scoreFile, "%d", &leaderBoard[i].score);
    }

    fclose(scoreFile);
}

void updateLeaderBoard(char name[], int score)
{
    int toEnter;
    for (i = 0; i < 10; i++) {
        if (score >=  leaderBoard[i].score) {
            toEnter = i;
            break;
        }
    }

    for (i = 8; i >= toEnter; i--) {
        strcpy(leaderBoard[i+1].name, leaderBoard[i].name);
        leaderBoard[i+1].score = leaderBoard[i].score;
    }

    strcpy(leaderBoard[toEnter].name, name);
    leaderBoard[toEnter].score = score;

    scoreFile = fopen("score.txt", "w");

    char tmpp[100];
    for (i = 0; i < 10; i++) {
        strcpy(tmpp, leaderBoard[i].name);
        fprintf(scoreFile, "%s %d", tmpp, leaderBoard[i].score);
    }

    fclose(scoreFile);
}

void drawGrid()
{
    iSetColor(0, 0, 255);

    iFilledRectangle(70, 70, 200, 20);
    iFilledRectangle(190, 70, 20, 80);
    iFilledRectangle(310, 70, 20, 80);
    iFilledRectangle(250, 130, 140, 20);
    iFilledRectangle(370, 70, 200, 20);
    iFilledRectangle(430, 70, 20, 80);
    iFilledRectangle(30, 130, 60, 20);
    iFilledRectangle(550, 130, 60, 20);
    iFilledRectangle(70, 190, 60, 20);
    iFilledRectangle(130, 130, 20, 80);
    iFilledRectangle(190, 190, 80, 20);
    iFilledRectangle(370, 190, 80, 20);
    iFilledRectangle(490, 130, 20, 80);
    iFilledRectangle(490, 190, 80, 20);
    iFilledRectangle(310, 190, 20, 80);
    iFilledRectangle(250, 250, 140, 20);
    iFilledRectangle(190, 250, 20, 80);
    iFilledRectangle(430, 250, 20, 80);
    iFilledRectangle(250, 310, 140, 10);
    iFilledRectangle(250, 310, 10, 80);
    iFilledRectangle(250, 380, 140, 10);
    iFilledRectangle(380, 310, 10, 80);
    iFilledRectangle(190, 370, 20, 140);
    iFilledRectangle(190, 430, 80, 20);
    iFilledRectangle(310, 430, 20, 80);
    iFilledRectangle(250, 490, 140, 20);
    iFilledRectangle(370, 430, 80, 20);
    iFilledRectangle(430, 370, 20, 140);
    iFilledRectangle(70, 490, 80, 20);
    iFilledRectangle(490, 490, 80, 20);
    iFilledRectangle(70, 550, 80, 40);
    iFilledRectangle(190, 550, 80, 40);
    iFilledRectangle(310, 550, 20, 80);
    iFilledRectangle(370, 550, 80, 40);
    iFilledRectangle(490, 550, 80, 40);

    iFilledRectangle(20, 20, 600, 10);
    iFilledRectangle(20, 20, 10, 230);
    iFilledRectangle(20, 250, 130, 10);
    iFilledRectangle(140, 250, 10, 80);
    iFilledRectangle(20, 320, 130, 10);
    iFilledRectangle(20, 370, 130, 10);
    iFilledRectangle(140, 370, 10, 80);
    iFilledRectangle(20, 440, 130, 10);
    iFilledRectangle(20, 450, 10, 180);
    iFilledRectangle(20, 630, 600, 10);
    iFilledRectangle(610, 20, 10, 230);
    iFilledRectangle(490, 250, 130, 10);
    iFilledRectangle(490, 250, 10, 80);
    iFilledRectangle(490, 320, 130, 10);
    iFilledRectangle(490, 370, 130, 10);
    iFilledRectangle(490, 370, 10, 80);
    iFilledRectangle(490, 440, 130, 10);
    iFilledRectangle(610, 440, 10, 200);

    //foods
    for (i = 0; i < f; i++) {
        iSetColor(255,255,255);
        if (food[i].on)
            iFilledCircle(food[i].x, food[i].y, 3.0);
    }

    for (j = 0; j < 4; j++) {
        iSetColor(255,255,255);
        if (fearFood[j].on)
            iFilledCircle(fearFood[j].x, fearFood[j].y, 7.0);
    }

}

int isForbidden(double x, double y)
{
    if (y==50&&x>=50&&x<=590)
        return 0;
    if (x==50&&y>=50&&y<=110)
        return 0;
    if (y==110&&x>=50&&x<=170)
        return 0;
    if (x==590&&y>=50&&y<=110)
        return 0;
    if (y==110&&x>=470&&x<=590)
        return 0;
    if (x==290&&y>=50&&y<=110)
        return 0;
    if (x==350&&y>=50&&y<=110)
        return 0;
    if (y==110&&x>=230&&x<=290)
        return 0;
    if (y==110&&x>=350&&x<=410)
        return 0;
    if (x==110&&y>=110&&y<=170)
        return 0;
    if (x==530&&y>=110&&y<=170)
        return 0;
    if (x==170&&y>=110&&y<=610)
        return 0;
    if (x==470&&y>=110&&y<=610)
        return 0;
    if (x==230&&y>=110&&y<=170)
        return 0;
    if (x==410&&y>=110&&y<=170)
        return 0;
    if (y==170&&x>=50&&x<=110)
        return 0;
    if (y==170&&x>=170&&x<=470)
        return 0;
    if (y==170&&x>=530&&x<=590)
        return 0;
    if (x==50&&y>=170&&y<=230)
        return 0;
    if (x==590&&y>=170&&y<=230)
        return 0;
    if (x==290&&y>=170&&y<=230)
        return 0;
    if (x==350&&y>=170&&y<=230)
        return 0;
    if (y==230&&x>=50&&x<=290)
        return 0;
    if (y==230&&x>=350&&x<=590)
        return 0;
    if (x==230&&y>=230&&y<=410)
        return 0;
    if (x==410&&y>=230&&y<=410)
        return 0;
    if (y==290&&x>=230&&x<=410)
        return 0;
    if (y==410&&x>=230&&x<=410)
        return 0;
    if (y==350&&x>=50&&x<=230)
        return 0;
    if (y==350&&x>=410&&x<=590)
        return 0;
    if (x==290&&y>=410&&y<=470)
        return 0;
    if (x==350&&y>=410&&y<=470)
        return 0;
    if (y==470&&x>=230&&x<=290)
        return 0;
    if (y==470&&x>=350&&x<=410)
        return 0;
    if (y==470&&x>=50&&x<=170)
        return 0;
    if (y==470&&x>=470&&x<=590)
        return 0;
    if (x==50&&y>=470&&y<=610)
        return 0;
    if (x==590&&y>=470&&y<=610)
        return 0;
    if (x==230&&y>=470&&y<=530)
        return 0;
    if (x==410&&y>=470&&y<=530)
        return 0;
    if (y==530&&x>=50&&x<=590)
        return 0;
    if (y==610&&x>=50&&x<=290)
        return 0;
    if (y==610&&x>=350&&x<=590)
        return 0;
    if (x==290&&y>=530&&y<=610)
        return 0;
    if (x==350&&y>=530&&y<=610)
        return 0;


    return 1;

}

int junctionToRight(double x, double y, int forGhost = 0)
{
    if (abs(x-50)<=20&&abs(y-50)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-50)<=20&&abs(y-110)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-50)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-50)<=20&&abs(y-230)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-50)<=20&&abs(y-470)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-50)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-50)<=20&&abs(y-610)<=20) {
        if (!forGhost) paco.x = 50-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-110)<=20&&abs(y-110)<=20) {
        if (!forGhost) paco.x = 110-15, paco.y = 110-15;
        return 1;
    }

    if (abs(x-170)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 170-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-170)<=20&&abs(y-230)<=20) {
        if (!forGhost) paco.x = 170-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-170)<=20&&abs(y-350)<=20) {
        if (!forGhost) paco.x = 170-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-170)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 170-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-170)<=20&&abs(y-610)<=20) {
        if (!forGhost) paco.x = 170-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-230)<=20&&abs(y-110)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-230)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-230)<=20&&abs(y-230)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-230)<=20&&abs(y-290)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 290-15;
        return 1;
    }
    if (abs(x-230)<=20&&abs(y-410)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-230)<=20&&abs(y-470)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-230)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 230-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-290)<=20&&abs(y-50)<=20) {
        if (!forGhost) paco.x = 290-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-290)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 290-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-290)<=20&&abs(y-410)<=20) {
        if (!forGhost) paco.x = 290-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-290)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 290-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-350)<=20&&abs(y-50)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-110)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-230)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-410)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-470)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-350)<=20&&abs(y-610)<=20) {
        if (!forGhost) paco.x = 350-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-410)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 410-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-410)<=20&&abs(y-230)<=20) {
        if (!forGhost) paco.x = 410-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-410)<=20&&abs(y-350)<=20) {
        if (!forGhost) paco.x = 410-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-410)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 410-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-470)<=20&&abs(y-110)<=20) {
        if (!forGhost) paco.x = 470-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-470)<=20&&abs(y-230)<=20) {
        if (!forGhost) paco.x = 470-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-470)<=20&&abs(y-350)<=20) {
        if (!forGhost) paco.x = 470-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-470)<=20&&abs(y-470)<=20) {
        if (!forGhost) paco.x = 470-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-470)<=20&&abs(y-530)<=20) {
        if (!forGhost) paco.x = 470-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-470)<=20&&abs(y-610)<=20) {
        if (!forGhost) paco.x = 470-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-530)<=20&&abs(y-110)<=20) {
        if (!forGhost) paco.x = 530-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-530)<=20&&abs(y-170)<=20) {
        if (!forGhost) paco.x = 530-15, paco.y = 170-15;
        return 1;
    }

    return 0;
}

int junctionToLeft(double x, double y, int forGhost = 0)
{
    if (abs(x-110)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 110-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-110)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 110-15, paco.y = 170-15;
        return 1;
    }

    if (abs(x-170)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-230)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-290)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-350)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-410)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-290)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 290-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-470)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 610-15;
        return 1;
    }

    if (abs(x-530)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 530-15, paco.y = 110-15;
        return 1;
    }

    if (abs(x-590)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-230)<=15) {
        paco.x = 590-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 610-15;
        return 1;
    }

    return 0;
}

int junctionToUp(double x, double y, int forGhost = 0)
{
    if (abs(x-50)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 50-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-50)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 50-15;
        return 1;
    }

    if (abs(x-110)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 110-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-110)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 110-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-530)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 530-15, paco.y = 110-15;
        return 1;
    }

    if (abs(x-50)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 170-15;
        return 1;
    }

    if (abs(x-170)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 230-15;
        return 1;
    }

    if (abs(x-230)<=15&&abs(y-290)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 290-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-290)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 290-15;
        return 1;
    }

    if (abs(x-170)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 350-15;
        return 1;
    }

    if (abs(x-290)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 410-15;
        return 1;
    }

    if (abs(x-50)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 470-15;
        return 1;
    }

    if (abs(x-50)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 530-15;
        return 1;
    }

    return 0;
}

int junctionToDown(double x, double y, int forGhost = 0)
{
    if (abs(x-50)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 110-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-110)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 110-15;
        return 1;
    }

    if (abs(x-110)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 110-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 170-15;
        return 1;
    }
    if (abs(x-530)<=15&&abs(y-170)<=15) {
        if (!forGhost) paco.x = 530-15, paco.y = 170-15;
        return 1;
    }

    if (abs(x-50)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 230-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-230)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 230-15;
        return 1;
    }

    if (abs(x-230)<=15&&abs(y-290)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 290-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-290)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 290-15;
        return 1;
    }

    if (abs(x-170)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 350-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-350)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 350-15;
        return 1;
    }

    if (abs(x-230)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 410-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-410)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 410-15;
        return 1;
    }

    if (abs(x-170)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 470-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-470)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 470-15;
        return 1;
    }

    if (abs(x-50)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-230)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 230-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-410)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 410-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 530-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-530)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 530-15;
        return 1;
    }

    if (abs(x-50)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 50-15, paco.y = 610-15;
        return 1;
    }
    if (abs(x-170)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 170-15, paco.y = 610-15;
        return 1;
    }
    if (abs(x-290)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 290-15, paco.y = 610-15;
        return 1;
    }
    if (abs(x-350)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 350-15, paco.y = 610-15;
        return 1;
    }
    if (abs(x-470)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 470-15, paco.y = 610-15;
        return 1;
    }
    if (abs(x-590)<=15&&abs(y-610)<=15) {
        if (!forGhost) paco.x = 590-15, paco.y = 610-15;
        return 1;
    }


    return 0;
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();

    //music
    if (music) {
        iSetColor(153, 255, 204);
        iFilledRectangle(490, 670, 60, 30);
        iSetColor(0, 0, 0);
        iText(500, 680, "MUSIC");
    }
    else if (!music) {
        iSetColor(204, 204, 204);
        iRectangle(490, 670, 60, 30);
        iText(500, 680, "MUSIC");
    }

    //menu
    if (!win && !lose) {
        iSetColor(153, 153, 255);
        iFilledRectangle(100, 670, 50, 30);
        iSetColor(0, 0, 0);
        iText(110, 680, "MENU");
    }

    if (gameOn) {
        foodCheck();

        //score
        char scoreText[10];
        itoa(score, scoreText, 10);
        iSetColor(255, 255, 255);
        iText(260, 690, ("SCORE: "), GLUT_BITMAP_HELVETICA_18);
        iText(340, 690, ("%s", scoreText), GLUT_BITMAP_HELVETICA_18);


        if (!pacoBonus)
            if (isCollision()) {
            lives--;
            iDelay(2.3);
            revive();
        }

        //maze and charecters
        drawGrid();
        iShowBMP2(paco.x, paco.y, pacoPic, 0x00ff00);
        if (!pacoBonus) {
            iShowBMP2(red.x, red.y, red.photo, 0x00ff00);
            iShowBMP2(cyan.x, cyan.y, cyan.photo, 0x00ff00);
            iShowBMP2(pink.x, pink.y, pink.photo, 0x00ff00);
            iShowBMP2(orange.x, orange.y, orange.photo, 0x00ff00);
        }


        //lives
        if (lives >= 1)
            iShowBMP2(270-15, 660-15, "pacoRt2.bmp", 0x00ff00);
        if (lives >= 2)
            iShowBMP2(310-15, 660-15, "pacoRt2.bmp", 0x00ff00);
        if (lives >= 3)
            iShowBMP2(350-15, 660-15, "pacoRt2.bmp", 0x00ff00);


        //game over logic
        if (eatenFood == f) {
            gameOn = 0;
            win = 1;
        }

        if (lives == 0) {
            gameOn = 0;
            lose = 1;
        }

    }

    if (menu) {
        iSetColor(255, 255, 255);

        iShowBMP2(240, 550, "pacoRt2.bmp", 0x00ff00);
        iText(280, 555, "PACMAN", GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledRectangle(200, 530, 250, 4);


        iText(260, 459, "CONTINUE", GLUT_BITMAP_HELVETICA_18);
        iText(260, 409, "NEW GAME", GLUT_BITMAP_HELVETICA_18);
        iText(260, 359, "HIGH SCORE", GLUT_BITMAP_HELVETICA_18);
        iText(260, 309, "HELP", GLUT_BITMAP_HELVETICA_18);
        iText(260, 259, "EXIT", GLUT_BITMAP_HELVETICA_18);

        iShowBMP2(240, 150, "redRt.bmp", 0x00ff00);
        iShowBMP2(290, 150, "cyanLt.bmp", 0x00ff00);
        iShowBMP2(340, 150, "pinkUp.bmp", 0x00ff00);
        iShowBMP2(390, 150, "orangeDn.bmp", 0x00ff00);
    }

    if (start) {
        iSetColor(255, 255, 255);

        iShowBMP2(240, 550, "pacoRt2.bmp", 0x00ff00);
        iText(280, 555, "PACMAN", GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledRectangle(200, 530, 250, 4);

        iText(260, 459, "CONTINUE", GLUT_BITMAP_HELVETICA_18);
        iText(260, 409, "NEW GAME", GLUT_BITMAP_HELVETICA_18);
        iText(260, 359, "HIGH SCORE", GLUT_BITMAP_HELVETICA_18);
        iText(260, 309, "HELP", GLUT_BITMAP_HELVETICA_18);
        iText(260, 259, "EXIT", GLUT_BITMAP_HELVETICA_18);

        iShowBMP2(240, 150, "redRt.bmp", 0x00ff00);
        iShowBMP2(290, 150, "cyanLt.bmp", 0x00ff00);
        iShowBMP2(340, 150, "pinkUp.bmp", 0x00ff00);
        iShowBMP2(390, 150, "orangeDn.bmp", 0x00ff00);
    }

    if (win) {
        iSetColor(255, 255, 255);
        iText(250, 400, "YOU WON!", GLUT_BITMAP_TIMES_ROMAN_24);

        iText(250, 350, "Your Score: ", GLUT_BITMAP_HELVETICA_12);
        char scoreText[10];
        itoa(score, scoreText, 10);
        iText(340, 350, ("%s", scoreText), GLUT_BITMAP_HELVETICA_12);


        iText(250, 320, "Name: ");
        iRectangle(250, 280, 140, 30);

        iText(260, 290, player.name);
    }

    if (lose) {
        iSetColor(255, 255, 255);
        iText(250, 400, "YOU LOST!", GLUT_BITMAP_TIMES_ROMAN_24);

        iText(250, 350, "Your Score: ", GLUT_BITMAP_HELVETICA_12);
        char scoreText[10];
        itoa(score, scoreText, 10);
        iText(340, 350, ("%s", scoreText), GLUT_BITMAP_HELVETICA_12);


        iText(250, 320, "Name: ");
        iRectangle(250, 280, 140, 30);

        iText(260, 290, player.name);
    }

    if (highScore) {
        iSetColor(255, 255, 255);

        iShowBMP2(230, 580, "pacoRt2.bmp", 0x00ff00);
        iText(270, 585, "HIGH SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledRectangle(200, 560, 250, 4);

        int posY = 550;
        for (i = 0; i < 10; i++) {
            posY -= 40;

            char sl[3];
            itoa(i+1, sl, 10);
            iSetColor(255, 255, 255);
            iText(200, posY, ("%s", sl), GLUT_BITMAP_HELVETICA_18);
            iText(230, posY, ("%s", leaderBoard[i].name), GLUT_BITMAP_HELVETICA_18);

            char sc[10];
            itoa(leaderBoard[i].score, sc, 10);
            iText(400, posY, ("%s", sc), GLUT_BITMAP_HELVETICA_18);
        }
    }

    if (help) {
        iSetColor(255, 255, 255);

        iShowBMP2(260, 550, "pacoRt2.bmp", 0x00ff00);
        iText(300, 555, "HELP", GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledRectangle(200, 530, 250, 4);


        iFilledCircle(150, 416, 4);
        iText(165, 409, "USE ARROW KEYS TO CONTROL.", GLUT_BITMAP_HELVETICA_18);
        iFilledCircle(150, 366, 4);
        iText(165, 359, "AVOID THE GHOSTS.", GLUT_BITMAP_HELVETICA_18);
        iFilledCircle(150, 316, 4);
        iText(165, 309, "HAVE POWER PELLETS FOR BONUS.", GLUT_BITMAP_HELVETICA_18);

        iShowBMP2(240, 150, "redRt.bmp", 0x00ff00);
        iShowBMP2(290, 150, "cyanLt.bmp", 0x00ff00);
        iShowBMP2(340, 150, "pinkUp.bmp", 0x00ff00);
        iShowBMP2(390, 150, "orangeDn.bmp", 0x00ff00);
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);

        //menu
        if (mx >= 100 && mx <= 150 && my >= 670 && my <= 700 && !win &&!lose) {
            menu = 1;
            if (gameOn) saveGame();
            gameOn = 0;
            help = 0;
            highScore = 0;
        }

        //music
        if (mx >= 490 && mx <= 550 && my >= 670 && my <= 700) {
            if (music) music = 0;
            else music = 1;
        }



        if (menu || start) {
            //continue
            if (mx >= 250 && mx <= 250+140 && my >= 450 && my <= 450+36) {
                menu = 0;
                start = 0;
                gameOn = 1;
                reloadGame();
            }
            //newgame
            if (mx >= 250 && mx <= 250+140 && my >= 400 && my <= 400+36) {
                menu = 0;
                start = 0;
                gameOn = 1;
                newGame();
            }
            //highscore
            if (mx >= 250 && mx <= 250+140 && my >= 350 && my <= 350+36) {
                menu = 0;
                start = 0;
                highScore = 1;
            }
            //help
            if (mx >= 250 && mx <= 250+140 && my >= 300 && my <= 300+36) {
                saveGame();
                help = 1;
                menu = 0;
                start = 0;
            }
            //exit
            if (mx >= 250 && mx <= 250+140 && my >= 250 && my <= 250+36) {
                saveGame();
                exit(0);
            }
        }

        if (win || lose) {

        }

        if (help || highScore) {

        }

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    //enter name
    if (win || lose)
    {
        if(key == '\r' && playerNameLength)
        {
		    win = 0;
		    lose = 0;
		    highScore = 1;

		    char duplicateName[100];

			strcpy(duplicateName, player.name);

			if (score > leaderBoard[9].score) {
                    updateLeaderBoard(duplicateName, score);
			}


			for(i = 0; i < playerNameLength; i++) {
				player.name[i] = 0;
			}
			playerNameLength = 0;
		}
		else if ((key>='a'&&key<='z') || (key>='A'&&key<='Z'))
		{
			player.name[playerNameLength] = key;
			printf("%c", player.name[i]);
			playerNameLength++;
		}
    }

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if((key == GLUT_KEY_LEFT)&&(!isForbidden(paco.x+15-5,paco.y+15)||(junctionToLeft(paco.x+15,paco.y+15))))
    {
        paco.toRight = 0;
        paco.toLeft = 1;
        paco.toUp = 0;
        paco.toDown = 0;
    }
    if(key == GLUT_KEY_RIGHT&&(!isForbidden(paco.x+15+5,paco.y+15)||(junctionToRight(paco.x+15,paco.y+15))))
    {
        paco.toRight = 1;
        paco.toLeft = 0;
        paco.toUp = 0;
        paco.toDown = 0;
    }
    if(key == GLUT_KEY_UP&&(!isForbidden(paco.x+15,paco.y+15+5)||(junctionToUp(paco.x+15,paco.y+15))))
    {
        paco.toRight = 0;
        paco.toLeft = 0;
        paco.toUp = 1;
        paco.toDown = 0;
    }
    if(key == GLUT_KEY_DOWN&&(!isForbidden(paco.x+15,paco.y+15-5)||(junctionToDown(paco.x+15,paco.y+15))))
    {
        paco.toRight = 0;
        paco.toLeft = 0;
        paco.toUp = 0;
        paco.toDown = 1;
    }

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}

void movePaco()
{
    //paco pictures
    char pacoPicRt[4][50] = {"pacoRt2.bmp","pacoRt1.bmp","pacoRt2.bmp","paco0.bmp"};
    char pacoPicLt[4][50] = {"pacoLt2.bmp","pacoLt1.bmp","pacoLt2.bmp","paco0.bmp"};
    char pacoPicUp[4][50] = {"pacoUp2.bmp","pacoUp1.bmp","pacoUp2.bmp","paco0.bmp"};
    char pacoPicDn[4][50] = {"pacoDn2.bmp","pacoDn1.bmp","pacoDn2.bmp","paco0.bmp"};

    if (!gameOn) return;

    //beginning
    if (pacoPause) {
        if (music)
            PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_beginning.wav", NULL, SND_FILENAME | SND_ASYNC);
        iDelay(2);
        pacoPause = 0;
        iDelay(2.98);
    }

//    //dying
//    if (pacoDying) {
//        strcpy(pacoPic, pacoPicDie[dsl%4]);
//        dsl++;
//        if (dsl==) {
//            dsl = 0;
//            pacoDying = 0;
//        }
//        return;
//    }

    //re enter
    if (paco.x==590-15&&paco.y==350-15&&paco.toRight) {
        paco.x = 50-15;
    }
    if (paco.x==50-15&&paco.y==350-15&&paco.toLeft) {
        paco.x = 590-15;
    }

    //movement
    if (paco.toRight&&!isForbidden(paco.x+15+5,paco.y+15)) {
        strcpy(pacoPic, pacoPicRt[c%4]);
        c++;
        if (c==4) c = 0;
        paco.x += 5;
    }

    else if (paco.toLeft&&!isForbidden(paco.x+15-5,paco.y+15)) {
        strcpy(pacoPic, pacoPicLt[c%4]);
        c++;
        if (c==4) c = 0;
        paco.x -= 5;
    }

    else if (paco.toUp&&!isForbidden(paco.x+15,paco.y+15+5)) {
        strcpy(pacoPic, pacoPicUp[c%4]);
        c++;
        if (c==4) c = 0;
        paco.y += 5;
    }

    else if (paco.toDown&&!isForbidden(paco.x+15,paco.y+15-5)) {
        strcpy(pacoPic, pacoPicDn[c%4]);
        c++;
        if (c==4) c = 0;
        paco.y -= 5;
    }

    else {
        c = 0;
        strcpy(pacoPic, "paco0.bmp");
    }
}

void moveRed()
{
    int targetX = paco.x, targetY = paco.y;

    //scatter
    if (!red.fear) {
        targetX = 590;
        targetY = 610;
    }

    //end scatter
    if (red.x==590-15&&red.y==610-15)
        red.fear = 1;

    //scatter
    if ((red.x-pink.x)*(red.x-pink.x)+(red.y-pink.y)*(red.y-pink.y) <= 50*50)
        red.fear = 0;

    double dist = 1000000000, tmp;
    int dir = 0;

    //find min distance
    if (!isForbidden(red.x+15+5,red.y+15)&&!red.toLeft) {
        tmp = sqrt((red.x+5-targetX)*(red.x+5-targetX)+(red.y-targetY)*(red.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 1;
        }
    }

    if (!isForbidden(red.x+15-5,red.y+15)&&!red.toRight) {
        tmp = sqrt((red.x-5-targetX)*(red.x-5-targetX)+(red.y-targetY)*(red.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 2;
        }
    }

    if (!isForbidden(red.x+15,red.y+15+5)&&!red.toDown) {
        tmp = sqrt((red.x-targetX)*(red.x-targetX)+(red.y+5-targetY)*(red.y+5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 3;
        }
    }

    if (!isForbidden(red.x+15,red.y+15-5)&&!red.toUp) {
        tmp = sqrt((red.x-targetX)*(red.x-targetX)+(red.y-5-targetY)*(red.y-5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 4;
        }
    }

    //none of above
    if (dir==0) {
        if (!isForbidden(red.x+15+5, red.y+15)) {
            red.toRight = 1;
            red.toLeft = 0;
            red.toUp = 0;
            red.toDown = 0;
        }
        if (!isForbidden(red.x+15-5, red.y+15)) {
            red.toRight = 0;
            red.toLeft = 1;
            red.toUp = 0;
            red.toDown = 0;
        }
        if (!isForbidden(red.x+15, red.y+15+5)) {
            red.toRight = 0;
            red.toLeft = 0;
            red.toUp = 1;
            red.toDown = 0;
        }
        if (!isForbidden(red.x+15, red.y+15-5)) {
            red.toRight = 0;
            red.toLeft = 0;
            red.toUp = 0;
            red.toDown = 1;
        }
    }
    else {
        if (dir == 1) {
            if (!isForbidden(red.x+15+5, red.y+15)) {
            red.toRight = 1;
            red.toLeft = 0;
            red.toUp = 0;
            red.toDown = 0;
            }
        }
        if (dir == 2) {
            if (!isForbidden(red.x+15-5, red.y+15)) {
            red.toRight = 0;
            red.toLeft = 1;
            red.toUp = 0;
            red.toDown = 0;
            }
        }
        else if (dir == 3) {
            if (!isForbidden(red.x+15, red.y+15+5)) {
            red.toRight = 0;
            red.toLeft = 0;
            red.toUp = 1;
            red.toDown = 0;
            }
        }
        else if (dir == 4) {
            if (!isForbidden(red.x+15, red.y+15-5)) {
            red.toRight = 0;
            red.toLeft = 0;
            red.toUp = 0;
            red.toDown = 1;
            }
        }
    }


    if (!gameOn) return;
    if (pacoBonus) return;

    if (red.x==590-15&&red.y==350-15&&red.toRight) {
        red.x = 50-15;
    }
    if (red.x==50-15&&red.y==350-15&&red.toLeft) {
        red.x = 590-15;
    }
    if (red.toRight) {
        strcpy(red.photo, "redRt.bmp");
        red.x += 5;
    }

    else if (red.toLeft) {
        strcpy(red.photo, "redLt.bmp");
        red.x -= 5;
    }

    else if (red.toUp) {
        strcpy(red.photo, "redUp.bmp");
        red.y += 5;
    }

    else if (red.toDown) {
        strcpy(red.photo, "redDn.bmp");
        red.y -= 5;
    }

}

void moveCyan()
{
    int targetX = paco.x - (red.x-paco.x), targetY = paco.y - (red.y-paco.y);

    if (!cyan.fear) {
        targetX = 590;
        targetY = 50;
    }

    if (cyan.x==590-15&&cyan.y==50-15)
        cyan.fear = 1;

    double dist = 1000000000, tmp;
    int dir = 0;

    if (!isForbidden(cyan.x+15+5,cyan.y+15)&&!cyan.toLeft) {
        tmp = sqrt((cyan.x+5-targetX)*(cyan.x+5-targetX)+(cyan.y-targetY)*(cyan.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 1;
        }
    }

    if (!isForbidden(cyan.x+15-5,cyan.y+15)&&!cyan.toRight) {
        tmp = sqrt((cyan.x-5-targetX)*(cyan.x-5-targetX)+(cyan.y-targetY)*(cyan.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 2;
        }
    }

    if (!isForbidden(cyan.x+15,cyan.y+15+5)&&!cyan.toDown) {
        tmp = sqrt((cyan.x-targetX)*(cyan.x-targetX)+(cyan.y+5-targetY)*(cyan.y+5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 3;
        }
    }

    if (!isForbidden(cyan.x+15,cyan.y+15-5)&&!cyan.toUp) {
        tmp = sqrt((cyan.x-targetX)*(cyan.x-targetX)+(cyan.y-5-targetY)*(cyan.y-5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 4;
        }
    }

    if (dir==0) {
        if (!isForbidden(cyan.x+15+5, cyan.y+15)) {
            cyan.toRight = 1;
            cyan.toLeft = 0;
            cyan.toUp = 0;
            cyan.toDown = 0;
        }
        if (!isForbidden(cyan.x+15-5, cyan.y+15)) {
            cyan.toRight = 0;
            cyan.toLeft = 1;
            cyan.toUp = 0;
            cyan.toDown = 0;
        }
        if (!isForbidden(cyan.x+15, cyan.y+15+5)) {
            cyan.toRight = 0;
            cyan.toLeft = 0;
            cyan.toUp = 1;
            cyan.toDown = 0;
        }
        if (!isForbidden(cyan.x+15, cyan.y+15-5)) {
            cyan.toRight = 0;
            cyan.toLeft = 0;
            cyan.toUp = 0;
            cyan.toDown = 1;
        }
    }
    else {
        if (dir == 1) {
            if (!isForbidden(cyan.x+15+5, cyan.y+15)) {
            cyan.toRight = 1;
            cyan.toLeft = 0;
            cyan.toUp = 0;
            cyan.toDown = 0;
            }
        }
        if (dir == 2) {
            if (!isForbidden(cyan.x+15-5, cyan.y+15)) {
            cyan.toRight = 0;
            cyan.toLeft = 1;
            cyan.toUp = 0;
            cyan.toDown = 0;
            }
        }
        else if (dir == 3) {
            if (!isForbidden(cyan.x+15, cyan.y+15+5)) {
            cyan.toRight = 0;
            cyan.toLeft = 0;
            cyan.toUp = 1;
            cyan.toDown = 0;
            }
        }
        else if (dir == 4) {
            if (!isForbidden(cyan.x+15, cyan.y+15-5)) {
            cyan.toRight = 0;
            cyan.toLeft = 0;
            cyan.toUp = 0;
            cyan.toDown = 1;
            }
        }
    }


    if (!gameOn) return;
    if (pacoBonus) return;

    if (cyan.x==590-15&&cyan.y==350-15&&cyan.toRight) {
        cyan.x = 50-15;
    }
    if (cyan.x==50-15&&cyan.y==350-15&&cyan.toLeft) {
        cyan.x = 590-15;
    }
    if (cyan.toRight) {
        strcpy(cyan.photo, "cyanRt.bmp");
        cyan.x += 5;
    }

    else if (cyan.toLeft) {
        strcpy(cyan.photo, "cyanLt.bmp");
        cyan.x -= 5;
    }

    else if (cyan.toUp) {
        strcpy(cyan.photo, "cyanUp.bmp");
        cyan.y += 5;
    }

    else if (cyan.toDown) {
        strcpy(cyan.photo, "cyanDn.bmp");
        cyan.y -= 5;
    }
}

void movePink()
{
    int targetX, targetY;

    if (paco.toRight) {
        targetX = paco.x + 80;
        targetY = paco.y;
    }

    if (paco.toLeft) {
        targetX = paco.x - 80;
        targetY = paco.y;
    }

    if (paco.toUp) {
        targetX = paco.x;
        targetY = paco.y + 80;
    }

    if (paco.toDown) {
        targetX = paco.x;
        targetY = paco.y - 80;
    }

    if (!pink.fear) {
        targetX = 50;
        targetY = 610;
    }

    if (pink.x==50-15&&pink.y==610-15)
        pink.fear = 1;

    if ((red.x-pink.x)*(red.x-pink.x)+(red.y-pink.y)*(red.y-pink.y) <= 160*160)
        pink.fear = 0;

    double dist = 1000000000, tmp;
    int dir = 0;

    if (!isForbidden(pink.x+15+5,pink.y+15)&&!pink.toLeft) {
        tmp = sqrt((pink.x+5-targetX)*(pink.x+5-targetX)+(pink.y-targetY)*(pink.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 1;
        }
    }

    if (!isForbidden(pink.x+15-5,pink.y+15)&&!pink.toRight) {
        tmp = sqrt((pink.x-5-targetX)*(pink.x-5-targetX)+(pink.y-targetY)*(pink.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 2;
        }
    }

    if (!isForbidden(pink.x+15,pink.y+15+5)&&!pink.toDown) {
        tmp = sqrt((pink.x-targetX)*(pink.x-targetX)+(pink.y+5-targetY)*(pink.y+5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 3;
        }
    }

    if (!isForbidden(pink.x+15,pink.y+15-5)&&!pink.toUp) {
        tmp = sqrt((pink.x-targetX)*(pink.x-targetX)+(pink.y-5-targetY)*(pink.y-5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 4;
        }
    }

    if (dir==0) {
        if (!isForbidden(pink.x+15+5, pink.y+15)) {
            pink.toRight = 1;
            pink.toLeft = 0;
            pink.toUp = 0;
            pink.toDown = 0;
        }
        if (!isForbidden(pink.x+15-5, pink.y+15)) {
            pink.toRight = 0;
            pink.toLeft = 1;
            pink.toUp = 0;
            pink.toDown = 0;
        }
        if (!isForbidden(pink.x+15, pink.y+15+5)) {
            pink.toRight = 0;
            pink.toLeft = 0;
            pink.toUp = 1;
            pink.toDown = 0;
        }
        if (!isForbidden(pink.x+15, pink.y+15-5)) {
            pink.toRight = 0;
            pink.toLeft = 0;
            pink.toUp = 0;
            pink.toDown = 1;
        }
    }
    else {
        if (dir == 1) {
            if (!isForbidden(pink.x+15+5, pink.y+15)) {
            pink.toRight = 1;
            pink.toLeft = 0;
            pink.toUp = 0;
            pink.toDown = 0;
            }
        }
        if (dir == 2) {
            if (!isForbidden(pink.x+15-5, pink.y+15)) {
            pink.toRight = 0;
            pink.toLeft = 1;
            pink.toUp = 0;
            pink.toDown = 0;
            }
        }
        else if (dir == 3) {
            if (!isForbidden(pink.x+15, pink.y+15+5)) {
            pink.toRight = 0;
            pink.toLeft = 0;
            pink.toUp = 1;
            pink.toDown = 0;
            }
        }
        else if (dir == 4) {
            if (!isForbidden(pink.x+15, pink.y+15-5)) {
            pink.toRight = 0;
            pink.toLeft = 0;
            pink.toUp = 0;
            pink.toDown = 1;
            }
        }
    }


    if (!gameOn) return;
    if (pacoBonus) return;

    if (pink.x==590-15&&pink.y==350-15&&pink.toRight) {
        pink.x = 50-15;
    }
    if (pink.x==50-15&&pink.y==350-15&&pink.toLeft) {
        pink.x = 590-15;
    }
    if (pink.toRight) {
        strcpy(pink.photo, "pinkRt.bmp");
        pink.x += 5;
    }

    else if (pink.toLeft) {
        strcpy(pink.photo, "pinkLt.bmp");
        pink.x -= 5;
    }

    else if (pink.toUp) {
        strcpy(pink.photo, "pinkUp.bmp");
        pink.y += 5;
    }

    else if (pink.toDown) {
        strcpy(pink.photo, "pinkDn.bmp");
        pink.y -= 5;
    }
}

void moveOrange()
{
    int targetX = paco.x, targetY = paco.y;

    if (!orange.fear) {
        targetX = 50;
        targetY = 50;
    }

    if (orange.x==50-15&&orange.y==50-15)
        orange.fear = 1;

    if ((orange.x-paco.x)*(orange.x-paco.x)+(orange.y-paco.y)*(orange.y-paco.y) <= 160*160)
        orange.fear = 0;

    double dist = 1000000000, tmp;
    int dir = 0;

    if (!isForbidden(orange.x+15+5,orange.y+15)&&!orange.toLeft) {
        tmp = sqrt((orange.x+5-targetX)*(orange.x+5-targetX)+(orange.y-targetY)*(orange.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 1;
        }
    }

    if (!isForbidden(orange.x+15-5,orange.y+15)&&!orange.toRight) {
        tmp = sqrt((orange.x-5-targetX)*(orange.x-5-targetX)+(orange.y-targetY)*(orange.y-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 2;
        }
    }

    if (!isForbidden(orange.x+15,orange.y+15+5)&&!orange.toDown) {
        tmp = sqrt((orange.x-targetX)*(orange.x-targetX)+(orange.y+5-targetY)*(orange.y+5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 3;
        }
    }

    if (!isForbidden(orange.x+15,orange.y+15-5)&&!orange.toUp) {
        tmp = sqrt((orange.x-targetX)*(orange.x-targetX)+(orange.y-5-targetY)*(orange.y-5-targetY));

        if (tmp < dist) {
            dist = tmp;
            dir = 4;
        }
    }

    if (dir==0) {
        if (!isForbidden(orange.x+15+5, orange.y+15)) {
            orange.toRight = 1;
            orange.toLeft = 0;
            orange.toUp = 0;
            orange.toDown = 0;
        }
        if (!isForbidden(orange.x+15-5, orange.y+15)) {
            orange.toRight = 0;
            orange.toLeft = 1;
            orange.toUp = 0;
            orange.toDown = 0;
        }
        if (!isForbidden(orange.x+15, orange.y+15+5)) {
            orange.toRight = 0;
            orange.toLeft = 0;
            orange.toUp = 1;
            orange.toDown = 0;
        }
        if (!isForbidden(orange.x+15, orange.y+15-5)) {
            orange.toRight = 0;
            orange.toLeft = 0;
            orange.toUp = 0;
            orange.toDown = 1;
        }
    }
    else {
        if (dir == 1) {
            if (!isForbidden(orange.x+15+5, orange.y+15)) {
            orange.toRight = 1;
            orange.toLeft = 0;
            orange.toUp = 0;
            orange.toDown = 0;
            }
        }
        if (dir == 2) {
            if (!isForbidden(orange.x+15-5, orange.y+15)) {
            orange.toRight = 0;
            orange.toLeft = 1;
            orange.toUp = 0;
            orange.toDown = 0;
            }
        }
        else if (dir == 3) {
            if (!isForbidden(orange.x+15, orange.y+15+5)) {
            orange.toRight = 0;
            orange.toLeft = 0;
            orange.toUp = 1;
            orange.toDown = 0;
            }
        }
        else if (dir == 4) {
            if (!isForbidden(orange.x+15, orange.y+15-5)) {
            orange.toRight = 0;
            orange.toLeft = 0;
            orange.toUp = 0;
            orange.toDown = 1;
            }
        }
    }


    if (!gameOn) return;
    if (pacoBonus) return;

    if (orange.x==590-15&&orange.y==350-15&&orange.toRight) {
        orange.x = 50-15;
    }
    if (orange.x==50-15&&orange.y==350-15&&orange.toLeft) {
        orange.x = 590-15;
    }
    if (orange.toRight) {
        strcpy(orange.photo, "orangeRt.bmp");
        orange.x += 5;
    }

    else if (orange.toLeft) {
        strcpy(orange.photo, "orangeLt.bmp");
        orange.x -= 5;
    }

    else if (orange.toUp) {
        strcpy(orange.photo, "orangeUp.bmp");
        orange.y += 5;
    }

    else if (orange.toDown) {
        strcpy(orange.photo, "orangeDn.bmp");
        orange.y -= 5;
    }
}

void bonusCalculator()
{
    if (!pacoBonus) return;
    bonus++;

    if (bonus == 60) {
        bonus = 0;
        pacoBonus = 0;
    }
}

int main()
{
    //place your own initialization codes here.


    if (music)
            PlaySound((LPCSTR) "E:\\Pacman Project\\pacman_intermission.wav", NULL, SND_FILENAME | SND_ASYNC);


    generateFoods();
    initializeLeaderBoard();


    iSetTimer(35, movePaco);

    iSetTimer(35, moveRed);
    iSetTimer(35, moveCyan);
    iSetTimer(35, movePink);
    iSetTimer(35, moveOrange);


    iSetTimer(50, bonusCalculator);


    iInitialize(width, height, "Pac-Man");

    return 0;
}
