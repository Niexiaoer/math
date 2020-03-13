/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <cstdint>
#include <boost/math/quadrature/wavelet_transforms.hpp>
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/image.hpp>
#include <Eigen/Dense>

namespace bg = boost::gil;
/*
int main(int argc, char *argv[])
{
    int height = 1000;
    int width = 1.618*height;
    auto img = bg::gray16_image_t{width, height, bg::gray16_pixel_t {0}};
    auto view = bg::view(img);
    auto count = std::uint16_t {0};
    for (auto it = view.begin(); it != view.end(); ++it)
    {
        *it = count++;
    }

    //bg::write_view("img.png", bg::const_view(img), bg::png_tag());
    bg::write_view("img.jpeg", bg::const_view(img), bg::png_tag());
    return 0;
}*/

int main()
{
    using boost::math::quadrature::daubechies_wavelet_transform;
    double a = 1.3;
    auto f = [&a](double t) {
        if(t==0) {
            return double(0);
        }
        return std::sin(a/t);
    };

    auto Wf = daubechies_wavelet_transform<decltype(f), double, 8>(f);

    Eigen::MatrixXd grid(512, 512);
    double s = 7;
    double t = 9.2;
    grid(0,0) = Wf(s, t);
    std::cout << "W[f](s,t) = " << grid(0,0) << "\n";
    return 0;
}