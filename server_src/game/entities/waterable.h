#ifndef WATERABLE_H_
#define WATERABLE_H_

class IWaterable {
public:
  virtual ~IWaterable() = default;

  virtual bool needsWater() const = 0;

  virtual bool water() = 0;

  virtual double waterEnergyCost() const = 0;
};

#endif // WATERABLE_H_
