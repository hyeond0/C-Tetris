#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

#define MAPWIDTH    15 // �� Row ũ�� ����, ���� ���� �����Ƿ� ���������δ� Row + 2
#define MAPHEIGHT   30 // �� Col ũ�� ����, �� �Ʒ� ���� �����Ƿ� ���������δ� Col + 1

// ����� 1, �� ������ 0, ���� 2


typedef struct _currentPosition // ��� ��ǥ ��� ���� ����ü �ڷ��� ����
{
    int X;
    int Y;
} Position;

void PositionInit(Position* BlockPos) // ��� ��ǥ �ʱⰪ ����
{
    BlockPos->X = 5;
    BlockPos->Y = 0;
}

void ConsoleInit() // �ܼ� Ŀ�� ���� ���� �� �ܼ� â ũ�� ����
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    system("mode con cols=100 lines=40"); // �ܼ� â ũ�� ����
}
void gotoxy(int x, int y) // Ŀ�� ��ǥ �̵� �Լ�
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

enum MAIN_MENU
{
    MENU_START = 1,
    MENU_EXIT,
    MENU_NONE
};

enum Block_Info
{
    BlockNull,
    BlockI,
    BlockO,
    BlockT,
    BlockZ,
    BlockS,
    BlockL,
    BlockJ,
};

Block_Info BlockInfo = BlockNull;

class CMenu
{
public:
    int OutputMenu()
    {
        while (true)
        {
            system("cls");
            CreateLogo();
            gotoxy(22, 17);
            cout << "======================= 1. ���� =======================" << endl;
            gotoxy(22, 18);
            cout << "======================= 2. ���� =======================" << endl;

            gotoxy(22, 22);
            cout << "�޴��� �����ϼ��� : ";
            int iInput = InputInt();
            if (iInput < MENU_START || iInput >= MENU_NONE)
            {
                cout << "�ٽ� �Է��ϼ���." << endl;
                system("pause");
                continue;
            }
            return iInput;
        }

    }

private:
    void CreateLogo() // Tetris ���
    {
        gotoxy(20, 7);
        cout << "    ######    ###     ######   ###      ###       ##     " << endl;
        gotoxy(20, 8);
        cout << "     ###    ##        ####    ## ##      ##     ## #    " << endl;
        gotoxy(20, 9);
        cout << "      ##    ##          ##    ##  ##     ##     ##      " << endl;
        gotoxy(20, 10);
        cout << "      ##   #####        ##   #####       ##     ####   " << endl;
        gotoxy(20, 11);
        cout << "      ##   ##           ##   ####       ###         ## " << endl;
        gotoxy(20, 12);
        cout << "      ###  ###          ###  ## ##      ###    ###  ## " << endl;
        gotoxy(20, 13);
        cout << "      ###    #####      ###  ##   ##    ###     #####  " << endl;
    }

    int InputInt()
    {
        int iInput;
        cin >> iInput;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            return 0;
        }

        return iInput;
    }
};

