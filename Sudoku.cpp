#include "Sudoku.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>

using namespace std;


Sudoku::Sudoku(){
    zero_no=0;
    zero_tmp=0;
    zero_tmp2=0;
    success_put = true;
}



void Sudoku::giveQuestion(){
        ini_map();
        //changeNum(5,2);
        //changeRow(1,0);
        //changeCol(1,2);
        //rotate(3);
        //flip(1);
        for(int i=0;i<81;i++){
            cout<<setw(2)<<map[i];
            if (i==8||i==17||i==26||i==35||i==44||i==53||i==62||i==71||i==80)
                cout<<endl;
        }
    }


    void Sudoku::readIn()
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                //cin>>get_map[i*9+j];
                cin>>map[i*9+j];
            }
        }

    }

    int Sudoku::solve()
    {
        if(no_ans(map)==1)
        {
            cout<<"0"<<endl;
            return 0;
        }
        if(mul_ans(map)==1)
        {
            cout<<"2"<<endl;
            return 0;
        }

        success_put = true;
        while(success_put)
        {
            zero_count();
            success_put = false;

            for(int i=0;i<zero_no;i++)
            {
                solve_easy();
            }
        }

        zero_count();

        if(zero_no==0)
        {
            cout<<endl;
            cout<<"1"<<endl;
            print_out();
            return 0;
        }

        //end of solve easy
        //print_out();

        //see its row col and 3*3
        success_put = true;
        while(success_put)
        {
            zero_count();
            success_put = false;

            for(int i=0;i<zero_no;i++)
            {
                solve_mid();
            }
        }
        zero_no=0;
        zero_count();
        if(zero_no==0)
        {
            cout<<"\n1"<<endl;
            //print out
            print_out();
            return 0;
        }

        //end of mid solve

        //start hard solve
        /*
        success_put = true;
        while(success_put)
        {
            zero_count();
            success_put = false;

            for(int i=0;i<zero_no;i++)
            {
                solve_hard();
            }
        }
        zero_no=0;
        zero_count();
        if(zero_no==0)
        {
            cout<<"\n1"<<endl;
            //print out
            print_out();
            return 0;
        }




*/
        //end of hard solve
        clone_map();
        zero_count_tmp();
        zero_count_tmp2();
        //zero_count();
        //zero_tmp=zero_no;
        //zero_tmp2=zero_no;

        if(backtrack_back()&&backtrack_front())
        {
            if(only())
            {
                cout<<"1"<<endl;
                print_out_tmp();
            }
            else
            {
                cout<<"2";
            }
        }
        else
        {
            cout<<"0";
        }

        //cout<<"2";



    }//end of solve


    void Sudoku::changeNum(int a, int b){
        if(a<=0||a>9||b<=0||b>9)
        {
            cout<<"changeNumshould only input numbers between 1~9"<<endl;
            return;
        }
        if(a!=b)
        {
            for(int i=0;i<81;i++){
                if(map[i]==a)
                    map[i] = -1;
            }
            for(int j=0;j<81;j++){
                if(map[j]==b)
                    map[j] = a;
            }
            for(int k=0;k<81;k++){
                if(map[k]== -1)
                    map[k] = b;
            }
        }
        else
        {
            //do nothing
        }
    }//end of num switch

    void Sudoku::changeRow(int a, int b){//---
        int tmp[81]={0};
        int c=0;

        if(a!=b && a>=0 && a<=2 && b>=0 && b<=2)
        {
            if((a==0&&b==1)||(a==1&&b==0))
            {
                c=1;
            }
            else if((a==0&&b==2)||(a==2&&b==0))
                {
                    c=2;
                }
                else//1&2
                {
                    c=3;
                }
            //=======
            switch(c)
            {
                case 1://0,1
                    for(int i=0;i<27;i++)
                        tmp[i+27]=map[i];
                    for(int i=27;i<54;i++)
                        tmp[i-27]=map[i];
                    for(int i=54;i<81;i++)
                        tmp[i]=map[i];
                    break;

                case 2://0,2
                    for(int i=0;i<27;i++)
                        tmp[i+54]=map[i];
                    for(int i=27;i<54;i++)
                        tmp[i]=map[i];
                    for(int i=54;i<81;i++)
                        tmp[i-54]=map[i];
                    break;

                case 3://1,2
                    for(int i=0;i<27;i++)
                        tmp[i]=map[i];
                    for(int i=27;i<54;i++)
                        tmp[i+27]=map[i];
                    for(int i=54;i<81;i++)
                        tmp[i-27]=map[i];
                    break;

                default:
                    cout<<"error change row!"<<endl;
            }//end of switch

        }
        else if(a==b && a>=0 && a<=2 && b>=0 && b<=2)
            {
                //do nothing
                return;
            }
            else
            {
                cout<<"changeRow: should only input 0<=a,b<=2"<<endl;
                return;
            }
        //=========
        for(int i=0;i<81;i++)
            map[i]=tmp[i];


    }//end of change row

    void Sudoku::changeCol(int a, int b){//|||
        int tmp[81]={0};
        int c=0;

        if(a!=b && a>=0 && a<=2 && b>=0 && b<=2)
        {
            if((a==0&&b==1)||(a==1&&b==0))
            {
                c=1;
            }
            else if((a==0&&b==2)||(a==2&&b==0))
                {
                    c=2;
                }
                else//1&2
                {
                    c=3;
                }
            //=======
            switch(c)
            {
                case 1://0,1
                    for(int j=0;j<3;j++)//0
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j+3]=map[i*9+j];
                        }
                    }

                    for(int j=3;j<6;j++)//1
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j-3]=map[i*9+j];
                        }
                    }

                    for(int j=6;j<9;j++)//2
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j]=map[i*9+j];
                        }
                    }
                    break;

                case 2://0,2
                    for(int j=0;j<3;j++)//0
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j+6]=map[i*9+j];
                        }
                    }

                    for(int j=3;j<6;j++)//1
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j]=map[i*9+j];
                        }
                    }

                    for(int j=6;j<9;j++)//2
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j-6]=map[i*9+j];
                        }
                    }
                    break;

                case 3://1,2
                    for(int j=0;j<3;j++)//0
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j]=map[i*9+j];
                        }
                    }

                    for(int j=3;j<6;j++)//1
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j+3]=map[i*9+j];
                        }
                    }

                    for(int j=6;j<9;j++)//2
                    {
                        for(int i=0;i<9;i++)
                        {
                            tmp[i*9+j-3]=map[i*9+j];
                        }
                    }
                    break;

                default:
                    cout<<"error change col!"<<endl;
            }//end of switch

        }
        else if(a==b && a>=0 && a<=2 && b>=0 && b<=2)
            {
                //do nothing
                return;
            }
            else
            {
                cout<<"changeCol: should only input 0<=a,b<=2"<<endl;
                return;
            }
        //=========
        for(int i=0;i<81;i++)
            map[i]=tmp[i];


    }//end of change col

    void Sudoku::rotate(int n){//題目轉向
        if(n<0||n>100)
        {
            cout<<"rotate: should only input integers between 0~100"<<endl;
            return;
        }

        int temp[81]={0};
        n=n%4;

        switch(n)
        {
            case 0://do nothing
                return;
                break;
            case 1://rotate clockwise for 1 time
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        temp[j*9+(8-i)]=map[i*9+j];
                    }
                }
                break;
            case 2://rotate clockwise for 2 times
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        temp[(8-i)*9+(8-j)]=map[i*9+j];
                    }
                }
                break;
            case 3://rotate clockwise for 3 times
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        temp[i+(8-j)*9]=map[i*9+j];
                    }
                }
                break;
            default:
                return;
        }
        for(int i=0;i<81;i++)
        {
            map[i]=temp[i];
        }

    }

    void Sudoku::flip(int n){
        int temp[81]={0};
        switch(n)
        {
            case 0:
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        temp[(8-i)*9+j]=map[i*9+j];
                    }
                }
                break;
            case 1:
                for(int i=0;i<9;i++)
                {
                    for(int j=0;j<9;j++)
                    {
                        temp[i*9+(8-j)]=map[i*9+j];
                    }
                }
                break;
            default:
                cout<<"should only input 0 or 1!"<<endl;
                return;
        }//end of switch
        for(int i=0;i<81;i++)
        {
            map[i]=temp[i];
        }
    }//end of flip

    void Sudoku::transform(){//not yet finish get_map not yet tested
        //readIn();
        srand(time(NULL));
        changeNum(rand()%9+1,rand()%9+1);
        changeRow(rand()%3,rand()%3);
        changeCol(rand()%3,rand()%3);
        rotate(rand()%101);
        flip(rand()%2);
        for(int i=0;i<81;i++){
            cout<<setw(2)<<map[i];
            if (i==8||i==17||i==26||i==35||i==44||i==53||i==62||i==71||i==80)
                cout<<endl;
        }
        cout<<"\n";
    }


    int Sudoku::ini_map(){
        int initial[81]= {5,3,0,0,7,0,0,0,0,6,0,0,1,9,5,0,0,0,0,9,8,0,0,0,0,6,0,8,0,0,0,6,0,0,0,3,4,0,0,8,0,3,0,0,1,7,0,0,0,2,0,0,0,6,0,6,0,0,0,0,2,8,0,0,0,0,4,1,9,0,0,5,0,0,0,0,8,0,0,7,9};
        for(int i=0;i<81;i++)
        {
            map[i]=initial[i];
        }


    }


    void Sudoku::print_out()
    {
        for(int i=0;i<81;i++){
            //cout<<setw(2)<<map[i];
            cout<<map[i]<<" ";
            if (i==8||i==17||i==26||i==35||i==44||i==53||i==62||i==71||i==80)
                cout<<endl;
        }
        cout<<"\n\n"<<endl;
    }

    void Sudoku::print_out_tmp()
    {
        for(int i=0;i<81;i++){
            //cout<<setw(2)<<map[i];
            cout<<tmp[i]<<" ";
            if (i==8||i==17||i==26||i==35||i==44||i==53||i==62||i==71||i==80)
                cout<<endl;
        }
        cout<<"\n\n"<<endl;
    }

    int Sudoku::find_zero(){

        for(int i=where+1;i<81;i++)
        {
            if(map[i]==0)
            {
                where = i;
                return i;
            }
        }
    }

    int Sudoku::zero_count()
    {
        zero_no=0;
        where = -1;
        for(int i=0;i<81;i++)
        {
            if(map[i]==0)
            {
                zero_no++;
            }
        }
    }

    int Sudoku::zero_count_tmp()
    {
        zero_tmp=0;
        //where = -1;
        for(int i=0;i<81;i++)
        {
            if(tmp[i]==0)
            {
                zero_tmp++;
            }
        }
    }

    int Sudoku::zero_count_tmp2()
    {
        zero_tmp2=0;
        //where = -1;
        for(int i=0;i<81;i++)
        {
            if(tmp2[i]==0)
            {
                zero_tmp2++;
            }
        }
    }

    bool Sudoku::check_bad(int wh,int num)//return true if bad
    {
        int wline = wh/9;
        int wcolumn = wh%9;
        int fakeplace = (wline/3)*3*9 +wcolumn/3*3;//the left-up of the 3*3 of where is in

        //橫
        for(int i=0;i<9;i++)
        {
            if(map[wline*9+i]==num)
            {
                return true;
            }
        }
        //直行
        for(int j=0;j<9;j++)
        {
            if(map[j*9+wcolumn]==num)
            {
                return true;
            }
        }
        //方框
        if(map[fakeplace]==num||map[fakeplace+1]==num||map[fakeplace+2]==num||map[fakeplace+9]==num||map[fakeplace+10]==num||map[fakeplace+11]==num||map[fakeplace+18]==num||map[fakeplace+19]==num||map[fakeplace+20]==num)
        {
            return true;
        }


        return false;
    }

    bool Sudoku::check_good_tmp(int wh,int num)//return true if good
    {
        int wline = wh/9;
        int wcolumn = wh%9;
        int fakeplace = (wline/3)*3*9 +wcolumn/3*3;//the left-up of the 3*3 of where is in

        //橫
        for(int i=0;i<9;i++)
        {
            if(tmp[wline*9+i]==num)
            {
                return false;
            }
        }
        //直行
        for(int j=0;j<9;j++)
        {
            if(tmp[j*9+wcolumn]==num)
            {
                return false;
            }
        }
        //方框
        if(tmp[fakeplace]==num||tmp[fakeplace+1]==num||tmp[fakeplace+2]==num||tmp[fakeplace+9]==num||tmp[fakeplace+10]==num||tmp[fakeplace+11]==num||tmp[fakeplace+18]==num||tmp[fakeplace+19]==num||tmp[fakeplace+20]==num)
        {
            return false;
        }


        return true;
    }

    bool Sudoku::check_good_tmp2(int wh,int num)//return true if good
    {
        int wline = wh/9;
        int wcolumn = wh%9;
        int fakeplace = (wline/3)*3*9 +wcolumn/3*3;//the left-up of the 3*3 of where is in

        //橫
        for(int i=0;i<9;i++)
        {
            if(tmp2[wline*9+i]==num)
            {
                return false;
            }
        }
        //直行
        for(int j=0;j<9;j++)
        {
            if(tmp2[j*9+wcolumn]==num)
            {
                return false;
            }
        }
        //方框
        if(tmp2[fakeplace]==num||tmp2[fakeplace+1]==num||tmp2[fakeplace+2]==num||tmp2[fakeplace+9]==num||tmp2[fakeplace+10]==num||tmp2[fakeplace+11]==num||tmp2[fakeplace+18]==num||tmp2[fakeplace+19]==num||tmp2[fakeplace+20]==num)
        {
            return false;
        }


        return true;
    }


    int Sudoku::solve_easy(){

        find_zero();
        int ok=0;
        int list_ok[10] = {0};
        int put=0;
        for(int i=1;i<10;i++)
        {
            if(check_bad(where,i))
            {
                //nothing
                //cout<<where<<" check bad "<<i<<"\t";
                //system("PAUSE");

            }
            else//maybe good
            {
                ok++;
                list_ok[i]++;
                //list_ok[i]=1;
            }
        }
        if(ok==1)
        {
            for(int a=1;a<10;a++)
            {
                if(list_ok[a]==1)
                {
                    put=a;
                }

            }
            map[where]=put;
            /*for(int a=1;a<10;a++)
            {
                cout<<list_ok[a]<<" ";
            }

            cout<<"\n"<<where<<":"<<put<<endl;
            */
            success_put=true;
        }
        /*else if(ok==0)//?????????
            {
                return 0;//error no ans
            }
        */
    }

    int Sudoku::solve_mid(){
        int list_exist[10]={0};
        find_zero();
        int wline = where/9;
        int wcolumn = where%9;
        int fakeplace = (wline/3)*3*9 +wcolumn/3*3;//the left-up of the 3*3 of where is in

        for(int i=0;i<9;i++)//row line into list
        {
            switch(map[wline*9+i])
            {
                case 1:
                    list_exist[1]++;
                    break;
                case 2:
                    list_exist[2]++;
                    break;
                case 3:
                    list_exist[3]++;
                    break;
                case 4:
                    list_exist[4]++;
                    break;
                case 5:
                    list_exist[5]++;
                    break;
                case 6:
                    list_exist[6]++;
                    break;
                case 7:
                    list_exist[7]++;
                    break;
                case 8:
                    list_exist[8]++;
                    break;
                case 9:
                    list_exist[9]++;
                    break;

            }//end of switch
        }

        for(int i=0;i<9;i++)//col into list
        {
            switch(map[i*9+wcolumn])
            {
                case 1:
                    list_exist[1]++;
                    break;
                case 2:
                    list_exist[2]++;
                    break;
                case 3:
                    list_exist[3]++;
                    break;
                case 4:
                    list_exist[4]++;
                    break;
                case 5:
                    list_exist[5]++;
                    break;
                case 6:
                    list_exist[6]++;
                    break;
                case 7:
                    list_exist[7]++;
                    break;
                case 8:
                    list_exist[8]++;
                    break;
                case 9:
                    list_exist[9]++;
                    break;
            }//end of switch
        }

        for(int i=0;i<3;i++)//3*3 into list
        {
            for(int j=0;j++;j<3)
                switch(map[fakeplace+i*9+j])
                {
                    case 1:
                        list_exist[1]++;
                        break;
                    case 2:
                        list_exist[2]++;
                        break;
                    case 3:
                        list_exist[3]++;
                        break;
                    case 4:
                        list_exist[4]++;
                        break;
                    case 5:
                        list_exist[5]++;
                        break;
                    case 6:
                        list_exist[6]++;
                        break;
                    case 7:
                        list_exist[7]++;
                        break;
                    case 8:
                        list_exist[8]++;
                        break;
                    case 9:
                        list_exist[9]++;
                        break;

            }//end of switch
        }

        int put=0;
        int no_yet=0;
        for(int i=1;i<10;i++)
        {
            if(list_exist[i]==0)
            {
                no_yet++;
            }
        }

        if(no_yet==1)//success
        {
            for(int i=1;i<10;i++)
            {
                if(list_exist[i]==0)
                {
                    put=i;
                }
                break;
            }
            map[where]=put;
            success_put = true;
        }
        else if(no_yet==0&&success_put==true)
            {
                cout<<"0";
                success_put=false;
                return 0;
            }

    }

    int Sudoku::solve_hard(){
        find_zero();
        bool suc=false;
        int zrow[9]={0};//put 1~9
        int zarr[3]={0};

        int wline = where/9;
        int wll=where/27;//compare with zarr
        int wcolumn = where%9;
        int wcc=wcolumn/3;
        int fakeplace = (wline/3)*3*9 +wcolumn/3*3;//the left-up of the 3*3 of where is in
        int f1=fakeplace%27;
        int f2=fakeplace-(fakeplace%9);

        int put=0;
        //宮對行區塊摒除
        //find all 0 of col into arr
        for(int i=0;i<9;i++)
        {
            if(map[i*9+wcolumn]==0)
            {
                zrow[i]++;
            }
        }
        //zero arr
        for(int i=0;i<9;i++)
        {
            if(zrow[i]==1)
            {
                zarr[i/3]++;
            }
        }
        //zarr[wll]=0;
        //try
        for(int i=1;i<10;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(zarr[j]!=0&&j!=wll)
                {
                    if(map[j*27+f1]==i||map[j*27+f1+1]==i||map[j*27+f1+2]==i||map[j*27+f1+9]==i||map[j*27+f1+10]==i||map[j*27+f1+11]==i||map[j*27+f1+18]==i||map[j*27+f1+19]==i||map[j*27+f1+20]==i)
                    {
                        zarr[j]=0;
                    }
                }
            }

            for(int k=0;k<3;k++)
            {
                if(zarr[k]==0&&zarr[wll]==1)
                {
                    suc=true;
                    put=i;
                }
                else
                {
                    suc=false;
                }
            }
        }

        if (suc)
        {
            map[where]=put;
            return 0;
        }

        //end宮對行區塊摒除
        //宮對列區塊摒除
        put=0;
        suc=false;
        zrow[9]={0};//put 1~9
        zarr[3]={0};
        for(int i=0;i<9;i++)
        {
            if(map[wline*9+i]==0)
            {
                zrow[i]++;
            }
        }
        //zero arr
        for(int i=0;i<9;i++)
        {
            if(zrow[i]==1)
            {
                zarr[i/3]++;
            }
        }
        //zarr[wll]=0;
        //try
        for(int i=1;i<10;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(zarr[j]!=0&&j!=wll)
                {
                    if(map[j*9+f2]==i||map[j*9+f2+1]==i||map[j*9+f2+2]==i||map[j*9+f2+9]==i||map[j*9+f2+10]==i||map[j*9+f2+11]==i||map[j*9+f2+18]==i||map[j*9+f2+19]==i||map[j*9+f2+20]==i)
                    {
                        zarr[j]=0;
                    }
                }
            }

            for(int k=0;k<3;k++)
            {
                if(zarr[k]==0&&zarr[wll]==1)
                {
                    suc=true;
                    put=i;
                }
                else
                {
                    suc=false;

                }
            }
        }

        if (suc)
        {
            map[where]=put;
            return 0;
        }
        //end of 宮對列區塊摒除

    }

    bool Sudoku::backtrack_front()
    {
        if (zero_tmp==0) {
            return true;
        }
        for (int i = 0; i<81;i++) {
            if (tmp[i]==0)
            {
                for(int n=1;n<10;n++)
                {
                    if(check_good_tmp(i,n))
                    {
                        tmp[i]=n;
                        zero_tmp--;
                        if(backtrack_front())
                            return true;
                        tmp[i]=0;
                        zero_tmp++;
                    }
                }
                return false;
            }
        }
    }

    bool Sudoku::backtrack_back()
    {
        //zero_count_tmp();
        if (zero_tmp2==0) {
            return true;
        }
        for (int i = 0; i<81;i++) {
            if (tmp2[i]==0)
            {
                for(int n=9;n>0;n--)
                {
                    if(check_good_tmp2(i,n))
                    {
                        tmp2[i]=n;
                        zero_tmp2--;
                        if(backtrack_back())
                            return true;
                        tmp2[i]=0;
                        zero_tmp2++;
                    }
                }
                return false;
            }
        }
    }

    //還沒考慮還沒開始解之前看不出來的無解
    int Sudoku::no_ans(int get[81]){ //if no ans then return 1,else return 0

        int row[10]={0};//存1~9的counter

        //看同橫排有沒同數字
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                switch(get[j*9+k]){
                    case 1:
                        row[1]++;
                        break;
                    case 2:
                        row[2]++;
                        break;
                    case 3:
                        row[3]++;
                        break;
                    case 4:
                        row[4]++;
                        break;
                    case 5:
                        row[5]++;
                        break;
                    case 6:
                        row[6]++;
                        break;
                    case 7:
                        row[7]++;
                        break;
                    case 8:
                        row[8]++;
                        break;
                    case 9:
                        row[9]++;
                        break;
                    default:
                        break;
                }//end switch
            }//end of for loop for row

            for(int m=1;m<10;m++)
            {
                if (row[m] >1)
                {
                    return 1;
                }
            }
            for(int l=0;l<10;l++)//empty row
            {
                row[l]=0;
            }

        }
        //============================
        //看直
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                switch(get[j+k*9]){
                    case 1:
                        row[1]++;
                        break;
                    case 2:
                        row[2]++;
                        break;
                    case 3:
                        row[3]++;
                        break;
                    case 4:
                        row[4]++;
                        break;
                    case 5:
                        row[5]++;
                        break;
                    case 6:
                        row[6]++;
                        break;
                    case 7:
                        row[7]++;
                        break;
                    case 8:
                        row[8]++;
                        break;
                    case 9:
                        row[9]++;
                        break;
                    default:
                        break;
                }//end switch
            }//end of for loop for col
            for(int m=1;m<10;m++)
            {
                if (row[m] >1)
                {
                    return 1;
                }
            }

            for(int l=0;l<10;l++)
            {
                row[l]=0;
            }

        }
        //========================
        //看方格

        for(int i=0;i<9;i+=3)
        {
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)
                {
                    for(int l=0;l<3;l++)
                    {
                        switch(get[i+j*27+k*9+l]){
                            case 1:
                                row[1]++;
                                break;
                            case 2:
                                row[2]++;
                                break;
                            case 3:
                                row[3]++;
                                break;
                            case 4:
                                row[4]++;
                                break;
                            case 5:
                                row[5]++;
                                break;
                            case 6:
                                row[6]++;
                                break;
                            case 7:
                                row[7]++;
                                break;
                            case 8:
                                row[8]++;
                                break;
                            case 9:
                                row[9]++;
                                break;
                            default:
                                break;
                        }//end switch
                    }
                }

                for(int m=1;m<10;m++)
                {
                    if (row[m] >1)
                    {
                        return 1;
                    }
                }

                //歸零
                for(int l=0;l<10;l++)
                {
                    row[l]=0;
                }

            }
        }

        return 0;
        //============================
    }//end of 無解

    int Sudoku::mul_ans(int get[81])
    {
        //若為唯一解 提示數不能少於17個
        int no_count=0;
        for(int i=0;i<144;i++)
        {
            if(map[i]==1||map[i]==2||map[i]==3||map[i]==4||map[i]==5||map[i]==6||map[i]==7||map[i]==8||map[i]==9)
            {
                no_count++;
            }
        }
        if (no_count<17)
        {
            return 1;
        }
        //=============
        //缺少2種提示数
        int count[10]={0};//存1~9的counter
        int coco=0;
        for(int x=0;x<144;x++)
        {
            switch(map[x]){
                case 1:
                    count[1]++;
                    break;
                case 2:
                    count[2]++;
                    break;
                case 3:
                    count[3]++;
                    break;
                case 4:
                    count[4]++;
                    break;
                case 5:
                    count[5]++;
                    break;
                case 6:
                    count[6]++;
                    break;
                case 7:
                    count[7]++;
                    break;
                case 8:
                    count[8]++;
                    break;
                case 9:
                    count[9]++;
                    break;
                default:
                    break;
            }//end switch
        }
        for(int y=1;y<10;y++)
        {
            if(count[y]=0)
            {
                coco++;
            }
        }
        if(coco>1)
        {
            return 1;
        }
        //========================
        //是否存在同一行大区块中是否两行都无提示数
        int cc=0;

        for(int i=0;i<4;i++)
        {
            int ccc=0;
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<12;k++)
                {
                    if(map[i*36+j*12+k]==0)
                    {
                        cc++;
                    }
                }
                if(cc==18)
                {
                    ccc++;
                }
                cc=0;
            }
            if(ccc>1)
            {
                return 1;
            }
        }
        //=================================
        //同一列大区块中是否两列都无提示数
        cc=0;

        for(int i=0;i<4;i++)
        {
            int ccc=0;
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<12;k++)
                {
                    if(map[i*3+j+k*12]==0)
                    {
                        cc++;
                    }
                }
                if(cc==18)
                {
                    ccc++;
                }
                cc=0;
            }
            if(ccc>1)
            {
                return 1;
            }
        }

        //=================================
    }//end 多解


    void Sudoku::clone_map()
    {
        for(int i=0;i<81;i++){
            tmp[i]=map[i];
            tmp2[i]=map[i];
        }
    }

    bool Sudoku::only()
    {
        for(int i =0;i<81;i++)
        {
            if(tmp[i]!=tmp2[i])
            {
                return false;
            }
        }
        return true;
    }
