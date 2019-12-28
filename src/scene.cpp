#include <specula/scene.hpp>

specula::Scene *specula::Scene::instance = new specula::Scene();

std::map<unsigned long, unsigned long>
specula::Scene::get_material_map() const {
  std::map<unsigned long, unsigned long> uuid_id_map;
  for (std::size_t i = 0; i < materials.size(); ++i) {
    uuid_id_map[materials[i]->uuid] = i;
  }
  return uuid_id_map;
}
std::map<unsigned long, unsigned long> specula::Scene::get_visible_map() const {
  std::map<unsigned long, unsigned long> uuid_id_map;
  unsigned long j = 0;
  for (std::size_t i = 0; i < objects.size(); ++i) {
    if (objects[i]->material != nullptr) {
      uuid_id_map[objects[i]->uuid] = j;
      j++;
    }
  }
  return uuid_id_map;
}

std::vector<std::shared_ptr<specula::Object>>
specula::Scene::get_visible() const {
  std::vector<std::shared_ptr<Object>> visible_objects;
  std::copy_if(
      objects.begin(), objects.end(), std::back_inserter(visible_objects),
      [](const std::shared_ptr<Object> &o) { return o->material != nullptr; });
  return visible_objects;
}