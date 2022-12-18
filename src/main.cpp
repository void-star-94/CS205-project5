#include <iostream>
#define SHOW_CONSTRUCT
#include "Wrapper.h"

#define tester(name, func) void test_##name(){ \
    std::cout<<"------------------------\n";    \
    std::cout<<"testing "<< #name <<"\n\n";      \
    func();                                    \
    std::cout<<"\n\n"<< #name <<" test finished\n";      \
    std::cout<<"------------------------\n";    \
}


void test1() {
    auto ptr = new float[8]{1, 2, 3, 4, 5, 6, 7};
    Matrix<float> a, b(2), c(2, 3), d(2, 3, 4), e(2, 4, ptr);
    std::cout << a << "\n" << b << "\n" << c << "\n" << d << "\n" << e;
}

void test2() {
    auto ptr = new double[8]{1, 2, 3, 4, 5, 6, 7};
    Matrix<double> a(4, 2, ptr);
    auto func = [&](Index i, Index j) {
        std::cout << "showing element at (" << i << ", " << j << "): " << a[i, j] << "\n";
    };

    std::cout << "showing the whole matrix:\n" << a;

    func(1, 0);
    func(3, 1);
    func(2, 0);
    func(0, 1);
}

void test3() {
    auto ptr = new int[30];
    for (int i = 0; i < 30; ++i) ptr[i] = i;
    Matrix<int> a(5, 6, ptr);
    std::cout << "showing the whole matrix:\n" << a << "\n";
    std::cout << "showing the block of matrix from point (1, 2) to point (2,4):\n";
    std::cout << a.block(1, 2, 2, 3) << "\n";
    std::cout << "showing the second column of the whole matrix:\n";
    std::cout << a.col(1);
    std::cout << "showing the second row of the previous block:\n";
    std::cout << a.block(1, 2, 2, 3).row(1);
}

void test4() {
    auto ptr1 = new int[30], ptr2 = new int[30];
    for (int i = 0; i < 30; ++i) {
        ptr1[i] = i;
        ptr2[i] = i + 10;
    }
    Matrix<int> a(5, 6, ptr1), b(6, 5, ptr2);
    Matrix<int> c = a, d;
    d = b;
    std::cout << "showing matrix c whose data is copied from a: \n" << c;
    std::cout << "showing matrix d whose data is copied from a using =: \n" << d;
}

void test5() {
    auto ptr = new float[12];
    for (int i = 0; i < 12; ++i) ptr[i] = (float) i + (float) i / 10.f;
    Matrix<float> b(4, 3, ptr);
    std::cout << "showing matrix b: \n" << b;
    std::cout << "reshape b from dimension (4, 3) to (3, 4):\n" << b.reshape(3, 4);
    std::cout << "testing sin function on b:\n" << sin(b);
    std::cout << "testing exp function on b:\n" << exp(b);
    std::cout << "testing log function on b:\n" << log(b);
    std::cout << "testing sqrt function on b:\n" << sqrt(b);
    std::cout << "testing ceil function on b:\n" << ceil(b);
}

void test6() {
    auto ptr = new float[12];
    for (int i = 0; i < 12; ++i) ptr[i] = (float) i + (float) i / 10.f;
    Matrix<float> b(4, 3, ptr);
    std::cout << "showing matrix b: \n" << b;
    std::cout << "testing b + 3:\n" << b + 3;
    std::cout << "testing 4 + b:\n" << 4ul + b;
    std::cout << "testing b - 5:\n" << b - 0x5;
    std::cout << "testing 6 - b:\n" << 6.0 - b;
    std::cout << "testing b * 2:\n" << b * 2;
    std::cout << "testing 3 * b:\n" << 3l * b;
    std::cout << "testing b / 2:\n" << b / 02;
    std::cout << "testing 100 / b element-wise:\n" << divide_EWise(100, b);
}

void test7() {
    auto ptr1 = new float[12], ptr2 = new float[12];
    for (int i = 0; i < 12; ++i) {
        ptr1[i] = (float) i;
        ptr2[i] = (float) i + (float) (i - 6) / 10.f;
    }
    Matrix<float> a(3, 4, ptr1), b(3, 4, ptr2);
    std::cout << "showing matrix a: \n" << a;
    std::cout << "showing matrix b: \n" << b;
    std::cout << "testing a + b:\n" << a + b;
    std::cout << "testing a - b:\n" << a - b;
    std::cout << "testing b - a:\n" << b - a;
    std::cout << "testing a * b element-wise:\n" << multiply_EWise(a, b);
    std::cout << "testing a / b element-wise:\n" << divide_EWise(a, b);
    std::cout << "testing max(a, b):\n" << max(a, b);
    std::cout << "testing a * b.reshape(4, 3):\n" << a * b.reshape(4, 3);
}

void test8() {
    auto ptr1 = new float[16], ptr2 = new float[16];
    for (int i = 0; i < 16; ++i) {
        ptr1[i] = (float) i;
        ptr2[i] = (float) i + (float) (i - 8) / 10.f;
    }
    Matrix<float> a(4, 4, ptr1), b(4, 4, ptr2);
    std::cout << "testing complex expression:\n";
    std::cout << divide_EWise(min(sin(max(a * 3 + b * 5 + 9, b + 6 - 5 * a)) / 5, a * b * 7), multiply_EWise(a, b));
}

tester(construct, test1)

tester(data_access, test2)

tester(block, test3)

tester(copy_and_assign, test4)

tester(unary_functions, test5)

tester(scalar_arithmetic, test6)

tester(binary_functions, test7)

tester(lazy_evaluation, test8)

int main() {
    test_construct();
    test_data_access();
    test_block();
    test_copy_and_assign();
    test_unary_functions();
    test_scalar_arithmetic();
    test_binary_functions();
    test_lazy_evaluation();
    return 0;
}
