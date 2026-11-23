#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <cstddef>

class Hittable {
private:
  size_t remainingHits;

public:
  explicit Hittable(size_t remainingHits) : remainingHits(remainingHits) {}
  virtual ~Hittable() = default;

  size_t getHitsLeft() const { return remainingHits; }

  /*
   * Golpea, en caso de alcanzar los hits necesarios devuelve true.
   */
  virtual bool hit(size_t damage = 1) {
    if (damage >= remainingHits)
      remainingHits = 0;
    else
      remainingHits -= damage;

    return remainingHits == 0;
  }

  void restoreHits(size_t hits) { remainingHits = hits; }
};

#endif // HITTABLE_H_
