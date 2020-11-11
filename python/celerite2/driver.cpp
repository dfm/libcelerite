// NOTE: This file was autogenerated
// NOTE: Changes should be made to the template

#include <pybind11/pybind11.h>
#include <cmath>
#include "driver.hpp"

namespace py = pybind11;

namespace celerite2 {
namespace driver {

auto factor (
    py::array_t<double, py::array::c_style> t,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> a,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> V,
    py::array_t<double, py::array::c_style> d,
    py::array_t<double, py::array::c_style> W
) {
    // Request buffers
    py::buffer_info tbuf = t.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info abuf = a.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Vbuf = V.request();
    py::buffer_info dbuf = d.request();
    py::buffer_info Wbuf = W.request();

    // Parse dimensions
    if (tbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t");
    ssize_t N = tbuf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];

    // Check shapes
    if (tbuf.ndim != 1 || tbuf.shape[0] != N) throw std::invalid_argument("Invalid shape: t");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (abuf.ndim != 1 || abuf.shape[0] != N) throw std::invalid_argument("Invalid shape: a");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Vbuf.ndim != 2 || Vbuf.shape[0] != N || Vbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: V");
    if (dbuf.ndim != 1 || dbuf.shape[0] != N) throw std::invalid_argument("Invalid shape: d");
    if (Wbuf.ndim != 2 || Wbuf.shape[0] != N || Wbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: W");

    Eigen::Index flag = 0;
#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t_((const double *)tbuf.ptr, N, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::VectorXd> a_((const double *)abuf.ptr, N, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> V_((const double *)Vbuf.ptr, N, J); \
    Eigen::Map<Eigen::VectorXd> d_((double *)dbuf.ptr, N, 1); \
    Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> W_((double *)Wbuf.ptr, N, J); \
    flag = celerite2::core::factor(t_, c_, a_, U_, V_, d_, W_); \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP
    if (flag) throw driver_linalg_exception();
    return std::make_tuple(d, W);
}

auto solve_lower (
    py::array_t<double, py::array::c_style> t,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> W,
    py::array_t<double, py::array::c_style> Y,
    py::array_t<double, py::array::c_style> Z
) {
    // Request buffers
    py::buffer_info tbuf = t.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Wbuf = W.request();
    py::buffer_info Ybuf = Y.request();
    py::buffer_info Zbuf = Z.request();

    // Parse dimensions
    if (tbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t");
    ssize_t N = tbuf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];
    if (Ybuf.ndim <= 1)
        throw std::invalid_argument("Invalid number of dimensions: Y");
    ssize_t nrhs = Ybuf.shape[1];

    // Check shapes
    if (tbuf.ndim != 1 || tbuf.shape[0] != N) throw std::invalid_argument("Invalid shape: t");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Wbuf.ndim != 2 || Wbuf.shape[0] != N || Wbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: W");
    if (Ybuf.ndim != 2 || Ybuf.shape[0] != N || Ybuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Y");
    if (Zbuf.ndim != 2 || Zbuf.shape[0] != N || Zbuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Z");

#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t_((const double *)tbuf.ptr, N, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> W_((const double *)Wbuf.ptr, N, J); \
    if (nrhs == 1) { \
        Eigen::Map<const Eigen::VectorXd> Y_((const double *)Ybuf.ptr, N, 1); \
        Eigen::Map<Eigen::VectorXd> Z_((double *)Zbuf.ptr, N, 1); \
        celerite2::core::solve_lower(t_, c_, U_, W_, Y_, Z_); \
    } else { \
        Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_((const double *)Ybuf.ptr, N, nrhs); \
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Z_((double *)Zbuf.ptr, N, nrhs); \
        celerite2::core::solve_lower(t_, c_, U_, W_, Y_, Z_); \
    } \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP

    return Z;
}

auto solve_upper (
    py::array_t<double, py::array::c_style> t,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> W,
    py::array_t<double, py::array::c_style> Y,
    py::array_t<double, py::array::c_style> Z
) {
    // Request buffers
    py::buffer_info tbuf = t.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Wbuf = W.request();
    py::buffer_info Ybuf = Y.request();
    py::buffer_info Zbuf = Z.request();

    // Parse dimensions
    if (tbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t");
    ssize_t N = tbuf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];
    if (Ybuf.ndim <= 1)
        throw std::invalid_argument("Invalid number of dimensions: Y");
    ssize_t nrhs = Ybuf.shape[1];

    // Check shapes
    if (tbuf.ndim != 1 || tbuf.shape[0] != N) throw std::invalid_argument("Invalid shape: t");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Wbuf.ndim != 2 || Wbuf.shape[0] != N || Wbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: W");
    if (Ybuf.ndim != 2 || Ybuf.shape[0] != N || Ybuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Y");
    if (Zbuf.ndim != 2 || Zbuf.shape[0] != N || Zbuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Z");

#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t_((const double *)tbuf.ptr, N, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> W_((const double *)Wbuf.ptr, N, J); \
    if (nrhs == 1) { \
        Eigen::Map<const Eigen::VectorXd> Y_((const double *)Ybuf.ptr, N, 1); \
        Eigen::Map<Eigen::VectorXd> Z_((double *)Zbuf.ptr, N, 1); \
        celerite2::core::solve_upper(t_, c_, U_, W_, Y_, Z_); \
    } else { \
        Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_((const double *)Ybuf.ptr, N, nrhs); \
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Z_((double *)Zbuf.ptr, N, nrhs); \
        celerite2::core::solve_upper(t_, c_, U_, W_, Y_, Z_); \
    } \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP

    return Z;
}

auto matmul_lower (
    py::array_t<double, py::array::c_style> t,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> V,
    py::array_t<double, py::array::c_style> Y,
    py::array_t<double, py::array::c_style> Z
) {
    // Request buffers
    py::buffer_info tbuf = t.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Vbuf = V.request();
    py::buffer_info Ybuf = Y.request();
    py::buffer_info Zbuf = Z.request();

    // Parse dimensions
    if (tbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t");
    ssize_t N = tbuf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];
    if (Ybuf.ndim <= 1)
        throw std::invalid_argument("Invalid number of dimensions: Y");
    ssize_t nrhs = Ybuf.shape[1];

    // Check shapes
    if (tbuf.ndim != 1 || tbuf.shape[0] != N) throw std::invalid_argument("Invalid shape: t");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Vbuf.ndim != 2 || Vbuf.shape[0] != N || Vbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: V");
    if (Ybuf.ndim != 2 || Ybuf.shape[0] != N || Ybuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Y");
    if (Zbuf.ndim != 2 || Zbuf.shape[0] != N || Zbuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Z");

#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t_((const double *)tbuf.ptr, N, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> V_((const double *)Vbuf.ptr, N, J); \
    if (nrhs == 1) { \
        Eigen::Map<const Eigen::VectorXd> Y_((const double *)Ybuf.ptr, N, 1); \
        Eigen::Map<Eigen::VectorXd> Z_((double *)Zbuf.ptr, N, 1); \
        celerite2::core::matmul_lower(t_, c_, U_, V_, Y_, Z_); \
    } else { \
        Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_((const double *)Ybuf.ptr, N, nrhs); \
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Z_((double *)Zbuf.ptr, N, nrhs); \
        celerite2::core::matmul_lower(t_, c_, U_, V_, Y_, Z_); \
    } \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP

    return Z;
}

auto matmul_upper (
    py::array_t<double, py::array::c_style> t,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> V,
    py::array_t<double, py::array::c_style> Y,
    py::array_t<double, py::array::c_style> Z
) {
    // Request buffers
    py::buffer_info tbuf = t.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Vbuf = V.request();
    py::buffer_info Ybuf = Y.request();
    py::buffer_info Zbuf = Z.request();

    // Parse dimensions
    if (tbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t");
    ssize_t N = tbuf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];
    if (Ybuf.ndim <= 1)
        throw std::invalid_argument("Invalid number of dimensions: Y");
    ssize_t nrhs = Ybuf.shape[1];

    // Check shapes
    if (tbuf.ndim != 1 || tbuf.shape[0] != N) throw std::invalid_argument("Invalid shape: t");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Vbuf.ndim != 2 || Vbuf.shape[0] != N || Vbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: V");
    if (Ybuf.ndim != 2 || Ybuf.shape[0] != N || Ybuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Y");
    if (Zbuf.ndim != 2 || Zbuf.shape[0] != N || Zbuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Z");

#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t_((const double *)tbuf.ptr, N, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> V_((const double *)Vbuf.ptr, N, J); \
    if (nrhs == 1) { \
        Eigen::Map<const Eigen::VectorXd> Y_((const double *)Ybuf.ptr, N, 1); \
        Eigen::Map<Eigen::VectorXd> Z_((double *)Zbuf.ptr, N, 1); \
        celerite2::core::matmul_upper(t_, c_, U_, V_, Y_, Z_); \
    } else { \
        Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_((const double *)Ybuf.ptr, N, nrhs); \
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Z_((double *)Zbuf.ptr, N, nrhs); \
        celerite2::core::matmul_upper(t_, c_, U_, V_, Y_, Z_); \
    } \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP

    return Z;
}

auto general_matmul_lower (
    py::array_t<double, py::array::c_style> t1,
    py::array_t<double, py::array::c_style> t2,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> V,
    py::array_t<double, py::array::c_style> Y,
    py::array_t<double, py::array::c_style> Z
) {
    // Request buffers
    py::buffer_info t1buf = t1.request();
    py::buffer_info t2buf = t2.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Vbuf = V.request();
    py::buffer_info Ybuf = Y.request();
    py::buffer_info Zbuf = Z.request();

    // Parse dimensions
    if (t1buf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t1");
    ssize_t N = t1buf.shape[0];
    if (t2buf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t2");
    ssize_t M = t2buf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];
    if (Ybuf.ndim <= 1)
        throw std::invalid_argument("Invalid number of dimensions: Y");
    ssize_t nrhs = Ybuf.shape[1];

    // Check shapes
    if (t1buf.ndim != 1 || t1buf.shape[0] != N) throw std::invalid_argument("Invalid shape: t1");
    if (t2buf.ndim != 1 || t2buf.shape[0] != M) throw std::invalid_argument("Invalid shape: t2");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Vbuf.ndim != 2 || Vbuf.shape[0] != M || Vbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: V");
    if (Ybuf.ndim != 2 || Ybuf.shape[0] != M || Ybuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Y");
    if (Zbuf.ndim != 2 || Zbuf.shape[0] != N || Zbuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Z");

#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t1_((const double *)t1buf.ptr, N, 1); \
    Eigen::Map<const Eigen::VectorXd> t2_((const double *)t2buf.ptr, M, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> V_((const double *)Vbuf.ptr, M, J); \
    if (nrhs == 1) { \
        Eigen::Map<const Eigen::VectorXd> Y_((const double *)Ybuf.ptr, M, 1); \
        Eigen::Map<Eigen::VectorXd> Z_((double *)Zbuf.ptr, N, 1); \
        celerite2::core::general_matmul_lower(t1_, t2_, c_, U_, V_, Y_, Z_); \
    } else { \
        Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_((const double *)Ybuf.ptr, M, nrhs); \
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Z_((double *)Zbuf.ptr, N, nrhs); \
        celerite2::core::general_matmul_lower(t1_, t2_, c_, U_, V_, Y_, Z_); \
    } \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP

    return Z;
}

auto general_matmul_upper (
    py::array_t<double, py::array::c_style> t1,
    py::array_t<double, py::array::c_style> t2,
    py::array_t<double, py::array::c_style> c,
    py::array_t<double, py::array::c_style> U,
    py::array_t<double, py::array::c_style> V,
    py::array_t<double, py::array::c_style> Y,
    py::array_t<double, py::array::c_style> Z
) {
    // Request buffers
    py::buffer_info t1buf = t1.request();
    py::buffer_info t2buf = t2.request();
    py::buffer_info cbuf = c.request();
    py::buffer_info Ubuf = U.request();
    py::buffer_info Vbuf = V.request();
    py::buffer_info Ybuf = Y.request();
    py::buffer_info Zbuf = Z.request();

    // Parse dimensions
    if (t1buf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t1");
    ssize_t N = t1buf.shape[0];
    if (t2buf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: t2");
    ssize_t M = t2buf.shape[0];
    if (cbuf.ndim <= 0)
        throw std::invalid_argument("Invalid number of dimensions: c");
    ssize_t J = cbuf.shape[0];
    if (Ybuf.ndim <= 1)
        throw std::invalid_argument("Invalid number of dimensions: Y");
    ssize_t nrhs = Ybuf.shape[1];

    // Check shapes
    if (t1buf.ndim != 1 || t1buf.shape[0] != N) throw std::invalid_argument("Invalid shape: t1");
    if (t2buf.ndim != 1 || t2buf.shape[0] != M) throw std::invalid_argument("Invalid shape: t2");
    if (cbuf.ndim != 1 || cbuf.shape[0] != J) throw std::invalid_argument("Invalid shape: c");
    if (Ubuf.ndim != 2 || Ubuf.shape[0] != N || Ubuf.shape[1] != J) throw std::invalid_argument("Invalid shape: U");
    if (Vbuf.ndim != 2 || Vbuf.shape[0] != M || Vbuf.shape[1] != J) throw std::invalid_argument("Invalid shape: V");
    if (Ybuf.ndim != 2 || Ybuf.shape[0] != M || Ybuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Y");
    if (Zbuf.ndim != 2 || Zbuf.shape[0] != N || Zbuf.shape[1] != nrhs) throw std::invalid_argument("Invalid shape: Z");

#define FIXED_SIZE_MAP(SIZE) \
    { \
    Eigen::Map<const Eigen::VectorXd> t1_((const double *)t1buf.ptr, N, 1); \
    Eigen::Map<const Eigen::VectorXd> t2_((const double *)t2buf.ptr, M, 1); \
    Eigen::Map<const Eigen::Matrix<double, SIZE, 1>> c_((const double *)cbuf.ptr, J, 1); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> U_((const double *)Ubuf.ptr, N, J); \
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, SIZE, order<SIZE>::value>> V_((const double *)Vbuf.ptr, M, J); \
    if (nrhs == 1) { \
        Eigen::Map<const Eigen::VectorXd> Y_((const double *)Ybuf.ptr, M, 1); \
        Eigen::Map<Eigen::VectorXd> Z_((double *)Zbuf.ptr, N, 1); \
        celerite2::core::general_matmul_upper(t1_, t2_, c_, U_, V_, Y_, Z_); \
    } else { \
        Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_((const double *)Ybuf.ptr, M, nrhs); \
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Z_((double *)Zbuf.ptr, N, nrhs); \
        celerite2::core::general_matmul_upper(t1_, t2_, c_, U_, V_, Y_, Z_); \
    } \
    }
    UNWRAP_CASES_MOST
#undef FIXED_SIZE_MAP

    return Z;
}

auto get_celerite_matrices(
    py::array_t<double, py::array::c_style> ar_in,
    py::array_t<double, py::array::c_style> ac_in,
    py::array_t<double, py::array::c_style> bc_in,
    py::array_t<double, py::array::c_style> dc_in,
    py::array_t<double, py::array::c_style> x_in,
    py::array_t<double, py::array::c_style> diag_in,
    py::array_t<double, py::array::c_style> a_out,
    py::array_t<double, py::array::c_style> U_out,
    py::array_t<double, py::array::c_style> V_out
) {
    auto ar = ar_in.unchecked<1>();
    auto ac = ac_in.unchecked<1>();
    auto bc = bc_in.unchecked<1>();
    auto dc = dc_in.unchecked<1>();

    auto x    = x_in.unchecked<1>();
    auto diag = diag_in.unchecked<1>();

    auto a = a_out.mutable_unchecked<1>();
    auto U = U_out.mutable_unchecked<2>();
    auto V = V_out.mutable_unchecked<2>();

    ssize_t N = x.shape(0), Jr = ar.shape(0), Jc = ac.shape(0), J = Jr + 2 * Jc;

    if (bc.shape(0) != Jc) throw std::invalid_argument("dimension mismatch: bc");
    if (dc.shape(0) != Jc) throw std::invalid_argument("dimension mismatch: dc");

    if (diag.shape(0) != N) throw std::invalid_argument("dimension mismatch: diag");

    if (a.shape(0) != N) throw std::invalid_argument("dimension mismatch: a");
    if (U.shape(0) != N || U.shape(1) != J) throw std::invalid_argument("dimension mismatch: U");
    if (V.shape(0) != N || V.shape(1) != J) throw std::invalid_argument("dimension mismatch: V");

    double sum = 0.0;
    for (ssize_t j = 0; j < Jr; ++j) sum += ar(j);
    for (ssize_t j = 0; j < Jc; ++j) sum += ac(j);

    for (ssize_t n = 0; n < N; ++n) {
        a(n) = diag(n) + sum;
        for (ssize_t j = 0; j < Jr; ++j) {
            V(n, j) = 1.0;
            U(n, j) = ar(j);
        }
        for (ssize_t j = 0, ind = Jr; j < Jc; ++j, ind += 2) {
            double arg = dc(j) * x(n);
            double cos = V(n, ind) = std::cos(arg);
            double sin = V(n, ind + 1) = std::sin(arg);

            U(n, ind)     = ac(j) * cos + bc(j) * sin;
            U(n, ind + 1) = ac(j) * sin - bc(j) * cos;
        }
    }

    return std::make_tuple(a_out, U_out, V_out);
}

} // namespace driver
} // namespace celerite2

PYBIND11_MODULE(driver, m) {
    py::register_exception<celerite2::driver::driver_linalg_exception>(m, "LinAlgError");
    m.def("factor", &celerite2::driver::factor);
    m.def("solve_lower", &celerite2::driver::solve_lower);
    m.def("solve_upper", &celerite2::driver::solve_upper);
    m.def("matmul_lower", &celerite2::driver::matmul_lower);
    m.def("matmul_upper", &celerite2::driver::matmul_upper);
    m.def("general_matmul_lower", &celerite2::driver::general_matmul_lower);
    m.def("general_matmul_upper", &celerite2::driver::general_matmul_upper);

    m.def("get_celerite_matrices", &celerite2::driver::get_celerite_matrices);

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}
