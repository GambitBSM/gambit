#ifndef POINT_COUNTER_HPP
#define POINT_COUNTER_HPP


class point_counter
{

public:
  using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
  using int32 = int32_t;

  point_counter(std::string name)
    : name(name)
  {}

  std::string name;
  static time_point startTime;
  int32 point_count = 0;
  int32 failed_count = 0;
  int32 timer = 0;
  
  void count()
  {
    time_point currTime = std::chrono::high_resolution_clock::now();
    double totalDur = std::chrono::duration<double>(currTime - startTime).count();

    if (timer < totalDur && point_count > 0)
    {
      timer += 20;
      std::cout << std::setw(20) << name << " failed: " << failed_count << "/" << point_count << " (" << (100*failed_count)/point_count << "%)\n";
    }

    ++point_count;
  }
  
  void count_invalid()
  {
    ++failed_count;
  }
};

#endif // POINT_COUNTER_HPP