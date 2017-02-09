#include <QCoreApplication>
#include <iostream>
#include <Eigen/Cholesky>
#include <Eigen/SparseCore>
#include <Eigen/Sparse>
#include <Eigen/SparseCore>
#include <Eigen/SparseCholesky>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Cholesky>

const int PIXELNUM = 20;

using namespace std;

typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::SparseVector<double> SpVec;
typedef Eigen::Triplet<double> T;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SpMat DMatrix(PIXELNUM-2,PIXELNUM);
    for (int i=0; i<PIXELNUM-2; i++) {
        for (int j=i; j<i+3 && j<PIXELNUM; j++) {
            if (j==i+1) {
                DMatrix.insert(i,j) = -2;
            }
            else if (j==i+2) {
                DMatrix.insert(i,j) = 1;
            }
            else if (j==i) {
                DMatrix.insert(i,j) = 1;
            }
        }
    }
    std::cout << "Dmatrix=" << std::endl << DMatrix << std::endl;

    double lambda = 1300;
    SpMat HMatrix = lambda*(DMatrix.transpose())*DMatrix;

    SpMat EyeMat(PIXELNUM,PIXELNUM);
    EyeMat.setIdentity();

    Eigen::SimplicialLLT <SpMat> lltOfHMatrix(HMatrix+EyeMat);

    std::cout << "HMatrix+EyeMat=" << std::endl << HMatrix+EyeMat << std::endl;

    SpMat UMatrix = lltOfHMatrix.matrixU();
    std::cout << "UMatrix=" << std::endl << UMatrix << std::endl;
    SpMat RMatrix = (UMatrix.transpose())*UMatrix;
    std::cout << "recover:" << std::endl << RMatrix;

    return a.exec();
}
