#include <iostream>
#include <vector>
using namespace std;

class Matrix
{   public:
    Matrix(int r, int c, vector<vector<int>> v)
    {
        row_=r;
        col_=c;
        val_=v;
    }
    int GetNumberOfRow();
    int GetNumberOfColumn();
    void SetElement(int i, int j, int value);
    void Display();
    Matrix AddMatrices(Matrix B);
    Matrix MultiplyMatrices(Matrix B);

    private:
    int row_;
    int col_;
    vector<vector<int>> val_;
  
};

int Matrix::GetNumberOfRow()
{
    return row_;
}


int Matrix::GetNumberOfColumn()
{
    return col_;
}


void Matrix::Display()
{   cout<<endl;
    for(int i=0;i<row_;i++)
        {
            for(int j=0;j<col_;j++)
                {
                    cout<<val_[i][j]<<" ";
                }
            cout<<endl;
        }
}


void Matrix::SetElement(int i, int j, int value)
{
    val_[i-1][j-1]=value;//index 0부터 시작이라 맞춰주기
}


Matrix Matrix::AddMatrices(Matrix B)
{   Matrix ans(row_,col_,val_);
    cout<<endl;
    for(int a=0;a<row_;a++)
    {
        for(int b=0; b<col_; b++)
        {
            ans.val_[a][b]=val_[a][b]+ B.val_[a][b];
        }
    }
    return ans;
}


Matrix Matrix::MultiplyMatrices(Matrix B)
{   Matrix ans(row_,col_,val_);
    cout<<endl;
    for(int a=0;a<row_;a++)
    {
        for(int b=0; b<col_; b++)
        {
            ans.val_[a][b]=0;
            for(int c=0; c<col_;c++)
            {
                ans.val_[a][b] += val_[a][c]*B.val_[c][b];
            }
        }
    }
    return ans;
}


int main(void)
{
    vector<vector<int>> m1{{1, 2, 3},{1, 1, 4},{6, 8, 5}};
    vector<vector<int>> m2{{5, 3, 1},{2, 1, 2},{3, 6, 9}};
    Matrix matrix1(3,3,m1);
    Matrix matrix2(3,3,m2);
    matrix1.Display();
    matrix2.Display();
    matrix1.SetElement(-1,3,3);
    matrix1.Display();
    Matrix a=matrix1.AddMatrices(matrix2);
    a.Display();
    Matrix b=matrix1.MultiplyMatrices(matrix2);
    b.Display();
    return 0;
}