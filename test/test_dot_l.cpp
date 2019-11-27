#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "helpers.hpp"

#include <Eigen/Dense>
#include <celerite2/core.hpp>

TEMPLATE_LIST_TEST_CASE("check the results of dot_l", "[dot_l]", TestKernels) {
  auto kernel = TestType::get_kernel();

  Vector x, diag;
  Matrix Y;
  std::tie(x, diag, Y) = get_data();
  const int N          = x.rows();

  typename decltype(kernel)::Vector a;
  typename decltype(kernel)::LowRank U, V, P;
  std::tie(a, U, V, P) = kernel.get_celerite_matrices(x, diag);

  Matrix K, S;
  celerite::core::to_dense(a, U, V, P, K);

  // Do the Cholesky using celerite
  int flag = celerite::core::factor(U, P, a, V, S);
  REQUIRE(flag == 0);

  // Reconstruct the L matrix
  Matrix UWT;
  celerite::core::to_dense(Eigen::VectorXd::Ones(N), U, V, P, UWT);
  UWT.triangularView<Eigen::StrictlyUpper>().setConstant(0.0);

  // Brute force the Cholesky factorization
  Eigen::LLT<Eigen::MatrixXd> LLT(K);
  Eigen::MatrixXd expect = LLT.matrixL() * Y;

  // Do the product using celerite
  celerite::core::dot_l(U, P, a, V, Y);

  double resid = (Y - expect).array().abs().maxCoeff();
  REQUIRE(resid < 1e-12);
}
