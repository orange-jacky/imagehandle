#include <iostream>
#include <vector>
#include <Eigen/Eigen>

using namespace Eigen;
using namespace std;

int main()
{
    Eigen::Vector2d v1, v2;     //Eigen中的变量
    v1 << 5, 6;   //默认的向量为列向量
    cout  << "v1 = " << endl << v1 << endl;
    v2 << 4, 5 ;
    Matrix2d result = v1*v2.transpose();
    cout << "result: " << endl << result << endl;

    Matrix3d m = Matrix3d::Random();
	cout << m << endl;
	cout << m.inverse() << endl;
}