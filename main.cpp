#include "MyMatrix.hpp"
int main ()
{ /*
   std::cout << "номер 2\n";
   // 1)
   Matrix              a1 ({
       { 11, -9 },
       { -9, 11 }
   });
   std::vector<double> f1 = { 3, -1 };
   std::cout << myu (a1, 1) << std::endl;
   std::cout << myu (a1, 2) << std::endl;
   // std::cout << myu (a1, 3) << std::endl;
   //    2)
   print_SLE_Jacobi (a1, f1);
   print_SLE_Seidel (a1, f1);
   // здесь начал выскакивать сегфолт
   // double t_opt = opt_relax_param (a1);
   // std::cout << "Оптимальный параметр релаксации " << t_opt << std::endl;

   std::cout << "номер 3\n";
   // 1)
   Matrix              a2 ({
       { -1, 1 },
       {  4, 3 }
   });
   std::vector<double> f2 = { 2, -1 };
   print_normalized_SLE (a2, f2);

   auto at = transpose (a2) * a2;
   // std::cout << opt_relax_param (at);
   std::cout << "номер 4\n";
   Matrix              a3 ({
       {  2, -1 },
       { -2,  3 },
       { -2,  1 }
   });
   std::vector<double> f3 = { 1, 2, 0 };
   std::vector<double> x1 = { -2, -2 / 3., -2 };
   std::vector<double> y1 = { -1, 2 / 3., 0 };
   print_normalized_SLE (a3, f3);
   std::cout << "x,y: " << solve_overdetermined_SLE (a3, f3) << std::endl;
   std::cout << "Номер 5\n";
   std::vector<double> x = { 0, 1, 2, 3, 7, 9 };
   std::vector<double> y = { 1, 2, 3, 1, 2, 9 };
   std::cout << "k,b : " << LSM (x, y);

 */

  MyMatrix::Matrix m ({
      {   1,  2,  3 },
      { -15, 22,  1 },
      {   1,  2,  4 },
      {   6,  7, 19 }
  });
  std::cout << m;

  Matrix a3 ({
      {  2, -1 },
      { -2,  3 },
      { -2,  1 }
  });

  std::vector<double> f3 = { 1, 2, 0 };
  // std::cout << solve_overdetermined_SLE_with_weightMatrix (
  //     a3, f3, weightMatrix (a3.getRowLen ()));
  // std::cout << solve_overdetermined_SLE (a3, f3);

  Matrix              a1 ({
      { 11, -9 },
      { -9, 11 }
  });
  std::vector<double> f1 = { 3, -1 };

  print_SLE_Jacobi (a1, f1);

  return 0;
}
