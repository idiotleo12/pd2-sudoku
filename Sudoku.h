#include <iostream>
class Sudoku{
public:
    Sudoku();
    void giveQuestion();
    void readIn();
    int solve();
    void changeNum(int a, int b);
    void changeRow(int a, int b);
    void changeCol(int a, int b);
    void rotate(int n);
    void flip(int n);
    void transform();

private:
    int map[81];
    int where;
    bool success_put;
    int zero_no;
public:
    int ini_map();
//private:
    void print_out();
private:
    int find_zero();
    int zero_count();
    bool check_bad(int wh,int num);
    int solve_easy();
    int solve_mid();
    int solve_hard();
    int no_ans(int get[81]);
    int mul_ans(int get[81]);
};//end of class