class CBlock
{
public:
    int IBlock[5][5] =
    {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0}
    };

    int OBlock[5][5] =
    {
        {0,0,0,0,0},
        {0,1,1,0,0},
        {0,1,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int TBlock[5][5] =
    {
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int ZBlock[5][5] =
    {
        {0,0,0,0,0},
        {0,1,1,0,0},
        {0,0,1,1,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int SBlock[5][5] =
    {
        {0,0,0,0,0},
        {0,0,1,1,0},
        {0,1,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int LBlock[5][5] =
    {
        {0,1,0,0,0},
        {0,1,0,0,0},
        {0,1,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int JBlock[5][5] =
    {
        {0,0,0,1,0},
        {0,0,0,1,0},
        {0,0,1,1,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    void DrawNextBlock(int blockShape[5][5]) // ���� ��� ���
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                gotoxy(57 + j * 2, 6 + i);
                cout << "  ";
            }
        }
        switch (BlockInfo)
        {
        case BlockI:
            for (int i = 0; i < 4; i++)
            {
                gotoxy(62, 8 + i);
                cout << "��";
            }
            break;
        case BlockO:
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                {
                    gotoxy(61 + j * 2, 8 + i);
                    cout << "��";
                }
            break;
        case BlockT:
            for (int j = 0; j <= 2; j++)
            {
                gotoxy(60 + j * 2, 8);
                cout << "��";
            }
            gotoxy(62, 9);
            cout << "��";
            break;
        case BlockZ:
            for (int j = 0; j < 2; j++)
            {
                gotoxy(61 + j * 2, 9);
                cout << "��";
                gotoxy(61 + j * 2 + 2, 10);
                cout << "��";
            }
            break;
        case BlockS:
            for (int j = 0; j < 2; j++)
            {
                gotoxy(63 + j * 2, 9);
                cout << "��";
                gotoxy(63 + j * 2 - 2, 10);
                cout << "��";
            }
            break;
        case BlockL:
            for (int i = 0; i < 3; i++)
            {
                gotoxy(61, 8 + i);
                cout << "��";
                if (i == 2)
                {
                    gotoxy(63, 8 + i);
                    cout << "��";
                }
            }
            break;
        case BlockJ:
            for (int i = 0; i < 3; i++)
            {
                gotoxy(63, 8 + i);
                cout << "��";
                if (i == 2)
                {
                    gotoxy(61, 8 + i);
                    cout << "��";
                }
            }
            break;
        default:
            break;
        }
    }
    void SetBlock(int blockShape[5][5]) // ���� ���, ���� ��� ����
    {
        srand((unsigned int)(time(NULL)));
        switch (rand() % 7) { // switch������ �� ���� �� Blockshape�� ����

        case 0:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = IBlock[i][j];
            BlockInfo = BlockI;
            break;
        case 1:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = OBlock[i][j];
            BlockInfo = BlockO;
            break;
        case 2:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = TBlock[i][j];
            BlockInfo = BlockT;
            break;
        case 3:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = ZBlock[i][j];
            BlockInfo = BlockZ;
            break;
        case 4:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = SBlock[i][j];
            BlockInfo = BlockS;
            break;
        case 5:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = LBlock[i][j];
            BlockInfo = BlockL;
            break;
        case 6:
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    blockShape[i][j] = JBlock[i][j];
            BlockInfo = BlockJ;
            break;
        default:
            break;
        }
    }

    void LimitBottom(int blockShape[5][5], int BottomArray[], int* BottomRow)
    {
        // �� ������ ���� �Ʒ��� �ִ� ���� BottomArray�� �����ϰ�, �� ���� BottomRow�� �����Ѵ�.
        for (int i = 0; i <= 4; i++)
        {
            for (int j = 0; j <= 4; j++)
            {
                if (blockShape[i][j] == 1)
                {
                    BottomArray[j] = i;
                    if ((*BottomRow) < BottomArray[j])
                        (*BottomRow) = BottomArray[j];
                }
            }
        }
    }

    int LimitLeft(int blockShape[5][5], int i, int LeftArray[], int* LeftRow, int* LeftCol)
    {
        // �� �ึ�� ���� ���ʿ� �ִ� ���� LeftArray�� �����ϰ�, LeftCol�� ���� ���ʿ� �ִ� ���� ��, LeftRow�� ���� ���ʿ� �ִ� ���� ���̴�.
        for (int j = 4; j >= 0; j--)
        {
            if (blockShape[i][j] == 1)
            {
                LeftArray[i] = j;
                if ((*LeftCol) > j)
                {
                    (*LeftCol) = j;
                    (*LeftRow) = i;
                }
            }
        }
        return LeftArray[i];
    }

    int LimitRight(int blockShape[5][5], int i, int RightArray[], int* RightRow, int* RightCol)
    {
        for (int j = 0; j <= 4; j++)
        {
            if (blockShape[i][j] == 1)
            {
                RightArray[i] = j;
                if ((*RightCol) < j)
                {
                    (*RightCol) = j;
                    (*RightRow) = i;
                }
            }
        }
        return RightArray[i];
    }
};

class CMap
{

public:
    CBlock Block;

    void InitMap(char map[MAPHEIGHT][MAPWIDTH]) // �� �ʱ�ȭ
    {
        for (int i = 0; i < MAPHEIGHT; i++)
        {
            for (int j = 0; j < MAPWIDTH; j++)
                map[i][j] = '0';
        }
    }

    void DrawMap(char map[MAPHEIGHT][MAPWIDTH]) // �� ����
    {

        // 1. 30x15 ���� �����δ� Ʋ ���� �� ���

        gotoxy(10, 5);
        for (int i = 0; i <= MAPHEIGHT; i++)
        {
            for (int j = 0; j < MAPWIDTH + 2; j++)
            {
                gotoxy(10 + j * 2, 5 + i);
                if (j == MAPWIDTH + 1 || j == 0 || i == MAPHEIGHT)
                    cout << "��";
            }
        }

        // 2. Ʋ �ȿ� 30x15 �� ���� �� ���

        gotoxy(12, 5);
        for (int i = 0; i < MAPHEIGHT; i++)
        {
            for (int j = 0; j < MAPWIDTH; j++)
            {
                gotoxy(12 + j * 2, 5 + i);
                if (map[i][j] == '0')
                    cout << "  ";
                else if (map[i][j] == '1')
                    cout << "��";
            }
            cout << endl;
        }
    }

    void DrawSubMap(int best, int score) // ����� (���� ���, ����ĭ) ����
    {

        gotoxy(61, 6);
        cout << "NEXT";
        for (int i = 0; i <= 7; i++)
        {
            for (int j = 0; j <= 7; j++)
            {
                gotoxy(55 + j * 2, 6 + i);
                if (j == 7 || j == 0 || i == 7)
                    cout << "��";
            }
        }

        gotoxy(60, 18);
        cout << "SCORE";
        for (int i = 0; i <= 4; i++)
        {
            for (int j = 0; j <= 7; j++)
            {
                gotoxy(55 + j * 2, 18 + i);
                if (j == 0 || j == 7 || i == 4)
                    cout << "��";
            }
        }

        gotoxy(62, 20);
        if (score > 100)
            gotoxy(61, 20);
        else if (score > 1000)
            gotoxy(60, 20);
        else if (score > 10000)
            gotoxy(59, 20);
        else if (score > 100000)
            gotoxy(58, 20);
        cout << score;
    }
    void RemoveShape(char Map[MAPHEIGHT][MAPWIDTH], int blockShape[5][5], Position* BlockPos)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (blockShape[i][j] == 1) // ����̸� 
                    Map[BlockPos->Y + i][BlockPos->X + j] = '0';
            }
        }
    }

    void CheckLine(char Map[MAPHEIGHT][MAPWIDTH], Position BlockPos, int* score)
    {
        int count = 0;
        int linecount = 0;
        int height = 0;

        for (int i = MAPHEIGHT; i >= (BlockPos.Y); i--)
        {
            for (int j = 0; j < MAPWIDTH; j++)
            {
                if (Map[i][j] == '0') {
                    break;
                }
                else if (Map[i][j] == '1')
                {
                    height = i;
                    count++;
                }

                if (count == MAPWIDTH)
                {
                    linecount++;
                    for (int j = 0; j <= MAPWIDTH; j++)
                    {
                        Map[height][j] = '0';
                    }

                    while (height > 1)
                    {
                        for (int j = 0; j <= MAPWIDTH; j++)
                        {
                            Map[height][j] = Map[height - 1][j];
                        }
                        height--;
                    }
                    i++; // �� �پ� �� �������Ƿ� �ٽ� �� �ٺ��� üũ
                }
            }
            count = 0;
        }

        if (linecount == 1)
            (*score) += 500;
        else if (linecount == 2)
            (*score) += 2500;
        else if (linecount == 3)
            (*score) += 5000;
        else if (linecount == 4)
            (*score) += 10000;
    }



    void OutputBlock(char Map[MAPHEIGHT][MAPWIDTH], int blockShape[5][5], Position BlockPos) // ��� ��� : 2���� �迭 Map�� ǥ��
    {
        // �� ��翡 �ش��ϴ� ��ǥ�� Map���� ��ǥ�� �ѷ��� ('1' �ο�)
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (blockShape[i][j] == 1)
                    Map[BlockPos.Y + i][BlockPos.X + j] = '1';
            }
        }
    }

    bool GoDown(char Map[MAPHEIGHT][MAPWIDTH], int blockShape[5][5], Position* BlockPos)
    {
        int BottomArray[5] = {}; // �� ������ ���� �Ʒ��� �ִ� ���� �����ϴ� �迭
        int BottomRow = 0; // ���� �Ʒ��� ��

        Block.LimitBottom(blockShape, BottomArray, &BottomRow); // botRow�� ���� ���� �Ʒ� ���� ����, Array�� �� ���� ������ ���� ����
        //Left, Right�� �ٸ��� Array�� �� ���� �ƴ�, �� ���� �������� ����ƴ�.
        //��� ���� �Ʒ��κ��� y��ǥ�� blocky�� ����, �� x�࿡ ���� �Ʒ��κ��� bottomArray�� ����
        for (int i = 0; i <= 4; i++)
        {
            if (BottomArray[i] != 0)
            {
                if (Map[(BlockPos->Y) + BottomArray[i] + 1][(BlockPos->X) + i] == '1' || (BlockPos->Y) + BottomRow + 1 == MAPHEIGHT)
                { // �� ���� ���� �Ʒ� ��� �� ĭ �Ʒ��� ����� �ְų� ��ĭ �Ʒ��� ���� ���, true�� ��ȯ�Ͽ� �ٴڿ� ��Ҵٴ� ���� �˷��ش�.
                    return true;
                }
            }
        }
        RemoveShape(Map, blockShape, BlockPos);
        Sleep(80);
        (BlockPos->Y)++;
        return false; // ���� �ʾ����� ����� �� ĭ �Ʒ��� ������.
    }

    void GoLeft(char Map[MAPHEIGHT][MAPWIDTH], int blockShape[5][5], Position* BlockPos)
    {
        int LeftArray[5] = {};
        bool goLeft = true;
        int LeftRow = 0;
        int LeftCol = 4;

        for (int i = 0; i <= 4; i++)
        {
            LeftArray[i] = Block.LimitLeft(blockShape, i, LeftArray, &LeftRow, &LeftCol);
            // LeftArray�� �� �࿡ ���� ���ʿ� �ִ� ����� ���� �����ϰ�, LeftRow�� ���� ���ʿ� �ִ� ����� ���� �����Ѵ�.
        }

        if ((BlockPos->X) + LeftArray[LeftRow] - 1 < 0) // ���� ���ʿ� �ִ� ���� �� ĭ ������ ���̸� �� �̻� ���� ���ϰ� false�� �ٲ۴�.
            goLeft = false;
        for (int j = 4; j >= 0; j--)
        {
            if (LeftArray[j] != 0)
            {
                if (Map[(BlockPos->Y) + j][(BlockPos->X) + LeftArray[j] - 1] == '1') // �� ���� ���� ���ʿ� �ִ� �� �� ĭ ���ʿ� ����� �ִٸ�, �� �̻� ���� ���ϰ� false�� �ٲ۴�.
                {
                    goLeft = false;
                }
            }
        }

        if (goLeft == true)
        {
            RemoveShape(Map, blockShape, BlockPos);
            (BlockPos->X)--;
        }
    }

    void GoRight(char Map[MAPHEIGHT][MAPWIDTH], int blockShape[5][5], Position* BlockPos)
    {
        int RightArray[5] = {};
        int RightRow = 0;
        int RightCol = 0;
        bool goRight = true;

        for (int i = 0; i <= 4; i++)
        {
            RightArray[i] = Block.LimitRight(blockShape, i, RightArray, &RightRow, &RightCol);
            // Left�� ���� ������� ����.
        }

        if ((BlockPos->X) + RightArray[RightRow] + 1 >= MAPWIDTH)
            goRight = false;
        for (int j = 0; j <= 4; j++)
        {

            if (RightArray[j] != 0)
            {
                if (Map[(BlockPos->Y) + j][(BlockPos->X) + RightArray[j] + 1] == '1')
                {
                    goRight = false;
                }
            }
        }

        if (goRight == true)
        {
            RemoveShape(Map, blockShape, BlockPos);
            (BlockPos->X)++;
        }
    }
    void Rotate(char Map[MAPHEIGHT][MAPWIDTH], int blockShape[5][5], Position* BlockPos)
    {
        int temp_arr[5][5] = {};
        int RightArray[5] = {}, LeftArray[5] = {}, BottomArray[5] = {};
        int RightRow = 0, RightCol = 0;
        int LeftRow = 0, LeftCol = 4;
        int BottomRow = 0;
        int count = 0;

        bool rotate = true;
        bool goLeft = true;
        bool goRight = true;

        RemoveShape(Map, blockShape, BlockPos);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                temp_arr[i][j] = blockShape[5 - j - 1][i];
            }
        }

        for (int i = 0; i < 5; i++)
        {
            RightArray[i] = Block.LimitRight(temp_arr, i, RightArray, &RightRow, &RightCol); // �� ���� ���� �����ʿ� �ִ� ���� ��
            LeftArray[i] = Block.LimitLeft(temp_arr, i, LeftArray, &LeftRow, &LeftCol); // �� ���� ���� ���ʿ� �ִ� ���� ��
        }

        Block.LimitBottom(temp_arr, BottomArray, &BottomRow);

        //////////////// ������� temp_arr�� rotate�� ����� �����ϰ� ��, ��, �Ʒ� ���� ���� �� ������ ���� //////////////////////////////

        while ((BlockPos->X) + LeftArray[LeftRow] - 1 < 0) // �ٲ� ����� ���� ���� ��ų� �� ĭ ���ʿ� ���� ���� ��
        {
            if (rotate == false)
            {
                count = 0;
                break;
            }

            for (int j = 0; j <= 4; j++)
            {
                if (Map[(BlockPos->Y) + j][(BlockPos->X) + RightArray[j] + 1] != '1' && Map[(BlockPos->Y) + BottomArray[j] + 1][(BlockPos->X) + j] != '1') // ��ĭ �����ʿ��� ���� ���� �Ʒ��� ������
                    count++;
                else
                {
                    rotate = false;
                    break;
                }
            }

            if (count == 5)
            {
                goRight = true;
                count = 0;
            }

            if (goRight == true)
                (BlockPos->X)++;
            if (rotate == false)
            {
                count = 0;
                break;
            }
        }

        //////////////////////////////////////////////////////////////////��

        while ((BlockPos->X) + RightArray[RightRow] + 1 >= MAPWIDTH) // ������ ���� ��Ұų�  �����ʿ� ���� ���� ��
        {
            goLeft = false;
            if (rotate == false)
            {
                count = 0;
                break;
            }

            for (int j = 0; j <= 4; j++)
            {
                if (Map[(BlockPos->Y) + j][(BlockPos->X) + LeftArray[j] - 1] != '1' && Map[(BlockPos->Y) + BottomArray[j] + 1][(BlockPos->X) + j] != '1') // ��ĭ ���ʿ��� ���� ���� �Ʒ����� ���� ������
                    count++;
                else
                {
                    rotate = false;
                    break;
                }

                if (count == 5)
                {
                    goLeft = true;
                    count = 0;
                }

                if (goLeft == true)
                {
                    (BlockPos->X)--;
                    goLeft = false;
                }

                if (rotate == false)
                {
                    count = 0;
                    break;
                }
            }
        }
        while ((BlockPos->Y) + BottomArray[BottomRow] >= MAPHEIGHT)
        {
            if (rotate == false)
            {
                count = 0;
                break;
            }

            for (int i = 0; i <= 4; i++)
            {
                if (Map[(BlockPos->Y) + i][(BlockPos->X) + LeftArray[i] - 1] != '1' && Map[(BlockPos->Y) + i][(BlockPos->X) + RightArray[i] + 1] != '1') // ��ĭ ���ʿ��� ���� ���� �Ʒ����� ���� ������
                    count++;
                else
                {
                    rotate = false;
                    break;
                }

                if (count == 5)
                {
                    (BlockPos->Y)--;
                    count = 0;
                }

                if (rotate == false)
                {
                    count = 0;
                    break;
                }
            }
        }

        for (int i = 0; i <= 4; i++)
        {
            if (Map[(BlockPos->Y) + i][(BlockPos->X) + LeftArray[i] - 1] == '1') // �� ���ʿ� ���� �ֵ���;
            {
                for (int j = 0; j <= 4; j++)
                {
                    if (Map[(BlockPos->Y) + j][(BlockPos->X) + LeftArray[j] - 1] != '1')
                    {
                        if (Map[(BlockPos->Y) + j][(BlockPos->X) + RightArray[j] + 1] != '1' && Map[(BlockPos->Y) + BottomArray[j] + 1][(BlockPos->X) + j] != '1')
                            count++;
                        else
                        {
                            rotate = false;
                            break;
                        }
                    }
                    else
                    {
                        rotate = false;
                        break;
                    }
                }


                if (count == 5)
                {
                    (BlockPos->X)++;
                    count = 0;
                }

                if (rotate == false)
                {
                    count = 0;
                    break;
                }
            }
        }

        for (int i = 0; i <= 4; i++)
        {
            if (Map[(BlockPos->Y) + i][(BlockPos->X) + RightArray[i] + 1] == '1') // �� ���ʿ� ���� �ֵ���;
            {
                for (int j = 0; j <= 4; j++)
                {
                    if (Map[(BlockPos->Y) + j][(BlockPos->X) + RightArray[j] + 1] != '1')
                    {
                        if (Map[(BlockPos->Y) + j][(BlockPos->X) + LeftArray[j] - 1] != '1' && Map[(BlockPos->Y) + BottomArray[j] + 1][(BlockPos->X) + j] != '1')
                            count++;
                        else
                        {
                            rotate = false;
                            break;
                        }
                    }
                    else
                    {
                        rotate = false;
                        break;
                    }
                }


                if (count == 5)
                {
                    (BlockPos->X)--;
                    count = 0;
                }

                if (rotate == false)
                {
                    count = 0;
                    break;
                }
            }
        }
        ////////////////////////////////// ��������� ����. ///////////////////


        if (rotate == true) // rotate�� ���� �ϴٸ� temp_arr�� ��Ͻ������� �״�� �Ű��ش�.
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    blockShape[i][j] = temp_arr[i][j];
                }
            }
        }
    }

    bool NoRotate(int BlockShape[5][5])
    {
        int count = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (BlockShape[i][j] == Block.OBlock[i][j])
                    count++;
            }
        }
        if (count == 25)
            return true;

        return false;
    }

    bool GameOverCheck(char map[MAPHEIGHT][MAPWIDTH])
    {
        for (int i = 0; i < MAPWIDTH; i++)
            if (map[0][i] == '1')
                return true;
        return false;
    }

    void GameOver(int* score)
    {
        system("cls");

        gotoxy(15, 12);
        cout << "  ####      ##     ##  ##   ######    ####    ##  ##   ######   #####   " << endl;
        gotoxy(15, 13);
        cout << " ##  ##    ####    ######   ##       ##  ##   ##  ##   ##       ##  ##  " << endl;
        gotoxy(15, 14);
        cout << " ##       ##  ##   ######   ####     ##  ##   ##  ##   ####     ##  ##  " << endl;
        gotoxy(15, 15);
        cout << " ## ###   ######   ##  ##   ##       ##  ##   ##  ##   ##       #####   " << endl;
        gotoxy(15, 16);
        cout << " ##  ##   ##  ##   ##  ##   ##       ##  ##    ####    ##       ## ##   " << endl;
        gotoxy(15, 17);
        cout << "  ####    ##  ##   ##  ##   ######    ####      ##     ######   ##  ##  " << endl;

        gotoxy(33, 22);
        cout << " ����� ������ " << *score << "�� �Դϴ�." << endl;


        for (int i = 5; i > 0; --i)
        {
            gotoxy(37, 24);
            cout << i << "�� �� �����մϴ�";
            Sleep(1000);
        }
    }
};


