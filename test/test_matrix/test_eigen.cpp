#include <cstdio>
#include <utility>
#include <cassert>
#include <revector/matrix.h>


Matrix A0({
    {-1,  2,  1},
    { 2, -4,  1},
    { 1,  1, -6}
});
Matrix init_vector0(matrix_t({{1}, {1}, {1}}));
long double epsilon0 = 1e-5;
long double lambda0 = -6.42106;
Matrix x0(matrix_t({{-0.046152}, {-0.374908}, {1}}));


Matrix A1({
    { 4, -2,  7,  3, -1,  8},
    {-2,  5,  1,  1,  4,  7},
    { 7,  1,  7,  2,  3,  5},
    { 3,  1,  2,  6,  5,  1},
    {-1,  4,  3,  5,  3,  2},
    { 8,  7,  5,  1,  2,  4}
});
Matrix init_vector1({{1}, {0}, {1}, {0}, {0}, {1}});
long double epsilon1 = 1e-5;
long double lambda1 = 21.30525;
Matrix x1({{0.8724}, {0.5401}, {0.9973}, {0.5644}, {0.4972}, {1.0}});
// Matrix x16({{-0.4824}, {-0.0702}, {1}, {-0.6005}, {0.5211}, {-0.4588}});


Matrix A2({
    {  2, -1,  0,  0,  0},
    { -1,  2, -1,  0,  0},
    {  0, -1,  2, -1,  0},
    {  0,  0, -1,  2, -1},
    {  0,  0,  0, -1,  2}
});
Matrix init_vector2({{1}, {1}, {1}, {1}, {1}});
long double epsilon2 = 1e-4;
long double lambda2 = 3.7321;
Matrix x2({{0.5}, {-0.866}, {1}, {-0.866}, {0.5}});


Matrix A3({
    { 2,  1,  3,  4},
    { 1, -3,  1,  5},
    { 3,  1,  6, -2},
    { 4,  5, -2, -1}
});
Matrix init_vector3({{1}, {1}, {1}, {1}});
long double epsilon3 = 1e-2;
long double lambda3 = -8.02857835;
Matrix x3({{-0.39}, {-0.9755}, {0.2955}, {1}});



std::vector<Matrix> A_list({A0, A1, A2, A3});
std::vector<Matrix> init_vector_list({init_vector0, init_vector1, init_vector2, init_vector3});
std::vector<long double> epsilons({epsilon0, epsilon1 ,epsilon2, epsilon3});
std::vector<long double> lambdas({lambda0, lambda1, lambda2, lambda3});
std::vector<Matrix> x_list({x0, x1, x2, x3});


void test_get_dominant_eigen(){
    const int TEST_CASE_COUNT = 4;

    for (int i = 0; i < TEST_CASE_COUNT; i++){
        std::pair<long double, Matrix> eigen_pair = A_list[i].get_dominant_eigen(init_vector_list[i], epsilons[i]);
        long double eigenvalue = eigen_pair.first;
        Matrix eigenvector = eigen_pair.second;

        // std::cout << eigenvalue << std::endl;
        // std::cout << eigenvector << std::endl;

        // Matrix kA1 = A_list[i] * eigenvector;
        // Matrix kA2 = eigenvalue * eigenvector;
        // std::cout << kA1 << std::endl;
        // std::cout << kA2 << std::endl;

        // std::cout << std::endl << std::endl;

        assert((A_list[i] * eigenvector - eigenvalue * eigenvector).inf_norm() < epsilons[i]);
        assert(eigenvalue - lambdas[i] < 1e-2);
        assert((eigenvector - x_list[i]).inf_norm() < 1e-2 ||
               (eigenvector + x_list[i]).inf_norm() < 1e-2);
    }
}


void test_get_smallest_eigen(){
    const int TEST_CASE_COUNT = 4;

    for (int i = 0; i < TEST_CASE_COUNT; i++){
        std::pair<long double, Matrix> eigen_pair = A_list[i].get_smallest_eigen(init_vector_list[i], epsilons[i]);
        long double eigenvalue = eigen_pair.first;
        Matrix eigenvector = eigen_pair.second;

        // std::cout << eigenvalue << std::endl;
        // std::cout << eigenvector << std::endl;
    }
}


void test_get_closest_eigen(){
    long double center = -4;
    std::pair<long double, Matrix> eigen_pair = A_list[0].get_closest_eigen(center, init_vector_list[0], epsilons[0]);
    long double eigenvalue = eigen_pair.first;
    Matrix eigenvector = eigen_pair.second;

    // std::cout << eigenvalue << std::endl;
    // std::cout << eigenvector << std::endl;

    // std::cout << std::endl << std::endl;
}


int main(){
    test_get_dominant_eigen();
    test_get_smallest_eigen();
    test_get_closest_eigen();
    printf("test_eigen passed.\n");
    return 0;
}