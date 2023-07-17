# C-Tetris
- C언어로 만든 테트리스 게임입니다. 터미널 환경에서 돌아가게 만들었습니다.

## Map

- 맵은 2차원 배열을 이용해 벽, 빈 공간, 블록을 구분해서 출력했습니다.
- gotoxy과 구조체 포인터를 활용해 출력을 해주고, Map 배열에 저장하는 방식으로
    
    구현했습니다.
    
- 다음 블록이 어떤 블록이 나오는지, 점수는 몇 점인지 나오게 구현했습니다.

## Block

- 블록은 5x5 배열을 이용해서 7개의 모양별로 블록을 구현했습니다.
- 랜덤 함수를 이용하여 7개의 블록 모양 중 하나가 출력되게 구현하였습니다.
- 회전 시 만들어질 블록 좌표에 블록이나 벽이 있는지 확인하고, 좌표를 한 칸 이동해 블록을
    
    출력할 수 있는 상황이면 이동하고, 그렇지 않으면 회전을 못 하도록 하였습니다.
    

## 기능

- A키로 ← 왼쪽으로 이동, D키로 → 오른쪽으로 이동합니다.
- Space 버튼을 누르면 오른쪽으로 90도 회전합니다.
- Sleep을 이용하여 일정한 속도로 블록이 내려옵니다.
- 라인이 다 블록으로 채워져서 지워질 때, 한 번에 여러 줄을 지우면 더 큰 점수를 얻습니다.
