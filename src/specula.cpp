#include "specula/specula.hpp"

#include <glm/glm.hpp>
#include <thread>

#include "specula/cli/progress_bar.hpp"
#include "specula/fs.hpp"
#include "specula/image/image.hpp"

void specula::render(const std::vector<std::shared_ptr<Primative>> &objs,
                     const std::vector<std::shared_ptr<Material>> &mats,
                     const std::size_t &spp, const std::size_t &img_width,
                     const std::size_t &img_height,
                     const std::string &output_path, std::size_t index,
                     bool sequence) {
  std::string output_file = output_path;
  if (sequence) {
    std::string directory =
        output_path.substr(0, output_path.find_last_of('.'));
    if (fs::exists(directory)) {
      fs::remove_all(directory);
    }
    fs::create_directory(directory);
    output_file = fmt::format(
        "%s/%lu%s", directory.c_str(), index,
        output_path
            .substr(output_path.find_last_of('.'),
                    output_path.length() - output_path.find_last_of('.'))
            .c_str());
  }
  std::size_t block_size = std::sqrt(
      img_width * img_height / (16 * std::thread::hardware_concurrency()));
  std::size_t hblocks = std::ceil(img_width / static_cast<double>(block_size));
  std::size_t vblocks = std::ceil(img_height / static_cast<double>(block_size));
  std::size_t blocks = hblocks * vblocks;

  terminal::ProgressBar progress(
      fmt::format("Rendering %s",
                  sequence ? std::to_string(index) : output_file),
      blocks);

  Image img({img_width, img_height});
  ldebug("%lux%lu", img_width, img_height);
  for (std::size_t i = 0; i < blocks; ++i) {
    std::array<double, 3> c = {{rand() / (double)RAND_MAX,
                                rand() / (double)RAND_MAX,
                                rand() / (double)RAND_MAX}};
    linfo("%lu: X: %lu-%lu Y:%lu-%lu", i, (i % hblocks) * block_size,
          std::min(((i % hblocks) + 1) * block_size, img_width), (i / hblocks) * block_size, std::min(((i / hblocks) + 1) * block_size, img_height));
    for (std::size_t x = (i % hblocks) * block_size;
         x < std::min(((i % hblocks) + 1) * block_size, img_width); ++x) {
      for (std::size_t y = (i / hblocks) * block_size;
           y < std::min(((i / hblocks) + 1) * block_size, img_height); ++y) {
        img(x, y) = c;
      }
    }
    // progress();
  }
  img.write(output_file);
}
