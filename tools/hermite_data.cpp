
#include <boost/math/tools/ntl.hpp>
#include <boost/math/tools/test_data.hpp>
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/math/special_functions/hermite.hpp>
#include <fstream>
#include <boost/math/tools/test_data.hpp>
#include <boost/tr1/random.hpp>

using namespace boost::math::tools;
using namespace boost::math;
using namespace std;


template<class T>
std::tr1::tuple<T, T, T> hermite_data(T n, T x)
{
   n = floor(n);
   T r1 = hermite(boost::math::tools::real_cast<unsigned>(n), x);
   return std::tr1::make_tuple(n, x, r1);
}
   
int test_main(int argc, char*argv [])
{
   using namespace boost::math::tools;

   NTL::RR::SetOutputPrecision(50);
   NTL::RR::SetPrecision(1000);

   parameter_info<NTL::RR> arg1, arg2, arg3;
   test_data<NTL::RR> data;

   std::cout << boost::math::hermite(10, static_cast<NTL::RR>(1e300)) << std::endl;

   bool cont;
   std::string line;

   if(argc < 1)
      return 1;

   do{
      if(0 == get_user_parameter_info(arg1, "n"))
         return 1;
      if(0 == get_user_parameter_info(arg2, "x"))
         return 1;
      arg1.type |= dummy_param;
      arg2.type |= dummy_param;

      data.insert(&hermite_data<NTL::RR>, arg1, arg2);

      std::cout << "Any more data [y/n]?";
      std::getline(std::cin, line);
      boost::algorithm::trim(line);
      cont = (line == "y");
   }while(cont);

   std::cout << "Enter name of test data file [default=hermite.ipp]";
   std::getline(std::cin, line);
   boost::algorithm::trim(line);
   if(line == "")
      line = "hermite.ipp";
   std::ofstream ofs(line.c_str());
   line.erase(line.find('.'));
   ofs << std::scientific;
   write_code(ofs, data, line.c_str());

   return 0;
}

