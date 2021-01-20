#include <optional>
#include <string>
#include <iostream>

std::optional<int> asInt(const std::string& s)
{
  try {
    return std::stoi(s);
  }
  catch (std::invalid_argument&) {}
  catch (std::out_of_range&) {}
  return std::nullopt;
}

int main()
{
  std::optional<int> oi = asInt("hello");
  if (oi) 
    std::cout<<"converted s to "<<*oi<<"\n";
  else
    std::cout<<"can't convert\n";
}