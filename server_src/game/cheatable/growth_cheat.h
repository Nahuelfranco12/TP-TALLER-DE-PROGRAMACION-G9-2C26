#ifndef GROWTH_CHEAT_H_
#define GROWTH_CHEAT_H_

class IGrowthCheat {
public:
  virtual ~IGrowthCheat() = default;

  virtual void growthCheat() = 0;
};

#endif // GROWTH_CHEAT_H_