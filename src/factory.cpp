#include "factory.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "observer.hpp"

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
  std::shared_ptr<NPC> result;

  switch (type) {
    case OrcType:
      result = std::make_shared<Orc>(x, y);
      break;
    case BearType:
      result = std::make_shared<Bear>(x, y);
      break;
    case SquirrelType:
      result = std::make_shared<Squirrel>(x, y);
      break;
    default:
      break;
  }

  if (result) {
    result->subscribe(TextObserver::get());
    result->subscribe(FileObserver::get());
  }

  return result;
}

std::shared_ptr<NPC> factory(std::istream &is) {
  std::shared_ptr<NPC> result;
  int type = 0;

  if (is >> type) {
    int x, y;

    if (!(is >> x >> y)) {
      std::cerr << "Invalid NPC entry in file\n";
      return nullptr;
    }

    switch (type) {
      case OrcType:
        result = std::make_shared<Orc>(x, y);
        break;
      case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
      case SquirrelType:
        result = std::make_shared<Squirrel>(x, y);
        break;
      default:
        std::cerr << "Unknown NPC type: " << type << "\n";
        return nullptr;
    }
  }

  if (result) {
    result->subscribe(TextObserver::get());
    result->subscribe(FileObserver::get());
  }

  return result;
}