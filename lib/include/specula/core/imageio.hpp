#ifndef SPECULA_CORE_IMAGEIO_HPP_
#define SPECULA_CORE_IMAGEIO_HPP_

#include "geometry.hpp"
#include "spectrum.hpp"
#include "specula/global.hpp"

#include <filesystem>
#include <memory>

/**
 * @defgroup core-imageio ImageIO
 * @ingroup core
 *
 * These function control the image IO for the renderer. Currently the image IO
 * uses [CImg](http://cimg.eu/). This provides a basic interface for a wide
 * selection of image formats. However, it would be preferred to load the images
 * using a more standardized library, or specific libraries for each image type.
 *
 * The current industry standard is to use
 * [OpenImageIO](https://github.com/OpenImageIO/oiio), which scans the current
 * system for supported libraries, and interfaces with each library
 * accordingly. OIIO provides IO for practically all image formats, and even
 * some video formats. However, to compile OpenImageIO, requires ``Boost``,
 * ``libjpeg``, ``libtiff``, ``libpng``, and ``OpenEXR`` to be *installed* on
 * the system. This unfortunately means that they cannot just be submodules. It
 * may be possible to trick OpenImageIO to look in our build directory, so we
 * can build each of these individually.
 *
 * @todo Convert the image io to use OIIO, or alternatively finish the
 * implementation for [ImageIO](https://github.com/LuxAter/ImageIO), and use
 * that.
 */

namespace specula {
std::unique_ptr<RGBSpectrum[]> read_image(const std::string &name,
                                          Point2i *resolution);
bool write_image(const std::string &name, const Float *rgb,
                 const Bounds2i &output_bounds,
                 const Point2i &total_resolution);

RGBSpectrum *read_image_exr(const std::filesystem::path &filepath, int *width,
                            int *height, Bounds2i *data_window = nullptr,
                            Bounds2i *display_window = nullptr);
RGBSpectrum *read_image_png(const std::filesystem::path &filepath, int *width,
                            int *height);
RGBSpectrum *read_image_bmp(const std::filesystem::path &filepath, int *width,
                            int *height);
RGBSpectrum *read_image_tga(const std::filesystem::path &filepath, int *width,
                            int *height);
RGBSpectrum *read_image_jpg(const std::filesystem::path &filepath, int *width,
                            int *height);
RGBSpectrum *read_image_hdr(const std::filesystem::path &filepath, int *width,
                            int *height);

bool write_image_exr(const std::filesystem::path &filepath, const Float *pixels,
                     int x_res, int y_res, int total_x_res, int total_y_res,
                     int x_offset, int y_offset);
bool write_image_png(const std::filesystem::path &filepath,
                     const std::uint8_t *pixels, int x_res, int y_res,
                     int total_x_res, int total_y_res, int x_offset,
                     int y_offset);
bool write_image_bmp(const std::filesystem::path &filepath,
                     const std::uint8_t *pixels, int x_res, int y_res,
                     int total_x_res, int total_y_res, int x_offset,
                     int y_offset);
bool write_image_tga(const std::filesystem::path &filepath,
                     const std::uint8_t *pixels, int x_res, int y_res,
                     int total_x_res, int total_y_res, int x_offset,
                     int y_offset);
bool write_image_jpg(const std::filesystem::path &filepath,
                     const std::uint8_t *pixels, int x_res, int y_res,
                     int total_x_res, int total_y_res, int x_offset,
                     int y_offset);
bool write_image_hdr(const std::filesystem::path &filepath, const float *pixels,
                     int x_res, int y_res, int total_x_res, int total_y_res,
                     int x_offset, int y_offset);
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_IMAGEIO_HPP_ */
