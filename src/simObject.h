#ifndef SIMOBJECT_H
#define SIMOBJECT_H

class simObject {
public:
  // initialization routine of object
  virtual void Init();

  // update routine
  virtual void Update();

  // termination routine
  virtual void Terminate();

private:
  // simulation rate. 1: Updates on every iteration; 2: updates every second
  // iteration; 
    int _simrate;
};

#endif