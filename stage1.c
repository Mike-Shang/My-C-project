// cs_moonlander.c
// Fangyuan SHANG z5614452
// 10 15 2024 DMY
// COMP1511 Programming Fundamentals


#include <stdio.h>

// Provided Constant Definitions
#define BOARD_LEN 10
#define BOARD_MAX_LEVELS 32
#define BASE_OXY_RATE 1.0
#define MAX_PORTALS 16
#define TITLE_STR_LEN 25
#define INVALID_INDEX -1
#define COMMAND_QUIT 'q'



// Provided Enum Definitions
enum entity {
    EMPTY,
    CHEESE,
    ROCK,
    LANDER,
    HOLE_DOWN,
    HOLE_UP,
    PORTAL
};



// Provided Struct Definitions
struct tile {
    enum entity entity;
};


// Provided Function Prototypes
void init_board(
    struct tile board[BOARD_LEN][BOARD_LEN]
);
void print_board(
    struct tile board[BOARD_LEN][BOARD_LEN],
    int player_row,
    int player_col,
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate
);
void print_board_header(void);
void print_player_stats(
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate
);

////////////////////////////////////////////////////////////////////////////////////
void init_position_cheese_rock(struct tile board[BOARD_LEN][BOARD_LEN]);
void init_position_lander(struct tile board[BOARD_LEN][BOARD_LEN]);


int main(void) {

    struct tile board[BOARD_LEN][BOARD_LEN];
    init_board(board);                                                               
    init_position_lander(board);                                                     
    print_board(board, INVALID_INDEX, INVALID_INDEX, 0, 0, 0.0, 0.0, BASE_OXY_RATE); 
    init_position_cheese_rock(board);
    print_board(board, INVALID_INDEX, INVALID_INDEX, 0, 0, 0.0, 0.0, BASE_OXY_RATE);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void init_position_lander(struct tile board[BOARD_LEN][BOARD_LEN])
{
    int init_position_lander_row;
    int init_position_lander_col;

    printf("Please enter the [row] [col] of the lander: ");
    scanf("%d %d", &init_position_lander_row, &init_position_lander_col);

    
    if (init_position_lander_row < 0 || init_position_lander_row >= BOARD_LEN || init_position_lander_col < 0 || init_position_lander_col >= BOARD_LEN)
    {
        
        init_position_lander_col = 4;
        init_position_lander_row = 4;
    }

    board[init_position_lander_row][init_position_lander_col].entity = LANDER;
}

void init_position_cheese_rock(struct tile board[BOARD_LEN][BOARD_LEN])
{
    char command_type;
    int cheese_row, cheese_col;
    int rock_row, rock_col;
    int large_rock_start_row, large_rock_start_col, large_rock_end_row, large_rock_end_col;
    printf("Please enter cheese and rock locations:\n");
    while (scanf("%c", &command_type) == 1)
    {
        if (command_type == 'c')
        {
            
            scanf("%d %d", &cheese_row, &cheese_col);

            if (cheese_row >= 0 && cheese_row < BOARD_LEN && cheese_col >= 0 && cheese_col < BOARD_LEN && board[cheese_row][cheese_col].entity == EMPTY)
            {
                board[cheese_row][cheese_col].entity = CHEESE;
            }
            else
            {
                printf("That is not a valid cheese placement!\n");
            }
        }
        else if (command_type == 'r')
        {
            scanf("%d %d", &rock_row, &rock_col);
            if (rock_row >= 0 && rock_row < BOARD_LEN && rock_col >= 0 && rock_col < BOARD_LEN && board[rock_row][rock_col].entity == EMPTY)
            {
                board[rock_row][rock_col].entity = ROCK;
            }
            else
            {
                printf("That is not a valid rock placement!\n");
            }
        }
        else if (command_type == 'R')
        {
            scanf("%d %d %d %d", &large_rock_start_row, &large_rock_start_col, &large_rock_end_row, &large_rock_end_col);
            int valid = 1; 
            if (large_rock_start_row > large_rock_end_row || large_rock_start_col > large_rock_end_col)
            {
                valid = 0; 
            }
            for (int row = large_rock_start_row; row <= large_rock_end_row && valid; row++)
            {
                for (int col = large_rock_start_col; col <= large_rock_end_col && valid; col++)
                {
                    if (row < 0 || row >= BOARD_LEN || col < 0 || col >= BOARD_LEN || board[row][col].entity != EMPTY)
                    {
                        valid = 0; 
                    }
                }
            }
            if (valid)
            {
                for (int row = large_rock_start_row; row <= large_rock_end_row; row++)
                {
                    for (int col = large_rock_start_col; col <= large_rock_end_col; col++)
                    {
                        board[row][col].entity = ROCK; 
                    }
                }
            }
            else
            {
                printf("That is not a valid rock placement!\n");
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Initialises the board to EMPTY for each tile
void init_board(struct tile board[BOARD_LEN][BOARD_LEN]) {
    for (int row = 0; row < BOARD_LEN; row++) {
        for (int col = 0; col < BOARD_LEN; col++) {
            board[row][col].entity = EMPTY;
        }
    }
    return;
}

// Prints a line commonly used when printing the board, line length scales with
// the BOARD_LEN constant
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < BOARD_LEN; col++) {
        printf("---+");
    }
    printf("\n");
    return;
}

// Prints the header of the cs_moonlander board
void print_board_header(void) {
    char title_str[TITLE_STR_LEN + 1] = "C S   M O O N L A N D E R";

    printf("|");
    for (int i = (4 * BOARD_LEN - TITLE_STR_LEN) / 2; i > 0; i--) {
        printf(" ");
    }

    printf("%s", title_str);

    for (int i = (4 * BOARD_LEN - TITLE_STR_LEN) / 2; i > 0; i--) {
        printf(" ");
    }
    printf("|\n");

    return;
}

// Prints the player stats when requested by the user
void print_player_stats(
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate
) {
    printf("Player Cheese: %d     Lander Cheese: %d\n",
            cheese_held, cheese_lander);
    printf("Oxy: %.2lf / %.2lf  @  %.6lf / move\n", oxy_level,
            oxy_capacity, oxy_rate);
    return;
}

// Prints the cs_moonlander board
void print_board(
    struct tile board[BOARD_LEN][BOARD_LEN],
    int player_row,
    int player_col,
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate) {

    print_board_line();
    print_board_header();
    print_board_line();
    for (int row = 0; row < BOARD_LEN; row++) {
        for (int col = 0; col < BOARD_LEN; col++) {
            printf("|");
            if (row == player_row && col == player_col) {
                printf("0.0");
            } else if (board[row][col].entity == ROCK) {
                printf("^^^");
            } else if (board[row][col].entity == LANDER) {
                printf("/|\\");
            } else if (board[row][col].entity == CHEESE) {
                printf("<(]");
            } else if (board[row][col].entity == HOLE_UP) {
                printf("/O\\");
            } else if (board[row][col].entity == HOLE_DOWN) {
                printf("\\O/");
            } else if (board[row][col].entity == PORTAL) {
                printf("~~~");
            } else {
                printf("   ");
            }
        }
        printf("|\n");
        print_board_line();
    }
    print_player_stats(cheese_held, cheese_lander, oxy_capacity, oxy_level,
            oxy_rate);
    print_board_line();
    return;
}