int Play(char Map[MAPHEIGHT][MAPWIDTH])
{

    int Score = 0, BestScore = 0;
    int BlockShape[5][5] = {}; //�� 5x5
    int NextBlock[5][5] = {}; //���� ��
    bool Bottom = false;
    bool noRotate = false;
    CMap map;
    CBlock block;

    Position BlockPos = { 2,2 };
    map.InitMap(Map);
    map.DrawMap(Map);
    map.DrawSubMap(BestScore, Score);
    PositionInit(&BlockPos); // ��ġ �ʱ�ȭ

    block.SetBlock(BlockShape); // �� ��� ����, ȸ�� ���� �������� ��ȯ
    block.SetBlock(NextBlock); // ������ ��� ����
    block.DrawNextBlock(NextBlock);

    while (true)
    {

        if (Bottom == true)  // ����� �������� ������
        {
            if (map.GameOverCheck(Map) == true)
            {
                map.GameOver(&Score);
                return 0; // while�� Ż��
            }

            map.CheckLine(Map, BlockPos, &Score); // ���� üũ
            PositionInit(&BlockPos); // Ŀ�� �ʱ�ȭ

            for (int i = 0; i < 5; i++)// block�� ���� �� ������� ��������
                for (int j = 0; j < 5; j++)
                    BlockShape[i][j] = NextBlock[i][j];

            block.SetBlock(NextBlock); // ���� �� ���� �����
            block.DrawNextBlock(NextBlock); //���� �� ��� Map�� ���
            Bottom = false; // ���ο� ����� �������� ���� false�� ��ȯ
        }

        map.OutputBlock(Map, BlockShape, BlockPos);
        map.DrawMap(Map);
        map.DrawSubMap(BestScore, Score);

        noRotate = map.NoRotate(BlockShape);
        Bottom = map.GoDown(Map, BlockShape, &BlockPos);

        if (Bottom == true) continue;

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) // Press 'Space' : ��� ���� �̵�
            if (noRotate == false)
                map.Rotate(Map, BlockShape, &BlockPos);

        if (GetAsyncKeyState('A') & 0x8000) // Press 'A' : ��� ���� �̵�
            map.GoLeft(Map, BlockShape, &BlockPos);

        if (GetAsyncKeyState('D') & 0x8000) // Press 'D' : ��� ���� �̵�
            map.GoRight(Map, BlockShape, &BlockPos);
    }
    return 0;
}

int main()
{
    char Map[MAPHEIGHT][MAPWIDTH] = {}; // �� ��ǥ ��� ���� 2���� �迭 ����
    ConsoleInit(); // Ŀ�� ����� �� �ܼ�â ũ�� �ʱ�ȭ �Լ�

    CMenu Menu;
    int iInput = Menu.OutputMenu();// ����ü, Switch-Case���� ���� �޴� ������ �Է�

    switch (iInput)
    {
    case MENU_START:
        system("cls");
        Play(Map); // ���� ����
        break;
    case MENU_EXIT:
        system("cls");
        break;
    }
}