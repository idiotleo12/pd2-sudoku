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
    int tmp[81];
    int tmp2[81];
    int where;
    bool success_put;
    int zero_no;
    int zero_tmp;
    int zero_tmp2;
public:
    int ini_map();
//private:
    void print_out();
    void print_out_tmp();
private:
    int find_zero();
    int zero_count();
    int zero_count_tmp();
    int zero_count_tmp2();
    bool check_bad(int wh,int num);
    bool check_good_tmp(int wh,int num);
    bool check_good_tmp2(int wh,int num);
    int solve_easy();
    int solve_mid();
    int solve_hard();
    int no_ans(int get[81]);
    int mul_ans(int get[81]);
    void clone_map();
    bool backtrack_front();
    bool backtrack_back();
    bool only();
};//end of class
