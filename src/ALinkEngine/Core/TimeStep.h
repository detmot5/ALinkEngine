#ifndef ALINKENGINE_CORE_TIMESTEP_H_
#define ALINKENGINE_CORE_TIMESTEP_H_

namespace ALink {
class TimeStep {
 public:
  TimeStep(float seconds) : seconds(seconds) {}
  float GetSeconds() { return seconds; }
  float GetMiliseconds() { return seconds * 1000.0f; }
  operator float() { return GetSeconds(); }

 private:
  float seconds = 0.0f;
};


}  // namespace ALink



#endif  // ALINKENGINE_CORE_TIMESTEP_H_

