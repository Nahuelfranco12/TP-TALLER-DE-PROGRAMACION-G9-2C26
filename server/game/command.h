#ifndef COMMAND_H_
#define COMMAND_H_

class World;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(World& world) = 0;
};

#endif // COMMAND_H_
